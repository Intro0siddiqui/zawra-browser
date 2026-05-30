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
#if ENABLE(GPU_PROCESS)
#include "RemoteComputePassEncoder.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteComputePassEncoderMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebGPUIdentifier.h" // NOLINT
#include <WebCore/WebGPUIntegralTypes.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteComputePassEncoder::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::Destruct::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::Destruct>(connection.connection(), decoder, this, &RemoteComputePassEncoder::destruct);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::SetPipeline::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::SetPipeline>(connection.connection(), decoder, this, &RemoteComputePassEncoder::setPipeline);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::Dispatch::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::Dispatch>(connection.connection(), decoder, this, &RemoteComputePassEncoder::dispatch);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::DispatchIndirect::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::DispatchIndirect>(connection.connection(), decoder, this, &RemoteComputePassEncoder::dispatchIndirect);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::End::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::End>(connection.connection(), decoder, this, &RemoteComputePassEncoder::end);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::SetBindGroup::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::SetBindGroup>(connection.connection(), decoder, this, &RemoteComputePassEncoder::setBindGroup);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::PushDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::PushDebugGroup>(connection.connection(), decoder, this, &RemoteComputePassEncoder::pushDebugGroup);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::PopDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::PopDebugGroup>(connection.connection(), decoder, this, &RemoteComputePassEncoder::popDebugGroup);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::InsertDebugMarker::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::InsertDebugMarker>(connection.connection(), decoder, this, &RemoteComputePassEncoder::insertDebugMarker);
    if (decoder.messageName() == Messages::RemoteComputePassEncoder::SetLabel::name())
        return IPC::handleMessage<Messages::RemoteComputePassEncoder::SetLabel>(connection.connection(), decoder, this, &RemoteComputePassEncoder::setLabel);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(connection);
#if ENABLE(IPC_TESTING_API)
    if (connection.connection().ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled stream message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::Destruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_SetPipeline>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::SetPipeline::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_Dispatch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::Dispatch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_DispatchIndirect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::DispatchIndirect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_End>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::End::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_SetBindGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::SetBindGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_PushDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::PushDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_PopDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::PopDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_InsertDebugMarker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::InsertDebugMarker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteComputePassEncoder_SetLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteComputePassEncoder::SetLabel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
