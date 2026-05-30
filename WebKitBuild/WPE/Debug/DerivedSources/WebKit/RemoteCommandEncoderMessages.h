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
#include "WebGPUCommandBufferDescriptor.h"
#include "WebGPUComputePassDescriptor.h"
#include "WebGPUExtent3D.h"
#include "WebGPUIdentifier.h"
#include "WebGPUImageCopyBuffer.h"
#include "WebGPUImageCopyTexture.h"
#include "WebGPURenderPassDescriptor.h"
#include <WebCore/WebGPUIntegralTypes.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteCommandEncoder {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteCommandEncoder;
}

class BeginRenderPass {
public:
    using Arguments = std::tuple<WebKit::WebGPU::RenderPassDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_BeginRenderPass; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BeginRenderPass(const WebKit::WebGPU::RenderPassDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::RenderPassDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class BeginComputePass {
public:
    using Arguments = std::tuple<std::optional<WebKit::WebGPU::ComputePassDescriptor>, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_BeginComputePass; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    BeginComputePass(const std::optional<WebKit::WebGPU::ComputePassDescriptor>& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::WebGPU::ComputePassDescriptor>&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CopyBufferToBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64, WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64, WebCore::WebGPU::Size64>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_CopyBufferToBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyBufferToBuffer(const WebKit::WebGPUIdentifier& source, const WebCore::WebGPU::Size64& sourceOffset, const WebKit::WebGPUIdentifier& destination, const WebCore::WebGPU::Size64& destinationOffset, const WebCore::WebGPU::Size64& size)
        : m_arguments(source, sourceOffset, destination, destinationOffset, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&, const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&, const WebCore::WebGPU::Size64&> m_arguments;
};

class CopyBufferToTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ImageCopyBuffer, WebKit::WebGPU::ImageCopyTexture, WebKit::WebGPU::Extent3D>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_CopyBufferToTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyBufferToTexture(const WebKit::WebGPU::ImageCopyBuffer& source, const WebKit::WebGPU::ImageCopyTexture& destination, const WebKit::WebGPU::Extent3D& copySize)
        : m_arguments(source, destination, copySize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ImageCopyBuffer&, const WebKit::WebGPU::ImageCopyTexture&, const WebKit::WebGPU::Extent3D&> m_arguments;
};

class CopyTextureToBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ImageCopyTexture, WebKit::WebGPU::ImageCopyBuffer, WebKit::WebGPU::Extent3D>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_CopyTextureToBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyTextureToBuffer(const WebKit::WebGPU::ImageCopyTexture& source, const WebKit::WebGPU::ImageCopyBuffer& destination, const WebKit::WebGPU::Extent3D& copySize)
        : m_arguments(source, destination, copySize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ImageCopyTexture&, const WebKit::WebGPU::ImageCopyBuffer&, const WebKit::WebGPU::Extent3D&> m_arguments;
};

class CopyTextureToTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ImageCopyTexture, WebKit::WebGPU::ImageCopyTexture, WebKit::WebGPU::Extent3D>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_CopyTextureToTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CopyTextureToTexture(const WebKit::WebGPU::ImageCopyTexture& source, const WebKit::WebGPU::ImageCopyTexture& destination, const WebKit::WebGPU::Extent3D& copySize)
        : m_arguments(source, destination, copySize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ImageCopyTexture&, const WebKit::WebGPU::ImageCopyTexture&, const WebKit::WebGPU::Extent3D&> m_arguments;
};

class ClearBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64, std::optional<WebCore::WebGPU::Size64>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_ClearBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ClearBuffer(const WebKit::WebGPUIdentifier& buffer, const WebCore::WebGPU::Size64& offset, const std::optional<WebCore::WebGPU::Size64>& size)
        : m_arguments(buffer, offset, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&, const std::optional<WebCore::WebGPU::Size64>&> m_arguments;
};

class Destruct {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_Destruct; }
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

class PushDebugGroup {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_PushDebugGroup; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit PushDebugGroup(const String& groupLabel)
        : m_arguments(groupLabel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class PopDebugGroup {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_PopDebugGroup; }
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

class InsertDebugMarker {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_InsertDebugMarker; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit InsertDebugMarker(const String& markerLabel)
        : m_arguments(markerLabel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class WriteTimestamp {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size32>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_WriteTimestamp; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    WriteTimestamp(const WebKit::WebGPUIdentifier& identifier, const WebCore::WebGPU::Size32& queryIndex)
        : m_arguments(identifier, queryIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size32&> m_arguments;
};

class ResolveQuerySet {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size32, WebCore::WebGPU::Size32, WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_ResolveQuerySet; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ResolveQuerySet(const WebKit::WebGPUIdentifier& identifier, const WebCore::WebGPU::Size32& firstQuery, const WebCore::WebGPU::Size32& queryCount, const WebKit::WebGPUIdentifier& destination, const WebCore::WebGPU::Size64& destinationOffset)
        : m_arguments(identifier, firstQuery, queryCount, destination, destinationOffset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size32&, const WebCore::WebGPU::Size32&, const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&> m_arguments;
};

class Finish {
public:
    using Arguments = std::tuple<WebKit::WebGPU::CommandBufferDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_Finish; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Finish(const WebKit::WebGPU::CommandBufferDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::CommandBufferDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class SetLabel {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCommandEncoder_SetLabel; }
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

} // namespace RemoteCommandEncoder
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
