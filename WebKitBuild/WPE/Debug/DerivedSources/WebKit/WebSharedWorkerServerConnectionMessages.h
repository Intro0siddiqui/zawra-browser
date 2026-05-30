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
#include <WebCore/SharedWorkerObjectIdentifier.h>
#include <WebCore/TransferredMessagePort.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
struct SharedWorkerKey;
struct WorkerOptions;
}

namespace Messages {
namespace WebSharedWorkerServerConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSharedWorkerServerConnection;
}

class RequestSharedWorker {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerKey, WebCore::SharedWorkerObjectIdentifier, WebCore::TransferredMessagePort, WebCore::WorkerOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerServerConnection_RequestSharedWorker; }
    static constexpr bool isSync = false;

    RequestSharedWorker(const WebCore::SharedWorkerKey& sharedWorkerKey, const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier, const WebCore::TransferredMessagePort& port, const WebCore::WorkerOptions& workerOptions)
        : m_arguments(sharedWorkerKey, sharedWorkerObjectIdentifier, port, workerOptions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerKey&, const WebCore::SharedWorkerObjectIdentifier&, const WebCore::TransferredMessagePort&, const WebCore::WorkerOptions&> m_arguments;
};

class SharedWorkerObjectIsGoingAway {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerKey, WebCore::SharedWorkerObjectIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerServerConnection_SharedWorkerObjectIsGoingAway; }
    static constexpr bool isSync = false;

    SharedWorkerObjectIsGoingAway(const WebCore::SharedWorkerKey& sharedWorkerKey, const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier)
        : m_arguments(sharedWorkerKey, sharedWorkerObjectIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerKey&, const WebCore::SharedWorkerObjectIdentifier&> m_arguments;
};

class SuspendForBackForwardCache {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerKey, WebCore::SharedWorkerObjectIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerServerConnection_SuspendForBackForwardCache; }
    static constexpr bool isSync = false;

    SuspendForBackForwardCache(const WebCore::SharedWorkerKey& sharedWorkerKey, const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier)
        : m_arguments(sharedWorkerKey, sharedWorkerObjectIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerKey&, const WebCore::SharedWorkerObjectIdentifier&> m_arguments;
};

class ResumeForBackForwardCache {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerKey, WebCore::SharedWorkerObjectIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerServerConnection_ResumeForBackForwardCache; }
    static constexpr bool isSync = false;

    ResumeForBackForwardCache(const WebCore::SharedWorkerKey& sharedWorkerKey, const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier)
        : m_arguments(sharedWorkerKey, sharedWorkerObjectIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerKey&, const WebCore::SharedWorkerObjectIdentifier&> m_arguments;
};

} // namespace WebSharedWorkerServerConnection
} // namespace Messages
