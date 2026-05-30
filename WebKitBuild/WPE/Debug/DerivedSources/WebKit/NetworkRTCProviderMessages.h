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

#if USE(LIBWEBRTC)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DataReference.h"
#include "LibWebRTCResolverIdentifier.h"
#include "MessageNames.h"
#include "RTCNetwork.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/LibWebRTCSocketIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class RegistrableDomain;
}

namespace WebKit {
struct RTCPacketOptions;
}

namespace Messages {
namespace NetworkRTCProvider {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkRTCProvider;
}

class CreateUDPSocket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, WebKit::RTCNetwork::SocketAddress, uint16_t, uint16_t, WebKit::WebPageProxyIdentifier, bool, bool, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_CreateUDPSocket; }
    static constexpr bool isSync = false;

    CreateUDPSocket(const WebCore::LibWebRTCSocketIdentifier& identifier, const WebKit::RTCNetwork::SocketAddress& localAddress, uint16_t minPort, uint16_t maxPort, const WebKit::WebPageProxyIdentifier& pageIdentifier, bool isFirstParty, bool isRelayDisabled, const WebCore::RegistrableDomain& domain)
        : m_arguments(identifier, localAddress, minPort, maxPort, pageIdentifier, isFirstParty, isRelayDisabled, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const WebKit::RTCNetwork::SocketAddress&, uint16_t, uint16_t, const WebKit::WebPageProxyIdentifier&, bool, bool, const WebCore::RegistrableDomain&> m_arguments;
};

class CreateClientTCPSocket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, WebKit::RTCNetwork::SocketAddress, WebKit::RTCNetwork::SocketAddress, String, int, WebKit::WebPageProxyIdentifier, bool, bool, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_CreateClientTCPSocket; }
    static constexpr bool isSync = false;

    CreateClientTCPSocket(const WebCore::LibWebRTCSocketIdentifier& identifier, const WebKit::RTCNetwork::SocketAddress& localAddress, const WebKit::RTCNetwork::SocketAddress& remoteAddress, const String& userAgent, const int& options, const WebKit::WebPageProxyIdentifier& pageIdentifier, bool isFirstParty, bool isRelayDisabled, const WebCore::RegistrableDomain& domain)
        : m_arguments(identifier, localAddress, remoteAddress, userAgent, options, pageIdentifier, isFirstParty, isRelayDisabled, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const WebKit::RTCNetwork::SocketAddress&, const WebKit::RTCNetwork::SocketAddress&, const String&, const int&, const WebKit::WebPageProxyIdentifier&, bool, bool, const WebCore::RegistrableDomain&> m_arguments;
};

class WrapNewTCPConnection {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, WebCore::LibWebRTCSocketIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_WrapNewTCPConnection; }
    static constexpr bool isSync = false;

    WrapNewTCPConnection(const WebCore::LibWebRTCSocketIdentifier& identifier, const WebCore::LibWebRTCSocketIdentifier& newConnectionSocketIdentifier)
        : m_arguments(identifier, newConnectionSocketIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const WebCore::LibWebRTCSocketIdentifier&> m_arguments;
};

class SetPlatformTCPSocketsEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_SetPlatformTCPSocketsEnabled; }
    static constexpr bool isSync = false;

    explicit SetPlatformTCPSocketsEnabled(bool enabled)
        : m_arguments(enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetPlatformUDPSocketsEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_SetPlatformUDPSocketsEnabled; }
    static constexpr bool isSync = false;

    explicit SetPlatformUDPSocketsEnabled(bool enabled)
        : m_arguments(enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class CreateResolver {
public:
    using Arguments = std::tuple<WebKit::LibWebRTCResolverIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_CreateResolver; }
    static constexpr bool isSync = false;

    CreateResolver(const WebKit::LibWebRTCResolverIdentifier& identifier, const String& address)
        : m_arguments(identifier, address)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LibWebRTCResolverIdentifier&, const String&> m_arguments;
};

class StopResolver {
public:
    using Arguments = std::tuple<WebKit::LibWebRTCResolverIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_StopResolver; }
    static constexpr bool isSync = false;

    explicit StopResolver(const WebKit::LibWebRTCResolverIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LibWebRTCResolverIdentifier&> m_arguments;
};

class SendToSocket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, IPC::DataReference, WebKit::RTCNetwork::SocketAddress, WebKit::RTCPacketOptions>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_SendToSocket; }
    static constexpr bool isSync = false;

    SendToSocket(const WebCore::LibWebRTCSocketIdentifier& identifier, const IPC::DataReference& data, const WebKit::RTCNetwork::SocketAddress& address, const WebKit::RTCPacketOptions& options)
        : m_arguments(identifier, data, address, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const IPC::DataReference&, const WebKit::RTCNetwork::SocketAddress&, const WebKit::RTCPacketOptions&> m_arguments;
};

class CloseSocket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_CloseSocket; }
    static constexpr bool isSync = false;

    explicit CloseSocket(const WebCore::LibWebRTCSocketIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&> m_arguments;
};

class SetSocketOption {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, int, int>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkRTCProvider_SetSocketOption; }
    static constexpr bool isSync = false;

    SetSocketOption(const WebCore::LibWebRTCSocketIdentifier& identifier, const int& option, const int& value)
        : m_arguments(identifier, option, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const int&, const int&> m_arguments;
};

} // namespace NetworkRTCProvider
} // namespace Messages

#endif // USE(LIBWEBRTC)
