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
#include "ServiceWorkerFetchTask.h"

#include "Decoder.h" // NOLINT
#include "FormDataReference.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "ServiceWorkerFetchTaskMessages.h" // NOLINT
#include "SharedBufferReference.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/NetworkLoadMetrics.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void ServiceWorkerFetchTask::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidNotHandle::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidNotHandle>(connection, decoder, this, &ServiceWorkerFetchTask::didNotHandle);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidFail::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidFail>(connection, decoder, this, &ServiceWorkerFetchTask::didFail);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidReceiveRedirectResponse::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidReceiveRedirectResponse>(connection, decoder, this, &ServiceWorkerFetchTask::didReceiveRedirectResponse);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidReceiveResponse::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidReceiveResponse>(connection, decoder, this, &ServiceWorkerFetchTask::didReceiveResponse);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidReceiveData::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidReceiveData>(connection, decoder, this, &ServiceWorkerFetchTask::didReceiveData);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidReceiveFormData::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidReceiveFormData>(connection, decoder, this, &ServiceWorkerFetchTask::didReceiveFormData);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::DidFinish::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::DidFinish>(connection, decoder, this, &ServiceWorkerFetchTask::didFinish);
    if (decoder.messageName() == Messages::ServiceWorkerFetchTask::UsePreload::name())
        return IPC::handleMessage<Messages::ServiceWorkerFetchTask::UsePreload>(connection, decoder, this, &ServiceWorkerFetchTask::usePreload);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidNotHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidNotHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidFail>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidFail::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidReceiveRedirectResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidReceiveRedirectResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidReceiveResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidReceiveResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidReceiveData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidReceiveData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidReceiveFormData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidReceiveFormData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_DidFinish>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::DidFinish::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::ServiceWorkerFetchTask_UsePreload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::ServiceWorkerFetchTask::UsePreload::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(SERVICE_WORKER)
