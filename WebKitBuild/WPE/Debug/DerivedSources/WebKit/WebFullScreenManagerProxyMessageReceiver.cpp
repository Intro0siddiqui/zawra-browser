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
#if ENABLE(FULLSCREEN_API)
#include "WebFullScreenManagerProxy.h"

#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebFullScreenManagerProxyMessages.h" // NOLINT
#include <WebCore/FloatSize.h> // NOLINT
#include <WebCore/IntRect.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebFullScreenManagerProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::EnterFullScreen::name())
        return IPC::handleMessage<Messages::WebFullScreenManagerProxy::EnterFullScreen>(connection, decoder, this, &WebFullScreenManagerProxy::enterFullScreen);
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::ExitFullScreen::name())
        return IPC::handleMessage<Messages::WebFullScreenManagerProxy::ExitFullScreen>(connection, decoder, this, &WebFullScreenManagerProxy::exitFullScreen);
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::BeganEnterFullScreen::name())
        return IPC::handleMessage<Messages::WebFullScreenManagerProxy::BeganEnterFullScreen>(connection, decoder, this, &WebFullScreenManagerProxy::beganEnterFullScreen);
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::BeganExitFullScreen::name())
        return IPC::handleMessage<Messages::WebFullScreenManagerProxy::BeganExitFullScreen>(connection, decoder, this, &WebFullScreenManagerProxy::beganExitFullScreen);
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::Close::name())
        return IPC::handleMessage<Messages::WebFullScreenManagerProxy::Close>(connection, decoder, this, &WebFullScreenManagerProxy::close);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool WebFullScreenManagerProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::WebFullScreenManagerProxy::SupportsFullScreen::name())
        return IPC::handleMessageSynchronous<Messages::WebFullScreenManagerProxy::SupportsFullScreen>(connection, decoder, replyEncoder, this, &WebFullScreenManagerProxy::supportsFullScreen);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_SupportsFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::SupportsFullScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebFullScreenManagerProxy_SupportsFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::SupportsFullScreen::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_EnterFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::EnterFullScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_ExitFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::ExitFullScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_BeganEnterFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::BeganEnterFullScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_BeganExitFullScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::BeganExitFullScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebFullScreenManagerProxy_Close>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebFullScreenManagerProxy::Close::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(FULLSCREEN_API)
