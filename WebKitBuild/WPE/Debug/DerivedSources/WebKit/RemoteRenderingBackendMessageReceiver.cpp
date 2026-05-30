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
#include "RemoteRenderingBackend.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "MarkSurfacesAsVolatileRequestIdentifier.h" // NOLINT
#if PLATFORM(COCOA)
#include "PrepareBackingStoreBuffersData.h" // NOLINT
#endif
#include "RemoteRenderingBackendMessages.h" // NOLINT
#include "RenderingUpdateID.h" // NOLINT
#include "ShapeDetectionIdentifier.h" // NOLINT
#include "ShareableBitmap.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/AlphaPremultiplication.h> // NOLINT
#include <WebCore/BarcodeDetectorOptionsInterface.h> // NOLINT
#include <WebCore/BarcodeFormatInterface.h> // NOLINT
#include <WebCore/DecomposedGlyphs.h> // NOLINT
#include <WebCore/DestinationColorSpace.h> // NOLINT
#include <WebCore/FaceDetectorOptionsInterface.h> // NOLINT
#include <WebCore/Filter.h> // NOLINT
#include <WebCore/FloatSize.h> // NOLINT
#include <WebCore/Font.h> // NOLINT
#include <WebCore/FontCustomPlatformData.h> // NOLINT
#include <WebCore/FontPlatformData.h> // NOLINT
#include <WebCore/Gradient.h> // NOLINT
#include <WebCore/ImageBufferBackend.h> // NOLINT
#include <WebCore/IntPoint.h> // NOLINT
#include <WebCore/IntRect.h> // NOLINT
#include <WebCore/PixelBuffer.h> // NOLINT
#include <WebCore/PixelBufferFormat.h> // NOLINT
#include <WebCore/RenderingMode.h> // NOLINT
#include <WebCore/RenderingResourceIdentifier.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Ref.h> // NOLINT
#include <wtf/Vector.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteRenderingBackend::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CreateImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CreateImageBuffer>(connection.connection(), decoder, this, &RemoteRenderingBackend::createImageBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::DestroyGetPixelBufferSharedMemory::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::DestroyGetPixelBufferSharedMemory>(connection.connection(), decoder, this, &RemoteRenderingBackend::destroyGetPixelBufferSharedMemory);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::PutPixelBufferForImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::PutPixelBufferForImageBuffer>(connection.connection(), decoder, this, &RemoteRenderingBackend::putPixelBufferForImageBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheNativeImage::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheNativeImage>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheNativeImage);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheFont::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheFont>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheFont);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheFontCustomPlatformData::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheFontCustomPlatformData>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheFontCustomPlatformData);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheDecomposedGlyphs::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheDecomposedGlyphs>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheDecomposedGlyphs);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheGradient::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheGradient>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheGradient);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CacheFilter::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CacheFilter>(connection.connection(), decoder, this, &RemoteRenderingBackend::cacheFilter);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseAllResources::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseAllResources>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseAllResources);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseAllImageResources::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseAllImageResources>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseAllImageResources);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseRenderingResource::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseRenderingResource>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseRenderingResource);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::MarkSurfacesVolatile::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::MarkSurfacesVolatile>(connection.connection(), decoder, this, &RemoteRenderingBackend::markSurfacesVolatile);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::FinalizeRenderingUpdate::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::FinalizeRenderingUpdate>(connection.connection(), decoder, this, &RemoteRenderingBackend::finalizeRenderingUpdate);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::MoveToSerializedBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::MoveToSerializedBuffer>(connection.connection(), decoder, this, &RemoteRenderingBackend::moveToSerializedBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::MoveToImageBuffer::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::MoveToImageBuffer>(connection.connection(), decoder, this, &RemoteRenderingBackend::moveToImageBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CreateRemoteBarcodeDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CreateRemoteBarcodeDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::createRemoteBarcodeDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseRemoteBarcodeDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseRemoteBarcodeDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseRemoteBarcodeDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::GetRemoteBarcodeDetectorSupportedFormats::name())
        return IPC::handleMessageAsync<Messages::RemoteRenderingBackend::GetRemoteBarcodeDetectorSupportedFormats>(connection.connection(), decoder, this, &RemoteRenderingBackend::getRemoteBarcodeDetectorSupportedFormats);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CreateRemoteFaceDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CreateRemoteFaceDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::createRemoteFaceDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseRemoteFaceDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseRemoteFaceDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseRemoteFaceDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::CreateRemoteTextDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::CreateRemoteTextDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::createRemoteTextDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::ReleaseRemoteTextDetector::name())
        return IPC::handleMessage<Messages::RemoteRenderingBackend::ReleaseRemoteTextDetector>(connection.connection(), decoder, this, &RemoteRenderingBackend::releaseRemoteTextDetector);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer>(connection, decoder, this, &RemoteRenderingBackend::getPixelBufferForImageBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory::name())
        return IPC::handleMessageSynchronous<Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory>(connection, decoder, this, &RemoteRenderingBackend::getPixelBufferForImageBufferWithNewMemory);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer>(connection, decoder, this, &RemoteRenderingBackend::getShareableBitmapForImageBuffer);
    if (decoder.messageName() == Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer>(connection, decoder, this, &RemoteRenderingBackend::getFilteredImageForImageBuffer);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteRenderingBackend::PrepareBuffersForDisplay::name())
        return IPC::handleMessageSynchronous<Messages::RemoteRenderingBackend::PrepareBuffersForDisplay>(connection, decoder, this, &RemoteRenderingBackend::prepareBuffersForDisplay);
#endif
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CreateImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CreateImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_GetPixelBufferForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_GetPixelBufferForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_GetPixelBufferForImageBufferWithNewMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_GetPixelBufferForImageBufferWithNewMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_DestroyGetPixelBufferSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::DestroyGetPixelBufferSharedMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_PutPixelBufferForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::PutPixelBufferForImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_GetShareableBitmapForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_GetShareableBitmapForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_GetFilteredImageForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_GetFilteredImageForImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheNativeImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheNativeImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheFont>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheFont::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheFontCustomPlatformData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheFontCustomPlatformData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheDecomposedGlyphs>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheDecomposedGlyphs::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheGradient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheGradient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CacheFilter>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CacheFilter::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseAllResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseAllResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseAllImageResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseAllImageResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseRenderingResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseRenderingResource::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_PrepareBuffersForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::PrepareBuffersForDisplay::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_PrepareBuffersForDisplay>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::PrepareBuffersForDisplay::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_MarkSurfacesVolatile>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::MarkSurfacesVolatile::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_FinalizeRenderingUpdate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::FinalizeRenderingUpdate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_MoveToSerializedBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::MoveToSerializedBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_MoveToImageBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::MoveToImageBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CreateRemoteBarcodeDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CreateRemoteBarcodeDetector::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseRemoteBarcodeDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseRemoteBarcodeDetector::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormats>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetRemoteBarcodeDetectorSupportedFormats::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormats>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::GetRemoteBarcodeDetectorSupportedFormats::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CreateRemoteFaceDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CreateRemoteFaceDetector::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseRemoteFaceDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseRemoteFaceDetector::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_CreateRemoteTextDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::CreateRemoteTextDetector::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteRenderingBackend_ReleaseRemoteTextDetector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteRenderingBackend::ReleaseRemoteTextDetector::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS)
