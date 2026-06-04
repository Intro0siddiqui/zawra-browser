/*
 * Copyright (C) 2008-2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "SQLiteStorageArea.h"

#include "Logging.h"
#include <WebCore/SQLiteFileSystem.h>
#include <WebCore/SQLiteStatement.h>
#include <WebCore/SQLiteTransaction.h>
#include <WebCore/StorageMap.h>
#include <WebCore/ZawraStorageBridge.h>
#include <wtf/FileSystem.h>

namespace WebKit {

constexpr Seconds transactionDuration { 500_ms };
constexpr unsigned maximumSizeForValuesKeptInMemory { 1 * KB };
constexpr auto createItemTableStatementAlternative = "CREATE TABLE IF NOT EXISTS ItemTable (key TEXT UNIQUE ON CONFLICT REPLACE, value BLOB NOT NULL ON CONFLICT FAIL)"_s;
constexpr auto createItemTableStatement = "CREATE TABLE ItemTable (key TEXT UNIQUE ON CONFLICT REPLACE, value BLOB NOT NULL ON CONFLICT FAIL)"_s;

ASCIILiteral SQLiteStorageArea::statementString(StatementType type) const
{
    switch (type) {
    case StatementType::CountItems:
        return "SELECT COUNT(*) FROM ItemTable"_s;
    case StatementType::DeleteItem:
        return "DELETE FROM ItemTable WHERE key=?"_s;
    case StatementType::DeleteAllItems:
        return "DELETE FROM ItemTable"_s;
    case StatementType::GetItem:
        return "SELECT value FROM ItemTable WHERE key=?"_s;
    case StatementType::GetAllItems:
        return "SELECT key, value FROM ItemTable"_s;
    case StatementType::SetItem:
        return "INSERT INTO ItemTable VALUES (?, ?)"_s;
    case StatementType::Invalid:
        break;
    }

    ASSERT_NOT_REACHED();
    return ""_s;
}

SQLiteStorageArea::SQLiteStorageArea(unsigned quota, const WebCore::ClientOrigin& origin, const String& path, Ref<WorkQueue>&& workQueue)
    : StorageAreaBase(quota, origin)
    , m_path(path)
    , m_queue(WTFMove(workQueue))
    , m_cachedStatements(static_cast<size_t>(StatementType::Invalid))
{
    ASSERT(!isMainRunLoop());
}

void SQLiteStorageArea::close()
{
    m_cache = std::nullopt;
    m_cacheSize = std::nullopt;
}

SQLiteStorageArea::~SQLiteStorageArea()
{
    ASSERT(!isMainRunLoop());

    bool databaseIsEmpty = isEmpty();
    close();
    if (databaseIsEmpty)
        WebCore::SQLiteFileSystem::deleteDatabaseFile(m_path);
}

bool SQLiteStorageArea::isEmpty()
{
    if (m_cache)
        return m_cache->isEmpty();
    return true;
}

void SQLiteStorageArea::clear()
{
    ASSERT(!isMainRunLoop());

    close();
    WebCore::SQLiteFileSystem::deleteDatabaseFile(m_path);
    notifyListenersAboutClear();
}

bool SQLiteStorageArea::createTableIfNecessary()
{
    return true;
}

bool SQLiteStorageArea::prepareDatabase(ShouldCreateIfNotExists shouldCreateIfNotExists)
{
    return true;
}

void SQLiteStorageArea::startTransactionIfNecessary()
{
    // removed
}

WebCore::SQLiteStatementAutoResetScope SQLiteStorageArea::cachedStatement(StatementType type)
{
    return WebCore::SQLiteStatementAutoResetScope { nullptr };
}

Expected<String, StorageError> SQLiteStorageArea::getItem(const String& key)
{
    if (m_cache) {
        auto iterator = m_cache->find(key);
        if (iterator == m_cache->end())
            return makeUnexpected(StorageError::ItemNotFound);

        if (auto* valueString = std::get_if<String>(&iterator->value)) {
            ASSERT(!valueString->isNull());
            return *valueString;
        }
    }

    return getItemFromDatabase(key);
}

Expected<String, StorageError> SQLiteStorageArea::getItemFromDatabase(const String& key)
{
    // Zawra Modification: Read data from BrowserDB via FFI bridge instead of SQLite
    String value = WebCore::ZawraStorageBridge::getData(key);
    if (!value.isNull() && !value.isEmpty())
        return value;
    
    return makeUnexpected(StorageError::ItemNotFound);
}

HashMap<String, String> SQLiteStorageArea::allItems()
{
    ASSERT(!isMainRunLoop());

    HashMap<String, String> items = WebCore::ZawraStorageBridge::getAllData();

    m_cache = HashMap<String, Value> { };
    m_cacheSize = 0;
    
    for (auto& item : items) {
        updateCacheIfNeeded(item.key, item.value);
    }

    return items;
}

Expected<void, StorageError> SQLiteStorageArea::setItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, String&& key, String&& value, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    //
        

    if (!requestSpace(key, value))
        return makeUnexpected(StorageError::QuotaExceeded);

    // Zawra Modification: Persist data to BrowserDB via FFI bridge instead of SQLite
    WebCore::ZawraStorageBridge::storeDataWithTTL(key, value, 0); // No TTL by default

    // startTransactionIfNecessary();
    String oldValue;
    if (auto valueOrError = getItem(key))
        oldValue = valueOrError.value();

/* Zawra: Disable SQLite persistence
    auto statement = cachedStatement(StatementType::SetItem);
    if (!statement || statement->bindText(1, key) || statement->bindBlob(2, value)) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::setItem failed on creating statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        
    }

    const auto result = statement->step();
    if (result != SQLITE_DONE) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::setItem failed on stepping statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        handleDatabaseCorruptionIfNeeded(result);
        
    }
*/

    dispatchEvents(connection, storageAreaImplID, key, oldValue, value, urlString);
    updateCacheIfNeeded(key, value);

    return { };
}

Expected<void, StorageError> SQLiteStorageArea::removeItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& key, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    //
        

    

    // startTransactionIfNecessary();
    String oldValue;
    if (auto valueOrError = getItem(key))
        oldValue = valueOrError.value();
    else
        return makeUnexpected(StorageError::ItemNotFound);

    // Zawra Modification: Delete data via BrowserDB FFI bridge instead of SQLite
    WebCore::ZawraStorageBridge::removeData(key);

/* Zawra: Disable SQLite persistence
    auto statement = cachedStatement(StatementType::DeleteItem);
    if (!statement || statement->bindText(1, key)) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::removeItem failed on creating statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        
    }

    const auto result = statement->step();
    if (result != SQLITE_DONE) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::removeItem failed on executing statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        handleDatabaseCorruptionIfNeeded(result);

        
    }
*/

    dispatchEvents(connection, storageAreaImplID, key, oldValue, String(), urlString);
    updateCacheIfNeeded(key, { });

    return { };
}

Expected<void, StorageError> SQLiteStorageArea::clear(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    //
        

    if (m_cache && m_cache->isEmpty())
        return makeUnexpected(StorageError::ItemNotFound);

    if (m_cache) {
        m_cache->clear();
        m_cacheSize = 0;
    }

    

    // startTransactionIfNecessary();
    
    // Zawra Modification: Clear all data via BrowserDB FFI bridge instead of SQLite
    WebCore::ZawraStorageBridge::clearData();

/* Zawra: Disable SQLite persistence
    auto statement = cachedStatement(StatementType::DeleteAllItems);
    if (!statement) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::clear failed on creating statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        
    }

    const auto result = statement->step();
    if (result != SQLITE_DONE) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::clear failed on executing statement (%d) - %s", m_database->lastError(), m_database->lastErrorMsg());
        handleDatabaseCorruptionIfNeeded(result);

        
    }

    if (m_database->lastChanges() <= 0)
        return makeUnexpected(StorageError::ItemNotFound);
*/

    dispatchEvents(connection, storageAreaImplID, String(), String(), String(), urlString);

    return { };
}

void SQLiteStorageArea::commitTransactionIfNecessary()
{
    // removed
}

void SQLiteStorageArea::handleLowMemoryWarning()
{
    // removed
}

bool SQLiteStorageArea::handleDatabaseCorruptionIfNeeded(int databaseError)
{
    return false;
}

void SQLiteStorageArea::updateCacheIfNeeded(const String& key, const String& value)
{
    if (!m_cache)
        return;

    ASSERT(m_cacheSize);
    auto iter = m_cache->find(key);
    bool itemExists = iter != m_cache->end();
    unsigned oldKeySize = 0;
    unsigned oldValueSize = 0;
    unsigned keySize = key.sizeInBytes();
    unsigned valueSize = value.sizeInBytes();
    if (itemExists) {
        oldKeySize = iter->key.sizeInBytes();
        WTF::switchOn(iter->value, [&](unsigned valueSize) {
            oldValueSize = valueSize;
        }, [&](const String& value) {
            oldValueSize = value.sizeInBytes();
        });
    }

    CheckedUint32 newCacheSize = *m_cacheSize;
    // Null value means to remove.
    if (value.isNull()) {
        m_cache->remove(key);
        newCacheSize -= oldKeySize;
        newCacheSize -= oldValueSize;
    } else {
        if (valueSize > maximumSizeForValuesKeptInMemory)
            m_cache->set(key, valueSize);
        else
            m_cache->set(key, value);
        newCacheSize -= oldKeySize;
        newCacheSize -= oldValueSize;
        newCacheSize += itemExists ? oldKeySize : keySize;
        newCacheSize += valueSize;
    }

    if (newCacheSize.hasOverflowed()) {
        RELEASE_LOG_ERROR(Storage, "SQLiteStorageArea::updateCacheIfNeeded newCacheSize has overflowed: cacheSize - %u, oldKeySize - %u, oldValueSize - %u, keySize - %u, valueSize - %u, will recompute", *m_cacheSize, oldKeySize, oldValueSize, keySize, valueSize);
        newCacheSize = 0;
        for (auto& value : m_cache->values()) {
            WTF::switchOn(value, [&](unsigned size) {
                newCacheSize += size;
            }, [&](const String& value) {
                newCacheSize += value.sizeInBytes();
            });
        }
    }

    m_cacheSize = newCacheSize;
}

bool SQLiteStorageArea::requestSpace(const String& key, const String& value)
{
    if (!m_cache)
        return key.sizeInBytes() + value.sizeInBytes() <= quota();
    if (value.isNull())
        return true;
    CheckedUint32 newCacheSize = *m_cacheSize;
    auto iter = m_cache->find(key);
    if (iter == m_cache->end())
        newCacheSize += key.sizeInBytes();
    else {
        auto oldValueSize = WTF::switchOn(iter->value, [](unsigned valueSize) {
            return valueSize;
        }, [](const String& value) {
            return value.sizeInBytes();
        });
        newCacheSize -= oldValueSize;
    }
    newCacheSize += value.sizeInBytes();
    if (newCacheSize.hasOverflowed())
        return false;
    return newCacheSize <= quota();
}

} // namespace WebKit
