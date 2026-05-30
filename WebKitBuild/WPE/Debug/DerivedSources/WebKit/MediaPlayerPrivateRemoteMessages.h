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

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DataReference.h"
#include "LayerHostingContext.h"
#include "MessageNames.h"
#include "RemoteMediaResourceIdentifier.h"
#include "RemoteVideoFrameProxy.h"
#include "TrackPrivateRemoteIdentifier.h"
#include <WebCore/Cookie.h>
#include <WebCore/PlatformMediaResourceLoader.h>
#include <WebCore/ResourceError.h>
#include <optional>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/MediaTime.h>
#include <wtf/Seconds.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class FloatSize;
class ISOWebVTTCue;
class IntSize;
class ResourceRequest;
class SerializedPlatformDataCueValue;
struct GenericCueData;
struct VideoFrameMetadata;
}

namespace WebKit {
struct AudioTrackPrivateRemoteConfiguration;
struct RemoteMediaPlayerState;
struct TextTrackPrivateRemoteConfiguration;
struct VideoTrackPrivateRemoteConfiguration;
}

namespace Messages {
namespace MediaPlayerPrivateRemote {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::MediaPlayerPrivateRemote;
}

class NetworkStateChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_NetworkStateChanged; }
    static constexpr bool isSync = false;

    explicit NetworkStateChanged(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class ReadyStateChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ReadyStateChanged; }
    static constexpr bool isSync = false;

    explicit ReadyStateChanged(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class FirstVideoFrameAvailable {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_FirstVideoFrameAvailable; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class VolumeChanged {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_VolumeChanged; }
    static constexpr bool isSync = false;

    explicit VolumeChanged(double volume)
        : m_arguments(volume)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class MuteChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_MuteChanged; }
    static constexpr bool isSync = false;

    explicit MuteChanged(bool mute)
        : m_arguments(mute)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class TimeChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_TimeChanged; }
    static constexpr bool isSync = false;

    explicit TimeChanged(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class DurationChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_DurationChanged; }
    static constexpr bool isSync = false;

    explicit DurationChanged(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class RateChanged {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RateChanged; }
    static constexpr bool isSync = false;

    explicit RateChanged(double rate)
        : m_arguments(rate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class PlaybackStateChanged {
public:
    using Arguments = std::tuple<bool, MediaTime, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_PlaybackStateChanged; }
    static constexpr bool isSync = false;

    PlaybackStateChanged(bool paused, const MediaTime& mediaTime, const MonotonicTime& wallTime)
        : m_arguments(paused, mediaTime, wallTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const MediaTime&, const MonotonicTime&> m_arguments;
};

class EngineFailedToLoad {
public:
    using Arguments = std::tuple<int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_EngineFailedToLoad; }
    static constexpr bool isSync = false;

    explicit EngineFailedToLoad(int64_t platformErrorCode)
        : m_arguments(platformErrorCode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int64_t> m_arguments;
};

class UpdateCachedState {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_UpdateCachedState; }
    static constexpr bool isSync = false;

    explicit UpdateCachedState(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class CharacteristicChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaPlayerState>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_CharacteristicChanged; }
    static constexpr bool isSync = false;

    explicit CharacteristicChanged(const WebKit::RemoteMediaPlayerState& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaPlayerState&> m_arguments;
};

class SizeChanged {
public:
    using Arguments = std::tuple<WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_SizeChanged; }
    static constexpr bool isSync = false;

    explicit SizeChanged(const WebCore::FloatSize& naturalSize)
        : m_arguments(naturalSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&> m_arguments;
};

class RenderingModeChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RenderingModeChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CurrentTimeChanged {
public:
    using Arguments = std::tuple<MediaTime, MonotonicTime, bool>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_CurrentTimeChanged; }
    static constexpr bool isSync = false;

    CurrentTimeChanged(const MediaTime& mediaTime, const MonotonicTime& wallTime, bool timeIsProgressing)
        : m_arguments(mediaTime, wallTime, timeIsProgressing)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&, const MonotonicTime&, bool> m_arguments;
};

class AddRemoteAudioTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::AudioTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddRemoteAudioTrack; }
    static constexpr bool isSync = false;

    AddRemoteAudioTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::AudioTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::AudioTrackPrivateRemoteConfiguration&> m_arguments;
};

class RemoveRemoteAudioTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveRemoteAudioTrack; }
    static constexpr bool isSync = false;

    explicit RemoveRemoteAudioTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID)
        : m_arguments(trackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class RemoteAudioTrackConfigurationChanged {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::AudioTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoteAudioTrackConfigurationChanged; }
    static constexpr bool isSync = false;

    RemoteAudioTrackConfigurationChanged(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::AudioTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::AudioTrackPrivateRemoteConfiguration&> m_arguments;
};

class AddRemoteVideoTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::VideoTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddRemoteVideoTrack; }
    static constexpr bool isSync = false;

    AddRemoteVideoTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::VideoTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::VideoTrackPrivateRemoteConfiguration&> m_arguments;
};

class RemoveRemoteVideoTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveRemoteVideoTrack; }
    static constexpr bool isSync = false;

    explicit RemoveRemoteVideoTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID)
        : m_arguments(trackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class RemoteVideoTrackConfigurationChanged {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::VideoTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoteVideoTrackConfigurationChanged; }
    static constexpr bool isSync = false;

    RemoteVideoTrackConfigurationChanged(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::VideoTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::VideoTrackPrivateRemoteConfiguration&> m_arguments;
};

class AddRemoteTextTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::TextTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddRemoteTextTrack; }
    static constexpr bool isSync = false;

    AddRemoteTextTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::TextTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::TextTrackPrivateRemoteConfiguration&> m_arguments;
};

class RemoveRemoteTextTrack {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveRemoteTextTrack; }
    static constexpr bool isSync = false;

    explicit RemoveRemoteTextTrack(const WebKit::TrackPrivateRemoteIdentifier& trackID)
        : m_arguments(trackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&> m_arguments;
};

class RemoteTextTrackConfigurationChanged {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebKit::TextTrackPrivateRemoteConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoteTextTrackConfigurationChanged; }
    static constexpr bool isSync = false;

    RemoteTextTrackConfigurationChanged(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebKit::TextTrackPrivateRemoteConfiguration& configuration)
        : m_arguments(trackID, configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebKit::TextTrackPrivateRemoteConfiguration&> m_arguments;
};

class ParseWebVTTFileHeader {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ParseWebVTTFileHeader; }
    static constexpr bool isSync = false;

    ParseWebVTTFileHeader(const WebKit::TrackPrivateRemoteIdentifier& trackID, const String& header)
        : m_arguments(trackID, header)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const String&> m_arguments;
};

class ParseWebVTTCueData {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ParseWebVTTCueData; }
    static constexpr bool isSync = false;

    ParseWebVTTCueData(const WebKit::TrackPrivateRemoteIdentifier& trackID, const IPC::DataReference& data)
        : m_arguments(trackID, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const IPC::DataReference&> m_arguments;
};

class ParseWebVTTCueDataStruct {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebCore::ISOWebVTTCue>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ParseWebVTTCueDataStruct; }
    static constexpr bool isSync = false;

    ParseWebVTTCueDataStruct(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebCore::ISOWebVTTCue& cueData)
        : m_arguments(trackID, cueData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebCore::ISOWebVTTCue&> m_arguments;
};

class AddDataCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, MediaTime, MediaTime, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddDataCue; }
    static constexpr bool isSync = false;

    AddDataCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const MediaTime& start, const MediaTime& end, const IPC::DataReference& data)
        : m_arguments(trackID, start, end, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const MediaTime&, const MediaTime&, const IPC::DataReference&> m_arguments;
};

#if ENABLE(DATACUE_VALUE)
class AddDataCueWithType {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, MediaTime, MediaTime, WebCore::SerializedPlatformDataCueValue, String>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddDataCueWithType; }
    static constexpr bool isSync = false;

    AddDataCueWithType(const WebKit::TrackPrivateRemoteIdentifier& trackID, const MediaTime& start, const MediaTime& end, const WebCore::SerializedPlatformDataCueValue& cueData, const String& type)
        : m_arguments(trackID, start, end, cueData, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const MediaTime&, const MediaTime&, const WebCore::SerializedPlatformDataCueValue&, const String&> m_arguments;
};
#endif

#if ENABLE(DATACUE_VALUE)
class UpdateDataCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, MediaTime, MediaTime, WebCore::SerializedPlatformDataCueValue>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_UpdateDataCue; }
    static constexpr bool isSync = false;

    UpdateDataCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const MediaTime& start, const MediaTime& end, const WebCore::SerializedPlatformDataCueValue& cueData)
        : m_arguments(trackID, start, end, cueData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const MediaTime&, const MediaTime&, const WebCore::SerializedPlatformDataCueValue&> m_arguments;
};
#endif

#if ENABLE(DATACUE_VALUE)
class RemoveDataCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, MediaTime, MediaTime, WebCore::SerializedPlatformDataCueValue>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveDataCue; }
    static constexpr bool isSync = false;

    RemoveDataCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const MediaTime& start, const MediaTime& end, const WebCore::SerializedPlatformDataCueValue& cueData)
        : m_arguments(trackID, start, end, cueData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const MediaTime&, const MediaTime&, const WebCore::SerializedPlatformDataCueValue&> m_arguments;
};
#endif

class AddGenericCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebCore::GenericCueData>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_AddGenericCue; }
    static constexpr bool isSync = false;

    AddGenericCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebCore::GenericCueData& cue)
        : m_arguments(trackID, cue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebCore::GenericCueData&> m_arguments;
};

class UpdateGenericCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebCore::GenericCueData>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_UpdateGenericCue; }
    static constexpr bool isSync = false;

    UpdateGenericCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebCore::GenericCueData& cue)
        : m_arguments(trackID, cue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebCore::GenericCueData&> m_arguments;
};

class RemoveGenericCue {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebCore::GenericCueData>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveGenericCue; }
    static constexpr bool isSync = false;

    RemoveGenericCue(const WebKit::TrackPrivateRemoteIdentifier& trackID, const WebCore::GenericCueData& cue)
        : m_arguments(trackID, cue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, const WebCore::GenericCueData&> m_arguments;
};

class RequestResource {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::ResourceRequest, WebCore::PlatformMediaResourceLoader::LoadOptions>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RequestResource; }
    static constexpr bool isSync = false;

    RequestResource(const WebKit::RemoteMediaResourceIdentifier& remoteMediaResourceIdentifier, const WebCore::ResourceRequest& request, WebCore::PlatformMediaResourceLoader::LoadOptions options)
        : m_arguments(remoteMediaResourceIdentifier, request, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::ResourceRequest&, WebCore::PlatformMediaResourceLoader::LoadOptions> m_arguments;
};

class RemoveResource {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_RemoveResource; }
    static constexpr bool isSync = false;

    explicit RemoveResource(const WebKit::RemoteMediaResourceIdentifier& remoteMediaResourceIdentifier)
        : m_arguments(remoteMediaResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&> m_arguments;
};

class SendH2Ping {
public:
    using Arguments = std::tuple<URL>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_SendH2Ping; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::MediaPlayerPrivateRemote_SendH2PingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Seconds, WebCore::ResourceError>>;
    explicit SendH2Ping(const URL& url)
        : m_arguments(url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&> m_arguments;
};

class ResourceNotSupported {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ResourceNotSupported; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ActiveSourceBuffersChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_ActiveSourceBuffersChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(ENCRYPTED_MEDIA)
class WaitingForKeyChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_WaitingForKeyChanged; }
    static constexpr bool isSync = false;

    explicit WaitingForKeyChanged(bool waitingForKey)
        : m_arguments(waitingForKey)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class InitializationDataEncountered {
public:
    using Arguments = std::tuple<String, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_InitializationDataEncountered; }
    static constexpr bool isSync = false;

    InitializationDataEncountered(const String& initDataType, const IPC::DataReference& initData)
        : m_arguments(initDataType, initData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const IPC::DataReference&> m_arguments;
};
#endif

#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
class MediaPlayerKeyNeeded {
public:
    using Arguments = std::tuple<IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_MediaPlayerKeyNeeded; }
    static constexpr bool isSync = false;

    explicit MediaPlayerKeyNeeded(const IPC::DataReference& message)
        : m_arguments(message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET)
class CurrentPlaybackTargetIsWirelessChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_CurrentPlaybackTargetIsWirelessChanged; }
    static constexpr bool isSync = false;

    explicit CurrentPlaybackTargetIsWirelessChanged(bool isCurrentPlaybackTargetWireless)
        : m_arguments(isCurrentPlaybackTargetWireless)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class GetRawCookies {
public:
    using Arguments = std::tuple<URL>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_GetRawCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::MediaPlayerPrivateRemote_GetRawCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::Cookie>>;
    explicit GetRawCookies(const URL& url)
        : m_arguments(url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class PushVideoFrameMetadata {
public:
    using Arguments = std::tuple<WebCore::VideoFrameMetadata, WebKit::RemoteVideoFrameProxy::Properties>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_PushVideoFrameMetadata; }
    static constexpr bool isSync = false;

    PushVideoFrameMetadata(const WebCore::VideoFrameMetadata& metadata, const WebKit::RemoteVideoFrameProxy::Properties& frameProperties)
        : m_arguments(metadata, frameProperties)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::VideoFrameMetadata&, const WebKit::RemoteVideoFrameProxy::Properties&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class LayerHostingContextIdChanged {
public:
    using Arguments = std::tuple<std::optional<WebKit::LayerHostingContextID>, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::MediaPlayerPrivateRemote_LayerHostingContextIdChanged; }
    static constexpr bool isSync = false;

    LayerHostingContextIdChanged(const std::optional<WebKit::LayerHostingContextID>& inlineLayerHostingContextId, const WebCore::IntSize& presentationSize)
        : m_arguments(inlineLayerHostingContextId, presentationSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::LayerHostingContextID>&, const WebCore::IntSize&> m_arguments;
};
#endif

} // namespace MediaPlayerPrivateRemote
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
