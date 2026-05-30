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

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "ShareableResource.h"
#include <WebCore/Cookie.h>
#include <WebCore/ResourceLoaderIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace JSC {
enum class MessageLevel : uint8_t;
enum class MessageSource : uint8_t;
}

namespace WebCore {
class RegistrableDomain;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
enum class HTTPCookieAcceptPolicy : uint8_t;
struct MessagePortIdentifier;
struct RTCDataChannelIdentifier;
}

namespace Messages {
namespace NetworkProcessConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkProcessConnection;
}

#if ENABLE(SHAREABLE_RESOURCE)
class DidCacheResource {
public:
    using Arguments = std::tuple<WebCore::ResourceRequest, WebKit::ShareableResource::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_DidCacheResource; }
    static constexpr bool isSync = false;

    DidCacheResource(const WebCore::ResourceRequest& request, WebKit::ShareableResource::Handle&& resource)
        : m_arguments(request, WTFMove(resource))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceRequest&, WebKit::ShareableResource::Handle&&> m_arguments;
};
#endif

class DidFinishPingLoad {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::ResourceError, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_DidFinishPingLoad; }
    static constexpr bool isSync = false;

    DidFinishPingLoad(const WebCore::ResourceLoaderIdentifier& pingLoadIdentifier, const WebCore::ResourceError& error, const WebCore::ResourceResponse& response)
        : m_arguments(pingLoadIdentifier, error, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceError&, const WebCore::ResourceResponse&> m_arguments;
};

class DidFinishPreconnection {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_DidFinishPreconnection; }
    static constexpr bool isSync = false;

    DidFinishPreconnection(const WebCore::ResourceLoaderIdentifier& preconnectionIdentifier, const WebCore::ResourceError& error)
        : m_arguments(preconnectionIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class SetOnLineState {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_SetOnLineState; }
    static constexpr bool isSync = false;

    explicit SetOnLineState(bool isOnLine)
        : m_arguments(isOnLine)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class CookieAcceptPolicyChanged {
public:
    using Arguments = std::tuple<WebCore::HTTPCookieAcceptPolicy>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_CookieAcceptPolicyChanged; }
    static constexpr bool isSync = false;

    explicit CookieAcceptPolicyChanged(WebCore::HTTPCookieAcceptPolicy policy)
        : m_arguments(policy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::HTTPCookieAcceptPolicy> m_arguments;
};

#if HAVE(COOKIE_CHANGE_LISTENER_API)
class CookiesAdded {
public:
    using Arguments = std::tuple<String, Vector<WebCore::Cookie>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_CookiesAdded; }
    static constexpr bool isSync = false;

    CookiesAdded(const String& host, const Vector<WebCore::Cookie>& cookies)
        : m_arguments(host, cookies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<WebCore::Cookie>&> m_arguments;
};
#endif

#if HAVE(COOKIE_CHANGE_LISTENER_API)
class CookiesDeleted {
public:
    using Arguments = std::tuple<String, Vector<WebCore::Cookie>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_CookiesDeleted; }
    static constexpr bool isSync = false;

    CookiesDeleted(const String& host, const Vector<WebCore::Cookie>& cookies)
        : m_arguments(host, cookies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<WebCore::Cookie>&> m_arguments;
};
#endif

#if HAVE(COOKIE_CHANGE_LISTENER_API)
class AllCookiesDeleted {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_AllCookiesDeleted; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(WEB_RTC)
class ConnectToRTCDataChannelRemoteSource {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, WebCore::RTCDataChannelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_ConnectToRTCDataChannelRemoteSource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessConnection_ConnectToRTCDataChannelRemoteSourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<bool>>;
    ConnectToRTCDataChannelRemoteSource(const WebCore::RTCDataChannelIdentifier& source, const WebCore::RTCDataChannelIdentifier& handler)
        : m_arguments(source, handler)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, const WebCore::RTCDataChannelIdentifier&> m_arguments;
};
#endif

class MessagesAvailableForPort {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_MessagesAvailableForPort; }
    static constexpr bool isSync = false;

    explicit MessagesAvailableForPort(const WebCore::MessagePortIdentifier& port)
        : m_arguments(port)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessagePortIdentifier&> m_arguments;
};

class BroadcastConsoleMessage {
public:
    using Arguments = std::tuple<JSC::MessageSource, JSC::MessageLevel, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_BroadcastConsoleMessage; }
    static constexpr bool isSync = false;

    BroadcastConsoleMessage(JSC::MessageSource messageSource, JSC::MessageLevel messageLevel, const String& message)
        : m_arguments(messageSource, messageLevel, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<JSC::MessageSource, JSC::MessageLevel, const String&> m_arguments;
};

class AddAllowedFirstPartyForCookies {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessConnection_AddAllowedFirstPartyForCookies; }
    static constexpr bool isSync = false;

    explicit AddAllowedFirstPartyForCookies(const WebCore::RegistrableDomain& firstPartyForCookies)
        : m_arguments(firstPartyForCookies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&> m_arguments;
};

} // namespace NetworkProcessConnection
} // namespace Messages
