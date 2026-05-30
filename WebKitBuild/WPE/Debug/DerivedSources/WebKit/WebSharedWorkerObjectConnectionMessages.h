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
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class ResourceError;
struct WorkerFetchResult;
struct WorkerInitializationData;
struct WorkerOptions;
}

namespace Messages {
namespace WebSharedWorkerObjectConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebSharedWorkerObjectConnection;
}

class FetchScriptInClient {
public:
    using Arguments = std::tuple<URL, WebCore::SharedWorkerObjectIdentifier, WebCore::WorkerOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerObjectConnection_FetchScriptInClient; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebSharedWorkerObjectConnection_FetchScriptInClientReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::WorkerFetchResult, WebCore::WorkerInitializationData>;
    FetchScriptInClient(const URL& url, const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier, const WebCore::WorkerOptions& workerOptions)
        : m_arguments(url, sharedWorkerObjectIdentifier, workerOptions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SharedWorkerObjectIdentifier&, const WebCore::WorkerOptions&> m_arguments;
};

class NotifyWorkerObjectOfLoadCompletion {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerObjectIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerObjectConnection_NotifyWorkerObjectOfLoadCompletion; }
    static constexpr bool isSync = false;

    NotifyWorkerObjectOfLoadCompletion(const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier, const WebCore::ResourceError& error)
        : m_arguments(sharedWorkerObjectIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerObjectIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class PostExceptionToWorkerObject {
public:
    using Arguments = std::tuple<WebCore::SharedWorkerObjectIdentifier, String, int, int, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebSharedWorkerObjectConnection_PostExceptionToWorkerObject; }
    static constexpr bool isSync = false;

    PostExceptionToWorkerObject(const WebCore::SharedWorkerObjectIdentifier& sharedWorkerObjectIdentifier, const String& errorMessage, const int& lineNumber, const int& columnNumber, const String& sourceURL)
        : m_arguments(sharedWorkerObjectIdentifier, errorMessage, lineNumber, columnNumber, sourceURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SharedWorkerObjectIdentifier&, const String&, const int&, const int&, const String&> m_arguments;
};

} // namespace WebSharedWorkerObjectConnection
} // namespace Messages
