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
#if ENABLE(SERVICE_WORKER)
#include "WebSWContextManagerConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "FormDataReference.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPreferencesStore.h" // NOLINT
#include "WebSWContextManagerConnectionMessages.h" // NOLINT
#include <WebCore/BackgroundFetchInformation.h> // NOLINT
#include <WebCore/FetchIdentifier.h> // NOLINT
#include <WebCore/FetchOptions.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#include <WebCore/NotificationData.h> // NOLINT
#include <WebCore/NotificationEventType.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
#include <WebCore/ScriptBuffer.h> // NOLINT
#endif
#include <WebCore/ServiceWorkerClientData.h> // NOLINT
#include <WebCore/ServiceWorkerContextData.h> // NOLINT
#include <WebCore/ServiceWorkerData.h> // NOLINT
#include <WebCore/ServiceWorkerIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerTypes.h> // NOLINT
#include <WebCore/WorkerThreadMode.h> // NOLINT
#include <optional> // NOLINT
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
#include <wtf/HashMap.h> // NOLINT
#endif
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
#include <wtf/URLHash.h> // NOLINT
#endif
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSWContextManagerConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::InstallServiceWorker::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::InstallServiceWorker>(connection, decoder, this, &WebSWContextManagerConnection::installServiceWorker);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::UpdateAppInitiatedValue::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::UpdateAppInitiatedValue>(connection, decoder, this, &WebSWContextManagerConnection::updateAppInitiatedValue);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::StartFetch::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::StartFetch>(connection, decoder, this, &WebSWContextManagerConnection::startFetch);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::CancelFetch::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::CancelFetch>(connection, decoder, this, &WebSWContextManagerConnection::cancelFetch);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::ContinueDidReceiveFetchResponse::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::ContinueDidReceiveFetchResponse>(connection, decoder, this, &WebSWContextManagerConnection::continueDidReceiveFetchResponse);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::PostMessageToServiceWorker::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::PostMessageToServiceWorker>(connection, decoder, this, &WebSWContextManagerConnection::postMessageToServiceWorker);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FireInstallEvent::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::FireInstallEvent>(connection, decoder, this, &WebSWContextManagerConnection::fireInstallEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FireActivateEvent::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::FireActivateEvent>(connection, decoder, this, &WebSWContextManagerConnection::fireActivateEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FirePushEvent::name())
        return IPC::handleMessageAsync<Messages::WebSWContextManagerConnection::FirePushEvent>(connection, decoder, this, &WebSWContextManagerConnection::firePushEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FireNotificationEvent::name())
        return IPC::handleMessageAsync<Messages::WebSWContextManagerConnection::FireNotificationEvent>(connection, decoder, this, &WebSWContextManagerConnection::fireNotificationEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FireBackgroundFetchEvent::name())
        return IPC::handleMessageAsync<Messages::WebSWContextManagerConnection::FireBackgroundFetchEvent>(connection, decoder, this, &WebSWContextManagerConnection::fireBackgroundFetchEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::FireBackgroundFetchClickEvent::name())
        return IPC::handleMessageAsync<Messages::WebSWContextManagerConnection::FireBackgroundFetchClickEvent>(connection, decoder, this, &WebSWContextManagerConnection::fireBackgroundFetchClickEvent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::TerminateWorker::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::TerminateWorker>(connection, decoder, this, &WebSWContextManagerConnection::terminateWorker);
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::DidSaveScriptsToDisk::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::DidSaveScriptsToDisk>(connection, decoder, this, &WebSWContextManagerConnection::didSaveScriptsToDisk);
#endif
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::MatchAllCompleted::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::MatchAllCompleted>(connection, decoder, this, &WebSWContextManagerConnection::matchAllCompleted);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::SkipWaitingCompleted::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::SkipWaitingCompleted>(connection, decoder, this, &WebSWContextManagerConnection::skipWaitingCompleted);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::SetUserAgent::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::SetUserAgent>(connection, decoder, this, &WebSWContextManagerConnection::setUserAgent);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::UpdatePreferencesStore::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::UpdatePreferencesStore>(connection, decoder, this, &WebSWContextManagerConnection::updatePreferencesStore);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::Close::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::Close>(connection, decoder, this, &WebSWContextManagerConnection::close);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::SetThrottleState::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::SetThrottleState>(connection, decoder, this, &WebSWContextManagerConnection::setThrottleState);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::ConvertFetchToDownload::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::ConvertFetchToDownload>(connection, decoder, this, &WebSWContextManagerConnection::convertFetchToDownload);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::NavigationPreloadIsReady::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::NavigationPreloadIsReady>(connection, decoder, this, &WebSWContextManagerConnection::navigationPreloadIsReady);
    if (decoder.messageName() == Messages::WebSWContextManagerConnection::NavigationPreloadFailed::name())
        return IPC::handleMessage<Messages::WebSWContextManagerConnection::NavigationPreloadFailed>(connection, decoder, this, &WebSWContextManagerConnection::navigationPreloadFailed);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_InstallServiceWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::InstallServiceWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_UpdateAppInitiatedValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::UpdateAppInitiatedValue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_StartFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::StartFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_CancelFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::CancelFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_ContinueDidReceiveFetchResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::ContinueDidReceiveFetchResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_PostMessageToServiceWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::PostMessageToServiceWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FireInstallEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireInstallEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FireActivateEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireActivateEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FirePushEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FirePushEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWContextManagerConnection_FirePushEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FirePushEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FireNotificationEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireNotificationEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWContextManagerConnection_FireNotificationEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireNotificationEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FireBackgroundFetchEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireBackgroundFetchEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWContextManagerConnection_FireBackgroundFetchEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireBackgroundFetchEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_FireBackgroundFetchClickEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireBackgroundFetchClickEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWContextManagerConnection_FireBackgroundFetchClickEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::FireBackgroundFetchClickEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_TerminateWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::TerminateWorker::Arguments>(globalObject, decoder);
}
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_DidSaveScriptsToDisk>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::DidSaveScriptsToDisk::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_MatchAllCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::MatchAllCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_SkipWaitingCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::SkipWaitingCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_SetUserAgent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::SetUserAgent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_UpdatePreferencesStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::UpdatePreferencesStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_Close>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::Close::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_SetThrottleState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::SetThrottleState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_ConvertFetchToDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::ConvertFetchToDownload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_NavigationPreloadIsReady>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::NavigationPreloadIsReady::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWContextManagerConnection_NavigationPreloadFailed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWContextManagerConnection::NavigationPreloadFailed::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(SERVICE_WORKER)
