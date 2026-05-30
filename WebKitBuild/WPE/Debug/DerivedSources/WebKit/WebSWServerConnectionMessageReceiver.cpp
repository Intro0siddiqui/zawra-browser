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
#include "WebSWServerConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RetrieveRecordResponseBodyCallbackIdentifier.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebSWServerConnectionMessages.h" // NOLINT
#include <WebCore/BackgroundFetchInformation.h> // NOLINT
#include <WebCore/BackgroundFetchOptions.h> // NOLINT
#include <WebCore/BackgroundFetchRecordIdentifier.h> // NOLINT
#include <WebCore/BackgroundFetchRecordInformation.h> // NOLINT
#include <WebCore/BackgroundFetchRequest.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/ExceptionData.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#include <WebCore/NavigationPreloadState.h> // NOLINT
#include <WebCore/ProcessQualified.h> // NOLINT
#include <WebCore/PushSubscriptionData.h> // NOLINT
#include <WebCore/PushSubscriptionIdentifier.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <WebCore/RetrieveRecordsOptions.h> // NOLINT
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#include <WebCore/SecurityOriginData.h> // NOLINT
#include <WebCore/ServiceWorkerClientData.h> // NOLINT
#include <WebCore/ServiceWorkerIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerJobData.h> // NOLINT
#include <WebCore/ServiceWorkerJobDataIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerRegistrationData.h> // NOLINT
#include <WebCore/ServiceWorkerRegistrationKey.h> // NOLINT
#include <WebCore/ServiceWorkerTypes.h> // NOLINT
#include <WebCore/WorkerFetchResult.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Expected.h> // NOLINT
#include <wtf/ObjectIdentifier.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSWServerConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebSWServerConnection::ScheduleJobInServer::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::ScheduleJobInServer>(connection, decoder, this, &WebSWServerConnection::scheduleJobInServer);
    if (decoder.messageName() == Messages::WebSWServerConnection::ScheduleUnregisterJobInServer::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::ScheduleUnregisterJobInServer>(connection, decoder, this, &WebSWServerConnection::scheduleUnregisterJobInServer);
    if (decoder.messageName() == Messages::WebSWServerConnection::FinishFetchingScriptInServer::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::FinishFetchingScriptInServer>(connection, decoder, this, &WebSWServerConnection::finishFetchingScriptInServer);
    if (decoder.messageName() == Messages::WebSWServerConnection::AddServiceWorkerRegistrationInServer::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::AddServiceWorkerRegistrationInServer>(connection, decoder, this, &WebSWServerConnection::addServiceWorkerRegistrationInServer);
    if (decoder.messageName() == Messages::WebSWServerConnection::RemoveServiceWorkerRegistrationInServer::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::RemoveServiceWorkerRegistrationInServer>(connection, decoder, this, &WebSWServerConnection::removeServiceWorkerRegistrationInServer);
    if (decoder.messageName() == Messages::WebSWServerConnection::PostMessageToServiceWorker::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::PostMessageToServiceWorker>(connection, decoder, this, &WebSWServerConnection::postMessageToServiceWorker);
    if (decoder.messageName() == Messages::WebSWServerConnection::DidResolveRegistrationPromise::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::DidResolveRegistrationPromise>(connection, decoder, this, &WebSWServerConnection::didResolveRegistrationPromise);
    if (decoder.messageName() == Messages::WebSWServerConnection::MatchRegistration::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::MatchRegistration>(connection, decoder, this, &WebSWServerConnection::matchRegistration);
    if (decoder.messageName() == Messages::WebSWServerConnection::WhenRegistrationReady::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::WhenRegistrationReady>(connection, decoder, this, &WebSWServerConnection::whenRegistrationReady);
    if (decoder.messageName() == Messages::WebSWServerConnection::GetRegistrations::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::GetRegistrations>(connection, decoder, this, &WebSWServerConnection::getRegistrations);
    if (decoder.messageName() == Messages::WebSWServerConnection::RegisterServiceWorkerClient::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::RegisterServiceWorkerClient>(connection, decoder, this, &WebSWServerConnection::registerServiceWorkerClient);
    if (decoder.messageName() == Messages::WebSWServerConnection::UnregisterServiceWorkerClient::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::UnregisterServiceWorkerClient>(connection, decoder, this, &WebSWServerConnection::unregisterServiceWorkerClient);
    if (decoder.messageName() == Messages::WebSWServerConnection::TerminateWorkerFromClient::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::TerminateWorkerFromClient>(connection, decoder, this, &WebSWServerConnection::terminateWorkerFromClient);
    if (decoder.messageName() == Messages::WebSWServerConnection::WhenServiceWorkerIsTerminatedForTesting::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::WhenServiceWorkerIsTerminatedForTesting>(connection, decoder, this, &WebSWServerConnection::whenServiceWorkerIsTerminatedForTesting);
    if (decoder.messageName() == Messages::WebSWServerConnection::SetThrottleState::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::SetThrottleState>(connection, decoder, this, &WebSWServerConnection::setThrottleState);
    if (decoder.messageName() == Messages::WebSWServerConnection::StoreRegistrationsOnDisk::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::StoreRegistrationsOnDisk>(connection, decoder, this, &WebSWServerConnection::storeRegistrationsOnDisk);
    if (decoder.messageName() == Messages::WebSWServerConnection::SubscribeToPushService::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::SubscribeToPushService>(connection, decoder, this, &WebSWServerConnection::subscribeToPushService);
    if (decoder.messageName() == Messages::WebSWServerConnection::UnsubscribeFromPushService::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::UnsubscribeFromPushService>(connection, decoder, this, &WebSWServerConnection::unsubscribeFromPushService);
    if (decoder.messageName() == Messages::WebSWServerConnection::GetPushSubscription::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::GetPushSubscription>(connection, decoder, this, &WebSWServerConnection::getPushSubscription);
    if (decoder.messageName() == Messages::WebSWServerConnection::GetPushPermissionState::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::GetPushPermissionState>(connection, decoder, this, &WebSWServerConnection::getPushPermissionState);
    if (decoder.messageName() == Messages::WebSWServerConnection::EnableNavigationPreload::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::EnableNavigationPreload>(connection, decoder, this, &WebSWServerConnection::enableNavigationPreload);
    if (decoder.messageName() == Messages::WebSWServerConnection::DisableNavigationPreload::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::DisableNavigationPreload>(connection, decoder, this, &WebSWServerConnection::disableNavigationPreload);
    if (decoder.messageName() == Messages::WebSWServerConnection::SetNavigationPreloadHeaderValue::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::SetNavigationPreloadHeaderValue>(connection, decoder, this, &WebSWServerConnection::setNavigationPreloadHeaderValue);
    if (decoder.messageName() == Messages::WebSWServerConnection::GetNavigationPreloadState::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::GetNavigationPreloadState>(connection, decoder, this, &WebSWServerConnection::getNavigationPreloadState);
    if (decoder.messageName() == Messages::WebSWServerConnection::StartBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::StartBackgroundFetch>(connection, decoder, this, &WebSWServerConnection::startBackgroundFetch);
    if (decoder.messageName() == Messages::WebSWServerConnection::BackgroundFetchInformation::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::BackgroundFetchInformation>(connection, decoder, this, &WebSWServerConnection::backgroundFetchInformation);
    if (decoder.messageName() == Messages::WebSWServerConnection::BackgroundFetchIdentifiers::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::BackgroundFetchIdentifiers>(connection, decoder, this, &WebSWServerConnection::backgroundFetchIdentifiers);
    if (decoder.messageName() == Messages::WebSWServerConnection::AbortBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::AbortBackgroundFetch>(connection, decoder, this, &WebSWServerConnection::abortBackgroundFetch);
    if (decoder.messageName() == Messages::WebSWServerConnection::MatchBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::MatchBackgroundFetch>(connection, decoder, this, &WebSWServerConnection::matchBackgroundFetch);
    if (decoder.messageName() == Messages::WebSWServerConnection::RetrieveRecordResponse::name())
        return IPC::handleMessageAsync<Messages::WebSWServerConnection::RetrieveRecordResponse>(connection, decoder, this, &WebSWServerConnection::retrieveRecordResponse);
    if (decoder.messageName() == Messages::WebSWServerConnection::RetrieveRecordResponseBody::name())
        return IPC::handleMessage<Messages::WebSWServerConnection::RetrieveRecordResponseBody>(connection, decoder, this, &WebSWServerConnection::retrieveRecordResponseBody);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_ScheduleJobInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::ScheduleJobInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_ScheduleUnregisterJobInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::ScheduleUnregisterJobInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_ScheduleUnregisterJobInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::ScheduleUnregisterJobInServer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_FinishFetchingScriptInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::FinishFetchingScriptInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_AddServiceWorkerRegistrationInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::AddServiceWorkerRegistrationInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_RemoveServiceWorkerRegistrationInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::RemoveServiceWorkerRegistrationInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_PostMessageToServiceWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::PostMessageToServiceWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_DidResolveRegistrationPromise>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::DidResolveRegistrationPromise::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_MatchRegistration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::MatchRegistration::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_MatchRegistration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::MatchRegistration::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_WhenRegistrationReady>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::WhenRegistrationReady::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_WhenRegistrationReady>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::WhenRegistrationReady::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_GetRegistrations>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetRegistrations::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_GetRegistrations>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetRegistrations::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_RegisterServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::RegisterServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_UnregisterServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::UnregisterServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_TerminateWorkerFromClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::TerminateWorkerFromClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_TerminateWorkerFromClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::TerminateWorkerFromClient::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_WhenServiceWorkerIsTerminatedForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::WhenServiceWorkerIsTerminatedForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_WhenServiceWorkerIsTerminatedForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::WhenServiceWorkerIsTerminatedForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_SetThrottleState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::SetThrottleState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_StoreRegistrationsOnDisk>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::StoreRegistrationsOnDisk::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_StoreRegistrationsOnDisk>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::StoreRegistrationsOnDisk::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_SubscribeToPushService>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::SubscribeToPushService::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_SubscribeToPushService>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::SubscribeToPushService::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_UnsubscribeFromPushService>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::UnsubscribeFromPushService::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_UnsubscribeFromPushService>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::UnsubscribeFromPushService::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_GetPushSubscription>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetPushSubscription::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_GetPushSubscription>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetPushSubscription::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_GetPushPermissionState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetPushPermissionState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_GetPushPermissionState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetPushPermissionState::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_EnableNavigationPreload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::EnableNavigationPreload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_EnableNavigationPreload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::EnableNavigationPreload::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_DisableNavigationPreload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::DisableNavigationPreload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_DisableNavigationPreload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::DisableNavigationPreload::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_SetNavigationPreloadHeaderValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::SetNavigationPreloadHeaderValue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_SetNavigationPreloadHeaderValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::SetNavigationPreloadHeaderValue::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_GetNavigationPreloadState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetNavigationPreloadState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_GetNavigationPreloadState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::GetNavigationPreloadState::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_StartBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::StartBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_StartBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::StartBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_BackgroundFetchInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::BackgroundFetchInformation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_BackgroundFetchInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::BackgroundFetchInformation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_BackgroundFetchIdentifiers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::BackgroundFetchIdentifiers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_BackgroundFetchIdentifiers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::BackgroundFetchIdentifiers::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_AbortBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::AbortBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_AbortBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::AbortBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_MatchBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::MatchBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_MatchBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::MatchBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_RetrieveRecordResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::RetrieveRecordResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerConnection_RetrieveRecordResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::RetrieveRecordResponse::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerConnection_RetrieveRecordResponseBody>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerConnection::RetrieveRecordResponseBody::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(SERVICE_WORKER)
