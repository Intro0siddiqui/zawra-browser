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
#include "AuxiliaryProcess.h"

#include "AuxiliaryProcessMessages.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void AuxiliaryProcess::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::AuxiliaryProcess::ShutDown::name())
        return IPC::handleMessage<Messages::AuxiliaryProcess::ShutDown>(connection, decoder, this, &AuxiliaryProcess::shutDown);
    if (decoder.messageName() == Messages::AuxiliaryProcess::SetProcessSuppressionEnabled::name())
        return IPC::handleMessage<Messages::AuxiliaryProcess::SetProcessSuppressionEnabled>(connection, decoder, this, &AuxiliaryProcess::setProcessSuppressionEnabled);
    if (decoder.messageName() == Messages::AuxiliaryProcess::MainThreadPing::name())
        return IPC::handleMessageAsync<Messages::AuxiliaryProcess::MainThreadPing>(connection, decoder, this, &AuxiliaryProcess::mainThreadPing);
#if OS(LINUX)
    if (decoder.messageName() == Messages::AuxiliaryProcess::DidReceiveMemoryPressureEvent::name())
        return IPC::handleMessage<Messages::AuxiliaryProcess::DidReceiveMemoryPressureEvent>(connection, decoder, this, &AuxiliaryProcess::didReceiveMemoryPressureEvent);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::AuxiliaryProcess_ShutDown>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::AuxiliaryProcess::ShutDown::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::AuxiliaryProcess_SetProcessSuppressionEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::AuxiliaryProcess::SetProcessSuppressionEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::AuxiliaryProcess_MainThreadPing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::AuxiliaryProcess::MainThreadPing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::AuxiliaryProcess_MainThreadPing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::AuxiliaryProcess::MainThreadPing::ReplyArguments>(globalObject, decoder);
}
#if OS(LINUX)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::AuxiliaryProcess_DidReceiveMemoryPressureEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::AuxiliaryProcess::DidReceiveMemoryPressureEvent::Arguments>(globalObject, decoder);
}
#endif

}

#endif

