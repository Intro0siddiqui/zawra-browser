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
#include "MessageNames.h"
#include "RetrieveRecordResponseBodyCallbackIdentifier.h"
#include <WebCore/BackgroundFetchInformation.h>
#include <WebCore/BackgroundFetchRecordIdentifier.h>
#include <WebCore/BackgroundFetchRecordInformation.h>
#include <WebCore/BackgroundFetchRequest.h>
#include <WebCore/ExceptionData.h>
#include <WebCore/NavigationPreloadState.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/PushSubscriptionData.h>
#include <WebCore/PushSubscriptionIdentifier.h>
#include <WebCore/ResourceResponse.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/ServiceWorkerIdentifier.h>
#include <WebCore/ServiceWorkerRegistrationData.h>
#include <WebCore/ServiceWorkerTypes.h>
#include <optional>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class SecurityOriginData;
class ServiceWorkerRegistrationKey;
struct BackgroundFetchOptions;
struct ClientOrigin;
struct MessageWithMessagePorts;
struct RetrieveRecordsOptions;
struct ServiceWorkerClientData;
struct ServiceWorkerJobData;
struct ServiceWorkerJobDataIdentifier;
struct WorkerFetchResult;
}

namespace Messages {
namespace WebSWServerConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSWServerConnection;
}

class ScheduleJobInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobData>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_ScheduleJobInServer; }
    static constexpr bool isSync = false;

    explicit ScheduleJobInServer(const WebCore::ServiceWorkerJobData& jobData)
        : m_arguments(jobData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobData&> m_arguments;
};

class ScheduleUnregisterJobInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobIdentifier, WebCore::ServiceWorkerRegistrationIdentifier, WebCore::ServiceWorkerOrClientIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_ScheduleUnregisterJobInServer; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_ScheduleUnregisterJobInServerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ExceptionData>>;
    ScheduleUnregisterJobInServer(const WebCore::ServiceWorkerJobIdentifier& jobIdentifier, const WebCore::ServiceWorkerRegistrationIdentifier& identifier, const WebCore::ServiceWorkerOrClientIdentifier& documentIdentifier)
        : m_arguments(jobIdentifier, identifier, documentIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobIdentifier&, const WebCore::ServiceWorkerRegistrationIdentifier&, const WebCore::ServiceWorkerOrClientIdentifier&> m_arguments;
};

class FinishFetchingScriptInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobDataIdentifier, WebCore::ServiceWorkerRegistrationKey, WebCore::WorkerFetchResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_FinishFetchingScriptInServer; }
    static constexpr bool isSync = false;

    FinishFetchingScriptInServer(const WebCore::ServiceWorkerJobDataIdentifier& jobDataIdentifier, const WebCore::ServiceWorkerRegistrationKey& registrationKey, const WebCore::WorkerFetchResult& result)
        : m_arguments(jobDataIdentifier, registrationKey, result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobDataIdentifier&, const WebCore::ServiceWorkerRegistrationKey&, const WebCore::WorkerFetchResult&> m_arguments;
};

class AddServiceWorkerRegistrationInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_AddServiceWorkerRegistrationInServer; }
    static constexpr bool isSync = false;

    explicit AddServiceWorkerRegistrationInServer(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class RemoveServiceWorkerRegistrationInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_RemoveServiceWorkerRegistrationInServer; }
    static constexpr bool isSync = false;

    explicit RemoveServiceWorkerRegistrationInServer(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class PostMessageToServiceWorker {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::MessageWithMessagePorts, WebCore::ServiceWorkerOrClientIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_PostMessageToServiceWorker; }
    static constexpr bool isSync = false;

    PostMessageToServiceWorker(const WebCore::ServiceWorkerIdentifier& destination, const WebCore::MessageWithMessagePorts& message, const WebCore::ServiceWorkerOrClientIdentifier& source)
        : m_arguments(destination, message, source)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const WebCore::MessageWithMessagePorts&, const WebCore::ServiceWorkerOrClientIdentifier&> m_arguments;
};

class DidResolveRegistrationPromise {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationKey>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_DidResolveRegistrationPromise; }
    static constexpr bool isSync = false;

    explicit DidResolveRegistrationPromise(const WebCore::ServiceWorkerRegistrationKey& key)
        : m_arguments(key)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationKey&> m_arguments;
};

class MatchRegistration {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_MatchRegistration; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_MatchRegistrationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ServiceWorkerRegistrationData>>;
    MatchRegistration(const WebCore::SecurityOriginData& topOrigin, const URL& clientURL)
        : m_arguments(topOrigin, clientURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const URL&> m_arguments;
};

class WhenRegistrationReady {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_WhenRegistrationReady; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_WhenRegistrationReadyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ServiceWorkerRegistrationData>>;
    WhenRegistrationReady(const WebCore::SecurityOriginData& topOrigin, const URL& clientURL)
        : m_arguments(topOrigin, clientURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const URL&> m_arguments;
};

class GetRegistrations {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_GetRegistrations; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_GetRegistrationsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::ServiceWorkerRegistrationData>>;
    GetRegistrations(const WebCore::SecurityOriginData& topOrigin, const URL& clientURL)
        : m_arguments(topOrigin, clientURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const URL&> m_arguments;
};

class RegisterServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::ServiceWorkerClientData, std::optional<WebCore::ServiceWorkerRegistrationIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_RegisterServiceWorkerClient; }
    static constexpr bool isSync = false;

    RegisterServiceWorkerClient(const WebCore::ClientOrigin& clientOrigin, const WebCore::ServiceWorkerClientData& data, const std::optional<WebCore::ServiceWorkerRegistrationIdentifier>& controllingServiceWorkerRegistrationIdentifier, const String& userAgent)
        : m_arguments(clientOrigin, data, controllingServiceWorkerRegistrationIdentifier, userAgent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::ServiceWorkerClientData&, const std::optional<WebCore::ServiceWorkerRegistrationIdentifier>&, const String&> m_arguments;
};

class UnregisterServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_UnregisterServiceWorkerClient; }
    static constexpr bool isSync = false;

    explicit UnregisterServiceWorkerClient(const WebCore::ScriptExecutionContextIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

class TerminateWorkerFromClient {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_TerminateWorkerFromClient; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_TerminateWorkerFromClientReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit TerminateWorkerFromClient(const WebCore::ServiceWorkerIdentifier& workerIdentifier)
        : m_arguments(workerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class WhenServiceWorkerIsTerminatedForTesting {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_WhenServiceWorkerIsTerminatedForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_WhenServiceWorkerIsTerminatedForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit WhenServiceWorkerIsTerminatedForTesting(const WebCore::ServiceWorkerIdentifier& workerIdentifier)
        : m_arguments(workerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class SetThrottleState {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_SetThrottleState; }
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

class StoreRegistrationsOnDisk {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_StoreRegistrationsOnDisk; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_StoreRegistrationsOnDiskReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SubscribeToPushService {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, Vector<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_SubscribeToPushService; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_SubscribeToPushServiceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::PushSubscriptionData, WebCore::ExceptionData>>;
    SubscribeToPushService(const WebCore::ServiceWorkerRegistrationIdentifier& identifier, const Vector<uint8_t>& applicationServerKey)
        : m_arguments(identifier, applicationServerKey)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const Vector<uint8_t>&> m_arguments;
};

class UnsubscribeFromPushService {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, WebCore::PushSubscriptionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_UnsubscribeFromPushService; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_UnsubscribeFromPushServiceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ExceptionData>>;
    UnsubscribeFromPushService(const WebCore::ServiceWorkerRegistrationIdentifier& serviceWorkerRegistrationIdentifier, const WebCore::PushSubscriptionIdentifier& pushSubscriptionIdentifier)
        : m_arguments(serviceWorkerRegistrationIdentifier, pushSubscriptionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const WebCore::PushSubscriptionIdentifier&> m_arguments;
};

class GetPushSubscription {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_GetPushSubscription; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_GetPushSubscriptionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<std::optional<WebCore::PushSubscriptionData>, WebCore::ExceptionData>>;
    explicit GetPushSubscription(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class GetPushPermissionState {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_GetPushPermissionState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_GetPushPermissionStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<uint8_t, WebCore::ExceptionData>>;
    explicit GetPushPermissionState(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class EnableNavigationPreload {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_EnableNavigationPreload; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_EnableNavigationPreloadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ExceptionData>>;
    explicit EnableNavigationPreload(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class DisableNavigationPreload {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_DisableNavigationPreload; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_DisableNavigationPreloadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ExceptionData>>;
    explicit DisableNavigationPreload(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class SetNavigationPreloadHeaderValue {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_SetNavigationPreloadHeaderValue; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_SetNavigationPreloadHeaderValueReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ExceptionData>>;
    SetNavigationPreloadHeaderValue(const WebCore::ServiceWorkerRegistrationIdentifier& identifier, const String& value)
        : m_arguments(identifier, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const String&> m_arguments;
};

class GetNavigationPreloadState {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_GetNavigationPreloadState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_GetNavigationPreloadStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::NavigationPreloadState, WebCore::ExceptionData>>;
    explicit GetNavigationPreloadState(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class StartBackgroundFetch {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, String, Vector<WebCore::BackgroundFetchRequest>, WebCore::BackgroundFetchOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_StartBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_StartBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::BackgroundFetchInformation, WebCore::ExceptionData>>;
    StartBackgroundFetch(const WebCore::ServiceWorkerRegistrationIdentifier& registrationIdentifier, const String& backgroundFetchIdentifier, const Vector<WebCore::BackgroundFetchRequest>& requests, const WebCore::BackgroundFetchOptions& options)
        : m_arguments(registrationIdentifier, backgroundFetchIdentifier, requests, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const String&, const Vector<WebCore::BackgroundFetchRequest>&, const WebCore::BackgroundFetchOptions&> m_arguments;
};

class BackgroundFetchInformation {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_BackgroundFetchInformation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_BackgroundFetchInformationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::BackgroundFetchInformation, WebCore::ExceptionData>>;
    BackgroundFetchInformation(const WebCore::ServiceWorkerRegistrationIdentifier& registrationIdentifier, const String& backgroundFetchIdentifier)
        : m_arguments(registrationIdentifier, backgroundFetchIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const String&> m_arguments;
};

class BackgroundFetchIdentifiers {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_BackgroundFetchIdentifiers; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_BackgroundFetchIdentifiersReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit BackgroundFetchIdentifiers(const WebCore::ServiceWorkerRegistrationIdentifier& registrationIdentifier)
        : m_arguments(registrationIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&> m_arguments;
};

class AbortBackgroundFetch {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_AbortBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_AbortBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    AbortBackgroundFetch(const WebCore::ServiceWorkerRegistrationIdentifier& registrationIdentifier, const String& backgroundFetchIdentifier)
        : m_arguments(registrationIdentifier, backgroundFetchIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const String&> m_arguments;
};

class MatchBackgroundFetch {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, String, WebCore::RetrieveRecordsOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_MatchBackgroundFetch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_MatchBackgroundFetchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::BackgroundFetchRecordInformation>>;
    MatchBackgroundFetch(const WebCore::ServiceWorkerRegistrationIdentifier& registrationIdentifier, const String& backgroundFetchIdentifier, const WebCore::RetrieveRecordsOptions& options)
        : m_arguments(registrationIdentifier, backgroundFetchIdentifier, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const String&, const WebCore::RetrieveRecordsOptions&> m_arguments;
};

class RetrieveRecordResponse {
public:
    using Arguments = std::tuple<WebCore::BackgroundFetchRecordIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_RetrieveRecordResponse; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerConnection_RetrieveRecordResponseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::ResourceResponse, WebCore::ExceptionData>>;
    explicit RetrieveRecordResponse(const WebCore::BackgroundFetchRecordIdentifier& recordIdentifier)
        : m_arguments(recordIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackgroundFetchRecordIdentifier&> m_arguments;
};

class RetrieveRecordResponseBody {
public:
    using Arguments = std::tuple<WebCore::BackgroundFetchRecordIdentifier, WebKit::RetrieveRecordResponseBodyCallbackIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerConnection_RetrieveRecordResponseBody; }
    static constexpr bool isSync = false;

    RetrieveRecordResponseBody(const WebCore::BackgroundFetchRecordIdentifier& recordIdentifier, const WebKit::RetrieveRecordResponseBodyCallbackIdentifier& callbackIdentifier)
        : m_arguments(recordIdentifier, callbackIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackgroundFetchRecordIdentifier&, const WebKit::RetrieveRecordResponseBodyCallbackIdentifier&> m_arguments;
};

} // namespace WebSWServerConnection
} // namespace Messages

#endif // ENABLE(SERVICE_WORKER)
