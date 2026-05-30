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
#include "FileSystemStorageError.h"
#include "FileSystemSyncAccessHandleInfo.h"
#include "MessageNames.h"
#include "StorageAreaIdentifier.h"
#include "StorageAreaImplIdentifier.h"
#include "StorageAreaMapIdentifier.h"
#include "StorageNamespaceIdentifier.h"
#include <WebCore/DOMCacheEngine.h>
#include <WebCore/DOMCacheIdentifier.h>
#include <WebCore/FileSystemHandleIdentifier.h>
#include <WebCore/FileSystemSyncAccessHandleIdentifier.h>
#include <WebCore/IDBResourceIdentifier.h>
#include <WebCore/IndexedDB.h>
#include <WebCore/StorageEstimate.h>
#include <WebCore/StorageType.h>
#include <optional>
#include <utility>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class IDBCursorInfo;
class IDBIndexInfo;
class IDBKeyData;
class IDBObjectStoreInfo;
class IDBRequestData;
class IDBResourceIdentifier;
class IDBTransactionInfo;
class IDBValue;
class ResourceRequest;
struct CacheQueryOptions;
struct ClientOrigin;
struct IDBGetAllRecordsData;
struct IDBGetRecordData;
struct IDBIterateCursorData;
struct IDBKeyRangeData;
struct RetrieveRecordsOptions;
}

namespace Messages {
namespace NetworkStorageManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkStorageManager;
}

class Persisted {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Persisted; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_PersistedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit Persisted(const WebCore::ClientOrigin& origin)
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

class Persist {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Persist; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_PersistReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit Persist(const WebCore::ClientOrigin& origin)
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

class Estimate {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Estimate; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_EstimateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::StorageEstimate>>;
    explicit Estimate(const WebCore::ClientOrigin& origin)
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

class FileSystemGetDirectory {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_FileSystemGetDirectory; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_FileSystemGetDirectoryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::FileSystemHandleIdentifier, WebKit::FileSystemStorageError>>;
    explicit FileSystemGetDirectory(const WebCore::ClientOrigin& origin)
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

class CloseHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CloseHandle; }
    static constexpr bool isSync = false;

    explicit CloseHandle(const WebCore::FileSystemHandleIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class IsSameEntry {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_IsSameEntry; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_IsSameEntryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    IsSameEntry(const WebCore::FileSystemHandleIdentifier& identifier, const WebCore::FileSystemHandleIdentifier& targetIdentifier)
        : m_arguments(identifier, targetIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class GetFileHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetFileHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_GetFileHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::FileSystemHandleIdentifier, WebKit::FileSystemStorageError>>;
    GetFileHandle(const WebCore::FileSystemHandleIdentifier& identifier, const String& name, bool createIfNecessary)
        : m_arguments(identifier, name, createIfNecessary)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const String&, bool> m_arguments;
};

class GetDirectoryHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetDirectoryHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_GetDirectoryHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::FileSystemHandleIdentifier, WebKit::FileSystemStorageError>>;
    GetDirectoryHandle(const WebCore::FileSystemHandleIdentifier& identifier, const String& name, bool createIfNecessary)
        : m_arguments(identifier, name, createIfNecessary)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const String&, bool> m_arguments;
};

class RemoveEntry {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_RemoveEntry; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_RemoveEntryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::FileSystemStorageError>>;
    RemoveEntry(const WebCore::FileSystemHandleIdentifier& identifier, const String& name, bool deleteRecursively)
        : m_arguments(identifier, name, deleteRecursively)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const String&, bool> m_arguments;
};

class Resolve {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Resolve; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_ResolveReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Vector<String>, WebKit::FileSystemStorageError>>;
    Resolve(const WebCore::FileSystemHandleIdentifier& identifier, const WebCore::FileSystemHandleIdentifier& targetIdentifier)
        : m_arguments(identifier, targetIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class Move {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, WebCore::FileSystemHandleIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Move; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_MoveReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::FileSystemStorageError>>;
    Move(const WebCore::FileSystemHandleIdentifier& identifier, const WebCore::FileSystemHandleIdentifier& destinationIdentifier, const String& newName)
        : m_arguments(identifier, destinationIdentifier, newName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const WebCore::FileSystemHandleIdentifier&, const String&> m_arguments;
};

class GetFile {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetFile; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_GetFileReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<String, WebKit::FileSystemStorageError>>;
    explicit GetFile(const WebCore::FileSystemHandleIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class CreateSyncAccessHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CreateSyncAccessHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CreateSyncAccessHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebKit::FileSystemSyncAccessHandleInfo, WebKit::FileSystemStorageError>>;
    explicit CreateSyncAccessHandle(const WebCore::FileSystemHandleIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class CloseSyncAccessHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, WebCore::FileSystemSyncAccessHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CloseSyncAccessHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CloseSyncAccessHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    CloseSyncAccessHandle(const WebCore::FileSystemHandleIdentifier& identifier, const WebCore::FileSystemSyncAccessHandleIdentifier& accessHandleIdentifier)
        : m_arguments(identifier, accessHandleIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const WebCore::FileSystemSyncAccessHandleIdentifier&> m_arguments;
};

class RequestNewCapacityForSyncAccessHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, WebCore::FileSystemSyncAccessHandleIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_RequestNewCapacityForSyncAccessHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_RequestNewCapacityForSyncAccessHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<uint64_t>>;
    RequestNewCapacityForSyncAccessHandle(const WebCore::FileSystemHandleIdentifier& identifier, const WebCore::FileSystemSyncAccessHandleIdentifier& accessHandleIdentifier, uint64_t newCapacity)
        : m_arguments(identifier, accessHandleIdentifier, newCapacity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const WebCore::FileSystemSyncAccessHandleIdentifier&, uint64_t> m_arguments;
};

class GetHandleNames {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetHandleNames; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_GetHandleNamesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Vector<String>, WebKit::FileSystemStorageError>>;
    explicit GetHandleNames(const WebCore::FileSystemHandleIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&> m_arguments;
};

class GetHandle {
public:
    using Arguments = std::tuple<WebCore::FileSystemHandleIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_GetHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<std::pair<WebCore::FileSystemHandleIdentifier, bool>, WebKit::FileSystemStorageError>>;
    GetHandle(const WebCore::FileSystemHandleIdentifier& identifier, const String& name)
        : m_arguments(identifier, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FileSystemHandleIdentifier&, const String&> m_arguments;
};

class ConnectToStorageArea {
public:
    using Arguments = std::tuple<WebCore::StorageType, WebKit::StorageAreaMapIdentifier, std::optional<WebKit::StorageNamespaceIdentifier>, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_ConnectToStorageArea; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_ConnectToStorageAreaReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::StorageAreaIdentifier, HashMap<String, String>, uint64_t>;
    ConnectToStorageArea(const WebCore::StorageType& type, const WebKit::StorageAreaMapIdentifier& sourceIdentifier, const std::optional<WebKit::StorageNamespaceIdentifier>& namespaceIdentifier, const WebCore::ClientOrigin& origin)
        : m_arguments(type, sourceIdentifier, namespaceIdentifier, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::StorageType&, const WebKit::StorageAreaMapIdentifier&, const std::optional<WebKit::StorageNamespaceIdentifier>&, const WebCore::ClientOrigin&> m_arguments;
};

class ConnectToStorageAreaSync {
public:
    using Arguments = std::tuple<WebCore::StorageType, WebKit::StorageAreaMapIdentifier, std::optional<WebKit::StorageNamespaceIdentifier>, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_ConnectToStorageAreaSync; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::StorageAreaIdentifier, HashMap<String, String>, uint64_t>;
    ConnectToStorageAreaSync(const WebCore::StorageType& type, const WebKit::StorageAreaMapIdentifier& sourceIdentifier, const std::optional<WebKit::StorageNamespaceIdentifier>& namespaceIdentifier, const WebCore::ClientOrigin& origin)
        : m_arguments(type, sourceIdentifier, namespaceIdentifier, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::StorageType&, const WebKit::StorageAreaMapIdentifier&, const std::optional<WebKit::StorageNamespaceIdentifier>&, const WebCore::ClientOrigin&> m_arguments;
};

class CancelConnectToStorageArea {
public:
    using Arguments = std::tuple<WebCore::StorageType, std::optional<WebKit::StorageNamespaceIdentifier>, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CancelConnectToStorageArea; }
    static constexpr bool isSync = false;

    CancelConnectToStorageArea(const WebCore::StorageType& type, const std::optional<WebKit::StorageNamespaceIdentifier>& namespaceIdentifier, const WebCore::ClientOrigin& origin)
        : m_arguments(type, namespaceIdentifier, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::StorageType&, const std::optional<WebKit::StorageNamespaceIdentifier>&, const WebCore::ClientOrigin&> m_arguments;
};

class DisconnectFromStorageArea {
public:
    using Arguments = std::tuple<WebKit::StorageAreaIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DisconnectFromStorageArea; }
    static constexpr bool isSync = false;

    explicit DisconnectFromStorageArea(const WebKit::StorageAreaIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::StorageAreaIdentifier&> m_arguments;
};

class CloneSessionStorageNamespace {
public:
    using Arguments = std::tuple<WebKit::StorageNamespaceIdentifier, WebKit::StorageNamespaceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CloneSessionStorageNamespace; }
    static constexpr bool isSync = false;

    CloneSessionStorageNamespace(const WebKit::StorageNamespaceIdentifier& fromStorageNamespaceID, const WebKit::StorageNamespaceIdentifier& toStorageNamespaceID)
        : m_arguments(fromStorageNamespaceID, toStorageNamespaceID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::StorageNamespaceIdentifier&, const WebKit::StorageNamespaceIdentifier&> m_arguments;
};

class SetItem {
public:
    using Arguments = std::tuple<WebKit::StorageAreaIdentifier, WebKit::StorageAreaImplIdentifier, String, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_SetItem; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_SetItemReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, HashMap<String, String>>;
    SetItem(const WebKit::StorageAreaIdentifier& identifier, const WebKit::StorageAreaImplIdentifier& implIdentifier, const String& key, const String& value, const String& urlString)
        : m_arguments(identifier, implIdentifier, key, value, urlString)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::StorageAreaIdentifier&, const WebKit::StorageAreaImplIdentifier&, const String&, const String&, const String&> m_arguments;
};

class RemoveItem {
public:
    using Arguments = std::tuple<WebKit::StorageAreaIdentifier, WebKit::StorageAreaImplIdentifier, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_RemoveItem; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_RemoveItemReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, HashMap<String, String>>;
    RemoveItem(const WebKit::StorageAreaIdentifier& identifier, const WebKit::StorageAreaImplIdentifier& implIdentifier, const String& key, const String& urlString)
        : m_arguments(identifier, implIdentifier, key, urlString)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::StorageAreaIdentifier&, const WebKit::StorageAreaImplIdentifier&, const String&, const String&> m_arguments;
};

class Clear {
public:
    using Arguments = std::tuple<WebKit::StorageAreaIdentifier, WebKit::StorageAreaImplIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_Clear; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_ClearReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    Clear(const WebKit::StorageAreaIdentifier& identifier, const WebKit::StorageAreaImplIdentifier& implIdentifier, const String& urlString)
        : m_arguments(identifier, implIdentifier, urlString)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::StorageAreaIdentifier&, const WebKit::StorageAreaImplIdentifier&, const String&> m_arguments;
};

class OpenDatabase {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_OpenDatabase; }
    static constexpr bool isSync = false;

    explicit OpenDatabase(const WebCore::IDBRequestData& requestData)
        : m_arguments(requestData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&> m_arguments;
};

class OpenDBRequestCancelled {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_OpenDBRequestCancelled; }
    static constexpr bool isSync = false;

    explicit OpenDBRequestCancelled(const WebCore::IDBRequestData& requestData)
        : m_arguments(requestData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&> m_arguments;
};

class DeleteDatabase {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DeleteDatabase; }
    static constexpr bool isSync = false;

    explicit DeleteDatabase(const WebCore::IDBRequestData& requestData)
        : m_arguments(requestData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&> m_arguments;
};

class EstablishTransaction {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IDBTransactionInfo>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_EstablishTransaction; }
    static constexpr bool isSync = false;

    EstablishTransaction(uint64_t databaseConnectionIdentifier, const WebCore::IDBTransactionInfo& info)
        : m_arguments(databaseConnectionIdentifier, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IDBTransactionInfo&> m_arguments;
};

class DatabaseConnectionPendingClose {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DatabaseConnectionPendingClose; }
    static constexpr bool isSync = false;

    explicit DatabaseConnectionPendingClose(uint64_t databaseConnectionIdentifier)
        : m_arguments(databaseConnectionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class DatabaseConnectionClosed {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DatabaseConnectionClosed; }
    static constexpr bool isSync = false;

    explicit DatabaseConnectionClosed(uint64_t databaseConnectionIdentifier)
        : m_arguments(databaseConnectionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class AbortOpenAndUpgradeNeeded {
public:
    using Arguments = std::tuple<uint64_t, std::optional<WebCore::IDBResourceIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_AbortOpenAndUpgradeNeeded; }
    static constexpr bool isSync = false;

    AbortOpenAndUpgradeNeeded(uint64_t databaseConnectionIdentifier, const std::optional<WebCore::IDBResourceIdentifier>& transactionIdentifier)
        : m_arguments(databaseConnectionIdentifier, transactionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const std::optional<WebCore::IDBResourceIdentifier>&> m_arguments;
};

class DidFireVersionChangeEvent {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IDBResourceIdentifier, WebCore::IndexedDB::ConnectionClosedOnBehalfOfServer>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DidFireVersionChangeEvent; }
    static constexpr bool isSync = false;

    DidFireVersionChangeEvent(uint64_t databaseConnectionIdentifier, const WebCore::IDBResourceIdentifier& requestIdentifier, const WebCore::IndexedDB::ConnectionClosedOnBehalfOfServer& connectionClosedOnBehalfOfServer)
        : m_arguments(databaseConnectionIdentifier, requestIdentifier, connectionClosedOnBehalfOfServer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IDBResourceIdentifier&, const WebCore::IndexedDB::ConnectionClosedOnBehalfOfServer&> m_arguments;
};

class DidFinishHandlingVersionChangeTransaction {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IDBResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DidFinishHandlingVersionChangeTransaction; }
    static constexpr bool isSync = false;

    DidFinishHandlingVersionChangeTransaction(uint64_t databaseConnectionIdentifier, const WebCore::IDBResourceIdentifier& transactionIdentifier)
        : m_arguments(databaseConnectionIdentifier, transactionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IDBResourceIdentifier&> m_arguments;
};

class AbortTransaction {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_AbortTransaction; }
    static constexpr bool isSync = false;

    explicit AbortTransaction(const WebCore::IDBResourceIdentifier& transactionIdentifier)
        : m_arguments(transactionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&> m_arguments;
};

class CommitTransaction {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CommitTransaction; }
    static constexpr bool isSync = false;

    CommitTransaction(const WebCore::IDBResourceIdentifier& transactionIdentifier, uint64_t pendingRequestCount)
        : m_arguments(transactionIdentifier, pendingRequestCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, uint64_t> m_arguments;
};

class CreateObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBObjectStoreInfo>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CreateObjectStore; }
    static constexpr bool isSync = false;

    CreateObjectStore(const WebCore::IDBRequestData& requestData, const WebCore::IDBObjectStoreInfo& info)
        : m_arguments(requestData, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBObjectStoreInfo&> m_arguments;
};

class DeleteObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DeleteObjectStore; }
    static constexpr bool isSync = false;

    DeleteObjectStore(const WebCore::IDBRequestData& requestData, const String& objectStoreName)
        : m_arguments(requestData, objectStoreName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const String&> m_arguments;
};

class RenameObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, uint64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_RenameObjectStore; }
    static constexpr bool isSync = false;

    RenameObjectStore(const WebCore::IDBRequestData& requestData, uint64_t objectStoreIdentifier, const String& newName)
        : m_arguments(requestData, objectStoreIdentifier, newName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, uint64_t, const String&> m_arguments;
};

class ClearObjectStore {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_ClearObjectStore; }
    static constexpr bool isSync = false;

    ClearObjectStore(const WebCore::IDBRequestData& requestData, uint64_t objectStoreIdentifier)
        : m_arguments(requestData, objectStoreIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, uint64_t> m_arguments;
};

class CreateIndex {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBIndexInfo>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CreateIndex; }
    static constexpr bool isSync = false;

    CreateIndex(const WebCore::IDBRequestData& requestData, const WebCore::IDBIndexInfo& info)
        : m_arguments(requestData, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBIndexInfo&> m_arguments;
};

class DeleteIndex {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, uint64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DeleteIndex; }
    static constexpr bool isSync = false;

    DeleteIndex(const WebCore::IDBRequestData& requestData, uint64_t objectStoreIdentifier, const String& indexName)
        : m_arguments(requestData, objectStoreIdentifier, indexName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, uint64_t, const String&> m_arguments;
};

class RenameIndex {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, uint64_t, uint64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_RenameIndex; }
    static constexpr bool isSync = false;

    RenameIndex(const WebCore::IDBRequestData& requestData, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const String& newName)
        : m_arguments(requestData, objectStoreIdentifier, indexIdentifier, newName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, uint64_t, uint64_t, const String&> m_arguments;
};

class PutOrAdd {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBKeyData, WebCore::IDBValue, WebCore::IndexedDB::ObjectStoreOverwriteMode>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_PutOrAdd; }
    static constexpr bool isSync = false;

    PutOrAdd(const WebCore::IDBRequestData& requestData, const WebCore::IDBKeyData& key, const WebCore::IDBValue& value, const WebCore::IndexedDB::ObjectStoreOverwriteMode& overwriteMode)
        : m_arguments(requestData, key, value, overwriteMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBKeyData&, const WebCore::IDBValue&, const WebCore::IndexedDB::ObjectStoreOverwriteMode&> m_arguments;
};

class GetRecord {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBGetRecordData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetRecord; }
    static constexpr bool isSync = false;

    GetRecord(const WebCore::IDBRequestData& requestData, const WebCore::IDBGetRecordData& getRecordData)
        : m_arguments(requestData, getRecordData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBGetRecordData&> m_arguments;
};

class GetAllRecords {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBGetAllRecordsData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetAllRecords; }
    static constexpr bool isSync = false;

    GetAllRecords(const WebCore::IDBRequestData& requestData, const WebCore::IDBGetAllRecordsData& getAllRecordsData)
        : m_arguments(requestData, getAllRecordsData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBGetAllRecordsData&> m_arguments;
};

class GetCount {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBKeyRangeData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetCount; }
    static constexpr bool isSync = false;

    GetCount(const WebCore::IDBRequestData& requestData, const WebCore::IDBKeyRangeData& range)
        : m_arguments(requestData, range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBKeyRangeData&> m_arguments;
};

class DeleteRecord {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBKeyRangeData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_DeleteRecord; }
    static constexpr bool isSync = false;

    DeleteRecord(const WebCore::IDBRequestData& requestData, const WebCore::IDBKeyRangeData& range)
        : m_arguments(requestData, range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBKeyRangeData&> m_arguments;
};

class OpenCursor {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBCursorInfo>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_OpenCursor; }
    static constexpr bool isSync = false;

    OpenCursor(const WebCore::IDBRequestData& requestData, const WebCore::IDBCursorInfo& info)
        : m_arguments(requestData, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBCursorInfo&> m_arguments;
};

class IterateCursor {
public:
    using Arguments = std::tuple<WebCore::IDBRequestData, WebCore::IDBIterateCursorData>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_IterateCursor; }
    static constexpr bool isSync = false;

    IterateCursor(const WebCore::IDBRequestData& requestData, const WebCore::IDBIterateCursorData& data)
        : m_arguments(requestData, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBRequestData&, const WebCore::IDBIterateCursorData&> m_arguments;
};

class GetAllDatabaseNamesAndVersions {
public:
    using Arguments = std::tuple<WebCore::IDBResourceIdentifier, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_GetAllDatabaseNamesAndVersions; }
    static constexpr bool isSync = false;

    GetAllDatabaseNamesAndVersions(const WebCore::IDBResourceIdentifier& requestIdentifier, const WebCore::ClientOrigin& origin)
        : m_arguments(requestIdentifier, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IDBResourceIdentifier&, const WebCore::ClientOrigin&> m_arguments;
};

class CacheStorageOpenCache {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageOpenCache; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageOpenCacheReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::CacheIdentifierOrError>;
    CacheStorageOpenCache(const WebCore::ClientOrigin& origin, const String& cacheName)
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

class CacheStorageRemoveCache {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageRemoveCache; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageRemoveCacheReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RemoveCacheIdentifierOrError>;
    explicit CacheStorageRemoveCache(const WebCore::DOMCacheIdentifier& cacheIdentifier)
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

class CacheStorageAllCaches {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageAllCaches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageAllCachesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::CacheInfosOrError>;
    CacheStorageAllCaches(const WebCore::ClientOrigin& origin, uint64_t updateCounter)
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

class CacheStorageReference {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageReference; }
    static constexpr bool isSync = false;

    explicit CacheStorageReference(const WebCore::DOMCacheIdentifier& cacheIdentifier)
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

class CacheStorageDereference {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageDereference; }
    static constexpr bool isSync = false;

    explicit CacheStorageDereference(const WebCore::DOMCacheIdentifier& cacheIdentifier)
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

class CacheStorageRetrieveRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, WebCore::RetrieveRecordsOptions>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageRetrieveRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageRetrieveRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::CrossThreadRecordsOrError>;
    CacheStorageRetrieveRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const WebCore::RetrieveRecordsOptions& options)
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

class CacheStorageRemoveRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, WebCore::ResourceRequest, WebCore::CacheQueryOptions>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageRemoveRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageRemoveRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RecordIdentifiersOrError>;
    CacheStorageRemoveRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const WebCore::ResourceRequest& request, const WebCore::CacheQueryOptions& options)
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

class CacheStoragePutRecords {
public:
    using Arguments = std::tuple<WebCore::DOMCacheIdentifier, Vector<WebCore::DOMCacheEngine::CrossThreadRecord>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStoragePutRecords; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStoragePutRecordsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMCacheEngine::RecordIdentifiersOrError>;
    CacheStoragePutRecords(const WebCore::DOMCacheIdentifier& cacheIdentifier, const Vector<WebCore::DOMCacheEngine::CrossThreadRecord>& records)
        : m_arguments(cacheIdentifier, records)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DOMCacheIdentifier&, const Vector<WebCore::DOMCacheEngine::CrossThreadRecord>&> m_arguments;
};

class CacheStorageClearMemoryRepresentation {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageClearMemoryRepresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageClearMemoryRepresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::DOMCacheEngine::Error>>;
    explicit CacheStorageClearMemoryRepresentation(const WebCore::ClientOrigin& origin)
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

class CacheStorageRepresentation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkStorageManager_CacheStorageRepresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkStorageManager_CacheStorageRepresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace NetworkStorageManager
} // namespace Messages
