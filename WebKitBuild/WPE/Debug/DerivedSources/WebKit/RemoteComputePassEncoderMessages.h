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
#include "WebGPUIdentifier.h"
#include <WebCore/WebGPUIntegralTypes.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteComputePassEncoder {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteComputePassEncoder;
}

class Destruct {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_Destruct; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_SetPipeline; }
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

class Dispatch {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Size32, WebCore::WebGPU::Size32, WebCore::WebGPU::Size32>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_Dispatch; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    Dispatch(const WebCore::WebGPU::Size32& workgroupCountX, const WebCore::WebGPU::Size32& workgroupCountY, const WebCore::WebGPU::Size32& workgroupCountZ)
        : m_arguments(workgroupCountX, workgroupCountY, workgroupCountZ)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::Size32&, const WebCore::WebGPU::Size32&, const WebCore::WebGPU::Size32&> m_arguments;
};

class DispatchIndirect {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebCore::WebGPU::Size64>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_DispatchIndirect; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    DispatchIndirect(const WebKit::WebGPUIdentifier& indirectBuffer, const WebCore::WebGPU::Size64& indirectOffset)
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

class End {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_End; }
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

class SetBindGroup {
public:
    using Arguments = std::tuple<WebCore::WebGPU::Index32, WebKit::WebGPUIdentifier, std::optional<Vector<WebCore::WebGPU::BufferDynamicOffset>>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_SetBindGroup; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_PushDebugGroup; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_PopDebugGroup; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_InsertDebugMarker; }
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

class SetLabel {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteComputePassEncoder_SetLabel; }
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

} // namespace RemoteComputePassEncoder
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
