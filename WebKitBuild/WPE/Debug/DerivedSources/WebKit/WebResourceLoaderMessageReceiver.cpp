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
#include "WebResourceLoader.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "FormDataReference.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "PrivateRelayed.h" // NOLINT
#if ENABLE(SHAREABLE_RESOURCE)
#include "ShareableResource.h" // NOLINT
#endif
#include "SharedBufferReference.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebResourceLoaderMessages.h" // NOLINT
#if ENABLE(CONTENT_FILTERING)
#include <WebCore/ContentFilterUnblockHandler.h> // NOLINT
#endif
#include <WebCore/NetworkLoadMetrics.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#if ENABLE(CONTENT_FILTERING)
#include <WebCore/SubstituteData.h> // NOLINT
#endif
#include <optional> // NOLINT
#include <wtf/MonotonicTime.h> // NOLINT
#if ENABLE(CONTENT_FILTERING)
#include <wtf/URLHash.h> // NOLINT
#endif
#if ENABLE(CONTENT_FILTERING)
#include <wtf/text/WTFString.h> // NOLINT
#endif

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebResourceLoader::didReceiveWebResourceLoaderMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebResourceLoader::WillSendRequest::name())
        return IPC::handleMessageAsync<Messages::WebResourceLoader::WillSendRequest>(connection, decoder, this, &WebResourceLoader::willSendRequest);
    if (decoder.messageName() == Messages::WebResourceLoader::SetWorkerStart::name())
        return IPC::handleMessage<Messages::WebResourceLoader::SetWorkerStart>(connection, decoder, this, &WebResourceLoader::setWorkerStart);
    if (decoder.messageName() == Messages::WebResourceLoader::DidSendData::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidSendData>(connection, decoder, this, &WebResourceLoader::didSendData);
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveResponse::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidReceiveResponse>(connection, decoder, this, &WebResourceLoader::didReceiveResponse);
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveData::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidReceiveData>(connection, decoder, this, &WebResourceLoader::didReceiveData);
    if (decoder.messageName() == Messages::WebResourceLoader::DidFinishResourceLoad::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidFinishResourceLoad>(connection, decoder, this, &WebResourceLoader::didFinishResourceLoad);
    if (decoder.messageName() == Messages::WebResourceLoader::DidFailResourceLoad::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidFailResourceLoad>(connection, decoder, this, &WebResourceLoader::didFailResourceLoad);
    if (decoder.messageName() == Messages::WebResourceLoader::DidFailServiceWorkerLoad::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidFailServiceWorkerLoad>(connection, decoder, this, &WebResourceLoader::didFailServiceWorkerLoad);
    if (decoder.messageName() == Messages::WebResourceLoader::ServiceWorkerDidNotHandle::name())
        return IPC::handleMessage<Messages::WebResourceLoader::ServiceWorkerDidNotHandle>(connection, decoder, this, &WebResourceLoader::serviceWorkerDidNotHandle);
    if (decoder.messageName() == Messages::WebResourceLoader::DidBlockAuthenticationChallenge::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidBlockAuthenticationChallenge>(connection, decoder, this, &WebResourceLoader::didBlockAuthenticationChallenge);
    if (decoder.messageName() == Messages::WebResourceLoader::StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied::name())
        return IPC::handleMessage<Messages::WebResourceLoader::StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied>(connection, decoder, this, &WebResourceLoader::stopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied);
#if ENABLE(SHAREABLE_RESOURCE)
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveResource::name())
        return IPC::handleMessage<Messages::WebResourceLoader::DidReceiveResource>(connection, decoder, this, &WebResourceLoader::didReceiveResource);
#endif
#if ENABLE(CONTENT_FILTERING)
    if (decoder.messageName() == Messages::WebResourceLoader::ContentFilterDidBlockLoad::name())
        return IPC::handleMessage<Messages::WebResourceLoader::ContentFilterDidBlockLoad>(connection, decoder, this, &WebResourceLoader::contentFilterDidBlockLoad);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_WillSendRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::WillSendRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebResourceLoader_WillSendRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::WillSendRequest::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_SetWorkerStart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::SetWorkerStart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidSendData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidSendData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidReceiveResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidReceiveResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidReceiveData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidReceiveData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidFinishResourceLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidFinishResourceLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidFailResourceLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidFailResourceLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidFailServiceWorkerLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidFailServiceWorkerLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_ServiceWorkerDidNotHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::ServiceWorkerDidNotHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidBlockAuthenticationChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidBlockAuthenticationChallenge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied::Arguments>(globalObject, decoder);
}
#if ENABLE(SHAREABLE_RESOURCE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_DidReceiveResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::DidReceiveResource::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(CONTENT_FILTERING)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebResourceLoader_ContentFilterDidBlockLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebResourceLoader::ContentFilterDidBlockLoad::Arguments>(globalObject, decoder);
}
#endif

}

#endif

