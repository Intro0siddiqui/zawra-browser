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
#include "MarkSurfacesAsVolatileRequestIdentifier.h"
#include "MessageNames.h"
#include "PrepareBackingStoreBuffersData.h"
#include "RenderingUpdateID.h"
#include "ShapeDetectionIdentifier.h"
#include "ShareableBitmap.h"
#include "SharedMemory.h"
#include <WebCore/BarcodeDetectorOptionsInterface.h>
#include <WebCore/BarcodeFormatInterface.h>
#include <WebCore/DecomposedGlyphs.h>
#include <WebCore/DestinationColorSpace.h>
#include <WebCore/FaceDetectorOptionsInterface.h>
#include <WebCore/Filter.h>
#include <WebCore/Font.h>
#include <WebCore/FontCustomPlatformData.h>
#include <WebCore/FontPlatformData.h>
#include <WebCore/Gradient.h>
#include <WebCore/PixelBuffer.h>
#include <WebCore/RenderingMode.h>
#include <WebCore/RenderingResourceIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/Ref.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {
class FloatSize;
class IntPoint;
class IntRect;
enum class PreserveResolution : bool;
enum class AlphaPremultiplication : uint8_t;
enum class PixelFormat : uint8_t;
struct PixelBufferFormat;
}

namespace Messages {
namespace RemoteRenderingBackend {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteRenderingBackend;
}

class CreateImageBuffer {
public:
    using Arguments = std::tuple<WebCore::FloatSize, WebCore::RenderingMode, WebCore::RenderingPurpose, float, WebCore::DestinationColorSpace, WebCore::PixelFormat, WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CreateImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateImageBuffer(const WebCore::FloatSize& logicalSize, const WebCore::RenderingMode& renderingMode, const WebCore::RenderingPurpose& renderingPurpose, float resolutionScale, const WebCore::DestinationColorSpace& colorSpace, WebCore::PixelFormat pixelFormat, const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier)
        : m_arguments(logicalSize, renderingMode, renderingPurpose, resolutionScale, colorSpace, pixelFormat, renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&, const WebCore::RenderingMode&, const WebCore::RenderingPurpose&, float, const WebCore::DestinationColorSpace&, WebCore::PixelFormat, const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class GetPixelBufferForImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::PixelBufferFormat, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_GetPixelBufferForImageBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    GetPixelBufferForImageBuffer(const WebCore::RenderingResourceIdentifier& imageBuffer, const WebCore::PixelBufferFormat& outputFormat, const WebCore::IntRect& srcRect)
        : m_arguments(imageBuffer, outputFormat, srcRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const WebCore::PixelBufferFormat&, const WebCore::IntRect&> m_arguments;
};

class GetPixelBufferForImageBufferWithNewMemory {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebKit::SharedMemory::Handle, WebCore::PixelBufferFormat, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_GetPixelBufferForImageBufferWithNewMemory; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    GetPixelBufferForImageBufferWithNewMemory(const WebCore::RenderingResourceIdentifier& imageBuffer, WebKit::SharedMemory::Handle&& handle, const WebCore::PixelBufferFormat& outputFormat, const WebCore::IntRect& srcRect)
        : m_arguments(imageBuffer, WTFMove(handle), outputFormat, srcRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, WebKit::SharedMemory::Handle&&, const WebCore::PixelBufferFormat&, const WebCore::IntRect&> m_arguments;
};

class DestroyGetPixelBufferSharedMemory {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_DestroyGetPixelBufferSharedMemory; }
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

class PutPixelBufferForImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, Ref<WebCore::PixelBuffer>, WebCore::IntRect, WebCore::IntPoint, WebCore::AlphaPremultiplication>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_PutPixelBufferForImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PutPixelBufferForImageBuffer(const WebCore::RenderingResourceIdentifier& imageBuffer, const Ref<WebCore::PixelBuffer>& pixelBuffer, const WebCore::IntRect& srcRect, const WebCore::IntPoint& destPoint, WebCore::AlphaPremultiplication destFormat)
        : m_arguments(imageBuffer, pixelBuffer, srcRect, destPoint, destFormat)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const Ref<WebCore::PixelBuffer>&, const WebCore::IntRect&, const WebCore::IntPoint&, WebCore::AlphaPremultiplication> m_arguments;
};

class GetShareableBitmapForImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, WebCore::PreserveResolution>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_GetShareableBitmapForImageBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    GetShareableBitmapForImageBuffer(const WebCore::RenderingResourceIdentifier& imageBuffer, WebCore::PreserveResolution preserveResolution)
        : m_arguments(imageBuffer, preserveResolution)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, WebCore::PreserveResolution> m_arguments;
};

class GetFilteredImageForImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier, Ref<WebCore::Filter>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_GetFilteredImageForImageBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    GetFilteredImageForImageBuffer(const WebCore::RenderingResourceIdentifier& imageBuffer, const Ref<WebCore::Filter>& filter)
        : m_arguments(imageBuffer, filter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&, const Ref<WebCore::Filter>&> m_arguments;
};

class CacheNativeImage {
public:
    using Arguments = std::tuple<WebKit::ShareableBitmap::Handle, WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheNativeImage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    CacheNativeImage(WebKit::ShareableBitmap::Handle&& handle, const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier)
        : m_arguments(WTFMove(handle), renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::ShareableBitmap::Handle&&, const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class CacheFont {
public:
    using Arguments = std::tuple<WebCore::Font::Attributes, WebCore::FontPlatformData::Attributes, std::optional<WebCore::RenderingResourceIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheFont; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    CacheFont(const WebCore::Font::Attributes& data, const WebCore::FontPlatformData::Attributes& platformData, const std::optional<WebCore::RenderingResourceIdentifier>& renderingResourceIdentifier)
        : m_arguments(data, platformData, renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Font::Attributes&, const WebCore::FontPlatformData::Attributes&, const std::optional<WebCore::RenderingResourceIdentifier>&> m_arguments;
};

class CacheFontCustomPlatformData {
public:
    using Arguments = std::tuple<Ref<WebCore::FontCustomPlatformData>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheFontCustomPlatformData; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    explicit CacheFontCustomPlatformData(const Ref<WebCore::FontCustomPlatformData>& customPlatformData)
        : m_arguments(customPlatformData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::FontCustomPlatformData>&> m_arguments;
};

class CacheDecomposedGlyphs {
public:
    using Arguments = std::tuple<Ref<WebCore::DecomposedGlyphs>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheDecomposedGlyphs; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    explicit CacheDecomposedGlyphs(const Ref<WebCore::DecomposedGlyphs>& decomposedGlyphs)
        : m_arguments(decomposedGlyphs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::DecomposedGlyphs>&> m_arguments;
};

class CacheGradient {
public:
    using Arguments = std::tuple<Ref<WebCore::Gradient>, WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheGradient; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    CacheGradient(const Ref<WebCore::Gradient>& gradient, const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier)
        : m_arguments(gradient, renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::Gradient>&, const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class CacheFilter {
public:
    using Arguments = std::tuple<Ref<WebCore::Filter>, WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CacheFilter; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    CacheFilter(const Ref<WebCore::Filter>& filter, const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier)
        : m_arguments(filter, renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::Filter>&, const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class ReleaseAllResources {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseAllResources; }
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

class ReleaseAllImageResources {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseAllImageResources; }
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

class ReleaseRenderingResource {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseRenderingResource; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ReleaseRenderingResource(const WebCore::RenderingResourceIdentifier& renderingResourceIdentifier)
        : m_arguments(renderingResourceIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&> m_arguments;
};

#if PLATFORM(COCOA)
class PrepareBuffersForDisplay {
public:
    using Arguments = std::tuple<Vector<WebKit::PrepareBackingStoreBuffersInputData>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_PrepareBuffersForDisplay; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::PrepareBackingStoreBuffersOutputData>>;
    explicit PrepareBuffersForDisplay(const Vector<WebKit::PrepareBackingStoreBuffersInputData>& swapBuffersInput)
        : m_arguments(swapBuffersInput)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::PrepareBackingStoreBuffersInputData>&> m_arguments;
};
#endif

class MarkSurfacesVolatile {
public:
    using Arguments = std::tuple<WebKit::MarkSurfacesAsVolatileRequestIdentifier, Vector<WebCore::RenderingResourceIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_MarkSurfacesVolatile; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MarkSurfacesVolatile(const WebKit::MarkSurfacesAsVolatileRequestIdentifier& requestIdentifier, const Vector<WebCore::RenderingResourceIdentifier>& renderingResourceIdentifiers)
        : m_arguments(requestIdentifier, renderingResourceIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MarkSurfacesAsVolatileRequestIdentifier&, const Vector<WebCore::RenderingResourceIdentifier>&> m_arguments;
};

class FinalizeRenderingUpdate {
public:
    using Arguments = std::tuple<WebKit::RenderingUpdateID>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_FinalizeRenderingUpdate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FinalizeRenderingUpdate(const WebKit::RenderingUpdateID& renderingUpdateID)
        : m_arguments(renderingUpdateID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RenderingUpdateID&> m_arguments;
};

class MoveToSerializedBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_MoveToSerializedBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit MoveToSerializedBuffer(const WebCore::RenderingResourceIdentifier& sourceImageBuffer)
        : m_arguments(sourceImageBuffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class MoveToImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_MoveToImageBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit MoveToImageBuffer(const WebCore::RenderingResourceIdentifier& destinationImageBuffer)
        : m_arguments(destinationImageBuffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class CreateRemoteBarcodeDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier, WebCore::ShapeDetection::BarcodeDetectorOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CreateRemoteBarcodeDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateRemoteBarcodeDetector(const WebKit::ShapeDetectionIdentifier& identifier, const WebCore::ShapeDetection::BarcodeDetectorOptions& barcodeDetectorOptions)
        : m_arguments(identifier, barcodeDetectorOptions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&, const WebCore::ShapeDetection::BarcodeDetectorOptions&> m_arguments;
};

class ReleaseRemoteBarcodeDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseRemoteBarcodeDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ReleaseRemoteBarcodeDetector(const WebKit::ShapeDetectionIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&> m_arguments;
};

class GetRemoteBarcodeDetectorSupportedFormats {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormats; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormatsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::ShapeDetection::BarcodeFormat>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateRemoteFaceDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier, WebCore::ShapeDetection::FaceDetectorOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CreateRemoteFaceDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateRemoteFaceDetector(const WebKit::ShapeDetectionIdentifier& identifier, const WebCore::ShapeDetection::FaceDetectorOptions& faceDetectorOptions)
        : m_arguments(identifier, faceDetectorOptions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&, const WebCore::ShapeDetection::FaceDetectorOptions&> m_arguments;
};

class ReleaseRemoteFaceDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseRemoteFaceDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ReleaseRemoteFaceDetector(const WebKit::ShapeDetectionIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&> m_arguments;
};

class CreateRemoteTextDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_CreateRemoteTextDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit CreateRemoteTextDetector(const WebKit::ShapeDetectionIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&> m_arguments;
};

class ReleaseRemoteTextDetector {
public:
    using Arguments = std::tuple<WebKit::ShapeDetectionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackend_ReleaseRemoteTextDetector; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ReleaseRemoteTextDetector(const WebKit::ShapeDetectionIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ShapeDetectionIdentifier&> m_arguments;
};

} // namespace RemoteRenderingBackend
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
