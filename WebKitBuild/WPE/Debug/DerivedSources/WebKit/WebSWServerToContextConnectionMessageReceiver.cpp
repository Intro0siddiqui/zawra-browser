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
#include "WebSWServerToContextConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebSWServerToContextConnectionMessages.h" // NOLINT
#include <JavaScriptCore/ConsoleTypes.h> // NOLINT
#include <WebCore/ExceptionData.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#include <WebCore/ProcessQualified.h> // NOLINT
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerClientData.h> // NOLINT
#include <WebCore/ServiceWorkerClientQueryOptions.h> // NOLINT
#include <WebCore/ServiceWorkerIdentifier.h> // NOLINT
#include <WebCore/ServiceWorkerImportedScript.h> // NOLINT
#include <WebCore/ServiceWorkerJobDataIdentifier.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Expected.h> // NOLINT
#include <wtf/ObjectIdentifier.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSWServerToContextConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::ScriptContextFailedToStart::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::ScriptContextFailedToStart>(connection, decoder, this, &WebSWServerToContextConnection::scriptContextFailedToStart);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::ScriptContextStarted::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::ScriptContextStarted>(connection, decoder, this, &WebSWServerToContextConnection::scriptContextStarted);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::DidFinishInstall::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::DidFinishInstall>(connection, decoder, this, &WebSWServerToContextConnection::didFinishInstall);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::DidFinishActivation::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::DidFinishActivation>(connection, decoder, this, &WebSWServerToContextConnection::didFinishActivation);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::SetServiceWorkerHasPendingEvents::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::SetServiceWorkerHasPendingEvents>(connection, decoder, this, &WebSWServerToContextConnection::setServiceWorkerHasPendingEvents);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::SkipWaiting::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::SkipWaiting>(connection, decoder, this, &WebSWServerToContextConnection::skipWaiting);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::WorkerTerminated::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::WorkerTerminated>(connection, decoder, this, &WebSWServerToContextConnection::workerTerminated);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::FindClientByVisibleIdentifier::name())
        return IPC::handleMessageAsync<Messages::WebSWServerToContextConnection::FindClientByVisibleIdentifier>(connection, decoder, this, &WebSWServerToContextConnection::findClientByVisibleIdentifier);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::MatchAll::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::MatchAll>(connection, decoder, this, &WebSWServerToContextConnection::matchAll);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::Claim::name())
        return IPC::handleMessageAsync<Messages::WebSWServerToContextConnection::Claim>(connection, decoder, this, &WebSWServerToContextConnection::claim);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::Focus::name())
        return IPC::handleMessageAsync<Messages::WebSWServerToContextConnection::Focus>(connection, decoder, this, &WebSWServerToContextConnection::focus);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::Navigate::name())
        return IPC::handleMessageAsync<Messages::WebSWServerToContextConnection::Navigate>(connection, decoder, this, &WebSWServerToContextConnection::navigate);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::SetScriptResource::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::SetScriptResource>(connection, decoder, this, &WebSWServerToContextConnection::setScriptResource);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::PostMessageToServiceWorkerClient::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::PostMessageToServiceWorkerClient>(connection, decoder, this, &WebSWServerToContextConnection::postMessageToServiceWorkerClient);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::DidFailHeartBeatCheck::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::DidFailHeartBeatCheck>(connection, decoder, this, &WebSWServerToContextConnection::didFailHeartBeatCheck);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::SetAsInspected::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::SetAsInspected>(connection, decoder, this, &WebSWServerToContextConnection::setAsInspected);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::OpenWindow::name())
        return IPC::handleMessageAsync<Messages::WebSWServerToContextConnection::OpenWindow>(connection, decoder, this, &WebSWServerToContextConnection::openWindow);
    if (decoder.messageName() == Messages::WebSWServerToContextConnection::ReportConsoleMessage::name())
        return IPC::handleMessage<Messages::WebSWServerToContextConnection::ReportConsoleMessage>(connection, decoder, this, &WebSWServerToContextConnection::reportConsoleMessage);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_ScriptContextFailedToStart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::ScriptContextFailedToStart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_ScriptContextStarted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::ScriptContextStarted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_DidFinishInstall>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::DidFinishInstall::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_DidFinishActivation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::DidFinishActivation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_SetServiceWorkerHasPendingEvents>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::SetServiceWorkerHasPendingEvents::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_SkipWaiting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::SkipWaiting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_WorkerTerminated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::WorkerTerminated::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_FindClientByVisibleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::FindClientByVisibleIdentifier::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerToContextConnection_FindClientByVisibleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::FindClientByVisibleIdentifier::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_MatchAll>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::MatchAll::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_Claim>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Claim::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerToContextConnection_Claim>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Claim::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_Focus>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Focus::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerToContextConnection_Focus>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Focus::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_Navigate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Navigate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerToContextConnection_Navigate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::Navigate::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_SetScriptResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::SetScriptResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_PostMessageToServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::PostMessageToServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_DidFailHeartBeatCheck>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::DidFailHeartBeatCheck::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_SetAsInspected>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::SetAsInspected::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_OpenWindow>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::OpenWindow::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSWServerToContextConnection_OpenWindow>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::OpenWindow::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSWServerToContextConnection_ReportConsoleMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSWServerToContextConnection::ReportConsoleMessage::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(SERVICE_WORKER)
