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
#include "RemoteMediaPlayerManagerProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteMediaPlayerManagerProxyMessages.h" // NOLINT
#include "RemoteMediaPlayerProxyConfiguration.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/MediaPlayer.h> // NOLINT
#include <WebCore/MediaPlayerEnums.h> // NOLINT
#include <WebCore/MediaPlayerIdentifier.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteMediaPlayerManagerProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteMediaPlayerManagerProxy::CreateMediaPlayer::name())
        return IPC::handleMessage<Messages::RemoteMediaPlayerManagerProxy::CreateMediaPlayer>(connection, decoder, this, &RemoteMediaPlayerManagerProxy::createMediaPlayer);
    if (decoder.messageName() == Messages::RemoteMediaPlayerManagerProxy::DeleteMediaPlayer::name())
        return IPC::handleMessage<Messages::RemoteMediaPlayerManagerProxy::DeleteMediaPlayer>(connection, decoder, this, &RemoteMediaPlayerManagerProxy::deleteMediaPlayer);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool RemoteMediaPlayerManagerProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::RemoteMediaPlayerManagerProxy::GetSupportedTypes::name())
        return IPC::handleMessageSynchronous<Messages::RemoteMediaPlayerManagerProxy::GetSupportedTypes>(connection, decoder, replyEncoder, this, &RemoteMediaPlayerManagerProxy::getSupportedTypes);
    if (decoder.messageName() == Messages::RemoteMediaPlayerManagerProxy::SupportsTypeAndCodecs::name())
        return IPC::handleMessageSynchronous<Messages::RemoteMediaPlayerManagerProxy::SupportsTypeAndCodecs>(connection, decoder, replyEncoder, this, &RemoteMediaPlayerManagerProxy::supportsTypeAndCodecs);
    if (decoder.messageName() == Messages::RemoteMediaPlayerManagerProxy::SupportsKeySystem::name())
        return IPC::handleMessageSynchronous<Messages::RemoteMediaPlayerManagerProxy::SupportsKeySystem>(connection, decoder, replyEncoder, this, &RemoteMediaPlayerManagerProxy::supportsKeySystem);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaPlayerManagerProxy_CreateMediaPlayer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::CreateMediaPlayer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaPlayerManagerProxy_DeleteMediaPlayer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::DeleteMediaPlayer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaPlayerManagerProxy_GetSupportedTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::GetSupportedTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaPlayerManagerProxy_GetSupportedTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::GetSupportedTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaPlayerManagerProxy_SupportsTypeAndCodecs>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::SupportsTypeAndCodecs::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaPlayerManagerProxy_SupportsTypeAndCodecs>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::SupportsTypeAndCodecs::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaPlayerManagerProxy_SupportsKeySystem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::SupportsKeySystem::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaPlayerManagerProxy_SupportsKeySystem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaPlayerManagerProxy::SupportsKeySystem::ReplyArguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
