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
#include "SharedMemory.h"
#include "TrackPrivateRemoteIdentifier.h"
#include <WebCore/MediaPlayer.h>
#include <WebCore/SourceBufferPrivate.h>
#include <optional>
#include <utility>
#include <wtf/Forward.h>
#include <wtf/MediaTime.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class SharedBufferReference;
}

namespace WebCore {
class ContentType;
class PlatformTimeRanges;
}

namespace Messages {
namespace RemoteSourceBufferProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteSourceBufferProxy;
}

class SetActive {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetActive; }
    static constexpr bool isSync = false;

    explicit SetActive(bool active)
        : m_arguments(active)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class CanSwitchToType {
public:
    using Arguments = std::tuple<WebCore::ContentType>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_CanSwitchToType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit CanSwitchToType(const WebCore::ContentType& contentType)
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

class SetMode {
public:
    using Arguments = std::tuple<WebCore::SourceBufferAppendMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetMode; }
    static constexpr bool isSync = false;

    explicit SetMode(const WebCore::SourceBufferAppendMode& appendMode)
        : m_arguments(appendMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SourceBufferAppendMode&> m_arguments;
};

class Append {
public:
    using Arguments = std::tuple<IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_Append; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSourceBufferProxy_AppendReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::SharedMemory::Handle>>;
    explicit Append(const IPC::SharedBufferReference& data)
        : m_arguments(data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::SharedBufferReference&> m_arguments;
};

class Abort {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_Abort; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ResetParserState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ResetParserState; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RemovedFromMediaSource {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_RemovedFromMediaSource; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetMediaSourceEnded {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetMediaSourceEnded; }
    static constexpr bool isSync = false;

    explicit SetMediaSourceEnded(bool isEnded)
        : m_arguments(isEnded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetReadyState {
public:
    using Arguments = std::tuple<WebCore::MediaPlayer::ReadyState>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetReadyState; }
    static constexpr bool isSync = false;

    explicit SetReadyState(const WebCore::MediaPlayer::ReadyState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayer::ReadyState&> m_arguments;
};

class StartChangingType {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_StartChangingType; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ClientReadyStateChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ClientReadyStateChanged; }
    static constexpr bool isSync = false;

    explicit ClientReadyStateChanged(bool sourceIsEnded)
        : m_arguments(sourceIsEnded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class AddTrackBuffer {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_AddTrackBuffer; }
    static constexpr bool isSync = false;

    explicit AddTrackBuffer(const WebKit::TrackPrivateRemoteIdentifier& remoteIdentifier)
        : m_arguments(remoteIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class ResetTrackBuffers {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ResetTrackBuffers; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ClearTrackBuffers {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ClearTrackBuffers; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetAllTrackBuffersNeedRandomAccess {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetAllTrackBuffersNeedRandomAccess; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RemoveCodedFrames {
public:
    using Arguments = std::tuple<MediaTime, MediaTime, MediaTime, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_RemoveCodedFrames; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSourceBufferProxy_RemoveCodedFramesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::PlatformTimeRanges, uint64_t>;
    RemoveCodedFrames(const MediaTime& start, const MediaTime& end, const MediaTime& currentTime, bool isEnded)
        : m_arguments(start, end, currentTime, isEnded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&, const MediaTime&, const MediaTime&, bool> m_arguments;
};

class EvictCodedFrames {
public:
    using Arguments = std::tuple<uint64_t, uint64_t, MediaTime, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_EvictCodedFrames; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::PlatformTimeRanges, uint64_t>;
    EvictCodedFrames(uint64_t newDataSize, uint64_t maximumBufferSize, const MediaTime& currentTime, bool isEnded)
        : m_arguments(newDataSize, maximumBufferSize, currentTime, isEnded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint64_t, const MediaTime&, bool> m_arguments;
};

class ReenqueueMediaIfNeeded {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ReenqueueMediaIfNeeded; }
    static constexpr bool isSync = false;

    explicit ReenqueueMediaIfNeeded(const MediaTime& currentMediaTime)
        : m_arguments(currentMediaTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SetGroupStartTimestamp {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetGroupStartTimestamp; }
    static constexpr bool isSync = false;

    explicit SetGroupStartTimestamp(const MediaTime& timestamp)
        : m_arguments(timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SetGroupStartTimestampToEndTimestamp {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetGroupStartTimestampToEndTimestamp; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetShouldGenerateTimestamps {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetShouldGenerateTimestamps; }
    static constexpr bool isSync = false;

    explicit SetShouldGenerateTimestamps(bool shouldGenerateTimestamps)
        : m_arguments(shouldGenerateTimestamps)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ResetTimestampOffsetInTrackBuffers {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_ResetTimestampOffsetInTrackBuffers; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetTimestampOffset {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetTimestampOffset; }
    static constexpr bool isSync = false;

    explicit SetTimestampOffset(const MediaTime& timestampOffset)
        : m_arguments(timestampOffset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SetAppendWindowStart {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetAppendWindowStart; }
    static constexpr bool isSync = false;

    explicit SetAppendWindowStart(const MediaTime& appendWindowStart)
        : m_arguments(appendWindowStart)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SetAppendWindowEnd {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetAppendWindowEnd; }
    static constexpr bool isSync = false;

    explicit SetAppendWindowEnd(const MediaTime& appendWindowEnd)
        : m_arguments(appendWindowEnd)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SeekToTime {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SeekToTime; }
    static constexpr bool isSync = false;

    explicit SeekToTime(const MediaTime& mediaTime)
        : m_arguments(mediaTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class UpdateTrackIds {
public:
    using Arguments = std::tuple<Vector<std::pair<WebKit::TrackPrivateRemoteIdentifier, WebKit::TrackPrivateRemoteIdentifier>>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_UpdateTrackIds; }
    static constexpr bool isSync = false;

    explicit UpdateTrackIds(const Vector<std::pair<WebKit::TrackPrivateRemoteIdentifier, WebKit::TrackPrivateRemoteIdentifier>>& identifierPairs)
        : m_arguments(identifierPairs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<std::pair<WebKit::TrackPrivateRemoteIdentifier, WebKit::TrackPrivateRemoteIdentifier>>&> m_arguments;
};

class BufferedSamplesForTrackId {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_BufferedSamplesForTrackId; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSourceBufferProxy_BufferedSamplesForTrackIdReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit BufferedSamplesForTrackId(const WebKit::TrackPrivateRemoteIdentifier& remoteIdentifier)
        : m_arguments(remoteIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class EnqueuedSamplesForTrackID {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_EnqueuedSamplesForTrackID; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSourceBufferProxy_EnqueuedSamplesForTrackIDReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit EnqueuedSamplesForTrackID(const WebKit::TrackPrivateRemoteIdentifier& remoteIdentifier)
        : m_arguments(remoteIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class MemoryPressure {
public:
    using Arguments = std::tuple<uint64_t, MediaTime, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_MemoryPressure; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSourceBufferProxy_MemoryPressureReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::PlatformTimeRanges, uint64_t>;
    MemoryPressure(uint64_t maximumBufferSize, const MediaTime& currentTime, bool isEnded)
        : m_arguments(maximumBufferSize, currentTime, isEnded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const MediaTime&, bool> m_arguments;
};

class SetMaximumQueueDepthForTrackID {
public:
    using Arguments = std::tuple<AtomString, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_SetMaximumQueueDepthForTrackID; }
    static constexpr bool isSync = false;

    SetMaximumQueueDepthForTrackID(const AtomString& trackID, uint64_t depth)
        : m_arguments(trackID, depth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const AtomString&, uint64_t> m_arguments;
};

class MinimumUpcomingPresentationTimeForTrackID {
public:
    using Arguments = std::tuple<AtomString>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSourceBufferProxy_MinimumUpcomingPresentationTimeForTrackID; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<MediaTime>;
    explicit MinimumUpcomingPresentationTimeForTrackID(const AtomString& trackID)
        : m_arguments(trackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const AtomString&> m_arguments;
};

} // namespace RemoteSourceBufferProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
