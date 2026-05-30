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
#include "WebSWClientConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RetrieveRecordResponseBodyCallbackIdentifier.h" // NOLINT
#include "SharedBufferReference.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebSWClientConnectionMessages.h" // NOLINT
#include <WebCore/BackgroundFetchInformation.h> // NOLINT
#include <WebCore/ExceptionData.h> // NOLINT
#include <WebCore/FetchOptions.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#include <WebCore/ProcessQualified.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerClientData.h> // NOLINT
#include <WebCore/ServiceWorkerData.h> // NOLINT
#include <WebCore/ServiceWorkerIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerRegistrationData.h> // NOLINT
#include <WebCore/ServiceWorkerRegistrationKey.h> // NOLINT
#include <WebCore/ServiceWorkerTypes.h> // NOLINT
#include <WebCore/ServiceWorkerUpdateViaCache.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/HashSet.h> // NOLINT
#include <wtf/ObjectIdentifier.h> // NOLINT
#include <wtf/WallTime.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSWClientConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebSWClientConnection::JobRejectedInServer::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::JobRejectedInServer>(connection, decoder, this, &WebSWClientConnection::jobRejectedInServer);
    if (decoder.messageName() == Messages::WebSWClientConnection::RegistrationJobResolvedInServer::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::RegistrationJobResolvedInServer>(connection, decoder, this, &WebSWClientConnection::registrationJobResolvedInServer);
    if (decoder.messageName() == Messages::WebSWClientConnection::StartScriptFetchForServer::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::StartScriptFetchForServer>(connection, decoder, this, &WebSWClientConnection::startScriptFetchForServer);
    if (decoder.messageName() == Messages::WebSWClientConnection::UpdateRegistrationState::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::UpdateRegistrationState>(connection, decoder, this, &WebSWClientConnection::updateRegistrationState);
    if (decoder.messageName() == Messages::WebSWClientConnection::UpdateWorkerState::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::UpdateWorkerState>(connection, decoder, this, &WebSWClientConnection::updateWorkerState);
    if (decoder.messageName() == Messages::WebSWClientConnection::FireUpdateFoundEvent::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::FireUpdateFoundEvent>(connection, decoder, this, &WebSWClientConnection::fireUpdateFoundEvent);
    if (decoder.messageName() == Messages::WebSWClientConnection::SetRegistrationLastUpdateTime::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::SetRegistrationLastUpdateTime>(connection, decoder, this, &WebSWClientConnection::setRegistrationLastUpdateTime);
    if (decoder.messageName() == Messages::WebSWClientConnection::SetRegistrationUpdateViaCache::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::SetRegistrationUpdateViaCache>(connection, decoder, this, &WebSWClientConnection::setRegistrationUpdateViaCache);
    if (decoder.messageName() == Messages::WebSWClientConnection::NotifyClientsOfControllerChange::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::NotifyClientsOfControllerChange>(connection, decoder, this, &WebSWClientConnection::notifyClientsOfControllerChange);
    if (decoder.messageName() == Messages::WebSWClientConnection::UpdateBackgroundFetchRegistration::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::UpdateBackgroundFetchRegistration>(connection, decoder, this, &WebSWClientConnection::updateBackgroundFetchRegistration);
    if (decoder.messageName() == Messages::WebSWClientConnection::SetSWOriginTableIsImported::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::SetSWOriginTableIsImported>(connection, decoder, this, &WebSWClientConnection::setSWOriginTableIsImported);
    if (decoder.messageName() == Messages::WebSWClientConnection::SetSWOriginTableSharedMemory::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::SetSWOriginTableSharedMemory>(connection, decoder, this, &WebSWClientConnection::setSWOriginTableSharedMemory);
    if (decoder.messageName() == Messages::WebSWClientConnection::PostMessageToServiceWorkerClient::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::PostMessageToServiceWorkerClient>(connection, decoder, this, &WebSWClientConnection::postMessageToServiceWorkerClient);
    if (decoder.messageName() == Messages::WebSWClientConnection::SetServiceWorkerClientIsControlled::name())
        return IPC::handleMessageAsync<Messages::WebSWClientConnection::SetServiceWorkerClientIsControlled>(connection, decoder, this, &WebSWClientConnection::setServiceWorkerClientIsControlled);
    if (decoder.messageName() == Messages::WebSWClientConnection::FocusServiceWorkerClient::name())
        return IPC::handleMessageAsync<Messages::WebSWClientConnection::FocusServiceWorkerClient>(connection, decoder, this, &WebSWClientConnection::focusServiceWorkerClient);
    if (decoder.messageName() == Messages::WebSWClientConnection::NotifyRecordResponseBodyChunk::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::NotifyRecordResponseBodyChunk>(connection, decoder, this, &WebSWClientConnection::notifyRecordResponseBodyChunk);
    if (decoder.messageName() == Messages::WebSWClientConnection::NotifyRecordResponseBodyEnd::name())
        return IPC::handleMessage<Messages::WebSWClientConnection::NotifyRecordResponseBodyEnd>(connection, decoder, this, &WebSWClientConnection::notifyRecordResponseBodyEnd);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_JobRejectedInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::JobRejectedInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_RegistrationJobResolvedInServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::RegistrationJobResolvedInServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_StartScriptFetchForServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::StartScriptFetchForServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_UpdateRegistrationState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::UpdateRegistrationState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_UpdateWorkerState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::UpdateWorkerState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_FireUpdateFoundEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::FireUpdateFoundEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_SetRegistrationLastUpdateTime>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetRegistrationLastUpdateTime::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_SetRegistrationUpdateViaCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetRegistrationUpdateViaCache::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_NotifyClientsOfControllerChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::NotifyClientsOfControllerChange::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_UpdateBackgroundFetchRegistration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::UpdateBackgroundFetchRegistration::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_SetSWOriginTableIsImported>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetSWOriginTableIsImported::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_SetSWOriginTableSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetSWOriginTableSharedMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_PostMessageToServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::PostMessageToServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_SetServiceWorkerClientIsControlled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetServiceWorkerClientIsControlled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWClientConnection_SetServiceWorkerClientIsControlled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::SetServiceWorkerClientIsControlled::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_FocusServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::FocusServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWClientConnection_FocusServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::FocusServiceWorkerClient::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_NotifyRecordResponseBodyChunk>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::NotifyRecordResponseBodyChunk::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWClientConnection_NotifyRecordResponseBodyEnd>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWClientConnection::NotifyRecordResponseBodyEnd::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(SERVICE_WORKER)
