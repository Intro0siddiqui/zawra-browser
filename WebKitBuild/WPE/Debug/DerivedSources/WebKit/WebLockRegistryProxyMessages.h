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
#include <WebCore/ProcessQualified.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/WebLockIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
enum class WebLockMode : bool;
struct ClientOrigin;
struct WebLockManagerSnapshot;
}

namespace Messages {
namespace WebLockRegistryProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebLockRegistryProxy;
}

class RequestLock {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::WebLockIdentifier, WebCore::ScriptExecutionContextIdentifier, String, WebCore::WebLockMode, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebLockRegistryProxy_RequestLock; }
    static constexpr bool isSync = false;

    RequestLock(const WebCore::ClientOrigin& clientOrigin, const WebCore::WebLockIdentifier& identifier, const WebCore::ScriptExecutionContextIdentifier& clientID, const String& name, WebCore::WebLockMode mode, bool steal, bool ifAvailable)
        : m_arguments(clientOrigin, identifier, clientID, name, mode, steal, ifAvailable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::WebLockIdentifier&, const WebCore::ScriptExecutionContextIdentifier&, const String&, WebCore::WebLockMode, bool, bool> m_arguments;
};

class ReleaseLock {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::WebLockIdentifier, WebCore::ScriptExecutionContextIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebLockRegistryProxy_ReleaseLock; }
    static constexpr bool isSync = false;

    ReleaseLock(const WebCore::ClientOrigin& clientOrigin, const WebCore::WebLockIdentifier& identifier, const WebCore::ScriptExecutionContextIdentifier& clientID, const String& name)
        : m_arguments(clientOrigin, identifier, clientID, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::WebLockIdentifier&, const WebCore::ScriptExecutionContextIdentifier&, const String&> m_arguments;
};

class AbortLockRequest {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::WebLockIdentifier, WebCore::ScriptExecutionContextIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebLockRegistryProxy_AbortLockRequest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebLockRegistryProxy_AbortLockRequestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    AbortLockRequest(const WebCore::ClientOrigin& clientOrigin, const WebCore::WebLockIdentifier& identifier, const WebCore::ScriptExecutionContextIdentifier& clientID, const String& name)
        : m_arguments(clientOrigin, identifier, clientID, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::WebLockIdentifier&, const WebCore::ScriptExecutionContextIdentifier&, const String&> m_arguments;
};

class Snapshot {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::WebLockRegistryProxy_Snapshot; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebLockRegistryProxy_SnapshotReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::WebLockManagerSnapshot>;
    explicit Snapshot(const WebCore::ClientOrigin& clientOrigin)
        : m_arguments(clientOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&> m_arguments;
};

class ClientIsGoingAway {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebLockRegistryProxy_ClientIsGoingAway; }
    static constexpr bool isSync = false;

    ClientIsGoingAway(const WebCore::ClientOrigin& clientOrigin, const WebCore::ScriptExecutionContextIdentifier& clientId)
        : m_arguments(clientOrigin, clientId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

} // namespace WebLockRegistryProxy
} // namespace Messages
