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
#include "WebGPUColor.h"
#include "WebGPUIdentifier.h"
#include <WebCore/WebGPUIndexFormat.h>
#include <WebCore/WebGPUIntegralTypes.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteRenderPassEncoder {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteRenderPassEncoder;
}

class Destruct {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_Destruct; }
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

class SetPipeline {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetPipeline; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SetPipeline(const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&> m_arguments;
};

class SetIndexBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::IndexFormat, std::optional<WebCore::WebGPU::Size64>, std::optional<WebCore::WebGPU::Size64>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetIndexBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SetIndexBuffer(const WebKit::WebGPUIdentifier& identifier, const WebCore::WebGPU::IndexFormat& indexFormat, const std::optional<WebCore::WebGPU::Size64>& offset, const std::optional<WebCore::WebGPU::Size64>& size)
        : m_arguments(identifier, indexFormat, offset, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::IndexFormat&, const std::optional<WebCore::WebGPU::Size64>&, const std::optional<WebCore::WebGPU::Size64>&> m_arguments;
};

class SetVertexBuffer {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Index32, WebKit::WebGPUIdentifier, std::optional<WebCore::WebGPU::Size64>, std::optional<WebCore::WebGPU::Size64>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetVertexBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SetVertexBuffer(const WebCore::WebGPU::Index32& slot, const WebKit::WebGPUIdentifier& identifier, const std::optional<WebCore::WebGPU::Size64>& offset, const std::optional<WebCore::WebGPU::Size64>& size)
        : m_arguments(slot, identifier, offset, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Index32&, const WebKit::WebGPUIdentifier&, const std::optional<WebCore::WebGPU::Size64>&, const std::optional<WebCore::WebGPU::Size64>&> m_arguments;
};

class Draw {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Size32, std::optional<WebCore::WebGPU::Size32>, std::optional<WebCore::WebGPU::Size32>, std::optional<WebCore::WebGPU::Size32>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_Draw; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Draw(const WebCore::WebGPU::Size32& vertexCount, const std::optional<WebCore::WebGPU::Size32>& instanceCount, const std::optional<WebCore::WebGPU::Size32>& firstVertex, const std::optional<WebCore::WebGPU::Size32>& firstInstance)
        : m_arguments(vertexCount, instanceCount, firstVertex, firstInstance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Size32&, const std::optional<WebCore::WebGPU::Size32>&, const std::optional<WebCore::WebGPU::Size32>&, const std::optional<WebCore::WebGPU::Size32>&> m_arguments;
};

class DrawIndexed {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Size32, std::optional<WebCore::WebGPU::Size32>, std::optional<WebCore::WebGPU::Size32>, std::optional<WebCore::WebGPU::SignedOffset32>, std::optional<WebCore::WebGPU::Size32>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_DrawIndexed; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawIndexed(const WebCore::WebGPU::Size32& indexCount, const std::optional<WebCore::WebGPU::Size32>& instanceCount, const std::optional<WebCore::WebGPU::Size32>& firstIndex, const std::optional<WebCore::WebGPU::SignedOffset32>& baseVertex, const std::optional<WebCore::WebGPU::Size32>& firstInstance)
        : m_arguments(indexCount, instanceCount, firstIndex, baseVertex, firstInstance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Size32&, const std::optional<WebCore::WebGPU::Size32>&, const std::optional<WebCore::WebGPU::Size32>&, const std::optional<WebCore::WebGPU::SignedOffset32>&, const std::optional<WebCore::WebGPU::Size32>&> m_arguments;
};

class DrawIndirect {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_DrawIndirect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawIndirect(const WebKit::WebGPUIdentifier& indirectBuffer, const WebCore::WebGPU::Size64& indirectOffset)
        : m_arguments(indirectBuffer, indirectOffset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&> m_arguments;
};

class DrawIndexedIndirect {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_DrawIndexedIndirect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DrawIndexedIndirect(const WebKit::WebGPUIdentifier& indirectBuffer, const WebCore::WebGPU::Size64& indirectOffset)
        : m_arguments(indirectBuffer, indirectOffset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebCore::WebGPU::Size64&> m_arguments;
};

class SetBindGroup {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Index32, WebKit::WebGPUIdentifier, std::optional<Vector<WebCore::WebGPU::BufferDynamicOffset>>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetBindGroup; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SetBindGroup(const WebCore::WebGPU::Index32& index, const WebKit::WebGPUIdentifier& identifier, const std::optional<Vector<WebCore::WebGPU::BufferDynamicOffset>>& dynamicOffsets)
        : m_arguments(index, identifier, dynamicOffsets)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Index32&, const WebKit::WebGPUIdentifier&, const std::optional<Vector<WebCore::WebGPU::BufferDynamicOffset>>&> m_arguments;
};

class PushDebugGroup {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_PushDebugGroup; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_PopDebugGroup; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_InsertDebugMarker; }
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

class SetViewport {
public:
    using Arguments = std::tuple<float, float, float, float, float, float>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetViewport; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SetViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
        : m_arguments(x, y, width, height, minDepth, maxDepth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, float, float, float, float, float> m_arguments;
};

class SetScissorRect {
public:
    using Arguments = std::tuple<WebCore::WebGPU::IntegerCoordinate, WebCore::WebGPU::IntegerCoordinate, WebCore::WebGPU::IntegerCoordinate, WebCore::WebGPU::IntegerCoordinate>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetScissorRect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    SetScissorRect(const WebCore::WebGPU::IntegerCoordinate& x, const WebCore::WebGPU::IntegerCoordinate& y, const WebCore::WebGPU::IntegerCoordinate& width, const WebCore::WebGPU::IntegerCoordinate& height)
        : m_arguments(x, y, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::IntegerCoordinate&, const WebCore::WebGPU::IntegerCoordinate&, const WebCore::WebGPU::IntegerCoordinate&, const WebCore::WebGPU::IntegerCoordinate&> m_arguments;
};

class SetBlendConstant {
public:
    using Arguments = std::tuple<WebKit::WebGPU::Color>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetBlendConstant; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SetBlendConstant(const WebKit::WebGPU::Color& color)
        : m_arguments(color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::Color&> m_arguments;
};

class SetStencilReference {
public:
    using Arguments = std::tuple<WebCore::WebGPU::StencilValue>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetStencilReference; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit SetStencilReference(const WebCore::WebGPU::StencilValue& stencilValue)
        : m_arguments(stencilValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::StencilValue&> m_arguments;
};

class BeginOcclusionQuery {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Size32>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_BeginOcclusionQuery; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit BeginOcclusionQuery(const WebCore::WebGPU::Size32& queryIndex)
        : m_arguments(queryIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Size32&> m_arguments;
};

class EndOcclusionQuery {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_EndOcclusionQuery; }
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

class ExecuteBundles {
public:
    using Arguments = std::tuple<Vector<WebKit::WebGPUIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_ExecuteBundles; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit ExecuteBundles(const Vector<WebKit::WebGPUIdentifier>& bundles)
        : m_arguments(bundles)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::WebGPUIdentifier>&> m_arguments;
};

class End {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_End; }
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

class SetLabel {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderPassEncoder_SetLabel; }
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

} // namespace RemoteRenderPassEncoder
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
