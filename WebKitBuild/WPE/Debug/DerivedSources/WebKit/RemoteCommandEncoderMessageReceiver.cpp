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
#include "RemoteCommandEncoder.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteCommandEncoderMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebGPUCommandBufferDescriptor.h" // NOLINT
#include "WebGPUComputePassDescriptor.h" // NOLINT
#include "WebGPUExtent3D.h" // NOLINT
#include "WebGPUIdentifier.h" // NOLINT
#include "WebGPUImageCopyBuffer.h" // NOLINT
#include "WebGPUImageCopyTexture.h" // NOLINT
#include "WebGPURenderPassDescriptor.h" // NOLINT
#include <WebCore/WebGPUIntegralTypes.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteCommandEncoder::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteCommandEncoder::BeginRenderPass::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::BeginRenderPass>(connection.connection(), decoder, this, &RemoteCommandEncoder::beginRenderPass);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::BeginComputePass::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::BeginComputePass>(connection.connection(), decoder, this, &RemoteCommandEncoder::beginComputePass);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::CopyBufferToBuffer::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::CopyBufferToBuffer>(connection.connection(), decoder, this, &RemoteCommandEncoder::copyBufferToBuffer);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::CopyBufferToTexture::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::CopyBufferToTexture>(connection.connection(), decoder, this, &RemoteCommandEncoder::copyBufferToTexture);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::CopyTextureToBuffer::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::CopyTextureToBuffer>(connection.connection(), decoder, this, &RemoteCommandEncoder::copyTextureToBuffer);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::CopyTextureToTexture::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::CopyTextureToTexture>(connection.connection(), decoder, this, &RemoteCommandEncoder::copyTextureToTexture);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::ClearBuffer::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::ClearBuffer>(connection.connection(), decoder, this, &RemoteCommandEncoder::clearBuffer);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::Destruct::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::Destruct>(connection.connection(), decoder, this, &RemoteCommandEncoder::destruct);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::PushDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::PushDebugGroup>(connection.connection(), decoder, this, &RemoteCommandEncoder::pushDebugGroup);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::PopDebugGroup::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::PopDebugGroup>(connection.connection(), decoder, this, &RemoteCommandEncoder::popDebugGroup);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::InsertDebugMarker::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::InsertDebugMarker>(connection.connection(), decoder, this, &RemoteCommandEncoder::insertDebugMarker);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::WriteTimestamp::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::WriteTimestamp>(connection.connection(), decoder, this, &RemoteCommandEncoder::writeTimestamp);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::ResolveQuerySet::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::ResolveQuerySet>(connection.connection(), decoder, this, &RemoteCommandEncoder::resolveQuerySet);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::Finish::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::Finish>(connection.connection(), decoder, this, &RemoteCommandEncoder::finish);
    if (decoder.messageName() == Messages::RemoteCommandEncoder::SetLabel::name())
        return IPC::handleMessage<Messages::RemoteCommandEncoder::SetLabel>(connection.connection(), decoder, this, &RemoteCommandEncoder::setLabel);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_BeginRenderPass>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::BeginRenderPass::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_BeginComputePass>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::BeginComputePass::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_CopyBufferToBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::CopyBufferToBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_CopyBufferToTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::CopyBufferToTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_CopyTextureToBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::CopyTextureToBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_CopyTextureToTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::CopyTextureToTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_ClearBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::ClearBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::Destruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_PushDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::PushDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_PopDebugGroup>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::PopDebugGroup::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_InsertDebugMarker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::InsertDebugMarker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_WriteTimestamp>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::WriteTimestamp::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_ResolveQuerySet>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::ResolveQuerySet::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_Finish>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::Finish::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCommandEncoder_SetLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCommandEncoder::SetLabel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
