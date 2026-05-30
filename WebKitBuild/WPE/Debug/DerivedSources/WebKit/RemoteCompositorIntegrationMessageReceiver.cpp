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
#include "RemoteCompositorIntegration.h"

#if PLATFORM(COCOA)
#include "ArgumentCoders.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include "ArgumentCodersDarwin.h" // NOLINT
#endif
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteCompositorIntegrationMessages.h" // NOLINT
#if PLATFORM(COCOA)
#include <wtf/MachSendRight.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <wtf/Vector.h> // NOLINT
#endif

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteCompositorIntegration::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteCompositorIntegration::Destruct::name())
        return IPC::handleMessage<Messages::RemoteCompositorIntegration::Destruct>(connection.connection(), decoder, this, &RemoteCompositorIntegration::destruct);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteCompositorIntegration::RecreateRenderBuffers::name())
        return IPC::handleMessageSynchronous<Messages::RemoteCompositorIntegration::RecreateRenderBuffers>(connection, decoder, this, &RemoteCompositorIntegration::recreateRenderBuffers);
#endif
    if (decoder.messageName() == Messages::RemoteCompositorIntegration::PrepareForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteCompositorIntegration::PrepareForDisplay>(connection, decoder, this, &RemoteCompositorIntegration::prepareForDisplay);
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

#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCompositorIntegration_RecreateRenderBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCompositorIntegration::RecreateRenderBuffers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCompositorIntegration_RecreateRenderBuffers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCompositorIntegration::RecreateRenderBuffers::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCompositorIntegration_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCompositorIntegration::PrepareForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCompositorIntegration_PrepareForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCompositorIntegration::PrepareForDisplay::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCompositorIntegration_Destruct>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCompositorIntegration::Destruct::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
