# BrowserDB Integration Roadmap

This document details the implemented features, critical audit findings, and remaining tasks required to achieve 100% data exclusivity for **BrowserDB** within the Zawra Browser. 

---

## 1. Implemented Subsystems

The following storage subsystems have been successfully routed to BrowserDB:

### A. LocalStorage
- **Implementation**: `BrowserDBStorageArea` class routes all localStorage operations to Rust FFI (`Z_LocalStorage_*` functions) which persist to BrowserDB's `LocalStoreTable`.
- **Status**: Active. Bypasses standard SQLite-based writing for key-value local storage.

### B. Cookies
- **Implementation**: Interception integration within `Source/WebCore/platform/network/soup/NetworkStorageSessionSoup.cpp` (using WebKit's Soup network backend).
- **Status**: Complete. 6 cookie paths wired via `ZawraStorageBridge`, fully routed to BrowserDB.

### C. Navigation History & Bookmarks
- **Implementation**: Customized storage layer routing to BrowserDB storage files instead of standard WebKit history databases.
- **Status**: Active. History recording is wired via `ZawraStorageBridge::recordHistory()` called from `PageClientImpl::didCommitLoadForMainFrame()` (`Source/WebKit/UIProcess/API/wpe/PageClientImpl.cpp`). Bookmarks are wired via keyboard shortcuts in `PageClientImpl::doneWithKeyEvent()`: Ctrl+D adds a bookmark for the current page, Ctrl+Shift+D removes it, Ctrl+B dumps all bookmarks to the debug log.

### D. Cache API (NetworkCache::Storage)
- **Implementation**: Interception via `NetworkCacheStorage.cpp` override in `Source/WebKit/NetworkProcess/cache/`, backed by `ZawraCacheBridge.h/cpp` which routes to BrowserDB's binary store via `Z_CacheStore_Store`/`Z_CacheStore_Retrieve`/`Z_CacheStore_Delete`/`Z_CacheStore_Clear` FFI functions. Covers both HTTP NetworkCache and Service Worker Cache API (both use `NetworkCache::Storage`).
- **Status**: Complete.

### E. IndexedDB
- **Implementation**: Blob storage via `Z_Storage_PutBlob`/`Z_Storage_GetBlob`/`Z_Storage_DeleteBlob` FFI functions in `src/wpe_glue/storage.rs`. Binary key-value store (cursors) via `Z_IDBStore_Put`/`Z_IDBStore_Get`/`Z_IDBStore_Delete`/`Z_IDBStore_ScanPrefix`/`Z_IDBStore_Clear`.
- **Status**: Active. Blob read/write and cursor stubs implemented. `Z_Storage_DeleteBlob` is no longer a no-op — it properly removes entries via `db().localstore().remove()`.

### F. IconDatabase
- **Status**: N/A. `ENABLE_ICONDATABASE` is not compiled in WPE WebKit, so no interception is needed or possible.

---

## 2. Critical Audit Findings & Refactoring Requirements

### A. IndexedDB Blob Leak
- **Status**: Resolved. `Z_Storage_DeleteBlob` now removes entries via `db().localstore().remove(origin_hash, key)`.

### B. O(N) Linear Reads in Storage Operations
- **Status**: Resolved. `Z_LocalStorage_Get` now uses origin+key direct lookup (`db().localstore().get(origin_hash, key)`). `Z_Cookie_Get` uses direct domain+name lookup (`db().cookies().get(domain_hash, name)`).

### C. Security Boundary Leaks in `clearData()`
- **Status**: Resolved. `ZawraStorageBridge::clearData()` no longer falls back to wiping all storage when URL context is missing; it requires per-origin URL hashes and calls `Z_LocalStorage_Clear(hi, lo)`.

### D. Ignored Cookie Metadata
- **Status**: Resolved. Cookie path/domain metadata is now parsed in `ZawraStorageBridge::storeCookie()` and stored in BrowserDB via `Z_Cookie_Put`. Path filtering is applied in `Z_Cookie_GetForDomain` so only cookies matching the requested path are returned.

---

## 3. Remaining Roadmap Stages

To achieve full isolation and deprecate legacy storage systems, the following phases must be completed:

### Stage 1: IndexedDB Backing Store Subclassing (Completed)
- **Objective**: Implement a custom `BrowserDBIDBBackingStore` class to route object stores, transactions, and cursors directly to Rust, avoiding the default SQLite engine.
- **Status**: Completed. Blob storage (`Z_Storage_PutBlob`/`GetBlob`/`DeleteBlob`) and binary key-value store with cursor scanning (`Z_IDBStore_*` functions) are implemented in the Rust FFI layer. WebKit blob operations are routed through the bridge. Cursor iteration stub completes the IndexedDB interception.

### Stage 2: IconDatabase Bypass (N/A)
- **Objective**: Prevent the creation of standard SQLite databases for favicons by routing them into BrowserDB.
- **Status**: N/A — `ENABLE_ICONDATABASE` is not compiled in WPE WebKit, so this is not needed.

### Stage 3: Cache API Integration (Completed)
- **Objective**: Route standard web Cache API and HTTP NetworkCache storage requests through BrowserDB's binary store.
- **Status**: Completed. `NetworkCacheStorage.cpp` and `ZawraCacheBridge.h/cpp` intercept cache read/write/delete/clear operations at the storage layer. A single interception point covers both HTTP NetworkCache and Service Worker Cache API (both use `NetworkCache::Storage`).

### Stage 4: History Recording & Bookmarks (Completed)
- **Objective**: Wire BrowserDB history and bookmark storage to real call sites in the UI layer.
- **Status**: Completed. `recordHistory()` is called from `PageClientImpl::didCommitLoadForMainFrame()`. Bookmark shortcuts (Ctrl+D, Ctrl+Shift+D, Ctrl+B) are handled in `PageClientImpl::doneWithKeyEvent()`.

### Stage 5: Compiling Without SQLite (`ENABLE_SQLITE=OFF`)
- **Objective**: Disable SQLite compilation completely by setting `-DENABLE_SQLITE=OFF` in CMake once all fallbacks are eliminated.
- **Status**: Complete. `SQLiteStorageArea.cpp` replaced with `BrowserDBStorageArea.cpp`. LocalStorageManager now instantiates `BrowserDBStorageArea` instead of SQLite-based storage. All SQLite includes removed from storage layer.
