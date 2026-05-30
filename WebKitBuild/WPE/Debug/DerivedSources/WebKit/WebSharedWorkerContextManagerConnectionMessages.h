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
#include <WebCore/SharedWorkerIdentifier.h>
#include <WebCore/TransferredMessagePort.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct ClientOrigin;
struct WorkerFetchResult;
struct WorkerInitializationData;
struct WorkerOptions;
}

namespace WebKit {
struct WebPreferencesStore;
}

namespace Messages {
namespace WebSharedWorkerContextManagerConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSharedWorkerContextManagerConnection;
}

class LaunchSharedWorker {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::SharedWorkerIdentifier, WebCore::WorkerOptions, WebCore::WorkerFetchResult, WebCore::WorkerInitializationData>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_LaunchSharedWorker; }
    static constexpr bool isSync = false;

    LaunchSharedWorker(const WebCore::ClientOrigin& origin, const WebCore::SharedWorkerIdentifier& sharedWorkerIdentifier, const WebCore::WorkerOptions& workerOptions, const WebCore::WorkerFetchResult& workerFetchResult, const WebCore::WorkerInitializationData& workerInitializationData)
        : m_arguments(origin, sharedWorkerIdentifier, workerOptions, workerFetchResult, workerInitializationData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::SharedWorkerIdentifier&, const WebCore::WorkerOptions&, const WebCore::WorkerFetchResult&, const WebCore::WorkerInitializationData&> m_arguments;
};

class PostConnectEvent {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerIdentifier, WebCore::TransferredMessagePort, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_PostConnectEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_PostConnectEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    PostConnectEvent(const WebCore::SharedWorkerIdentifier& sharedWorkerIdentifier, const WebCore::TransferredMessagePort& port, const String& sourceOrigin)
        : m_arguments(sharedWorkerIdentifier, port, sourceOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerIdentifier&, const WebCore::TransferredMessagePort&, const String&> m_arguments;
};

class TerminateSharedWorker {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_TerminateSharedWorker; }
    static constexpr bool isSync = false;

    explicit TerminateSharedWorker(const WebCore::SharedWorkerIdentifier& sharedWorkerIdentifier)
        : m_arguments(sharedWorkerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerIdentifier&> m_arguments;
};

class UpdatePreferencesStore {
public:
    using Arguments = std::tuple<WebKit::WebPreferencesStore>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_UpdatePreferencesStore; }
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

class SetUserAgent {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_SetUserAgent; }
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

class Close {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_Close; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SuspendSharedWorker {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_SuspendSharedWorker; }
    static constexpr bool isSync = false;

    explicit SuspendSharedWorker(const WebCore::SharedWorkerIdentifier& sharedWorkerIdentifier)
        : m_arguments(sharedWorkerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerIdentifier&> m_arguments;
};

class ResumeSharedWorker {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerContextManagerConnection_ResumeSharedWorker; }
    static constexpr bool isSync = false;

    explicit ResumeSharedWorker(const WebCore::SharedWorkerIdentifier& sharedWorkerIdentifier)
        : m_arguments(sharedWorkerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerIdentifier&> m_arguments;
};

} // namespace WebSharedWorkerContextManagerConnection
} // namespace Messages
