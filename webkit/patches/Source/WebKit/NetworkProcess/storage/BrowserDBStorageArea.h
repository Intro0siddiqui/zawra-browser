#pragma once

#include "StorageAreaBase.h"
#include <wtf/NeverDestroyed.h>
#include <wtf/FastMalloc.h>

namespace WebKit {

class BrowserDBStorageArea final : public StorageAreaBase {
    WTF_MAKE_FAST_ALLOCATED;
public:
    static std::unique_ptr<BrowserDBStorageArea> create(unsigned quota, const WebCore::ClientOrigin&, const String& path, Ref<WorkQueue>&&);
    BrowserDBStorageArea(unsigned quota, const WebCore::ClientOrigin&, const String& path, Ref<WorkQueue>&&);
    ~BrowserDBStorageArea();

    void clear() final;

private:
    Type type() const final { return StorageAreaBase::Type::SQLite; }
    StorageType storageType() const final { return StorageAreaBase::StorageType::Local; }
    bool isEmpty() final;
    HashMap<String, String> allItems() final;
    Expected<void, StorageError> setItem(IPC::Connection::UniqueID, StorageAreaImplIdentifier, String&& key, String&& value, const String& urlString) final;
    Expected<void, StorageError> removeItem(IPC::Connection::UniqueID, StorageAreaImplIdentifier, const String& key, const String& urlString) final;
    Expected<void, StorageError> clear(IPC::Connection::UniqueID, StorageAreaImplIdentifier, const String& urlString) final;

    String m_path;
    const Ref<WorkQueue> m_queue;
    void* m_db { nullptr };
};

} // namespace WebKit
