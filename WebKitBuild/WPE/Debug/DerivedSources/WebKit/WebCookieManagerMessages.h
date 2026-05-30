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
#include <WebCore/Cookie.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace PAL {
class SessionID;
}

namespace WebCore {
enum class HTTPCookieAcceptPolicy : uint8_t;
struct Cookie;
}

namespace WebKit {
enum class SoupCookiePersistentStorageType : bool;
}

namespace Messages {
namespace WebCookieManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebCookieManager;
}

class GetHostnamesWithCookies {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_GetHostnamesWithCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_GetHostnamesWithCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit GetHostnamesWithCookies(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

class DeleteCookiesForHostnames {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_DeleteCookiesForHostnames; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_DeleteCookiesForHostnamesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteCookiesForHostnames(const PAL::SessionID& sessionID, const Vector<String>& hostnames)
        : m_arguments(sessionID, hostnames)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<String>&> m_arguments;
};

class DeleteAllCookies {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_DeleteAllCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_DeleteAllCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit DeleteAllCookies(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

class SetCookie {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<WebCore::Cookie>>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_SetCookie; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_SetCookieReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetCookie(const PAL::SessionID& sessionID, const Vector<WebCore::Cookie>& cookie)
        : m_arguments(sessionID, cookie)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<WebCore::Cookie>&> m_arguments;
};

class SetCookies {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<WebCore::Cookie>, URL, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_SetCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_SetCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetCookies(const PAL::SessionID& sessionID, const Vector<WebCore::Cookie>& cookies, const URL& url, const URL& mainDocumentURL)
        : m_arguments(sessionID, cookies, url, mainDocumentURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<WebCore::Cookie>&, const URL&, const URL&> m_arguments;
};

class GetAllCookies {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_GetAllCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_GetAllCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::Cookie>>;
    explicit GetAllCookies(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

class GetCookies {
public:
    using Arguments = std::tuple<PAL::SessionID, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_GetCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_GetCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::Cookie>>;
    GetCookies(const PAL::SessionID& sessionID, const URL& url)
        : m_arguments(sessionID, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const URL&> m_arguments;
};

class DeleteCookie {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::Cookie>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_DeleteCookie; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_DeleteCookieReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteCookie(const PAL::SessionID& sessionID, const WebCore::Cookie& cookie)
        : m_arguments(sessionID, cookie)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::Cookie&> m_arguments;
};

class DeleteAllCookiesModifiedSince {
public:
    using Arguments = std::tuple<PAL::SessionID, WallTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_DeleteAllCookiesModifiedSince; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_DeleteAllCookiesModifiedSinceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteAllCookiesModifiedSince(const PAL::SessionID& sessionID, const WallTime& time)
        : m_arguments(sessionID, time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WallTime&> m_arguments;
};

class SetHTTPCookieAcceptPolicy {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::HTTPCookieAcceptPolicy>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_SetHTTPCookieAcceptPolicy; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_SetHTTPCookieAcceptPolicyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetHTTPCookieAcceptPolicy(const PAL::SessionID& sessionID, WebCore::HTTPCookieAcceptPolicy policy)
        : m_arguments(sessionID, policy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, WebCore::HTTPCookieAcceptPolicy> m_arguments;
};

class GetHTTPCookieAcceptPolicy {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_GetHTTPCookieAcceptPolicy; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_GetHTTPCookieAcceptPolicyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::HTTPCookieAcceptPolicy>;
    explicit GetHTTPCookieAcceptPolicy(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

class StartObservingCookieChanges {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_StartObservingCookieChanges; }
    static constexpr bool isSync = false;

    explicit StartObservingCookieChanges(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

class StopObservingCookieChanges {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_StopObservingCookieChanges; }
    static constexpr bool isSync = false;

    explicit StopObservingCookieChanges(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

#if USE(SOUP)
class ReplaceCookies {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<WebCore::Cookie>>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_ReplaceCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebCookieManager_ReplaceCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ReplaceCookies(const PAL::SessionID& sessionID, const Vector<WebCore::Cookie>& cookies)
        : m_arguments(sessionID, cookies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<WebCore::Cookie>&> m_arguments;
};
#endif

#if USE(SOUP)
class SetCookiePersistentStorage {
public:
    using Arguments = std::tuple<PAL::SessionID, String, WebKit::SoupCookiePersistentStorageType>;

    static IPC::MessageName name() { return IPC::MessageName::WebCookieManager_SetCookiePersistentStorage; }
    static constexpr bool isSync = false;

    SetCookiePersistentStorage(const PAL::SessionID& sessionID, const String& storagePath, WebKit::SoupCookiePersistentStorageType storageType)
        : m_arguments(sessionID, storagePath, storageType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&, WebKit::SoupCookiePersistentStorageType> m_arguments;
};
#endif

} // namespace WebCookieManager
} // namespace Messages
