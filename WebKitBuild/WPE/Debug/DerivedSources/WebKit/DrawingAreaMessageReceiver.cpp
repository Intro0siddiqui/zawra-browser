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
#include "DrawingArea.h"

#if PLATFORM(COCOA)
#include "ArgumentCoders.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include "ArgumentCodersDarwin.h" // NOLINT
#endif
#include "Decoder.h" // NOLINT
#include "DrawingAreaMessages.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if PLATFORM(COCOA) || PLATFORM(COCOA) || PLATFORM(GTK) || USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || USE(GRAPHICS_LAYER_WC)
#include "WebCoreArgumentCoders.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/DestinationColorSpace.h> // NOLINT
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
#include <WebCore/FloatPoint.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/FloatRect.h> // NOLINT
#endif
#if PLATFORM(COCOA) || USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || USE(GRAPHICS_LAYER_WC)
#include <WebCore/IntSize.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/PlatformLayerIdentifier.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <optional> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <wtf/MachSendRight.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <wtf/MonotonicTime.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <wtf/text/WTFString.h> // NOLINT
#endif

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void DrawingArea::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    if (decoder.messageName() == Messages::DrawingArea::UpdateGeometry::name())
        return IPC::handleMessageAsync<Messages::DrawingArea::UpdateGeometry>(connection, decoder, this, &DrawingArea::updateGeometry);
    if (decoder.messageName() == Messages::DrawingArea::TargetRefreshRateDidChange::name())
        return IPC::handleMessage<Messages::DrawingArea::TargetRefreshRateDidChange>(connection, decoder, this, &DrawingArea::targetRefreshRateDidChange);
    if (decoder.messageName() == Messages::DrawingArea::SetDeviceScaleFactor::name())
        return IPC::handleMessage<Messages::DrawingArea::SetDeviceScaleFactor>(connection, decoder, this, &DrawingArea::setDeviceScaleFactor);
    if (decoder.messageName() == Messages::DrawingArea::ForceUpdate::name())
        return IPC::handleMessage<Messages::DrawingArea::ForceUpdate>(connection, decoder, this, &DrawingArea::forceUpdate);
    if (decoder.messageName() == Messages::DrawingArea::DidDiscardBackingStore::name())
        return IPC::handleMessage<Messages::DrawingArea::DidDiscardBackingStore>(connection, decoder, this, &DrawingArea::didDiscardBackingStore);
#endif
    if (decoder.messageName() == Messages::DrawingArea::DisplayDidRefresh::name())
        return IPC::handleMessage<Messages::DrawingArea::DisplayDidRefresh>(connection, decoder, this, &DrawingArea::displayDidRefresh);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::DrawingArea::UpdateGeometry::name())
        return IPC::handleMessageAsync<Messages::DrawingArea::UpdateGeometry>(connection, decoder, this, &DrawingArea::updateGeometry);
    if (decoder.messageName() == Messages::DrawingArea::SetDeviceScaleFactor::name())
        return IPC::handleMessage<Messages::DrawingArea::SetDeviceScaleFactor>(connection, decoder, this, &DrawingArea::setDeviceScaleFactor);
    if (decoder.messageName() == Messages::DrawingArea::SetColorSpace::name())
        return IPC::handleMessage<Messages::DrawingArea::SetColorSpace>(connection, decoder, this, &DrawingArea::setColorSpace);
    if (decoder.messageName() == Messages::DrawingArea::SetViewExposedRect::name())
        return IPC::handleMessage<Messages::DrawingArea::SetViewExposedRect>(connection, decoder, this, &DrawingArea::setViewExposedRect);
    if (decoder.messageName() == Messages::DrawingArea::AcceleratedAnimationDidStart::name())
        return IPC::handleMessage<Messages::DrawingArea::AcceleratedAnimationDidStart>(connection, decoder, this, &DrawingArea::acceleratedAnimationDidStart);
    if (decoder.messageName() == Messages::DrawingArea::AcceleratedAnimationDidEnd::name())
        return IPC::handleMessage<Messages::DrawingArea::AcceleratedAnimationDidEnd>(connection, decoder, this, &DrawingArea::acceleratedAnimationDidEnd);
    if (decoder.messageName() == Messages::DrawingArea::DispatchAfterEnsuringDrawing::name())
        return IPC::handleMessageAsyncWithReplyID<Messages::DrawingArea::DispatchAfterEnsuringDrawing>(connection, decoder, this, &DrawingArea::dispatchAfterEnsuringDrawing);
#endif
#if USE(GRAPHICS_LAYER_WC)
    if (decoder.messageName() == Messages::DrawingArea::UpdateGeometryWC::name())
        return IPC::handleMessage<Messages::DrawingArea::UpdateGeometryWC>(connection, decoder, this, &DrawingArea::updateGeometryWC);
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    if (decoder.messageName() == Messages::DrawingArea::AdjustTransientZoom::name())
        return IPC::handleMessage<Messages::DrawingArea::AdjustTransientZoom>(connection, decoder, this, &DrawingArea::adjustTransientZoom);
    if (decoder.messageName() == Messages::DrawingArea::CommitTransientZoom::name())
        return IPC::handleMessage<Messages::DrawingArea::CommitTransientZoom>(connection, decoder, this, &DrawingArea::commitTransientZoom);
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

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_UpdateGeometry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::UpdateGeometry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::DrawingArea_UpdateGeometry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::UpdateGeometry::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_TargetRefreshRateDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::TargetRefreshRateDidChange::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_SetDeviceScaleFactor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::SetDeviceScaleFactor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_ForceUpdate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::ForceUpdate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_DidDiscardBackingStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::DidDiscardBackingStore::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_DisplayDidRefresh>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::DisplayDidRefresh::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_UpdateGeometry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::UpdateGeometry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::DrawingArea_UpdateGeometry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::UpdateGeometry::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_SetDeviceScaleFactor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::SetDeviceScaleFactor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_SetColorSpace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::SetColorSpace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_SetViewExposedRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::SetViewExposedRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_AcceleratedAnimationDidStart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::AcceleratedAnimationDidStart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_AcceleratedAnimationDidEnd>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::AcceleratedAnimationDidEnd::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_DispatchAfterEnsuringDrawing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::DispatchAfterEnsuringDrawing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::DrawingArea_DispatchAfterEnsuringDrawing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::DispatchAfterEnsuringDrawing::ReplyArguments>(globalObject, decoder);
}
#endif
#if USE(GRAPHICS_LAYER_WC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_UpdateGeometryWC>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::UpdateGeometryWC::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_AdjustTransientZoom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::AdjustTransientZoom::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::DrawingArea_CommitTransientZoom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::DrawingArea::CommitTransientZoom::Arguments>(globalObject, decoder);
}
#endif

}

#endif

