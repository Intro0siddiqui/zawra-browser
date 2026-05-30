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

#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "RemoteSourceBufferIdentifier.h"
#include <WebCore/MediaPlayerEnums.h>
#include <WebCore/MediaSourcePrivate.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MediaTime.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class ContentType;
class PlatformTimeRanges;
}

namespace Messages {
namespace RemoteMediaSourceProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaSourceProxy;
}

class AddSourceBuffer {
public:
    using Arguments = std::tuple<WebCore::ContentType>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_AddSourceBuffer; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::MediaSourcePrivate::AddStatus, std::optional<WebKit::RemoteSourceBufferIdentifier>>;
    explicit AddSourceBuffer(const WebCore::ContentType& contentType)
        : m_arguments(contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ContentType&> m_arguments;
};

class DurationChanged {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_DurationChanged; }
    static constexpr bool isSync = false;

    explicit DurationChanged(const MediaTime& duration)
        : m_arguments(duration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class BufferedChanged {
public:
    using Arguments = std::tuple<WebCore::PlatformTimeRanges>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_BufferedChanged; }
    static constexpr bool isSync = false;

    explicit BufferedChanged(const WebCore::PlatformTimeRanges& buffered)
        : m_arguments(buffered)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformTimeRanges&> m_arguments;
};

class SetReadyState {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::ReadyState>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_SetReadyState; }
    static constexpr bool isSync = false;

    explicit SetReadyState(const WebCore::MediaPlayerEnums::ReadyState& readyState)
        : m_arguments(readyState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayerEnums::ReadyState&> m_arguments;
};

class SetIsSeeking {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_SetIsSeeking; }
    static constexpr bool isSync = false;

    explicit SetIsSeeking(bool isSeeking)
        : m_arguments(isSeeking)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class WaitForSeekCompleted {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_WaitForSeekCompleted; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SeekCompleted {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_SeekCompleted; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetTimeFudgeFactor {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_SetTimeFudgeFactor; }
    static constexpr bool isSync = false;

    explicit SetTimeFudgeFactor(const MediaTime& fudgeFactor)
        : m_arguments(fudgeFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class MarkEndOfStream {
public:
    using Arguments = std::tuple<WebCore::MediaSourcePrivate::EndOfStreamStatus>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_MarkEndOfStream; }
    static constexpr bool isSync = false;

    explicit MarkEndOfStream(const WebCore::MediaSourcePrivate::EndOfStreamStatus& status)
        : m_arguments(status)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaSourcePrivate::EndOfStreamStatus&> m_arguments;
};

class UnmarkEndOfStream {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaSourceProxy_UnmarkEndOfStream; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace RemoteMediaSourceProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
