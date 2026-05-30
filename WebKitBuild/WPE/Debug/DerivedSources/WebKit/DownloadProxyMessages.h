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
#include "IdentifierTypes.h"
#include "MessageNames.h"
#include "SandboxExtension.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class AuthenticationChallenge;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
}

namespace WebKit {
enum class AllowOverwrite : bool;
}

namespace Messages {
namespace DownloadProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::DownloadProxy;
}

class DidStart {
public:
    using Arguments = std::tuple<WebCore::ResourceRequest, String>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidStart; }
    static constexpr bool isSync = false;

    DidStart(const WebCore::ResourceRequest& request, const String& suggestedFilename)
        : m_arguments(request, suggestedFilename)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceRequest&, const String&> m_arguments;
};

class DidReceiveAuthenticationChallenge {
public:
    using Arguments = std::tuple<WebCore::AuthenticationChallenge, WebKit::AuthenticationChallengeIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidReceiveAuthenticationChallenge; }
    static constexpr bool isSync = false;

    DidReceiveAuthenticationChallenge(const WebCore::AuthenticationChallenge& challenge, const WebKit::AuthenticationChallengeIdentifier& challengeID)
        : m_arguments(challenge, challengeID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::AuthenticationChallenge&, const WebKit::AuthenticationChallengeIdentifier&> m_arguments;
};

class WillSendRequest {
public:
    using Arguments = std::tuple<WebCore::ResourceRequest, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_WillSendRequest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::DownloadProxy_WillSendRequestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceRequest>;
    WillSendRequest(const WebCore::ResourceRequest& redirectRequest, const WebCore::ResourceResponse& redirectResponse)
        : m_arguments(redirectRequest, redirectResponse)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> m_arguments;
};

class DecideDestinationWithSuggestedFilename {
public:
    using Arguments = std::tuple<WebCore::ResourceResponse, String>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DecideDestinationWithSuggestedFilename; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::DownloadProxy_DecideDestinationWithSuggestedFilenameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, WebKit::SandboxExtension::Handle, WebKit::AllowOverwrite>;
    DecideDestinationWithSuggestedFilename(const WebCore::ResourceResponse& response, const String& suggestedFilename)
        : m_arguments(response, suggestedFilename)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceResponse&, const String&> m_arguments;
};

class DidReceiveData {
public:
    using Arguments = std::tuple<uint64_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidReceiveData; }
    static constexpr bool isSync = false;

    DidReceiveData(uint64_t bytesWritten, uint64_t totalBytesWritten, uint64_t totalBytesExpectedToWrite)
        : m_arguments(bytesWritten, totalBytesWritten, totalBytesExpectedToWrite)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, uint64_t, uint64_t> m_arguments;
};

class DidCreateDestination {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidCreateDestination; }
    static constexpr bool isSync = false;

    explicit DidCreateDestination(const String& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class DidFinish {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidFinish; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidFail {
public:
    using Arguments = std::tuple<WebCore::ResourceError, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::DownloadProxy_DidFail; }
    static constexpr bool isSync = false;

    DidFail(const WebCore::ResourceError& error, const IPC::DataReference& resumeData)
        : m_arguments(error, resumeData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceError&, const IPC::DataReference&> m_arguments;
};

} // namespace DownloadProxy
} // namespace Messages
