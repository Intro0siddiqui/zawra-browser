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
- **Status**: Partial (bridge infrastructure exists). Only `incrementHistoryVisit` in `Page.cpp` is wired up to BrowserDB. The following bridge methods exist in both C++ and Rust but are **never called** from any WebKit patch: `recordHistory()`, `addBookmark()`, `removeBookmark()`, `getBookmarks()`, `deleteCookiesForDomain()`. These are dead code awaiting call-site integration.

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

### Stage 1: IndexedDB Backing Store Subclassing
- **Objective**: Implement a custom `BrowserDBIDBBackingStore` class to route object stores, transactions, and cursors directly to Rust, avoiding the default SQLite engine.
- **Key Files**:
  - `Source/WebKit/NetworkProcess/storage/IDBStorageManager.cpp`
  - `Source/WebCore/Modules/indexeddb/server/IDBBackingStore.h`
  - `Source/WebCore/Modules/indexeddb/server/SQLiteIDBBackingStore.cpp` (Reference)

### Stage 2: IconDatabase Bypass
- **Objective**: Prevent the creation of standard SQLite databases for favicons by routing them into BrowserDB.
- **Key Files**:
  - `Source/WebCore/loader/icon/IconDatabase.cpp`
- **Tasks**:
  - Intercept the `IconDatabase::open` call to use a BrowserDB handle instead of `sqlite3_open`.

### Stage 3: Service Worker Cache API Integration
- **Objective**: Route standard web Cache API storage requests through Z-Net/BrowserDB ring buffers.
- **Key Files**:
  - `Source/WebKit/NetworkProcess/cache/NetworkCacheStorage.cpp`
  - `Source/WebCore/Modules/cache/CacheStorage.cpp`

### Stage 4: Compiling Without SQLite (`ENABLE_SQLITE=OFF`)
- **Objective**: Disable SQLite compilation completely by setting `-DENABLE_SQLITE=OFF` in CMake once all fallbacks are eliminated.
- **Outcome**: A minimized, hardened browser binary with zero legacy SQL attack surface or footprint.
