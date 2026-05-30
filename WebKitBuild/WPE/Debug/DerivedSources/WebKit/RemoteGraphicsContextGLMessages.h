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

#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)

#include "ArgumentCoders.h"
#include "ArrayReference.h"
#include "ArrayReferenceTuple.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "RemoteVideoFrameProxy.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#if USE(GRAPHICS_LAYER_WC)
#include "WCContentBufferIdentifier.h"
#endif
#include <WebCore/DestinationColorSpace.h>
#include <WebCore/GraphicsContextGL.h>
#include <WebCore/GraphicsTypesGL.h>
#include <WebCore/IntSize.h>
#include <WebCore/PixelBuffer.h>
#include <WebCore/RenderingResourceIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MachSendRight.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class DMABufObject;
class IntRect;
class IntSize;
struct GraphicsContextGLActiveInfo;
}

namespace Messages {
namespace RemoteGraphicsContextGL {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteGraphicsContextGL;
}

class Reshape {
public:
    using Arguments = std::tuple<int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Reshape; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Reshape(int32_t width, int32_t height)
        : m_arguments(width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t> m_arguments;
};

#if PLATFORM(COCOA)
class PrepareForDisplay {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PrepareForDisplay; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<MachSendRight>;
    explicit PrepareForDisplay(const IPC::Semaphore& finishedFence)
        : m_arguments(finishedFence)
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

#if USE(GRAPHICS_LAYER_WC)
class PrepareForDisplay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PrepareForDisplay; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::WCContentBufferIdentifier>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(GBM)
class PrepareForDisplay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PrepareForDisplay; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DMABufObject>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if !PLATFORM(COCOA) && !USE(GRAPHICS_LAYER_WC) && !USE(GBM)
class PrepareForDisplay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PrepareForDisplay; }
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
#endif

class EnsureExtensionEnabled {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EnsureExtensionEnabled; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit EnsureExtensionEnabled(const String& extension)
        : m_arguments(extension)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class MarkContextChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MarkContextChanged; }
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

class GetErrors {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetErrors; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<GCGLErrorCodeSet>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PaintRenderingResultsToCanvas {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToCanvas; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit PaintRenderingResultsToCanvas(const WebCore::RenderingResourceIdentifier& imageBuffer)
        : m_arguments(imageBuffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&> m_arguments;
};

class PaintCompositedResultsToCanvas {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToCanvas; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit PaintCompositedResultsToCanvas(const WebCore::RenderingResourceIdentifier& imageBuffer)
        : m_arguments(imageBuffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RenderingResourceIdentifier&> m_arguments;
};

#if ENABLE(VIDEO) && PLATFORM(COCOA)
class CopyTextureFromVideoFrame {
public:
    using Arguments = std::tuple<WebKit::SharedVideoFrame, uint32_t, uint32_t, int32_t, uint32_t, uint32_t, uint32_t, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CopyTextureFromVideoFrame; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    CopyTextureFromVideoFrame(WebKit::SharedVideoFrame&& frame, uint32_t texture, uint32_t target, int32_t level, uint32_t internalFormat, uint32_t format, uint32_t type, bool premultiplyAlpha, bool flipY)
        : m_arguments(WTFMove(frame), texture, target, level, internalFormat, format, type, premultiplyAlpha, flipY)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedVideoFrame&&, uint32_t, uint32_t, int32_t, uint32_t, uint32_t, uint32_t, bool, bool> m_arguments;
};
#endif

#if ENABLE(VIDEO) && PLATFORM(COCOA)
class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SetSharedVideoFrameSemaphore; }
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

#if ENABLE(VIDEO) && PLATFORM(COCOA)
class SetSharedVideoFrameMemory {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SetSharedVideoFrameMemory; }
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

#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
class PaintCompositedResultsToVideoFrame {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PaintCompositedResultsToVideoFrame; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::RemoteVideoFrameProxy::Properties>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class SimulateEventForTesting {
public:
    using Arguments = std::tuple<WebCore::GraphicsContextGL::SimulatedEventForTesting>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SimulateEventForTesting; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SimulateEventForTesting(const WebCore::GraphicsContextGL::SimulatedEventForTesting& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::GraphicsContextGL::SimulatedEventForTesting&> m_arguments;
};

class ReadPixelsInline {
public:
    using Arguments = std::tuple<WebCore::IntRect, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ReadPixelsInline; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::IntSize>, IPC::ArrayReference<uint8_t>>;
    ReadPixelsInline(const WebCore::IntRect& rect, uint32_t format, uint32_t type)
        : m_arguments(rect, format, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, uint32_t, uint32_t> m_arguments;
};

class ReadPixelsSharedMemory {
public:
    using Arguments = std::tuple<WebCore::IntRect, uint32_t, uint32_t, WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ReadPixelsSharedMemory; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::IntSize>>;
    ReadPixelsSharedMemory(const WebCore::IntRect& rect, uint32_t format, uint32_t type, WebKit::SharedMemory::Handle&& handle)
        : m_arguments(rect, format, type, WTFMove(handle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, uint32_t, uint32_t, WebKit::SharedMemory::Handle&&> m_arguments;
};

class MultiDrawArraysANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawArraysANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawArraysANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t>& firstsAndCounts)
        : m_arguments(mode, firstsAndCounts)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t>&> m_arguments;
};

class MultiDrawArraysInstancedANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawArraysInstancedANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawArraysInstancedANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>& firstsCountsAandInstanceCounts)
        : m_arguments(mode, firstsCountsAandInstanceCounts)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>&> m_arguments;
};

class MultiDrawElementsANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawElementsANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawElementsANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t>& countsAndOffsets, uint32_t type)
        : m_arguments(mode, countsAndOffsets, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t>&, uint32_t> m_arguments;
};

class MultiDrawElementsInstancedANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawElementsInstancedANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawElementsInstancedANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>& countsOffsetsAndInstanceCounts, uint32_t type)
        : m_arguments(mode, countsOffsetsAndInstanceCounts, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t>&, uint32_t> m_arguments;
};

class MultiDrawArraysInstancedBaseInstanceANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawArraysInstancedBaseInstanceANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawArraysInstancedBaseInstanceANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, uint32_t>& firstsCountsInstanceCountsAndBaseInstances)
        : m_arguments(mode, firstsCountsInstanceCountsAndBaseInstances)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, uint32_t>&> m_arguments;
};

class MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, int32_t, uint32_t>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE(uint32_t mode, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, int32_t, uint32_t>& countsOffsetsInstanceCountsBaseVerticesAndBaseInstances, uint32_t type)
        : m_arguments(mode, countsOffsetsInstanceCountsBaseVerticesAndBaseInstances, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReferenceTuple<int32_t, int32_t, int32_t, int32_t, uint32_t>&, uint32_t> m_arguments;
};

#if PLATFORM(COCOA)
class CreateAndBindEGLImage {
public:
    using Arguments = std::tuple<GCGLenum, WebCore::GraphicsContextGL::EGLImageSource>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateAndBindEGLImage; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t, WebCore::IntSize>;
    CreateAndBindEGLImage(const GCGLenum& target, WebCore::GraphicsContextGL::EGLImageSource&& source)
        : m_arguments(target, WTFMove(source))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const GCGLenum&, WebCore::GraphicsContextGL::EGLImageSource&&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class CreateEGLSync {
public:
    using Arguments = std::tuple<MachSendRight, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateEGLSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isReplyStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    CreateEGLSync(MachSendRight&& syncEvent, uint64_t signalValue)
        : m_arguments(WTFMove(syncEvent), signalValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<MachSendRight&&, uint64_t> m_arguments;
};
#endif

class ActiveTexture {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ActiveTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ActiveTexture(uint32_t texture)
        : m_arguments(texture)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class AttachShader {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_AttachShader; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    AttachShader(uint32_t program, uint32_t shader)
        : m_arguments(program, shader)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BindAttribLocation {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindAttribLocation; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindAttribLocation(uint32_t arg0, uint32_t index, const String& name)
        : m_arguments(arg0, index, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, const String&> m_arguments;
};

class BindBuffer {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindBuffer(uint32_t target, uint32_t arg1)
        : m_arguments(target, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BindFramebuffer {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindFramebuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindFramebuffer(uint32_t target, uint32_t arg1)
        : m_arguments(target, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BindRenderbuffer {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindRenderbuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindRenderbuffer(uint32_t target, uint32_t arg1)
        : m_arguments(target, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BindTexture {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindTexture(uint32_t target, uint32_t arg1)
        : m_arguments(target, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BlendColor {
public:
    using Arguments = std::tuple<float, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendColor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendColor(float red, float green, float blue, float alpha)
        : m_arguments(red, green, blue, alpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float, float, float> m_arguments;
};

class BlendEquation {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendEquation; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit BlendEquation(uint32_t mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BlendEquationSeparate {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendEquationSeparate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendEquationSeparate(uint32_t modeRGB, uint32_t modeAlpha)
        : m_arguments(modeRGB, modeAlpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BlendFunc {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendFunc; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendFunc(uint32_t sfactor, uint32_t dfactor)
        : m_arguments(sfactor, dfactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BlendFuncSeparate {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendFuncSeparate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendFuncSeparate(uint32_t srcRGB, uint32_t dstRGB, uint32_t srcAlpha, uint32_t dstAlpha)
        : m_arguments(srcRGB, dstRGB, srcAlpha, dstAlpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class CheckFramebufferStatus {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CheckFramebufferStatus; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    explicit CheckFramebufferStatus(uint32_t target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class Clear {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Clear; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit Clear(uint32_t mask)
        : m_arguments(mask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class ClearColor {
public:
    using Arguments = std::tuple<float, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearColor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearColor(float red, float green, float blue, float alpha)
        : m_arguments(red, green, blue, alpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float, float, float> m_arguments;
};

class ClearDepth {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearDepth; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClearDepth(float depth)
        : m_arguments(depth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class ClearStencil {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearStencil; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ClearStencil(int32_t s)
        : m_arguments(s)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};

class ColorMask {
public:
    using Arguments = std::tuple<bool, bool, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ColorMask; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ColorMask(bool red, bool green, bool blue, bool alpha)
        : m_arguments(red, green, blue, alpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, bool, bool> m_arguments;
};

class CompileShader {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompileShader; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit CompileShader(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class CopyTexImage2D {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CopyTexImage2D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyTexImage2D(uint32_t target, int32_t level, uint32_t internalformat, int32_t x, int32_t y, int32_t width, int32_t height, int32_t border)
        : m_arguments(target, level, internalformat, x, y, width, height, border)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class CopyTexSubImage2D {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CopyTexSubImage2D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyTexSubImage2D(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t x, int32_t y, int32_t width, int32_t height)
        : m_arguments(target, level, xoffset, yoffset, x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class CreateBuffer {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateFramebuffer {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateFramebuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateProgram {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateProgram; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateRenderbuffer {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateRenderbuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateShader {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateShader; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    explicit CreateShader(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class CreateTexture {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateTexture; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CullFace {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CullFace; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit CullFace(uint32_t mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteBuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteBuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteFramebuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteFramebuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteFramebuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteProgram {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteProgram; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteProgram(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteRenderbuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteRenderbuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteRenderbuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteShader {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteShader; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteShader(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DeleteTexture {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteTexture(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DepthFunc {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DepthFunc; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DepthFunc(uint32_t func)
        : m_arguments(func)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DepthMask {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DepthMask; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DepthMask(bool flag)
        : m_arguments(flag)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class DepthRange {
public:
    using Arguments = std::tuple<float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DepthRange; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DepthRange(float zNear, float zFar)
        : m_arguments(zNear, zFar)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float> m_arguments;
};

class DestroyEGLImage {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DestroyEGLImage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DestroyEGLImage(uint64_t handle)
        : m_arguments(handle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class DetachShader {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DetachShader; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DetachShader(uint32_t arg0, uint32_t arg1)
        : m_arguments(arg0, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class Disable {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Disable; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit Disable(uint32_t cap)
        : m_arguments(cap)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DisableVertexAttribArray {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DisableVertexAttribArray; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DisableVertexAttribArray(uint32_t index)
        : m_arguments(index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DrawArrays {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawArrays; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawArrays(uint32_t mode, int32_t first, int32_t count)
        : m_arguments(mode, first, count)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t> m_arguments;
};

class DrawElements {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawElements; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawElements(uint32_t mode, int32_t count, uint32_t type, uint64_t offset)
        : m_arguments(mode, count, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, uint64_t> m_arguments;
};

class Enable {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Enable; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit Enable(uint32_t cap)
        : m_arguments(cap)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class EnableVertexAttribArray {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EnableVertexAttribArray; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit EnableVertexAttribArray(uint32_t index)
        : m_arguments(index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class Finish {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Finish; }
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

class Flush {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Flush; }
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

class FramebufferRenderbuffer {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_FramebufferRenderbuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FramebufferRenderbuffer(uint32_t target, uint32_t attachment, uint32_t renderbuffertarget, uint32_t arg3)
        : m_arguments(target, attachment, renderbuffertarget, arg3)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class FramebufferTexture2D {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_FramebufferTexture2D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FramebufferTexture2D(uint32_t target, uint32_t attachment, uint32_t textarget, uint32_t arg3, int32_t level)
        : m_arguments(target, attachment, textarget, arg3, level)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, int32_t> m_arguments;
};

class FrontFace {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_FrontFace; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit FrontFace(uint32_t mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GenerateMipmap {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GenerateMipmap; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit GenerateMipmap(uint32_t target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetActiveAttrib {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetActiveAttrib; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, WebCore::GraphicsContextGLActiveInfo>;
    GetActiveAttrib(uint32_t program, uint32_t index)
        : m_arguments(program, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetActiveUniform {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetActiveUniform; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, WebCore::GraphicsContextGLActiveInfo>;
    GetActiveUniform(uint32_t program, uint32_t index)
        : m_arguments(program, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetAttribLocation {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetAttribLocation; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetAttribLocation(uint32_t arg0, const String& name)
        : m_arguments(arg0, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};

class GetBufferParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetBufferParameteri; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetBufferParameteri(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetString {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetString; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetString(uint32_t name)
        : m_arguments(name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetFloatv {
public:
    using Arguments = std::tuple<uint32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetFloatv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<float>>;
    GetFloatv(uint32_t pname, size_t valueSize)
        : m_arguments(pname, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, size_t> m_arguments;
};

class GetIntegerv {
public:
    using Arguments = std::tuple<uint32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetIntegerv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t>>;
    GetIntegerv(uint32_t pname, size_t valueSize)
        : m_arguments(pname, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, size_t> m_arguments;
};

class GetIntegeri_v {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetIntegeri_v; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t, 4>>;
    GetIntegeri_v(uint32_t pname, uint32_t index)
        : m_arguments(pname, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetInteger64 {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetInteger64; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    explicit GetInteger64(uint32_t pname)
        : m_arguments(pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetInteger64i {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetInteger64i; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    GetInteger64i(uint32_t pname, uint32_t index)
        : m_arguments(pname, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetProgrami {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetProgrami; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetProgrami(uint32_t program, uint32_t pname)
        : m_arguments(program, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetBooleanv {
public:
    using Arguments = std::tuple<uint32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetBooleanv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<bool>>;
    GetBooleanv(uint32_t pname, size_t valueSize)
        : m_arguments(pname, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, size_t> m_arguments;
};

class GetFramebufferAttachmentParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetFramebufferAttachmentParameteri; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetFramebufferAttachmentParameteri(uint32_t target, uint32_t attachment, uint32_t pname)
        : m_arguments(target, attachment, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class GetProgramInfoLog {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetProgramInfoLog; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetProgramInfoLog(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetRenderbufferParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetRenderbufferParameteri; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetRenderbufferParameteri(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetShaderi {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetShaderi; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetShaderi(uint32_t arg0, uint32_t pname)
        : m_arguments(arg0, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetShaderInfoLog {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetShaderInfoLog; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetShaderInfoLog(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetShaderPrecisionFormat {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetShaderPrecisionFormat; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t, 2>, GCGLint>;
    GetShaderPrecisionFormat(uint32_t shaderType, uint32_t precisionType)
        : m_arguments(shaderType, precisionType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetShaderSource {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetShaderSource; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetShaderSource(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetTexParameterf {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetTexParameterf; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<float>;
    GetTexParameterf(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetTexParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetTexParameteri; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetTexParameteri(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetUniformfv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformfv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<float>>;
    GetUniformfv(uint32_t program, int32_t location, size_t valueSize)
        : m_arguments(program, location, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, size_t> m_arguments;
};

class GetUniformiv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformiv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t>>;
    GetUniformiv(uint32_t program, int32_t location, size_t valueSize)
        : m_arguments(program, location, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, size_t> m_arguments;
};

class GetUniformuiv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformuiv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<uint32_t>>;
    GetUniformuiv(uint32_t program, int32_t location, size_t valueSize)
        : m_arguments(program, location, valueSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, size_t> m_arguments;
};

class GetUniformLocation {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformLocation; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetUniformLocation(uint32_t arg0, const String& name)
        : m_arguments(arg0, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};

class GetVertexAttribOffset {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetVertexAttribOffset; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    GetVertexAttribOffset(uint32_t index, uint32_t pname)
        : m_arguments(index, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class Hint {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Hint; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Hint(uint32_t target, uint32_t mode)
        : m_arguments(target, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class IsBuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsBuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsEnabled {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsEnabled; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsEnabled(uint32_t cap)
        : m_arguments(cap)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsFramebuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsFramebuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsFramebuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsProgram {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsProgram; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsProgram(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsRenderbuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsRenderbuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsRenderbuffer(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsShader {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsShader; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsShader(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsTexture {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsTexture; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsTexture(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class LineWidth {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_LineWidth; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit LineWidth(float arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class LinkProgram {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_LinkProgram; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit LinkProgram(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class PixelStorei {
public:
    using Arguments = std::tuple<uint32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PixelStorei; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PixelStorei(uint32_t pname, int32_t param)
        : m_arguments(pname, param)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t> m_arguments;
};

class PolygonOffset {
public:
    using Arguments = std::tuple<float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PolygonOffset; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PolygonOffset(float factor, float units)
        : m_arguments(factor, units)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float> m_arguments;
};

class RenderbufferStorage {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_RenderbufferStorage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    RenderbufferStorage(uint32_t target, uint32_t internalformat, int32_t width, int32_t height)
        : m_arguments(target, internalformat, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, int32_t, int32_t> m_arguments;
};

class SampleCoverage {
public:
    using Arguments = std::tuple<float, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SampleCoverage; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SampleCoverage(float value, bool invert)
        : m_arguments(value, invert)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, bool> m_arguments;
};

class Scissor {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Scissor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Scissor(int32_t x, int32_t y, int32_t width, int32_t height)
        : m_arguments(x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class ShaderSource {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ShaderSource; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ShaderSource(uint32_t arg0, const String& arg1)
        : m_arguments(arg0, arg1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};

class StencilFunc {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilFunc; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StencilFunc(uint32_t func, int32_t ref, uint32_t mask)
        : m_arguments(func, ref, mask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t> m_arguments;
};

class StencilFuncSeparate {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, int32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilFuncSeparate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StencilFuncSeparate(uint32_t face, uint32_t func, int32_t ref, uint32_t mask)
        : m_arguments(face, func, ref, mask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, int32_t, uint32_t> m_arguments;
};

class StencilMask {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilMask; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit StencilMask(uint32_t mask)
        : m_arguments(mask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class StencilMaskSeparate {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilMaskSeparate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StencilMaskSeparate(uint32_t face, uint32_t mask)
        : m_arguments(face, mask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class StencilOp {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilOp; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StencilOp(uint32_t fail, uint32_t zfail, uint32_t zpass)
        : m_arguments(fail, zfail, zpass)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class StencilOpSeparate {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_StencilOpSeparate; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    StencilOpSeparate(uint32_t face, uint32_t fail, uint32_t zfail, uint32_t zpass)
        : m_arguments(face, fail, zfail, zpass)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class TexParameterf {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexParameterf; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexParameterf(uint32_t target, uint32_t pname, float param)
        : m_arguments(target, pname, param)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, float> m_arguments;
};

class TexParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexParameteri; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexParameteri(uint32_t target, uint32_t pname, int32_t param)
        : m_arguments(target, pname, param)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, int32_t> m_arguments;
};

class Uniform1f {
public:
    using Arguments = std::tuple<int32_t, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1f(int32_t location, float x)
        : m_arguments(location, x)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, float> m_arguments;
};

class Uniform1fv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1fv(int32_t location, const IPC::ArrayReference<float>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<float>&> m_arguments;
};

class Uniform1i {
public:
    using Arguments = std::tuple<int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1i; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1i(int32_t location, int32_t x)
        : m_arguments(location, x)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t> m_arguments;
};

class Uniform1iv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1iv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1iv(int32_t location, const IPC::ArrayReference<int32_t>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<int32_t>&> m_arguments;
};

class Uniform2f {
public:
    using Arguments = std::tuple<int32_t, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2f(int32_t location, float x, float y)
        : m_arguments(location, x, y)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, float, float> m_arguments;
};

class Uniform2fv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2fv(int32_t location, const IPC::ArrayReference<float>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<float>&> m_arguments;
};

class Uniform2i {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2i; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2i(int32_t location, int32_t x, int32_t y)
        : m_arguments(location, x, y)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t> m_arguments;
};

class Uniform2iv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2iv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2iv(int32_t location, const IPC::ArrayReference<int32_t>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<int32_t>&> m_arguments;
};

class Uniform3f {
public:
    using Arguments = std::tuple<int32_t, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3f(int32_t location, float x, float y, float z)
        : m_arguments(location, x, y, z)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, float, float, float> m_arguments;
};

class Uniform3fv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3fv(int32_t location, const IPC::ArrayReference<float>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<float>&> m_arguments;
};

class Uniform3i {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3i; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3i(int32_t location, int32_t x, int32_t y, int32_t z)
        : m_arguments(location, x, y, z)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class Uniform3iv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3iv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3iv(int32_t location, const IPC::ArrayReference<int32_t>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<int32_t>&> m_arguments;
};

class Uniform4f {
public:
    using Arguments = std::tuple<int32_t, float, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4f(int32_t location, float x, float y, float z, float w)
        : m_arguments(location, x, y, z, w)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, float, float, float, float> m_arguments;
};

class Uniform4fv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4fv(int32_t location, const IPC::ArrayReference<float>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<float>&> m_arguments;
};

class Uniform4i {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4i; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4i(int32_t location, int32_t x, int32_t y, int32_t z, int32_t w)
        : m_arguments(location, x, y, z, w)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class Uniform4iv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4iv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4iv(int32_t location, const IPC::ArrayReference<int32_t>& v)
        : m_arguments(location, v)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<int32_t>&> m_arguments;
};

class UniformMatrix2fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix2fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix2fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& value)
        : m_arguments(location, transpose, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix3fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix3fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix3fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& value)
        : m_arguments(location, transpose, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix4fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix4fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix4fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& value)
        : m_arguments(location, transpose, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UseProgram {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UseProgram; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit UseProgram(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class ValidateProgram {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ValidateProgram; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ValidateProgram(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class VertexAttrib1f {
public:
    using Arguments = std::tuple<uint32_t, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib1f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib1f(uint32_t index, float x)
        : m_arguments(index, x)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, float> m_arguments;
};

class VertexAttrib1fv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<float, 1>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib1fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib1fv(uint32_t index, const IPC::ArrayReference<float, 1>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<float, 1>&> m_arguments;
};

class VertexAttrib2f {
public:
    using Arguments = std::tuple<uint32_t, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib2f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib2f(uint32_t index, float x, float y)
        : m_arguments(index, x, y)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, float, float> m_arguments;
};

class VertexAttrib2fv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<float, 2>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib2fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib2fv(uint32_t index, const IPC::ArrayReference<float, 2>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<float, 2>&> m_arguments;
};

class VertexAttrib3f {
public:
    using Arguments = std::tuple<uint32_t, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib3f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib3f(uint32_t index, float x, float y, float z)
        : m_arguments(index, x, y, z)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, float, float, float> m_arguments;
};

class VertexAttrib3fv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<float, 3>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib3fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib3fv(uint32_t index, const IPC::ArrayReference<float, 3>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<float, 3>&> m_arguments;
};

class VertexAttrib4f {
public:
    using Arguments = std::tuple<uint32_t, float, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib4f; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib4f(uint32_t index, float x, float y, float z, float w)
        : m_arguments(index, x, y, z, w)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, float, float, float, float> m_arguments;
};

class VertexAttrib4fv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<float, 4>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttrib4fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttrib4fv(uint32_t index, const IPC::ArrayReference<float, 4>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<float, 4>&> m_arguments;
};

class VertexAttribPointer {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, bool, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribPointer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribPointer(uint32_t index, int32_t size, uint32_t type, bool normalized, int32_t stride, uint64_t offset)
        : m_arguments(index, size, type, normalized, stride, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, bool, int32_t, uint64_t> m_arguments;
};

class Viewport {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Viewport; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Viewport(int32_t x, int32_t y, int32_t width, int32_t height)
        : m_arguments(x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class BufferData0 {
public:
    using Arguments = std::tuple<uint32_t, uint64_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BufferData0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BufferData0(uint32_t target, uint64_t arg1, uint32_t usage)
        : m_arguments(target, arg1, usage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint64_t, uint32_t> m_arguments;
};

class BufferData1 {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<uint8_t>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BufferData1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BufferData1(uint32_t target, const IPC::ArrayReference<uint8_t>& data, uint32_t usage)
        : m_arguments(target, data, usage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<uint8_t>&, uint32_t> m_arguments;
};

class BufferSubData {
public:
    using Arguments = std::tuple<uint32_t, uint64_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BufferSubData; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BufferSubData(uint32_t target, uint64_t offset, const IPC::ArrayReference<uint8_t>& data)
        : m_arguments(target, offset, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint64_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class ReadPixelsBufferObject {
public:
    using Arguments = std::tuple<WebCore::IntRect, uint32_t, uint32_t, uint64_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ReadPixelsBufferObject; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ReadPixelsBufferObject(const WebCore::IntRect& arg0, uint32_t format, uint32_t type, uint64_t offset, int32_t alignment, int32_t rowLength)
        : m_arguments(arg0, format, type, offset, alignment, rowLength)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, uint32_t, uint32_t, uint64_t, int32_t, int32_t> m_arguments;
};

class TexImage2D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexImage2D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexImage2D0(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t border, uint32_t format, uint32_t type, const IPC::ArrayReference<uint8_t>& pixels)
        : m_arguments(target, level, internalformat, width, height, border, format, type, pixels)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class TexImage2D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexImage2D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexImage2D1(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t border, uint32_t format, uint32_t type, uint64_t offset)
        : m_arguments(target, level, internalformat, width, height, border, format, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t> m_arguments;
};

class TexSubImage2D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexSubImage2D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexSubImage2D0(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t width, int32_t height, uint32_t format, uint32_t type, const IPC::ArrayReference<uint8_t>& pixels)
        : m_arguments(target, level, xoffset, yoffset, width, height, format, type, pixels)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class TexSubImage2D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexSubImage2D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexSubImage2D1(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t width, int32_t height, uint32_t format, uint32_t type, uint64_t offset)
        : m_arguments(target, level, xoffset, yoffset, width, height, format, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t> m_arguments;
};

class CompressedTexImage2D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexImage2D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexImage2D0(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t border, int32_t imageSize, const IPC::ArrayReference<uint8_t>& data)
        : m_arguments(target, level, internalformat, width, height, border, imageSize, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class CompressedTexImage2D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexImage2D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexImage2D1(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t border, int32_t imageSize, uint64_t offset)
        : m_arguments(target, level, internalformat, width, height, border, imageSize, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, uint64_t> m_arguments;
};

class CompressedTexSubImage2D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexSubImage2D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexSubImage2D0(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t width, int32_t height, uint32_t format, int32_t imageSize, const IPC::ArrayReference<uint8_t>& data)
        : m_arguments(target, level, xoffset, yoffset, width, height, format, imageSize, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class CompressedTexSubImage2D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexSubImage2D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexSubImage2D1(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t width, int32_t height, uint32_t format, int32_t imageSize, uint64_t offset)
        : m_arguments(target, level, xoffset, yoffset, width, height, format, imageSize, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, uint64_t> m_arguments;
};

class DrawArraysInstanced {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawArraysInstanced; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawArraysInstanced(uint32_t mode, int32_t first, int32_t count, int32_t primcount)
        : m_arguments(mode, first, count, primcount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t> m_arguments;
};

class DrawElementsInstanced {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, uint64_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawElementsInstanced; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawElementsInstanced(uint32_t mode, int32_t count, uint32_t type, uint64_t offset, int32_t primcount)
        : m_arguments(mode, count, type, offset, primcount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, uint64_t, int32_t> m_arguments;
};

class VertexAttribDivisor {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribDivisor; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribDivisor(uint32_t index, uint32_t divisor)
        : m_arguments(index, divisor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class CreateVertexArray {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateVertexArray; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DeleteVertexArray {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteVertexArray; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteVertexArray(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsVertexArray {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsVertexArray; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsVertexArray(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BindVertexArray {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindVertexArray; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit BindVertexArray(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class CopyBufferSubData {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint64_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CopyBufferSubData; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyBufferSubData(uint32_t readTarget, uint32_t writeTarget, uint64_t readOffset, uint64_t writeOffset, uint64_t arg4)
        : m_arguments(readTarget, writeTarget, readOffset, writeOffset, arg4)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint64_t, uint64_t, uint64_t> m_arguments;
};

class GetBufferSubData {
public:
    using Arguments = std::tuple<uint32_t, uint64_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetBufferSubData; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<uint8_t>>;
    GetBufferSubData(uint32_t target, uint64_t offset, size_t dataSize)
        : m_arguments(target, offset, dataSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint64_t, size_t> m_arguments;
};

class BlitFramebuffer {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlitFramebuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlitFramebuffer(int32_t srcX0, int32_t srcY0, int32_t srcX1, int32_t srcY1, int32_t dstX0, int32_t dstY0, int32_t dstX1, int32_t dstY1, uint32_t mask, uint32_t filter)
        : m_arguments(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t> m_arguments;
};

class FramebufferTextureLayer {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_FramebufferTextureLayer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    FramebufferTextureLayer(uint32_t target, uint32_t attachment, uint32_t texture, int32_t level, int32_t layer)
        : m_arguments(target, attachment, texture, level, layer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, int32_t, int32_t> m_arguments;
};

class InvalidateFramebuffer {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_InvalidateFramebuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    InvalidateFramebuffer(uint32_t target, const IPC::ArrayReference<uint32_t>& attachments)
        : m_arguments(target, attachments)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class InvalidateSubFramebuffer {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<uint32_t>, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_InvalidateSubFramebuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    InvalidateSubFramebuffer(uint32_t target, const IPC::ArrayReference<uint32_t>& attachments, int32_t x, int32_t y, int32_t width, int32_t height)
        : m_arguments(target, attachments, x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<uint32_t>&, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class ReadBuffer {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ReadBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ReadBuffer(uint32_t src)
        : m_arguments(src)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class RenderbufferStorageMultisample {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_RenderbufferStorageMultisample; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    RenderbufferStorageMultisample(uint32_t target, int32_t samples, uint32_t internalformat, int32_t width, int32_t height)
        : m_arguments(target, samples, internalformat, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t> m_arguments;
};

class TexStorage2D {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexStorage2D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexStorage2D(uint32_t target, int32_t levels, uint32_t internalformat, int32_t width, int32_t height)
        : m_arguments(target, levels, internalformat, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t> m_arguments;
};

class TexStorage3D {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexStorage3D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexStorage3D(uint32_t target, int32_t levels, uint32_t internalformat, int32_t width, int32_t height, int32_t depth)
        : m_arguments(target, levels, internalformat, width, height, depth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t> m_arguments;
};

class TexImage3D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexImage3D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexImage3D0(uint32_t target, int32_t level, int32_t internalformat, int32_t width, int32_t height, int32_t depth, int32_t border, uint32_t format, uint32_t type, const IPC::ArrayReference<uint8_t>& pixels)
        : m_arguments(target, level, internalformat, width, height, depth, border, format, type, pixels)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class TexImage3D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexImage3D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexImage3D1(uint32_t target, int32_t level, int32_t internalformat, int32_t width, int32_t height, int32_t depth, int32_t border, uint32_t format, uint32_t type, uint64_t offset)
        : m_arguments(target, level, internalformat, width, height, depth, border, format, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t> m_arguments;
};

class TexSubImage3D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexSubImage3D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexSubImage3D0(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t zoffset, int32_t width, int32_t height, int32_t depth, uint32_t format, uint32_t type, const IPC::ArrayReference<uint8_t>& pixels)
        : m_arguments(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class TexSubImage3D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TexSubImage3D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TexSubImage3D1(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t zoffset, int32_t width, int32_t height, int32_t depth, uint32_t format, uint32_t type, uint64_t offset)
        : m_arguments(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t, uint64_t> m_arguments;
};

class CopyTexSubImage3D {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CopyTexSubImage3D; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyTexSubImage3D(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t zoffset, int32_t x, int32_t y, int32_t width, int32_t height)
        : m_arguments(target, level, xoffset, yoffset, zoffset, x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class CompressedTexImage3D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexImage3D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexImage3D0(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t depth, int32_t border, int32_t imageSize, const IPC::ArrayReference<uint8_t>& data)
        : m_arguments(target, level, internalformat, width, height, depth, border, imageSize, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class CompressedTexImage3D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexImage3D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexImage3D1(uint32_t target, int32_t level, uint32_t internalformat, int32_t width, int32_t height, int32_t depth, int32_t border, int32_t imageSize, uint64_t offset)
        : m_arguments(target, level, internalformat, width, height, depth, border, imageSize, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint64_t> m_arguments;
};

class CompressedTexSubImage3D0 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, IPC::ArrayReference<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexSubImage3D0; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexSubImage3D0(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t zoffset, int32_t width, int32_t height, int32_t depth, uint32_t format, int32_t imageSize, const IPC::ArrayReference<uint8_t>& data)
        : m_arguments(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, const IPC::ArrayReference<uint8_t>&> m_arguments;
};

class CompressedTexSubImage3D1 {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CompressedTexSubImage3D1; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CompressedTexSubImage3D1(uint32_t target, int32_t level, int32_t xoffset, int32_t yoffset, int32_t zoffset, int32_t width, int32_t height, int32_t depth, uint32_t format, int32_t imageSize, uint64_t offset)
        : m_arguments(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, int32_t, uint64_t> m_arguments;
};

class GetFragDataLocation {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetFragDataLocation; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetFragDataLocation(uint32_t program, const String& name)
        : m_arguments(program, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};

class Uniform1ui {
public:
    using Arguments = std::tuple<int32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1ui; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1ui(int32_t location, uint32_t v0)
        : m_arguments(location, v0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, uint32_t> m_arguments;
};

class Uniform2ui {
public:
    using Arguments = std::tuple<int32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2ui; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2ui(int32_t location, uint32_t v0, uint32_t v1)
        : m_arguments(location, v0, v1)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, uint32_t, uint32_t> m_arguments;
};

class Uniform3ui {
public:
    using Arguments = std::tuple<int32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3ui; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3ui(int32_t location, uint32_t v0, uint32_t v1, uint32_t v2)
        : m_arguments(location, v0, v1, v2)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class Uniform4ui {
public:
    using Arguments = std::tuple<int32_t, uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4ui; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4ui(int32_t location, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
        : m_arguments(location, v0, v1, v2, v3)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class Uniform1uiv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform1uiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform1uiv(int32_t location, const IPC::ArrayReference<uint32_t>& data)
        : m_arguments(location, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class Uniform2uiv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform2uiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform2uiv(int32_t location, const IPC::ArrayReference<uint32_t>& data)
        : m_arguments(location, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class Uniform3uiv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform3uiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform3uiv(int32_t location, const IPC::ArrayReference<uint32_t>& data)
        : m_arguments(location, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class Uniform4uiv {
public:
    using Arguments = std::tuple<int32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_Uniform4uiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Uniform4uiv(int32_t location, const IPC::ArrayReference<uint32_t>& data)
        : m_arguments(location, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class UniformMatrix2x3fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix2x3fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix2x3fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix3x2fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix3x2fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix3x2fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix2x4fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix2x4fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix2x4fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix4x2fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix4x2fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix4x2fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix3x4fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix3x4fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix3x4fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class UniformMatrix4x3fv {
public:
    using Arguments = std::tuple<int32_t, bool, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformMatrix4x3fv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformMatrix4x3fv(int32_t location, bool transpose, const IPC::ArrayReference<float>& data)
        : m_arguments(location, transpose, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, bool, const IPC::ArrayReference<float>&> m_arguments;
};

class VertexAttribI4i {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribI4i; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribI4i(uint32_t index, int32_t x, int32_t y, int32_t z, int32_t w)
        : m_arguments(index, x, y, z, w)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, int32_t> m_arguments;
};

class VertexAttribI4iv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<int32_t, 4>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribI4iv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribI4iv(uint32_t index, const IPC::ArrayReference<int32_t, 4>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<int32_t, 4>&> m_arguments;
};

class VertexAttribI4ui {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribI4ui; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribI4ui(uint32_t index, uint32_t x, uint32_t y, uint32_t z, uint32_t w)
        : m_arguments(index, x, y, z, w)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class VertexAttribI4uiv {
public:
    using Arguments = std::tuple<uint32_t, IPC::ArrayReference<uint32_t, 4>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribI4uiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribI4uiv(uint32_t index, const IPC::ArrayReference<uint32_t, 4>& values)
        : m_arguments(index, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const IPC::ArrayReference<uint32_t, 4>&> m_arguments;
};

class VertexAttribIPointer {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_VertexAttribIPointer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    VertexAttribIPointer(uint32_t index, int32_t size, uint32_t type, int32_t stride, uint64_t offset)
        : m_arguments(index, size, type, stride, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, uint64_t> m_arguments;
};

class DrawRangeElements {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, int32_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawRangeElements; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawRangeElements(uint32_t mode, uint32_t start, uint32_t end, int32_t count, uint32_t type, uint64_t offset)
        : m_arguments(mode, start, end, count, type, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, int32_t, uint32_t, uint64_t> m_arguments;
};

class DrawBuffers {
public:
    using Arguments = std::tuple<IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawBuffers; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawBuffers(const IPC::ArrayReference<uint32_t>& bufs)
        : m_arguments(bufs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class ClearBufferiv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, IPC::ArrayReference<int32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearBufferiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearBufferiv(uint32_t buffer, int32_t drawbuffer, const IPC::ArrayReference<int32_t>& values)
        : m_arguments(buffer, drawbuffer, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, const IPC::ArrayReference<int32_t>&> m_arguments;
};

class ClearBufferuiv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearBufferuiv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearBufferuiv(uint32_t buffer, int32_t drawbuffer, const IPC::ArrayReference<uint32_t>& values)
        : m_arguments(buffer, drawbuffer, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class ClearBufferfv {
public:
    using Arguments = std::tuple<uint32_t, int32_t, IPC::ArrayReference<float>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearBufferfv; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearBufferfv(uint32_t buffer, int32_t drawbuffer, const IPC::ArrayReference<float>& values)
        : m_arguments(buffer, drawbuffer, values)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, const IPC::ArrayReference<float>&> m_arguments;
};

class ClearBufferfi {
public:
    using Arguments = std::tuple<uint32_t, int32_t, float, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClearBufferfi; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearBufferfi(uint32_t buffer, int32_t drawbuffer, float depth, int32_t stencil)
        : m_arguments(buffer, drawbuffer, depth, stencil)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, float, int32_t> m_arguments;
};

class CreateQuery {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateQuery; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DeleteQuery {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteQuery; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteQuery(uint32_t query)
        : m_arguments(query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsQuery {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsQuery; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsQuery(uint32_t query)
        : m_arguments(query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BeginQuery {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BeginQuery; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BeginQuery(uint32_t target, uint32_t query)
        : m_arguments(target, query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class EndQuery {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EndQuery; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit EndQuery(uint32_t target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class GetQuery {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetQuery; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetQuery(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetQueryObjectui {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetQueryObjectui; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    GetQueryObjectui(uint32_t query, uint32_t pname)
        : m_arguments(query, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class CreateSampler {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateSampler; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DeleteSampler {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteSampler; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteSampler(uint32_t sampler)
        : m_arguments(sampler)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsSampler {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsSampler; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsSampler(uint32_t sampler)
        : m_arguments(sampler)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BindSampler {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindSampler; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindSampler(uint32_t unit, uint32_t sampler)
        : m_arguments(unit, sampler)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class SamplerParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SamplerParameteri; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SamplerParameteri(uint32_t sampler, uint32_t pname, int32_t param)
        : m_arguments(sampler, pname, param)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, int32_t> m_arguments;
};

class SamplerParameterf {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SamplerParameterf; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SamplerParameterf(uint32_t sampler, uint32_t pname, float param)
        : m_arguments(sampler, pname, param)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, float> m_arguments;
};

class GetSamplerParameterf {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetSamplerParameterf; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<float>;
    GetSamplerParameterf(uint32_t sampler, uint32_t pname)
        : m_arguments(sampler, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetSamplerParameteri {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetSamplerParameteri; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetSamplerParameteri(uint32_t sampler, uint32_t pname)
        : m_arguments(sampler, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class FenceSync {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_FenceSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    FenceSync(uint32_t condition, uint32_t flags)
        : m_arguments(condition, flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class IsSync {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsSync(uint64_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class DeleteSync {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteSync; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteSync(uint64_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class ClientWaitSync {
public:
    using Arguments = std::tuple<uint64_t, uint32_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClientWaitSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    ClientWaitSync(uint64_t arg0, uint32_t flags, uint64_t timeout)
        : m_arguments(arg0, flags, timeout)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint32_t, uint64_t> m_arguments;
};

class WaitSync {
public:
    using Arguments = std::tuple<uint64_t, uint32_t, int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_WaitSync; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    WaitSync(uint64_t arg0, uint32_t flags, int64_t timeout)
        : m_arguments(arg0, flags, timeout)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint32_t, int64_t> m_arguments;
};

class GetSynci {
public:
    using Arguments = std::tuple<uint64_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetSynci; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetSynci(uint64_t arg0, uint32_t pname)
        : m_arguments(arg0, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint32_t> m_arguments;
};

class CreateTransformFeedback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateTransformFeedback; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DeleteTransformFeedback {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteTransformFeedback; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteTransformFeedback(uint32_t id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsTransformFeedback {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsTransformFeedback; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsTransformFeedback(uint32_t id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BindTransformFeedback {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindTransformFeedback; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindTransformFeedback(uint32_t target, uint32_t id)
        : m_arguments(target, id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BeginTransformFeedback {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BeginTransformFeedback; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit BeginTransformFeedback(uint32_t primitiveMode)
        : m_arguments(primitiveMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class EndTransformFeedback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EndTransformFeedback; }
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

class TransformFeedbackVaryings {
public:
    using Arguments = std::tuple<uint32_t, Vector<String>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_TransformFeedbackVaryings; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    TransformFeedbackVaryings(uint32_t program, const Vector<String>& varyings, uint32_t bufferMode)
        : m_arguments(program, varyings, bufferMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const Vector<String>&, uint32_t> m_arguments;
};

class GetTransformFeedbackVarying {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetTransformFeedbackVarying; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::GraphicsContextGLActiveInfo>;
    GetTransformFeedbackVarying(uint32_t program, uint32_t index)
        : m_arguments(program, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class PauseTransformFeedback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PauseTransformFeedback; }
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

class ResumeTransformFeedback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ResumeTransformFeedback; }
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

class BindBufferBase {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindBufferBase; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindBufferBase(uint32_t target, uint32_t index, uint32_t buffer)
        : m_arguments(target, index, buffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class BindBufferRange {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BindBufferRange; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BindBufferRange(uint32_t target, uint32_t index, uint32_t buffer, uint64_t offset, uint64_t arg4)
        : m_arguments(target, index, buffer, offset, arg4)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint64_t, uint64_t> m_arguments;
};

class GetUniformIndices {
public:
    using Arguments = std::tuple<uint32_t, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformIndices; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<uint32_t>>;
    GetUniformIndices(uint32_t program, const Vector<String>& uniformNames)
        : m_arguments(program, uniformNames)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const Vector<String>&> m_arguments;
};

class GetActiveUniforms {
public:
    using Arguments = std::tuple<uint32_t, Vector<uint32_t>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetActiveUniforms; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<int32_t>>;
    GetActiveUniforms(uint32_t program, const Vector<uint32_t>& uniformIndices, uint32_t pname)
        : m_arguments(program, uniformIndices, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const Vector<uint32_t>&, uint32_t> m_arguments;
};

class GetUniformBlockIndex {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetUniformBlockIndex; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    GetUniformBlockIndex(uint32_t program, const String& uniformBlockName)
        : m_arguments(program, uniformBlockName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};

class GetActiveUniformBlockName {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockName; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    GetActiveUniformBlockName(uint32_t program, uint32_t uniformBlockIndex)
        : m_arguments(program, uniformBlockIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class UniformBlockBinding {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_UniformBlockBinding; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    UniformBlockBinding(uint32_t program, uint32_t uniformBlockIndex, uint32_t uniformBlockBinding)
        : m_arguments(program, uniformBlockIndex, uniformBlockBinding)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class GetActiveUniformBlockiv {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetActiveUniformBlockiv; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t>>;
    GetActiveUniformBlockiv(uint32_t program, uint32_t uniformBlockIndex, uint32_t pname, size_t paramsSize)
        : m_arguments(program, uniformBlockIndex, pname, paramsSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, size_t> m_arguments;
};

class GetTranslatedShaderSourceANGLE {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetTranslatedShaderSourceANGLE; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetTranslatedShaderSourceANGLE(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DrawBuffersEXT {
public:
    using Arguments = std::tuple<IPC::ArrayReference<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawBuffersEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DrawBuffersEXT(const IPC::ArrayReference<uint32_t>& bufs)
        : m_arguments(bufs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::ArrayReference<uint32_t>&> m_arguments;
};

class CreateQueryEXT {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_CreateQueryEXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint32_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DeleteQueryEXT {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DeleteQueryEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit DeleteQueryEXT(uint32_t query)
        : m_arguments(query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IsQueryEXT {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_IsQueryEXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsQueryEXT(uint32_t query)
        : m_arguments(query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class BeginQueryEXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BeginQueryEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BeginQueryEXT(uint32_t target, uint32_t query)
        : m_arguments(target, query)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class EndQueryEXT {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EndQueryEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit EndQueryEXT(uint32_t target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class QueryCounterEXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_QueryCounterEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    QueryCounterEXT(uint32_t query, uint32_t target)
        : m_arguments(query, target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetQueryiEXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetQueryiEXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetQueryiEXT(uint32_t target, uint32_t pname)
        : m_arguments(target, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetQueryObjectiEXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetQueryObjectiEXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t>;
    GetQueryObjectiEXT(uint32_t query, uint32_t pname)
        : m_arguments(query, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetQueryObjectui64EXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetQueryObjectui64EXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    GetQueryObjectui64EXT(uint32_t query, uint32_t pname)
        : m_arguments(query, pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class GetInteger64EXT {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetInteger64EXT; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    explicit GetInteger64EXT(uint32_t pname)
        : m_arguments(pname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class EnableiOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EnableiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    EnableiOES(uint32_t target, uint32_t index)
        : m_arguments(target, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class DisableiOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DisableiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DisableiOES(uint32_t target, uint32_t index)
        : m_arguments(target, index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BlendEquationiOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendEquationiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendEquationiOES(uint32_t buf, uint32_t mode)
        : m_arguments(buf, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class BlendEquationSeparateiOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendEquationSeparateiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendEquationSeparateiOES(uint32_t buf, uint32_t modeRGB, uint32_t modeAlpha)
        : m_arguments(buf, modeRGB, modeAlpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class BlendFunciOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendFunciOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendFunciOES(uint32_t buf, uint32_t src, uint32_t dst)
        : m_arguments(buf, src, dst)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t> m_arguments;
};

class BlendFuncSeparateiOES {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlendFuncSeparateiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlendFuncSeparateiOES(uint32_t buf, uint32_t srcRGB, uint32_t dstRGB, uint32_t srcAlpha, uint32_t dstAlpha)
        : m_arguments(buf, srcRGB, dstRGB, srcAlpha, dstAlpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t> m_arguments;
};

class ColorMaskiOES {
public:
    using Arguments = std::tuple<uint32_t, bool, bool, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ColorMaskiOES; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ColorMaskiOES(uint32_t buf, bool red, bool green, bool blue, bool alpha)
        : m_arguments(buf, red, green, blue, alpha)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, bool, bool, bool, bool> m_arguments;
};

class DrawArraysInstancedBaseInstanceANGLE {
public:
    using Arguments = std::tuple<uint32_t, int32_t, int32_t, int32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawArraysInstancedBaseInstanceANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawArraysInstancedBaseInstanceANGLE(uint32_t mode, int32_t first, int32_t count, int32_t instanceCount, uint32_t baseInstance)
        : m_arguments(mode, first, count, instanceCount, baseInstance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, int32_t, int32_t, uint32_t> m_arguments;
};

class DrawElementsInstancedBaseVertexBaseInstanceANGLE {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, uint64_t, int32_t, int32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DrawElementsInstancedBaseVertexBaseInstanceANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawElementsInstancedBaseVertexBaseInstanceANGLE(uint32_t mode, int32_t count, uint32_t type, uint64_t offset, int32_t instanceCount, int32_t baseVertex, uint32_t baseInstance)
        : m_arguments(mode, count, type, offset, instanceCount, baseVertex, baseInstance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, uint64_t, int32_t, int32_t, uint32_t> m_arguments;
};

class ClipControlEXT {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClipControlEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClipControlEXT(uint32_t origin, uint32_t depth)
        : m_arguments(origin, depth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class ProvokingVertexANGLE {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ProvokingVertexANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ProvokingVertexANGLE(uint32_t provokeMode)
        : m_arguments(provokeMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class PolygonModeANGLE {
public:
    using Arguments = std::tuple<uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PolygonModeANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PolygonModeANGLE(uint32_t face, uint32_t mode)
        : m_arguments(face, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t> m_arguments;
};

class PolygonOffsetClampEXT {
public:
    using Arguments = std::tuple<float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PolygonOffsetClampEXT; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    PolygonOffsetClampEXT(float factor, float units, float clamp)
        : m_arguments(factor, units, clamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float, float> m_arguments;
};

class RenderbufferStorageMultisampleANGLE {
public:
    using Arguments = std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_RenderbufferStorageMultisampleANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    RenderbufferStorageMultisampleANGLE(uint32_t target, int32_t samples, uint32_t internalformat, int32_t width, int32_t height)
        : m_arguments(target, samples, internalformat, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, int32_t, uint32_t, int32_t, int32_t> m_arguments;
};

class BlitFramebufferANGLE {
public:
    using Arguments = std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_BlitFramebufferANGLE; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BlitFramebufferANGLE(int32_t srcX0, int32_t srcY0, int32_t srcX1, int32_t srcY1, int32_t dstX0, int32_t dstY0, int32_t dstX1, int32_t dstY1, uint32_t mask, uint32_t filter)
        : m_arguments(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t, uint32_t> m_arguments;
};

class GetInternalformativ {
public:
    using Arguments = std::tuple<uint32_t, uint32_t, uint32_t, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_GetInternalformativ; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::ArrayReference<int32_t>>;
    GetInternalformativ(uint32_t target, uint32_t internalformat, uint32_t pname, size_t paramsSize)
        : m_arguments(target, internalformat, pname, paramsSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, uint32_t, uint32_t, size_t> m_arguments;
};

class SetDrawingBufferColorSpace {
public:
    using Arguments = std::tuple<WebCore::DestinationColorSpace>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_SetDrawingBufferColorSpace; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SetDrawingBufferColorSpace(const WebCore::DestinationColorSpace& arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DestinationColorSpace&> m_arguments;
};

class PaintRenderingResultsToPixelBuffer {
public:
    using Arguments = std::tuple<WebCore::GraphicsContextGL::FlipY>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_PaintRenderingResultsToPixelBuffer; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::PixelBuffer>>;
    explicit PaintRenderingResultsToPixelBuffer(const WebCore::GraphicsContextGL::FlipY& arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::GraphicsContextGL::FlipY&> m_arguments;
};

class DestroyEGLSync {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_DestroyEGLSync; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit DestroyEGLSync(uint64_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class ClientWaitEGLSyncWithFlush {
public:
    using Arguments = std::tuple<uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_ClientWaitEGLSyncWithFlush; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClientWaitEGLSyncWithFlush(uint64_t arg0, uint64_t timeout)
        : m_arguments(arg0, timeout)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint64_t> m_arguments;
};

class EnableRequiredWebXRExtensions {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteGraphicsContextGL_EnableRequiredWebXRExtensions; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace RemoteGraphicsContextGL
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
