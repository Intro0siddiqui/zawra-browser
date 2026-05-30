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

#pragma once

#if ENABLE(GPU_PROCESS)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#include <WebCore/ControlPart.h>
#include <WebCore/ControlStyle.h>
#include <WebCore/DestinationColorSpace.h>
#include <WebCore/DisplayList.h>
#include <WebCore/Filter.h>
#include <WebCore/FloatRect.h>
#include <WebCore/MediaPlayerIdentifier.h>
#include <WebCore/PathSegmentData.h>
#include <WebCore/RenderingResourceIdentifier.h>
#include <WebCore/SystemImage.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/Ref.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {
class AffineTransform;
class Color;
class FloatPoint;
class FloatRect;
class FloatRoundedRect;
class FloatSize;
class Path;
class PathSegment;
enum class WindRule : bool;
enum class BlendMode : uint8_t;
enum class CompositeOperator : uint8_t;
enum class LineCap : uint8_t;
enum class LineJoin : uint8_t;
struct DocumentMarkerLineStyle;
struct ImagePaintingOptions;
}

namespace Messages {
namespace RemoteDisplayListRecorder {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteDisplayListRecorder;
}

class Save {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Save; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Restore {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Restore; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Translate {
public:
    using Arguments = std::tuple<float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Translate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    Translate(float x, float y)
        : m_arguments(x, y)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float> m_arguments;
};

class Rotate {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Rotate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit Rotate(float angle)
        : m_arguments(angle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class Scale {
public:
    using Arguments = std::tuple<WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Scale; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit Scale(const WebCore::FloatSize& scale)
        : m_arguments(scale)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&> m_arguments;
};

class SetCTM {
public:
    using Arguments = std::tuple<WebCore::AffineTransform>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetCTM; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetCTM(const WebCore::AffineTransform& ctm)
        : m_arguments(ctm)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::AffineTransform&> m_arguments;
};

class ConcatenateCTM {
public:
    using Arguments = std::tuple<WebCore::AffineTransform>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ConcatenateCTM; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit ConcatenateCTM(const WebCore::AffineTransform& ctm)
        : m_arguments(ctm)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::AffineTransform&> m_arguments;
};

class SetInlineFillColor {
public:
    using Arguments = std::tuple<WebCore::DisplayList::SetInlineFillColor>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetInlineFillColor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetInlineFillColor(const WebCore::DisplayList::SetInlineFillColor& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::SetInlineFillColor&> m_arguments;
};

class SetInlineStrokeColor {
public:
    using Arguments = std::tuple<WebCore::DisplayList::SetInlineStrokeColor>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetInlineStrokeColor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetInlineStrokeColor(const WebCore::DisplayList::SetInlineStrokeColor& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::SetInlineStrokeColor&> m_arguments;
};

class SetStrokeThickness {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetStrokeThickness; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetStrokeThickness(float thickness)
        : m_arguments(thickness)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class SetState {
public:
    using Arguments = std::tuple<WebCore::DisplayList::SetState>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetState; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetState(const WebCore::DisplayList::SetState& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::SetState&> m_arguments;
};

class SetLineCap {
public:
    using Arguments = std::tuple<WebCore::LineCap>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetLineCap; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetLineCap(WebCore::LineCap lineCap)
        : m_arguments(lineCap)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::LineCap> m_arguments;
};

class SetLineDash {
public:
    using Arguments = std::tuple<WebCore::DisplayList::SetLineDash>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetLineDash; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetLineDash(const WebCore::DisplayList::SetLineDash& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::SetLineDash&> m_arguments;
};

class SetLineJoin {
public:
    using Arguments = std::tuple<WebCore::LineJoin>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetLineJoin; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetLineJoin(WebCore::LineJoin lineJoin)
        : m_arguments(lineJoin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::LineJoin> m_arguments;
};

class SetMiterLimit {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetMiterLimit; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit SetMiterLimit(float limit)
        : m_arguments(limit)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class ClearShadow {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClearShadow; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Clip {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_Clip; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit Clip(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class ClipRoundedRect {
public:
    using Arguments = std::tuple<WebCore::FloatRoundedRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipRoundedRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClipRoundedRect(const WebCore::FloatRoundedRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRoundedRect&> m_arguments;
};

class ClipOut {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipOut; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClipOut(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class ClipOutRoundedRect {
public:
    using Arguments = std::tuple<WebCore::FloatRoundedRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipOutRoundedRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClipOutRoundedRect(const WebCore::FloatRoundedRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRoundedRect&> m_arguments;
};

class ClipToImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipToImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClipToImageBuffer(const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier, const WebCore::FloatRect& destinationRect)
        : m_arguments(renderingResourceIdentifier, destinationRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::FloatRect&> m_arguments;
};

class ClipOutToPath {
public:
    using Arguments = std::tuple<WebCore::Path>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipOutToPath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClipOutToPath(const WebCore::Path& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&> m_arguments;
};

class ClipPath {
public:
    using Arguments = std::tuple<WebCore::Path, WebCore::WindRule>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClipPath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClipPath(const WebCore::Path& path, WebCore::WindRule windRule)
        : m_arguments(path, windRule)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&, WebCore::WindRule> m_arguments;
};

class ResetClip {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ResetClip; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DrawGlyphs {
public:
    using Arguments = std::tuple<WebCore::DisplayList::DrawGlyphs>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawGlyphs; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawGlyphs(const WebCore::DisplayList::DrawGlyphs& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::DrawGlyphs&> m_arguments;
};

class DrawDecomposedGlyphs {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawDecomposedGlyphs; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawDecomposedGlyphs(const WebCore::RenderingResourceIdentifier& fontIdentifier, const WebCore::RenderingResourceIdentifier& decomposedGlyphsIdentifier)
        : m_arguments(fontIdentifier, decomposedGlyphsIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class DrawFilteredImageBuffer {
public:
    using Arguments = std::tuple<std::optional<WebCore::RenderingResourceIdentifier>, WebCore::FloatRect, Ref<WebCore::Filter>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawFilteredImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawFilteredImageBuffer(const std::optional<WebCore::RenderingResourceIdentifier>& sourceImageIdentifier, const WebCore::FloatRect& sourceImageRect, const Ref<WebCore::Filter>& filter)
        : m_arguments(sourceImageIdentifier, sourceImageRect, filter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::RenderingResourceIdentifier>&, const WebCore::FloatRect&, const Ref<WebCore::Filter>&> m_arguments;
};

class DrawImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::FloatRect, WebCore::FloatRect, WebCore::ImagePaintingOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawImageBuffer(const WebCore::RenderingResourceIdentifier& imageBufferIdentifier, const WebCore::FloatRect& destinationRect, const WebCore::FloatRect& srcRect, const WebCore::ImagePaintingOptions& options)
        : m_arguments(imageBufferIdentifier, destinationRect, srcRect, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::ImagePaintingOptions&> m_arguments;
};

class DrawNativeImage {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::FloatSize, WebCore::FloatRect, WebCore::FloatRect, WebCore::ImagePaintingOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawNativeImage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawNativeImage(const WebCore::RenderingResourceIdentifier& imageIdentifier, const WebCore::FloatSize& imageSize, const WebCore::FloatRect& destRect, const WebCore::FloatRect& srcRect, const WebCore::ImagePaintingOptions& options)
        : m_arguments(imageIdentifier, imageSize, destRect, srcRect, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::FloatSize&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::ImagePaintingOptions&> m_arguments;
};

class DrawSystemImage {
public:
    using Arguments = std::tuple<Ref<WebCore::SystemImage>, WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawSystemImage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawSystemImage(const Ref<WebCore::SystemImage>& systemImage, const WebCore::FloatRect& destinationRect)
        : m_arguments(systemImage, destinationRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::SystemImage>&, const WebCore::FloatRect&> m_arguments;
};

class DrawPattern {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::FloatRect, WebCore::FloatRect, WebCore::AffineTransform, WebCore::FloatPoint, WebCore::FloatSize, WebCore::ImagePaintingOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawPattern; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawPattern(const WebCore::RenderingResourceIdentifier& imageIdentifier, const WebCore::FloatRect& destRect, const WebCore::FloatRect& tileRect, const WebCore::AffineTransform& transform, const WebCore::FloatPoint& phase, const WebCore::FloatSize& spacing, const WebCore::ImagePaintingOptions& options)
        : m_arguments(imageIdentifier, destRect, tileRect, transform, phase, spacing, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::AffineTransform&, const WebCore::FloatPoint&, const WebCore::FloatSize&, const WebCore::ImagePaintingOptions&> m_arguments;
};

class BeginTransparencyLayer {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_BeginTransparencyLayer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit BeginTransparencyLayer(float opacity)
        : m_arguments(opacity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class EndTransparencyLayer {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_EndTransparencyLayer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DrawRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawRect(const WebCore::FloatRect& rect, float borderThickness)
        : m_arguments(rect, borderThickness)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, float> m_arguments;
};

class DrawLine {
public:
    using Arguments = std::tuple<WebCore::FloatPoint, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawLine; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawLine(const WebCore::FloatPoint& point1, const WebCore::FloatPoint& point2)
        : m_arguments(point1, point2)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&, const WebCore::FloatPoint&> m_arguments;
};

class DrawLinesForText {
public:
    using Arguments = std::tuple<WebCore::DisplayList::DrawLinesForText>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawLinesForText; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawLinesForText(const WebCore::DisplayList::DrawLinesForText& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::DrawLinesForText&> m_arguments;
};

class DrawDotsForDocumentMarker {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::DocumentMarkerLineStyle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawDotsForDocumentMarker; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawDotsForDocumentMarker(const WebCore::FloatRect& rect, const WebCore::DocumentMarkerLineStyle& style)
        : m_arguments(rect, style)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::DocumentMarkerLineStyle&> m_arguments;
};

class DrawEllipse {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawEllipse; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawEllipse(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class DrawPath {
public:
    using Arguments = std::tuple<WebCore::Path>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawPath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawPath(const WebCore::Path& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&> m_arguments;
};

class DrawFocusRingPath {
public:
    using Arguments = std::tuple<WebCore::Path, float, WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawFocusRingPath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawFocusRingPath(const WebCore::Path& path, float outlineWidth, const WebCore::Color& color)
        : m_arguments(path, outlineWidth, color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&, float, const WebCore::Color&> m_arguments;
};

class DrawFocusRingRects {
public:
    using Arguments = std::tuple<Vector<WebCore::FloatRect>, float, float, WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawFocusRingRects; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawFocusRingRects(const Vector<WebCore::FloatRect>& rects, float outlineOffset, float outlineWidth, const WebCore::Color& color)
        : m_arguments(rects, outlineOffset, outlineWidth, color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::FloatRect>&, float, float, const WebCore::Color&> m_arguments;
};

class FillRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillRect(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class FillRectWithColor {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillRectWithColor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FillRectWithColor(const WebCore::FloatRect& rect, const WebCore::Color& color)
        : m_arguments(rect, color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::Color&> m_arguments;
};

class FillRectWithGradient {
public:
    using Arguments = std::tuple<WebCore::DisplayList::FillRectWithGradient>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillRectWithGradient; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillRectWithGradient(const WebCore::DisplayList::FillRectWithGradient& item)
        : m_arguments(item)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DisplayList::FillRectWithGradient&> m_arguments;
};

class FillCompositedRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::Color, WebCore::CompositeOperator, WebCore::BlendMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillCompositedRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FillCompositedRect(const WebCore::FloatRect& rect, const WebCore::Color& color, WebCore::CompositeOperator op, WebCore::BlendMode blendMode)
        : m_arguments(rect, color, op, blendMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::Color&, WebCore::CompositeOperator, WebCore::BlendMode> m_arguments;
};

class FillRoundedRect {
public:
    using Arguments = std::tuple<WebCore::FloatRoundedRect, WebCore::Color, WebCore::BlendMode>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillRoundedRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FillRoundedRect(const WebCore::FloatRoundedRect& rect, const WebCore::Color& color, WebCore::BlendMode blendMode)
        : m_arguments(rect, color, blendMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRoundedRect&, const WebCore::Color&, WebCore::BlendMode> m_arguments;
};

class FillRectWithRoundedHole {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::FloatRoundedRect, WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillRectWithRoundedHole; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FillRectWithRoundedHole(const WebCore::FloatRect& rect, const WebCore::FloatRoundedRect& roundedHoleRect, const WebCore::Color& color)
        : m_arguments(rect, roundedHoleRect, color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::FloatRoundedRect&, const WebCore::Color&> m_arguments;
};

#if ENABLE(INLINE_PATH_DATA)
class FillLine {
public:
    using Arguments = std::tuple<WebCore::PathDataLine>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillLine; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillLine(const WebCore::PathDataLine& line)
        : m_arguments(line)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataLine&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class FillArc {
public:
    using Arguments = std::tuple<WebCore::PathArc>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillArc; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillArc(const WebCore::PathArc& arc)
        : m_arguments(arc)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathArc&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class FillQuadCurve {
public:
    using Arguments = std::tuple<WebCore::PathDataQuadCurve>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillQuadCurve; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillQuadCurve(const WebCore::PathDataQuadCurve& curve)
        : m_arguments(curve)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataQuadCurve&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class FillBezierCurve {
public:
    using Arguments = std::tuple<WebCore::PathDataBezierCurve>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillBezierCurve; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillBezierCurve(const WebCore::PathDataBezierCurve& curve)
        : m_arguments(curve)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataBezierCurve&> m_arguments;
};
#endif

class FillPathSegment {
public:
    using Arguments = std::tuple<WebCore::PathSegment>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillPathSegment; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit FillPathSegment(const WebCore::PathSegment& segment)
        : m_arguments(segment)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathSegment&> m_arguments;
};

class FillPath {
public:
    using Arguments = std::tuple<WebCore::Path>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillPath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillPath(const WebCore::Path& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&> m_arguments;
};

class FillEllipse {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FillEllipse; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FillEllipse(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class ConvertToLuminanceMask {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ConvertToLuminanceMask; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class TransformToColorSpace {
public:
    using Arguments = std::tuple<WebCore::DestinationColorSpace>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_TransformToColorSpace; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit TransformToColorSpace(const WebCore::DestinationColorSpace& colorSpace)
        : m_arguments(colorSpace)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DestinationColorSpace&> m_arguments;
};

#if ENABLE(VIDEO)
class PaintFrameForMedia {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerIdentifier, WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_PaintFrameForMedia; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PaintFrameForMedia(const WebCore::MediaPlayerIdentifier& identifier, const WebCore::FloatRect& destination)
        : m_arguments(identifier, destination)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayerIdentifier&, const WebCore::FloatRect&> m_arguments;
};
#endif

class StrokeRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StrokeRect(const WebCore::FloatRect& rect, float lineWidth)
        : m_arguments(rect, lineWidth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, float> m_arguments;
};

#if ENABLE(INLINE_PATH_DATA)
class StrokeLine {
public:
    using Arguments = std::tuple<WebCore::PathDataLine>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeLine; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokeLine(const WebCore::PathDataLine& line)
        : m_arguments(line)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataLine&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class StrokeLineWithColorAndThickness {
public:
    using Arguments = std::tuple<WebCore::PathDataLine, WebCore::DisplayList::SetInlineStrokeColor, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeLineWithColorAndThickness; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    StrokeLineWithColorAndThickness(const WebCore::PathDataLine& line, const WebCore::DisplayList::SetInlineStrokeColor& color, float thickness)
        : m_arguments(line, color, thickness)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataLine&, const WebCore::DisplayList::SetInlineStrokeColor&, float> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class StrokeArc {
public:
    using Arguments = std::tuple<WebCore::PathArc>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeArc; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokeArc(const WebCore::PathArc& arc)
        : m_arguments(arc)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathArc&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class StrokeQuadCurve {
public:
    using Arguments = std::tuple<WebCore::PathDataQuadCurve>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeQuadCurve; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokeQuadCurve(const WebCore::PathDataQuadCurve& curve)
        : m_arguments(curve)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataQuadCurve&> m_arguments;
};
#endif

#if ENABLE(INLINE_PATH_DATA)
class StrokeBezierCurve {
public:
    using Arguments = std::tuple<WebCore::PathDataBezierCurve>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeBezierCurve; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokeBezierCurve(const WebCore::PathDataBezierCurve& curve)
        : m_arguments(curve)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathDataBezierCurve&> m_arguments;
};
#endif

class StrokePathSegment {
public:
    using Arguments = std::tuple<WebCore::PathSegment>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokePathSegment; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokePathSegment(const WebCore::PathSegment& segment)
        : m_arguments(segment)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PathSegment&> m_arguments;
};

class StrokePath {
public:
    using Arguments = std::tuple<WebCore::Path>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokePath; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokePath(const WebCore::Path& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Path&> m_arguments;
};

class StrokeEllipse {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_StrokeEllipse; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = true;

    explicit StrokeEllipse(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class ClearRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ClearRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClearRect(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class DrawControlPart {
public:
    using Arguments = std::tuple<Ref<WebCore::ControlPart>, WebCore::FloatRoundedRect, float, WebCore::ControlStyle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_DrawControlPart; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawControlPart(const Ref<WebCore::ControlPart>& part, const WebCore::FloatRoundedRect& borderRect, float deviceScaleFactor, const WebCore::ControlStyle& style)
        : m_arguments(part, borderRect, deviceScaleFactor, style)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::ControlPart>&, const WebCore::FloatRoundedRect&, float, const WebCore::ControlStyle&> m_arguments;
};

#if USE(CG)
class ApplyStrokePattern {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ApplyStrokePattern; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(CG)
class ApplyFillPattern {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ApplyFillPattern; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class ApplyDeviceScaleFactor {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_ApplyDeviceScaleFactor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ApplyDeviceScaleFactor(float scaleFactor)
        : m_arguments(scaleFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class FlushContext {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FlushContext; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    explicit FlushContext(const IPC::Semaphore& semaphore)
        : m_arguments(semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&> m_arguments;
};

class FlushContextSync {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_FlushContextSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA) && ENABLE(VIDEO)
class PaintVideoFrame {
public:
    using Arguments = std::tuple<WebKit::SharedVideoFrame, WebCore::FloatRect, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_PaintVideoFrame; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    PaintVideoFrame(WebKit::SharedVideoFrame&& frame, const WebCore::FloatRect& rect, bool shouldDiscardAlpha)
        : m_arguments(WTFMove(frame), rect, shouldDiscardAlpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedVideoFrame&&, const WebCore::FloatRect&, bool> m_arguments;
};
#endif

#if PLATFORM(COCOA) && ENABLE(VIDEO)
class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetSharedVideoFrameSemaphore; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    explicit SetSharedVideoFrameSemaphore(const IPC::Semaphore& semaphore)
        : m_arguments(semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&> m_arguments;
};
#endif

#if PLATFORM(COCOA) && ENABLE(VIDEO)
class SetSharedVideoFrameMemory {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDisplayListRecorder_SetSharedVideoFrameMemory; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    explicit SetSharedVideoFrameMemory(WebKit::SharedMemory::Handle&& storageHandle)
        : m_arguments(WTFMove(storageHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedMemory::Handle&&> m_arguments;
};
#endif

} // namespace RemoteDisplayListRecorder
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
