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

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "RemoteMediaResourceIdentifier.h"
#include "SharedMemory.h"
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace IPC {
class SharedBufferReference;
}

namespace WebCore {
class NetworkLoadMetrics;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
enum class ShouldContinuePolicyCheck : bool;
}

namespace Messages {
namespace RemoteMediaResourceManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaResourceManager;
}

class ResponseReceived {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::ResourceResponse, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_ResponseReceived; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaResourceManager_ResponseReceivedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ShouldContinuePolicyCheck>;
    ResponseReceived(const WebKit::RemoteMediaResourceIdentifier& identifier, const WebCore::ResourceResponse& response, bool didPassAccessControlCheck)
        : m_arguments(identifier, response, didPassAccessControlCheck)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::ResourceResponse&, bool> m_arguments;
};

class RedirectReceived {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::ResourceRequest, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_RedirectReceived; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaResourceManager_RedirectReceivedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceRequest>;
    RedirectReceived(const WebKit::RemoteMediaResourceIdentifier& identifier, const WebCore::ResourceRequest& request, const WebCore::ResourceResponse& response)
        : m_arguments(identifier, request, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> m_arguments;
};

class DataSent {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_DataSent; }
    static constexpr bool isSync = false;

    DataSent(const WebKit::RemoteMediaResourceIdentifier& identifier, uint64_t bytesSent, uint64_t totalBytesToBeSent)
        : m_arguments(identifier, bytesSent, totalBytesToBeSent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, uint64_t, uint64_t> m_arguments;
};

class DataReceived {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_DataReceived; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaResourceManager_DataReceivedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::SharedMemory::Handle>>;
    DataReceived(const WebKit::RemoteMediaResourceIdentifier& identifier, const IPC::SharedBufferReference& data)
        : m_arguments(identifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const IPC::SharedBufferReference&> m_arguments;
};

class AccessControlCheckFailed {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_AccessControlCheckFailed; }
    static constexpr bool isSync = false;

    AccessControlCheckFailed(const WebKit::RemoteMediaResourceIdentifier& identifier, const WebCore::ResourceError& error)
        : m_arguments(identifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class LoadFailed {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_LoadFailed; }
    static constexpr bool isSync = false;

    LoadFailed(const WebKit::RemoteMediaResourceIdentifier& identifier, const WebCore::ResourceError& error)
        : m_arguments(identifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class LoadFinished {
public:
    using Arguments = std::tuple<WebKit::RemoteMediaResourceIdentifier, WebCore::NetworkLoadMetrics>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaResourceManager_LoadFinished; }
    static constexpr bool isSync = false;

    LoadFinished(const WebKit::RemoteMediaResourceIdentifier& identifier, const WebCore::NetworkLoadMetrics& metrics)
        : m_arguments(identifier, metrics)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteMediaResourceIdentifier&, const WebCore::NetworkLoadMetrics&> m_arguments;
};

} // namespace RemoteMediaResourceManager
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
