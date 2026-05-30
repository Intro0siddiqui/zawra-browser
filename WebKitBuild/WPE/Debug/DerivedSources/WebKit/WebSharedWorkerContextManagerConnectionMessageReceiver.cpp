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
#include "WebSharedWorkerContextManagerConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPreferencesStore.h" // NOLINT
#include "WebSharedWorkerContextManagerConnectionMessages.h" // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/SharedWorkerIdentifier.h> // NOLINT
#include <WebCore/TransferredMessagePort.h> // NOLINT
#include <WebCore/WorkerFetchResult.h> // NOLINT
#include <WebCore/WorkerInitializationData.h> // NOLINT
#include <WebCore/WorkerOptions.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebSharedWorkerContextManagerConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::LaunchSharedWorker::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::LaunchSharedWorker>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::launchSharedWorker);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::PostConnectEvent::name())
        return IPC::handleMessageAsync<Messages::WebSharedWorkerContextManagerConnection::PostConnectEvent>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::postConnectEvent);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::TerminateSharedWorker::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::TerminateSharedWorker>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::terminateSharedWorker);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::UpdatePreferencesStore::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::UpdatePreferencesStore>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::updatePreferencesStore);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::SetUserAgent::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::SetUserAgent>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::setUserAgent);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::Close::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::Close>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::close);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::SuspendSharedWorker::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::SuspendSharedWorker>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::suspendSharedWorker);
    if (decoder.messageName() == Messages::WebSharedWorkerContextManagerConnection::ResumeSharedWorker::name())
        return IPC::handleMessage<Messages::WebSharedWorkerContextManagerConnection::ResumeSharedWorker>(connection, decoder, this, &WebSharedWorkerContextManagerConnection::resumeSharedWorker);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_LaunchSharedWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::LaunchSharedWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_PostConnectEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::PostConnectEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebSharedWorkerContextManagerConnection_PostConnectEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::PostConnectEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_TerminateSharedWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::TerminateSharedWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_UpdatePreferencesStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::UpdatePreferencesStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_SetUserAgent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::SetUserAgent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_Close>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::Close::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_SuspendSharedWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::SuspendSharedWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebSharedWorkerContextManagerConnection_ResumeSharedWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebSharedWorkerContextManagerConnection::ResumeSharedWorker::Arguments>(globalObject, decoder);
}

}

#endif

