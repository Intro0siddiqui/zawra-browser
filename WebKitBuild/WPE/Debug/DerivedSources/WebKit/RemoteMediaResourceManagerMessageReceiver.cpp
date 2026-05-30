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
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "RemoteMediaResourceManager.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteMediaResourceIdentifier.h" // NOLINT
#include "RemoteMediaResourceManagerMessages.h" // NOLINT
#include "SharedBufferReference.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/FrameLoaderTypes.h> // NOLINT
#include <WebCore/NetworkLoadMetrics.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <optional> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteMediaResourceManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::ResponseReceived::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaResourceManager::ResponseReceived>(connection, decoder, this, &RemoteMediaResourceManager::responseReceived);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::RedirectReceived::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaResourceManager::RedirectReceived>(connection, decoder, this, &RemoteMediaResourceManager::redirectReceived);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::DataSent::name())
        return IPC::handleMessage<Messages::RemoteMediaResourceManager::DataSent>(connection, decoder, this, &RemoteMediaResourceManager::dataSent);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::DataReceived::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaResourceManager::DataReceived>(connection, decoder, this, &RemoteMediaResourceManager::dataReceived);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::AccessControlCheckFailed::name())
        return IPC::handleMessage<Messages::RemoteMediaResourceManager::AccessControlCheckFailed>(connection, decoder, this, &RemoteMediaResourceManager::accessControlCheckFailed);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::LoadFailed::name())
        return IPC::handleMessage<Messages::RemoteMediaResourceManager::LoadFailed>(connection, decoder, this, &RemoteMediaResourceManager::loadFailed);
    if (decoder.messageName() == Messages::RemoteMediaResourceManager::LoadFinished::name())
        return IPC::handleMessage<Messages::RemoteMediaResourceManager::LoadFinished>(connection, decoder, this, &RemoteMediaResourceManager::loadFinished);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_ResponseReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::ResponseReceived::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaResourceManager_ResponseReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::ResponseReceived::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_RedirectReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::RedirectReceived::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaResourceManager_RedirectReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::RedirectReceived::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_DataSent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::DataSent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_DataReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::DataReceived::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaResourceManager_DataReceived>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::DataReceived::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_AccessControlCheckFailed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::AccessControlCheckFailed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_LoadFailed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::LoadFailed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaResourceManager_LoadFinished>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaResourceManager::LoadFinished::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
