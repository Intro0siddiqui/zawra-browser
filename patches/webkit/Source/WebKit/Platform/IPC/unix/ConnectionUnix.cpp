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
#include <sys/syscall.h>
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
    void* Z_Hajr_MapBootstrapRingWithSignal(uint64_t id, int signal_fd);
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
    // Save per-connection Hajr info from the Identifier so platformOpen()
    // can use it instead of global env vars (which get overwritten when
    // multiple children are launched).
    m_hasHajrInfo = identifier.hasHajrInfo;
    m_hajrRing1 = identifier.hajrRing1;
    m_hajrRing2 = identifier.hajrRing2;
    m_hajrSig1 = identifier.hajrSig1;
    m_hajrSig2 = identifier.hajrSig2;
    m_hajrPidfd = identifier.hajrPidfd;
    m_fdTransferFd = identifier.hajrFdTransferFd;

    if (!m_hasHajrInfo && identifier.handle != -1) {
        // Socketpair-backed IPC connections created by createConnectionIdentifierPair()
        // must use their own descriptor. Do not inherit the UIProcess parent
        // connection's Hajr environment, otherwise secondary connections such as
        // NetworkProcess<->WebProcess read/write on the wrong ring pair.
        m_socketDescriptor = identifier.handle;
#if USE(GLIB)
        m_socket = adoptGRef(g_socket_new_from_fd(m_socketDescriptor, nullptr));
#endif
    } else if (!m_hasHajrInfo) {
        const char* ring1Str = getenv("ZAWRA_HAJR_RING1");
        const char* ring2Str = getenv("ZAWRA_HAJR_RING2");
        const char* sig1Str = getenv("ZAWRA_HAJR_SIGNAL1");
        const char* sig2Str = getenv("ZAWRA_HAJR_SIGNAL2");
        if (ring1Str && ring2Str && sig1Str && sig2Str) {
            m_hajrRing1 = strtoull(ring1Str, nullptr, 10);
            m_hajrRing2 = strtoull(ring2Str, nullptr, 10);
            m_hajrSig1 = atoi(sig1Str);
            m_hajrSig2 = atoi(sig2Str);
            const char* parentPidFDStr = getenv("ZAWRA_HAJR_PARENT_PIDFD");
            m_hajrPidfd = parentPidFDStr ? atoi(parentPidFDStr) : -1;
            const char* fdTransferStr = getenv("ZAWRA_HAJR_FDTRANSFER");
            m_fdTransferFd = fdTransferStr ? atoi(fdTransferStr) : -1;
            m_hasHajrInfo = true;
        }
    }

    if (m_hasHajrInfo) {
        // When Hajr is enabled, identifier.handle IS the eventfd (signal2_fd),
        // NOT a socket. Do NOT wrap it in a GSocket — g_socket_new_from_fd
        // takes ownership and its lifecycle management would close the
        // eventfd, colliding with the ring buffer's signal_fd and causing
        // EBADF in hajr_ring_wait (busy-spin / compositor stall).
        m_socketDescriptor = -1;
    } else {
        m_socketDescriptor = identifier.handle;
#if USE(GLIB)
        m_socket = adoptGRef(g_socket_new_from_fd(m_socketDescriptor, nullptr));
#endif
    }

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
    if (m_hajrSignalSource) {
        g_source_destroy(m_hajrSignalSource);
        g_source_unref(m_hajrSignalSource);
        m_hajrSignalSource = nullptr;
    }
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
        fprintf(stderr, "[ZAWRA] readyReadHandler ENTERED on tid=%d isServer=%d\n", (int)syscall(SYS_gettid), m_isServer);
        // Clear eventfd signal if any
        hajr_ring_wait(m_inboundRing);

        while (true) {
            MessageInfo msgInfo;
            size_t msgInfoBytesRead = 0;
            int32_t res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&msgInfo), sizeof(msgInfo), &msgInfoBytesRead);
            if (res != 1 || msgInfoBytesRead == 0)
                break;

            fprintf(stderr, "[HAJR-CONN] readyReadHandler READ MSG: this=%p inbound=%p inboundSig=%d bodySize=%zu attCount=%zu tid=%d\n",
                (void*)this, (void*)m_inboundRing,
                m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
                msgInfo.bodySize(), msgInfo.attachmentCount(), (int)syscall(SYS_gettid));

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

            // Read handle values from ring to advance read pointer (they're part of the wire format)
            // The actual FDs are received separately via SCM_RIGHTS on the transfer socket.
            Vector<int32_t> handleValues;
            for (uint32_t i = 0; i < attachmentCount; ++i) {
                int32_t handle;
                size_t handleRead = 0;
                res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&handle), sizeof(handle), &handleRead);
                if (res != 1 || handleRead != sizeof(handle)) {
                    fprintf(stderr, "[ZAWRA] readyReadHandler - FAILED TO READ HANDLE %u FROM RING\n", i);
                    attachmentFail = true;
                    break;
                }
                handleValues.append(handle);
            }

            // Now receive the actual FDs via SCM_RIGHTS from the transfer socket
            if (!attachmentFail && attachmentCount > 0 && m_fdTransferFd != -1) {
                struct iovec iov;
                char dummy = 0;
                iov.iov_base = &dummy;
                iov.iov_len = sizeof(dummy);

                size_t cmsgSpace = CMSG_SPACE(sizeof(int) * attachmentCount);
                Vector<uint8_t> cmsgBuf(cmsgSpace);
                memset(cmsgBuf.data(), 0, cmsgSpace);

                struct msghdr msg;
                memset(&msg, 0, sizeof(msg));
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
                msg.msg_control = cmsgBuf.data();
                msg.msg_controllen = cmsgSpace;

                ssize_t recvResult = recvmsg(m_fdTransferFd, &msg, 0);
                fprintf(stderr, "[CRASH-V2] readyReadHandler: SCM_RIGHTS recvmsg result=%zd errno=%d fdCount=%u fdTransferFd=%d\n",
                    recvResult, (recvResult == -1) ? errno : 0, attachmentCount, m_fdTransferFd);

                if (recvResult == -1) {
                    fprintf(stderr, "[ZAWRA] readyReadHandler - SCM_RIGHTS recvmsg FAILED, errno=%d\n", errno);
                    attachmentFail = true;
                } else {
                    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
                    if (!cmsg || cmsg->cmsg_level != SOL_SOCKET || cmsg->cmsg_type != SCM_RIGHTS) {
                        fprintf(stderr, "[ZAWRA] readyReadHandler - SCM_RIGHTS cmsg header invalid\n");
                        attachmentFail = true;
                    } else {
                        int* receivedFds = reinterpret_cast<int*>(CMSG_DATA(cmsg));
                        for (uint32_t i = 0; i < attachmentCount; ++i) {
                            int fd = receivedFds[i];
                            if (fd == -1) {
                                fprintf(stderr, "[ZAWRA] readyReadHandler - SCM_RIGHTS received fd=-1 for index %u\n", i);
                                attachmentFail = true;
                                break;
                            }
                            if (!setCloseOnExec(fd)) {
                                close(fd);
                                attachmentFail = true;
                                break;
                            }
                            fds.append(Attachment(fd, Attachment::Adopt));
                        }
                    }
                }
            } else if (!attachmentFail && attachmentCount > 0) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - attachmentCount=%u but no FD transfer socket\n", attachmentCount);
                attachmentFail = true;
            }

            if (attachmentFail) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT RETRIEVAL FAILED, skipping body+checksum to resync ring\n");
                // Skip remaining body + checksum to resync ring position
                if (msgInfo.bodySize() > 0) {
                    uint8_t* skipBuf = static_cast<uint8_t*>(fastMalloc(msgInfo.bodySize()));
                    size_t skipRead = 0;
                    hajr_ring_read(m_inboundRing, skipBuf, msgInfo.bodySize(), &skipRead);
                    fastFree(skipBuf);
                }
                uint32_t skipChecksum = 0;
                size_t skipChecksumRead = 0;
                hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&skipChecksum), sizeof(skipChecksum), &skipChecksumRead);
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

            if (decoder) {
                static int s_readCount = 0;
                static uint64_t s_prevFirst8 = 0;
                static size_t s_prevBodySize = 0;
                static int s_dupCount = 0;
                s_readCount++;
                if (msgInfo.bodySize() >= 8) {
                    uint64_t first8;
                    memcpy(&first8, payloadBuffer, sizeof(first8));
                    if (first8 == s_prevFirst8 && msgInfo.bodySize() == s_prevBodySize && s_readCount > 1) {
                        s_dupCount++;
                        if (s_dupCount <= 10 || (s_dupCount % 1000) == 0)
                            fprintf(stderr, "[STORM-DUP] readyReadHandler DUPLICATE #%d (dupCount=%d) this=%p inbound=%p inboundSig=%d first8=0x%016lX bodySize=%zu tid=%d\n",
                                s_readCount, s_dupCount, (void*)this, (void*)m_inboundRing,
                                m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
                                first8, msgInfo.bodySize(), (int)syscall(SYS_gettid));
                    } else if (s_dupCount > 0) {
                        fprintf(stderr, "[STORM-DUP] readyReadHandler: dup streak ended after %d duplicates, this=%p inbound=%p inboundSig=%d new msg first8=0x%016lX tid=%d\n",
                            s_dupCount, (void*)this, (void*)m_inboundRing,
                            m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
                            first8, (int)syscall(SYS_gettid));
                        s_dupCount = 0;
                    }
                    s_prevFirst8 = first8;
                    s_prevBodySize = msgInfo.bodySize();
                    if (s_readCount <= 20 || (s_readCount % 10000) == 0)
                        fprintf(stderr, "[STORM-READ] readyReadHandler DISPATCH #%d: this=%p inbound=%p inboundSig=%d bodySize=%zu first8=0x%016lX tid=%d\n",
                            s_readCount, (void*)this, (void*)m_inboundRing,
                            m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
                            msgInfo.bodySize(), first8, (int)syscall(SYS_gettid));
                }
                processIncomingMessage(WTFMove(decoder));
            } else {
                fprintf(stderr, "[ZAWRA] readyReadHandler - Decoder::create FAILED bodySize=%zu tid=%d\n", msgInfo.bodySize(), (int)syscall(SYS_gettid));
                fastFree(payloadBuffer);
            }
        }
        return;
    }

    // Legacy fallback or signals that didn't go through the ring
    while (true) {
        ssize_t bytesRead = readBytesFromSocket(m_socketDescriptor, m_readBuffer, m_fileDescriptors);
        if (bytesRead <= 0) {
            if (bytesRead == 0 || (bytesRead < 0 && errno != EAGAIN && errno != EWOULDBLOCK)) {
                connectionDidClose();
                return;
            }
            break;
        }
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

#if USE(GLIB)
struct HajrSource {
    GSource source;
    GPollFD pollFd;
};

static GSourceFuncs s_hajrSourceFuncs = {
    // prepare
    [](GSource* source, gint* timeout) -> gboolean {
        *timeout = -1;
        return FALSE;
    },
    // check
    [](GSource* source) -> gboolean {
        auto* hajrSource = reinterpret_cast<HajrSource*>(source);
        return (hajrSource->pollFd.revents & (G_IO_IN | G_IO_HUP | G_IO_ERR)) != 0;
    },
    // dispatch
    [](GSource* source, GSourceFunc callback, gpointer user_data) -> gboolean {
        if (!callback)
            return G_SOURCE_REMOVE;
        return callback(user_data);
    },
    // finalize
    nullptr,
    nullptr,
    nullptr
};
#endif

void Connection::platformOpen()
{
    RefPtr<Connection> protectedThis(this);
    m_isConnected = true;

    // Prefer per-connection Hajr info from the Identifier (set by parent).
    // Fall back to env vars for child processes (which inherit env at fork).
    uint64_t ring1 = 0, ring2 = 0;
    int sig1 = -1, sig2 = -1, pidfd = -1;
    bool haveHajrInfo = false;

    if (m_hasHajrInfo) {
        ring1 = m_hajrRing1;
        ring2 = m_hajrRing2;
        sig1 = m_hajrSig1;
        sig2 = m_hajrSig2;
        pidfd = m_hajrPidfd;
        haveHajrInfo = true;
    } else {
        const char* ring1Str = getenv("ZAWRA_HAJR_RING1");
        const char* ring2Str = getenv("ZAWRA_HAJR_RING2");
        const char* sig1Str = getenv("ZAWRA_HAJR_SIGNAL1");
        const char* sig2Str = getenv("ZAWRA_HAJR_SIGNAL2");
        const char* parentPidFDStr = getenv("ZAWRA_HAJR_PARENT_PIDFD");

        if (ring1Str && ring2Str && sig1Str && sig2Str) {
            ring1 = strtoull(ring1Str, nullptr, 10);
            ring2 = strtoull(ring2Str, nullptr, 10);
            sig1 = atoi(sig1Str);
            sig2 = atoi(sig2Str);
            pidfd = parentPidFDStr ? atoi(parentPidFDStr) : -1;
            haveHajrInfo = true;
        }
    }

    if (haveHajrInfo) {
        // When Hajr is enabled, the "socket" descriptor is actually an
        // eventfd used for ring buffer signaling. If platformInitialize()
        // wrapped it in a GSocket (child-side fallback path reading from
        // env vars), release it now to prevent GSocket lifecycle from
        // closing the eventfd that the ring buffer depends on.
#if USE(GLIB)
        if (m_socket && m_socketDescriptor != -1) {
            int sockFd = g_socket_get_fd(m_socket.get());
            if (sockFd == sig1 || sockFd == sig2) {
                int dupFd = dup(sockFd);
                if (sockFd == sig1)
                    sig1 = dupFd;
                if (sockFd == sig2)
                    sig2 = dupFd;
                m_socket = nullptr;
                m_socketDescriptor = -1;
            }
        }
#endif

        if (!m_isServer) {
            int parentPidfd = syscall(434, getppid(), 0);
            if (parentPidfd != -1) {
                pidfd = parentPidfd;
            } else {
                fprintf(stderr, "[ZAWRA-ERROR] Failed to dynamically open parent pidfd: errno=%d\n", errno);
            }
        }
        if (pidfd != -1)
            hajr_ipc_set_other_pidfd(pidfd);

        if (m_isServer) {
            m_inboundRing = static_cast<C_HardenedRingBuffer*>(Z_Hajr_MapBootstrapRingWithSignal(ring2, sig2));
            m_outboundRing = static_cast<C_HardenedRingBuffer*>(Z_Hajr_MapBootstrapRingWithSignal(ring1, sig1));
        } else {
            m_inboundRing = static_cast<C_HardenedRingBuffer*>(Z_Hajr_MapBootstrapRingWithSignal(ring1, sig1));
            m_outboundRing = static_cast<C_HardenedRingBuffer*>(Z_Hajr_MapBootstrapRingWithSignal(ring2, sig2));
        }
        m_isHajrEnabled = (m_inboundRing && m_outboundRing);
        fprintf(stderr, "[HAJR-CONN] platformOpen: this=%p isServer=%d m_isHajrEnabled=%d inbound=%p outbound=%p inboundSig=%d outboundSig=%d ring1=%llu ring2=%llu sig1=%d sig2=%d pidfd=%d\n",
            (void*)this, m_isServer, m_isHajrEnabled,
            (void*)m_inboundRing, (void*)m_outboundRing,
            m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
            m_outboundRing ? hajr_ring_get_signal_fd(m_outboundRing) : -1,
            (unsigned long long)ring1, (unsigned long long)ring2, sig1, sig2, pidfd);
#if USE(GLIB)
        if (m_isHajrEnabled) {
            int hajrFd = hajr_ring_get_signal_fd(m_inboundRing);
            m_hajrSignalSource = g_source_new(&s_hajrSourceFuncs, sizeof(HajrSource));
            auto* hajrSource = reinterpret_cast<HajrSource*>(m_hajrSignalSource);
            hajrSource->pollFd.fd = hajrFd;
            hajrSource->pollFd.events = static_cast<GIOCondition>(G_IO_IN | G_IO_HUP | G_IO_ERR);
            hajrSource->pollFd.revents = 0;
            g_source_add_poll(m_hajrSignalSource, &hajrSource->pollFd);
            this->ref();
            g_source_set_callback(m_hajrSignalSource, [](gpointer data) -> gboolean {
                auto* connection = static_cast<Connection*>(data);
                connection->readyReadHandler();
                return G_SOURCE_CONTINUE;
            }, this, [](gpointer data) {
                static_cast<Connection*>(data)->deref();
            });
#if USE(GLIB_EVENT_LOOP)
            g_source_attach(m_hajrSignalSource, m_connectionQueue->runLoop().mainContext());
#else
            g_source_attach(m_hajrSignalSource, nullptr);
#endif
            fprintf(stderr, "[CRASH-V2] platformOpen: AFTER g_source_attach, returning\n");
        }
#endif
    }

#if USE(GLIB)
    GSocket* monitorSocket = m_isHajrEnabled ? nullptr : m_socket.get();
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

    // When Hajr is enabled, the HajrSource GSource (attached above) handles
    // inbound data via poll on the signal fd. Dispatching readyReadHandler()
    // directly would BLOCK the queue thread inside hajr_ring_wait() because
    // no data is available yet, permanently stalling all subsequent dispatches
    // (including sendOutgoingMessages).
    if (!m_isHajrEnabled) {
        m_connectionQueue->dispatch([protectedThis] {
            protectedThis->readyReadHandler();
        });
    }

    fprintf(stderr, "[CRASH-V2] platformOpen: DONE, m_isHajrEnabled=%d\n", m_isHajrEnabled);
}

bool Connection::sendOutputMessage(UnixMessage& outputMessage)
{
    fprintf(stderr, "[CRASH-V2] sendOutputMessage: called, m_isHajrEnabled=%d\n", m_isHajrEnabled);
    if (m_isHajrEnabled && m_outboundRing) {
        fprintf(stderr, "[CRASH-V2] sendOutputMessage: entering hajr block\n");
        auto& messageInfo = outputMessage.messageInfo();
        auto& attachments = outputMessage.attachments();
        uint32_t attachmentCount = attachments.size();
        
        fprintf(stderr, "[CRASH-V2] sendOutputMessage: size calculated\n");
        size_t total_size = sizeof(messageInfo) + sizeof(attachmentCount) + (attachmentCount * sizeof(int32_t)) + outputMessage.bodySize() + sizeof(uint32_t);
        Vector<uint8_t> payload(total_size);
        uint8_t* ptr = payload.data();

        memcpy(ptr, &messageInfo, sizeof(messageInfo));
        ptr += sizeof(messageInfo);

        memcpy(ptr, &attachmentCount, sizeof(attachmentCount));
        ptr += sizeof(attachmentCount);

        fprintf(stderr, "[CRASH-V2] sendOutputMessage: copying %u attachments\n", attachmentCount);
        for (auto& attachment : attachments) {
            int32_t handle = hajr_ipc_send_fd(m_outboundRing, attachment.value());
            memcpy(ptr, &handle, sizeof(handle));
            ptr += sizeof(handle);
        }

        fprintf(stderr, "[CRASH-V2] sendOutputMessage: copying body (size=%zu)\n", outputMessage.bodySize());
        memcpy(ptr, outputMessage.body(), outputMessage.bodySize());

        fprintf(stderr, "[CRASH-V2] sendOutputMessage: calculating checksum\n");
        // Calculate checksum over msgInfo + body (core message integrity)
        uint32_t checksum = hajr_ipc_message_checksum(
            reinterpret_cast<const uint8_t*>(&messageInfo),
            sizeof(messageInfo),
            outputMessage.body(),
            outputMessage.bodySize()
        );
        memcpy(ptr + outputMessage.bodySize(), &checksum, sizeof(checksum));

        fprintf(stderr, "[HAJR-CONN] sendOutputMessage: this=%p outbound=%p outboundSig=%d bodySize=%zu attachments=%u tid=%d\n",
            (void*)this, (void*)m_outboundRing,
            m_outboundRing ? hajr_ring_get_signal_fd(m_outboundRing) : -1,
            outputMessage.bodySize(), attachmentCount, (int)syscall(SYS_gettid));
        fprintf(stderr, "[CRASH-V2] sendOutputMessage: writing to ring\n");
        if (hajr_ring_write(m_outboundRing, payload.data(), payload.size()) == 1) {
            // If we have attachments, send FDs via SCM_RIGHTS on the transfer socket.
            // pidfd_getfd requires CAP_SYS_PTRACE which sandboxed children lack.
            if (attachmentCount > 0 && m_fdTransferFd != -1) {
                // Build iovec + cmsg for sendmsg with SCM_RIGHTS
                // We send a tiny 1-byte payload alongside the FDs to maintain message boundaries
                struct iovec iov;
                char dummy = 0;
                iov.iov_base = &dummy;
                iov.iov_len = sizeof(dummy);

                // Calculate cmsg buffer size for up to 254 FDs
                size_t cmsgSpace = CMSG_SPACE(sizeof(int) * attachmentCount);
                Vector<uint8_t> cmsgBuf(cmsgSpace);
                memset(cmsgBuf.data(), 0, cmsgSpace);

                struct msghdr msg;
                memset(&msg, 0, sizeof(msg));
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
                msg.msg_control = cmsgBuf.data();
                msg.msg_controllen = cmsgSpace;

                struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
                cmsg->cmsg_level = SOL_SOCKET;
                cmsg->cmsg_type = SCM_RIGHTS;
                cmsg->cmsg_len = CMSG_LEN(sizeof(int) * attachmentCount);

                int* fds = reinterpret_cast<int*>(CMSG_DATA(cmsg));
                int fdIndex = 0;
                for (auto& attachment : attachments) {
                    fds[fdIndex++] = attachment.value();
                }

                ssize_t sendResult = sendmsg(m_fdTransferFd, &msg, MSG_NOSIGNAL);
                fprintf(stderr, "[CRASH-V2] sendOutputMessage: SCM_RIGHTS sendmsg result=%zd errno=%d fdCount=%u fdTransferFd=%d\n",
                    sendResult, (sendResult == -1) ? errno : 0, attachmentCount, m_fdTransferFd);
                if (sendResult == -1) {
                    fprintf(stderr, "[CRASH-V2] sendOutputMessage: SCM_RIGHTS FAILED\n");
                }
            }
        fprintf(stderr, "[CRASH-V2] sendOutputMessage: signaling ring\n");
        hajr_ring_signal(m_outboundRing);
        fprintf(stderr, "[CRASH-V2] sendOutputMessage: returning true\n");
        return true;
    }
    }

    if (m_socketDescriptor != -1) {
        auto& messageInfo = outputMessage.messageInfo();
        auto& attachments = outputMessage.attachments();
        uint32_t attachmentCount = attachments.size();

        size_t totalSize = sizeof(messageInfo)
            + sizeof(attachmentCount)
            + (attachmentCount * sizeof(AttachmentInfo))
            + outputMessage.bodySize()
            + sizeof(uint32_t);
        Vector<uint8_t> payload(totalSize);
        uint8_t* ptr = payload.data();

        memcpy(ptr, &messageInfo, sizeof(messageInfo));
        ptr += sizeof(messageInfo);

        memcpy(ptr, &attachmentCount, sizeof(attachmentCount));
        ptr += sizeof(attachmentCount);

        for (uint32_t i = 0; i < attachmentCount; ++i) {
            AttachmentInfo info;
            memcpy(ptr, &info, sizeof(info));
            ptr += sizeof(info);
        }

        memcpy(ptr, outputMessage.body(), outputMessage.bodySize());
        ptr += outputMessage.bodySize();

        uint32_t checksum = hajr_ipc_message_checksum(
            reinterpret_cast<const uint8_t*>(&messageInfo),
            sizeof(messageInfo),
            outputMessage.body(),
            outputMessage.bodySize());
        memcpy(ptr, &checksum, sizeof(checksum));

        struct iovec iov;
        iov.iov_base = payload.data();
        iov.iov_len = payload.size();

        struct msghdr msg;
        memset(&msg, 0, sizeof(msg));
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        Vector<uint8_t> cmsgBuffer;
        if (attachmentCount > 0) {
            cmsgBuffer.resize(CMSG_SPACE(sizeof(int) * attachmentCount));
            msg.msg_control = cmsgBuffer.data();
            msg.msg_controllen = CMSG_SPACE(sizeof(int) * attachmentCount);

            cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
            cmsg->cmsg_level = SOL_SOCKET;
            cmsg->cmsg_type = SCM_RIGHTS;
            cmsg->cmsg_len = CMSG_LEN(sizeof(int) * attachmentCount);

            int* fds = reinterpret_cast<int*>(CMSG_DATA(cmsg));
            for (uint32_t i = 0; i < attachmentCount; ++i)
                fds[i] = attachments[i].value();
        }

        ssize_t sendResult = sendmsg(m_socketDescriptor, &msg, MSG_NOSIGNAL);
        fprintf(stderr, "[SOCK-SEND] sendmsg result=%zd errno=%d fdCount=%u fd=%d bodySize=%zu\n",
            sendResult == -1 ? -1 : static_cast<long>(sendResult),
            sendResult == -1 ? errno : 0, attachmentCount, m_socketDescriptor, outputMessage.bodySize());
        if (sendResult == -1)
            return false;

        return static_cast<size_t>(sendResult) == payload.size();
    }

    fprintf(stderr, "[CRASH-V2] sendOutputMessage: returning false\n");
    return false; 
}

bool Connection::platformCanSendOutgoingMessages() const { return !m_pendingOutputMessage; }

bool Connection::sendOutgoingMessage(UniqueRef<Encoder>&& encoder)
{
    static int s_sendCount = 0;
    s_sendCount++;
    if (s_sendCount <= 20 || (s_sendCount % 10000) == 0) {
        fprintf(stderr, "[STORM-SEND] sendOutgoingMessage #%d: msgName=%d receiver=%d destID=0x%016lX bodySize=%zu tid=%d\n",
            s_sendCount, (int)encoder->messageName(), (int)encoder->messageReceiverName(),
            (unsigned long)encoder->destinationID(), encoder->bufferSize(), (int)syscall(SYS_gettid));
    }
    UnixMessage outputMessage(encoder.get());
    if (outputMessage.attachments().size() > (attachmentMaxAmount - 1)) {
        ASSERT_NOT_REACHED();
        return false;
    }

    fprintf(stderr, "[CRASH-V2] sendOutgoingMessage: checking size inline\n");
    size_t messageSizeWithBodyInline = sizeof(MessageInfo) + (outputMessage.attachments().size() * sizeof(AttachmentInfo)) + outputMessage.bodySize();
    if (messageSizeWithBodyInline > messageMaxSize && outputMessage.bodySize()) {
        fprintf(stderr, "[CRASH-V2] sendOutgoingMessage: handling large message (size=%zu, max=%zu)\n", messageSizeWithBodyInline, static_cast<size_t>(messageMaxSize));
        RefPtr<WebKit::SharedMemory> oolMessageBody = WebKit::SharedMemory::allocate(outputMessage.bodySize());
        if (!oolMessageBody)
            return false;

        auto handle = oolMessageBody->createHandle(WebKit::SharedMemory::Protection::ReadOnly);
        if (!handle)
            return false;

        outputMessage.messageInfo().setBodyOutOfLine();

        memcpy(oolMessageBody->data(), outputMessage.body(), outputMessage.bodySize());

        outputMessage.appendAttachment(handle->releaseHandle());
    }

    fprintf(stderr, "[CRASH-V2] sendOutgoingMessage: calling sendOutputMessage\n");
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
