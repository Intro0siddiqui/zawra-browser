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
#include "AudioMediaStreamTrackRendererInternalUnitIdentifier.h"
#include "AudioSessionRoutingArbitratorProxy.h"
#include "Connection.h"
#include "GPUProcessConnectionInfo.h"
#include "MessageNames.h"
#include <WebCore/AudioSession.h>
#include <WebCore/PlatformMediaSession.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>


namespace Messages {
namespace GPUProcessConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::GPUProcessConnection;
}

class DidInitialize {
public:
    using Arguments = std::tuple<std::optional<WebKit::GPUProcessConnectionInfo>>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessConnection_DidInitialize; }
    static constexpr bool isSync = false;

    explicit DidInitialize(const std::optional<WebKit::GPUProcessConnectionInfo>& info)
        : m_arguments(info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::GPUProcessConnectionInfo>&> m_arguments;
};

class DidReceiveRemoteCommand {
public:
    using Arguments = std::tuple<WebCore::PlatformMediaSession::RemoteControlCommandType, WebCore::PlatformMediaSession::RemoteCommandArgument>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessConnection_DidReceiveRemoteCommand; }
    static constexpr bool isSync = false;

    DidReceiveRemoteCommand(WebCore::PlatformMediaSession::RemoteControlCommandType type, const WebCore::PlatformMediaSession::RemoteCommandArgument& argument)
        : m_arguments(type, argument)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::PlatformMediaSession::RemoteControlCommandType, const WebCore::PlatformMediaSession::RemoteCommandArgument&> m_arguments;
};

#if ENABLE(ROUTING_ARBITRATION)
class BeginRoutingArbitrationWithCategory {
public:
    using Arguments = std::tuple<WebCore::AudioSession::CategoryType>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessConnection_BeginRoutingArbitrationWithCategory; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcessConnection_BeginRoutingArbitrationWithCategoryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::AudioSessionRoutingArbitratorProxy::RoutingArbitrationError, WebKit::AudioSessionRoutingArbitratorProxy::DefaultRouteChanged>;
    explicit BeginRoutingArbitrationWithCategory(WebCore::AudioSession::CategoryType category)
        : m_arguments(category)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::AudioSession::CategoryType> m_arguments;
};
#endif

#if ENABLE(ROUTING_ARBITRATION)
class EndRoutingArbitration {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessConnection_EndRoutingArbitration; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM) && PLATFORM(COCOA)
class ResetAudioMediaStreamTrackRendererInternalUnit {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessConnection_ResetAudioMediaStreamTrackRendererInternalUnit; }
    static constexpr bool isSync = false;

    explicit ResetAudioMediaStreamTrackRendererInternalUnit(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&> m_arguments;
};
#endif

} // namespace GPUProcessConnection
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
