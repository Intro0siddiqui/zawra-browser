# BrowserDB Integration Roadmap

This document details the remaining tasks and specific source files required to achieve 100% data exclusivity for **BrowserDB** within the Zawra Browser. Currently, the browser utilizes BrowserDB for high-throughput items (Cookies, LocalStorage) but falls back to SQLite for complex structures.

## 1. High Priority: Zero-Latency Native API ("God-Mode")
Expose BrowserDB directly to the JavaScript environment to allow developers to bypass standard Web APIs for maximum performance.

- **Objective**: Create a `navigator.zawra.db` global object in the JS context.
- **Key Files**:
    - `Source/WebCore/bindings/js/JSDOMGlobalObject.cpp`: To inject the new global.
    - `Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp`: To provide the underlying data access.
- **Tasks**:
    - Implement a Zero-Copy `ArrayBuffer` bridge so JS can read BrowserDB memory directly.
    - Expose `get()`, `put()`, and `query()` methods directly to the engine.

## 2. High Priority: IndexedDB Replacement
IndexedDB is the most complex storage API in WebKit. It currently uses a SQLite backing store.

- **Objective**: Implement `BrowserDBIDBBackingStore` to route all object stores, cursors, and transactions to Rust.
- **Key Files**:
    - `Source/WebKit/NetworkProcess/storage/IDBStorageManager.cpp`: The factory that instantiates the backing store.
    - `Source/WebCore/Modules/indexeddb/server/IDBBackingStore.h`: The interface we must implement.
    - `Source/WebCore/Modules/indexeddb/server/SQLiteIDBBackingStore.cpp`: The reference implementation to be bypassed.
- **Tasks**:
    - Create a Rust FFI layer for B-Tree style range scans (required for cursors).
    - Map IndexedDB Transactions to BrowserDB atomic commits.

## 2. Medium Priority: Metadata & Internal Databases
WebKit uses "silent" databases for browser maintenance.

### A. IconDatabase (Favicons)
- **Objective**: Route site icons to the persistent BrowserDB cache.
- **Key Files**:
    - `Source/WebCore/loader/icon/IconDatabase.cpp`
- **Tasks**:
    - Patch `IconDatabase::open` to utilize a BrowserDB handle instead of `sqlite3_open`.

### B. Cache API (Service Workers)
- **Objective**: Ensure Web-Standard Cache API data is stored in the high-performance Z-Net/BrowserDB ring buffers.
- **Key Files**:
    - `Source/WebKit/NetworkProcess/cache/NetworkCacheStorage.cpp`
    - `Source/WebCore/Modules/cache/CacheStorage.cpp`

## 3. The "Pure" Goal: Disabling SQLite
Once all components above are bridged, we can attempt to remove SQLite from the build entirely.

- **Objective**: Set `ENABLE_SQLITE=OFF` in CMake.
- **File**: `CMakeLists.txt` (Root and Port levels).
- **Outcome**: A smaller, faster binary with zero legacy SQL overhead.

---
*Created on Saturday, May 30, 2026*
