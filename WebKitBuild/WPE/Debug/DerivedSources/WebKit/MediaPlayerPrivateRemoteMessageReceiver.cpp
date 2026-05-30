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

#include "config.h"
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "MediaPlayerPrivateRemote.h"

#include "ArgumentCoders.h" // NOLINT
#include "AudioTrackPrivateRemoteConfiguration.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if PLATFORM(COCOA)
#include "LayerHostingContext.h" // NOLINT
#endif
#include "MediaPlayerPrivateRemoteMessages.h" // NOLINT
#include "RemoteMediaPlayerState.h" // NOLINT
#include "RemoteMediaResourceIdentifier.h" // NOLINT
#if PLATFORM(COCOA)
#include "RemoteVideoFrameProxy.h" // NOLINT
#endif
#include "TextTrackPrivateRemoteConfiguration.h" // NOLINT
#include "TrackPrivateRemoteIdentifier.h" // NOLINT
#include "VideoTrackPrivateRemoteConfiguration.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#if PLATFORM(IOS_FAMILY)
#include <WebCore/Cookie.h> // NOLINT
#endif
#include <WebCore/FloatSize.h> // NOLINT
#include <WebCore/ISOVTTCue.h> // NOLINT
#include <WebCore/InbandGenericCue.h> // NOLINT
#if PLATFORM(COCOA)
#include <WebCore/IntSize.h> // NOLINT
#endif
#include <WebCore/PlatformMediaResourceLoader.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#if ENABLE(DATACUE_VALUE)
#include <WebCore/SerializedPlatformDataCueValue.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/VideoFrameMetadata.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <optional> // NOLINT
#endif
#include <wtf/Expected.h> // NOLINT
#include <wtf/MediaTime.h> // NOLINT
#include <wtf/MonotonicTime.h> // NOLINT
#include <wtf/Seconds.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#if PLATFORM(IOS_FAMILY)
#include <wtf/Vector.h> // NOLINT
#endif
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void MediaPlayerPrivateRemote::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::NetworkStateChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::NetworkStateChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::networkStateChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ReadyStateChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ReadyStateChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::readyStateChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::FirstVideoFrameAvailable::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::FirstVideoFrameAvailable>(connection, decoder, this, &MediaPlayerPrivateRemote::firstVideoFrameAvailable);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::VolumeChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::VolumeChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::volumeChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::MuteChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::MuteChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::muteChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::TimeChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::TimeChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::timeChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::DurationChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::DurationChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::durationChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RateChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RateChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::rateChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::PlaybackStateChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::PlaybackStateChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::playbackStateChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::EngineFailedToLoad::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::EngineFailedToLoad>(connection, decoder, this, &MediaPlayerPrivateRemote::engineFailedToLoad);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::UpdateCachedState::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::UpdateCachedState>(connection, decoder, this, &MediaPlayerPrivateRemote::updateCachedState);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::CharacteristicChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::CharacteristicChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::characteristicChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::SizeChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::SizeChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::sizeChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RenderingModeChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RenderingModeChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::renderingModeChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::CurrentTimeChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::CurrentTimeChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::currentTimeChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddRemoteAudioTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddRemoteAudioTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::addRemoteAudioTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveRemoteAudioTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveRemoteAudioTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::removeRemoteAudioTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoteAudioTrackConfigurationChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoteAudioTrackConfigurationChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::remoteAudioTrackConfigurationChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddRemoteVideoTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddRemoteVideoTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::addRemoteVideoTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveRemoteVideoTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveRemoteVideoTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::removeRemoteVideoTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoteVideoTrackConfigurationChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoteVideoTrackConfigurationChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::remoteVideoTrackConfigurationChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddRemoteTextTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddRemoteTextTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::addRemoteTextTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveRemoteTextTrack::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveRemoteTextTrack>(connection, decoder, this, &MediaPlayerPrivateRemote::removeRemoteTextTrack);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoteTextTrackConfigurationChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoteTextTrackConfigurationChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::remoteTextTrackConfigurationChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ParseWebVTTFileHeader::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ParseWebVTTFileHeader>(connection, decoder, this, &MediaPlayerPrivateRemote::parseWebVTTFileHeader);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ParseWebVTTCueData::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ParseWebVTTCueData>(connection, decoder, this, &MediaPlayerPrivateRemote::parseWebVTTCueData);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ParseWebVTTCueDataStruct::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ParseWebVTTCueDataStruct>(connection, decoder, this, &MediaPlayerPrivateRemote::parseWebVTTCueDataStruct);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddDataCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddDataCue>(connection, decoder, this, &MediaPlayerPrivateRemote::addDataCue);
#if ENABLE(DATACUE_VALUE)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddDataCueWithType::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddDataCueWithType>(connection, decoder, this, &MediaPlayerPrivateRemote::addDataCueWithType);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::UpdateDataCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::UpdateDataCue>(connection, decoder, this, &MediaPlayerPrivateRemote::updateDataCue);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveDataCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveDataCue>(connection, decoder, this, &MediaPlayerPrivateRemote::removeDataCue);
#endif
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::AddGenericCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::AddGenericCue>(connection, decoder, this, &MediaPlayerPrivateRemote::addGenericCue);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::UpdateGenericCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::UpdateGenericCue>(connection, decoder, this, &MediaPlayerPrivateRemote::updateGenericCue);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveGenericCue::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveGenericCue>(connection, decoder, this, &MediaPlayerPrivateRemote::removeGenericCue);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RequestResource::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RequestResource>(connection, decoder, this, &MediaPlayerPrivateRemote::requestResource);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::RemoveResource::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::RemoveResource>(connection, decoder, this, &MediaPlayerPrivateRemote::removeResource);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::SendH2Ping::name())
        return IPC::handleMessageAsync<Messages::MediaPlayerPrivateRemote::SendH2Ping>(connection, decoder, this, &MediaPlayerPrivateRemote::sendH2Ping);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ResourceNotSupported::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ResourceNotSupported>(connection, decoder, this, &MediaPlayerPrivateRemote::resourceNotSupported);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::ActiveSourceBuffersChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::ActiveSourceBuffersChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::activeSourceBuffersChanged);
#if ENABLE(ENCRYPTED_MEDIA)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::WaitingForKeyChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::WaitingForKeyChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::waitingForKeyChanged);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::InitializationDataEncountered::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::InitializationDataEncountered>(connection, decoder, this, &MediaPlayerPrivateRemote::initializationDataEncountered);
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::MediaPlayerKeyNeeded::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::MediaPlayerKeyNeeded>(connection, decoder, this, &MediaPlayerPrivateRemote::mediaPlayerKeyNeeded);
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::CurrentPlaybackTargetIsWirelessChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::CurrentPlaybackTargetIsWirelessChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::currentPlaybackTargetIsWirelessChanged);
#endif
#if PLATFORM(IOS_FAMILY)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::GetRawCookies::name())
        return IPC::handleMessageAsync<Messages::MediaPlayerPrivateRemote::GetRawCookies>(connection, decoder, this, &MediaPlayerPrivateRemote::getRawCookies);
#endif
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::PushVideoFrameMetadata::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::PushVideoFrameMetadata>(connection, decoder, this, &MediaPlayerPrivateRemote::pushVideoFrameMetadata);
    if (decoder.messageName() == Messages::MediaPlayerPrivateRemote::LayerHostingContextIdChanged::name())
        return IPC::handleMessage<Messages::MediaPlayerPrivateRemote::LayerHostingContextIdChanged>(connection, decoder, this, &MediaPlayerPrivateRemote::layerHostingContextIdChanged);
#endif
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_NetworkStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::NetworkStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ReadyStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ReadyStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_FirstVideoFrameAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::FirstVideoFrameAvailable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_VolumeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::VolumeChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_MuteChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::MuteChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_TimeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::TimeChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_DurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::DurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_PlaybackStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::PlaybackStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_EngineFailedToLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::EngineFailedToLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_UpdateCachedState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::UpdateCachedState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_CharacteristicChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::CharacteristicChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_SizeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::SizeChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RenderingModeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RenderingModeChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_CurrentTimeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::CurrentTimeChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddRemoteAudioTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddRemoteAudioTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveRemoteAudioTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveRemoteAudioTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoteAudioTrackConfigurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoteAudioTrackConfigurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddRemoteVideoTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddRemoteVideoTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveRemoteVideoTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveRemoteVideoTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoteVideoTrackConfigurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoteVideoTrackConfigurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddRemoteTextTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddRemoteTextTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveRemoteTextTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveRemoteTextTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoteTextTrackConfigurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoteTextTrackConfigurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ParseWebVTTFileHeader>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ParseWebVTTFileHeader::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ParseWebVTTCueData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ParseWebVTTCueData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ParseWebVTTCueDataStruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ParseWebVTTCueDataStruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddDataCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddDataCue::Arguments>(globalObject, decoder);
}
#if ENABLE(DATACUE_VALUE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddDataCueWithType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddDataCueWithType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_UpdateDataCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::UpdateDataCue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveDataCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveDataCue::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_AddGenericCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::AddGenericCue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_UpdateGenericCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::UpdateGenericCue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveGenericCue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveGenericCue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RequestResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RequestResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_RemoveResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::RemoveResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_SendH2Ping>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::SendH2Ping::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::MediaPlayerPrivateRemote_SendH2Ping>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::SendH2Ping::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ResourceNotSupported>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ResourceNotSupported::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_ActiveSourceBuffersChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::ActiveSourceBuffersChanged::Arguments>(globalObject, decoder);
}
#if ENABLE(ENCRYPTED_MEDIA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_WaitingForKeyChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::WaitingForKeyChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_InitializationDataEncountered>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::InitializationDataEncountered::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_MediaPlayerKeyNeeded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::MediaPlayerKeyNeeded::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_CurrentPlaybackTargetIsWirelessChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::CurrentPlaybackTargetIsWirelessChanged::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(IOS_FAMILY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_GetRawCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::GetRawCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::MediaPlayerPrivateRemote_GetRawCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::GetRawCookies::ReplyArguments>(globalObject, decoder);
}
#endif
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_PushVideoFrameMetadata>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::PushVideoFrameMetadata::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::MediaPlayerPrivateRemote_LayerHostingContextIdChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::MediaPlayerPrivateRemote::LayerHostingContextIdChanged::Arguments>(globalObject, decoder);
}
#endif

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
