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
    m_db = getOrCreateDatabase(m_path);
}

BrowserDBStorageArea::~BrowserDBStorageArea()
{
}

void BrowserDBStorageArea::clear()
{
    if (m_db) {
        String originStr = origin().topOrigin.toString();
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
    HashMap<String, String> items;
    if (m_db) {
        String originStr = origin().topOrigin.toString();
        browserdb_localstore_get_all(m_db, originStr.utf8().data(), allItemsCallback, &items);
    }
    return items;
}

Expected<void, StorageError> BrowserDBStorageArea::setItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, String&& key, String&& value, const String& urlString)
{
    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().topOrigin.toString();
    auto oldValueStr = browserdb_localstore_get(m_db, originStr.utf8().data(), key.utf8().data());
    String oldValue;
    if (oldValueStr) {
        oldValue = String::fromUTF8(oldValueStr);
        browserdb_free_string(oldValueStr);
    }

    int32_t res = browserdb_localstore_insert(m_db, originStr.utf8().data(), key.utf8().data(), value.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, value, urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::removeItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& key, const String& urlString)
{
    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().topOrigin.toString();
    auto oldValueStr = browserdb_localstore_get(m_db, originStr.utf8().data(), key.utf8().data());
    if (!oldValueStr)
        return makeUnexpected(StorageError::ItemNotFound);

    String oldValue = String::fromUTF8(oldValueStr);
    browserdb_free_string(oldValueStr);

    int32_t res = browserdb_localstore_remove(m_db, originStr.utf8().data(), key.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, String(), urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::clear(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& urlString)
{
    if (!m_db)
        return makeUnexpected(StorageError::Database);

    String originStr = origin().topOrigin.toString();
    int32_t res = browserdb_localstore_clear(m_db, originStr.utf8().data());
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, String(), String(), String(), urlString);

    return { };
}

} // namespace WebKit
