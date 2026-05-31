/*
 * Copyright (C) 2026 Zawra Browser Authors. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "SocketMonitor.h"

#if USE(GLIB_EVENT_LOOP)
#include "GSocketMonitor.h"
#include <gio/gio.h>
#include <unistd.h>
#else
#include <poll.h>
#include <memory>
#include <atomic>
#endif

#include <wtf/Threading.h>

namespace WTF {

SocketMonitor::~SocketMonitor()
{
    stop();
}

// ============================================================================
// GLib event-loop path
// ============================================================================

#if USE(GLIB_EVENT_LOOP)

void SocketMonitor::start(int socketFd, SocketCondition condition, RunLoop& runLoop, Function<void(SocketCondition)>&& callback)
{
    stop();

    m_socketFd   = socketFd;
    m_condition  = condition;
    m_runLoop    = &runLoop;
    m_callback   = WTFMove(callback);

    // GSocket takes ownership of the fd, so dup first to keep m_socketDescriptor valid.
    // The original fd continues to be used by Connection for send()/recvmsg() directly.
    int dupFd = ::dup(socketFd);
    if (dupFd == -1)
        return;

    GError* error = nullptr;
    m_socket = adoptGRef(g_socket_new_from_fd(dupFd, &error));
    if (!m_socket) {
        if (error)
            g_error_free(error);
        ::close(dupFd);
        return;
    }

    // Build GIOCondition from our SocketCondition bitmask.
    // Start from 0 — do NOT pre-set G_IO_IN to avoid the double-set bug.
    GIOCondition gioCond = static_cast<GIOCondition>(0);
    if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Readable))
        gioCond |= G_IO_IN;
    if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Writable))
        gioCond |= G_IO_OUT;
    if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Error))
        gioCond |= G_IO_ERR;
    if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Hangup))
        gioCond |= G_IO_HUP | G_IO_NVAL;

    // The wrapper translates GIOCondition back to our SocketCondition enum.
    // Captures `this` — safe because stop() calls m_gsocketMonitor.stop() which
    // removes the source before `this` can be destroyed.
    auto wrapperCallback = [this](GIOCondition receivedCond) -> gboolean {
        SocketCondition ourCond = SocketCondition::Readable;
        if (receivedCond & G_IO_IN)
            ourCond = SocketCondition::Readable;
        else if (receivedCond & G_IO_OUT)
            ourCond = SocketCondition::Writable;
        else if (receivedCond & G_IO_ERR)
            ourCond = SocketCondition::Error;
        else if (receivedCond & (G_IO_HUP | G_IO_NVAL))
            ourCond = SocketCondition::Hangup;

        if (m_callback)
            m_callback(ourCond);
        return G_SOURCE_CONTINUE;
    };

    m_gsocketMonitor.start(m_socket.get(), gioCond, runLoop, WTFMove(wrapperCallback));
    m_isActive = true;
}

// ============================================================================
// Non-GLib POSIX path — background poll() thread
// ============================================================================

#else

void SocketMonitor::start(int socketFd, SocketCondition condition, RunLoop& runLoop, Function<void(SocketCondition)>&& callback)
{
    stop();

    m_socketFd  = socketFd;
    m_condition = condition;
    m_runLoop   = &runLoop;
    m_isActive  = true;

    // Shared stop flag — set by stop(), checked by the poll thread every 50 ms.
    auto stopFlag = std::make_shared<std::atomic<bool>>(false);
    m_stopFlag = stopFlag;

    // WTF::Function is move-only; wrap in shared_ptr so both this object and
    // the thread lambda can safely reference it without copying.
    auto sharedCallback = std::make_shared<Function<void(SocketCondition)>>(WTFMove(callback));

    Thread::create("SocketMonitor", [socketFd, condition, &runLoop, stopFlag, sharedCallback]() mutable {
        while (!stopFlag->load(std::memory_order_relaxed)) {
            struct pollfd pfd;
            pfd.fd      = socketFd;
            pfd.events  = 0;
            pfd.revents = 0;

            if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Readable))
                pfd.events |= POLLIN;
            if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Writable))
                pfd.events |= POLLOUT;
            if (static_cast<uint8_t>(condition) & static_cast<uint8_t>(SocketCondition::Error))
                pfd.events |= POLLERR | POLLHUP;

            // 50 ms timeout so the stop flag is checked regularly.
            int result = ::poll(&pfd, 1, 50);

            if (stopFlag->load(std::memory_order_relaxed))
                break;

            if (result <= 0)
                continue; // timeout, EINTR, or error — loop again

            SocketCondition triggered;
            if (pfd.revents & POLLIN)
                triggered = SocketCondition::Readable;
            else if (pfd.revents & POLLOUT)
                triggered = SocketCondition::Writable;
            else if (pfd.revents & (POLLERR | POLLHUP | POLLPRI))
                triggered = SocketCondition::Error;
            else
                continue;

            if (!sharedCallback || !(*sharedCallback))
                continue;

            // Dispatch to the run loop; capture shared_ptr by value (not move)
            // so the thread can fire again on the next poll cycle.
            runLoop.dispatch([sharedCallback, triggered]() {
                if (*sharedCallback)
                    (*sharedCallback)(triggered);
            });
        }
    });
    // Thread::create() returns Ref<Thread>; dropping the Ref here is safe —
    // the thread holds a self-reference while running.
}

#endif // USE(GLIB_EVENT_LOOP)

// ============================================================================
// stop() — common to both paths
// ============================================================================

void SocketMonitor::stop()
{
#if USE(GLIB_EVENT_LOOP)
    m_gsocketMonitor.stop();
    m_socket = nullptr;
#else
    if (m_stopFlag) {
        m_stopFlag->store(true, std::memory_order_relaxed);
        m_stopFlag.reset();
    }
    m_isActive = false;
#endif
    m_callback  = nullptr;
    m_socketFd  = -1;
}

} // namespace WTF