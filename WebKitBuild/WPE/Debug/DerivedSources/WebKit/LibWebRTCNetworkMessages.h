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
#include "MessageNames.h"
#include "RTCNetwork.h"
#include <WebCore/LibWebRTCSocketIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace LibWebRTCNetwork {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::LibWebRTCNetwork;
}

class SignalReadPacket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, IPC::DataReference, WebKit::RTCNetwork::IPAddress, uint16_t, int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalReadPacket; }
    static constexpr bool isSync = false;

    SignalReadPacket(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier, const IPC::DataReference& data, const WebKit::RTCNetwork::IPAddress& address, uint16_t port, int64_t timestamp)
        : m_arguments(socketIdentifier, data, address, port, timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const IPC::DataReference&, const WebKit::RTCNetwork::IPAddress&, uint16_t, int64_t> m_arguments;
};

class SignalSentPacket {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, int, int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalSentPacket; }
    static constexpr bool isSync = false;

    SignalSentPacket(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier, const int& packetSize, int64_t timestamp)
        : m_arguments(socketIdentifier, packetSize, timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const int&, int64_t> m_arguments;
};

class SignalAddressReady {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, WebKit::RTCNetwork::SocketAddress>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalAddressReady; }
    static constexpr bool isSync = false;

    SignalAddressReady(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier, const WebKit::RTCNetwork::SocketAddress& address)
        : m_arguments(socketIdentifier, address)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const WebKit::RTCNetwork::SocketAddress&> m_arguments;
};

class SignalConnect {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalConnect; }
    static constexpr bool isSync = false;

    explicit SignalConnect(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier)
        : m_arguments(socketIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&> m_arguments;
};

class SignalClose {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, int>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalClose; }
    static constexpr bool isSync = false;

    SignalClose(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier, const int& error)
        : m_arguments(socketIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const int&> m_arguments;
};

class SignalUsedInterface {
public:
    using Arguments = std::tuple<WebCore::LibWebRTCSocketIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCNetwork_SignalUsedInterface; }
    static constexpr bool isSync = false;

    SignalUsedInterface(const WebCore::LibWebRTCSocketIdentifier& socketIdentifier, const String& interfaceName)
        : m_arguments(socketIdentifier, interfaceName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LibWebRTCSocketIdentifier&, const String&> m_arguments;
};

} // namespace LibWebRTCNetwork
} // namespace Messages

#endif // USE(LIBWEBRTC)
