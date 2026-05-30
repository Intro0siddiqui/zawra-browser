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
#include "SharedMemory.h"
#include <WebCore/FetchOptions.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/ServiceWorkerClientData.h>
#include <WebCore/ServiceWorkerData.h>
#include <WebCore/ServiceWorkerIdentifier.h>
#include <WebCore/ServiceWorkerTypes.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/HashSet.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class SharedBufferReference;
}

namespace WebCore {
class ResourceError;
class ServiceWorkerRegistrationKey;
enum class ShouldNotifyWhenResolved : bool;
enum class ServiceWorkerRegistrationState : uint8_t;
enum class ServiceWorkerState : uint8_t;
enum class ServiceWorkerUpdateViaCache : uint8_t;
struct BackgroundFetchInformation;
struct ExceptionData;
struct MessageWithMessagePorts;
struct ServiceWorkerData;
struct ServiceWorkerRegistrationData;
}

namespace Messages {
namespace WebSWClientConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSWClientConnection;
}

class JobRejectedInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobIdentifier, WebCore::ExceptionData>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_JobRejectedInServer; }
    static constexpr bool isSync = false;

    JobRejectedInServer(const WebCore::ServiceWorkerJobIdentifier& jobDataIdentifier, const WebCore::ExceptionData& exception)
        : m_arguments(jobDataIdentifier, exception)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobIdentifier&, const WebCore::ExceptionData&> m_arguments;
};

class RegistrationJobResolvedInServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobIdentifier, WebCore::ServiceWorkerRegistrationData, WebCore::ShouldNotifyWhenResolved>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_RegistrationJobResolvedInServer; }
    static constexpr bool isSync = false;

    RegistrationJobResolvedInServer(const WebCore::ServiceWorkerJobIdentifier& jobDataIdentifier, const WebCore::ServiceWorkerRegistrationData& registration, WebCore::ShouldNotifyWhenResolved shouldNotifyWhenResolved)
        : m_arguments(jobDataIdentifier, registration, shouldNotifyWhenResolved)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobIdentifier&, const WebCore::ServiceWorkerRegistrationData&, WebCore::ShouldNotifyWhenResolved> m_arguments;
};

class StartScriptFetchForServer {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerJobIdentifier, WebCore::ServiceWorkerRegistrationKey, WebCore::FetchOptions::Cache>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_StartScriptFetchForServer; }
    static constexpr bool isSync = false;

    StartScriptFetchForServer(const WebCore::ServiceWorkerJobIdentifier& jobDataIdentifier, const WebCore::ServiceWorkerRegistrationKey& registrationKey, WebCore::FetchOptions::Cache cachePolicy)
        : m_arguments(jobDataIdentifier, registrationKey, cachePolicy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerJobIdentifier&, const WebCore::ServiceWorkerRegistrationKey&, WebCore::FetchOptions::Cache> m_arguments;
};

class UpdateRegistrationState {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, WebCore::ServiceWorkerRegistrationState, std::optional<WebCore::ServiceWorkerData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_UpdateRegistrationState; }
    static constexpr bool isSync = false;

    UpdateRegistrationState(const WebCore::ServiceWorkerRegistrationIdentifier& identifier, WebCore::ServiceWorkerRegistrationState state, const std::optional<WebCore::ServiceWorkerData>& serviceWorkerIdentifier)
        : m_arguments(identifier, state, serviceWorkerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, WebCore::ServiceWorkerRegistrationState, const std::optional<WebCore::ServiceWorkerData>&> m_arguments;
};

class UpdateWorkerState {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, WebCore::ServiceWorkerState>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_UpdateWorkerState; }
    static constexpr bool isSync = false;

    UpdateWorkerState(const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, WebCore::ServiceWorkerState state)
        : m_arguments(serviceWorkerIdentifier, state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, WebCore::ServiceWorkerState> m_arguments;
};

class FireUpdateFoundEvent {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_FireUpdateFoundEvent; }
    static constexpr bool isSync = false;

    explicit FireUpdateFoundEvent(const WebCore::ServiceWorkerRegistrationIdentifier& identifier)
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

class SetRegistrationLastUpdateTime {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, WallTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_SetRegistrationLastUpdateTime; }
    static constexpr bool isSync = false;

    SetRegistrationLastUpdateTime(const WebCore::ServiceWorkerRegistrationIdentifier& identifier, const WallTime& lastUpdateTime)
        : m_arguments(identifier, lastUpdateTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, const WallTime&> m_arguments;
};

class SetRegistrationUpdateViaCache {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerRegistrationIdentifier, WebCore::ServiceWorkerUpdateViaCache>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_SetRegistrationUpdateViaCache; }
    static constexpr bool isSync = false;

    SetRegistrationUpdateViaCache(const WebCore::ServiceWorkerRegistrationIdentifier& identifier, WebCore::ServiceWorkerUpdateViaCache updateViaCache)
        : m_arguments(identifier, updateViaCache)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerRegistrationIdentifier&, WebCore::ServiceWorkerUpdateViaCache> m_arguments;
};

class NotifyClientsOfControllerChange {
public:
    using Arguments = std::tuple<HashSet<WebCore::ScriptExecutionContextIdentifier>, std::optional<WebCore::ServiceWorkerData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_NotifyClientsOfControllerChange; }
    static constexpr bool isSync = false;

    NotifyClientsOfControllerChange(const HashSet<WebCore::ScriptExecutionContextIdentifier>& contextIdentifiers, const std::optional<WebCore::ServiceWorkerData>& newController)
        : m_arguments(contextIdentifiers, newController)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const HashSet<WebCore::ScriptExecutionContextIdentifier>&, const std::optional<WebCore::ServiceWorkerData>&> m_arguments;
};

class UpdateBackgroundFetchRegistration {
public:
    using Arguments = std::tuple<WebCore::BackgroundFetchInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_UpdateBackgroundFetchRegistration; }
    static constexpr bool isSync = false;

    explicit UpdateBackgroundFetchRegistration(const WebCore::BackgroundFetchInformation& information)
        : m_arguments(information)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackgroundFetchInformation&> m_arguments;
};

class SetSWOriginTableIsImported {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_SetSWOriginTableIsImported; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetSWOriginTableSharedMemory {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_SetSWOriginTableSharedMemory; }
    static constexpr bool isSync = false;

    explicit SetSWOriginTableSharedMemory(WebKit::SharedMemory::Handle&& handle)
        : m_arguments(WTFMove(handle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedMemory::Handle&&> m_arguments;
};

class PostMessageToServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, WebCore::MessageWithMessagePorts, WebCore::ServiceWorkerData, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_PostMessageToServiceWorkerClient; }
    static constexpr bool isSync = false;

    PostMessageToServiceWorkerClient(const WebCore::ScriptExecutionContextIdentifier& destinationContextIdentifier, const WebCore::MessageWithMessagePorts& message, const WebCore::ServiceWorkerData& source, const String& sourceOrigin)
        : m_arguments(destinationContextIdentifier, message, source, sourceOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const WebCore::MessageWithMessagePorts&, const WebCore::ServiceWorkerData&, const String&> m_arguments;
};

class SetServiceWorkerClientIsControlled {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, WebCore::ServiceWorkerRegistrationData>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_SetServiceWorkerClientIsControlled; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWClientConnection_SetServiceWorkerClientIsControlledReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    SetServiceWorkerClientIsControlled(const WebCore::ScriptExecutionContextIdentifier& workerIdentifier, const WebCore::ServiceWorkerRegistrationData& data)
        : m_arguments(workerIdentifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const WebCore::ServiceWorkerRegistrationData&> m_arguments;
};

class FocusServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_FocusServiceWorkerClient; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWClientConnection_FocusServiceWorkerClientReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ServiceWorkerClientData>>;
    explicit FocusServiceWorkerClient(const WebCore::ScriptExecutionContextIdentifier& clientIdentifier)
        : m_arguments(clientIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

class NotifyRecordResponseBodyChunk {
public:
    using Arguments = std::tuple<WebKit::RetrieveRecordResponseBodyCallbackIdentifier, IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_NotifyRecordResponseBodyChunk; }
    static constexpr bool isSync = false;

    NotifyRecordResponseBodyChunk(const WebKit::RetrieveRecordResponseBodyCallbackIdentifier& identifier, const IPC::SharedBufferReference& data)
        : m_arguments(identifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RetrieveRecordResponseBodyCallbackIdentifier&, const IPC::SharedBufferReference&> m_arguments;
};

class NotifyRecordResponseBodyEnd {
public:
    using Arguments = std::tuple<WebKit::RetrieveRecordResponseBodyCallbackIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWClientConnection_NotifyRecordResponseBodyEnd; }
    static constexpr bool isSync = false;

    NotifyRecordResponseBodyEnd(const WebKit::RetrieveRecordResponseBodyCallbackIdentifier& identifier, const WebCore::ResourceError& error)
        : m_arguments(identifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RetrieveRecordResponseBodyCallbackIdentifier&, const WebCore::ResourceError&> m_arguments;
};

} // namespace WebSWClientConnection
} // namespace Messages

#endif // ENABLE(SERVICE_WORKER)
