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
#include "SourceBufferPrivateRemote.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "InitializationSegmentInfo.h" // NOLINT
#include "SourceBufferPrivateRemoteMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/PlatformTimeRanges.h> // NOLINT
#include <WebCore/SourceBufferPrivateClient.h> // NOLINT
#include <wtf/MediaTime.h> // NOLINT
#include <wtf/Vector.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void SourceBufferPrivateRemote::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveInitializationSegment::name())
        return IPC::handleMessageAsync<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveInitializationSegment>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateDidReceiveInitializationSegment);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateStreamEndedWithDecodeError::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateStreamEndedWithDecodeError>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateStreamEndedWithDecodeError);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateAppendComplete::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateAppendComplete>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateAppendComplete);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateHighestPresentationTimestampChanged::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateHighestPresentationTimestampChanged>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateHighestPresentationTimestampChanged);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateBufferedChanged::name())
        return IPC::handleMessageAsync<Messages::SourceBufferPrivateRemote::SourceBufferPrivateBufferedChanged>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateBufferedChanged);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateTrackBuffersChanged::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateTrackBuffersChanged>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateTrackBuffersChanged);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateDurationChanged::name())
        return IPC::handleMessageAsync<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDurationChanged>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateDurationChanged);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidParseSample::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidParseSample>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateDidParseSample);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidDropSample::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidDropSample>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateDidDropSample);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveRenderingError::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveRenderingError>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateDidReceiveRenderingError);
    if (decoder.messageName() == Messages::SourceBufferPrivateRemote::SourceBufferPrivateReportExtraMemoryCost::name())
        return IPC::handleMessage<Messages::SourceBufferPrivateRemote::SourceBufferPrivateReportExtraMemoryCost>(connection, decoder, this, &SourceBufferPrivateRemote::sourceBufferPrivateReportExtraMemoryCost);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegment>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveInitializationSegment::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegment>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveInitializationSegment::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateStreamEndedWithDecodeError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateStreamEndedWithDecodeError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateAppendComplete>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateAppendComplete::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateHighestPresentationTimestampChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateHighestPresentationTimestampChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateBufferedChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateBufferedChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateBufferedChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateBufferedChanged::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateTrackBuffersChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateTrackBuffersChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDurationChanged::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidParseSample>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidParseSample::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidDropSample>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidDropSample::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveRenderingError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateDidReceiveRenderingError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SourceBufferPrivateRemote_SourceBufferPrivateReportExtraMemoryCost>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SourceBufferPrivateRemote::SourceBufferPrivateReportExtraMemoryCost::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
