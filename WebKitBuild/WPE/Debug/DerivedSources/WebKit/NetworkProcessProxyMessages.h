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
#include "DataTaskIdentifier.h"
#include "FormDataReference.h"
#include "IdentifierTypes.h"
#include "MessageNames.h"
#include "NetworkResourceLoadIdentifier.h"
#include "QuotaIncreaseRequestIdentifier.h"
#include "UserContentControllerIdentifier.h"
#include "WebPageProxyIdentifier.h"
#include "WebsiteDataFetchOption.h"
#include "WebsiteDataType.h"
#include <WebCore/FrameIdentifier.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/ProcessIdentifier.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/RegistrableDomain.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/SecurityOriginData.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/HashSet.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/OptionSet.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace JSC {
enum class MessageLevel : uint8_t;
enum class MessageSource : uint8_t;
}

namespace PAL {
class SessionID;
}

namespace WebCore {
class AuthenticationChallenge;
class Credential;
class RegistrableDomain;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
class SecurityOriginData;
enum class ShouldSample : bool;
enum class BrowsingContextGroupSwitchDecision : uint8_t;
struct ClientOrigin;
}

namespace WebKit {
enum class AuthenticationChallengeDisposition : uint8_t;
enum class BackgroundFetchChange : uint8_t;
enum class RemoteWorkerType : uint8_t;
struct ResourceLoadInfo;
}

namespace Messages {
namespace NetworkProcessProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkProcessProxy;
}

class DidReceiveAuthenticationChallenge {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::WebPageProxyIdentifier, std::optional<WebCore::SecurityOriginData>, WebCore::AuthenticationChallenge, bool, WebKit::AuthenticationChallengeIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DidReceiveAuthenticationChallenge; }
    static constexpr bool isSync = false;

    DidReceiveAuthenticationChallenge(const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& pageID, const std::optional<WebCore::SecurityOriginData>& topOrigin, const WebCore::AuthenticationChallenge& challenge, bool negotiatedLegacyTLS, const WebKit::AuthenticationChallengeIdentifier& challengeID)
        : m_arguments(sessionID, pageID, topOrigin, challenge, negotiatedLegacyTLS, challengeID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&, const std::optional<WebCore::SecurityOriginData>&, const WebCore::AuthenticationChallenge&, bool, const WebKit::AuthenticationChallengeIdentifier&> m_arguments;
};

class NegotiatedLegacyTLS {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NegotiatedLegacyTLS; }
    static constexpr bool isSync = false;

    explicit NegotiatedLegacyTLS(const WebKit::WebPageProxyIdentifier& pageID)
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

class DidNegotiateModernTLS {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DidNegotiateModernTLS; }
    static constexpr bool isSync = false;

    DidNegotiateModernTLS(const WebKit::WebPageProxyIdentifier& pageID, const URL& url)
        : m_arguments(pageID, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const URL&> m_arguments;
};

class DidBlockLoadToKnownTracker {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DidBlockLoadToKnownTracker; }
    static constexpr bool isSync = false;

    DidBlockLoadToKnownTracker(const WebKit::WebPageProxyIdentifier& pageID, const URL& url)
        : m_arguments(pageID, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const URL&> m_arguments;
};

class TestProcessIncomingSyncMessagesWhenWaitingForSyncReply {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply; }
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

class TerminateUnresponsiveServiceWorkerProcesses {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_TerminateUnresponsiveServiceWorkerProcesses; }
    static constexpr bool isSync = false;

    explicit TerminateUnresponsiveServiceWorkerProcesses(const WebCore::ProcessIdentifier& processIdentifier)
        : m_arguments(processIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};

class LogDiagnosticMessage {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, String, String, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_LogDiagnosticMessage; }
    static constexpr bool isSync = false;

    LogDiagnosticMessage(const WebKit::WebPageProxyIdentifier& pageID, const String& message, const String& description, WebCore::ShouldSample shouldSample)
        : m_arguments(pageID, message, description, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const String&, const String&, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithResult {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, String, String, uint32_t, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_LogDiagnosticMessageWithResult; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithResult(const WebKit::WebPageProxyIdentifier& pageID, const String& message, const String& description, uint32_t result, WebCore::ShouldSample shouldSample)
        : m_arguments(pageID, message, description, result, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const String&, const String&, uint32_t, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithValue {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, String, String, double, unsigned, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_LogDiagnosticMessageWithValue; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithValue(const WebKit::WebPageProxyIdentifier& pageID, const String& message, const String& description, double value, const unsigned& significantFigures, WebCore::ShouldSample shouldSample)
        : m_arguments(pageID, message, description, value, significantFigures, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const String&, const String&, double, const unsigned&, WebCore::ShouldSample> m_arguments;
};

#if ENABLE(TRACKING_PREVENTION)
class LogTestingEvent {
public:
    using Arguments = std::tuple<PAL::SessionID, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_LogTestingEvent; }
    static constexpr bool isSync = false;

    LogTestingEvent(const PAL::SessionID& sessionID, const String& event)
        : m_arguments(sessionID, event)
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

#if ENABLE(TRACKING_PREVENTION)
class NotifyResourceLoadStatisticsProcessed {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NotifyResourceLoadStatisticsProcessed; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class NotifyWebsiteDataDeletionForRegistrableDomainsFinished {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NotifyWebsiteDataDeletionForRegistrableDomainsFinished; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class NotifyWebsiteDataScanForRegistrableDomainsFinished {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NotifyWebsiteDataScanForRegistrableDomainsFinished; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class RequestStorageAccessConfirm {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::FrameIdentifier, WebCore::RegistrableDomain, WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_RequestStorageAccessConfirm; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_RequestStorageAccessConfirmReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    RequestStorageAccessConfirm(const WebKit::WebPageProxyIdentifier& pageID, const WebCore::FrameIdentifier& frameID, const WebCore::RegistrableDomain& subFrameDomain, const WebCore::RegistrableDomain& topFrameDomain)
        : m_arguments(pageID, frameID, subFrameDomain, topFrameDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::FrameIdentifier&, const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class DeleteWebsiteDataInUIProcessForRegistrableDomains {
public:
    using Arguments = std::tuple<PAL::SessionID, OptionSet<WebKit::WebsiteDataType>, OptionSet<WebKit::WebsiteDataFetchOption>, Vector<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomains; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomainsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<HashSet<WebCore::RegistrableDomain>>;
    DeleteWebsiteDataInUIProcessForRegistrableDomains(const PAL::SessionID& sessionID, const OptionSet<WebKit::WebsiteDataType>& dataTypes, const OptionSet<WebKit::WebsiteDataFetchOption>& fetchOptions, const Vector<WebCore::RegistrableDomain>& domains)
        : m_arguments(sessionID, dataTypes, fetchOptions, domains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const OptionSet<WebKit::WebsiteDataType>&, const OptionSet<WebKit::WebsiteDataFetchOption>&, const Vector<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource; }
    static constexpr bool isSync = false;

    explicit DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource(const WebKit::WebPageProxyIdentifier& pageID)
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
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetDomainsWithUserInteraction {
public:
    using Arguments = std::tuple<HashSet<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_SetDomainsWithUserInteraction; }
    static constexpr bool isSync = false;

    explicit SetDomainsWithUserInteraction(const HashSet<WebCore::RegistrableDomain>& domains)
        : m_arguments(domains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const HashSet<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetDomainsWithCrossPageStorageAccess {
public:
    using Arguments = std::tuple<HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_SetDomainsWithCrossPageStorageAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_SetDomainsWithCrossPageStorageAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetDomainsWithCrossPageStorageAccess(const HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>& domains)
        : m_arguments(domains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(CONTENT_EXTENSIONS)
class ContentExtensionRules {
public:
    using Arguments = std::tuple<WebKit::UserContentControllerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ContentExtensionRules; }
    static constexpr bool isSync = false;

    explicit ContentExtensionRules(const WebKit::UserContentControllerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserContentControllerIdentifier&> m_arguments;
};
#endif

class TerminateWebProcess {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_TerminateWebProcess; }
    static constexpr bool isSync = false;

    explicit TerminateWebProcess(const WebCore::ProcessIdentifier& webProcessIdentifier)
        : m_arguments(webProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};

#if ENABLE(SERVICE_WORKER)
class StartServiceWorkerBackgroundProcessing {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_StartServiceWorkerBackgroundProcessing; }
    static constexpr bool isSync = false;

    explicit StartServiceWorkerBackgroundProcessing(const WebCore::ProcessIdentifier& serviceWorkerProcessIdentifier)
        : m_arguments(serviceWorkerProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class EndServiceWorkerBackgroundProcessing {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_EndServiceWorkerBackgroundProcessing; }
    static constexpr bool isSync = false;

    explicit EndServiceWorkerBackgroundProcessing(const WebCore::ProcessIdentifier& serviceWorkerProcessIdentifier)
        : m_arguments(serviceWorkerProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class RequestBackgroundFetchPermission {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_RequestBackgroundFetchPermission; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_RequestBackgroundFetchPermissionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    RequestBackgroundFetchPermission(const PAL::SessionID& sessionID, const WebCore::ClientOrigin& origin)
        : m_arguments(sessionID, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::ClientOrigin&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class NotifyBackgroundFetchChange {
public:
    using Arguments = std::tuple<PAL::SessionID, String, WebKit::BackgroundFetchChange>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NotifyBackgroundFetchChange; }
    static constexpr bool isSync = false;

    NotifyBackgroundFetchChange(const PAL::SessionID& sessionID, const String& backgroundFetchIdentifier, WebKit::BackgroundFetchChange change)
        : m_arguments(sessionID, backgroundFetchIdentifier, change)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&, WebKit::BackgroundFetchChange> m_arguments;
};
#endif

class EstablishRemoteWorkerContextConnectionToNetworkProcess {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, WebCore::RegistrableDomain, std::optional<WebCore::ProcessIdentifier>, std::optional<WebCore::ScriptExecutionContextIdentifier>, PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ProcessIdentifier>;
    EstablishRemoteWorkerContextConnectionToNetworkProcess(WebKit::RemoteWorkerType workerType, const WebCore::RegistrableDomain& registrableDomain, const std::optional<WebCore::ProcessIdentifier>& requestingProcessIdentifier, const std::optional<WebCore::ScriptExecutionContextIdentifier>& serviceWorkerPageIdentifier, const PAL::SessionID& sessionID)
        : m_arguments(workerType, registrableDomain, requestingProcessIdentifier, serviceWorkerPageIdentifier, sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const WebCore::RegistrableDomain&, const std::optional<WebCore::ProcessIdentifier>&, const std::optional<WebCore::ScriptExecutionContextIdentifier>&, const PAL::SessionID&> m_arguments;
};

class RemoteWorkerContextConnectionNoLongerNeeded {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_RemoteWorkerContextConnectionNoLongerNeeded; }
    static constexpr bool isSync = false;

    RemoteWorkerContextConnectionNoLongerNeeded(WebKit::RemoteWorkerType workerType, const WebCore::ProcessIdentifier& identifier)
        : m_arguments(workerType, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const WebCore::ProcessIdentifier&> m_arguments;
};

class RegisterRemoteWorkerClientProcess {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, WebCore::ProcessIdentifier, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_RegisterRemoteWorkerClientProcess; }
    static constexpr bool isSync = false;

    RegisterRemoteWorkerClientProcess(WebKit::RemoteWorkerType workerType, const WebCore::ProcessIdentifier& clientProcessIdentifier, const WebCore::ProcessIdentifier& remoteWorkerProcessIdentifier)
        : m_arguments(workerType, clientProcessIdentifier, remoteWorkerProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const WebCore::ProcessIdentifier&, const WebCore::ProcessIdentifier&> m_arguments;
};

class UnregisterRemoteWorkerClientProcess {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, WebCore::ProcessIdentifier, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_UnregisterRemoteWorkerClientProcess; }
    static constexpr bool isSync = false;

    UnregisterRemoteWorkerClientProcess(WebKit::RemoteWorkerType workerType, const WebCore::ProcessIdentifier& clientProcessIdentifier, const WebCore::ProcessIdentifier& remoteWorkerProcessIdentifier)
        : m_arguments(workerType, clientProcessIdentifier, remoteWorkerProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const WebCore::ProcessIdentifier&, const WebCore::ProcessIdentifier&> m_arguments;
};

class SetWebProcessHasUploads {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_SetWebProcessHasUploads; }
    static constexpr bool isSync = false;

    SetWebProcessHasUploads(const WebCore::ProcessIdentifier& processID, bool hasUpload)
        : m_arguments(processID, hasUpload)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, bool> m_arguments;
};

#if ENABLE(APP_BOUND_DOMAINS)
class GetAppBoundDomains {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_GetAppBoundDomains; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_GetAppBoundDomainsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<HashSet<WebCore::RegistrableDomain>>;
    explicit GetAppBoundDomains(const PAL::SessionID& sessionID)
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

class RequestStorageSpace {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ClientOrigin, uint64_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_RequestStorageSpace; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_RequestStorageSpaceReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<uint64_t>>;
    RequestStorageSpace(const PAL::SessionID& sessionID, const WebCore::ClientOrigin& origin, uint64_t quota, uint64_t currentSize, uint64_t spaceRequired)
        : m_arguments(sessionID, origin, quota, currentSize, spaceRequired)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::ClientOrigin&, uint64_t, uint64_t, uint64_t> m_arguments;
};

class IncreaseQuota {
public:
    using Arguments = std::tuple<PAL::SessionID, WebCore::ClientOrigin, WebKit::QuotaIncreaseRequestIdentifier, uint64_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_IncreaseQuota; }
    static constexpr bool isSync = false;

    IncreaseQuota(const PAL::SessionID& sessionID, const WebCore::ClientOrigin& origin, const WebKit::QuotaIncreaseRequestIdentifier& identifier, uint64_t quota, uint64_t currentSize, uint64_t spaceRequested)
        : m_arguments(sessionID, origin, identifier, quota, currentSize, spaceRequested)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebCore::ClientOrigin&, const WebKit::QuotaIncreaseRequestIdentifier&, uint64_t, uint64_t, uint64_t> m_arguments;
};

class ResourceLoadDidSendRequest {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebKit::ResourceLoadInfo, WebCore::ResourceRequest, std::optional<IPC::FormDataReference>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ResourceLoadDidSendRequest; }
    static constexpr bool isSync = false;

    ResourceLoadDidSendRequest(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebKit::ResourceLoadInfo& resourceLoadInfo, const WebCore::ResourceRequest& request, const std::optional<IPC::FormDataReference>& httpBody)
        : m_arguments(pageIdentifier, resourceLoadInfo, request, httpBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebKit::ResourceLoadInfo&, const WebCore::ResourceRequest&, const std::optional<IPC::FormDataReference>&> m_arguments;
};

class ResourceLoadDidPerformHTTPRedirection {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebKit::ResourceLoadInfo, WebCore::ResourceResponse, WebCore::ResourceRequest>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ResourceLoadDidPerformHTTPRedirection; }
    static constexpr bool isSync = false;

    ResourceLoadDidPerformHTTPRedirection(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebKit::ResourceLoadInfo& resourceLoadInfo, const WebCore::ResourceResponse& resourceResponse, const WebCore::ResourceRequest& request)
        : m_arguments(pageIdentifier, resourceLoadInfo, resourceResponse, request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebKit::ResourceLoadInfo&, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&> m_arguments;
};

class ResourceLoadDidReceiveChallenge {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebKit::ResourceLoadInfo, WebCore::AuthenticationChallenge>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ResourceLoadDidReceiveChallenge; }
    static constexpr bool isSync = false;

    ResourceLoadDidReceiveChallenge(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebKit::ResourceLoadInfo& resourceLoadInfo, const WebCore::AuthenticationChallenge& challenge)
        : m_arguments(pageIdentifier, resourceLoadInfo, challenge)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebKit::ResourceLoadInfo&, const WebCore::AuthenticationChallenge&> m_arguments;
};

class ResourceLoadDidReceiveResponse {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebKit::ResourceLoadInfo, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ResourceLoadDidReceiveResponse; }
    static constexpr bool isSync = false;

    ResourceLoadDidReceiveResponse(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebKit::ResourceLoadInfo& resourceLoadInfo, const WebCore::ResourceResponse& response)
        : m_arguments(pageIdentifier, resourceLoadInfo, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebKit::ResourceLoadInfo&, const WebCore::ResourceResponse&> m_arguments;
};

class ResourceLoadDidCompleteWithError {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebKit::ResourceLoadInfo, WebCore::ResourceResponse, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ResourceLoadDidCompleteWithError; }
    static constexpr bool isSync = false;

    ResourceLoadDidCompleteWithError(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebKit::ResourceLoadInfo& resourceLoadInfo, const WebCore::ResourceResponse& response, const WebCore::ResourceError& error)
        : m_arguments(pageIdentifier, resourceLoadInfo, response, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebKit::ResourceLoadInfo&, const WebCore::ResourceResponse&, const WebCore::ResourceError&> m_arguments;
};

class TriggerBrowsingContextGroupSwitchForNavigation {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, uint64_t, WebCore::BrowsingContextGroupSwitchDecision, WebCore::RegistrableDomain, WebKit::NetworkResourceLoadIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    TriggerBrowsingContextGroupSwitchForNavigation(const WebKit::WebPageProxyIdentifier& pageIdentifier, uint64_t navigationID, WebCore::BrowsingContextGroupSwitchDecision browsingContextGroupSwitchDecision, const WebCore::RegistrableDomain& responseDomain, const WebKit::NetworkResourceLoadIdentifier& existingNetworkResourceLoadIdentifierToResume)
        : m_arguments(pageIdentifier, navigationID, browsingContextGroupSwitchDecision, responseDomain, existingNetworkResourceLoadIdentifierToResume)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, uint64_t, WebCore::BrowsingContextGroupSwitchDecision, const WebCore::RegistrableDomain&, const WebKit::NetworkResourceLoadIdentifier&> m_arguments;
};

#if USE(SOUP)
class DidExceedMemoryLimit {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DidExceedMemoryLimit; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
class GetWindowSceneIdentifierForPaymentPresentation {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetWindowSceneIdentifierForPaymentPresentation(const WebKit::WebPageProxyIdentifier& webPageProxyIdentifier)
        : m_arguments(webPageProxyIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&> m_arguments;
};
#endif

class DataTaskReceivedChallenge {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, WebCore::AuthenticationChallenge>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DataTaskReceivedChallenge; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_DataTaskReceivedChallengeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::AuthenticationChallengeDisposition, WebCore::Credential>;
    DataTaskReceivedChallenge(const WebKit::DataTaskIdentifier& identifier, const WebCore::AuthenticationChallenge& challenge)
        : m_arguments(identifier, challenge)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const WebCore::AuthenticationChallenge&> m_arguments;
};

class DataTaskWillPerformHTTPRedirection {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, WebCore::ResourceResponse, WebCore::ResourceRequest>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DataTaskWillPerformHTTPRedirection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_DataTaskWillPerformHTTPRedirectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    DataTaskWillPerformHTTPRedirection(const WebKit::DataTaskIdentifier& identifier, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest& request)
        : m_arguments(identifier, response, request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&> m_arguments;
};

class DataTaskDidReceiveResponse {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DataTaskDidReceiveResponse; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_DataTaskDidReceiveResponseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    DataTaskDidReceiveResponse(const WebKit::DataTaskIdentifier& identifier, const WebCore::ResourceResponse& response)
        : m_arguments(identifier, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const WebCore::ResourceResponse&> m_arguments;
};

class DataTaskDidReceiveData {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DataTaskDidReceiveData; }
    static constexpr bool isSync = false;

    DataTaskDidReceiveData(const WebKit::DataTaskIdentifier& identifier, const IPC::DataReference& data)
        : m_arguments(identifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const IPC::DataReference&> m_arguments;
};

class DataTaskDidCompleteWithError {
public:
    using Arguments = std::tuple<WebKit::DataTaskIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DataTaskDidCompleteWithError; }
    static constexpr bool isSync = false;

    DataTaskDidCompleteWithError(const WebKit::DataTaskIdentifier& identifier, const WebCore::ResourceError& error)
        : m_arguments(identifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataTaskIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class OpenWindowFromServiceWorker {
public:
    using Arguments = std::tuple<PAL::SessionID, String, WebCore::SecurityOriginData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_OpenWindowFromServiceWorker; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_OpenWindowFromServiceWorkerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::PageIdentifier>>;
    OpenWindowFromServiceWorker(const PAL::SessionID& sessionID, const String& urlString, const WebCore::SecurityOriginData& serviceWorkerOrigin)
        : m_arguments(sessionID, urlString, serviceWorkerOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const String&, const WebCore::SecurityOriginData&> m_arguments;
};

class NavigateServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::ScriptExecutionContextIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_NavigateServiceWorkerClient; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_NavigateServiceWorkerClientReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::PageIdentifier>, std::optional<WebCore::FrameIdentifier>>;
    NavigateServiceWorkerClient(const WebCore::FrameIdentifier& frameIdentifier, const WebCore::ScriptExecutionContextIdentifier& documentIdentifier, const URL& url)
        : m_arguments(frameIdentifier, documentIdentifier, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::ScriptExecutionContextIdentifier&, const URL&> m_arguments;
};

class ReportConsoleMessage {
public:
    using Arguments = std::tuple<PAL::SessionID, URL, WebCore::SecurityOriginData, JSC::MessageSource, JSC::MessageLevel, String, unsigned long>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ReportConsoleMessage; }
    static constexpr bool isSync = false;

    ReportConsoleMessage(const PAL::SessionID& sessionID, const URL& scriptURL, const WebCore::SecurityOriginData& serviceWorkerOrigin, JSC::MessageSource messageSource, JSC::MessageLevel messageLevel, const String& message, const unsigned long& requestIdentifier)
        : m_arguments(sessionID, scriptURL, serviceWorkerOrigin, messageSource, messageLevel, message, requestIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const URL&, const WebCore::SecurityOriginData&, JSC::MessageSource, JSC::MessageLevel, const String&, const unsigned long&> m_arguments;
};

class CookiesDidChange {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_CookiesDidChange; }
    static constexpr bool isSync = false;

    explicit CookiesDidChange(const PAL::SessionID& sessionID)
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

class DeleteWebsiteDataInWebProcessesForOrigin {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebsiteDataType>, WebCore::ClientOrigin, PAL::SessionID, WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOrigin; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOriginReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteDataInWebProcessesForOrigin(const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const WebCore::ClientOrigin& origin, const PAL::SessionID& sessionID, const WebKit::WebPageProxyIdentifier& webPageProxyID)
        : m_arguments(websiteDataTypes, origin, sessionID, webPageProxyID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebsiteDataType>&, const WebCore::ClientOrigin&, const PAL::SessionID&, const WebKit::WebPageProxyIdentifier&> m_arguments;
};

class ReloadExecutionContextsForOrigin {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, PAL::SessionID, std::optional<WebCore::FrameIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ReloadExecutionContextsForOrigin; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkProcessProxy_ReloadExecutionContextsForOriginReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ReloadExecutionContextsForOrigin(const WebCore::ClientOrigin& origin, const PAL::SessionID& sessionID, const std::optional<WebCore::FrameIdentifier>& triggeringFrame)
        : m_arguments(origin, sessionID, triggeringFrame)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const PAL::SessionID&, const std::optional<WebCore::FrameIdentifier>&> m_arguments;
};

#if USE(RUNNINGBOARD)
class WakeUpWebProcessForIPC {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_WakeUpWebProcessForIPC; }
    static constexpr bool isSync = false;

    explicit WakeUpWebProcessForIPC(const WebCore::ProcessIdentifier& processIdentifier)
        : m_arguments(processIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};
#endif

#if ENABLE(NETWORK_ISSUE_REPORTING)
class ReportNetworkIssue {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkProcessProxy_ReportNetworkIssue; }
    static constexpr bool isSync = false;

    ReportNetworkIssue(const WebKit::WebPageProxyIdentifier& webPageProxyIdentifier, const URL& requestURL)
        : m_arguments(webPageProxyIdentifier, requestURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const URL&> m_arguments;
};
#endif

} // namespace NetworkProcessProxy
} // namespace Messages
