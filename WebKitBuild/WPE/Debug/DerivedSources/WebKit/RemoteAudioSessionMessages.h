/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <WebCore/AudioSession.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebKit {
struct RemoteAudioSessionConfiguration;
}

namespace Messages {
namespace RemoteAudioSession {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteAudioSession;
}

class ConfigurationChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioSessionConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioSession_ConfigurationChanged; }
    static constexpr bool isSync = false;

    explicit ConfigurationChanged(const WebKit::RemoteAudioSessionConfiguration& configuration)
        : m_arguments(configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioSessionConfiguration&> m_arguments;
};

class BeginInterruptionRemote {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioSession_BeginInterruptionRemote; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class EndInterruptionRemote {
public:
    using Arguments = std::tuple<WebCore::AudioSession::MayResume>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioSession_EndInterruptionRemote; }
    static constexpr bool isSync = false;

    explicit EndInterruptionRemote(const WebCore::AudioSession::MayResume& flags)
        : m_arguments(flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::AudioSession::MayResume&> m_arguments;
};

} // namespace RemoteAudioSession
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
