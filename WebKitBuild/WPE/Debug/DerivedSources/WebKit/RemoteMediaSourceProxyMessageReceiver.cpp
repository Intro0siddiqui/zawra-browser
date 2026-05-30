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
#include "RemoteMediaSourceProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteMediaSourceProxyMessages.h" // NOLINT
#include "RemoteSourceBufferIdentifier.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/ContentType.h> // NOLINT
#include <WebCore/MediaPlayerEnums.h> // NOLINT
#include <WebCore/MediaSourcePrivate.h> // NOLINT
#include <WebCore/PlatformTimeRanges.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/MediaTime.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteMediaSourceProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::DurationChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::DurationChanged>(connection, decoder, this, &RemoteMediaSourceProxy::durationChanged);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::BufferedChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::BufferedChanged>(connection, decoder, this, &RemoteMediaSourceProxy::bufferedChanged);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::SetReadyState::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::SetReadyState>(connection, decoder, this, &RemoteMediaSourceProxy::setReadyState);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::SetIsSeeking::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::SetIsSeeking>(connection, decoder, this, &RemoteMediaSourceProxy::setIsSeeking);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::WaitForSeekCompleted::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::WaitForSeekCompleted>(connection, decoder, this, &RemoteMediaSourceProxy::waitForSeekCompleted);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::SeekCompleted::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::SeekCompleted>(connection, decoder, this, &RemoteMediaSourceProxy::seekCompleted);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::SetTimeFudgeFactor::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::SetTimeFudgeFactor>(connection, decoder, this, &RemoteMediaSourceProxy::setTimeFudgeFactor);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::MarkEndOfStream::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::MarkEndOfStream>(connection, decoder, this, &RemoteMediaSourceProxy::markEndOfStream);
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::UnmarkEndOfStream::name())
        return IPC::handleMessage<Messages::RemoteMediaSourceProxy::UnmarkEndOfStream>(connection, decoder, this, &RemoteMediaSourceProxy::unmarkEndOfStream);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool RemoteMediaSourceProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::RemoteMediaSourceProxy::AddSourceBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteMediaSourceProxy::AddSourceBuffer>(connection, decoder, replyEncoder, this, &RemoteMediaSourceProxy::addSourceBuffer);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_AddSourceBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::AddSourceBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaSourceProxy_AddSourceBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::AddSourceBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_DurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::DurationChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_BufferedChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::BufferedChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_SetReadyState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::SetReadyState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_SetIsSeeking>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::SetIsSeeking::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_WaitForSeekCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::WaitForSeekCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_SeekCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::SeekCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_SetTimeFudgeFactor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::SetTimeFudgeFactor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_MarkEndOfStream>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::MarkEndOfStream::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaSourceProxy_UnmarkEndOfStream>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaSourceProxy::UnmarkEndOfStream::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
