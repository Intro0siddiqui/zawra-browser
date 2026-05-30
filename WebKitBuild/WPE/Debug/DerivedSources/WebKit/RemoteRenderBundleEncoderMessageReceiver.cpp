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
#include "RemoteRenderBundleEncoder.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteRenderBundleEncoderMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebGPUIdentifier.h" // NOLINT
#include "WebGPURenderBundleDescriptor.h" // NOLINT
#include <WebCore/WebGPUIndexFormat.h> // NOLINT
#include <WebCore/WebGPUIntegralTypes.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteRenderBundleEncoder::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::Destruct::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::Destruct>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::destruct);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::SetPipeline::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::SetPipeline>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::setPipeline);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::SetIndexBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::SetIndexBuffer>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::setIndexBuffer);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::SetVertexBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::SetVertexBuffer>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::setVertexBuffer);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::Draw::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::Draw>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::draw);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::DrawIndexed::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::DrawIndexed>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::drawIndexed);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::DrawIndirect::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::DrawIndirect>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::drawIndirect);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::DrawIndexedIndirect::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::DrawIndexedIndirect>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::drawIndexedIndirect);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::SetBindGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::SetBindGroup>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::setBindGroup);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::PushDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::PushDebugGroup>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::pushDebugGroup);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::PopDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::PopDebugGroup>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::popDebugGroup);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::InsertDebugMarker::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::InsertDebugMarker>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::insertDebugMarker);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::Finish::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::Finish>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::finish);
    if (decoder.messageName() == Messages::RemoteRenderBundleEncoder::SetLabel::name())
        return IPC::handleMessage<Messages::RemoteRenderBundleEncoder::SetLabel>(connection.connection(), decoder, this, &RemoteRenderBundleEncoder::setLabel);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::Destruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_SetPipeline>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::SetPipeline::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_SetIndexBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::SetIndexBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_SetVertexBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::SetVertexBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_Draw>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::Draw::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_DrawIndexed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::DrawIndexed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_DrawIndirect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::DrawIndirect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_DrawIndexedIndirect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::DrawIndexedIndirect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_SetBindGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::SetBindGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_PushDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::PushDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_PopDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::PopDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_InsertDebugMarker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::InsertDebugMarker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_Finish>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::Finish::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderBundleEncoder_SetLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderBundleEncoder::SetLabel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
