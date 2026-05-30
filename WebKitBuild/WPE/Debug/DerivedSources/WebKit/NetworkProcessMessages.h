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
#include "BackgroundFetchState.h"
#include "Connection.h"
#include "DataReference.h"
#include "DataTaskIdentifier.h"
#include "DownloadID.h"
#include "MessageNames.h"
#include "NavigatingToAppBoundDomain.h"
#include "QuotaIncreaseRequestIdentifier.h"
#include "SandboxExtension.h"
#include "WebPageProxyIdentifier.h"
#include "WebPushMessage.h"
#include "WebResourceLoadStatisticsStore.h"
#include "WebsiteDataFetchOption.h"
#include "WebsiteDataType.h"
#include <WebCore/CrossSiteNavigationDataTransfer.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/ProcessIdentifier.h>
#include <WebCore/RegistrableDomain.h>
#include <WebCore/SecurityOriginData.h>
#include <optional>
#include <utility>
#include <wtf/Forward.h>
#include <wtf/HashSet.h>
#include <wtf/OptionSet.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/UUID.h>
#include <wtf/Vector.h>
#include <wtf/WallTime.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class FormDataReference;
}

namespace PAL {
class SessionID;
}

namespace WebCore {
class CertificateInfo;
class CurlProxySettings;
class PrivateClickMeasurement;
class RegistrableDomain;
class ResourceRequest;
class SecurityOriginData;
enum class NotificationEventType : bool;
enum class SameSiteStrictEnforcementEnabled : bool;
enum class FirstPartyWebsiteDataRemovalMode : uint8_t;
enum class HTTPCookieAcceptPolicy : uint8_t;
enum class PushPermissionState : uint8_t;
enum class StoredCredentialsPolicy : uint8_t;
enum class ThirdPartyCookieBlockingMode : uint8_t;
struct ClientOrigin;
struct NotificationData;
struct SoupNetworkProxySettings;
}

namespace WebKit {
class WebPageNetworkParameters;
enum class CallDownloadDidStart : bool;
enum class LoadedWebArchive : bool;
enum class ShouldGrandfatherStatistics : bool;
enum class CacheModel : uint8_t;
enum class RemoteWorkerType : uint8_t;
struct AppPrivacyReportTestingData;
struct NetworkProcessConnectionParameters;
struct NetworkProcessCreationParameters;
struct WebPushMessage;
struct WebsiteData;
struct WebsiteDataStoreParameters;
}

namespace Messages {
namespace NetworkProcess {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkProcess;
}

class InitializeNetworkProcess {
public:
    using Arguments = std::tuple<WebKit::NetworkProcessCreationParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_InitializeNetworkProcess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_InitializeNetworkProcessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit InitializeNetworkProcess(const WebKit::NetworkProcessCreationParameters& processCreationParameters)
        : m_arguments(processCreationParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::NetworkProcessCreationParameters&> m_arguments;
};

class CreateNetworkConnectionToWebProcess {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, PAL::SessionID, WebKit::NetworkProcessConnectionParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CreateNetworkConnectionToWebProcess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_CreateNetworkConnectionToWebProcessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::Connection::Handle>, WebCore::HTTPCookieAcceptPolicy>;
    CreateNetworkConnectionToWebProcess(const WebCore::ProcessIdentifier& processIdentifier, const PAL::SessionID& sessionID, const WebKit::NetworkProcessConnectionParameters& parameters)
        : m_arguments(processIdentifier, sessionID, parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, const PAL::SessionID&, const WebKit::NetworkProcessConnectionParameters&> m_arguments;
};

class AddAllowedFirstPartyForCookies {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, WebCore::RegistrableDomain, WebKit::LoadedWebArchive>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AddAllowedFirstPartyForCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_AddAllowedFirstPartyForCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    AddAllowedFirstPartyForCookies(const WebCore::ProcessIdentifier& processIdentifier, const WebCore::RegistrableDomain& firstPartyForCookies, WebKit::LoadedWebArchive loadedWebArchive)
        : m_arguments(processIdentifier, firstPartyForCookies, loadedWebArchive)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, const WebCore::RegistrableDomain&, WebKit::LoadedWebArchive> m_arguments;
};

#if USE(SOUP)
class SetIgnoreTLSErrors {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetIgnoreTLSErrors; }
    static constexpr bool isSync = false;

    SetIgnoreTLSErrors(const PAL::SessionID& sessionID, bool ignoreTLSErrors)
        : m_arguments(sessionID, ignoreTLSErrors)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if USE(SOUP)
class UserPreferredLanguagesChanged {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_UserPreferredLanguagesChanged; }
    static constexpr bool isSync = false;

    explicit UserPreferredLanguagesChanged(const Vector<String>& languages)
        : m_arguments(languages)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};
#endif

#if USE(SOUP)
class SetNetworkProxySettings {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::SoupNetworkProxySettings>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetNetworkProxySettings; }
    static constexpr bool isSync = false;

    SetNetworkProxySettings(const PAL::SessionID& sessionID, const WebCore::SoupNetworkProxySettings& settings)
        : m_arguments(sessionID, settings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::SoupNetworkProxySettings&> m_arguments;
};
#endif

#if USE(SOUP)
class PrefetchDNS {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_PrefetchDNS; }
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
#endif

#if USE(SOUP)
class SetPersistentCredentialStorageEnabled {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPersistentCredentialStorageEnabled; }
    static constexpr bool isSync = false;

    SetPersistentCredentialStorageEnabled(const PAL::SessionID& sessionID, bool enabled)
        : m_arguments(sessionID, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if USE(CURL)
class SetNetworkProxySettings {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::CurlProxySettings>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetNetworkProxySettings; }
    static constexpr bool isSync = false;

    SetNetworkProxySettings(const PAL::SessionID& sessionID, const WebCore::CurlProxySettings& settings)
        : m_arguments(sessionID, settings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::CurlProxySettings&> m_arguments;
};
#endif

class AddWebsiteDataStore {
public:
    using Arguments = std::tuple<WebKit::WebsiteDataStoreParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AddWebsiteDataStore; }
    static constexpr bool isSync = false;

    explicit AddWebsiteDataStore(const WebKit::WebsiteDataStoreParameters& websiteDataStoreParameters)
        : m_arguments(websiteDataStoreParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebsiteDataStoreParameters&> m_arguments;
};

class DestroySession {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DestroySession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DestroySessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit DestroySession(const PAL::SessionID& sessionID)
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

class FetchWebsiteData {
public:
    using Arguments = std::tuple<PAL::SessionID, OptionSet<WebKit::WebsiteDataType>, OptionSet<WebKit::WebsiteDataFetchOption>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_FetchWebsiteData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_FetchWebsiteDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebsiteData>;
    FetchWebsiteData(const PAL::SessionID& sessionID, const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const OptionSet<WebKit::WebsiteDataFetchOption>& fetchOptions)
        : m_arguments(sessionID, websiteDataTypes, fetchOptions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const OptionSet<WebKit::WebsiteDataType>&, const OptionSet<WebKit::WebsiteDataFetchOption>&> m_arguments;
};

class DeleteWebsiteData {
public:
    using Arguments = std::tuple<PAL::SessionID, OptionSet<WebKit::WebsiteDataType>, WallTime>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DeleteWebsiteData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DeleteWebsiteDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteData(const PAL::SessionID& sessionID, const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const WallTime& modifiedSince)
        : m_arguments(sessionID, websiteDataTypes, modifiedSince)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const OptionSet<WebKit::WebsiteDataType>&, const WallTime&> m_arguments;
};

class DeleteWebsiteDataForOrigins {
public:
    using Arguments = std::tuple<PAL::SessionID, OptionSet<WebKit::WebsiteDataType>, Vector<WebCore::SecurityOriginData>, Vector<String>, Vector<String>, Vector<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DeleteWebsiteDataForOrigins; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DeleteWebsiteDataForOriginsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteDataForOrigins(const PAL::SessionID& sessionID, const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const Vector<WebCore::SecurityOriginData>& origins, const Vector<String>& cookieHostNames, const Vector<String>& HSTSCacheHostNames, const Vector<WebCore::RegistrableDomain>& registrableDomains)
        : m_arguments(sessionID, websiteDataTypes, origins, cookieHostNames, HSTSCacheHostNames, registrableDomains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const OptionSet<WebKit::WebsiteDataType>&, const Vector<WebCore::SecurityOriginData>&, const Vector<String>&, const Vector<String>&, const Vector<WebCore::RegistrableDomain>&> m_arguments;
};

class RenameOriginInWebsiteData {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::SecurityOriginData, WebCore::SecurityOriginData, OptionSet<WebKit::WebsiteDataType>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RenameOriginInWebsiteData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_RenameOriginInWebsiteDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    RenameOriginInWebsiteData(const PAL::SessionID& sessionID, const WebCore::SecurityOriginData& oldOrigin, const WebCore::SecurityOriginData& newOrigin, const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes)
        : m_arguments(sessionID, oldOrigin, newOrigin, websiteDataTypes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::SecurityOriginData&, const WebCore::SecurityOriginData&, const OptionSet<WebKit::WebsiteDataType>&> m_arguments;
};

class WebsiteDataOriginDirectoryForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ClientOrigin, OptionSet<WebKit::WebsiteDataType>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_WebsiteDataOriginDirectoryForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_WebsiteDataOriginDirectoryForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    WebsiteDataOriginDirectoryForTesting(const PAL::SessionID& sessionID, const WebCore::ClientOrigin& origin, const OptionSet<WebKit::WebsiteDataType>& websiteDataType)
        : m_arguments(sessionID, origin, websiteDataType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::ClientOrigin&, const OptionSet<WebKit::WebsiteDataType>&> m_arguments;
};

class DownloadRequest {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::DownloadID, WebCore::ResourceRequest, std::optional<WebKit::NavigatingToAppBoundDomain>, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DownloadRequest; }
    static constexpr bool isSync = false;

    DownloadRequest(const PAL::SessionID& sessionID, const WebKit::DownloadID& downloadID, const WebCore::ResourceRequest& request, const std::optional<WebKit::NavigatingToAppBoundDomain>& isNavigatingToAppBoundDomain, const String& suggestedFilename)
        : m_arguments(sessionID, downloadID, request, isNavigatingToAppBoundDomain, suggestedFilename)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::DownloadID&, const WebCore::ResourceRequest&, const std::optional<WebKit::NavigatingToAppBoundDomain>&, const String&> m_arguments;
};

class ResumeDownload {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::DownloadID, IPC::DataReference, String, WebKit::SandboxExtension::Handle, WebKit::CallDownloadDidStart>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResumeDownload; }
    static constexpr bool isSync = false;

    ResumeDownload(const PAL::SessionID& sessionID, const WebKit::DownloadID& downloadID, const IPC::DataReference& resumeData, const String& path, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle, WebKit::CallDownloadDidStart callDownloadDidStart)
        : m_arguments(sessionID, downloadID, resumeData, path, sandboxExtensionHandle, callDownloadDidStart)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::DownloadID&, const IPC::DataReference&, const String&, const WebKit::SandboxExtension::Handle&, WebKit::CallDownloadDidStart> m_arguments;
};

class CancelDownload {
public:
    using Arguments = std::tuple<WebKit::DownloadID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CancelDownload; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_CancelDownloadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::DataReference>;
    explicit CancelDownload(const WebKit::DownloadID& downloadID)
        : m_arguments(downloadID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DownloadID&> m_arguments;
};

#if PLATFORM(COCOA)
class PublishDownloadProgress {
public:
    using Arguments = std::tuple<WebKit::DownloadID, URL, WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_PublishDownloadProgress; }
    static constexpr bool isSync = false;

    PublishDownloadProgress(const WebKit::DownloadID& downloadID, const URL& url, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle)
        : m_arguments(downloadID, url, sandboxExtensionHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DownloadID&, const URL&, const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

class DataTaskWithRequest {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, PAL::SessionID, WebCore::ResourceRequest, IPC::FormDataReference>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DataTaskWithRequest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DataTaskWithRequestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::DataTaskIdentifier>;
    DataTaskWithRequest(const WebKit::WebPageProxyIdentifier& pageID, const PAL::SessionID& sessionID, const WebCore::ResourceRequest& request, const IPC::FormDataReference& requestBody)
        : m_arguments(pageID, sessionID, request, requestBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const PAL::SessionID&, const WebCore::ResourceRequest&, const IPC::FormDataReference&> m_arguments;
};

class CancelDataTask {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CancelDataTask; }
    static constexpr bool isSync = false;

    CancelDataTask(const WebKit::DataTaskIdentifier& taskIdentifier, const PAL::SessionID& sessionID)
        : m_arguments(taskIdentifier, sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const PAL::SessionID&> m_arguments;
};

class ApplicationDidEnterBackground {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ApplicationDidEnterBackground; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ApplicationWillEnterForeground {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ApplicationWillEnterForeground; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetAllowsAnySSLCertificateForWebSocket {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetAllowsAnySSLCertificateForWebSocket; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetAllowsAnySSLCertificateForWebSocket(bool enabled)
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

class FlushCookies {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_FlushCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_FlushCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit FlushCookies(const PAL::SessionID& sessionID)
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

class AllowSpecificHTTPSCertificateForHost {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::CertificateInfo, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AllowSpecificHTTPSCertificateForHost; }
    static constexpr bool isSync = false;

    AllowSpecificHTTPSCertificateForHost(const PAL::SessionID& sessionID, const WebCore::CertificateInfo& certificate, const String& host)
        : m_arguments(sessionID, certificate, host)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::CertificateInfo&, const String&> m_arguments;
};

class AllowTLSCertificateChainForLocalPCMTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::CertificateInfo>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AllowTLSCertificateChainForLocalPCMTesting; }
    static constexpr bool isSync = false;

    AllowTLSCertificateChainForLocalPCMTesting(const PAL::SessionID& sessionID, const WebCore::CertificateInfo& certificate)
        : m_arguments(sessionID, certificate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::CertificateInfo&> m_arguments;
};

class SetCacheModel {
public:
    using Arguments = std::tuple<WebKit::CacheModel>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetCacheModel; }
    static constexpr bool isSync = false;

    explicit SetCacheModel(WebKit::CacheModel cacheModel)
        : m_arguments(cacheModel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::CacheModel> m_arguments;
};

class SetCacheModelSynchronouslyForTesting {
public:
    using Arguments = std::tuple<WebKit::CacheModel>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetCacheModelSynchronouslyForTesting; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetCacheModelSynchronouslyForTesting(WebKit::CacheModel cacheModel)
        : m_arguments(cacheModel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::CacheModel> m_arguments;
};

class ProcessWillSuspendImminentlyForTestingSync {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ProcessWillSuspendImminentlyForTestingSync; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PrepareToSuspend {
public:
    using Arguments = std::tuple<bool, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_PrepareToSuspend; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_PrepareToSuspendReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PrepareToSuspend(bool isSuspensionImminent, const MonotonicTime& estimatedSuspendTime)
        : m_arguments(isSuspensionImminent, estimatedSuspendTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const MonotonicTime&> m_arguments;
};

class ProcessDidResume {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ProcessDidResume; }
    static constexpr bool isSync = false;

    explicit ProcessDidResume(bool forForegroundActivity)
        : m_arguments(forForegroundActivity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class NotifyMediaStreamingActivity {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_NotifyMediaStreamingActivity; }
    static constexpr bool isSync = false;

    explicit NotifyMediaStreamingActivity(bool activity)
        : m_arguments(activity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class PreconnectTo {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier, WebCore::ResourceRequest, WebCore::StoredCredentialsPolicy, std::optional<WebKit::NavigatingToAppBoundDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_PreconnectTo; }
    static constexpr bool isSync = false;

    PreconnectTo(const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::PageIdentifier& webPageID, const WebCore::ResourceRequest& request, WebCore::StoredCredentialsPolicy storedCredentialsPolicy, const std::optional<WebKit::NavigatingToAppBoundDomain>& isNavigatingToAppBoundDomain)
        : m_arguments(sessionID, webPageProxyID, webPageID, request, storedCredentialsPolicy, isNavigatingToAppBoundDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&, const WebCore::ResourceRequest&, WebCore::StoredCredentialsPolicy, const std::optional<WebKit::NavigatingToAppBoundDomain>&> m_arguments;
};

#if ENABLE(TRACKING_PREVENTION)
class ClearPrevalentResource {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearPrevalentResource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearPrevalentResourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ClearPrevalentResource(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ClearUserInteraction {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearUserInteraction; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearUserInteractionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ClearUserInteraction(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class DumpResourceLoadStatistics {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DumpResourceLoadStatistics; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DumpResourceLoadStatisticsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit DumpResourceLoadStatistics(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetTrackingPreventionEnabled {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetTrackingPreventionEnabled; }
    static constexpr bool isSync = false;

    SetTrackingPreventionEnabled(const PAL::SessionID& sessionID, bool enabled)
        : m_arguments(sessionID, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetResourceLoadStatisticsLogTestingEvent {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetResourceLoadStatisticsLogTestingEvent; }
    static constexpr bool isSync = false;

    explicit SetResourceLoadStatisticsLogTestingEvent(bool enabled)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class UpdatePrevalentDomainsToBlockCookiesFor {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_UpdatePrevalentDomainsToBlockCookiesFor; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_UpdatePrevalentDomainsToBlockCookiesForReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UpdatePrevalentDomainsToBlockCookiesFor(const PAL::SessionID& sessionID, const Vector<WebCore::RegistrableDomain>& domainsToBlock)
        : m_arguments(sessionID, domainsToBlock)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsGrandfathered {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsGrandfathered; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsGrandfatheredReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsGrandfathered(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& targetDomain)
        : m_arguments(sessionID, targetDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsPrevalentResource {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsPrevalentResource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsPrevalentResourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsPrevalentResource(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& targetDomain)
        : m_arguments(sessionID, targetDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsVeryPrevalentResource {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsVeryPrevalentResource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsVeryPrevalentResourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsVeryPrevalentResource(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& targetDomain)
        : m_arguments(sessionID, targetDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetLastSeen {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetLastSeen; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetLastSeenReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetLastSeen(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain, const Seconds& seconds)
        : m_arguments(sessionID, resourceDomain, seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class MergeStatisticForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain, WebCore::RegistrableDomain, Seconds, bool, Seconds, bool, bool, bool, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_MergeStatisticForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_MergeStatisticForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    MergeStatisticForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain, const WebCore::RegistrableDomain& topFrameDomain1, const WebCore::RegistrableDomain& topFrameDomain2, const Seconds& lastSeen, bool hadUserInteraction, const Seconds& mostRecentUserInteraction, bool isGrandfathered, bool isPrevalent, bool isVeryPrevalent, uint64_t dataRecordsRemoved)
        : m_arguments(sessionID, resourceDomain, topFrameDomain1, topFrameDomain2, lastSeen, hadUserInteraction, mostRecentUserInteraction, isGrandfathered, isPrevalent, isVeryPrevalent, dataRecordsRemoved)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const Seconds&, bool, const Seconds&, bool, bool, bool, uint64_t> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class InsertExpiredStatisticForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, uint64_t, bool, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_InsertExpiredStatisticForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_InsertExpiredStatisticForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    InsertExpiredStatisticForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain, uint64_t numberOfOperatingDaysPassed, bool hadUserInteraction, bool isScheduledForAllButCookieDataRemoval, bool isPrevalent)
        : m_arguments(sessionID, resourceDomain, numberOfOperatingDaysPassed, hadUserInteraction, isScheduledForAllButCookieDataRemoval, isPrevalent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, uint64_t, bool, bool, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetPrevalentResource {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrevalentResource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrevalentResourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrevalentResource(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetPrevalentResourceForDebugMode {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrevalentResourceForDebugMode; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrevalentResourceForDebugModeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrevalentResourceForDebugMode(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsResourceLoadStatisticsEphemeral {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsResourceLoadStatisticsEphemeral; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsResourceLoadStatisticsEphemeralReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsResourceLoadStatisticsEphemeral(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class HadUserInteraction {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_HadUserInteraction; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_HadUserInteractionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    HadUserInteraction(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsRelationshipOnlyInDatabaseOnce {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsRelationshipOnlyInDatabaseOnce; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsRelationshipOnlyInDatabaseOnceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsRelationshipOnlyInDatabaseOnce(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subDomain, const WebCore::RegistrableDomain& topDomain)
        : m_arguments(sessionID, subDomain, topDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class HasLocalStorage {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_HasLocalStorage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_HasLocalStorageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    HasLocalStorage(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class GetAllStorageAccessEntries {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetAllStorageAccessEntries; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetAllStorageAccessEntriesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit GetAllStorageAccessEntries(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsRegisteredAsRedirectingTo {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsRegisteredAsRedirectingTo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsRegisteredAsRedirectingToReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsRegisteredAsRedirectingTo(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& redirectedFromDomain, const WebCore::RegistrableDomain& redirectedToDomain)
        : m_arguments(sessionID, redirectedFromDomain, redirectedToDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsRegisteredAsSubFrameUnder {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsRegisteredAsSubFrameUnder; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsRegisteredAsSubFrameUnderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsRegisteredAsSubFrameUnder(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subFrameDomain, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(sessionID, subFrameDomain, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class IsRegisteredAsSubresourceUnder {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_IsRegisteredAsSubresourceUnder; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_IsRegisteredAsSubresourceUnderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsRegisteredAsSubresourceUnder(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subresourceDomain, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(sessionID, subresourceDomain, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class DomainIDExistsInDatabase {
public:
    using Arguments = std::tuple<PAL::SessionID, int>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DomainIDExistsInDatabase; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DomainIDExistsInDatabaseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    DomainIDExistsInDatabase(const PAL::SessionID& sessionID, const int& domainID)
        : m_arguments(sessionID, domainID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const int&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class LogFrameNavigation {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain, WebCore::RegistrableDomain, bool, bool, Seconds, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_LogFrameNavigation; }
    static constexpr bool isSync = false;

    LogFrameNavigation(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& targetDomain, const WebCore::RegistrableDomain& topFrameDomain, const WebCore::RegistrableDomain& sourceDomain, bool isRedirect, bool isMainFrame, const Seconds& delayAfterMainFrameDocumentLoad, bool wasPotentiallyInitiatedByUser)
        : m_arguments(sessionID, targetDomain, topFrameDomain, sourceDomain, isRedirect, isMainFrame, delayAfterMainFrameDocumentLoad, wasPotentiallyInitiatedByUser)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, bool, bool, const Seconds&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class LogUserInteraction {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_LogUserInteraction; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_LogUserInteractionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    LogUserInteraction(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(sessionID, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ResetParametersToDefaultValues {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetParametersToDefaultValues; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResetParametersToDefaultValuesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResetParametersToDefaultValues(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class ScheduleClearInMemoryAndPersistent {
public:
    using Arguments = std::tuple<PAL::SessionID, std::optional<WallTime>, WebKit::ShouldGrandfatherStatistics>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ScheduleClearInMemoryAndPersistent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ScheduleClearInMemoryAndPersistentReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ScheduleClearInMemoryAndPersistent(const PAL::SessionID& sessionID, const std::optional<WallTime>& modifiedSince, WebKit::ShouldGrandfatherStatistics shouldGrandfather)
        : m_arguments(sessionID, modifiedSince, shouldGrandfather)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const std::optional<WallTime>&, WebKit::ShouldGrandfatherStatistics> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ScheduleCookieBlockingUpdate {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ScheduleCookieBlockingUpdate; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ScheduleCookieBlockingUpdateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ScheduleCookieBlockingUpdate(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class ScheduleStatisticsAndDataRecordsProcessing {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ScheduleStatisticsAndDataRecordsProcessing; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ScheduleStatisticsAndDataRecordsProcessingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ScheduleStatisticsAndDataRecordsProcessing(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class StatisticsDatabaseHasAllTables {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_StatisticsDatabaseHasAllTables; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_StatisticsDatabaseHasAllTablesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit StatisticsDatabaseHasAllTables(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetCacheMaxAgeCapForPrevalentResources {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetCacheMaxAgeCapForPrevalentResources; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetCacheMaxAgeCapForPrevalentResourcesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetCacheMaxAgeCapForPrevalentResources(const PAL::SessionID& sessionID, const Seconds& seconds)
        : m_arguments(sessionID, seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetGrandfathered {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetGrandfathered; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetGrandfatheredReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetGrandfathered(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain, bool isGrandfathered)
        : m_arguments(sessionID, resourceDomain, isGrandfathered)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class GetResourceLoadStatisticsDataSummary {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetResourceLoadStatisticsDataSummary; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetResourceLoadStatisticsDataSummaryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::WebResourceLoadStatisticsStore::ThirdPartyData>>;
    explicit GetResourceLoadStatisticsDataSummary(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetGrandfatheringTime {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetGrandfatheringTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetGrandfatheringTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetGrandfatheringTime(const PAL::SessionID& sessionID, const Seconds& seconds)
        : m_arguments(sessionID, seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetMaxStatisticsEntries {
public:
    using Arguments = std::tuple<PAL::SessionID, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetMaxStatisticsEntries; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetMaxStatisticsEntriesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetMaxStatisticsEntries(const PAL::SessionID& sessionID, uint64_t maximumEntryCount)
        : m_arguments(sessionID, maximumEntryCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, uint64_t> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetMinimumTimeBetweenDataRecordsRemoval {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetMinimumTimeBetweenDataRecordsRemoval; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetMinimumTimeBetweenDataRecordsRemovalReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetMinimumTimeBetweenDataRecordsRemoval(const PAL::SessionID& sessionID, const Seconds& seconds)
        : m_arguments(sessionID, seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetPruneEntriesDownTo {
public:
    using Arguments = std::tuple<PAL::SessionID, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPruneEntriesDownTo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPruneEntriesDownToReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPruneEntriesDownTo(const PAL::SessionID& sessionID, uint64_t maximumEntryCount)
        : m_arguments(sessionID, maximumEntryCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, uint64_t> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetShouldClassifyResourcesBeforeDataRecordsRemoval {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemoval; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemovalReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetShouldClassifyResourcesBeforeDataRecordsRemoval(const PAL::SessionID& sessionID, bool value)
        : m_arguments(sessionID, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetNotifyPagesWhenDataRecordsWereScanned {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetNotifyPagesWhenDataRecordsWereScanned; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetNotifyPagesWhenDataRecordsWereScannedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetNotifyPagesWhenDataRecordsWereScanned(const PAL::SessionID& sessionID, bool value)
        : m_arguments(sessionID, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetResourceLoadStatisticsTimeAdvanceForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetResourceLoadStatisticsTimeAdvanceForTesting(const PAL::SessionID& sessionID, const Seconds& time)
        : m_arguments(sessionID, time)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetIsRunningResourceLoadStatisticsTest {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetIsRunningResourceLoadStatisticsTest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetIsRunningResourceLoadStatisticsTestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetIsRunningResourceLoadStatisticsTest(const PAL::SessionID& sessionID, bool value)
        : m_arguments(sessionID, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetResourceLoadStatisticsDebugMode {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetResourceLoadStatisticsDebugMode; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetResourceLoadStatisticsDebugModeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetResourceLoadStatisticsDebugMode(const PAL::SessionID& sessionID, bool debugMode)
        : m_arguments(sessionID, debugMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetVeryPrevalentResource {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetVeryPrevalentResource; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetVeryPrevalentResourceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetVeryPrevalentResource(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& resourceDomain)
        : m_arguments(sessionID, resourceDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetSubframeUnderTopFrameDomain {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetSubframeUnderTopFrameDomain; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetSubframeUnderTopFrameDomainReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetSubframeUnderTopFrameDomain(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subFrameDomain, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(sessionID, subFrameDomain, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetSubresourceUnderTopFrameDomain {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetSubresourceUnderTopFrameDomain; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetSubresourceUnderTopFrameDomainReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetSubresourceUnderTopFrameDomain(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subresourceDomain, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(sessionID, subresourceDomain, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetSubresourceUniqueRedirectTo {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetSubresourceUniqueRedirectTo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetSubresourceUniqueRedirectToReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetSubresourceUniqueRedirectTo(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subresourceDomain, const WebCore::RegistrableDomain& redirectedToDomain)
        : m_arguments(sessionID, subresourceDomain, redirectedToDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetSubresourceUniqueRedirectFrom {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetSubresourceUniqueRedirectFrom; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetSubresourceUniqueRedirectFromReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetSubresourceUniqueRedirectFrom(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& subresourceDomain, const WebCore::RegistrableDomain& redirectedFromDomain)
        : m_arguments(sessionID, subresourceDomain, redirectedFromDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetTimeToLiveUserInteraction {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetTimeToLiveUserInteraction; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetTimeToLiveUserInteractionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetTimeToLiveUserInteraction(const PAL::SessionID& sessionID, const Seconds& seconds)
        : m_arguments(sessionID, seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetTopFrameUniqueRedirectTo {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetTopFrameUniqueRedirectTo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetTopFrameUniqueRedirectToReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetTopFrameUniqueRedirectTo(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& topFrameDomain, const WebCore::RegistrableDomain& redirectedToDomain)
        : m_arguments(sessionID, topFrameDomain, redirectedToDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetTopFrameUniqueRedirectFrom {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetTopFrameUniqueRedirectFrom; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetTopFrameUniqueRedirectFromReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetTopFrameUniqueRedirectFrom(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& topFrameDomain, const WebCore::RegistrableDomain& redirectedFromDomain)
        : m_arguments(sessionID, topFrameDomain, redirectedFromDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ResetCacheMaxAgeCapForPrevalentResources {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetCacheMaxAgeCapForPrevalentResources; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResetCacheMaxAgeCapForPrevalentResourcesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResetCacheMaxAgeCapForPrevalentResources(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class DidCommitCrossSiteLoadWithDataTransfer {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain, OptionSet<WebCore::CrossSiteNavigationDataTransfer::Flag>, WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DidCommitCrossSiteLoadWithDataTransfer; }
    static constexpr bool isSync = false;

    DidCommitCrossSiteLoadWithDataTransfer(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& fromDomain, const WebCore::RegistrableDomain& toDomain, const OptionSet<WebCore::CrossSiteNavigationDataTransfer::Flag>& navigationDataTransfer, const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::PageIdentifier& webPageID)
        : m_arguments(sessionID, fromDomain, toDomain, navigationDataTransfer, webPageProxyID, webPageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, const OptionSet<WebCore::CrossSiteNavigationDataTransfer::Flag>&, const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetCrossSiteLoadWithLinkDecorationForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetCrossSiteLoadWithLinkDecorationForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& fromDomain, const WebCore::RegistrableDomain& toDomain)
        : m_arguments(sessionID, fromDomain, toDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ResetCrossSiteLoadsWithLinkDecorationForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResetCrossSiteLoadsWithLinkDecorationForTesting(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class DeleteCookiesForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DeleteCookiesForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DeleteCookiesForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteCookiesForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& domain, bool includeHttpOnlyCookies)
        : m_arguments(sessionID, domain, includeHttpOnlyCookies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class HasIsolatedSession {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_HasIsolatedSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_HasIsolatedSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    HasIsolatedSession(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& domain)
        : m_arguments(sessionID, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class CloseITPDatabase {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CloseITPDatabase; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_CloseITPDatabaseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit CloseITPDatabase(const PAL::SessionID& sessionID)
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
#endif

#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
class SetAppBoundDomainsForResourceLoadStatistics {
public:
    using Arguments = std::tuple<PAL::SessionID, HashSet<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetAppBoundDomainsForResourceLoadStatistics; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetAppBoundDomainsForResourceLoadStatisticsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetAppBoundDomainsForResourceLoadStatistics(const PAL::SessionID& sessionID, const HashSet<WebCore::RegistrableDomain>& appBoundDomains)
        : m_arguments(sessionID, appBoundDomains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const HashSet<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
class SetManagedDomainsForResourceLoadStatistics {
public:
    using Arguments = std::tuple<PAL::SessionID, HashSet<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetManagedDomainsForResourceLoadStatistics; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetManagedDomainsForResourceLoadStatisticsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetManagedDomainsForResourceLoadStatistics(const PAL::SessionID& sessionID, const HashSet<WebCore::RegistrableDomain>& appBoundDomains)
        : m_arguments(sessionID, appBoundDomains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const HashSet<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetShouldDowngradeReferrerForTesting {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetShouldDowngradeReferrerForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetShouldDowngradeReferrerForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetShouldDowngradeReferrerForTesting(bool enabled)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetThirdPartyCookieBlockingMode {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ThirdPartyCookieBlockingMode>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetThirdPartyCookieBlockingMode; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetThirdPartyCookieBlockingModeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetThirdPartyCookieBlockingMode(const PAL::SessionID& sessionID, WebCore::ThirdPartyCookieBlockingMode blockingMode)
        : m_arguments(sessionID, blockingMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, WebCore::ThirdPartyCookieBlockingMode> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetShouldEnbleSameSiteStrictEnforcementForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::SameSiteStrictEnforcementEnabled>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetShouldEnbleSameSiteStrictEnforcementForTesting(const PAL::SessionID& sessionID, WebCore::SameSiteStrictEnforcementEnabled enabled)
        : m_arguments(sessionID, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, WebCore::SameSiteStrictEnforcementEnabled> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetFirstPartyWebsiteDataRemovalModeForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::FirstPartyWebsiteDataRemovalMode>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetFirstPartyWebsiteDataRemovalModeForTesting(const PAL::SessionID& sessionID, WebCore::FirstPartyWebsiteDataRemovalMode mode)
        : m_arguments(sessionID, mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, WebCore::FirstPartyWebsiteDataRemovalMode> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetToSameSiteStrictCookiesForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetToSameSiteStrictCookiesForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetToSameSiteStrictCookiesForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetToSameSiteStrictCookiesForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& domain)
        : m_arguments(sessionID, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetFirstPartyHostCNAMEDomainForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, String, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetFirstPartyHostCNAMEDomainForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetFirstPartyHostCNAMEDomainForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetFirstPartyHostCNAMEDomainForTesting(const PAL::SessionID& sessionID, const String& firstPartyHost, const WebCore::RegistrableDomain& cnameDomain)
        : m_arguments(sessionID, firstPartyHost, cnameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetThirdPartyCNAMEDomainForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetThirdPartyCNAMEDomainForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetThirdPartyCNAMEDomainForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetThirdPartyCNAMEDomainForTesting(const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& domain)
        : m_arguments(sessionID, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

class SetPrivateClickMeasurementDebugMode {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementDebugMode; }
    static constexpr bool isSync = false;

    SetPrivateClickMeasurementDebugMode(const PAL::SessionID& sessionID, bool debugMode)
        : m_arguments(sessionID, debugMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};

class SetBlobRegistryTopOriginPartitioningEnabled {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetBlobRegistryTopOriginPartitioningEnabled; }
    static constexpr bool isSync = false;

    SetBlobRegistryTopOriginPartitioningEnabled(const PAL::SessionID& sessionID, bool enabled)
        : m_arguments(sessionID, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};

class SetSessionIsControlledByAutomation {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetSessionIsControlledByAutomation; }
    static constexpr bool isSync = false;

    SetSessionIsControlledByAutomation(const PAL::SessionID& sessionID, bool controlled)
        : m_arguments(sessionID, controlled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};

class RegisterURLSchemeAsSecure {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RegisterURLSchemeAsSecure; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsSecure(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsBypassingContentSecurityPolicy {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsBypassingContentSecurityPolicy(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsLocal {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RegisterURLSchemeAsLocal; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsLocal(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsNoAccess {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RegisterURLSchemeAsNoAccess; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsNoAccess(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SyncLocalStorage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SyncLocalStorage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SyncLocalStorageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class StoreServiceWorkerRegistrations {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_StoreServiceWorkerRegistrations; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_StoreServiceWorkerRegistrationsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit StoreServiceWorkerRegistrations(const PAL::SessionID& sessionID)
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

class StorePrivateClickMeasurement {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::PrivateClickMeasurement>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_StorePrivateClickMeasurement; }
    static constexpr bool isSync = false;

    StorePrivateClickMeasurement(const PAL::SessionID& sessionID, const WebCore::PrivateClickMeasurement& privateClickMeasurement)
        : m_arguments(sessionID, privateClickMeasurement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::PrivateClickMeasurement&> m_arguments;
};

class DumpPrivateClickMeasurement {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DumpPrivateClickMeasurement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DumpPrivateClickMeasurementReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit DumpPrivateClickMeasurement(const PAL::SessionID& sessionID)
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

class ClearPrivateClickMeasurement {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearPrivateClickMeasurement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearPrivateClickMeasurementReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ClearPrivateClickMeasurement(const PAL::SessionID& sessionID)
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

class SetPrivateClickMeasurementOverrideTimerForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementOverrideTimerForTesting(const PAL::SessionID& sessionID, bool value)
        : m_arguments(sessionID, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};

class MarkAttributedPrivateClickMeasurementsAsExpiredForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit MarkAttributedPrivateClickMeasurementsAsExpiredForTesting(const PAL::SessionID& sessionID)
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

class SetPrivateClickMeasurementEphemeralMeasurementForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementEphemeralMeasurementForTesting(const PAL::SessionID& sessionID, bool value)
        : m_arguments(sessionID, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, bool> m_arguments;
};

class SimulatePrivateClickMeasurementSessionRestart {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SimulatePrivateClickMeasurementSessionRestart; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SimulatePrivateClickMeasurementSessionRestartReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SimulatePrivateClickMeasurementSessionRestart(const PAL::SessionID& sessionID)
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

class SetPrivateClickMeasurementTokenPublicKeyURLForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementTokenPublicKeyURLForTesting(const PAL::SessionID& sessionID, const URL& url)
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

class SetPrivateClickMeasurementTokenSignatureURLForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementTokenSignatureURLForTesting(const PAL::SessionID& sessionID, const URL& url)
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

class SetPrivateClickMeasurementAttributionReportURLsForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, URL, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementAttributionReportURLsForTesting(const PAL::SessionID& sessionID, const URL& sourceURL, const URL& destinationURL)
        : m_arguments(sessionID, sourceURL, destinationURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const URL&, const URL&> m_arguments;
};

class MarkPrivateClickMeasurementsAsExpiredForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit MarkPrivateClickMeasurementsAsExpiredForTesting(const PAL::SessionID& sessionID)
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

class SetPCMFraudPreventionValuesForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, String, String, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPCMFraudPreventionValuesForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPCMFraudPreventionValuesForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPCMFraudPreventionValuesForTesting(const PAL::SessionID& sessionID, const String& secretToken, const String& unlinkableToken, const String& signature, const String& keyID)
        : m_arguments(sessionID, secretToken, unlinkableToken, signature, keyID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&, const String&, const String&, const String&> m_arguments;
};

class SetPrivateClickMeasurementAppBundleIDForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPrivateClickMeasurementAppBundleIDForTesting(const PAL::SessionID& sessionID, const String& appBundleIDForTesting)
        : m_arguments(sessionID, appBundleIDForTesting)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};

class ClosePCMDatabase {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClosePCMDatabase; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClosePCMDatabaseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ClosePCMDatabase(const PAL::SessionID& sessionID)
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

class SetServiceWorkerFetchTimeoutForTesting {
public:
    using Arguments = std::tuple<Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetServiceWorkerFetchTimeoutForTesting; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetServiceWorkerFetchTimeoutForTesting(const Seconds& seconds)
        : m_arguments(seconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Seconds&> m_arguments;
};

class ResetServiceWorkerFetchTimeoutForTesting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetServiceWorkerFetchTimeoutForTesting; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ResetQuota {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetQuota; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResetQuotaReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResetQuota(const PAL::SessionID& sessionID)
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

#if PLATFORM(IOS_FAMILY)
class SetBackupExclusionPeriodForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetBackupExclusionPeriodForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetBackupExclusionPeriodForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetBackupExclusionPeriodForTesting(const PAL::SessionID& sessionID, const Seconds& period)
        : m_arguments(sessionID, period)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Seconds&> m_arguments;
};
#endif

class ResetStoragePersistedState {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResetStoragePersistedState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResetStoragePersistedStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ResetStoragePersistedState(const PAL::SessionID& sessionID)
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

class CloneSessionStorageForWebPage {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPageProxyIdentifier, WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CloneSessionStorageForWebPage; }
    static constexpr bool isSync = false;

    CloneSessionStorageForWebPage(const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& sourcePage, const WebKit::WebPageProxyIdentifier& destinationPage)
        : m_arguments(sessionID, sourcePage, destinationPage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&, const WebKit::WebPageProxyIdentifier&> m_arguments;
};

class DidIncreaseQuota {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ClientOrigin, WebKit::QuotaIncreaseRequestIdentifier, std::optional<uint64_t>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DidIncreaseQuota; }
    static constexpr bool isSync = false;

    DidIncreaseQuota(const PAL::SessionID& sessionID, const WebCore::ClientOrigin& origin, const WebKit::QuotaIncreaseRequestIdentifier& identifier, const std::optional<uint64_t>& newQuota)
        : m_arguments(sessionID, origin, identifier, newQuota)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::ClientOrigin&, const WebKit::QuotaIncreaseRequestIdentifier&, const std::optional<uint64_t>&> m_arguments;
};

#if ENABLE(APP_BOUND_DOMAINS)
class HasAppBoundSession {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_HasAppBoundSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_HasAppBoundSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit HasAppBoundSession(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(APP_BOUND_DOMAINS)
class ClearAppBoundSession {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearAppBoundSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearAppBoundSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ClearAppBoundSession(const PAL::SessionID& sessionID)
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
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
class DisableServiceWorkerEntitlement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DisableServiceWorkerEntitlement; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
class ClearServiceWorkerEntitlementOverride {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearServiceWorkerEntitlementOverride; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearServiceWorkerEntitlementOverrideReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class UpdateBundleIdentifier {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_UpdateBundleIdentifier; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_UpdateBundleIdentifierReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit UpdateBundleIdentifier(const String& bundleIdentifier)
        : m_arguments(bundleIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class ClearBundleIdentifier {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearBundleIdentifier; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearBundleIdentifierReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA)
class AppPrivacyReportTestingData {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AppPrivacyReportTestingData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_AppPrivacyReportTestingDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::AppPrivacyReportTestingData>;
    explicit AppPrivacyReportTestingData(const PAL::SessionID& sessionID)
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
#endif

#if PLATFORM(COCOA)
class ClearAppPrivacyReportTestingData {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearAppPrivacyReportTestingData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClearAppPrivacyReportTestingDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ClearAppPrivacyReportTestingData(const PAL::SessionID& sessionID)
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
#endif

class AddWebPageNetworkParameters {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPageProxyIdentifier, WebKit::WebPageNetworkParameters>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AddWebPageNetworkParameters; }
    static constexpr bool isSync = false;

    AddWebPageNetworkParameters(const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& pageID, const WebKit::WebPageNetworkParameters& parameters)
        : m_arguments(sessionID, pageID, parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&, const WebKit::WebPageNetworkParameters&> m_arguments;
};

class RemoveWebPageNetworkParameters {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_RemoveWebPageNetworkParameters; }
    static constexpr bool isSync = false;

    RemoveWebPageNetworkParameters(const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& pageID)
        : m_arguments(sessionID, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&> m_arguments;
};

class CountNonDefaultSessionSets {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_CountNonDefaultSessionSets; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_CountNonDefaultSessionSetsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<size_t>;
    explicit CountNonDefaultSessionSets(const PAL::SessionID& sessionID)
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

#if ENABLE(CFPREFS_DIRECT_MODE)
class NotifyPreferencesChanged {
public:
    using Arguments = std::tuple<String, String, std::optional<String>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_NotifyPreferencesChanged; }
    static constexpr bool isSync = false;

    NotifyPreferencesChanged(const String& domain, const String& key, const std::optional<String>& encodedValue)
        : m_arguments(domain, key, encodedValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<String>&> m_arguments;
};
#endif

class TerminateRemoteWorkerContextConnectionWhenPossible {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, PAL::SessionID, WebCore::RegistrableDomain, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_TerminateRemoteWorkerContextConnectionWhenPossible; }
    static constexpr bool isSync = false;

    TerminateRemoteWorkerContextConnectionWhenPossible(WebKit::RemoteWorkerType workerType, const PAL::SessionID& sessionID, const WebCore::RegistrableDomain& registrableDomain, const WebCore::ProcessIdentifier& processIdentifier)
        : m_arguments(workerType, sessionID, registrableDomain, processIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const PAL::SessionID&, const WebCore::RegistrableDomain&, const WebCore::ProcessIdentifier&> m_arguments;
};

#if ENABLE(SERVICE_WORKER)
class GetPendingPushMessages {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetPendingPushMessages; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetPendingPushMessagesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::WebPushMessage>>;
    explicit GetPendingPushMessages(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(SERVICE_WORKER)
class ProcessPushMessage {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPushMessage, WebCore::PushPermissionState>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ProcessPushMessage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ProcessPushMessageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ProcessPushMessage(const PAL::SessionID& sessionID, const WebKit::WebPushMessage& pushMessage, WebCore::PushPermissionState pushPermissionState)
        : m_arguments(sessionID, pushMessage, pushPermissionState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPushMessage&, WebCore::PushPermissionState> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class ProcessNotificationEvent {
public:
    using Arguments = std::tuple<WebCore::NotificationData, WebCore::NotificationEventType>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ProcessNotificationEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ProcessNotificationEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ProcessNotificationEvent(const WebCore::NotificationData& data, WebCore::NotificationEventType eventType)
        : m_arguments(data, eventType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::NotificationData&, WebCore::NotificationEventType> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class GetAllBackgroundFetchIdentifiers {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetAllBackgroundFetchIdentifiers; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetAllBackgroundFetchIdentifiersReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit GetAllBackgroundFetchIdentifiers(const PAL::SessionID& sessionID)
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
#endif

#if ENABLE(SERVICE_WORKER)
class GetBackgroundFetchState {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetBackgroundFetchState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetBackgroundFetchStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::BackgroundFetchState>>;
    GetBackgroundFetchState(const PAL::SessionID& sessionID, const String& identifier)
        : m_arguments(sessionID, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class AbortBackgroundFetch {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_AbortBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_AbortBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    AbortBackgroundFetch(const PAL::SessionID& sessionID, const String& identifier)
        : m_arguments(sessionID, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class PauseBackgroundFetch {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_PauseBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_PauseBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PauseBackgroundFetch(const PAL::SessionID& sessionID, const String& identifier)
        : m_arguments(sessionID, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class ResumeBackgroundFetch {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ResumeBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ResumeBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ResumeBackgroundFetch(const PAL::SessionID& sessionID, const String& identifier)
        : m_arguments(sessionID, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class ClickBackgroundFetch {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClickBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_ClickBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ClickBackgroundFetch(const PAL::SessionID& sessionID, const String& identifier)
        : m_arguments(sessionID, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&> m_arguments;
};
#endif

class SetPushAndNotificationsEnabledForOrigin {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::SecurityOriginData, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetPushAndNotificationsEnabledForOrigin; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_SetPushAndNotificationsEnabledForOriginReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetPushAndNotificationsEnabledForOrigin(const PAL::SessionID& sessionID, const WebCore::SecurityOriginData& origin, bool enabled)
        : m_arguments(sessionID, origin, enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::SecurityOriginData&, bool> m_arguments;
};

class DeletePushAndNotificationRegistration {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::SecurityOriginData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_DeletePushAndNotificationRegistration; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_DeletePushAndNotificationRegistrationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    DeletePushAndNotificationRegistration(const PAL::SessionID& sessionID, const WebCore::SecurityOriginData& origin)
        : m_arguments(sessionID, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::SecurityOriginData&> m_arguments;
};

class GetOriginsWithPushAndNotificationPermissions {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_GetOriginsWithPushAndNotificationPermissions; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_GetOriginsWithPushAndNotificationPermissionsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::SecurityOriginData>>;
    explicit GetOriginsWithPushAndNotificationPermissions(const PAL::SessionID& sessionID)
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

class HasPushSubscriptionForTesting {
public:
    using Arguments = std::tuple<PAL::SessionID, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_HasPushSubscriptionForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcess_HasPushSubscriptionForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    HasPushSubscriptionForTesting(const PAL::SessionID& sessionID, const URL& scopeURL)
        : m_arguments(sessionID, scopeURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const URL&> m_arguments;
};

#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
class SetEmulatedConditions {
public:
    using Arguments = std::tuple<PAL::SessionID, std::optional<int64_t>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetEmulatedConditions; }
    static constexpr bool isSync = false;

    SetEmulatedConditions(const PAL::SessionID& sessionID, const std::optional<int64_t>& bytesPerSecondLimit)
        : m_arguments(sessionID, bytesPerSecondLimit)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const std::optional<int64_t>&> m_arguments;
};
#endif

#if HAVE(NW_PROXY_CONFIG)
class ClearProxyConfigData {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_ClearProxyConfigData; }
    static constexpr bool isSync = false;

    explicit ClearProxyConfigData(const PAL::SessionID& sessionID)
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
#endif

#if HAVE(NW_PROXY_CONFIG)
class SetProxyConfigData {
public:
    using Arguments = std::tuple<PAL::SessionID, Vector<std::pair<Vector<uint8_t>, WTF::UUID>>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcess_SetProxyConfigData; }
    static constexpr bool isSync = false;

    SetProxyConfigData(const PAL::SessionID& sessionID, const Vector<std::pair<Vector<uint8_t>, WTF::UUID>>& proxyConfigurations)
        : m_arguments(sessionID, proxyConfigurations)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const Vector<std::pair<Vector<uint8_t>, WTF::UUID>>&> m_arguments;
};
#endif

} // namespace NetworkProcess
} // namespace Messages
