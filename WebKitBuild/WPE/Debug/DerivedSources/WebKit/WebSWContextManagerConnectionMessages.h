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

#if ENABLE(SERVICE_WORKER)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DataReference.h"
#include "MessageNames.h"
#include <WebCore/FetchIdentifier.h>
#include <WebCore/ScriptBuffer.h>
#include <WebCore/ServiceWorkerClientData.h>
#include <WebCore/ServiceWorkerData.h>
#include <WebCore/ServiceWorkerIdentifier.h>
#include <WebCore/ServiceWorkerTypes.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/URLHash.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class FormDataReference;
}

namespace WebCore {
class ResourceError;
class ResourceRequest;
class ResourceResponse;
class ScriptBuffer;
enum class LastNavigationWasAppInitiated : bool;
enum class NotificationEventType : bool;
enum class WorkerThreadMode : bool;
struct BackgroundFetchInformation;
struct FetchOptions;
struct MessageWithMessagePorts;
struct NotificationData;
struct ServiceWorkerContextData;
struct ServiceWorkerData;
}

namespace WebKit {
struct WebPreferencesStore;
}

namespace Messages {
namespace WebSWContextManagerConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSWContextManagerConnection;
}

class InstallServiceWorker {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerContextData, WebCore::ServiceWorkerData, String, WebCore::WorkerThreadMode>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_InstallServiceWorker; }
    static constexpr bool isSync = false;

    InstallServiceWorker(const WebCore::ServiceWorkerContextData& contextData, const WebCore::ServiceWorkerData& workerData, const String& userAgent, WebCore::WorkerThreadMode workerThreadMode)
        : m_arguments(contextData, workerData, userAgent, workerThreadMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerContextData&, const WebCore::ServiceWorkerData&, const String&, WebCore::WorkerThreadMode> m_arguments;
};

class UpdateAppInitiatedValue {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::LastNavigationWasAppInitiated>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_UpdateAppInitiatedValue; }
    static constexpr bool isSync = false;

    UpdateAppInitiatedValue(const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, WebCore::LastNavigationWasAppInitiated lastNavigationWasAppInitiated)
        : m_arguments(serviceWorkerIdentifier, lastNavigationWasAppInitiated)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, WebCore::LastNavigationWasAppInitiated> m_arguments;
};

class StartFetch {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier, WebCore::ResourceRequest, WebCore::FetchOptions, IPC::FormDataReference, String, bool, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_StartFetch; }
    static constexpr bool isSync = false;

    StartFetch(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& fetchIdentifier, const WebCore::ResourceRequest& request, const WebCore::FetchOptions& options, const IPC::FormDataReference& requestBody, const String& referrer, bool isServiceWorkerNavigationPreloadEnabled, const String& clientIdentifier, const String& resutlingClientIdentifier)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, fetchIdentifier, request, options, requestBody, referrer, isServiceWorkerNavigationPreloadEnabled, clientIdentifier, resutlingClientIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&, const WebCore::ResourceRequest&, const WebCore::FetchOptions&, const IPC::FormDataReference&, const String&, bool, const String&, const String&> m_arguments;
};

class CancelFetch {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_CancelFetch; }
    static constexpr bool isSync = false;

    CancelFetch(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& fetchIdentifier)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, fetchIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&> m_arguments;
};

class ContinueDidReceiveFetchResponse {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_ContinueDidReceiveFetchResponse; }
    static constexpr bool isSync = false;

    ContinueDidReceiveFetchResponse(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& fetchIdentifier)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, fetchIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&> m_arguments;
};

class PostMessageToServiceWorker {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::MessageWithMessagePorts, WebCore::ServiceWorkerOrClientData>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_PostMessageToServiceWorker; }
    static constexpr bool isSync = false;

    PostMessageToServiceWorker(const WebCore::ServiceWorkerIdentifier& destinationIdentifier, const WebCore::MessageWithMessagePorts& message, const WebCore::ServiceWorkerOrClientData& sourceData)
        : m_arguments(destinationIdentifier, message, sourceData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::MessageWithMessagePorts&, const WebCore::ServiceWorkerOrClientData&> m_arguments;
};

class FireInstallEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FireInstallEvent; }
    static constexpr bool isSync = false;

    explicit FireInstallEvent(const WebCore::ServiceWorkerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class FireActivateEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FireActivateEvent; }
    static constexpr bool isSync = false;

    explicit FireActivateEvent(const WebCore::ServiceWorkerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class FirePushEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, std::optional<IPC::DataReference>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FirePushEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWContextManagerConnection_FirePushEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FirePushEvent(const WebCore::ServiceWorkerIdentifier& identifier, const std::optional<IPC::DataReference>& data)
        : m_arguments(identifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const std::optional<IPC::DataReference>&> m_arguments;
};

class FireNotificationEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::NotificationData, WebCore::NotificationEventType>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FireNotificationEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWContextManagerConnection_FireNotificationEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FireNotificationEvent(const WebCore::ServiceWorkerIdentifier& identifier, const WebCore::NotificationData& data, WebCore::NotificationEventType type)
        : m_arguments(identifier, data, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::NotificationData&, WebCore::NotificationEventType> m_arguments;
};

class FireBackgroundFetchEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::BackgroundFetchInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FireBackgroundFetchEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWContextManagerConnection_FireBackgroundFetchEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FireBackgroundFetchEvent(const WebCore::ServiceWorkerIdentifier& identifier, const WebCore::BackgroundFetchInformation& info)
        : m_arguments(identifier, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::BackgroundFetchInformation&> m_arguments;
};

class FireBackgroundFetchClickEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::BackgroundFetchInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_FireBackgroundFetchClickEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWContextManagerConnection_FireBackgroundFetchClickEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FireBackgroundFetchClickEvent(const WebCore::ServiceWorkerIdentifier& identifier, const WebCore::BackgroundFetchInformation& info)
        : m_arguments(identifier, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::BackgroundFetchInformation&> m_arguments;
};

class TerminateWorker {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_TerminateWorker; }
    static constexpr bool isSync = false;

    explicit TerminateWorker(const WebCore::ServiceWorkerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
class DidSaveScriptsToDisk {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::ScriptBuffer, HashMap<URL, WebCore::ScriptBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_DidSaveScriptsToDisk; }
    static constexpr bool isSync = false;

    DidSaveScriptsToDisk(const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::ScriptBuffer& script, const HashMap<URL, WebCore::ScriptBuffer>& importedScripts)
        : m_arguments(serviceWorkerIdentifier, script, importedScripts)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::ScriptBuffer&, const HashMap<URL, WebCore::ScriptBuffer>&> m_arguments;
};
#endif

class MatchAllCompleted {
public:
    using Arguments = std::tuple<uint64_t, Vector<WebCore::ServiceWorkerClientData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_MatchAllCompleted; }
    static constexpr bool isSync = false;

    MatchAllCompleted(uint64_t matchAllRequestIdentifier, const Vector<WebCore::ServiceWorkerClientData>& clientsData)
        : m_arguments(matchAllRequestIdentifier, clientsData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const Vector<WebCore::ServiceWorkerClientData>&> m_arguments;
};

class SkipWaitingCompleted {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_SkipWaitingCompleted; }
    static constexpr bool isSync = false;

    explicit SkipWaitingCompleted(uint64_t matchAllRequestIdentifier)
        : m_arguments(matchAllRequestIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class SetUserAgent {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_SetUserAgent; }
    static constexpr bool isSync = false;

    explicit SetUserAgent(const String& userAgent)
        : m_arguments(userAgent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class UpdatePreferencesStore {
public:
    using Arguments = std::tuple<WebKit::WebPreferencesStore>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_UpdatePreferencesStore; }
    static constexpr bool isSync = false;

    explicit UpdatePreferencesStore(const WebKit::WebPreferencesStore& store)
        : m_arguments(store)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPreferencesStore&> m_arguments;
};

class Close {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_Close; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetThrottleState {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_SetThrottleState; }
    static constexpr bool isSync = false;

    explicit SetThrottleState(bool isThrottleable)
        : m_arguments(isThrottleable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ConvertFetchToDownload {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_ConvertFetchToDownload; }
    static constexpr bool isSync = false;

    ConvertFetchToDownload(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& identifier)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&> m_arguments;
};

class NavigationPreloadIsReady {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_NavigationPreloadIsReady; }
    static constexpr bool isSync = false;

    NavigationPreloadIsReady(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& identifier, const WebCore::ResourceResponse& response)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, identifier, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&, const WebCore::ResourceResponse&> m_arguments;
};

class NavigationPreloadFailed {
public:
    using Arguments = std::tuple<WebCore::SWServerConnectionIdentifier, WebCore::ServiceWorkerIdentifier, WebCore::FetchIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWContextManagerConnection_NavigationPreloadFailed; }
    static constexpr bool isSync = false;

    NavigationPreloadFailed(const WebCore::SWServerConnectionIdentifier& serverConnectionIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::FetchIdentifier& identifier, const WebCore::ResourceError& error)
        : m_arguments(serverConnectionIdentifier, serviceWorkerIdentifier, identifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SWServerConnectionIdentifier&, const WebCore::ServiceWorkerIdentifier&, const WebCore::FetchIdentifier&, const WebCore::ResourceError&> m_arguments;
};

} // namespace WebSWContextManagerConnection
} // namespace Messages

#endif // ENABLE(SERVICE_WORKER)
