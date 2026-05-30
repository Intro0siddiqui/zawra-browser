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

#pragma once

#include <wtf/Forward.h>
#include <wtf/Function.h>
#include <wtf/Noncopyable.h>

#if !USE(GLIB_EVENT_LOOP)
#include <atomic>
#include <memory>
#endif

#if USE(GLIB_EVENT_LOOP)
#include "GSocketMonitor.h"
#include <wtf/glib/GRefPtr.h>
// Forward declaration — avoids pulling gio.h into every TU that includes this header.
typedef struct _GSocket GSocket;
#endif

namespace WTF {

enum class SocketCondition : uint8_t {
    Readable = 1 << 0,
    Writable = 1 << 1,
    Error    = 1 << 2,
    Hangup   = 1 << 3,
};

// Bitwise operators so callers can write:
//   SocketCondition::Readable | SocketCondition::Error | SocketCondition::Hangup
inline SocketCondition operator|(SocketCondition a, SocketCondition b)
{
    return static_cast<SocketCondition>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
inline SocketCondition operator&(SocketCondition a, SocketCondition b)
{
    return static_cast<SocketCondition>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}
inline bool operator!(SocketCondition a) { return !static_cast<uint8_t>(a); }

// SocketMonitor — portable socket event monitoring abstraction.
//
// Unified API: start() always takes a raw int fd on all platforms.
// On GLib builds the implementation wraps it in a GSocket internally
// so callers never need to know about GSocket.
class SocketMonitor {
    WTF_MAKE_NONCOPYABLE(SocketMonitor);
public:
    SocketMonitor() = default;
    ~SocketMonitor();

    void start(int socketFd, SocketCondition, RunLoop&, Function<void(SocketCondition)>&&);
    void stop();
    bool isActive() const { return m_isActive; }

private:
    bool m_isActive { false };
    int m_socketFd { -1 };
    SocketCondition m_condition { SocketCondition::Readable };
    RunLoop* m_runLoop { nullptr };
    Function<void(SocketCondition)> m_callback;

#if USE(GLIB_EVENT_LOOP)
    GRefPtr<GSocket> m_socket;
    GSocketMonitor m_gsocketMonitor;
#else
    // Shared flag used to signal the background poll thread to exit.
    std::shared_ptr<std::atomic<bool>> m_stopFlag;
#endif
};

} // namespace WTF

using WTF::SocketMonitor;
using WTF::SocketCondition;