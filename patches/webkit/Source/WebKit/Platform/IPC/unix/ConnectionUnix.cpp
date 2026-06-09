#include "config.h"
#include "Connection.h"

#include "Decoder.h"
#include "Encoder.h"
#include "IPCUtilities.h"
#include "UnixMessage.h"
#include "SharedMemory.h"
#include <errno.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <wtf/Assertions.h>
#include <wtf/FastMalloc.h>
#include <wtf/SafeStrerror.h>

#if USE(GLIB)
#include <gio/gio.h>
#include <glib.h>
#endif

#if OS(DARWIN)
#define MSG_NOSIGNAL 0
#endif

// Although it's available on Darwin, SOCK_SEQPACKET seems to work differently
// than in traditional Unix so fallback to STREAM on that platform.
#if defined(SOCK_SEQPACKET) && !OS(DARWIN)
#define SOCKET_TYPE SOCK_SEQPACKET
#else
#if USE(GLIB)
#define SOCKET_TYPE SOCK_STREAM
#else
#define SOCKET_TYPE SOCK_DGRAM
#endif
#endif // SOCK_SEQPACKET

// Hajr FFI Declarations
extern "C" {
    typedef struct C_HardenedRingBuffer C_HardenedRingBuffer;
    void* Zawra_Hajr_MapBootstrapRingWithSignal(uint64_t id, int signal_fd);
    void hajr_ring_free(C_HardenedRingBuffer*);
    int32_t hajr_ring_write(C_HardenedRingBuffer*, const uint8_t* data, size_t length);
    int32_t hajr_ring_read(C_HardenedRingBuffer*, uint8_t* buf, size_t length, size_t* bytes_read);
    int32_t hajr_ring_signal(C_HardenedRingBuffer*);
    int32_t hajr_ring_wait(C_HardenedRingBuffer*);
    int32_t hajr_ring_get_signal_fd(C_HardenedRingBuffer*);
    int32_t hajr_ipc_send_fd(C_HardenedRingBuffer*, int fd);
    int32_t hajr_ipc_recv_fd(C_HardenedRingBuffer*, int handle);
    void hajr_ipc_set_other_pidfd(int pidfd);
    uint32_t hajr_ipc_message_checksum(const uint8_t* header, size_t header_len, const uint8_t* payload, size_t payload_len);
    bool hajr_ipc_verify_checksum(const uint8_t* header, size_t header_len, const uint8_t* payload, size_t payload_len, uint32_t expected_checksum);
}

namespace IPC {

static const size_t messageMaxSize = 4096;
static const size_t attachmentMaxAmount = 254;

class AttachmentInfo {
    WTF_MAKE_FAST_ALLOCATED;
public:
    AttachmentInfo() { memset(static_cast<void*>(this), 0, sizeof(*this)); }
    AttachmentInfo(const AttachmentInfo& info) { *this = info; }
    void setNull() { m_isNull = true; }
    bool isNull() const { return m_isNull; }
private:
    bool m_isNull;
};

void Connection::platformInitialize(Identifier identifier)
{
    m_socketDescriptor = identifier.handle;
#if USE(GLIB)
    m_socket = adoptGRef(g_socket_new_from_fd(m_socketDescriptor, nullptr));
#endif
    m_readBuffer.reserveInitialCapacity(messageMaxSize);
    m_fileDescriptors.reserveInitialCapacity(attachmentMaxAmount);
}

bool Connection::platformPrepareForOpen()
{
    // The default inline implementation in Connection.cpp is gated by
    // !USE(UNIX_DOMAIN_SOCKETS), so we must provide our own for Unix.
    // Returning true defers all real work to platformOpen(), which is
    // where Hajr bootstrap and the socket monitor start.
    return true;
}

void Connection::platformInvalidate()
{
    if (m_inboundRing) {
        hajr_ring_free(m_inboundRing);
        m_inboundRing = nullptr;
    }
    if (m_outboundRing) {
        hajr_ring_free(m_outboundRing);
        m_outboundRing = nullptr;
    }

    if (!m_isConnected)
        return;

    m_readSocketMonitor.stop();
    m_writeSocketMonitor.stop();

#if USE(GLIB)
    m_hajrSignalSocket = nullptr;
#endif

    m_socketDescriptor = -1;
    m_isConnected = false;
}
static ssize_t readBytesFromSocket(int socketDescriptor, Vector<uint8_t>& buffer, Vector<int>& fileDescriptors)
{
    struct msghdr message;
    memset(&message, 0, sizeof(message));

    struct iovec iov[1];
    memset(&iov, 0, sizeof(iov));

    message.msg_controllen = CMSG_SPACE(sizeof(int) * attachmentMaxAmount);
    MallocPtr<char> attachmentDescriptorBuffer = MallocPtr<char>::malloc(sizeof(char) * message.msg_controllen);
    memset(attachmentDescriptorBuffer.get(), 0, sizeof(char) * message.msg_controllen);
    message.msg_control = attachmentDescriptorBuffer.get();

    size_t previousBufferSize = buffer.size();
    buffer.grow(buffer.capacity());
    iov[0].iov_base = buffer.data() + previousBufferSize;
    iov[0].iov_len = buffer.size() - previousBufferSize;

    message.msg_iov = iov;
    message.msg_iovlen = 1;

    while (true) {
        ssize_t bytesRead = recvmsg(socketDescriptor, &message, MSG_NOSIGNAL);

        if (bytesRead < 0) {
            if (errno == EINTR)
                continue;

            buffer.shrink(previousBufferSize);
            return -1;
        }

        if (message.msg_flags & MSG_CTRUNC) {
            // Control data has been discarded, which is expected by processMessage(), so consider this a read failure.
            buffer.shrink(previousBufferSize);
            return -1;
        }

        struct cmsghdr* controlMessage;
        for (controlMessage = CMSG_FIRSTHDR(&message); controlMessage; controlMessage = CMSG_NXTHDR(&message, controlMessage)) {
            if (controlMessage->cmsg_level == SOL_SOCKET && controlMessage->cmsg_type == SCM_RIGHTS) {
                if (controlMessage->cmsg_len < CMSG_LEN(0) || controlMessage->cmsg_len > CMSG_LEN(sizeof(int) * attachmentMaxAmount)) {
                    ASSERT_NOT_REACHED();
                    break;
                }
                size_t previousFileDescriptorsSize = fileDescriptors.size();
                size_t fileDescriptorsCount = (controlMessage->cmsg_len - CMSG_LEN(0)) / sizeof(int);
                fileDescriptors.grow(fileDescriptors.size() + fileDescriptorsCount);
                memcpy(fileDescriptors.data() + previousFileDescriptorsSize, CMSG_DATA(controlMessage), sizeof(int) * fileDescriptorsCount);

                for (size_t i = 0; i < fileDescriptorsCount; ++i) {
                    if (!setCloseOnExec(fileDescriptors[previousFileDescriptorsSize + i])) {
                        ASSERT_NOT_REACHED();
                        break;
                    }
                }
                break;
            }
        }

        buffer.shrink(previousBufferSize + bytesRead);
        return bytesRead;
    }

    return -1;
}

void Connection::readyReadHandler()
{
    if (m_isHajrEnabled && m_inboundRing) {
        // Clear eventfd signal if any
        hajr_ring_wait(m_inboundRing);

        while (true) {
            MessageInfo msgInfo;
            size_t msgInfoBytesRead = 0;
            int32_t res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&msgInfo), sizeof(msgInfo), &msgInfoBytesRead);
            if (res != 1 || msgInfoBytesRead == 0)
                break;

            if (msgInfoBytesRead != sizeof(msgInfo)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - PARTIAL MESSAGE INFO READ\n");
                break;
            }

            uint32_t attachmentCount = 0;
            size_t countRead = 0;
            res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&attachmentCount), sizeof(attachmentCount), &countRead);
            if (res != 1 || countRead != sizeof(attachmentCount)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - FAILED TO READ ATTACHMENT COUNT\n");
                break;
            }

            if (attachmentCount > attachmentMaxAmount) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT COUNT %u EXCEEDS MAXIMUM %zu, POSSIBLE RCE ATTEMPT\n", attachmentCount, attachmentMaxAmount);
                break;
            }

            Vector<Attachment> fds;
            bool attachmentFail = false;
            for (uint32_t i = 0; i < attachmentCount; ++i) {
                int32_t handle;
                size_t handleRead = 0;
                res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&handle), sizeof(handle), &handleRead);
                if (res != 1 || handleRead != sizeof(handle)) {
                    attachmentFail = true;
                    break;
                }
                int fd = hajr_ipc_recv_fd(m_inboundRing, handle);
                if (fd == -1) {
                    attachmentFail = true;
                    break;
                }
                fds.append(Attachment(fd, Attachment::Adopt));
            }

            if (attachmentFail) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT RETRIEVAL FAILED\n");
                break;
            }

            uint8_t* payloadBuffer = static_cast<uint8_t*>(fastMalloc(msgInfo.bodySize()));
            size_t bodyBytesRead = 0;
            res = hajr_ring_read(m_inboundRing, payloadBuffer, msgInfo.bodySize(), &bodyBytesRead);
            if (res != 1 || bodyBytesRead != msgInfo.bodySize()) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - BODY READ FAILED\n");
                fastFree(payloadBuffer);
                break;
            }

            // Read and verify checksum
            uint32_t receivedChecksum = 0;
            size_t checksumRead = 0;
            res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&receivedChecksum), sizeof(receivedChecksum), &checksumRead);
            if (res != 1 || checksumRead != sizeof(receivedChecksum)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - CHECKSUM READ FAILED\n");
                fastFree(payloadBuffer);
                break;
            }

            // Verify checksum over messageInfo + attachmentCount + payload
            // Reconstruct the data for verification (simplified - in production, buffer during read)
            uint32_t computedChecksum = hajr_ipc_message_checksum(
                reinterpret_cast<const uint8_t*>(&msgInfo),
                sizeof(msgInfo),
                payloadBuffer,
                msgInfo.bodySize()
            );
            
            if (computedChecksum != receivedChecksum) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - CHECKSUM MISMATCH: expected 0x%08X, got 0x%08X, POSSIBLE CORRUPTION\n", receivedChecksum, computedChecksum);
                fastFree(payloadBuffer);
                break;
            }

            auto decoder = Decoder::create(
                payloadBuffer,
                msgInfo.bodySize(),
                [](const uint8_t* ptr, size_t) { fastFree(const_cast<uint8_t*>(ptr)); },
                WTFMove(fds)
            );

            if (decoder)
                processIncomingMessage(WTFMove(decoder));
        }
    }

    // Legacy fallback or signals that didn't go through the ring
    while (true) {
        ssize_t bytesRead = readBytesFromSocket(m_socketDescriptor, m_readBuffer, m_fileDescriptors);
        if (bytesRead <= 0)
            break;
        while (processMessage()) { }
    }
}

bool Connection::processMessage()
{
    if (m_readBuffer.size() < sizeof(MessageInfo))
        return false;

    uint8_t* messageData = m_readBuffer.data();
    MessageInfo messageInfo;
    memcpy(static_cast<void*>(&messageInfo), messageData, sizeof(messageInfo));
    messageData += sizeof(messageInfo);

    if (messageInfo.attachmentCount() > attachmentMaxAmount || (!messageInfo.isBodyOutOfLine() && messageInfo.bodySize() > messageMaxSize)) {
        ASSERT_NOT_REACHED();
        return false;
    }

    size_t messageLength = sizeof(MessageInfo) + messageInfo.attachmentCount() * sizeof(AttachmentInfo) + (messageInfo.isBodyOutOfLine() ? 0 : messageInfo.bodySize());
    if (m_readBuffer.size() < messageLength)
        return false;

    size_t attachmentFileDescriptorCount = 0;
    size_t attachmentCount = messageInfo.attachmentCount();
    Vector<AttachmentInfo> attachmentInfo(attachmentCount);

    if (attachmentCount) {
        memcpy(static_cast<void*>(attachmentInfo.data()), messageData, sizeof(AttachmentInfo) * attachmentCount);
        messageData += sizeof(AttachmentInfo) * attachmentCount;

        for (size_t i = 0; i < attachmentCount; ++i) {
            if (!attachmentInfo[i].isNull())
                attachmentFileDescriptorCount++;
        }

        if (messageInfo.isBodyOutOfLine())
            attachmentCount--;
    }

    Vector<Attachment> attachments(attachmentCount);
    RefPtr<WebKit::SharedMemory> oolMessageBody;

    size_t fdIndex = 0;
    for (size_t i = 0; i < attachmentCount; ++i) {
        int fd = !attachmentInfo[i].isNull() ? m_fileDescriptors[fdIndex++] : -1;
        attachments[attachmentCount - i - 1] = UnixFileDescriptor { fd, UnixFileDescriptor::Adopt };
    }

    if (messageInfo.isBodyOutOfLine()) {
        ASSERT(messageInfo.bodySize());

        if (attachmentInfo[attachmentCount].isNull()) {
            ASSERT_NOT_REACHED();
            return false;
        }

        WebKit::SharedMemory::Handle handle;
        handle.m_size = messageInfo.bodySize();
        handle.m_handle = UnixFileDescriptor { m_fileDescriptors[attachmentFileDescriptorCount - 1], UnixFileDescriptor::Adopt };

        oolMessageBody = WebKit::SharedMemory::map(WTFMove(handle), WebKit::SharedMemory::Protection::ReadOnly);
        if (!oolMessageBody) {
            ASSERT_NOT_REACHED();
            return false;
        }
    }

    ASSERT(attachments.size() == (messageInfo.isBodyOutOfLine() ? messageInfo.attachmentCount() - 1 : messageInfo.attachmentCount()));

    uint8_t* messageBody = messageData;
    if (messageInfo.isBodyOutOfLine())
        messageBody = reinterpret_cast<uint8_t*>(oolMessageBody->data());

    auto decoder = Decoder::create(messageBody, messageInfo.bodySize(), WTFMove(attachments));
    ASSERT(decoder);
    if (!decoder)
        return false;

    processIncomingMessage(WTFMove(decoder));

    if (m_readBuffer.size() > messageLength) {
        memmove(m_readBuffer.data(), m_readBuffer.data() + messageLength, m_readBuffer.size() - messageLength);
        m_readBuffer.shrink(m_readBuffer.size() - messageLength);
    } else
        m_readBuffer.shrink(0);

    if (attachmentFileDescriptorCount) {
        if (m_fileDescriptors.size() > attachmentFileDescriptorCount) {
            memmove(m_fileDescriptors.data(), m_fileDescriptors.data() + attachmentFileDescriptorCount, (m_fileDescriptors.size() - attachmentFileDescriptorCount) * sizeof(int));
            m_fileDescriptors.shrink(m_fileDescriptors.size() - attachmentFileDescriptorCount);
        } else
            m_fileDescriptors.shrink(0);
    }

    return true;
}

void Connection::platformOpen()
{
    RefPtr<Connection> protectedThis(this);
    m_isConnected = true;

    const char* ring1Str = getenv("ZAWRA_HAJR_RING1");
    const char* ring2Str = getenv("ZAWRA_HAJR_RING2");
    const char* sig1Str = getenv("ZAWRA_HAJR_SIGNAL1");
    const char* sig2Str = getenv("ZAWRA_HAJR_SIGNAL2");
    const char* parentPidFDStr = getenv("ZAWRA_HAJR_PARENT_PIDFD");

    if (ring1Str && ring2Str && sig1Str && sig2Str) {
        uint64_t ring1 = strtoull(ring1Str, nullptr, 10);
        uint64_t ring2 = strtoull(ring2Str, nullptr, 10);
        int sig1 = atoi(sig1Str);
        int sig2 = atoi(sig2Str);

        if (parentPidFDStr && !m_isServer)
            hajr_ipc_set_other_pidfd(atoi(parentPidFDStr));

        if (m_isServer) {
            m_inboundRing = static_cast<C_HardenedRingBuffer*>(Zawra_Hajr_MapBootstrapRingWithSignal(ring2, sig2));
            m_outboundRing = static_cast<C_HardenedRingBuffer*>(Zawra_Hajr_MapBootstrapRingWithSignal(ring1, sig1));
        } else {
            m_inboundRing = static_cast<C_HardenedRingBuffer*>(Zawra_Hajr_MapBootstrapRingWithSignal(ring1, sig1));
            m_outboundRing = static_cast<C_HardenedRingBuffer*>(Zawra_Hajr_MapBootstrapRingWithSignal(ring2, sig2));
        }
        m_isHajrEnabled = (m_inboundRing && m_outboundRing);
#if USE(GLIB)
        if (m_isHajrEnabled) {
            // Wrap the hajr eventfd signal fd in a *separate* GSocket.
            // We must NOT rewrap m_socket here: the GSocket created in
            // platformInitialize() took ownership of m_socketDescriptor via
            // g_socket_new_from_fd(), and overwriting m_socket would release
            // the old GRefPtr, destroying the GSocket and silently closing
            // the IPC socket fd that the legacy fallback path in
            // readyReadHandler() may still try to read from.
            m_hajrSignalSocket = adoptGRef(g_socket_new_from_fd(hajr_ring_get_signal_fd(m_inboundRing), nullptr));
        }
#endif
    }

#if USE(GLIB)
    GSocket* monitorSocket = m_isHajrEnabled ? m_hajrSignalSocket.get() : m_socket.get();
    if (monitorSocket) {
        m_readSocketMonitor.start(monitorSocket, static_cast<GIOCondition>(G_IO_IN | G_IO_HUP | G_IO_ERR), m_connectionQueue->runLoop(), [protectedThis](GIOCondition condition) -> gboolean {
            if (condition & (G_IO_HUP | G_IO_ERR)) {
                protectedThis->connectionDidClose();
                return G_SOURCE_REMOVE;
            }
            protectedThis->readyReadHandler();
            return G_SOURCE_CONTINUE;
        });
    }
#endif

    m_connectionQueue->dispatch([protectedThis] {
        protectedThis->readyReadHandler();
    });
}

bool Connection::sendOutputMessage(UnixMessage& outputMessage)
{
    if (m_isHajrEnabled && m_outboundRing) {
        auto& messageInfo = outputMessage.messageInfo();
        auto& attachments = outputMessage.attachments();
        uint32_t attachmentCount = attachments.size();
        
        // Size: messageInfo + attachmentCount + handles + body + checksum
        size_t total_size = sizeof(messageInfo) + sizeof(attachmentCount) + (attachmentCount * sizeof(int32_t)) + outputMessage.bodySize() + sizeof(uint32_t);
        Vector<uint8_t> payload(total_size);
        uint8_t* ptr = payload.data();

        memcpy(ptr, &messageInfo, sizeof(messageInfo));
        ptr += sizeof(messageInfo);

        memcpy(ptr, &attachmentCount, sizeof(attachmentCount));
        ptr += sizeof(attachmentCount);

        for (auto& attachment : attachments) {
            int32_t handle = hajr_ipc_send_fd(m_outboundRing, attachment.value());
            memcpy(ptr, &handle, sizeof(handle));
            ptr += sizeof(handle);
        }

        memcpy(ptr, outputMessage.body(), outputMessage.bodySize());

        // Calculate checksum over msgInfo + body (core message integrity)
        uint32_t checksum = hajr_ipc_message_checksum(
            reinterpret_cast<const uint8_t*>(&messageInfo),
            sizeof(messageInfo),
            outputMessage.body(),
            outputMessage.bodySize()
        );
        memcpy(ptr + outputMessage.bodySize(), &checksum, sizeof(checksum));

        if (hajr_ring_write(m_outboundRing, payload.data(), payload.size()) == 1) {
            hajr_ring_signal(m_outboundRing);
            return true;
        }
    }
    return false; 
}

bool Connection::platformCanSendOutgoingMessages() const { return !m_pendingOutputMessage; }

bool Connection::sendOutgoingMessage(UniqueRef<Encoder>&& encoder)
{
    UnixMessage outputMessage(encoder.get());
    return sendOutputMessage(outputMessage);
}
SocketPair createPlatformConnection(unsigned options)
{
    int sockets[2];
    RELEASE_ASSERT(socketpair(AF_UNIX, SOCKET_TYPE, 0, sockets) != -1);

    if (options & SetCloexecOnServer) {
        if (!setCloseOnExec(sockets[1]))
            RELEASE_ASSERT_NOT_REACHED();
    }

    if (options & SetCloexecOnClient) {
        if (!setCloseOnExec(sockets[0]))
            RELEASE_ASSERT_NOT_REACHED();
    }

    SocketPair socketPair = { sockets[0], sockets[1] };
    return socketPair;
}

void Connection::willSendSyncMessage(OptionSet<SendSyncOption>)
{
}

void Connection::didReceiveSyncReply(OptionSet<SendSyncOption>)
{
}

std::optional<Connection::ConnectionIdentifierPair> Connection::createConnectionIdentifierPair()
{
    SocketPair socketPair = createPlatformConnection();
    return ConnectionIdentifierPair { Identifier { UnixFileDescriptor { socketPair.server,  UnixFileDescriptor::Adopt } }, UnixFileDescriptor { socketPair.client, UnixFileDescriptor::Adopt } };
}

} // namespace IPC
