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
#include "DrawingAreaProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Connection.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "DrawingAreaProxyMessages.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "LayerTreeContext.h" // NOLINT
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
#include "UpdateInfo.h" // NOLINT
#endif
#include <wtf/Vector.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void DrawingAreaProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::DrawingAreaProxy::EnterAcceleratedCompositingMode::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::EnterAcceleratedCompositingMode>(connection, decoder, this, &DrawingAreaProxy::enterAcceleratedCompositingMode);
    if (decoder.messageName() == Messages::DrawingAreaProxy::UpdateAcceleratedCompositingMode::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::UpdateAcceleratedCompositingMode>(connection, decoder, this, &DrawingAreaProxy::updateAcceleratedCompositingMode);
    if (decoder.messageName() == Messages::DrawingAreaProxy::DidFirstLayerFlush::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::DidFirstLayerFlush>(connection, decoder, this, &DrawingAreaProxy::didFirstLayerFlush);
    if (decoder.messageName() == Messages::DrawingAreaProxy::DispatchPresentationCallbacksAfterFlushingLayers::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::DispatchPresentationCallbacksAfterFlushingLayers>(connection, decoder, this, &DrawingAreaProxy::dispatchPresentationCallbacksAfterFlushingLayers);
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    if (decoder.messageName() == Messages::DrawingAreaProxy::Update::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::Update>(connection, decoder, this, &DrawingAreaProxy::update);
    if (decoder.messageName() == Messages::DrawingAreaProxy::ExitAcceleratedCompositingMode::name())
        return IPC::handleMessage<Messages::DrawingAreaProxy::ExitAcceleratedCompositingMode>(connection, decoder, this, &DrawingAreaProxy::exitAcceleratedCompositingMode);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_EnterAcceleratedCompositingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::EnterAcceleratedCompositingMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_UpdateAcceleratedCompositingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::UpdateAcceleratedCompositingMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_DidFirstLayerFlush>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::DidFirstLayerFlush::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_DispatchPresentationCallbacksAfterFlushingLayers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::DispatchPresentationCallbacksAfterFlushingLayers::Arguments>(globalObject, decoder);
}
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_Update>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::Update::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingAreaProxy_ExitAcceleratedCompositingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingAreaProxy::ExitAcceleratedCompositingMode::Arguments>(globalObject, decoder);
}
#endif

}

#endif

