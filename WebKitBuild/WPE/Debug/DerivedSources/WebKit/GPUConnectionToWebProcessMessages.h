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
#include "GraphicsContextGLIdentifier.h"
#include "MessageNames.h"
#include "RemoteAudioHardwareListenerIdentifier.h"
#include "RemoteRemoteCommandListenerIdentifier.h"
#include "RenderingBackendIdentifier.h"
#include "StreamServerConnection.h"
#if USE(GRAPHICS_LAYER_WC)
#include "WCLayerTreeHostIdentifier.h"
#endif
#include "WebGPUIdentifier.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/GraphicsContextGLAttributes.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/RenderingResourceIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct NowPlayingInfo;
}

namespace WebKit {
struct MediaOverridesForTesting;
struct RemoteAudioSessionConfiguration;
struct RemoteRenderingBackendCreationParameters;
}

namespace Messages {
namespace GPUConnectionToWebProcess {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::GPUConnectionToWebProcess;
}

class CreateRenderingBackend {
public:
    using Arguments = std::tuple<WebKit::RemoteRenderingBackendCreationParameters, IPC::StreamServerConnection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateRenderingBackend; }
    static constexpr bool isSync = false;

    CreateRenderingBackend(const WebKit::RemoteRenderingBackendCreationParameters& creationParameters, IPC::StreamServerConnection::Handle&& connectionHandle)
        : m_arguments(creationParameters, WTFMove(connectionHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteRenderingBackendCreationParameters&, IPC::StreamServerConnection::Handle&&> m_arguments;
};

class ReleaseRenderingBackend {
public:
    using Arguments = std::tuple<WebKit::RenderingBackendIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseRenderingBackend; }
    static constexpr bool isSync = false;

    explicit ReleaseRenderingBackend(const WebKit::RenderingBackendIdentifier& renderingBackendIdentifier)
        : m_arguments(renderingBackendIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RenderingBackendIdentifier&> m_arguments;
};

class ReleaseSerializedImageBuffer {
public:
    using Arguments = std::tuple<WebCore::RenderingResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseSerializedImageBuffer; }
    static constexpr bool isSync = false;

    explicit ReleaseSerializedImageBuffer(const WebCore::RenderingResourceIdentifier& imageBuffer)
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

#if ENABLE(WEBGL)
class CreateGraphicsContextGL {
public:
    using Arguments = std::tuple<WebCore::GraphicsContextGLAttributes, WebKit::GraphicsContextGLIdentifier, WebKit::RenderingBackendIdentifier, IPC::StreamServerConnection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateGraphicsContextGL; }
    static constexpr bool isSync = false;

    CreateGraphicsContextGL(const WebCore::GraphicsContextGLAttributes& attributes, const WebKit::GraphicsContextGLIdentifier& graphicsContextGLIdentifier, const WebKit::RenderingBackendIdentifier& renderingBackendIdentifier, IPC::StreamServerConnection::Handle&& serverConnection)
        : m_arguments(attributes, graphicsContextGLIdentifier, renderingBackendIdentifier, WTFMove(serverConnection))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::GraphicsContextGLAttributes&, const WebKit::GraphicsContextGLIdentifier&, const WebKit::RenderingBackendIdentifier&, IPC::StreamServerConnection::Handle&&> m_arguments;
};
#endif

#if ENABLE(WEBGL)
class ReleaseGraphicsContextGL {
public:
    using Arguments = std::tuple<WebKit::GraphicsContextGLIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseGraphicsContextGL; }
    static constexpr bool isSync = false;

    explicit ReleaseGraphicsContextGL(const WebKit::GraphicsContextGLIdentifier& graphicsContextGLIdentifier)
        : m_arguments(graphicsContextGLIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GraphicsContextGLIdentifier&> m_arguments;
};
#endif

class CreateRemoteGPU {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier, WebKit::RenderingBackendIdentifier, IPC::StreamServerConnection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateRemoteGPU; }
    static constexpr bool isSync = false;

    CreateRemoteGPU(const WebKit::WebGPUIdentifier& identifier, const WebKit::RenderingBackendIdentifier& renderingBackendIdentifier, IPC::StreamServerConnection::Handle&& serverConnection)
        : m_arguments(identifier, renderingBackendIdentifier, WTFMove(serverConnection))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebGPUIdentifier&, const WebKit::RenderingBackendIdentifier&, IPC::StreamServerConnection::Handle&&> m_arguments;
};

class ReleaseRemoteGPU {
public:
    using Arguments = std::tuple<WebKit::WebGPUIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseRemoteGPU; }
    static constexpr bool isSync = false;

    explicit ReleaseRemoteGPU(const WebKit::WebGPUIdentifier& identifier)
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

class ClearNowPlayingInfo {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ClearNowPlayingInfo; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetNowPlayingInfo {
public:
    using Arguments = std::tuple<WebCore::NowPlayingInfo>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_SetNowPlayingInfo; }
    static constexpr bool isSync = false;

    explicit SetNowPlayingInfo(const WebCore::NowPlayingInfo& nowPlayingInfo)
        : m_arguments(nowPlayingInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::NowPlayingInfo&> m_arguments;
};

#if USE(AUDIO_SESSION)
class EnsureAudioSession {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_EnsureAudioSession; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RemoteAudioSessionConfiguration>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class EnsureMediaSessionHelper {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_EnsureMediaSessionHelper; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(VP9)
class EnableVP9Decoders {
public:
    using Arguments = std::tuple<bool, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_EnableVP9Decoders; }
    static constexpr bool isSync = false;

    EnableVP9Decoders(bool shouldEnableVP8Decoder, bool shouldEnableVP9Decoder, bool shouldEnableVP9SWDecoder)
        : m_arguments(shouldEnableVP8Decoder, shouldEnableVP9Decoder, shouldEnableVP9SWDecoder)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, bool> m_arguments;
};
#endif

#if HAVE(VISIBILITY_PROPAGATION_VIEW)
class CreateVisibilityPropagationContextForPage {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateVisibilityPropagationContextForPage; }
    static constexpr bool isSync = false;

    CreateVisibilityPropagationContextForPage(const WebKit::WebPageProxyIdentifier& pageProxyID, const WebCore::PageIdentifier& pageID, bool canShowWhileLocked)
        : m_arguments(pageProxyID, pageID, canShowWhileLocked)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&, bool> m_arguments;
};
#endif

#if HAVE(VISIBILITY_PROPAGATION_VIEW)
class DestroyVisibilityPropagationContextForPage {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_DestroyVisibilityPropagationContextForPage; }
    static constexpr bool isSync = false;

    DestroyVisibilityPropagationContextForPage(const WebKit::WebPageProxyIdentifier& pageProxyID, const WebCore::PageIdentifier& pageID)
        : m_arguments(pageProxyID, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&> m_arguments;
};
#endif

class SetMediaOverridesForTesting {
public:
    using Arguments = std::tuple<WebKit::MediaOverridesForTesting>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_SetMediaOverridesForTesting; }
    static constexpr bool isSync = false;

    explicit SetMediaOverridesForTesting(const WebKit::MediaOverridesForTesting& configuration)
        : m_arguments(configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MediaOverridesForTesting&> m_arguments;
};

class CreateAudioHardwareListener {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioHardwareListenerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateAudioHardwareListener; }
    static constexpr bool isSync = false;

    explicit CreateAudioHardwareListener(const WebKit::RemoteAudioHardwareListenerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioHardwareListenerIdentifier&> m_arguments;
};

class ReleaseAudioHardwareListener {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioHardwareListenerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseAudioHardwareListener; }
    static constexpr bool isSync = false;

    explicit ReleaseAudioHardwareListener(const WebKit::RemoteAudioHardwareListenerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioHardwareListenerIdentifier&> m_arguments;
};

class CreateRemoteCommandListener {
public:
    using Arguments = std::tuple<WebKit::RemoteRemoteCommandListenerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateRemoteCommandListener; }
    static constexpr bool isSync = false;

    explicit CreateRemoteCommandListener(const WebKit::RemoteRemoteCommandListenerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteRemoteCommandListenerIdentifier&> m_arguments;
};

class ReleaseRemoteCommandListener {
public:
    using Arguments = std::tuple<WebKit::RemoteRemoteCommandListenerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseRemoteCommandListener; }
    static constexpr bool isSync = false;

    explicit ReleaseRemoteCommandListener(const WebKit::RemoteRemoteCommandListenerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteRemoteCommandListenerIdentifier&> m_arguments;
};

class ConfigureLoggingChannel {
public:
    using Arguments = std::tuple<String, WTFLogChannelState, WTFLogLevel>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ConfigureLoggingChannel; }
    static constexpr bool isSync = false;

    ConfigureLoggingChannel(const String& channelName, WTFLogChannelState state, WTFLogLevel level)
        : m_arguments(channelName, state, level)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WTFLogChannelState, WTFLogLevel> m_arguments;
};

#if USE(GRAPHICS_LAYER_WC)
class CreateWCLayerTreeHost {
public:
    using Arguments = std::tuple<WebKit::WCLayerTreeHostIdentifier, uint64_t, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_CreateWCLayerTreeHost; }
    static constexpr bool isSync = false;

    CreateWCLayerTreeHost(const WebKit::WCLayerTreeHostIdentifier& identifier, uint64_t nativeWindow, bool usesOffscreenRendering)
        : m_arguments(identifier, nativeWindow, usesOffscreenRendering)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WCLayerTreeHostIdentifier&, uint64_t, bool> m_arguments;
};
#endif

#if USE(GRAPHICS_LAYER_WC)
class ReleaseWCLayerTreeHost {
public:
    using Arguments = std::tuple<WebKit::WCLayerTreeHostIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_ReleaseWCLayerTreeHost; }
    static constexpr bool isSync = false;

    explicit ReleaseWCLayerTreeHost(const WebKit::WCLayerTreeHostIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WCLayerTreeHostIdentifier&> m_arguments;
};
#endif

#if ENABLE(MEDIA_SOURCE)
class EnableMockMediaSource {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUConnectionToWebProcess_EnableMockMediaSource; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

} // namespace GPUConnectionToWebProcess
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
