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
#include "RemoteRenderPassEncoder.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteRenderPassEncoderMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebGPUColor.h" // NOLINT
#include "WebGPUIdentifier.h" // NOLINT
#include <WebCore/WebGPUIndexFormat.h> // NOLINT
#include <WebCore/WebGPUIntegralTypes.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteRenderPassEncoder::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::Destruct::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::Destruct>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::destruct);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetPipeline::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetPipeline>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setPipeline);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetIndexBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetIndexBuffer>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setIndexBuffer);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetVertexBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetVertexBuffer>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setVertexBuffer);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::Draw::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::Draw>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::draw);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::DrawIndexed::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::DrawIndexed>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::drawIndexed);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::DrawIndirect::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::DrawIndirect>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::drawIndirect);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::DrawIndexedIndirect::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::DrawIndexedIndirect>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::drawIndexedIndirect);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetBindGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetBindGroup>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setBindGroup);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::PushDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::PushDebugGroup>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::pushDebugGroup);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::PopDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::PopDebugGroup>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::popDebugGroup);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::InsertDebugMarker::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::InsertDebugMarker>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::insertDebugMarker);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetViewport::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetViewport>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setViewport);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetScissorRect::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetScissorRect>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setScissorRect);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetBlendConstant::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetBlendConstant>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setBlendConstant);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetStencilReference::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetStencilReference>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setStencilReference);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::BeginOcclusionQuery::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::BeginOcclusionQuery>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::beginOcclusionQuery);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::EndOcclusionQuery::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::EndOcclusionQuery>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::endOcclusionQuery);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::ExecuteBundles::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::ExecuteBundles>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::executeBundles);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::End::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::End>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::end);
    if (decoder.messageName() == Messages::RemoteRenderPassEncoder::SetLabel::name())
        return IPC::handleMessage<Messages::RemoteRenderPassEncoder::SetLabel>(connection.connection(), decoder, this, &RemoteRenderPassEncoder::setLabel);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::Destruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetPipeline>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetPipeline::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetIndexBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetIndexBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetVertexBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetVertexBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_Draw>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::Draw::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_DrawIndexed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::DrawIndexed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_DrawIndirect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::DrawIndirect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_DrawIndexedIndirect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::DrawIndexedIndirect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetBindGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetBindGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_PushDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::PushDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_PopDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::PopDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_InsertDebugMarker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::InsertDebugMarker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetViewport>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetViewport::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetScissorRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetScissorRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetBlendConstant>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetBlendConstant::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetStencilReference>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetStencilReference::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_BeginOcclusionQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::BeginOcclusionQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_EndOcclusionQuery>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::EndOcclusionQuery::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_ExecuteBundles>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::ExecuteBundles::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_End>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::End::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderPassEncoder_SetLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderPassEncoder::SetLabel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
