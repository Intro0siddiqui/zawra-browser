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
#if ENABLE(MEDIA_SESSION_COORDINATOR)
#include "RemoteMediaSessionCoordinatorProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteMediaSessionCoordinatorProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/ExceptionData.h> // NOLINT
#include <WebCore/MediaPositionState.h> // NOLINT
#include <WebCore/MediaSessionPlaybackState.h> // NOLINT
#include <WebCore/MediaSessionReadyState.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteMediaSessionCoordinatorProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::Join::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaSessionCoordinatorProxy::Join>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::join);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::Leave::name())
        return IPC::handleMessage<Messages::RemoteMediaSessionCoordinatorProxy::Leave>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::leave);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSeekTo::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSeekTo>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::coordinateSeekTo);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePlay::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePlay>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::coordinatePlay);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePause::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePause>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::coordinatePause);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSetTrack::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSetTrack>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::coordinateSetTrack);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::PositionStateChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSessionCoordinatorProxy::PositionStateChanged>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::positionStateChanged);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::ReadyStateChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSessionCoordinatorProxy::ReadyStateChanged>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::readyStateChanged);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::PlaybackStateChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSessionCoordinatorProxy::PlaybackStateChanged>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::playbackStateChanged);
    if (decoder.messageName() == Messages::RemoteMediaSessionCoordinatorProxy::TrackIdentifierChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSessionCoordinatorProxy::TrackIdentifierChanged>(connection, decoder, this, &RemoteMediaSessionCoordinatorProxy::trackIdentifierChanged);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_Join>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::Join::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSessionCoordinatorProxy_Join>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::Join::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_Leave>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::Leave::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinateSeekTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSeekTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinateSeekTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSeekTo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinatePlay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePlay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinatePlay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePlay::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinatePause>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePause::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinatePause>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinatePause::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinateSetTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSetTrack::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSessionCoordinatorProxy_CoordinateSetTrack>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::CoordinateSetTrack::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_PositionStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::PositionStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_ReadyStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::ReadyStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_PlaybackStateChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::PlaybackStateChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSessionCoordinatorProxy_TrackIdentifierChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSessionCoordinatorProxy::TrackIdentifierChanged::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(MEDIA_SESSION_COORDINATOR)
