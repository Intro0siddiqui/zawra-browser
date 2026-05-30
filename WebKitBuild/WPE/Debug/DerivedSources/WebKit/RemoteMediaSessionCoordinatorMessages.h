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

#if ENABLE(MEDIA_SESSION_COORDINATOR)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MonotonicTime.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
enum class MediaSessionCoordinatorState : uint8_t;
}

namespace Messages {
namespace RemoteMediaSessionCoordinator {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaSessionCoordinator;
}

class SeekSessionToTime {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSessionCoordinator_SeekSessionToTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaSessionCoordinator_SeekSessionToTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit SeekSessionToTime(double time)
        : m_arguments(time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class PlaySession {
public:
    using Arguments = std::tuple<std::optional<double>, std::optional<MonotonicTime>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSessionCoordinator_PlaySession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaSessionCoordinator_PlaySessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    PlaySession(const std::optional<double>& atTime, const std::optional<MonotonicTime>& hostTime)
        : m_arguments(atTime, hostTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<double>&, const std::optional<MonotonicTime>&> m_arguments;
};

class PauseSession {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSessionCoordinator_PauseSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaSessionCoordinator_PauseSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetSessionTrack {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSessionCoordinator_SetSessionTrack; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaSessionCoordinator_SetSessionTrackReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit SetSessionTrack(const String& trackIdentifier)
        : m_arguments(trackIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class CoordinatorStateChanged {
public:
    using Arguments = std::tuple<WebCore::MediaSessionCoordinatorState>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSessionCoordinator_CoordinatorStateChanged; }
    static constexpr bool isSync = false;

    explicit CoordinatorStateChanged(WebCore::MediaSessionCoordinatorState state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaSessionCoordinatorState> m_arguments;
};

} // namespace RemoteMediaSessionCoordinator
} // namespace Messages

#endif // ENABLE(MEDIA_SESSION_COORDINATOR)
