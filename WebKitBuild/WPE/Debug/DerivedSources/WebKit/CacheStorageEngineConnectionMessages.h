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
#include <WebCore/DOMCacheEngine.h>
#include <WebCore/DOMCacheIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class ResourceRequest;
struct CacheQueryOptions;
struct ClientOrigin;
struct RetrieveRecordsOptions;
}

namespace Messages {
namespace CacheStorageEngineConnection {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::CacheStorageEngineConnection;
}

class Reference {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_Reference; }
    static constexpr bool isSync = false;

    explicit Reference(const WebCore::DOMCacheIdentifier& cacheIdentifier)
        : m_arguments(cacheIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&> m_arguments;
};

class Dereference {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_Dereference; }
    static constexpr bool isSync = false;

    explicit Dereference(const WebCore::DOMCacheIdentifier& cacheIdentifier)
        : m_arguments(cacheIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&> m_arguments;
};

class Open {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, String>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_Open; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_OpenReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::CacheIdentifierOrError>;
    Open(const WebCore::ClientOrigin& origin, const String& cacheName)
        : m_arguments(origin, cacheName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const String&> m_arguments;
};

class Remove {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_Remove; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_RemoveReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RemoveCacheIdentifierOrError>;
    explicit Remove(const WebCore::DOMCacheIdentifier& cacheIdentifier)
        : m_arguments(cacheIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&> m_arguments;
};

class Caches {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_Caches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_CachesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::CacheInfosOrError>;
    Caches(const WebCore::ClientOrigin& origin, uint64_t updateCounter)
        : m_arguments(origin, updateCounter)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, uint64_t> m_arguments;
};

class RetrieveRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, WebCore::RetrieveRecordsOptions>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_RetrieveRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_RetrieveRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RecordsOrError>;
    RetrieveRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const WebCore::RetrieveRecordsOptions& options)
        : m_arguments(cacheIdentifier, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&, const WebCore::RetrieveRecordsOptions&> m_arguments;
};

class DeleteMatchingRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, WebCore::ResourceRequest, WebCore::CacheQueryOptions>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_DeleteMatchingRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_DeleteMatchingRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RecordIdentifiersOrError>;
    DeleteMatchingRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const WebCore::ResourceRequest& request, const WebCore::CacheQueryOptions& options)
        : m_arguments(cacheIdentifier, request, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&, const WebCore::ResourceRequest&, const WebCore::CacheQueryOptions&> m_arguments;
};

class PutRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, Vector<WebCore::DOMCacheEngine::Record>>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_PutRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_PutRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RecordIdentifiersOrError>;
    PutRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const Vector<WebCore::DOMCacheEngine::Record>& record)
        : m_arguments(cacheIdentifier, record)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&, const Vector<WebCore::DOMCacheEngine::Record>&> m_arguments;
};

class ClearMemoryRepresentation {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_ClearMemoryRepresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_ClearMemoryRepresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::DOMCacheEngine::Error>>;
    explicit ClearMemoryRepresentation(const WebCore::ClientOrigin& origin)
        : m_arguments(origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&> m_arguments;
};

class EngineRepresentation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::CacheStorageEngineConnection_EngineRepresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::CacheStorageEngineConnection_EngineRepresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace CacheStorageEngineConnection
} // namespace Messages
