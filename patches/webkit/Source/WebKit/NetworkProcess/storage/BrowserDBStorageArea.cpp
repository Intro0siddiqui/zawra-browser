/*
 * Copyright (C) 2024 Zawra Browser. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "BrowserDBStorageArea.h"

#include <wtf/NeverDestroyed.h>

extern "C" {
void* browserdb_open(const char* path);
void browserdb_close(void* db);
int32_t browserdb_localstore_insert(void* db, const char* origin, const char* key, const char* value);
char* browserdb_localstore_get(void* db, const char* origin, const char* key);
int32_t browserdb_localstore_remove(void* db, const char* origin, const char* key);
int32_t browserdb_localstore_clear(void* db, const char* origin);
int32_t browserdb_localstore_get_all(void* db, const char* origin, void (*callback)(const char*, const char*, void*), void* user_data);
void browserdb_free_string(char* s);
}

namespace WebKit {

static HashMap<String, void*>& globalDatabases()
{
    static NeverDestroyed<HashMap<String, void*>> databases;
    return databases;
}

static void* getOrCreateDatabase(const String& path)
{
    auto& databases = globalDatabases();
    auto it = databases.find(path);
    if (it != databases.end())
        return it->value;

    void* db = browserdb_open(path.utf8().data());
    if (db)
        databases.add(path, db);
    return db;
}

std::unique_ptr<BrowserDBStorageArea> BrowserDBStorageArea::create(unsigned quota, const WebCore::ClientOrigin& origin, const String& path, Ref<WorkQueue>&& workQueue)
{
    return makeUnique<BrowserDBStorageArea>(quota, origin, path, WTFMove(workQueue));
}

BrowserDBStorageArea::BrowserDBStorageArea(unsigned quota, const WebCore::ClientOrigin& origin, const String& path, Ref<WorkQueue>&& workQueue)
    : StorageAreaBase(quota, origin)
    , m_path(path)
    , m_queue(WTFMove(workQueue))
{
    ASSERT(!isMainRunLoop());
    m_db = getOrCreateDatabase(m_path);
}

BrowserDBStorageArea::~BrowserDBStorageArea()
{
}

void BrowserDBStorageArea::clear()
{
    ASSERT(!isMainRunLoop());

    if (m_db) {
        String originStr = origin().clientOrigin.databaseIdentifier();
        browserdb_localstore_clear(m_db, originStr.utf8().data());
    }
    notifyListenersAboutClear();
}

bool BrowserDBStorageArea::isEmpty()
{
    return allItems().isEmpty();
}

static void allItemsCallback(const char* key, const char* value, void* userData)
{
    auto* map = static_cast<HashMap<String, String>*>(userData);
    map->add(String::fromUTF8(key), String::fromUTF8(value));
}

HashMap<String, String> BrowserDBStorageArea::allItems()
{
    ASSERT(!isMainRunLoop());

    HashMap<String, String> items;
    if (m_db) {
        String originStr = origin().clientOrigin.databaseIdentifier();
        browserdb_localstore_get_all(m_db, originStr.utf8().data(), allItemsCallback, &items);
    }
    return items;
}

Expected<void, StorageError> BrowserDBStorageArea::setItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, String&& key, String&& value, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().clientOrigin.databaseIdentifier();

    String oldValue;
    if (auto* oldValuePtr = browserdb_localstore_get(m_db, originStr.utf8().data(), key.utf8().data())) {
        oldValue = String::fromUTF8(oldValuePtr);
        browserdb_free_string(oldValuePtr);
    }

    int32_t res = browserdb_localstore_insert(m_db, originStr.utf8().data(), key.utf8().data(), value.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, value, urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::removeItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& key, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().clientOrigin.databaseIdentifier();

    auto* oldValuePtr = browserdb_localstore_get(m_db, originStr.utf8().data(), key.utf8().data());
    if (!oldValuePtr)
        return makeUnexpected(StorageError::ItemNotFound);

    String oldValue = String::fromUTF8(oldValuePtr);
    browserdb_free_string(oldValuePtr);

    int32_t res = browserdb_localstore_remove(m_db, originStr.utf8().data(), key.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, String(), urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::clear(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& urlString)
{
    ASSERT(!isMainRunLoop());

    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().clientOrigin.databaseIdentifier();
    int32_t res = browserdb_localstore_clear(m_db, originStr.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, String(), String(), String(), urlString);

    return { };
}

} // namespace WebKit