#include "config.h"
#include "BrowserDBStorageArea.h"

#include "ZawraStorageBridge.h"
#include <wtf/NeverDestroyed.h>

namespace WebKit {

std::unique_ptr<BrowserDBStorageArea> BrowserDBStorageArea::create(unsigned quota, const WebCore::ClientOrigin& origin, const String& path, Ref<WorkQueue>&& workQueue)
{
    return makeUnique<BrowserDBStorageArea>(quota, origin, path, WTFMove(workQueue));
}

BrowserDBStorageArea::BrowserDBStorageArea(unsigned quota, const WebCore::ClientOrigin& origin, const String& path, Ref<WorkQueue>&& workQueue)
    : StorageAreaBase(quota, origin)
    , m_path(path)
    , m_queue(WTFMove(workQueue))
{
}

BrowserDBStorageArea::~BrowserDBStorageArea()
{
}

void BrowserDBStorageArea::clear()
{
    String originStr = origin().topOrigin.toString();
    WebCore::ZawraStorageBridge::localStorageClear(originStr);
    notifyListenersAboutClear();
}

bool BrowserDBStorageArea::isEmpty()
{
    return false; // TODO: Implement if needed for performance
}

HashMap<String, String> BrowserDBStorageArea::allItems()
{
    // For now, return empty or implement a bulk-fetch bridge if required
    return HashMap<String, String>();
}

Expected<void, StorageError> BrowserDBStorageArea::setItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, String&& key, String&& value, const String& urlString)
{
    String originStr = origin().topOrigin.toString();
    String oldValue = WebCore::ZawraStorageBridge::localStorageGet(originStr, key);

    int32_t res = WebCore::ZawraStorageBridge::localStoragePut(originStr, key, value);
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, value, urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::removeItem(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& key, const String& urlString)
{
    String originStr = origin().topOrigin.toString();
    String oldValue = WebCore::ZawraStorageBridge::localStorageGet(originStr, key);
    if (oldValue.isNull())
        return makeUnexpected(StorageError::ItemNotFound);

    int32_t res = WebCore::ZawraStorageBridge::localStorageRemove(originStr, key);
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, key, oldValue, String(), urlString);

    return { };
}

Expected<void, StorageError> BrowserDBStorageArea::clear(IPC::Connection::UniqueID connection, StorageAreaImplIdentifier storageAreaImplID, const String& urlString)
{
    String originStr = origin().topOrigin.toString();
    int32_t res = WebCore::ZawraStorageBridge::localStorageClear(originStr);
    if (res != 0)
        return makeUnexpected(StorageError::Database);

    dispatchEvents(connection, storageAreaImplID, String(), String(), String(), urlString);

    return { };
}

} // namespace WebKit
