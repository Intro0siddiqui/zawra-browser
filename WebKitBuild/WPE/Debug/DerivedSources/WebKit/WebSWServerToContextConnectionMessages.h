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
#include <WebCore/ExceptionData.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/ServiceWorkerClientData.h>
#include <WebCore/ServiceWorkerIdentifier.h>
#include <WebCore/ServiceWorkerJobDataIdentifier.h>
#include <optional>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace JSC {
enum class MessageLevel : uint8_t;
enum class MessageSource : uint8_t;
}

namespace WebCore {
struct MessageWithMessagePorts;
struct ServiceWorkerClientQueryOptions;
struct ServiceWorkerImportedScript;
}

namespace Messages {
namespace WebSWServerToContextConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSWServerToContextConnection;
}

class ScriptContextFailedToStart {
public:
    using Arguments = std::tuple<std::optional<WebCore::ServiceWorkerJobDataIdentifier>, WebCore::ServiceWorkerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_ScriptContextFailedToStart; }
    static constexpr bool isSync = false;

    ScriptContextFailedToStart(const std::optional<WebCore::ServiceWorkerJobDataIdentifier>& jobDataIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const String& message)
        : m_arguments(jobDataIdentifier, serviceWorkerIdentifier, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ServiceWorkerJobDataIdentifier>&, const WebCore::ServiceWorkerIdentifier&, const String&> m_arguments;
};

class ScriptContextStarted {
public:
    using Arguments = std::tuple<std::optional<WebCore::ServiceWorkerJobDataIdentifier>, WebCore::ServiceWorkerIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_ScriptContextStarted; }
    static constexpr bool isSync = false;

    ScriptContextStarted(const std::optional<WebCore::ServiceWorkerJobDataIdentifier>& jobDataIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, bool doesHandleFetch)
        : m_arguments(jobDataIdentifier, serviceWorkerIdentifier, doesHandleFetch)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ServiceWorkerJobDataIdentifier>&, const WebCore::ServiceWorkerIdentifier&, bool> m_arguments;
};

class DidFinishInstall {
public:
    using Arguments = std::tuple<std::optional<WebCore::ServiceWorkerJobDataIdentifier>, WebCore::ServiceWorkerIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_DidFinishInstall; }
    static constexpr bool isSync = false;

    DidFinishInstall(const std::optional<WebCore::ServiceWorkerJobDataIdentifier>& jobDataIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, bool wasSuccessful)
        : m_arguments(jobDataIdentifier, serviceWorkerIdentifier, wasSuccessful)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ServiceWorkerJobDataIdentifier>&, const WebCore::ServiceWorkerIdentifier&, bool> m_arguments;
};

class DidFinishActivation {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_DidFinishActivation; }
    static constexpr bool isSync = false;

    explicit DidFinishActivation(const WebCore::ServiceWorkerIdentifier& identifier)
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

class SetServiceWorkerHasPendingEvents {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_SetServiceWorkerHasPendingEvents; }
    static constexpr bool isSync = false;

    SetServiceWorkerHasPendingEvents(const WebCore::ServiceWorkerIdentifier& identifier, bool hasPendingEvents)
        : m_arguments(identifier, hasPendingEvents)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, bool> m_arguments;
};

class SkipWaiting {
public:
    using Arguments = std::tuple<uint64_t, WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_SkipWaiting; }
    static constexpr bool isSync = false;

    SkipWaiting(uint64_t matchAllRequestIdentifier, const WebCore::ServiceWorkerIdentifier& identifier)
        : m_arguments(matchAllRequestIdentifier, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class WorkerTerminated {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_WorkerTerminated; }
    static constexpr bool isSync = false;

    explicit WorkerTerminated(const WebCore::ServiceWorkerIdentifier& identifier)
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

class FindClientByVisibleIdentifier {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_FindClientByVisibleIdentifier; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerToContextConnection_FindClientByVisibleIdentifierReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ServiceWorkerClientData>>;
    FindClientByVisibleIdentifier(const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const String& clientIdentifier)
        : m_arguments(serviceWorkerIdentifier, clientIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const String&> m_arguments;
};

class MatchAll {
public:
    using Arguments = std::tuple<uint64_t, WebCore::ServiceWorkerIdentifier, WebCore::ServiceWorkerClientQueryOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_MatchAll; }
    static constexpr bool isSync = false;

    MatchAll(uint64_t matchAllRequestIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const WebCore::ServiceWorkerClientQueryOptions& options)
        : m_arguments(matchAllRequestIdentifier, serviceWorkerIdentifier, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::ServiceWorkerIdentifier&, const WebCore::ServiceWorkerClientQueryOptions&> m_arguments;
};

class Claim {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_Claim; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerToContextConnection_ClaimReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ExceptionData>>;
    explicit Claim(const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier)
        : m_arguments(serviceWorkerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&> m_arguments;
};

class Focus {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_Focus; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerToContextConnection_FocusReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ServiceWorkerClientData>>;
    explicit Focus(const WebCore::ScriptExecutionContextIdentifier& serviceWorkerClientIdentifier)
        : m_arguments(serviceWorkerClientIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

class Navigate {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, WebCore::ServiceWorkerIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_Navigate; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerToContextConnection_NavigateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<std::optional<WebCore::ServiceWorkerClientData>, WebCore::ExceptionData>>;
    Navigate(const WebCore::ScriptExecutionContextIdentifier& clientIdentifier, const WebCore::ServiceWorkerIdentifier& serviceWorkerIdentifier, const URL& url)
        : m_arguments(clientIdentifier, serviceWorkerIdentifier, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const WebCore::ServiceWorkerIdentifier&, const URL&> m_arguments;
};

class SetScriptResource {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, URL, WebCore::ServiceWorkerImportedScript>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_SetScriptResource; }
    static constexpr bool isSync = false;

    SetScriptResource(const WebCore::ServiceWorkerIdentifier& identifier, const URL& scriptURL, const WebCore::ServiceWorkerImportedScript& script)
        : m_arguments(identifier, scriptURL, script)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const URL&, const WebCore::ServiceWorkerImportedScript&> m_arguments;
};

class PostMessageToServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, WebCore::MessageWithMessagePorts, WebCore::ServiceWorkerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_PostMessageToServiceWorkerClient; }
    static constexpr bool isSync = false;

    PostMessageToServiceWorkerClient(const WebCore::ScriptExecutionContextIdentifier& destination, const WebCore::MessageWithMessagePorts& message, const WebCore::ServiceWorkerIdentifier& source, const String& sourceOrigin)
        : m_arguments(destination, message, source, sourceOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const WebCore::MessageWithMessagePorts&, const WebCore::ServiceWorkerIdentifier&, const String&> m_arguments;
};

class DidFailHeartBeatCheck {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_DidFailHeartBeatCheck; }
    static constexpr bool isSync = false;

    explicit DidFailHeartBeatCheck(const WebCore::ServiceWorkerIdentifier& identifier)
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

class SetAsInspected {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_SetAsInspected; }
    static constexpr bool isSync = false;

    SetAsInspected(const WebCore::ServiceWorkerIdentifier& identifier, bool isInspected)
        : m_arguments(identifier, isInspected)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, bool> m_arguments;
};

class OpenWindow {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_OpenWindow; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSWServerToContextConnection_OpenWindowReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<std::optional<WebCore::ServiceWorkerClientData>, WebCore::ExceptionData>>;
    OpenWindow(const WebCore::ServiceWorkerIdentifier& identifier, const URL& url)
        : m_arguments(identifier, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, const URL&> m_arguments;
};

class ReportConsoleMessage {
public:
    using Arguments = std::tuple<WebCore::ServiceWorkerIdentifier, JSC::MessageSource, JSC::MessageLevel, String, unsigned long>;

    static IPC::MessageName name() { return IPC::MessageName::WebSWServerToContextConnection_ReportConsoleMessage; }
    static constexpr bool isSync = false;

    ReportConsoleMessage(const WebCore::ServiceWorkerIdentifier& identifier, JSC::MessageSource messageSource, JSC::MessageLevel messageLevel, const String& message, const unsigned long& requestIdentifier)
        : m_arguments(identifier, messageSource, messageLevel, message, requestIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ServiceWorkerIdentifier&, JSC::MessageSource, JSC::MessageLevel, const String&, const unsigned long&> m_arguments;
};

} // namespace WebSWServerToContextConnection
} // namespace Messages

#endif // ENABLE(SERVICE_WORKER)
