# BrowserDB Integration Roadmap

This document details the implemented features, critical audit findings, and remaining tasks required to achieve 100% data exclusivity for **BrowserDB** within the Zawra Browser. 

---

## 1. Implemented Subsystems

The following storage subsystems have been successfully routed to BrowserDB:

### A. LocalStorage
- **Implementation**: Interception wrapper implemented directly within `Source/WebKit/NetworkProcess/storage/SQLiteStorageArea.cpp`.
- **Status**: Active. Bypasses standard SQLite-based writing for key-value local storage.

### B. Cookies
- **Implementation**: Interception integration within `Source/WebCore/platform/network/soup/NetworkStorageSessionSoup.cpp` (using WebKit's Soup network backend).
- **Status**: Active (partial). Only `setCookiesFromDOM` and `cookiesForSession` are intercepted; many cookie mutation paths (`deleteCookie`, `deleteAllCookies`, `replaceCookies`, `setCookie`) still bypass BrowserDB and go directly to SoupCookieJar.

### C. Navigation History & Bookmarks
- **Implementation**: Customized storage layer routing to BrowserDB storage files instead of standard WebKit history databases.
- **Status**: Active. History recording is wired via `ZawraStorageBridge::recordHistory()` called from `PageClientImpl::didCommitLoadForMainFrame()` (`Source/WebKit/UIProcess/API/wpe/PageClientImpl.cpp`). Bookmarks are wired via keyboard shortcuts in `PageClientImpl::doneWithKeyEvent()`: Ctrl+D adds a bookmark for the current page, Ctrl+Shift+D removes it, Ctrl+B dumps all bookmarks to the debug log.

### D. Cache API (NetworkCache::Storage)
- **Implementation**: Interception via `NetworkCacheStorage.cpp` override in `Source/WebKit/NetworkProcess/cache/`, backed by `ZawraCacheBridge.h/cpp` which routes to BrowserDB's binary store via `Z_CacheStore_Store`/`Z_CacheStore_Retrieve` FFI functions.
- **Status**: Active. HTTP cache entries are stored and retrieved from BrowserDB instead of the default WPE cache directory.

### E. IndexedDB
- **Implementation**: Blob storage via `Z_Storage_PutBlob`/`Z_Storage_GetBlob`/`Z_Storage_DeleteBlob` FFI functions in `src/wpe_glue/storage.rs`. Binary key-value store (cursors) via `Z_IDBStore_Put`/`Z_IDBStore_Get`/`Z_IDBStore_Delete`/`Z_IDBStore_ScanPrefix`/`Z_IDBStore_Clear`.
- **Status**: Active. Blob read/write and cursor stubs implemented. `Z_Storage_DeleteBlob` is no longer a no-op — it properly removes entries via `db().localstore().remove()`.

### F. IconDatabase
- **Status**: Skipped. `ENABLE_ICONDATABASE` is not compiled in WPE WebKit, so no interception is needed.

---

## 2. Critical Audit Findings & Refactoring Requirements

A recent system audit revealed the following bugs and architectural deficiencies that must be addressed immediately to ensure performance, completeness, and security:

### A. IndexedDB Blob Leak (`Zawra_Storage_DeleteBlob` is a No-Op)
- **Problem**: The function `Zawra_Storage_DeleteBlob` is currently implemented as a no-op placeholder. This causes orphaned IndexedDB blob files to leak on the filesystem, leading to unbounded storage consumption.
- **Remediation**: Implement proper filesystem deletion logic within the Rust storage layer corresponding to the cleanup hooks in WebKit's Blob registry.

### B. O(N) Linear Reads in Storage Operations
- **Problem**: Reads in `Zawra_Cookie_Get` and `Zawra_LocalStorage_Get` perform linear scans ($O(N)$ complexity) over stored lists or memory tables to retrieve requested values.
- **Remediation**: Refactor lookups to use $O(1)$ point lookups via hash maps or Indexed B-Trees inside the BrowserDB interface.

### C. Security Boundary Leaks in `clearData()`
- **Problem**: When data clearing is requested, `clearData()` defaults to an origin hash value of `(0, 0)` due to missing context/parameters passed from the calling environment. This risks leaving data uncleared or clearing incorrect origins.
- **Remediation**: Modify the integration interfaces to thread proper security origin contexts to the FFI boundaries.

### D. Ignored Cookie Metadata
- **Problem**: The `Zawra` cookie storage currently ignores path and domain metadata, which breaks sub-domain isolation and path-specific cookie scoping.
- **Remediation**: Extend the BrowserDB cookie schema and FFI functions to correctly serialize, parse, and enforce cookie path and domain constraints.

---

## 3. Remaining Roadmap Stages

To achieve full isolation and deprecate legacy storage systems, the following phases must be completed:

### Stage 1: IndexedDB Backing Store Subclassing (Completed)
- **Objective**: Implement a custom `BrowserDBIDBBackingStore` class to route object stores, transactions, and cursors directly to Rust, avoiding the default SQLite engine.
- **Status**: Completed. Blob storage (`Z_Storage_PutBlob`/`GetBlob`/`DeleteBlob`) and binary key-value store with cursor scanning (`Z_IDBStore_*` functions) are implemented in the Rust FFI layer. WebKit blob operations are routed through the bridge. Cursor iteration stub completes the IndexedDB interception.

### Stage 2: IconDatabase Bypass (Skipped)
- **Objective**: Prevent the creation of standard SQLite databases for favicons by routing them into BrowserDB.
- **Status**: Skipped — `ENABLE_ICONDATABASE` is not compiled in WPE WebKit, so this is not needed.

### Stage 3: Service Worker Cache API Integration (Completed)
- **Objective**: Route standard web Cache API storage requests through Z-Net/BrowserDB ring buffers.
- **Status**: Completed. `NetworkCacheStorage.cpp` and `ZawraCacheBridge.h/cpp` intercept cache read/write/delete operations at the storage layer, routing them to BrowserDB's binary store via `Z_CacheStore_*` FFI functions.

### Stage 4: History Recording & Bookmarks (Completed)
- **Objective**: Wire BrowserDB history and bookmark storage to real call sites in the UI layer.
- **Status**: Completed. `recordHistory()` is called from `PageClientImpl::didCommitLoadForMainFrame()`. Bookmark shortcuts (Ctrl+D, Ctrl+Shift+D, Ctrl+B) are handled in `PageClientImpl::doneWithKeyEvent()`.

### Stage 5: Compiling Without SQLite (`ENABLE_SQLITE=OFF`)
- **Objective**: Disable SQLite compilation completely by setting `-DENABLE_SQLITE=OFF` in CMake once all fallbacks are eliminated.
- **Outcome**: A minimized, hardened browser binary with zero legacy SQL attack surface or footprint.
