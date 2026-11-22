/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2011 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "Connection.h"

#include "Decoder.h"
#include "Encoder.h"
#include "IPCUtilities.h"
#include "Logging.h"
#include "UnixMessage.h"
#include <WebCore/SharedMemory.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <wtf/Assertions.h>
#include <wtf/Borrow.h>
#include <wtf/MallocSpan.h>
#include <wtf/SafeStrerror.h>
#include <wtf/StdLibExtras.h>
#include <wtf/TZoneMallocInlines.h>
#include <wtf/Threading.h>
#include <wtf/UniStdExtras.h>

#if USE(GLIB)
#include <gio/gio.h>
#include <glib.h>
#endif

#if OS(DARWIN)
#define MSG_NOSIGNAL 0
#endif

// Although it's available on Darwin, SOCK_SEQPACKET seems to work differently
// than in traditional Unix so fallback to DGRAM on that platform.
#if defined(SOCK_SEQPACKET) && !OS(DARWIN)
#define SOCKET_TYPE SOCK_SEQPACKET
#else
#define SOCKET_TYPE SOCK_DGRAM
#endif

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

WTF_ALLOW_UNSAFE_BUFFER_USAGE_BEGIN // Unix port

namespace IPC {

#if USE(GLIB)
struct HajrSource {
    GSource source;
    GPollFD pollFd;
};

static gboolean hajrSourcePrepare(GSource*, gint* timeout)
{
    *timeout = -1;
    return FALSE;
}

static gboolean hajrSourceCheck(GSource* source)
{
    auto* hajrSource = reinterpret_cast<HajrSource*>(source);
    return hajrSource->pollFd.revents != 0;
}

static gboolean hajrSourceDispatch(GSource* source, GSourceFunc callback, gpointer userData)
{
    auto* hajrSource = reinterpret_cast<HajrSource*>(source);
    GIOCondition revents = static_cast<GIOCondition>(hajrSource->pollFd.revents);
    hajrSource->pollFd.revents = 0;
    uint64_t val = 0;
    ssize_t rc = read(hajrSource->pollFd.fd, &val, sizeof(val));
    (void)rc;
    if (callback)
        callback(userData);
    if (revents & (G_IO_HUP | G_IO_ERR))
        return G_SOURCE_REMOVE;
    return G_SOURCE_CONTINUE;
}

static GSourceFuncs s_hajrSourceFuncs = {
    hajrSourcePrepare,
    hajrSourceCheck,
    hajrSourceDispatch,
    nullptr, nullptr, nullptr
};
#endif

static const size_t messageMaxSize = 4096;
static const size_t attachmentMaxAmount = 254;

class AttachmentInfo {
    WTF_MAKE_TZONE_ALLOCATED_INLINE(AttachmentInfo);
public:
    AttachmentInfo()
    {
        // The entire AttachmentInfo is passed to write(), so we have to zero our
        // padding bytes to avoid writing uninitialized memory.
        zeroBytes(*this);
    }

    AttachmentInfo(const AttachmentInfo& info)
        : AttachmentInfo()
    {
        *this = info;
    }

    AttachmentInfo& operator=(const AttachmentInfo&) = default;

    // The attachment is not null unless explicitly set.
    void setNull() { m_isNull = true; }
    bool isNull() const { return m_isNull; }

private:
    // The AttachmentInfo will be copied using memcpy, so all members must be trivially copyable.
    bool m_isNull;
};

static_assert(sizeof(MessageInfo) + sizeof(AttachmentInfo) * attachmentMaxAmount <= messageMaxSize, "messageMaxSize is too small.");

int Connection::socketDescriptor() const
{
    return m_socketDescriptor.value();
}

static void unsetHajrEnvironmentVariables()
{
    unsetenv("ZAWRA_HAJR_RING1");
    unsetenv("ZAWRA_HAJR_RING2");
    unsetenv("ZAWRA_HAJR_SIGNAL1");
    unsetenv("ZAWRA_HAJR_SIGNAL2");
    unsetenv("ZAWRA_HAJR_PARENT_PIDFD");
    unsetenv("ZAWRA_HAJR_FDTRANSFER");
    unsetenv("ZAWRA_HAJR_INBOUND");
    unsetenv("ZAWRA_HAJR_OUTBOUND");
    unsetenv("ZAWRA_HAJR_INBOUND_SIGNAL");
    unsetenv("ZAWRA_HAJR_OUTBOUND_SIGNAL");
    unsetenv("ZAWRA_HAJR_FD_TRANSFER");
    unsetenv("ZAWRA_HAJR_PIDFD");
}

void Connection::platformInitialize(Identifier&& identifier)
{
    m_hasHajrInfo = identifier.hasHajrInfo;
    m_hajrRing1 = identifier.hajrRing1;
    m_hajrRing2 = identifier.hajrRing2;
    m_hajrSig1 = identifier.hajrSig1;
    m_hajrSig2 = identifier.hajrSig2;
    m_hajrPidfd = identifier.hajrPidfd;
    m_fdTransferFd = identifier.hajrFdTransferFd;

    const char* ring1Str = getenv("ZAWRA_HAJR_RING1");
    if (!ring1Str)
        ring1Str = getenv("ZAWRA_HAJR_INBOUND");
    if (!m_hasHajrInfo && ring1Str) {
        const char* ring2Str = getenv("ZAWRA_HAJR_RING2");
        if (!ring2Str)
            ring2Str = getenv("ZAWRA_HAJR_OUTBOUND");
        const char* sig1Str = getenv("ZAWRA_HAJR_SIGNAL1");
        if (!sig1Str)
            sig1Str = getenv("ZAWRA_HAJR_INBOUND_SIGNAL");
        const char* sig2Str = getenv("ZAWRA_HAJR_SIGNAL2");
        if (!sig2Str)
            sig2Str = getenv("ZAWRA_HAJR_OUTBOUND_SIGNAL");
        if (ring2Str && sig1Str && sig2Str) {
            m_hajrRing1 = strtoull(ring1Str, nullptr, 10);
            m_hajrRing2 = strtoull(ring2Str, nullptr, 10);
            m_hajrSig1 = atoi(sig1Str);
            m_hajrSig2 = atoi(sig2Str);
            const char* parentPidFDStr = getenv("ZAWRA_HAJR_PARENT_PIDFD");
            if (!parentPidFDStr)
                parentPidFDStr = getenv("ZAWRA_HAJR_PIDFD");
            m_hajrPidfd = parentPidFDStr ? atoi(parentPidFDStr) : -1;
            const char* fdTransferStr = getenv("ZAWRA_HAJR_FDTRANSFER");
            if (!fdTransferStr)
                fdTransferStr = getenv("ZAWRA_HAJR_FD_TRANSFER");
            m_fdTransferFd = fdTransferStr ? atoi(fdTransferStr) : -1;
            m_hasHajrInfo = true;
            unsetHajrEnvironmentVariables();
        }
    }

    if (m_hasHajrInfo) {
        // When Hajr is enabled, identifier.handle is an eventfd (signal2_fd), not a socket.
        // Explicitly release so its destructor does not close the eventfd.
        identifier.handle.release();
    } else if (identifier.handle) {
        m_socketDescriptor = WTF::move(identifier.handle);
#if USE(GLIB)
        if (m_socketDescriptor.value() != -1)
            m_socket = adoptGRef(g_socket_new_from_fd(m_socketDescriptor.value(), nullptr));
#endif
    }

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
        hajr_ring_free(m_outboundRing);
        m_outboundRing = nullptr;
    }

    if (m_socketDescriptor.value() != -1)
        closeWithRetry(m_socketDescriptor.release());

    if (!m_isConnected)
        return;

#if USE(GLIB)
    if (m_hajrSignalSource) {
        g_source_destroy(m_hajrSignalSource);
        g_source_unref(m_hajrSignalSource);
        m_hajrSignalSource = nullptr;
    }
    m_readSocketMonitor.stop();
    m_writeSocketMonitor.stop();
    m_socket = nullptr;
#endif

    m_isConnected = false;
}

bool Connection::processMessage()
{
    if (m_readBuffer.size() < sizeof(MessageInfo))
        return false;

    Borrow readBuffer = m_readBuffer;
    auto messageData = readBuffer->mutableSpan();
    MessageInfo messageInfo;
    memcpySpan(asMutableByteSpan(messageInfo), consumeSpan(messageData, sizeof(messageInfo)));

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
        memcpySpan(asMutableByteSpan(attachmentInfo.mutableSpan()), consumeSpan(messageData, sizeof(AttachmentInfo) * attachmentCount));
        for (size_t i = 0; i < attachmentCount; ++i) {
            if (!attachmentInfo[i].isNull())
                attachmentFileDescriptorCount++;
        }

        if (messageInfo.isBodyOutOfLine())
            attachmentCount--;
    }

    Vector<Attachment> attachments(attachmentCount);
    RefPtr<WebCore::SharedMemory> oolMessageBody;

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

        auto fd = UnixFileDescriptor { m_fileDescriptors[attachmentFileDescriptorCount - 1], UnixFileDescriptor::Adopt };
        if (!fd) {
            ASSERT_NOT_REACHED();
            return false;
        }

        auto handle = WebCore::SharedMemory::Handle { WTF::move(fd), messageInfo.bodySize() };
        oolMessageBody = WebCore::SharedMemory::map(WTF::move(handle), WebCore::SharedMemory::Protection::ReadOnly);
        if (!oolMessageBody) {
            ASSERT_NOT_REACHED();
            return false;
        }
    }

    ASSERT(attachments.size() == (messageInfo.isBodyOutOfLine() ? messageInfo.attachmentCount() - 1 : messageInfo.attachmentCount()));

    auto messageBody = messageData;
    if (messageInfo.isBodyOutOfLine())
        messageBody = oolMessageBody->mutableSpan();

    auto decoder = Decoder::create(messageBody.first(messageInfo.bodySize()), WTF::move(attachments));
    ASSERT(decoder);
    if (!decoder)
        return false;

    processIncomingMessage(makeUniqueRefFromNonNullUniquePtr(WTF::move(decoder)));

    if (m_readBuffer.size() > messageLength) {
        memmoveSpan(m_readBuffer.mutableSpan(), m_readBuffer.subspan(messageLength));
        m_readBuffer.shrink(m_readBuffer.size() - messageLength);
    } else
        m_readBuffer.shrink(0);

    if (attachmentFileDescriptorCount) {
        if (m_fileDescriptors.size() > attachmentFileDescriptorCount) {
            memmoveSpan(m_fileDescriptors.mutableSpan(), m_fileDescriptors.subspan(attachmentFileDescriptorCount));
            m_fileDescriptors.shrink(m_fileDescriptors.size() - attachmentFileDescriptorCount);
        } else
            m_fileDescriptors.shrink(0);
    }

    return true;
}

static ssize_t readBytesFromSocket(int socketDescriptor, Vector<uint8_t>& buffer, Vector<int>& fileDescriptors)
{
    struct msghdr message;
    memset(&message, 0, sizeof(message));

    struct iovec iov[1];
    memset(&iov, 0, sizeof(iov));

    auto attachmentDescriptorBuffer = MallocSpan<char>::zeroedMalloc(CMSG_SPACE(sizeof(int) * attachmentMaxAmount));
    auto attachmentDescriptorSpan = attachmentDescriptorBuffer.mutableSpan();
    message.msg_control = attachmentDescriptorSpan.data();
    message.msg_controllen = attachmentDescriptorSpan.size();

    size_t previousBufferSize = buffer.size();
    buffer.grow(buffer.capacity());
    iov[0].iov_base = buffer.mutableSpan().data() + previousBufferSize;
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
                memcpy(fileDescriptors.mutableSpan().subspan(previousFileDescriptorsSize).data(), CMSG_DATA(controlMessage), sizeof(int) * fileDescriptorsCount);

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
        while (true) {
            MessageInfo msgInfo;
            size_t bytesRead = 0;
            int32_t res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&msgInfo), sizeof(msgInfo), &bytesRead);
            if (res != 1 || bytesRead == 0)
                break;

            if (bytesRead != sizeof(msgInfo)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - PARTIAL MESSAGE INFO READ: got %zu, expected %zu\n", bytesRead, sizeof(msgInfo));
                break;
            }

            uint32_t attachmentCount = 0;
            size_t countBytesRead = 0;
            res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&attachmentCount), sizeof(attachmentCount), &countBytesRead);
            if (res != 1 || countBytesRead != sizeof(attachmentCount)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT COUNT READ FAILED\n");
                break;
            }

            Vector<int32_t> handles(attachmentCount);
            size_t validFdCount = 0;
            bool attachmentFail = false;
            for (uint32_t i = 0; i < attachmentCount; ++i) {
                int32_t handle = -1;
                size_t handleBytesRead = 0;
                res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&handle), sizeof(handle), &handleBytesRead);
                if (res != 1 || handleBytesRead != sizeof(handle)) {
                    fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT HANDLE READ FAILED at index %u\n", i);
                    attachmentFail = true;
                    break;
                }
                handles[i] = handle;
                if (handle >= 0)
                    validFdCount++;
            }

            Vector<int> receivedFds;
            if (!attachmentFail && validFdCount > 0 && m_fdTransferFd != -1) {
                char dummy = 0;
                struct iovec iov;
                iov.iov_base = &dummy;
                iov.iov_len = 1;

                std::vector<char> cmsgBuf(CMSG_SPACE(sizeof(int) * validFdCount));
                struct msghdr msg;
                memset(&msg, 0, sizeof(msg));
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
                msg.msg_control = cmsgBuf.data();
                msg.msg_controllen = cmsgBuf.size();

                ssize_t recvResult = recvmsg(m_fdTransferFd, &msg, MSG_NOSIGNAL);
                if (recvResult <= 0) {
                    fprintf(stderr, "[ZAWRA] readyReadHandler - SCM_RIGHTS recvmsg failed: res=%zd errno=%d\n", recvResult, errno);
                    attachmentFail = true;
                } else {
                    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
                    if (!cmsg || cmsg->cmsg_level != SOL_SOCKET || cmsg->cmsg_type != SCM_RIGHTS) {
                        fprintf(stderr, "[ZAWRA] readyReadHandler - SCM_RIGHTS cmsg missing or wrong type\n");
                        attachmentFail = true;
                    } else {
                        size_t numFds = (cmsg->cmsg_len - CMSG_LEN(0)) / sizeof(int);
                        int* rawFds = reinterpret_cast<int*>(CMSG_DATA(cmsg));
                        for (size_t f = 0; f < numFds; ++f) {
                            int fd = rawFds[f];
                            if (!setCloseOnExec(fd)) {
                                close(fd);
                                attachmentFail = true;
                                break;
                            }
                            receivedFds.append(fd);
                        }
                        if (receivedFds.size() != validFdCount) {
                            fprintf(stderr, "[ZAWRA] readyReadHandler - FD count mismatch: expected %zu, got %zu\n", validFdCount, receivedFds.size());
                            attachmentFail = true;
                        }
                    }
                }
            } else if (!attachmentFail && validFdCount > 0) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - validFdCount=%zu but no FD transfer socket\n", validFdCount);
                attachmentFail = true;
            }

            if (attachmentFail) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - ATTACHMENT RETRIEVAL FAILED, skipping body+checksum\n");
                for (int fd : receivedFds)
                    close(fd);
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

            uint32_t effectiveAttachmentCount = attachmentCount;
            if (msgInfo.isBodyOutOfLine() && effectiveAttachmentCount > 0)
                effectiveAttachmentCount--;

            Vector<Attachment> fds(effectiveAttachmentCount);
            size_t fdIdx = 0;
            for (size_t i = 0; i < effectiveAttachmentCount; ++i) {
                int fd = (handles[i] >= 0 && fdIdx < receivedFds.size()) ? receivedFds[fdIdx++] : -1;
                fds[effectiveAttachmentCount - i - 1] = UnixFileDescriptor { fd, UnixFileDescriptor::Adopt };
            }

            if (msgInfo.isBodyOutOfLine()) {
                int oolFd = (handles[attachmentCount - 1] >= 0 && fdIdx < receivedFds.size()) ? receivedFds[fdIdx++] : -1;
                if (oolFd != -1)
                    close(oolFd);
            }

            uint8_t* payloadBuffer = static_cast<uint8_t*>(fastMalloc(msgInfo.bodySize()));
            size_t bodyBytesRead = 0;
            res = hajr_ring_read(m_inboundRing, payloadBuffer, msgInfo.bodySize(), &bodyBytesRead);
            if (res != 1 || bodyBytesRead != msgInfo.bodySize()) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - BODY READ FAILED\n");
                fastFree(payloadBuffer);
                break;
            }

            uint32_t receivedChecksum = 0;
            size_t checksumRead = 0;
            res = hajr_ring_read(m_inboundRing, reinterpret_cast<uint8_t*>(&receivedChecksum), sizeof(receivedChecksum), &checksumRead);
            if (res != 1 || checksumRead != sizeof(receivedChecksum)) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - CHECKSUM READ FAILED\n");
                fastFree(payloadBuffer);
                break;
            }

            uint32_t computedChecksum = hajr_ipc_message_checksum(
                reinterpret_cast<const uint8_t*>(&msgInfo),
                sizeof(msgInfo),
                payloadBuffer,
                msgInfo.bodySize()
            );

            if (computedChecksum != receivedChecksum) {
                fprintf(stderr, "[ZAWRA] readyReadHandler - CHECKSUM MISMATCH: expected 0x%08X, got 0x%08X\n", receivedChecksum, computedChecksum);
                fastFree(payloadBuffer);
                break;
            }

            auto decoder = Decoder::create(
                std::span { payloadBuffer, msgInfo.bodySize() },
                [](std::span<const uint8_t> span) { fastFree(const_cast<uint8_t*>(span.data())); },
                WTF::move(fds)
            );

            if (decoder) {
                processIncomingMessage(makeUniqueRefFromNonNullUniquePtr(WTF::move(decoder)));
            } else {
                fprintf(stderr, "[ZAWRA] readyReadHandler - Decoder::create FAILED bodySize=%zu\n", msgInfo.bodySize());
                fastFree(payloadBuffer);
            }
        }
        return;
    }

    // Socket fallback
    while (true) {
        ssize_t bytesRead = readBytesFromSocket(socketDescriptor(), m_readBuffer, m_fileDescriptors);

        if (bytesRead < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;

            if (errno == ECONNRESET) {
                connectionDidClose();
                return;
            }

            if (m_isConnected) {
                WTFLogAlways("Error receiving IPC message on socket %d in process %d: %s", socketDescriptor(), getpid(), safeStrerror(errno).data());
                connectionDidClose();
            }
            return;
        }

        if (!bytesRead) {
            connectionDidClose();
            return;
        }

        while (true) {
            if (!processMessage())
                break;
        }
    }
}

bool Connection::platformPrepareForOpen()
{
    if (m_hasHajrInfo)
        return true;
    if (setNonBlock(socketDescriptor()))
        return true;
    ASSERT_NOT_REACHED();
    return false;
}

void Connection::platformOpen()
{
    RefPtr<Connection> protectedThis(this);
    m_isConnected = true;

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
        unsetHajrEnvironmentVariables();
    } else {
        const char* ring1Str = getenv("ZAWRA_HAJR_RING1");
        if (!ring1Str)
            ring1Str = getenv("ZAWRA_HAJR_INBOUND");
        const char* ring2Str = getenv("ZAWRA_HAJR_RING2");
        if (!ring2Str)
            ring2Str = getenv("ZAWRA_HAJR_OUTBOUND");
        const char* sig1Str = getenv("ZAWRA_HAJR_SIGNAL1");
        if (!sig1Str)
            sig1Str = getenv("ZAWRA_HAJR_INBOUND_SIGNAL");
        const char* sig2Str = getenv("ZAWRA_HAJR_SIGNAL2");
        if (!sig2Str)
            sig2Str = getenv("ZAWRA_HAJR_OUTBOUND_SIGNAL");
        const char* parentPidFDStr = getenv("ZAWRA_HAJR_PARENT_PIDFD");
        if (!parentPidFDStr)
            parentPidFDStr = getenv("ZAWRA_HAJR_PIDFD");

        if (ring1Str && ring2Str && sig1Str && sig2Str) {
            ring1 = strtoull(ring1Str, nullptr, 10);
            ring2 = strtoull(ring2Str, nullptr, 10);
            sig1 = atoi(sig1Str);
            sig2 = atoi(sig2Str);
            pidfd = parentPidFDStr ? atoi(parentPidFDStr) : -1;
            const char* fdTransferStr = getenv("ZAWRA_HAJR_FDTRANSFER");
            if (!fdTransferStr)
                fdTransferStr = getenv("ZAWRA_HAJR_FD_TRANSFER");
            if (fdTransferStr && m_fdTransferFd == -1)
                m_fdTransferFd = atoi(fdTransferStr);
            haveHajrInfo = true;
            unsetHajrEnvironmentVariables();
        }
    }

    if (haveHajrInfo) {
#if USE(GLIB)
        if (m_socket && m_socketDescriptor.value() != -1) {
            int sockFd = g_socket_get_fd(m_socket.get());
            if (sockFd == sig1 || sockFd == sig2) {
                int dupFd = dup(sockFd);
                if (sockFd == sig1)
                    sig1 = dupFd;
                if (sockFd == sig2)
                    sig2 = dupFd;
                m_socket = nullptr;
                m_socketDescriptor = { };
            }
        }
#endif

        if (!m_isServer && pidfd == -1) {
            int parentPidfd = syscall(__NR_pidfd_open, getppid(), 0);
            if (parentPidfd != -1)
                pidfd = parentPidfd;
            else
                fprintf(stderr, "[ZAWRA-ERROR] Failed to dynamically open parent pidfd: errno=%d\n", errno);
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
        LOG(IPC, "[HAJR-CONN] platformOpen: this=%p isServer=%d m_isHajrEnabled=%d inbound=%p outbound=%p inboundSig=%d outboundSig=%d ring1=%llu ring2=%llu sig1=%d sig2=%d pidfd=%d",
            (void*)this, m_isServer, m_isHajrEnabled,
            (void*)m_inboundRing, (void*)m_outboundRing,
            m_inboundRing ? hajr_ring_get_signal_fd(m_inboundRing) : -1,
            m_outboundRing ? hajr_ring_get_signal_fd(m_outboundRing) : -1,
            (unsigned long long)ring1, (unsigned long long)ring2, sig1, sig2, pidfd);

#if USE(GLIB)
        if (m_isHajrEnabled) {
            int hajrFd = hajr_ring_get_signal_fd(m_inboundRing);
            if (hajrFd != -1) {
                int flags = fcntl(hajrFd, F_GETFL, 0);
                if (flags >= 0)
                    fcntl(hajrFd, F_SETFL, flags | O_NONBLOCK);
            }
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
        }
#endif
    }

#if USE(GLIB)
    GSocket* monitorSocket = m_isHajrEnabled ? nullptr : m_socket.get();
    if (monitorSocket) {
        m_readSocketMonitor.start(monitorSocket, static_cast<GIOCondition>(G_IO_IN | G_IO_HUP | G_IO_ERR), m_connectionQueue->runLoop(), nullptr, [protectedThis](GIOCondition condition) -> gboolean {
            if (condition & (G_IO_HUP | G_IO_ERR)) {
                protectedThis->connectionDidClose();
                return G_SOURCE_REMOVE;
            }

            if (condition & G_IO_IN)
                protectedThis->readyReadHandler();

            return G_SOURCE_CONTINUE;
        });
    }
#endif

    if (!m_isHajrEnabled) {
        m_connectionQueue->dispatch([protectedThis] {
            protectedThis->readyReadHandler();
        });
    }
}

bool Connection::platformCanSendOutgoingMessages() const
{
    return true;
}

bool Connection::sendOutgoingMessage(UniqueRef<Encoder>&& encoder)
{
    static_assert(sizeof(MessageInfo) + attachmentMaxAmount * sizeof(size_t) <= messageMaxSize, "Attachments fit to message inline");

    UnixMessage outputMessage(encoder.get());
    if (outputMessage.attachments().size() > (attachmentMaxAmount - 1)) {
        ASSERT_NOT_REACHED();
        return false;
    }

    size_t maxInlineSize = m_isHajrEnabled ? (512 * 1024) : messageMaxSize;
    size_t messageSizeWithBodyInline = sizeof(MessageInfo) + (outputMessage.attachments().size() * sizeof(AttachmentInfo)) + outputMessage.bodySize();
    if (messageSizeWithBodyInline > maxInlineSize && outputMessage.bodySize()) {
        if (!outputMessage.setBodyOutOfLine())
            return false;
    }

    return sendOutputMessage(WTF::move(outputMessage));
}

bool Connection::sendOutputMessage(UnixMessage&& outputMessage)
{
    if (m_isHajrEnabled && m_outboundRing) {
        auto& messageInfo = outputMessage.messageInfo();
        auto& attachments = outputMessage.attachments();
        uint32_t attachmentCount = attachments.size();

        size_t totalPayloadSize = sizeof(messageInfo) + sizeof(attachmentCount) + (attachmentCount * sizeof(int32_t)) + outputMessage.bodySize() + sizeof(uint32_t);
        Vector<uint8_t> payload;
        payload.grow(totalPayloadSize);
        uint8_t* ptr = payload.mutableSpan().data();

        memcpy(ptr, &messageInfo, sizeof(messageInfo));
        ptr += sizeof(messageInfo);

        memcpy(ptr, &attachmentCount, sizeof(attachmentCount));
        ptr += sizeof(attachmentCount);

        size_t validFdCount = 0;
        for (auto& attachment : attachments) {
            int32_t handle = attachment.value();
            if (handle >= 0)
                validFdCount++;
            memcpy(ptr, &handle, sizeof(handle));
            ptr += sizeof(handle);
        }

        memcpy(ptr, outputMessage.body().data(), outputMessage.bodySize());

        uint32_t checksum = hajr_ipc_message_checksum(
            reinterpret_cast<const uint8_t*>(&messageInfo),
            sizeof(messageInfo),
            outputMessage.body().data(),
            outputMessage.bodySize()
        );
        memcpy(ptr + outputMessage.bodySize(), &checksum, sizeof(checksum));

        if (hajr_ring_write(m_outboundRing, payload.span().data(), payload.size()) == 1) {
            if (validFdCount > 0 && m_fdTransferFd != -1) {
                char dummy = 0;
                struct iovec iov;
                iov.iov_base = &dummy;
                iov.iov_len = 1;

                std::vector<char> cmsgBuf(CMSG_SPACE(sizeof(int) * validFdCount));
                struct msghdr msg;
                memset(&msg, 0, sizeof(msg));
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
                msg.msg_control = cmsgBuf.data();
                msg.msg_controllen = cmsgBuf.size();

                struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
                cmsg->cmsg_level = SOL_SOCKET;
                cmsg->cmsg_type = SCM_RIGHTS;
                cmsg->cmsg_len = CMSG_LEN(sizeof(int) * validFdCount);

                int* fdPtr = reinterpret_cast<int*>(CMSG_DATA(cmsg));
                size_t fdIdx = 0;
                for (size_t i = 0; i < attachmentCount; ++i) {
                    if (attachments[i].value() >= 0)
                        fdPtr[fdIdx++] = attachments[i].value();
                }

                ssize_t sendResult = sendmsg(m_fdTransferFd, &msg, MSG_NOSIGNAL);
                if (sendResult == -1)
                    LOG(IPC, "sendOutputMessage: SCM_RIGHTS failed fd=%d errno=%d (%s)", m_fdTransferFd, errno, strerror(errno));
            }
            hajr_ring_signal(m_outboundRing);
            return true;
        }
    }

    auto& messageInfo = outputMessage.messageInfo();
    struct msghdr message;
    memset(&message, 0, sizeof(message));

    struct iovec iov[3];
    memset(&iov, 0, sizeof(iov));

    message.msg_iov = iov;
    int iovLength = 1;

    iov[0].iov_base = reinterpret_cast<void*>(&messageInfo);
    iov[0].iov_len = sizeof(messageInfo);

    Vector<AttachmentInfo> attachmentInfo;
    MallocSpan<char> attachmentFDBuffer;

    auto& attachments = outputMessage.attachments();
    if (!attachments.isEmpty()) {
        int* fdPtr = nullptr;

        size_t validFdCount = std::count_if(attachments.begin(), attachments.end(),
            [](const Attachment& attachment) {
                return attachment.value() >= 0;
            });

        if (validFdCount > 0) {
            attachmentFDBuffer = MallocSpan<char>::zeroedMalloc(CMSG_SPACE(sizeof(int) * validFdCount));
            auto span = attachmentFDBuffer.mutableSpan();
            message.msg_control = span.data();
            message.msg_controllen = span.size();

            struct cmsghdr* cmsg = CMSG_FIRSTHDR(&message);
            cmsg->cmsg_level = SOL_SOCKET;
            cmsg->cmsg_type = SCM_RIGHTS;
            cmsg->cmsg_len = CMSG_LEN(sizeof(int) * validFdCount);

            fdPtr = reinterpret_cast<int*>(CMSG_DATA(cmsg));
        }

        attachmentInfo.grow(attachments.size());

        size_t fdIndex = 0;
        for (size_t i = 0; i < attachments.size(); ++i) {
            if (attachments[i].value() >= 0) {
                ASSERT(fdPtr);
                fdPtr[fdIndex++] = attachments[i].value();
            } else
                attachmentInfo[i].setNull();
        }

        iov[iovLength].iov_base = attachmentInfo.mutableSpan().data();
        iov[iovLength].iov_len = sizeof(AttachmentInfo) * attachments.size();
        ++iovLength;
    }

    if (!messageInfo.isBodyOutOfLine() && outputMessage.bodySize()) {
        iov[iovLength].iov_base = reinterpret_cast<void*>(outputMessage.body().data());
        iov[iovLength].iov_len = outputMessage.bodySize();
        ++iovLength;
    }

    message.msg_iovlen = iovLength;

    while (sendmsg(socketDescriptor(), &message, MSG_NOSIGNAL) == -1) {
        if (errno == EINTR)
            continue;
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            struct pollfd pollfd;

            pollfd.fd = socketDescriptor();
            pollfd.events = POLLOUT;
            pollfd.revents = 0;
            poll(&pollfd, 1, -1);
            continue;
        }

#if OS(LINUX)
        if (errno == EPIPE || errno == ECONNRESET)
#else
        if (errno == ECONNRESET)
#endif
        {
            connectionDidClose();
            return false;
        }

        if (m_isConnected)
            WTFLogAlways("Error sending IPC message: %s", safeStrerror(errno).data());
        return false;
    }

    return true;
}

std::optional<Connection::ConnectionIdentifierPair> Connection::createConnectionIdentifierPair()
{
    SocketPair socketPair = createPlatformConnection(SOCKET_TYPE);
    return { { Identifier { WTF::move(socketPair.server) }, ConnectionHandle { WTF::move(socketPair.client) } } };
}

void Connection::sendCredentials() const
{
}

} // namespace IPC

WTF_ALLOW_UNSAFE_BUFFER_USAGE_END
