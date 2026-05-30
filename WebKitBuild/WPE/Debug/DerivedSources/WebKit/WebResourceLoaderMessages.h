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
#include "ShareableResource.h"
#include <WebCore/NetworkLoadMetrics.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class FormDataReference;
class SharedBufferReference;
}

namespace WebCore {
class ContentFilterUnblockHandler;
class NetworkLoadMetrics;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
class SubstituteData;
}

namespace WebKit {
enum class PrivateRelayed : bool;
}

namespace Messages {
namespace WebResourceLoader {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebResourceLoader;
}

class WillSendRequest {
public:
    using Arguments = std::tuple<WebCore::ResourceRequest, IPC::FormDataReference, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_WillSendRequest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebResourceLoader_WillSendRequestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceRequest, bool>;
    WillSendRequest(const WebCore::ResourceRequest& request, const IPC::FormDataReference& requestBody, const WebCore::ResourceResponse& redirectResponse)
        : m_arguments(request, requestBody, redirectResponse)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceRequest&, const IPC::FormDataReference&, const WebCore::ResourceResponse&> m_arguments;
};

class SetWorkerStart {
public:
    using Arguments = std::tuple<MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_SetWorkerStart; }
    static constexpr bool isSync = false;

    explicit SetWorkerStart(const MonotonicTime& value)
        : m_arguments(value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MonotonicTime&> m_arguments;
};

class DidSendData {
public:
    using Arguments = std::tuple<uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidSendData; }
    static constexpr bool isSync = false;

    DidSendData(uint64_t bytesSent, uint64_t totalBytesToBeSent)
        : m_arguments(bytesSent, totalBytesToBeSent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint64_t> m_arguments;
};

class DidReceiveResponse {
public:
    using Arguments = std::tuple<WebCore::ResourceResponse, WebKit::PrivateRelayed, bool, std::optional<WebCore::NetworkLoadMetrics>>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidReceiveResponse; }
    static constexpr bool isSync = false;

    DidReceiveResponse(const WebCore::ResourceResponse& response, WebKit::PrivateRelayed privateRelayed, bool needsContinueDidReceiveResponseMessage, const std::optional<WebCore::NetworkLoadMetrics>& optionalNetworkLoadMetrics)
        : m_arguments(response, privateRelayed, needsContinueDidReceiveResponseMessage, optionalNetworkLoadMetrics)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceResponse&, WebKit::PrivateRelayed, bool, const std::optional<WebCore::NetworkLoadMetrics>&> m_arguments;
};

class DidReceiveData {
public:
    using Arguments = std::tuple<IPC::SharedBufferReference, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidReceiveData; }
    static constexpr bool isSync = false;

    DidReceiveData(const IPC::SharedBufferReference& data, uint64_t encodedDataLength)
        : m_arguments(data, encodedDataLength)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::SharedBufferReference&, uint64_t> m_arguments;
};

class DidFinishResourceLoad {
public:
    using Arguments = std::tuple<WebCore::NetworkLoadMetrics>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidFinishResourceLoad; }
    static constexpr bool isSync = false;

    explicit DidFinishResourceLoad(const WebCore::NetworkLoadMetrics& networkLoadMetrics)
        : m_arguments(networkLoadMetrics)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::NetworkLoadMetrics&> m_arguments;
};

class DidFailResourceLoad {
public:
    using Arguments = std::tuple<WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidFailResourceLoad; }
    static constexpr bool isSync = false;

    explicit DidFailResourceLoad(const WebCore::ResourceError& error)
        : m_arguments(error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceError&> m_arguments;
};

class DidFailServiceWorkerLoad {
public:
    using Arguments = std::tuple<WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidFailServiceWorkerLoad; }
    static constexpr bool isSync = false;

    explicit DidFailServiceWorkerLoad(const WebCore::ResourceError& error)
        : m_arguments(error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceError&> m_arguments;
};

class ServiceWorkerDidNotHandle {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_ServiceWorkerDidNotHandle; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidBlockAuthenticationChallenge {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidBlockAuthenticationChallenge; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied {
public:
    using Arguments = std::tuple<WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied; }
    static constexpr bool isSync = false;

    explicit StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied(const WebCore::ResourceResponse& response)
        : m_arguments(response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceResponse&> m_arguments;
};

#if ENABLE(SHAREABLE_RESOURCE)
class DidReceiveResource {
public:
    using Arguments = std::tuple<WebKit::ShareableResource::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_DidReceiveResource; }
    static constexpr bool isSync = false;

    explicit DidReceiveResource(WebKit::ShareableResource::Handle&& resource)
        : m_arguments(WTFMove(resource))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::ShareableResource::Handle&&> m_arguments;
};
#endif

#if ENABLE(CONTENT_FILTERING)
class ContentFilterDidBlockLoad {
public:
    using Arguments = std::tuple<WebCore::ContentFilterUnblockHandler, String, WebCore::ResourceError, URL, WebCore::SubstituteData>;

    static IPC::MessageName name() { return IPC::MessageName::WebResourceLoader_ContentFilterDidBlockLoad; }
    static constexpr bool isSync = false;

    ContentFilterDidBlockLoad(const WebCore::ContentFilterUnblockHandler& unblockHandler, const String& unblockRequestDeniedScript, const WebCore::ResourceError& error, const URL& blockedPageURL, const WebCore::SubstituteData& substituteData)
        : m_arguments(unblockHandler, unblockRequestDeniedScript, error, blockedPageURL, substituteData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ContentFilterUnblockHandler&, const String&, const WebCore::ResourceError&, const URL&, const WebCore::SubstituteData&> m_arguments;
};
#endif

} // namespace WebResourceLoader
} // namespace Messages
