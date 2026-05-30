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
#include "WebSocketChannel.h"

#include "ArgumentCoders.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebSocketChannelMessages.h" // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSocketChannel::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebSocketChannel::DidConnect::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidConnect>(connection, decoder, this, &WebSocketChannel::didConnect);
    if (decoder.messageName() == Messages::WebSocketChannel::DidClose::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidClose>(connection, decoder, this, &WebSocketChannel::didClose);
    if (decoder.messageName() == Messages::WebSocketChannel::DidReceiveText::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidReceiveText>(connection, decoder, this, &WebSocketChannel::didReceiveText);
    if (decoder.messageName() == Messages::WebSocketChannel::DidReceiveBinaryData::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidReceiveBinaryData>(connection, decoder, this, &WebSocketChannel::didReceiveBinaryData);
    if (decoder.messageName() == Messages::WebSocketChannel::DidReceiveMessageError::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidReceiveMessageError>(connection, decoder, this, &WebSocketChannel::didReceiveMessageError);
    if (decoder.messageName() == Messages::WebSocketChannel::DidSendHandshakeRequest::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidSendHandshakeRequest>(connection, decoder, this, &WebSocketChannel::didSendHandshakeRequest);
    if (decoder.messageName() == Messages::WebSocketChannel::DidReceiveHandshakeResponse::name())
        return IPC::handleMessage<Messages::WebSocketChannel::DidReceiveHandshakeResponse>(connection, decoder, this, &WebSocketChannel::didReceiveHandshakeResponse);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidConnect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidConnect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidClose>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidClose::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidReceiveText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidReceiveText::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidReceiveBinaryData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidReceiveBinaryData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidReceiveMessageError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidReceiveMessageError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidSendHandshakeRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidSendHandshakeRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSocketChannel_DidReceiveHandshakeResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSocketChannel::DidReceiveHandshakeResponse::Arguments>(globalObject, decoder);
}

}

#endif

