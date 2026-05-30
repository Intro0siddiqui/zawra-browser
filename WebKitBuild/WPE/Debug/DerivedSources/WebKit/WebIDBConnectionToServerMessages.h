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
#include <WebCore/IDBDatabaseNameAndVersion.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {
class IDBError;
class IDBResourceIdentifier;
class IDBResultData;
}

namespace WebKit {
class WebIDBResult;
}

namespace Messages {
namespace WebIDBConnectionToServer {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebIDBConnectionToServer;
}

class DidDeleteDatabase {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidDeleteDatabase; }
    static constexpr bool isSync = false;

    explicit DidDeleteDatabase(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidOpenDatabase {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidOpenDatabase; }
    static constexpr bool isSync = false;

    explicit DidOpenDatabase(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidAbortTransaction {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, WebCore::IDBError>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidAbortTransaction; }
    static constexpr bool isSync = false;

    DidAbortTransaction(const WebCore::IDBResourceIdentifier& transactionIdentifier, const WebCore::IDBError& error)
        : m_arguments(transactionIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, const WebCore::IDBError&> m_arguments;
};

class DidCommitTransaction {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, WebCore::IDBError>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidCommitTransaction; }
    static constexpr bool isSync = false;

    DidCommitTransaction(const WebCore::IDBResourceIdentifier& transactionIdentifier, const WebCore::IDBError& error)
        : m_arguments(transactionIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, const WebCore::IDBError&> m_arguments;
};

class DidCreateObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidCreateObjectStore; }
    static constexpr bool isSync = false;

    explicit DidCreateObjectStore(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidDeleteObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidDeleteObjectStore; }
    static constexpr bool isSync = false;

    explicit DidDeleteObjectStore(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidRenameObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidRenameObjectStore; }
    static constexpr bool isSync = false;

    explicit DidRenameObjectStore(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidClearObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidClearObjectStore; }
    static constexpr bool isSync = false;

    explicit DidClearObjectStore(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidCreateIndex {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidCreateIndex; }
    static constexpr bool isSync = false;

    explicit DidCreateIndex(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidDeleteIndex {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidDeleteIndex; }
    static constexpr bool isSync = false;

    explicit DidDeleteIndex(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidRenameIndex {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidRenameIndex; }
    static constexpr bool isSync = false;

    explicit DidRenameIndex(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidPutOrAdd {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidPutOrAdd; }
    static constexpr bool isSync = false;

    explicit DidPutOrAdd(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidGetRecord {
public:
    using Arguments = std::tuple<WebKit::WebIDBResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidGetRecord; }
    static constexpr bool isSync = false;

    explicit DidGetRecord(const WebKit::WebIDBResult& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebIDBResult&> m_arguments;
};

class DidGetAllRecords {
public:
    using Arguments = std::tuple<WebKit::WebIDBResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidGetAllRecords; }
    static constexpr bool isSync = false;

    explicit DidGetAllRecords(const WebKit::WebIDBResult& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebIDBResult&> m_arguments;
};

class DidGetCount {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidGetCount; }
    static constexpr bool isSync = false;

    explicit DidGetCount(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidDeleteRecord {
public:
    using Arguments = std::tuple<WebCore::IDBResultData>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidDeleteRecord; }
    static constexpr bool isSync = false;

    explicit DidDeleteRecord(const WebCore::IDBResultData& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResultData&> m_arguments;
};

class DidOpenCursor {
public:
    using Arguments = std::tuple<WebKit::WebIDBResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidOpenCursor; }
    static constexpr bool isSync = false;

    explicit DidOpenCursor(const WebKit::WebIDBResult& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebIDBResult&> m_arguments;
};

class DidIterateCursor {
public:
    using Arguments = std::tuple<WebKit::WebIDBResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidIterateCursor; }
    static constexpr bool isSync = false;

    explicit DidIterateCursor(const WebKit::WebIDBResult& result)
        : m_arguments(result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebIDBResult&> m_arguments;
};

class FireVersionChangeEvent {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IDBResourceIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_FireVersionChangeEvent; }
    static constexpr bool isSync = false;

    FireVersionChangeEvent(uint64_t databaseConnectionIdentifier, const WebCore::IDBResourceIdentifier& requestIdentifier, uint64_t requestedVersion)
        : m_arguments(databaseConnectionIdentifier, requestIdentifier, requestedVersion)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IDBResourceIdentifier&, uint64_t> m_arguments;
};

class DidStartTransaction {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, WebCore::IDBError>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidStartTransaction; }
    static constexpr bool isSync = false;

    DidStartTransaction(const WebCore::IDBResourceIdentifier& transactionIdentifier, const WebCore::IDBError& error)
        : m_arguments(transactionIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, const WebCore::IDBError&> m_arguments;
};

class DidCloseFromServer {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IDBError>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidCloseFromServer; }
    static constexpr bool isSync = false;

    DidCloseFromServer(uint64_t databaseConnectionIdentifier, const WebCore::IDBError& error)
        : m_arguments(databaseConnectionIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IDBError&> m_arguments;
};

class NotifyOpenDBRequestBlocked {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_NotifyOpenDBRequestBlocked; }
    static constexpr bool isSync = false;

    NotifyOpenDBRequestBlocked(const WebCore::IDBResourceIdentifier& requestIdentifier, uint64_t oldVersion, uint64_t newVersion)
        : m_arguments(requestIdentifier, oldVersion, newVersion)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, uint64_t, uint64_t> m_arguments;
};

class DidGetAllDatabaseNamesAndVersions {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, Vector<WebCore::IDBDatabaseNameAndVersion>>;

    static IPC::MessageName name() { return IPC::MessageName::WebIDBConnectionToServer_DidGetAllDatabaseNamesAndVersions; }
    static constexpr bool isSync = false;

    DidGetAllDatabaseNamesAndVersions(const WebCore::IDBResourceIdentifier& requestIdentifier, const Vector<WebCore::IDBDatabaseNameAndVersion>& databases)
        : m_arguments(requestIdentifier, databases)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, const Vector<WebCore::IDBDatabaseNameAndVersion>&> m_arguments;
};

} // namespace WebIDBConnectionToServer
} // namespace Messages
