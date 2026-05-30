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
#include "DownloadProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "DownloadID.h" // NOLINT
#include "DownloadProxyMessages.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IdentifierTypes.h" // NOLINT
#include "SandboxExtension.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/AuthenticationChallenge.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void DownloadProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::DownloadProxy::DidStart::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidStart>(connection, decoder, this, &DownloadProxy::didStart);
    if (decoder.messageName() == Messages::DownloadProxy::DidReceiveAuthenticationChallenge::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidReceiveAuthenticationChallenge>(connection, decoder, this, &DownloadProxy::didReceiveAuthenticationChallenge);
    if (decoder.messageName() == Messages::DownloadProxy::WillSendRequest::name())
        return IPC::handleMessageAsync<Messages::DownloadProxy::WillSendRequest>(connection, decoder, this, &DownloadProxy::willSendRequest);
    if (decoder.messageName() == Messages::DownloadProxy::DecideDestinationWithSuggestedFilename::name())
        return IPC::handleMessageAsync<Messages::DownloadProxy::DecideDestinationWithSuggestedFilename>(connection, decoder, this, &DownloadProxy::decideDestinationWithSuggestedFilename);
    if (decoder.messageName() == Messages::DownloadProxy::DidReceiveData::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidReceiveData>(connection, decoder, this, &DownloadProxy::didReceiveData);
    if (decoder.messageName() == Messages::DownloadProxy::DidCreateDestination::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidCreateDestination>(connection, decoder, this, &DownloadProxy::didCreateDestination);
    if (decoder.messageName() == Messages::DownloadProxy::DidFinish::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidFinish>(connection, decoder, this, &DownloadProxy::didFinish);
    if (decoder.messageName() == Messages::DownloadProxy::DidFail::name())
        return IPC::handleMessage<Messages::DownloadProxy::DidFail>(connection, decoder, this, &DownloadProxy::didFail);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidStart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidStart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidReceiveAuthenticationChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidReceiveAuthenticationChallenge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_WillSendRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::WillSendRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::DownloadProxy_WillSendRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::WillSendRequest::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DecideDestinationWithSuggestedFilename>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DecideDestinationWithSuggestedFilename::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::DownloadProxy_DecideDestinationWithSuggestedFilename>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DecideDestinationWithSuggestedFilename::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidReceiveData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidReceiveData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidCreateDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidCreateDestination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidFinish>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidFinish::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DownloadProxy_DidFail>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DownloadProxy::DidFail::Arguments>(globalObject, decoder);
}

}

#endif

