#include "config.h"
#include "Connection.h"

#include "Decoder.h"
#include "Encoder.h"
#include "IPCUtilities.h"
#include "UnixMessage.h"
#include <errno.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <wtf/Assertions.h>
#include <wtf/FastMalloc.h>
#include <wtf/SafeStrerror.h>

#if USE(GLIB)
#include <glib.h>
#endif

// Hajr FFI Declarations
extern "C" {
    typedef struct C_HardenedRingBuffer C_HardenedRingBuffer;
    void* Zawra_Hajr_MapBootstrapRingWithSignal(uint64_t id, int signal_fd);
    void hajr_ring_free(C_HardenedRingBuffer*);
    int32_t hajr_ring_write(C_HardenedRingBuffer*, const uint8_t* data, size_t length);
    int32_t hajr_ring_read(C_HardenedRingBuffer*, uint8_t* buf, size_t length, size_t* bytes_read);
    int32_t hajr_ring_signal(C_HardenedRingBuffer*);
    int32_t hajr_ring_wait(C_HardenedRingBuffer*);
    int32_t hajr_ipc_send_fd(C_HardenedRingBuffer*, int fd);
    int32_t hajr_ipc_recv_fd(C_HardenedRingBuffer*, int handle);
    void hajr_ipc_set_other_pidfd(int pidfd);
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

void Connection::platformInvalidate()
{
    if (m_inboundRing) {
        hajr_ring_free(m_inboundRing);
        m_inboundRing = nullptr;
    }
    if (m_outboundRing) {
        if (m_pendingRingMessages > 0) {
            hajr_ring_signal(m_outboundRing);
            m_pendingRingMessages = 0;
        }
        hajr_ring_free(m_outboundRing);
        m_outboundRing = nullptr;
    }

    if (!m_isConnected)
        return;

    m_readSocketMonitor.stop();
    m_writeSocketMonitor.stop();

    m_socketDescriptor = -1;
    m_isConnected = false;
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
    }

#if USE(GLIB)
    m_readSocketMonitor.start(m_socket.get(), static_cast<GIOCondition>(G_IO_IN | G_IO_HUP | G_IO_ERR), m_connectionQueue->runLoop(), [protectedThis](GIOCondition condition) -> gboolean {
        if (condition & (G_IO_HUP | G_IO_ERR)) {
            protectedThis->connectionDidClose();
            return G_SOURCE_REMOVE;
        }
        protectedThis->readyReadHandler();
        return G_SOURCE_CONTINUE;
    });
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
        
        size_t total_size = sizeof(messageInfo) + sizeof(attachmentCount) + (attachmentCount * sizeof(int32_t)) + outputMessage.bodySize();
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

        if (hajr_ring_write(m_outboundRing, payload.data(), payload.size()) == 1) {
            m_pendingRingMessages++;
            if (m_pendingRingMessages >= m_ringBatchSize) {
                hajr_ring_signal(m_outboundRing);
                m_pendingRingMessages = 0;
            }
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

// Stubs for missing pieces
void Connection::willSendSyncMessage(OptionSet<SendSyncOption>) { }
void Connection::didReceiveSyncReply(OptionSet<SendSyncOption>) { }
std::optional<Connection::ConnectionIdentifierPair> Connection::createConnectionIdentifierPair() { return std::nullopt; }

} // namespace IPC
