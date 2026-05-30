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
#include "MessageNames.h"
#include "WebGPUExtent3D.h"
#include "WebGPUIdentifier.h"
#include "WebGPUImageCopyExternalImage.h"
#include "WebGPUImageCopyTexture.h"
#include "WebGPUImageCopyTextureTagged.h"
#include "WebGPUImageDataLayout.h"
#include <WebCore/WebGPUIntegralTypes.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteQueue {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteQueue;
}

class Destruct {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_Destruct; }
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

class Submit {
public:
    using Arguments = std::tuple<Vector<WebKit::WebGPUIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_Submit; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit Submit(const Vector<WebKit::WebGPUIdentifier>& commandBuffers)
        : m_arguments(commandBuffers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::WebGPUIdentifier>&> m_arguments;
};

class OnSubmittedWorkDone {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_OnSubmittedWorkDone; }
    static constexpr bool isSync = true;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = false;
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

class WriteBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64, Vector<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_WriteBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    WriteBuffer(const WebKit::WebGPUIdentifier& identifier, const WebCore::WebGPU::Size64& bufferOffset, const Vector<uint8_t>& data)
        : m_arguments(identifier, bufferOffset, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&, const Vector<uint8_t>&> m_arguments;
};

class WriteTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ImageCopyTexture, Vector<uint8_t>, WebKit::WebGPU::ImageDataLayout, WebKit::WebGPU::Extent3D>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_WriteTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    WriteTexture(const WebKit::WebGPU::ImageCopyTexture& destination, const Vector<uint8_t>& data, const WebKit::WebGPU::ImageDataLayout& imageDataLayout, const WebKit::WebGPU::Extent3D& size)
        : m_arguments(destination, data, imageDataLayout, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ImageCopyTexture&, const Vector<uint8_t>&, const WebKit::WebGPU::ImageDataLayout&, const WebKit::WebGPU::Extent3D&> m_arguments;
};

class CopyExternalImageToTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ImageCopyExternalImage, WebKit::WebGPU::ImageCopyTextureTagged, WebKit::WebGPU::Extent3D>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_CopyExternalImageToTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyExternalImageToTexture(const WebKit::WebGPU::ImageCopyExternalImage& source, const WebKit::WebGPU::ImageCopyTextureTagged& destination, const WebKit::WebGPU::Extent3D& copySize)
        : m_arguments(source, destination, copySize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ImageCopyExternalImage&, const WebKit::WebGPU::ImageCopyTextureTagged&, const WebKit::WebGPU::Extent3D&> m_arguments;
};

class SetLabel {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteQueue_SetLabel; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SetLabel(const String& label)
        : m_arguments(label)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

} // namespace RemoteQueue
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
