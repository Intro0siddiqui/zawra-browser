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
#include "MessageNames.h"
#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
#include "RemoteCDMInstanceIdentifier.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(LEGACY_ENCRYPTED_MEDIA)
#include "RemoteLegacyCDMSessionIdentifier.h"
#endif
#include "RemoteMediaSourceIdentifier.h"
#include "RemoteVideoFrameProxy.h"
#include "SandboxExtension.h"
#include "TrackPrivateRemoteIdentifier.h"
#include <WebCore/DestinationColorSpace.h>
#include <WebCore/InbandTextTrackPrivate.h>
#include <WebCore/MediaPlayer.h>
#include <WebCore/MediaPlayerEnums.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MachSendRight.h>
#include <wtf/MediaTime.h>
#include <wtf/MonotonicTime.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class ContentType;
class FloatSize;
class IntSize;
class LayoutRect;
class MediaPlaybackTargetContext;
class SecurityOriginData;
enum class DynamicRangeMode : uint8_t;
}

namespace WebKit {
struct RemoteMediaPlayerConfiguration;
}

namespace Messages {
namespace RemoteMediaPlayerProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaPlayerProxy;
}

class PrepareForPlayback {
public:
    using Arguments = std::tuple<bool, WebCore::MediaPlayerEnums::Preload, bool, WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm, bool, WebCore::IntSize, float, WebCore::DynamicRangeMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PrepareForPlayback; }
    static constexpr bool isSync = false;

    PrepareForPlayback(bool privateMode, WebCore::MediaPlayerEnums::Preload preload, bool preservesPitch, const WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm& pitchCorrectionAlgorithm, bool prepareForRendering, const WebCore::IntSize& presentationSize, float videoContentScale, WebCore::DynamicRangeMode mode)
        : m_arguments(privateMode, preload, preservesPitch, pitchCorrectionAlgorithm, prepareForRendering, presentationSize, videoContentScale, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, WebCore::MediaPlayerEnums::Preload, bool, const WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm&, bool, const WebCore::IntSize&, float, WebCore::DynamicRangeMode> m_arguments;
};

class Load {
public:
    using Arguments = std::tuple<URL, std::optional<WebKit::SandboxExtension::Handle>, WebCore::ContentType, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_Load; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaPlayerProxy_LoadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RemoteMediaPlayerConfiguration>;
    Load(const URL& url, const std::optional<WebKit::SandboxExtension::Handle>& sandboxExtension, const WebCore::ContentType& contentType, const String& keySystem, bool requiresRemotePlayback)
        : m_arguments(url, sandboxExtension, contentType, keySystem, requiresRemotePlayback)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const std::optional<WebKit::SandboxExtension::Handle>&, const WebCore::ContentType&, const String&, bool> m_arguments;
};

#if ENABLE(MEDIA_SOURCE)
class LoadMediaSource {
public:
    using Arguments = std::tuple<URL, WebCore::ContentType, bool, WebKit::RemoteMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_LoadMediaSource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaPlayerProxy_LoadMediaSourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RemoteMediaPlayerConfiguration>;
    LoadMediaSource(const URL& url, const WebCore::ContentType& contentType, bool webMParserEnabled, const WebKit::RemoteMediaSourceIdentifier& mediaSourceIdentifier)
        : m_arguments(url, contentType, webMParserEnabled, mediaSourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::ContentType&, bool, const WebKit::RemoteMediaSourceIdentifier&> m_arguments;
};
#endif

class CancelLoad {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_CancelLoad; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PrepareToPlay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PrepareToPlay; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Play {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_Play; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Pause {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_Pause; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetVolume {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetVolume; }
    static constexpr bool isSync = false;

    explicit SetVolume(double volume)
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

class SetMuted {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetMuted; }
    static constexpr bool isSync = false;

    explicit SetMuted(bool muted)
        : m_arguments(muted)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class Seek {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_Seek; }
    static constexpr bool isSync = false;

    explicit Seek(const MediaTime& time)
        : m_arguments(time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SeekWithTolerance {
public:
    using Arguments = std::tuple<MediaTime, MediaTime, MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SeekWithTolerance; }
    static constexpr bool isSync = false;

    SeekWithTolerance(const MediaTime& time, const MediaTime& negativeTolerance, const MediaTime& positiveTolerance)
        : m_arguments(time, negativeTolerance, positiveTolerance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&, const MediaTime&, const MediaTime&> m_arguments;
};

class SetPreload {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::Preload>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPreload; }
    static constexpr bool isSync = false;

    explicit SetPreload(WebCore::MediaPlayerEnums::Preload preload)
        : m_arguments(preload)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaPlayerEnums::Preload> m_arguments;
};

class SetPrivateBrowsingMode {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPrivateBrowsingMode; }
    static constexpr bool isSync = false;

    explicit SetPrivateBrowsingMode(bool privateMode)
        : m_arguments(privateMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetPreservesPitch {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPreservesPitch; }
    static constexpr bool isSync = false;

    explicit SetPreservesPitch(bool preservesPitch)
        : m_arguments(preservesPitch)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetPitchCorrectionAlgorithm {
public:
    using Arguments = std::tuple<WebCore::MediaPlayer::PitchCorrectionAlgorithm>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPitchCorrectionAlgorithm; }
    static constexpr bool isSync = false;

    explicit SetPitchCorrectionAlgorithm(const WebCore::MediaPlayer::PitchCorrectionAlgorithm& algorithm)
        : m_arguments(algorithm)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayer::PitchCorrectionAlgorithm&> m_arguments;
};

class PrepareForRendering {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PrepareForRendering; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetPageIsVisible {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPageIsVisible; }
    static constexpr bool isSync = false;

    explicit SetPageIsVisible(bool visible)
        : m_arguments(visible)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetShouldMaintainAspectRatio {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldMaintainAspectRatio; }
    static constexpr bool isSync = false;

    explicit SetShouldMaintainAspectRatio(bool maintainAspectRatio)
        : m_arguments(maintainAspectRatio)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class AcceleratedRenderingStateChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_AcceleratedRenderingStateChanged; }
    static constexpr bool isSync = false;

    explicit AcceleratedRenderingStateChanged(bool canBeAccelerated)
        : m_arguments(canBeAccelerated)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetShouldDisableSleep {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldDisableSleep; }
    static constexpr bool isSync = false;

    explicit SetShouldDisableSleep(bool disable)
        : m_arguments(disable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetRate {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetRate; }
    static constexpr bool isSync = false;

    explicit SetRate(double rate)
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

class DidLoadingProgress {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_DidLoadingProgress; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaPlayerProxy_DidLoadingProgressReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(VIDEO_PRESENTATION_MODE)
class UpdateVideoFullscreenInlineImage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_UpdateVideoFullscreenInlineImage; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(VIDEO_PRESENTATION_MODE)
class SetVideoFullscreenMode {
public:
    using Arguments = std::tuple<WebCore::MediaPlayer::VideoFullscreenMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetVideoFullscreenMode; }
    static constexpr bool isSync = false;

    explicit SetVideoFullscreenMode(const WebCore::MediaPlayer::VideoFullscreenMode& mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayer::VideoFullscreenMode&> m_arguments;
};
#endif

#if ENABLE(VIDEO_PRESENTATION_MODE)
class SetVideoFullscreenGravity {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::VideoGravity>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetVideoFullscreenGravity; }
    static constexpr bool isSync = false;

    explicit SetVideoFullscreenGravity(WebCore::MediaPlayerEnums::VideoGravity gravity)
        : m_arguments(gravity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaPlayerEnums::VideoGravity> m_arguments;
};
#endif

#if ENABLE(VIDEO_PRESENTATION_MODE)
class VideoFullscreenStandbyChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_VideoFullscreenStandbyChanged; }
    static constexpr bool isSync = false;

    explicit VideoFullscreenStandbyChanged(bool standby)
        : m_arguments(standby)
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

class SetBufferingPolicy {
public:
    using Arguments = std::tuple<WebCore::MediaPlayer::BufferingPolicy>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetBufferingPolicy; }
    static constexpr bool isSync = false;

    explicit SetBufferingPolicy(const WebCore::MediaPlayer::BufferingPolicy& policy)
        : m_arguments(policy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayer::BufferingPolicy&> m_arguments;
};

class SetPresentationSize {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPresentationSize; }
    static constexpr bool isSync = false;

    explicit SetPresentationSize(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

#if PLATFORM(COCOA)
class SetVideoInlineSizeFenced {
public:
    using Arguments = std::tuple<WebCore::FloatSize, MachSendRight>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetVideoInlineSizeFenced; }
    static constexpr bool isSync = false;

    SetVideoInlineSizeFenced(const WebCore::FloatSize& size, MachSendRight&& machSendRight)
        : m_arguments(size, WTFMove(machSendRight))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&, MachSendRight&&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET)
class SetWirelessVideoPlaybackDisabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetWirelessVideoPlaybackDisabled; }
    static constexpr bool isSync = false;

    explicit SetWirelessVideoPlaybackDisabled(bool disabled)
        : m_arguments(disabled)
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

#if ENABLE(WIRELESS_PLAYBACK_TARGET)
class SetWirelessPlaybackTarget {
public:
    using Arguments = std::tuple<WebCore::MediaPlaybackTargetContext>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetWirelessPlaybackTarget; }
    static constexpr bool isSync = false;

    explicit SetWirelessPlaybackTarget(const WebCore::MediaPlaybackTargetContext& target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlaybackTargetContext&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET)
class SetShouldPlayToPlaybackTarget {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldPlayToPlaybackTarget; }
    static constexpr bool isSync = false;

    explicit SetShouldPlayToPlaybackTarget(bool shouldPlay)
        : m_arguments(shouldPlay)
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

#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
class SetLegacyCDMSession {
public:
    using Arguments = std::tuple<std::optional<WebKit::RemoteLegacyCDMSessionIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetLegacyCDMSession; }
    static constexpr bool isSync = false;

    explicit SetLegacyCDMSession(const std::optional<WebKit::RemoteLegacyCDMSessionIdentifier>& instanceId)
        : m_arguments(instanceId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::RemoteLegacyCDMSessionIdentifier>&> m_arguments;
};
#endif

#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
class KeyAdded {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_KeyAdded; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class CdmInstanceAttached {
public:
    using Arguments = std::tuple<WebKit::RemoteCDMInstanceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_CdmInstanceAttached; }
    static constexpr bool isSync = false;

    explicit CdmInstanceAttached(const WebKit::RemoteCDMInstanceIdentifier& instanceId)
        : m_arguments(instanceId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteCDMInstanceIdentifier&> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class CdmInstanceDetached {
public:
    using Arguments = std::tuple<WebKit::RemoteCDMInstanceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_CdmInstanceDetached; }
    static constexpr bool isSync = false;

    explicit CdmInstanceDetached(const WebKit::RemoteCDMInstanceIdentifier& instanceId)
        : m_arguments(instanceId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteCDMInstanceIdentifier&> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class AttemptToDecryptWithInstance {
public:
    using Arguments = std::tuple<WebKit::RemoteCDMInstanceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_AttemptToDecryptWithInstance; }
    static constexpr bool isSync = false;

    explicit AttemptToDecryptWithInstance(const WebKit::RemoteCDMInstanceIdentifier& instanceId)
        : m_arguments(instanceId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteCDMInstanceIdentifier&> m_arguments;
};
#endif

#if ENABLE(LEGACY_ENCRYPTED_MEDIA) && ENABLE(ENCRYPTED_MEDIA)
class SetShouldContinueAfterKeyNeeded {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldContinueAfterKeyNeeded; }
    static constexpr bool isSync = false;

    explicit SetShouldContinueAfterKeyNeeded(bool should)
        : m_arguments(should)
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

class BeginSimulatedHDCPError {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_BeginSimulatedHDCPError; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class EndSimulatedHDCPError {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_EndSimulatedHDCPError; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class NotifyActiveSourceBuffersChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_NotifyActiveSourceBuffersChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ApplicationWillResignActive {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_ApplicationWillResignActive; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ApplicationDidBecomeActive {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_ApplicationDidBecomeActive; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class NotifyTrackModeChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_NotifyTrackModeChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class TracksChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_TracksChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AudioTrackSetEnabled {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_AudioTrackSetEnabled; }
    static constexpr bool isSync = false;

    AudioTrackSetEnabled(const WebKit::TrackPrivateRemoteIdentifier& identifier, bool enabled)
        : m_arguments(identifier, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, bool> m_arguments;
};

class VideoTrackSetSelected {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_VideoTrackSetSelected; }
    static constexpr bool isSync = false;

    VideoTrackSetSelected(const WebKit::TrackPrivateRemoteIdentifier& identifier, bool selected)
        : m_arguments(identifier, selected)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, bool> m_arguments;
};

class TextTrackSetMode {
public:
    using Arguments = std::tuple<WebKit::TrackPrivateRemoteIdentifier, WebCore::InbandTextTrackPrivate::Mode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_TextTrackSetMode; }
    static constexpr bool isSync = false;

    TextTrackSetMode(const WebKit::TrackPrivateRemoteIdentifier& identifier, WebCore::InbandTextTrackPrivate::Mode mode)
        : m_arguments(identifier, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TrackPrivateRemoteIdentifier&, WebCore::InbandTextTrackPrivate::Mode> m_arguments;
};

class PerformTaskAtMediaTime {
public:
    using Arguments = std::tuple<MediaTime, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PerformTaskAtMediaTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaPlayerProxy_PerformTaskAtMediaTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<MediaTime>, std::optional<MonotonicTime>>;
    PerformTaskAtMediaTime(const MediaTime& mediaTime, const MonotonicTime& messageTime)
        : m_arguments(mediaTime, messageTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&, const MonotonicTime&> m_arguments;
};

class IsCrossOrigin {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_IsCrossOrigin; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<bool>>;
    explicit IsCrossOrigin(const WebCore::SecurityOriginData& origin)
        : m_arguments(origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&> m_arguments;
};

class SetVideoPlaybackMetricsUpdateInterval {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetVideoPlaybackMetricsUpdateInterval; }
    static constexpr bool isSync = false;

    explicit SetVideoPlaybackMetricsUpdateInterval(double interval)
        : m_arguments(interval)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class SetPreferredDynamicRangeMode {
public:
    using Arguments = std::tuple<WebCore::DynamicRangeMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetPreferredDynamicRangeMode; }
    static constexpr bool isSync = false;

    explicit SetPreferredDynamicRangeMode(WebCore::DynamicRangeMode mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::DynamicRangeMode> m_arguments;
};

#if PLATFORM(IOS_FAMILY)
class ErrorLog {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_ErrorLog; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class AccessLog {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_AccessLog; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(WEB_AUDIO)
class CreateAudioSourceProvider {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_CreateAudioSourceProvider; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(WEB_AUDIO)
class SetShouldEnableAudioSourceProvider {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldEnableAudioSourceProvider; }
    static constexpr bool isSync = false;

    explicit SetShouldEnableAudioSourceProvider(bool shouldEnable)
        : m_arguments(shouldEnable)
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

#if PLATFORM(COCOA)
class NativeImageForCurrentTime {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_NativeImageForCurrentTime; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<MachSendRight>, WebCore::DestinationColorSpace>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ColorSpace {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_ColorSpace; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DestinationColorSpace>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && !HAVE(AVSAMPLEBUFFERDISPLAYLAYER_COPYDISPLAYEDPIXELBUFFER))
class WillBeAskedToPaintGL {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_WillBeAskedToPaintGL; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class VideoFrameForCurrentTimeIfChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_VideoFrameForCurrentTimeIfChanged; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::RemoteVideoFrameProxy::Properties>, bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PlayAtHostTime {
public:
    using Arguments = std::tuple<MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PlayAtHostTime; }
    static constexpr bool isSync = false;

    explicit PlayAtHostTime(const MonotonicTime& time)
        : m_arguments(time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MonotonicTime&> m_arguments;
};

class PauseAtHostTime {
public:
    using Arguments = std::tuple<MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PauseAtHostTime; }
    static constexpr bool isSync = false;

    explicit PauseAtHostTime(const MonotonicTime& time)
        : m_arguments(time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MonotonicTime&> m_arguments;
};

class StartVideoFrameMetadataGathering {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_StartVideoFrameMetadataGathering; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class StopVideoFrameMetadataGathering {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_StopVideoFrameMetadataGathering; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PlayerContentBoxRectChanged {
public:
    using Arguments = std::tuple<WebCore::LayoutRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_PlayerContentBoxRectChanged; }
    static constexpr bool isSync = false;

    explicit PlayerContentBoxRectChanged(const WebCore::LayoutRect& contentRect)
        : m_arguments(contentRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LayoutRect&> m_arguments;
};

class SetShouldDisableHDR {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_SetShouldDisableHDR; }
    static constexpr bool isSync = false;

    explicit SetShouldDisableHDR(bool shouldDisable)
        : m_arguments(shouldDisable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class RequestHostingContextID {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerProxy_RequestHostingContextID; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaPlayerProxy_RequestHostingContextIDReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace RemoteMediaPlayerProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
