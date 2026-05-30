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
#include "WebGPUBindGroupDescriptor.h"
#include "WebGPUBindGroupLayoutDescriptor.h"
#include "WebGPUBufferDescriptor.h"
#include "WebGPUCommandEncoderDescriptor.h"
#include "WebGPUComputePipelineDescriptor.h"
#include "WebGPUError.h"
#include "WebGPUExternalTextureDescriptor.h"
#include "WebGPUIdentifier.h"
#include "WebGPUPipelineLayoutDescriptor.h"
#include "WebGPUQuerySetDescriptor.h"
#include "WebGPURenderBundleEncoderDescriptor.h"
#include "WebGPURenderPipelineDescriptor.h"
#include "WebGPUSamplerDescriptor.h"
#include "WebGPUShaderModuleDescriptor.h"
#include "WebGPUTextureDescriptor.h"
#include <WebCore/WebGPUErrorFilter.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteDevice {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteDevice;
}

class Destroy {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_Destroy; }
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

class Destruct {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_Destruct; }
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

class CreateBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPU::BufferDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateBuffer(const WebKit::WebGPU::BufferDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::BufferDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::TextureDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateTexture(const WebKit::WebGPU::TextureDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::TextureDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateSampler {
public:
    using Arguments = std::tuple<WebKit::WebGPU::SamplerDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateSampler; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateSampler(const WebKit::WebGPU::SamplerDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::SamplerDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class ImportExternalTexture {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ExternalTextureDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_ImportExternalTexture; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    ImportExternalTexture(const WebKit::WebGPU::ExternalTextureDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ExternalTextureDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateBindGroupLayout {
public:
    using Arguments = std::tuple<WebKit::WebGPU::BindGroupLayoutDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateBindGroupLayout; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateBindGroupLayout(const WebKit::WebGPU::BindGroupLayoutDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::BindGroupLayoutDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreatePipelineLayout {
public:
    using Arguments = std::tuple<WebKit::WebGPU::PipelineLayoutDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreatePipelineLayout; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreatePipelineLayout(const WebKit::WebGPU::PipelineLayoutDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::PipelineLayoutDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateBindGroup {
public:
    using Arguments = std::tuple<WebKit::WebGPU::BindGroupDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateBindGroup; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateBindGroup(const WebKit::WebGPU::BindGroupDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::BindGroupDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateShaderModule {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ShaderModuleDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateShaderModule; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateShaderModule(const WebKit::WebGPU::ShaderModuleDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ShaderModuleDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateComputePipeline {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ComputePipelineDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateComputePipeline; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateComputePipeline(const WebKit::WebGPU::ComputePipelineDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ComputePipelineDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateRenderPipeline {
public:
    using Arguments = std::tuple<WebKit::WebGPU::RenderPipelineDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateRenderPipeline; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateRenderPipeline(const WebKit::WebGPU::RenderPipelineDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::RenderPipelineDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateComputePipelineAsync {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ComputePipelineDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateComputePipelineAsync; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteDevice_CreateComputePipelineAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    CreateComputePipelineAsync(const WebKit::WebGPU::ComputePipelineDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ComputePipelineDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateRenderPipelineAsync {
public:
    using Arguments = std::tuple<WebKit::WebGPU::RenderPipelineDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateRenderPipelineAsync; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteDevice_CreateRenderPipelineAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    CreateRenderPipelineAsync(const WebKit::WebGPU::RenderPipelineDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::RenderPipelineDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateCommandEncoder {
public:
    using Arguments = std::tuple<std::optional<WebKit::WebGPU::CommandEncoderDescriptor>, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateCommandEncoder; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateCommandEncoder(const std::optional<WebKit::WebGPU::CommandEncoderDescriptor>& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::WebGPU::CommandEncoderDescriptor>&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateRenderBundleEncoder {
public:
    using Arguments = std::tuple<WebKit::WebGPU::RenderBundleEncoderDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateRenderBundleEncoder; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateRenderBundleEncoder(const WebKit::WebGPU::RenderBundleEncoderDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::RenderBundleEncoderDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class CreateQuerySet {
public:
    using Arguments = std::tuple<WebKit::WebGPU::QuerySetDescriptor, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_CreateQuerySet; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    CreateQuerySet(const WebKit::WebGPU::QuerySetDescriptor& descriptor, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::QuerySetDescriptor&, const WebKit::WebGPUIdentifier&> m_arguments;
};

class PushErrorScope {
public:
    using Arguments = std::tuple<WebCore::WebGPU::ErrorFilter>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_PushErrorScope; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    explicit PushErrorScope(const WebCore::WebGPU::ErrorFilter& errorFilter)
        : m_arguments(errorFilter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebGPU::ErrorFilter&> m_arguments;
};

class PopErrorScope {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_PopErrorScope; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = true;
    static constexpr bool isReplyStreamEncodable = true;
    static constexpr bool isStreamBatched = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteDevice_PopErrorScopeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::WebGPU::Error>>;
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_SetLabel; }
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

#if PLATFORM(COCOA) && ENABLE(VIDEO)
class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_SetSharedVideoFrameSemaphore; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_SetSharedVideoFrameMemory; }
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

#if PLATFORM(COCOA) && ENABLE(VIDEO)
class ImportExternalTextureFromPixelBuffer {
public:
    using Arguments = std::tuple<WebKit::WebGPU::ExternalTextureDescriptor, std::optional<WebKit::SharedVideoFrame::Buffer>, WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteDevice_ImportExternalTextureFromPixelBuffer; }
    static constexpr bool isSync = false;
    static constexpr bool isStreamEncodable = false;
    static constexpr bool isStreamBatched = false;

    ImportExternalTextureFromPixelBuffer(const WebKit::WebGPU::ExternalTextureDescriptor& descriptor, std::optional<WebKit::SharedVideoFrame::Buffer>&& sharedBuffer, const WebKit::WebGPUIdentifier& identifier)
        : m_arguments(descriptor, WTFMove(sharedBuffer), identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPU::ExternalTextureDescriptor&, std::optional<WebKit::SharedVideoFrame::Buffer>&&, const WebKit::WebGPUIdentifier&> m_arguments;
};
#endif

} // namespace RemoteDevice
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
