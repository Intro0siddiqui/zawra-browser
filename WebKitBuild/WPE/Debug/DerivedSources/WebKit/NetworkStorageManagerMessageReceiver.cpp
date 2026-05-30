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

#include "config.h"
#include "NetworkStorageManager.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "FileSystemStorageError.h" // NOLINT
#include "FileSystemSyncAccessHandleInfo.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "NetworkStorageManagerMessages.h" // NOLINT
#include "StorageAreaIdentifier.h" // NOLINT
#include "StorageAreaImplIdentifier.h" // NOLINT
#include "StorageAreaMapIdentifier.h" // NOLINT
#include "StorageNamespaceIdentifier.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CacheQueryOptions.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/DOMCacheEngine.h> // NOLINT
#include <WebCore/DOMCacheIdentifier.h> // NOLINT
#include <WebCore/FileSystemHandleIdentifier.h> // NOLINT
#include <WebCore/FileSystemSyncAccessHandleIdentifier.h> // NOLINT
#include <WebCore/IDBCursorInfo.h> // NOLINT
#include <WebCore/IDBGetAllRecordsData.h> // NOLINT
#include <WebCore/IDBGetRecordData.h> // NOLINT
#include <WebCore/IDBIndexInfo.h> // NOLINT
#include <WebCore/IDBIterateCursorData.h> // NOLINT
#include <WebCore/IDBKeyData.h> // NOLINT
#include <WebCore/IDBKeyRangeData.h> // NOLINT
#include <WebCore/IDBObjectStoreInfo.h> // NOLINT
#include <WebCore/IDBRequestData.h> // NOLINT
#include <WebCore/IDBResourceIdentifier.h> // NOLINT
#include <WebCore/IDBTransactionInfo.h> // NOLINT
#include <WebCore/IDBValue.h> // NOLINT
#include <WebCore/IndexedDB.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/RetrieveRecordsOptions.h> // NOLINT
#include <WebCore/StorageEstimate.h> // NOLINT
#include <WebCore/StorageType.h> // NOLINT
#include <optional> // NOLINT
#include <utility> // NOLINT
#include <wtf/Expected.h> // NOLINT
#include <wtf/HashMap.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkStorageManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkStorageManager::Persisted::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Persisted>(connection, decoder, this, &NetworkStorageManager::persisted);
    if (decoder.messageName() == Messages::NetworkStorageManager::Persist::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Persist>(connection, decoder, this, &NetworkStorageManager::persist);
    if (decoder.messageName() == Messages::NetworkStorageManager::Estimate::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Estimate>(connection, decoder, this, &NetworkStorageManager::estimate);
    if (decoder.messageName() == Messages::NetworkStorageManager::FileSystemGetDirectory::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::FileSystemGetDirectory>(connection, decoder, this, &NetworkStorageManager::fileSystemGetDirectory);
    if (decoder.messageName() == Messages::NetworkStorageManager::CloseHandle::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CloseHandle>(connection, decoder, this, &NetworkStorageManager::closeHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::IsSameEntry::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::IsSameEntry>(connection, decoder, this, &NetworkStorageManager::isSameEntry);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetFileHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::GetFileHandle>(connection, decoder, this, &NetworkStorageManager::getFileHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetDirectoryHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::GetDirectoryHandle>(connection, decoder, this, &NetworkStorageManager::getDirectoryHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::RemoveEntry::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::RemoveEntry>(connection, decoder, this, &NetworkStorageManager::removeEntry);
    if (decoder.messageName() == Messages::NetworkStorageManager::Resolve::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Resolve>(connection, decoder, this, &NetworkStorageManager::resolve);
    if (decoder.messageName() == Messages::NetworkStorageManager::Move::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Move>(connection, decoder, this, &NetworkStorageManager::move);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetFile::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::GetFile>(connection, decoder, this, &NetworkStorageManager::getFile);
    if (decoder.messageName() == Messages::NetworkStorageManager::CreateSyncAccessHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CreateSyncAccessHandle>(connection, decoder, this, &NetworkStorageManager::createSyncAccessHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::CloseSyncAccessHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CloseSyncAccessHandle>(connection, decoder, this, &NetworkStorageManager::closeSyncAccessHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::RequestNewCapacityForSyncAccessHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::RequestNewCapacityForSyncAccessHandle>(connection, decoder, this, &NetworkStorageManager::requestNewCapacityForSyncAccessHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetHandleNames::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::GetHandleNames>(connection, decoder, this, &NetworkStorageManager::getHandleNames);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetHandle::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::GetHandle>(connection, decoder, this, &NetworkStorageManager::getHandle);
    if (decoder.messageName() == Messages::NetworkStorageManager::ConnectToStorageArea::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::ConnectToStorageArea>(connection, decoder, this, &NetworkStorageManager::connectToStorageArea);
    if (decoder.messageName() == Messages::NetworkStorageManager::CancelConnectToStorageArea::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CancelConnectToStorageArea>(connection, decoder, this, &NetworkStorageManager::cancelConnectToStorageArea);
    if (decoder.messageName() == Messages::NetworkStorageManager::DisconnectFromStorageArea::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DisconnectFromStorageArea>(connection, decoder, this, &NetworkStorageManager::disconnectFromStorageArea);
    if (decoder.messageName() == Messages::NetworkStorageManager::CloneSessionStorageNamespace::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CloneSessionStorageNamespace>(connection, decoder, this, &NetworkStorageManager::cloneSessionStorageNamespace);
    if (decoder.messageName() == Messages::NetworkStorageManager::SetItem::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::SetItem>(connection, decoder, this, &NetworkStorageManager::setItem);
    if (decoder.messageName() == Messages::NetworkStorageManager::RemoveItem::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::RemoveItem>(connection, decoder, this, &NetworkStorageManager::removeItem);
    if (decoder.messageName() == Messages::NetworkStorageManager::Clear::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::Clear>(connection, decoder, this, &NetworkStorageManager::clear);
    if (decoder.messageName() == Messages::NetworkStorageManager::OpenDatabase::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::OpenDatabase>(connection, decoder, this, &NetworkStorageManager::openDatabase);
    if (decoder.messageName() == Messages::NetworkStorageManager::OpenDBRequestCancelled::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::OpenDBRequestCancelled>(connection, decoder, this, &NetworkStorageManager::openDBRequestCancelled);
    if (decoder.messageName() == Messages::NetworkStorageManager::DeleteDatabase::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DeleteDatabase>(connection, decoder, this, &NetworkStorageManager::deleteDatabase);
    if (decoder.messageName() == Messages::NetworkStorageManager::EstablishTransaction::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::EstablishTransaction>(connection, decoder, this, &NetworkStorageManager::establishTransaction);
    if (decoder.messageName() == Messages::NetworkStorageManager::DatabaseConnectionPendingClose::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DatabaseConnectionPendingClose>(connection, decoder, this, &NetworkStorageManager::databaseConnectionPendingClose);
    if (decoder.messageName() == Messages::NetworkStorageManager::DatabaseConnectionClosed::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DatabaseConnectionClosed>(connection, decoder, this, &NetworkStorageManager::databaseConnectionClosed);
    if (decoder.messageName() == Messages::NetworkStorageManager::AbortOpenAndUpgradeNeeded::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::AbortOpenAndUpgradeNeeded>(connection, decoder, this, &NetworkStorageManager::abortOpenAndUpgradeNeeded);
    if (decoder.messageName() == Messages::NetworkStorageManager::DidFireVersionChangeEvent::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DidFireVersionChangeEvent>(connection, decoder, this, &NetworkStorageManager::didFireVersionChangeEvent);
    if (decoder.messageName() == Messages::NetworkStorageManager::DidFinishHandlingVersionChangeTransaction::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DidFinishHandlingVersionChangeTransaction>(connection, decoder, this, &NetworkStorageManager::didFinishHandlingVersionChangeTransaction);
    if (decoder.messageName() == Messages::NetworkStorageManager::AbortTransaction::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::AbortTransaction>(connection, decoder, this, &NetworkStorageManager::abortTransaction);
    if (decoder.messageName() == Messages::NetworkStorageManager::CommitTransaction::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CommitTransaction>(connection, decoder, this, &NetworkStorageManager::commitTransaction);
    if (decoder.messageName() == Messages::NetworkStorageManager::CreateObjectStore::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CreateObjectStore>(connection, decoder, this, &NetworkStorageManager::createObjectStore);
    if (decoder.messageName() == Messages::NetworkStorageManager::DeleteObjectStore::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DeleteObjectStore>(connection, decoder, this, &NetworkStorageManager::deleteObjectStore);
    if (decoder.messageName() == Messages::NetworkStorageManager::RenameObjectStore::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::RenameObjectStore>(connection, decoder, this, &NetworkStorageManager::renameObjectStore);
    if (decoder.messageName() == Messages::NetworkStorageManager::ClearObjectStore::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::ClearObjectStore>(connection, decoder, this, &NetworkStorageManager::clearObjectStore);
    if (decoder.messageName() == Messages::NetworkStorageManager::CreateIndex::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CreateIndex>(connection, decoder, this, &NetworkStorageManager::createIndex);
    if (decoder.messageName() == Messages::NetworkStorageManager::DeleteIndex::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DeleteIndex>(connection, decoder, this, &NetworkStorageManager::deleteIndex);
    if (decoder.messageName() == Messages::NetworkStorageManager::RenameIndex::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::RenameIndex>(connection, decoder, this, &NetworkStorageManager::renameIndex);
    if (decoder.messageName() == Messages::NetworkStorageManager::PutOrAdd::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::PutOrAdd>(connection, decoder, this, &NetworkStorageManager::putOrAdd);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetRecord::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::GetRecord>(connection, decoder, this, &NetworkStorageManager::getRecord);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetAllRecords::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::GetAllRecords>(connection, decoder, this, &NetworkStorageManager::getAllRecords);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetCount::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::GetCount>(connection, decoder, this, &NetworkStorageManager::getCount);
    if (decoder.messageName() == Messages::NetworkStorageManager::DeleteRecord::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::DeleteRecord>(connection, decoder, this, &NetworkStorageManager::deleteRecord);
    if (decoder.messageName() == Messages::NetworkStorageManager::OpenCursor::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::OpenCursor>(connection, decoder, this, &NetworkStorageManager::openCursor);
    if (decoder.messageName() == Messages::NetworkStorageManager::IterateCursor::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::IterateCursor>(connection, decoder, this, &NetworkStorageManager::iterateCursor);
    if (decoder.messageName() == Messages::NetworkStorageManager::GetAllDatabaseNamesAndVersions::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::GetAllDatabaseNamesAndVersions>(connection, decoder, this, &NetworkStorageManager::getAllDatabaseNamesAndVersions);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageOpenCache::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageOpenCache>(connection, decoder, this, &NetworkStorageManager::cacheStorageOpenCache);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageRemoveCache::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageRemoveCache>(connection, decoder, this, &NetworkStorageManager::cacheStorageRemoveCache);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageAllCaches::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageAllCaches>(connection, decoder, this, &NetworkStorageManager::cacheStorageAllCaches);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageReference::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CacheStorageReference>(connection, decoder, this, &NetworkStorageManager::cacheStorageReference);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageDereference::name())
        return IPC::handleMessage<Messages::NetworkStorageManager::CacheStorageDereference>(connection, decoder, this, &NetworkStorageManager::cacheStorageDereference);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageRetrieveRecords::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageRetrieveRecords>(connection, decoder, this, &NetworkStorageManager::cacheStorageRetrieveRecords);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageRemoveRecords::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageRemoveRecords>(connection, decoder, this, &NetworkStorageManager::cacheStorageRemoveRecords);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStoragePutRecords::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStoragePutRecords>(connection, decoder, this, &NetworkStorageManager::cacheStoragePutRecords);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageClearMemoryRepresentation::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageClearMemoryRepresentation>(connection, decoder, this, &NetworkStorageManager::cacheStorageClearMemoryRepresentation);
    if (decoder.messageName() == Messages::NetworkStorageManager::CacheStorageRepresentation::name())
        return IPC::handleMessageAsync<Messages::NetworkStorageManager::CacheStorageRepresentation>(connection, decoder, this, &NetworkStorageManager::cacheStorageRepresentation);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool NetworkStorageManager::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkStorageManager::ConnectToStorageAreaSync::name())
        return IPC::handleMessageSynchronous<Messages::NetworkStorageManager::ConnectToStorageAreaSync>(connection, decoder, replyEncoder, this, &NetworkStorageManager::connectToStorageAreaSync);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(replyEncoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return false;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled synchronous message %s to %" PRIu64, description(decoder.messageName()), decoder.destinationID());
    return false;
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Persisted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Persisted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Persisted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Persisted::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Persist>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Persist::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Persist>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Persist::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Estimate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Estimate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Estimate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Estimate::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_FileSystemGetDirectory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::FileSystemGetDirectory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_FileSystemGetDirectory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::FileSystemGetDirectory::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CloseHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CloseHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_IsSameEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::IsSameEntry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_IsSameEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::IsSameEntry::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetFileHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetFileHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_GetFileHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetFileHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetDirectoryHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetDirectoryHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_GetDirectoryHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetDirectoryHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_RemoveEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RemoveEntry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_RemoveEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RemoveEntry::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Resolve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Resolve::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Resolve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Resolve::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Move>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Move::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Move>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Move::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetFile>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetFile::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_GetFile>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetFile::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CreateSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CreateSyncAccessHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CreateSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CreateSyncAccessHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CloseSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CloseSyncAccessHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CloseSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CloseSyncAccessHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_RequestNewCapacityForSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RequestNewCapacityForSyncAccessHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_RequestNewCapacityForSyncAccessHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RequestNewCapacityForSyncAccessHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetHandleNames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetHandleNames::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_GetHandleNames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetHandleNames::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_GetHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_ConnectToStorageArea>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::ConnectToStorageArea::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_ConnectToStorageArea>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::ConnectToStorageArea::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_ConnectToStorageAreaSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::ConnectToStorageAreaSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_ConnectToStorageAreaSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::ConnectToStorageAreaSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CancelConnectToStorageArea>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CancelConnectToStorageArea::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DisconnectFromStorageArea>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DisconnectFromStorageArea::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CloneSessionStorageNamespace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CloneSessionStorageNamespace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_SetItem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::SetItem::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_SetItem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::SetItem::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_RemoveItem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RemoveItem::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_RemoveItem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RemoveItem::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_Clear>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Clear::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_Clear>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::Clear::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_OpenDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::OpenDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_OpenDBRequestCancelled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::OpenDBRequestCancelled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DeleteDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DeleteDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_EstablishTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::EstablishTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DatabaseConnectionPendingClose>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DatabaseConnectionPendingClose::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DatabaseConnectionClosed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DatabaseConnectionClosed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_AbortOpenAndUpgradeNeeded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::AbortOpenAndUpgradeNeeded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DidFireVersionChangeEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DidFireVersionChangeEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DidFinishHandlingVersionChangeTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DidFinishHandlingVersionChangeTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_AbortTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::AbortTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CommitTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CommitTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CreateObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CreateObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DeleteObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DeleteObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_RenameObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RenameObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_ClearObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::ClearObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CreateIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CreateIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DeleteIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DeleteIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_RenameIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::RenameIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_PutOrAdd>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::PutOrAdd::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetRecord>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetRecord::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetAllRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetAllRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetCount::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_DeleteRecord>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::DeleteRecord::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_OpenCursor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::OpenCursor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_IterateCursor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::IterateCursor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_GetAllDatabaseNamesAndVersions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::GetAllDatabaseNamesAndVersions::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageOpenCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageOpenCache::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageOpenCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageOpenCache::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageRemoveCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRemoveCache::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageRemoveCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRemoveCache::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageAllCaches>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageAllCaches::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageAllCaches>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageAllCaches::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageReference>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageReference::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageDereference>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageDereference::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageRetrieveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRetrieveRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageRetrieveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRetrieveRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageRemoveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRemoveRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageRemoveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRemoveRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStoragePutRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStoragePutRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStoragePutRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStoragePutRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageClearMemoryRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageClearMemoryRepresentation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageClearMemoryRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageClearMemoryRepresentation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkStorageManager_CacheStorageRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRepresentation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkStorageManager_CacheStorageRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkStorageManager::CacheStorageRepresentation::ReplyArguments>(globalObject, decoder);
}

}

#endif

