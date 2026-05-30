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
#include "DataReference.h"
#include "DownloadID.h"
#include "MessageNames.h"
#include "NavigatingToAppBoundDomain.h"
#include "NetworkResourceLoadIdentifier.h"
#include "SandboxExtension.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/AdvancedPrivacyProtections.h>
#include <WebCore/BlobPart.h>
#include <WebCore/Cookie.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/MessageWithMessagePorts.h>
#include <WebCore/NetworkLoadInformation.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceLoadStatistics.h>
#include <WebCore/ResourceLoaderIdentifier.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/SecurityOriginData.h>
#include <WebCore/WebSocketIdentifier.h>
#include <optional>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/OptionSet.h>
#include <wtf/Seconds.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class MockContentFilterSettings;
class NetworkLoadMetrics;
class RegistrableDomain;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
enum class ApplyTrackingPrevention : bool;
enum class IncludeSecureCookies : bool;
enum class ShouldRelaxThirdPartyCookieBlocking : bool;
enum class StorageAccessScope : bool;
enum class LoadSchedulingMode : uint8_t;
enum class StoredCredentialsPolicy : uint8_t;
struct ClientOrigin;
struct Cookie;
struct CookieStoreGetOptions;
struct MessagePortIdentifier;
struct MessageWithMessagePorts;
struct PolicyContainer;
struct RTCDataChannelIdentifier;
struct RequestStorageAccessResult;
struct SameSiteInfo;
}

namespace WebKit {
class NetworkResourceLoadParameters;
}

namespace Messages {
namespace NetworkConnectionToWebProcess {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkConnectionToWebProcess;
}

class ScheduleResourceLoad {
public:
    using Arguments = std::tuple<WebKit::NetworkResourceLoadParameters, std::optional<WebKit::NetworkResourceLoadIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ScheduleResourceLoad; }
    static constexpr bool isSync = false;

    ScheduleResourceLoad(const WebKit::NetworkResourceLoadParameters& resourceLoadParameters, const std::optional<WebKit::NetworkResourceLoadIdentifier>& existingLoaderToResume)
        : m_arguments(resourceLoadParameters, existingLoaderToResume)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::NetworkResourceLoadParameters&, const std::optional<WebKit::NetworkResourceLoadIdentifier>&> m_arguments;
};

class PerformSynchronousLoad {
public:
    using Arguments = std::tuple<WebKit::NetworkResourceLoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PerformSynchronousLoad; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceError, WebCore::ResourceResponse, Vector<uint8_t>>;
    explicit PerformSynchronousLoad(const WebKit::NetworkResourceLoadParameters& resourceLoadParameters)
        : m_arguments(resourceLoadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::NetworkResourceLoadParameters&> m_arguments;
};

class TestProcessIncomingSyncMessagesWhenWaitingForSyncReply {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit TestProcessIncomingSyncMessagesWhenWaitingForSyncReply(const WebKit::WebPageProxyIdentifier& pageID)
        : m_arguments(pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&> m_arguments;
};

class LoadPing {
public:
    using Arguments = std::tuple<WebKit::NetworkResourceLoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_LoadPing; }
    static constexpr bool isSync = false;

    explicit LoadPing(const WebKit::NetworkResourceLoadParameters& resourceLoadParameters)
        : m_arguments(resourceLoadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::NetworkResourceLoadParameters&> m_arguments;
};

class RemoveLoadIdentifier {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RemoveLoadIdentifier; }
    static constexpr bool isSync = false;

    explicit RemoveLoadIdentifier(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier)
        : m_arguments(resourceLoadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

class PageLoadCompleted {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PageLoadCompleted; }
    static constexpr bool isSync = false;

    explicit PageLoadCompleted(const WebCore::PageIdentifier& webPageID)
        : m_arguments(webPageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&> m_arguments;
};

class BrowsingContextRemoved {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_BrowsingContextRemoved; }
    static constexpr bool isSync = false;

    BrowsingContextRemoved(const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::PageIdentifier& webPageID, const WebCore::FrameIdentifier& webFrameID)
        : m_arguments(webPageProxyID, webPageID, webFrameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&, const WebCore::FrameIdentifier&> m_arguments;
};

class PrefetchDNS {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PrefetchDNS; }
    static constexpr bool isSync = false;

    explicit PrefetchDNS(const String& hostname)
        : m_arguments(hostname)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SendH2Ping {
public:
    using Arguments = std::tuple<WebKit::NetworkResourceLoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SendH2Ping; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_SendH2PingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Seconds, WebCore::ResourceError>>;
    explicit SendH2Ping(const WebKit::NetworkResourceLoadParameters& parameters)
        : m_arguments(parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::NetworkResourceLoadParameters&> m_arguments;
};

class PreconnectTo {
public:
    using Arguments = std::tuple<std::optional<WebCore::ResourceLoaderIdentifier>, WebKit::NetworkResourceLoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PreconnectTo; }
    static constexpr bool isSync = false;

    PreconnectTo(const std::optional<WebCore::ResourceLoaderIdentifier>& preconnectionIdentifier, const WebKit::NetworkResourceLoadParameters& loadParameters)
        : m_arguments(preconnectionIdentifier, loadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ResourceLoaderIdentifier>&, const WebKit::NetworkResourceLoadParameters&> m_arguments;
};

class IsResourceLoadFinished {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_IsResourceLoadFinished; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_IsResourceLoadFinishedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsResourceLoadFinished(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier)
        : m_arguments(resourceLoadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

class StartDownload {
public:
    using Arguments = std::tuple<WebKit::DownloadID, WebCore::ResourceRequest, std::optional<WebKit::NavigatingToAppBoundDomain>, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_StartDownload; }
    static constexpr bool isSync = false;

    StartDownload(const WebKit::DownloadID& downloadID, const WebCore::ResourceRequest& request, const std::optional<WebKit::NavigatingToAppBoundDomain>& isNavigatingToAppBoundDomain, const String& suggestedName)
        : m_arguments(downloadID, request, isNavigatingToAppBoundDomain, suggestedName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DownloadID&, const WebCore::ResourceRequest&, const std::optional<WebKit::NavigatingToAppBoundDomain>&, const String&> m_arguments;
};

class ConvertMainResourceLoadToDownload {
public:
    using Arguments = std::tuple<std::optional<WebCore::ResourceLoaderIdentifier>, WebKit::DownloadID, WebCore::ResourceRequest, WebCore::ResourceResponse, std::optional<WebKit::NavigatingToAppBoundDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ConvertMainResourceLoadToDownload; }
    static constexpr bool isSync = false;

    ConvertMainResourceLoadToDownload(const std::optional<WebCore::ResourceLoaderIdentifier>& mainResourceLoadIdentifier, const WebKit::DownloadID& downloadID, const WebCore::ResourceRequest& request, const WebCore::ResourceResponse& response, const std::optional<WebKit::NavigatingToAppBoundDomain>& isNavigatingToAppBoundDomain)
        : m_arguments(mainResourceLoadIdentifier, downloadID, request, response, isNavigatingToAppBoundDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ResourceLoaderIdentifier>&, const WebKit::DownloadID&, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, const std::optional<WebKit::NavigatingToAppBoundDomain>&> m_arguments;
};

class CookiesForDOM {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CookiesForDOM; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, bool>;
    CookiesForDOM(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID, WebCore::IncludeSecureCookies includeSecureCookies, WebCore::ApplyTrackingPrevention applyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, includeSecureCookies, applyTrackingPrevention, shouldRelaxThirdPartyCookieBlocking)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking> m_arguments;
};

class SetCookiesFromDOM {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::ApplyTrackingPrevention, String, WebCore::ShouldRelaxThirdPartyCookieBlocking>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetCookiesFromDOM; }
    static constexpr bool isSync = false;

    SetCookiesFromDOM(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID, WebCore::ApplyTrackingPrevention applyTrackingPrevention, const String& cookieString, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, applyTrackingPrevention, cookieString, shouldRelaxThirdPartyCookieBlocking)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&, WebCore::ApplyTrackingPrevention, const String&, WebCore::ShouldRelaxThirdPartyCookieBlocking> m_arguments;
};

class CookieRequestHeaderFieldValue {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, std::optional<WebCore::FrameIdentifier>, std::optional<WebCore::PageIdentifier>, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CookieRequestHeaderFieldValue; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, bool>;
    CookieRequestHeaderFieldValue(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const std::optional<WebCore::FrameIdentifier>& frameID, const std::optional<WebCore::PageIdentifier>& pageID, WebCore::IncludeSecureCookies includeSecureCookies, WebCore::ApplyTrackingPrevention applyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, includeSecureCookies, applyTrackingPrevention, shouldRelaxThirdPartyCookieBlocking)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const std::optional<WebCore::FrameIdentifier>&, const std::optional<WebCore::PageIdentifier>&, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking> m_arguments;
};

class GetRawCookies {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, std::optional<WebCore::FrameIdentifier>, std::optional<WebCore::PageIdentifier>, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_GetRawCookies; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::Cookie>>;
    GetRawCookies(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const std::optional<WebCore::FrameIdentifier>& frameID, const std::optional<WebCore::PageIdentifier>& pageID, WebCore::ApplyTrackingPrevention applyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, applyTrackingPrevention, shouldRelaxThirdPartyCookieBlocking)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const std::optional<WebCore::FrameIdentifier>&, const std::optional<WebCore::PageIdentifier>&, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking> m_arguments;
};

class SetRawCookie {
public:
    using Arguments = std::tuple<WebCore::Cookie>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetRawCookie; }
    static constexpr bool isSync = false;

    explicit SetRawCookie(const WebCore::Cookie& cookie)
        : m_arguments(cookie)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Cookie&> m_arguments;
};

class DeleteCookie {
public:
    using Arguments = std::tuple<URL, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_DeleteCookie; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_DeleteCookieReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteCookie(const URL& url, const String& cookieName)
        : m_arguments(url, cookieName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const String&> m_arguments;
};

class DomCookiesForHost {
public:
    using Arguments = std::tuple<URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_DomCookiesForHost; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::Cookie>>;
    explicit DomCookiesForHost(const URL& host)
        : m_arguments(host)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&> m_arguments;
};

class CookiesForDOMAsync {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking, WebCore::CookieStoreGetOptions>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CookiesForDOMAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_CookiesForDOMAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<Vector<WebCore::Cookie>>>;
    CookiesForDOMAsync(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID, WebCore::IncludeSecureCookies includeSecureCookies, WebCore::ApplyTrackingPrevention applyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking, const WebCore::CookieStoreGetOptions& options)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, includeSecureCookies, applyTrackingPrevention, shouldRelaxThirdPartyCookieBlocking, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&, WebCore::IncludeSecureCookies, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking, const WebCore::CookieStoreGetOptions&> m_arguments;
};

class SetCookieFromDOMAsync {
public:
    using Arguments = std::tuple<URL, WebCore::SameSiteInfo, URL, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking, WebCore::Cookie>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetCookieFromDOMAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_SetCookieFromDOMAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    SetCookieFromDOMAsync(const URL& firstParty, const WebCore::SameSiteInfo& sameSiteInfo, const URL& url, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID, WebCore::ApplyTrackingPrevention applyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking, const WebCore::Cookie& cookie)
        : m_arguments(firstParty, sameSiteInfo, url, frameID, pageID, applyTrackingPrevention, shouldRelaxThirdPartyCookieBlocking, cookie)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SameSiteInfo&, const URL&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&, WebCore::ApplyTrackingPrevention, WebCore::ShouldRelaxThirdPartyCookieBlocking, const WebCore::Cookie&> m_arguments;
};

#if HAVE(COOKIE_CHANGE_LISTENER_API)
class SubscribeToCookieChangeNotifications {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SubscribeToCookieChangeNotifications; }
    static constexpr bool isSync = false;

    explicit SubscribeToCookieChangeNotifications(const String& host)
        : m_arguments(host)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};
#endif

#if HAVE(COOKIE_CHANGE_LISTENER_API)
class UnsubscribeFromCookieChangeNotifications {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UnsubscribeFromCookieChangeNotifications; }
    static constexpr bool isSync = false;

    explicit UnsubscribeFromCookieChangeNotifications(const String& host)
        : m_arguments(host)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};
#endif

class RegisterInternalFileBlobURL {
public:
    using Arguments = std::tuple<URL, String, String, WebKit::SandboxExtension::Handle, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterInternalFileBlobURL; }
    static constexpr bool isSync = false;

    RegisterInternalFileBlobURL(const URL& url, const String& path, const String& replacementPath, const WebKit::SandboxExtension::Handle& extensionHandle, const String& contentType)
        : m_arguments(url, path, replacementPath, extensionHandle, contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const String&, const String&, const WebKit::SandboxExtension::Handle&, const String&> m_arguments;
};

class RegisterInternalBlobURL {
public:
    using Arguments = std::tuple<URL, Vector<WebCore::BlobPart>, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURL; }
    static constexpr bool isSync = false;

    RegisterInternalBlobURL(const URL& url, const Vector<WebCore::BlobPart>& blobParts, const String& contentType)
        : m_arguments(url, blobParts, contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const Vector<WebCore::BlobPart>&, const String&> m_arguments;
};

class RegisterBlobURL {
public:
    using Arguments = std::tuple<URL, URL, WebCore::PolicyContainer, std::optional<WebCore::SecurityOriginData>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterBlobURL; }
    static constexpr bool isSync = false;

    RegisterBlobURL(const URL& url, const URL& srcURL, const WebCore::PolicyContainer& policyContainer, const std::optional<WebCore::SecurityOriginData>& topOrigin)
        : m_arguments(url, srcURL, policyContainer, topOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const URL&, const WebCore::PolicyContainer&, const std::optional<WebCore::SecurityOriginData>&> m_arguments;
};

class RegisterInternalBlobURLOptionallyFileBacked {
public:
    using Arguments = std::tuple<URL, URL, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURLOptionallyFileBacked; }
    static constexpr bool isSync = false;

    RegisterInternalBlobURLOptionallyFileBacked(const URL& url, const URL& srcURL, const String& fileBackedPath, const String& contentType)
        : m_arguments(url, srcURL, fileBackedPath, contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const URL&, const String&, const String&> m_arguments;
};

class RegisterInternalBlobURLForSlice {
public:
    using Arguments = std::tuple<URL, URL, int64_t, int64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURLForSlice; }
    static constexpr bool isSync = false;

    RegisterInternalBlobURLForSlice(const URL& url, const URL& srcURL, int64_t start, int64_t end, const String& contentType)
        : m_arguments(url, srcURL, start, end, contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const URL&, int64_t, int64_t, const String&> m_arguments;
};

class UnregisterBlobURL {
public:
    using Arguments = std::tuple<URL, std::optional<WebCore::SecurityOriginData>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UnregisterBlobURL; }
    static constexpr bool isSync = false;

    UnregisterBlobURL(const URL& url, const std::optional<WebCore::SecurityOriginData>& topOrigin)
        : m_arguments(url, topOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const std::optional<WebCore::SecurityOriginData>&> m_arguments;
};

class BlobSize {
public:
    using Arguments = std::tuple<URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_BlobSize; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    explicit BlobSize(const URL& url)
        : m_arguments(url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&> m_arguments;
};

class WriteBlobsToTemporaryFilesForIndexedDB {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDB; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDBReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit WriteBlobsToTemporaryFilesForIndexedDB(const Vector<String>& blobURLs)
        : m_arguments(blobURLs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

class RegisterBlobURLHandle {
public:
    using Arguments = std::tuple<URL, std::optional<WebCore::SecurityOriginData>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterBlobURLHandle; }
    static constexpr bool isSync = false;

    RegisterBlobURLHandle(const URL& url, const std::optional<WebCore::SecurityOriginData>& topOrigin)
        : m_arguments(url, topOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const std::optional<WebCore::SecurityOriginData>&> m_arguments;
};

class UnregisterBlobURLHandle {
public:
    using Arguments = std::tuple<URL, std::optional<WebCore::SecurityOriginData>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UnregisterBlobURLHandle; }
    static constexpr bool isSync = false;

    UnregisterBlobURLHandle(const URL& url, const std::optional<WebCore::SecurityOriginData>& topOrigin)
        : m_arguments(url, topOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const std::optional<WebCore::SecurityOriginData>&> m_arguments;
};

class SetCaptureExtraNetworkLoadMetricsEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetCaptureExtraNetworkLoadMetricsEnabled; }
    static constexpr bool isSync = false;

    explicit SetCaptureExtraNetworkLoadMetricsEnabled(bool enabled)
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

class CreateSocketChannel {
public:
    using Arguments = std::tuple<WebCore::ResourceRequest, String, WebCore::WebSocketIdentifier, WebKit::WebPageProxyIdentifier, std::optional<WebCore::FrameIdentifier>, std::optional<WebCore::PageIdentifier>, WebCore::ClientOrigin, bool, bool, OptionSet<WebCore::AdvancedPrivacyProtections>, WebCore::ShouldRelaxThirdPartyCookieBlocking, WebCore::StoredCredentialsPolicy>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CreateSocketChannel; }
    static constexpr bool isSync = false;

    CreateSocketChannel(const WebCore::ResourceRequest& request, const String& protocol, const WebCore::WebSocketIdentifier& identifier, const WebKit::WebPageProxyIdentifier& webPageProxyID, const std::optional<WebCore::FrameIdentifier>& frameID, const std::optional<WebCore::PageIdentifier>& pageID, const WebCore::ClientOrigin& clientOrigin, bool hadMainFrameMainResourcePrivateRelayed, bool allowPrivacyProxy, const OptionSet<WebCore::AdvancedPrivacyProtections>& protections, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking, WebCore::StoredCredentialsPolicy storedCredentialsPolicy)
        : m_arguments(request, protocol, identifier, webPageProxyID, frameID, pageID, clientOrigin, hadMainFrameMainResourcePrivateRelayed, allowPrivacyProxy, protections, shouldRelaxThirdPartyCookieBlocking, storedCredentialsPolicy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceRequest&, const String&, const WebCore::WebSocketIdentifier&, const WebKit::WebPageProxyIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const std::optional<WebCore::PageIdentifier>&, const WebCore::ClientOrigin&, bool, bool, const OptionSet<WebCore::AdvancedPrivacyProtections>&, WebCore::ShouldRelaxThirdPartyCookieBlocking, WebCore::StoredCredentialsPolicy> m_arguments;
};

class ClearPageSpecificData {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ClearPageSpecificData; }
    static constexpr bool isSync = false;

    explicit ClearPageSpecificData(const WebCore::PageIdentifier& pageID)
        : m_arguments(pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&> m_arguments;
};

#if ENABLE(TRACKING_PREVENTION)
class RemoveStorageAccessForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RemoveStorageAccessForFrame; }
    static constexpr bool isSync = false;

    RemoveStorageAccessForFrame(const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID)
        : m_arguments(frameID, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class LogUserInteraction {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_LogUserInteraction; }
    static constexpr bool isSync = false;

    explicit LogUserInteraction(const WebCore::RegistrableDomain& domain)
        : m_arguments(domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ResourceLoadStatisticsUpdated {
public:
    using Arguments = std::tuple<Vector<WebCore::ResourceLoadStatistics>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdated; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdatedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResourceLoadStatisticsUpdated(const Vector<WebCore::ResourceLoadStatistics>& statistics)
        : m_arguments(statistics)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::ResourceLoadStatistics>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class HasStorageAccess {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::RegistrableDomain, WebCore::FrameIdentifier, WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_HasStorageAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_HasStorageAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    HasStorageAccess(const WebCore::RegistrableDomain& subFrameDomain, const WebCore::RegistrableDomain& topFrameDomain, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& pageID)
        : m_arguments(subFrameDomain, topFrameDomain, frameID, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class RequestStorageAccess {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::RegistrableDomain, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebKit::WebPageProxyIdentifier, WebCore::StorageAccessScope>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RequestStorageAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_RequestStorageAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::RequestStorageAccessResult>;
    RequestStorageAccess(const WebCore::RegistrableDomain& subFrameDomain, const WebCore::RegistrableDomain& topFrameDomain, const WebCore::FrameIdentifier& frameID, const WebCore::PageIdentifier& webPageID, const WebKit::WebPageProxyIdentifier& webPageProxyID, WebCore::StorageAccessScope scope)
        : m_arguments(subFrameDomain, topFrameDomain, frameID, webPageID, webPageProxyID, scope)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const WebCore::FrameIdentifier&, const WebCore::PageIdentifier&, const WebKit::WebPageProxyIdentifier&, WebCore::StorageAccessScope> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class RequestStorageAccessUnderOpener {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::PageIdentifier, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RequestStorageAccessUnderOpener; }
    static constexpr bool isSync = false;

    RequestStorageAccessUnderOpener(const WebCore::RegistrableDomain& domainInNeedOfStorageAccess, const WebCore::PageIdentifier& openerPageID, const WebCore::RegistrableDomain& openerDomain)
        : m_arguments(domainInNeedOfStorageAccess, openerPageID, openerDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::PageIdentifier&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

class AddOriginAccessAllowListEntry {
public:
    using Arguments = std::tuple<String, String, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_AddOriginAccessAllowListEntry; }
    static constexpr bool isSync = false;

    AddOriginAccessAllowListEntry(const String& sourceOrigin, const String& destinationProtocol, const String& destinationHost, bool allowDestinationSubdomains)
        : m_arguments(sourceOrigin, destinationProtocol, destinationHost, allowDestinationSubdomains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, bool> m_arguments;
};

class RemoveOriginAccessAllowListEntry {
public:
    using Arguments = std::tuple<String, String, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RemoveOriginAccessAllowListEntry; }
    static constexpr bool isSync = false;

    RemoveOriginAccessAllowListEntry(const String& sourceOrigin, const String& destinationProtocol, const String& destinationHost, bool allowDestinationSubdomains)
        : m_arguments(sourceOrigin, destinationProtocol, destinationHost, allowDestinationSubdomains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, bool> m_arguments;
};

class ResetOriginAccessAllowLists {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ResetOriginAccessAllowLists; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetNetworkLoadInformationResponse {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_GetNetworkLoadInformationResponse; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceResponse>;
    explicit GetNetworkLoadInformationResponse(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier)
        : m_arguments(resourceLoadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

class GetNetworkLoadIntermediateInformation {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_GetNetworkLoadIntermediateInformation; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::NetworkTransactionInformation>>;
    explicit GetNetworkLoadIntermediateInformation(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier)
        : m_arguments(resourceLoadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

class TakeNetworkLoadInformationMetrics {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_TakeNetworkLoadInformationMetrics; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::NetworkLoadMetrics>;
    explicit TakeNetworkLoadInformationMetrics(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier)
        : m_arguments(resourceLoadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

#if ENABLE(SERVICE_WORKER)
class EstablishSWContextConnection {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::RegistrableDomain, std::optional<WebCore::ScriptExecutionContextIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_EstablishSWContextConnection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_EstablishSWContextConnectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    EstablishSWContextConnection(const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::RegistrableDomain& domain, const std::optional<WebCore::ScriptExecutionContextIdentifier>& serviceWorkerPageIdentifier)
        : m_arguments(webPageProxyID, domain, serviceWorkerPageIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::RegistrableDomain&, const std::optional<WebCore::ScriptExecutionContextIdentifier>&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class CloseSWContextConnection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CloseSWContextConnection; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class EstablishSharedWorkerContextConnection {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    EstablishSharedWorkerContextConnection(const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::RegistrableDomain& domain)
        : m_arguments(webPageProxyID, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::RegistrableDomain&> m_arguments;
};

class CloseSharedWorkerContextConnection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CloseSharedWorkerContextConnection; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateRTCProvider {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CreateRTCProvider; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_CreateRTCProviderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(WEB_RTC)
class ConnectToRTCDataChannelRemoteSource {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, WebCore::RTCDataChannelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSourceReply; }
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

class UpdateQuotaBasedOnSpaceUsageForTesting {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UpdateQuotaBasedOnSpaceUsageForTesting; }
    static constexpr bool isSync = false;

    explicit UpdateQuotaBasedOnSpaceUsageForTesting(const WebCore::ClientOrigin& origin)
        : m_arguments(origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&> m_arguments;
};

class CreateNewMessagePortChannel {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier, WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_CreateNewMessagePortChannel; }
    static constexpr bool isSync = false;

    CreateNewMessagePortChannel(const WebCore::MessagePortIdentifier& port1, const WebCore::MessagePortIdentifier& port2)
        : m_arguments(port1, port2)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessagePortIdentifier&, const WebCore::MessagePortIdentifier&> m_arguments;
};

class EntangleLocalPortInThisProcessToRemote {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier, WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_EntangleLocalPortInThisProcessToRemote; }
    static constexpr bool isSync = false;

    EntangleLocalPortInThisProcessToRemote(const WebCore::MessagePortIdentifier& local, const WebCore::MessagePortIdentifier& remote)
        : m_arguments(local, remote)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessagePortIdentifier&, const WebCore::MessagePortIdentifier&> m_arguments;
};

class MessagePortDisentangled {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_MessagePortDisentangled; }
    static constexpr bool isSync = false;

    explicit MessagePortDisentangled(const WebCore::MessagePortIdentifier& local)
        : m_arguments(local)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessagePortIdentifier&> m_arguments;
};

class MessagePortClosed {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_MessagePortClosed; }
    static constexpr bool isSync = false;

    explicit MessagePortClosed(const WebCore::MessagePortIdentifier& local)
        : m_arguments(local)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessagePortIdentifier&> m_arguments;
};

class TakeAllMessagesForPort {
public:
    using Arguments = std::tuple<WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_TakeAllMessagesForPort; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_TakeAllMessagesForPortReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::MessageWithMessagePorts>, uint64_t>;
    explicit TakeAllMessagesForPort(const WebCore::MessagePortIdentifier& port)
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

class PostMessageToRemote {
public:
    using Arguments = std::tuple<WebCore::MessageWithMessagePorts, WebCore::MessagePortIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PostMessageToRemote; }
    static constexpr bool isSync = false;

    PostMessageToRemote(const WebCore::MessageWithMessagePorts& message, const WebCore::MessagePortIdentifier& remote)
        : m_arguments(message, remote)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MessageWithMessagePorts&, const WebCore::MessagePortIdentifier&> m_arguments;
};

class DidDeliverMessagePortMessages {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_DidDeliverMessagePortMessages; }
    static constexpr bool isSync = false;

    explicit DidDeliverMessagePortMessages(uint64_t messageBatchIdentifier)
        : m_arguments(messageBatchIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class RegisterURLSchemesAsCORSEnabled {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_RegisterURLSchemesAsCORSEnabled; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemesAsCORSEnabled(const Vector<String>& schemes)
        : m_arguments(schemes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

class SetCORSDisablingPatterns {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetCORSDisablingPatterns; }
    static constexpr bool isSync = false;

    SetCORSDisablingPatterns(const WebCore::PageIdentifier& pageIdentifier, const Vector<String>& patterns)
        : m_arguments(pageIdentifier, patterns)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const Vector<String>&> m_arguments;
};

#if PLATFORM(MAC)
class GetProcessDisplayName {
public:
    using Arguments = std::tuple<audit_token_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_GetProcessDisplayName; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkConnectionToWebProcess_GetProcessDisplayNameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetProcessDisplayName(const audit_token_t& auditToken)
        : m_arguments(auditToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const audit_token_t&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class UpdateActivePages {
public:
    using Arguments = std::tuple<String, Vector<String>, audit_token_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UpdateActivePages; }
    static constexpr bool isSync = false;

    UpdateActivePages(const String& name, const Vector<String>& activePagesOrigins, const audit_token_t& auditToken)
        : m_arguments(name, activePagesOrigins, auditToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<String>&, const audit_token_t&> m_arguments;
};
#endif

class SetResourceLoadSchedulingMode {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebCore::LoadSchedulingMode>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_SetResourceLoadSchedulingMode; }
    static constexpr bool isSync = false;

    SetResourceLoadSchedulingMode(const WebCore::PageIdentifier& webPageID, WebCore::LoadSchedulingMode mode)
        : m_arguments(webPageID, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, WebCore::LoadSchedulingMode> m_arguments;
};

class PrioritizeResourceLoads {
public:
    using Arguments = std::tuple<Vector<WebCore::ResourceLoaderIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_PrioritizeResourceLoads; }
    static constexpr bool isSync = false;

    explicit PrioritizeResourceLoads(const Vector<WebCore::ResourceLoaderIdentifier>& loadIdentifiers)
        : m_arguments(loadIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::ResourceLoaderIdentifier>&> m_arguments;
};

#if ENABLE(CONTENT_FILTERING)
class InstallMockContentFilter {
public:
    using Arguments = std::tuple<WebCore::MockContentFilterSettings>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_InstallMockContentFilter; }
    static constexpr bool isSync = false;

    explicit InstallMockContentFilter(const WebCore::MockContentFilterSettings& settings)
        : m_arguments(settings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MockContentFilterSettings&> m_arguments;
};
#endif

#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
class LogOnBehalfOfWebContent {
public:
    using Arguments = std::tuple<IPC::DataReference, IPC::DataReference, IPC::DataReference, uint8_t, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_LogOnBehalfOfWebContent; }
    static constexpr bool isSync = false;

    LogOnBehalfOfWebContent(const IPC::DataReference& logChannel, const IPC::DataReference& logCategory, const IPC::DataReference& logString, uint8_t logType, int32_t pid)
        : m_arguments(logChannel, logCategory, logString, logType, pid)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&, const IPC::DataReference&, const IPC::DataReference&, uint8_t, int32_t> m_arguments;
};
#endif

class AddAllowedFirstPartyForCookies {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_AddAllowedFirstPartyForCookies; }
    static constexpr bool isSync = false;

    explicit AddAllowedFirstPartyForCookies(const WebCore::RegistrableDomain& firstPartyDomain)
        : m_arguments(firstPartyDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&> m_arguments;
};

class UseRedirectionForCurrentNavigation {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkConnectionToWebProcess_UseRedirectionForCurrentNavigation; }
    static constexpr bool isSync = false;

    UseRedirectionForCurrentNavigation(const WebCore::ResourceLoaderIdentifier& resourceLoadIdentifier, const WebCore::ResourceResponse& response)
        : m_arguments(resourceLoadIdentifier, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceResponse&> m_arguments;
};

} // namespace NetworkConnectionToWebProcess
} // namespace Messages
