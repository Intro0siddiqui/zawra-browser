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
#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
#include "RemoteSourceBufferProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteSourceBufferProxyMessages.h" // NOLINT
#include "SharedBufferReference.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "TrackPrivateRemoteIdentifier.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/ContentType.h> // NOLINT
#include <WebCore/MediaPlayer.h> // NOLINT
#include <WebCore/PlatformTimeRanges.h> // NOLINT
#include <WebCore/SourceBufferPrivate.h> // NOLINT
#include <optional> // NOLINT
#include <utility> // NOLINT
#include <wtf/MediaTime.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteSourceBufferProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetActive::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetActive>(connection, decoder, this, &RemoteSourceBufferProxy::setActive);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetMode::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetMode>(connection, decoder, this, &RemoteSourceBufferProxy::setMode);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::Append::name())
        return IPC::handleMessageAsync<Messages::RemoteSourceBufferProxy::Append>(connection, decoder, this, &RemoteSourceBufferProxy::append);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::Abort::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::Abort>(connection, decoder, this, &RemoteSourceBufferProxy::abort);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ResetParserState::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ResetParserState>(connection, decoder, this, &RemoteSourceBufferProxy::resetParserState);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::RemovedFromMediaSource::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::RemovedFromMediaSource>(connection, decoder, this, &RemoteSourceBufferProxy::removedFromMediaSource);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetMediaSourceEnded::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetMediaSourceEnded>(connection, decoder, this, &RemoteSourceBufferProxy::setMediaSourceEnded);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetReadyState::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetReadyState>(connection, decoder, this, &RemoteSourceBufferProxy::setReadyState);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::StartChangingType::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::StartChangingType>(connection, decoder, this, &RemoteSourceBufferProxy::startChangingType);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ClientReadyStateChanged::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ClientReadyStateChanged>(connection, decoder, this, &RemoteSourceBufferProxy::clientReadyStateChanged);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::AddTrackBuffer::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::AddTrackBuffer>(connection, decoder, this, &RemoteSourceBufferProxy::addTrackBuffer);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ResetTrackBuffers::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ResetTrackBuffers>(connection, decoder, this, &RemoteSourceBufferProxy::resetTrackBuffers);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ClearTrackBuffers::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ClearTrackBuffers>(connection, decoder, this, &RemoteSourceBufferProxy::clearTrackBuffers);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetAllTrackBuffersNeedRandomAccess::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetAllTrackBuffersNeedRandomAccess>(connection, decoder, this, &RemoteSourceBufferProxy::setAllTrackBuffersNeedRandomAccess);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::RemoveCodedFrames::name())
        return IPC::handleMessageAsync<Messages::RemoteSourceBufferProxy::RemoveCodedFrames>(connection, decoder, this, &RemoteSourceBufferProxy::removeCodedFrames);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ReenqueueMediaIfNeeded::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ReenqueueMediaIfNeeded>(connection, decoder, this, &RemoteSourceBufferProxy::reenqueueMediaIfNeeded);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetGroupStartTimestamp::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetGroupStartTimestamp>(connection, decoder, this, &RemoteSourceBufferProxy::setGroupStartTimestamp);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetGroupStartTimestampToEndTimestamp::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetGroupStartTimestampToEndTimestamp>(connection, decoder, this, &RemoteSourceBufferProxy::setGroupStartTimestampToEndTimestamp);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetShouldGenerateTimestamps::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetShouldGenerateTimestamps>(connection, decoder, this, &RemoteSourceBufferProxy::setShouldGenerateTimestamps);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::ResetTimestampOffsetInTrackBuffers::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::ResetTimestampOffsetInTrackBuffers>(connection, decoder, this, &RemoteSourceBufferProxy::resetTimestampOffsetInTrackBuffers);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetTimestampOffset::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetTimestampOffset>(connection, decoder, this, &RemoteSourceBufferProxy::setTimestampOffset);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetAppendWindowStart::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetAppendWindowStart>(connection, decoder, this, &RemoteSourceBufferProxy::setAppendWindowStart);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetAppendWindowEnd::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetAppendWindowEnd>(connection, decoder, this, &RemoteSourceBufferProxy::setAppendWindowEnd);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SeekToTime::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SeekToTime>(connection, decoder, this, &RemoteSourceBufferProxy::seekToTime);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::UpdateTrackIds::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::UpdateTrackIds>(connection, decoder, this, &RemoteSourceBufferProxy::updateTrackIds);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::BufferedSamplesForTrackId::name())
        return IPC::handleMessageAsync<Messages::RemoteSourceBufferProxy::BufferedSamplesForTrackId>(connection, decoder, this, &RemoteSourceBufferProxy::bufferedSamplesForTrackId);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::EnqueuedSamplesForTrackID::name())
        return IPC::handleMessageAsync<Messages::RemoteSourceBufferProxy::EnqueuedSamplesForTrackID>(connection, decoder, this, &RemoteSourceBufferProxy::enqueuedSamplesForTrackID);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::MemoryPressure::name())
        return IPC::handleMessageAsync<Messages::RemoteSourceBufferProxy::MemoryPressure>(connection, decoder, this, &RemoteSourceBufferProxy::memoryPressure);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::SetMaximumQueueDepthForTrackID::name())
        return IPC::handleMessage<Messages::RemoteSourceBufferProxy::SetMaximumQueueDepthForTrackID>(connection, decoder, this, &RemoteSourceBufferProxy::setMaximumQueueDepthForTrackID);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool RemoteSourceBufferProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::CanSwitchToType::name())
        return IPC::handleMessageSynchronous<Messages::RemoteSourceBufferProxy::CanSwitchToType>(connection, decoder, replyEncoder, this, &RemoteSourceBufferProxy::canSwitchToType);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::EvictCodedFrames::name())
        return IPC::handleMessageSynchronous<Messages::RemoteSourceBufferProxy::EvictCodedFrames>(connection, decoder, replyEncoder, this, &RemoteSourceBufferProxy::evictCodedFrames);
    if (decoder.messageName() == Messages::RemoteSourceBufferProxy::MinimumUpcomingPresentationTimeForTrackID::name())
        return IPC::handleMessageSynchronous<Messages::RemoteSourceBufferProxy::MinimumUpcomingPresentationTimeForTrackID>(connection, decoder, replyEncoder, this, &RemoteSourceBufferProxy::minimumUpcomingPresentationTimeForTrackID);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(replyEncoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return false;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled synchronous message %s to %" PRIu64, description(decoder.messageName()), decoder.destinationID());
    return false;
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetActive>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetActive::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_CanSwitchToType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::CanSwitchToType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_CanSwitchToType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::CanSwitchToType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_Append>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::Append::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_Append>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::Append::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_Abort>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::Abort::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ResetParserState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ResetParserState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_RemovedFromMediaSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::RemovedFromMediaSource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetMediaSourceEnded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetMediaSourceEnded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetReadyState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetReadyState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_StartChangingType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::StartChangingType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ClientReadyStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ClientReadyStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_AddTrackBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::AddTrackBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ResetTrackBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ResetTrackBuffers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ClearTrackBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ClearTrackBuffers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetAllTrackBuffersNeedRandomAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetAllTrackBuffersNeedRandomAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_RemoveCodedFrames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::RemoveCodedFrames::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_RemoveCodedFrames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::RemoveCodedFrames::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_EvictCodedFrames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::EvictCodedFrames::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_EvictCodedFrames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::EvictCodedFrames::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ReenqueueMediaIfNeeded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ReenqueueMediaIfNeeded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetGroupStartTimestamp>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetGroupStartTimestamp::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetGroupStartTimestampToEndTimestamp>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetGroupStartTimestampToEndTimestamp::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetShouldGenerateTimestamps>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetShouldGenerateTimestamps::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_ResetTimestampOffsetInTrackBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::ResetTimestampOffsetInTrackBuffers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetTimestampOffset>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetTimestampOffset::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetAppendWindowStart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetAppendWindowStart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetAppendWindowEnd>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetAppendWindowEnd::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SeekToTime>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SeekToTime::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_UpdateTrackIds>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::UpdateTrackIds::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_BufferedSamplesForTrackId>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::BufferedSamplesForTrackId::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_BufferedSamplesForTrackId>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::BufferedSamplesForTrackId::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_EnqueuedSamplesForTrackID>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::EnqueuedSamplesForTrackID::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_EnqueuedSamplesForTrackID>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::EnqueuedSamplesForTrackID::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_MemoryPressure>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::MemoryPressure::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_MemoryPressure>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::MemoryPressure::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_SetMaximumQueueDepthForTrackID>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::SetMaximumQueueDepthForTrackID::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSourceBufferProxy_MinimumUpcomingPresentationTimeForTrackID>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::MinimumUpcomingPresentationTimeForTrackID::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteSourceBufferProxy_MinimumUpcomingPresentationTimeForTrackID>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSourceBufferProxy::MinimumUpcomingPresentationTimeForTrackID::ReplyArguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
