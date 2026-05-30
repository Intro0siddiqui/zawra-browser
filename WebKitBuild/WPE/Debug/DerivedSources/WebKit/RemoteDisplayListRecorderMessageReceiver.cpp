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
#include "RemoteDisplayListRecorder.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCSemaphore.h" // NOLINT
#include "RemoteDisplayListRecorderMessages.h" // NOLINT
#if PLATFORM(COCOA) && ENABLE(VIDEO)
#include "SharedMemory.h" // NOLINT
#endif
#if PLATFORM(COCOA) && ENABLE(VIDEO)
#include "SharedVideoFrame.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/AffineTransform.h> // NOLINT
#include <WebCore/Color.h> // NOLINT
#include <WebCore/ControlPart.h> // NOLINT
#include <WebCore/ControlStyle.h> // NOLINT
#include <WebCore/DestinationColorSpace.h> // NOLINT
#include <WebCore/DisplayList.h> // NOLINT
#include <WebCore/Filter.h> // NOLINT
#include <WebCore/FloatPoint.h> // NOLINT
#include <WebCore/FloatRect.h> // NOLINT
#include <WebCore/FloatRoundedRect.h> // NOLINT
#include <WebCore/FloatSize.h> // NOLINT
#include <WebCore/GraphicsTypes.h> // NOLINT
#include <WebCore/ImagePaintingOptions.h> // NOLINT
#if ENABLE(VIDEO)
#include <WebCore/MediaPlayerIdentifier.h> // NOLINT
#endif
#include <WebCore/Path.h> // NOLINT
#include <WebCore/PathSegment.h> // NOLINT
#if ENABLE(INLINE_PATH_DATA)
#include <WebCore/PathSegmentData.h> // NOLINT
#endif
#include <WebCore/RenderingResourceIdentifier.h> // NOLINT
#include <WebCore/SystemImage.h> // NOLINT
#include <WebCore/WindRule.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Ref.h> // NOLINT
#include <wtf/Vector.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteDisplayListRecorder::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Save::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Save>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::save);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Restore::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Restore>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::restore);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Translate::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Translate>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::translate);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Rotate::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Rotate>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::rotate);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Scale::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Scale>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::scale);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetCTM::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetCTM>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setCTM);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ConcatenateCTM::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ConcatenateCTM>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::concatenateCTM);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetInlineFillColor::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetInlineFillColor>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setInlineFillColor);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetInlineStrokeColor::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetInlineStrokeColor>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setInlineStrokeColor);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetStrokeThickness::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetStrokeThickness>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setStrokeThickness);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetState::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetState>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setState);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetLineCap::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetLineCap>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setLineCap);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetLineDash::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetLineDash>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setLineDash);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetLineJoin::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetLineJoin>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setLineJoin);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetMiterLimit::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetMiterLimit>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setMiterLimit);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClearShadow::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClearShadow>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clearShadow);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::Clip::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::Clip>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clip);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipRoundedRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipRoundedRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipRoundedRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipOut::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipOut>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipOut);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipOutRoundedRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipOutRoundedRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipOutRoundedRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipToImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipToImageBuffer>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipToImageBuffer);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipOutToPath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipOutToPath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipOutToPath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClipPath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClipPath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clipPath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ResetClip::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ResetClip>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::resetClip);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawGlyphs::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawGlyphs>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawGlyphs);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawDecomposedGlyphs::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawDecomposedGlyphs>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawDecomposedGlyphs);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawFilteredImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawFilteredImageBuffer>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawFilteredImageBuffer);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawImageBuffer>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawImageBuffer);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawNativeImage::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawNativeImage>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawNativeImage);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawSystemImage::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawSystemImage>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawSystemImage);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawPattern::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawPattern>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawPattern);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::BeginTransparencyLayer::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::BeginTransparencyLayer>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::beginTransparencyLayer);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::EndTransparencyLayer::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::EndTransparencyLayer>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::endTransparencyLayer);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawLine::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawLine>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawLine);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawLinesForText::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawLinesForText>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawLinesForText);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawDotsForDocumentMarker::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawDotsForDocumentMarker>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawDotsForDocumentMarker);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawEllipse::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawEllipse>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawEllipse);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawPath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawPath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawPath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawFocusRingPath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawFocusRingPath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawFocusRingPath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawFocusRingRects::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawFocusRingRects>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawFocusRingRects);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillRectWithColor::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillRectWithColor>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillRectWithColor);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillRectWithGradient::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillRectWithGradient>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillRectWithGradient);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillCompositedRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillCompositedRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillCompositedRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillRoundedRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillRoundedRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillRoundedRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillRectWithRoundedHole::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillRectWithRoundedHole>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillRectWithRoundedHole);
#if ENABLE(INLINE_PATH_DATA)
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillLine::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillLine>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillLine);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillArc::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillArc>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillArc);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillQuadCurve::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillQuadCurve>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillQuadCurve);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillBezierCurve::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillBezierCurve>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillBezierCurve);
#endif
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillPathSegment::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillPathSegment>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillPathSegment);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillPath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillPath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillPath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FillEllipse::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FillEllipse>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::fillEllipse);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ConvertToLuminanceMask::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ConvertToLuminanceMask>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::convertToLuminanceMask);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::TransformToColorSpace::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::TransformToColorSpace>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::transformToColorSpace);
#if ENABLE(VIDEO)
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::PaintFrameForMedia::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::PaintFrameForMedia>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::paintFrameForMedia);
#endif
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeRect);
#if ENABLE(INLINE_PATH_DATA)
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeLine::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeLine>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeLine);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeLineWithColorAndThickness::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeLineWithColorAndThickness>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeLineWithColorAndThickness);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeArc::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeArc>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeArc);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeQuadCurve::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeQuadCurve>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeQuadCurve);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeBezierCurve::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeBezierCurve>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeBezierCurve);
#endif
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokePathSegment::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokePathSegment>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokePathSegment);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokePath::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokePath>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokePath);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::StrokeEllipse::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::StrokeEllipse>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::strokeEllipse);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ClearRect::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ClearRect>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::clearRect);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::DrawControlPart::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::DrawControlPart>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::drawControlPart);
#if USE(CG)
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ApplyStrokePattern::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ApplyStrokePattern>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::applyStrokePattern);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ApplyFillPattern::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ApplyFillPattern>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::applyFillPattern);
#endif
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::ApplyDeviceScaleFactor::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::ApplyDeviceScaleFactor>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::applyDeviceScaleFactor);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FlushContext::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::FlushContext>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::flushContext);
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::PaintVideoFrame::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::PaintVideoFrame>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::paintVideoFrame);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetSharedVideoFrameSemaphore>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::RemoteDisplayListRecorder::SetSharedVideoFrameMemory>(connection.connection(), decoder, this, &RemoteDisplayListRecorder::setSharedVideoFrameMemory);
#endif
    if (decoder.messageName() == Messages::RemoteDisplayListRecorder::FlushContextSync::name())
        return IPC::handleMessageSynchronous<Messages::RemoteDisplayListRecorder::FlushContextSync>(connection, decoder, this, &RemoteDisplayListRecorder::flushContextSync);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Save>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Save::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Restore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Restore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Translate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Translate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Rotate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Rotate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Scale>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Scale::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetCTM>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetCTM::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ConcatenateCTM>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ConcatenateCTM::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetInlineFillColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetInlineFillColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetInlineStrokeColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetInlineStrokeColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetStrokeThickness>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetStrokeThickness::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetLineCap>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetLineCap::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetLineDash>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetLineDash::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetLineJoin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetLineJoin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetMiterLimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetMiterLimit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClearShadow>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClearShadow::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_Clip>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::Clip::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipRoundedRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipRoundedRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipOut>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipOut::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipOutRoundedRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipOutRoundedRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipToImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipToImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipOutToPath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipOutToPath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClipPath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClipPath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ResetClip>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ResetClip::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawGlyphs>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawGlyphs::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawDecomposedGlyphs>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawDecomposedGlyphs::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawFilteredImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawFilteredImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawNativeImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawNativeImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawSystemImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawSystemImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawPattern>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawPattern::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_BeginTransparencyLayer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::BeginTransparencyLayer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_EndTransparencyLayer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::EndTransparencyLayer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawLine>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawLine::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawLinesForText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawLinesForText::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawDotsForDocumentMarker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawDotsForDocumentMarker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawEllipse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawEllipse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawPath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawPath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawFocusRingPath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawFocusRingPath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawFocusRingRects>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawFocusRingRects::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillRectWithColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillRectWithColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillRectWithGradient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillRectWithGradient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillCompositedRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillCompositedRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillRoundedRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillRoundedRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillRectWithRoundedHole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillRectWithRoundedHole::Arguments>(globalObject, decoder);
}
#if ENABLE(INLINE_PATH_DATA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillLine>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillLine::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillArc>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillArc::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillQuadCurve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillQuadCurve::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillBezierCurve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillBezierCurve::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillPathSegment>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillPathSegment::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillPath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillPath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FillEllipse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FillEllipse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ConvertToLuminanceMask>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ConvertToLuminanceMask::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_TransformToColorSpace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::TransformToColorSpace::Arguments>(globalObject, decoder);
}
#if ENABLE(VIDEO)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_PaintFrameForMedia>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::PaintFrameForMedia::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeRect::Arguments>(globalObject, decoder);
}
#if ENABLE(INLINE_PATH_DATA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeLine>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeLine::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeLineWithColorAndThickness>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeLineWithColorAndThickness::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeArc>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeArc::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeQuadCurve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeQuadCurve::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeBezierCurve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeBezierCurve::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokePathSegment>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokePathSegment::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokePath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokePath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_StrokeEllipse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::StrokeEllipse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ClearRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ClearRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_DrawControlPart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::DrawControlPart::Arguments>(globalObject, decoder);
}
#if USE(CG)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ApplyStrokePattern>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ApplyStrokePattern::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ApplyFillPattern>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ApplyFillPattern::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_ApplyDeviceScaleFactor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::ApplyDeviceScaleFactor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FlushContext>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FlushContext::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_FlushContextSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FlushContextSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteDisplayListRecorder_FlushContextSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::FlushContextSync::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA) && ENABLE(VIDEO)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_PaintVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::PaintVideoFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteDisplayListRecorder_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteDisplayListRecorder::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}
#endif

}

#endif


#endif // ENABLE(GPU_PROCESS)
