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
#include "RemoteQueue.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteQueueMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebGPUExtent3D.h" // NOLINT
#include "WebGPUIdentifier.h" // NOLINT
#include "WebGPUImageCopyExternalImage.h" // NOLINT
#include "WebGPUImageCopyTexture.h" // NOLINT
#include "WebGPUImageCopyTextureTagged.h" // NOLINT
#include "WebGPUImageDataLayout.h" // NOLINT
#include <WebCore/WebGPUIntegralTypes.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteQueue::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteQueue::Destruct::name())
        return IPC::handleMessage<Messages::RemoteQueue::Destruct>(connection.connection(), decoder, this, &RemoteQueue::destruct);
    if (decoder.messageName() == Messages::RemoteQueue::Submit::name())
        return IPC::handleMessage<Messages::RemoteQueue::Submit>(connection.connection(), decoder, this, &RemoteQueue::submit);
    if (decoder.messageName() == Messages::RemoteQueue::WriteBuffer::name())
        return IPC::handleMessage<Messages::RemoteQueue::WriteBuffer>(connection.connection(), decoder, this, &RemoteQueue::writeBuffer);
    if (decoder.messageName() == Messages::RemoteQueue::WriteTexture::name())
        return IPC::handleMessage<Messages::RemoteQueue::WriteTexture>(connection.connection(), decoder, this, &RemoteQueue::writeTexture);
    if (decoder.messageName() == Messages::RemoteQueue::CopyExternalImageToTexture::name())
        return IPC::handleMessage<Messages::RemoteQueue::CopyExternalImageToTexture>(connection.connection(), decoder, this, &RemoteQueue::copyExternalImageToTexture);
    if (decoder.messageName() == Messages::RemoteQueue::SetLabel::name())
        return IPC::handleMessage<Messages::RemoteQueue::SetLabel>(connection.connection(), decoder, this, &RemoteQueue::setLabel);
    if (decoder.messageName() == Messages::RemoteQueue::OnSubmittedWorkDone::name())
        return IPC::handleMessageSynchronous<Messages::RemoteQueue::OnSubmittedWorkDone>(connection, decoder, this, &RemoteQueue::onSubmittedWorkDone);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::Destruct::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_Submit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::Submit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_OnSubmittedWorkDone>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::OnSubmittedWorkDone::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteQueue_OnSubmittedWorkDone>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::OnSubmittedWorkDone::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_WriteBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::WriteBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_WriteTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::WriteTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_CopyExternalImageToTexture>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::CopyExternalImageToTexture::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteQueue_SetLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteQueue::SetLabel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
