# SQLite Removal — Full BrowserDB Replacement Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use compose:subagent (recommended) or compose:execute to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace all upstream SQLite consumers with BrowserDB-backed implementations, add CMake disable flags for each component, and remove SQLite from the build entirely.

**Architecture:** Each SQLite-consuming component gets: (1) new Rust FFI functions in `src/wpe_glue/storage.rs`, (2) a C++ bridge in `ZawraStorageBridge.h/cpp`, (3) the upstream consumer file patched to call the bridge instead of SQLite APIs. CMake `ENABLE_*` flags gate compilation of each component. Once all consumers are replaced, SQLite is removed from `OptionsWPE.cmake` and `WebCore_LIBRARIES`.

**Tech Stack:** C++ (WebKit patches), Rust (BrowserDB FFI), CMake (build flags)

---

## File Structure

### Existing files to modify
| File | Purpose |
|------|---------|
| `src/wpe_glue/storage.rs` | Add FFI functions for each component |
| `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.h` | Add static bridge methods |
| `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp` | Implement bridge methods |
| `patches/webkit/Source/cmake/OptionsWPE.cmake` | Add `ENABLE_*` flags, remove `find_package(SQLite3 REQUIRED)` |
| `patches/webkit/Source/WebCore/CMakeLists.txt` | Conditional source file inclusion |
| `patches/webkit/Source/WebCore/Headers.cmake` | Conditional header listing |
| `patches/webkit/Source/WebKit/Sources.txt` | Conditional NetworkProcess source listing |
| `patches/webkit/Source/WebKit/CMakeLists.txt` | Conditional include directories |

### New files to create
| File | Purpose |
|------|---------|
| `patches/webkit/Source/WebCore/Modules/webdatabase/ZWebSQLBridge.h` | WebSQL bridge header |
| `patches/webkit/Source/WebCore/Modules/webdatabase/ZWebSQLBridge.cpp` | WebSQL bridge implementation |
| `patches/webkit/Source/WebCore/loader/appcache/ZAppCacheBridge.h` | ApplicationCache bridge header |
| `patches/webkit/Source/WebCore/loader/appcache/ZAppCacheBridge.cpp` | ApplicationCache bridge implementation |
| `patches/webkit/Source/WebKit/NetworkProcess/Classifier/ZITPBridge.h` | ITP bridge header |
| `patches/webkit/Source/WebKit/NetworkProcess/Classifier/ZITPBridge.cpp` | ITP bridge implementation |
| `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/ZPCMBridge.h` | PCM bridge header |
| `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/ZPCMBridge.cpp` | PCM bridge implementation |
| `patches/webkit/Source/WebCore/Modules/push-api/ZPushBridge.h` | Push bridge header |
| `patches/webkit/Source/WebCore/Modules/push-api/ZPushBridge.cpp` | Push bridge implementation |
| `patches/webkit/Source/WebCore/workers/service/server/ZSWRegBridge.h` | SW Registration bridge header |
| `patches/webkit/Source/WebCore/workers/service/server/ZSWRegBridge.cpp` | SW Registration bridge implementation |

---

## Phase 1: CMake Disable Flags

### Task 1.1: Add feature flags to OptionsWPE.cmake

**Covers:** Build system configuration

**Files:**
- Create: `patches/webkit/Source/cmake/OptionsWPE.cmake`

- [ ] **Step 1: Create the patched OptionsWPE.cmake**

Copy the upstream `webkit/source/Source/cmake/OptionsWPE.cmake` to `patches/webkit/Source/cmake/OptionsWPE.cmake`, then add these flags after the existing `WEBKIT_OPTION_DEFINE` block (around line 70):

```cmake
# Zawra SQLite replacement flags
WEBKIT_OPTION_DEFINE(ENABLE_WEBSQL "Toggle WebSQL database support" PRIVATE ON)
WEBKIT_OPTION_DEFINE(ENABLE_APPLICATION_CACHE "Toggle Application Cache support" PRIVATE ON)
WEBKIT_OPTION_DEFINE(ENABLE_PRIVATE_CLICK_MEASUREMENT "Toggle Private Click Measurement" PRIVATE ON)
```

Note: `ENABLE_TRACKING_PREVENTION` and `ENABLE_SERVICE_WORKER` already exist. We add overrides in the WPE section:

```cmake
# Zawra: default these ON for WPE (they are OFF globally)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TRACKING_PREVENTION PRIVATE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SERVICE_WORKER PRIVATE ON)
```

- [ ] **Step 2: Run zawra-setup to overlay the patch**

```bash
cargo run --release -p zawra-setup
```

- [ ] **Step 3: Run CMake configure to verify flags appear**

```bash
cd webkit/build && cmake -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_VIDEO=OFF -DENABLE_VIDEO_LOOP=OFF -DENABLE_WEB_AUDIO=OFF \
  -DENABLE_WEB_CODECS=OFF -DENABLE_XSLT=OFF \
  -DENABLE_WEBSQL=OFF -DENABLE_APPLICATION_CACHE=OFF \
  ../source 2>&1 | tail -5
```

Expected: CMake configures successfully. `ENABLE_WEBSQL=OFF` and `ENABLE_APPLICATION_CACHE=OFF` are recognized.

- [ ] **Step 4: Commit**

```bash
git add patches/webkit/Source/cmake/OptionsWPE.cmake
git commit -m "feat(build): add Zawra CMake flags for SQLite component disabling"
```

### Task 1.2: Make WebCore sources conditional

**Covers:** Build system configuration

**Files:**
- Modify: `patches/webkit/Source/WebCore/CMakeLists.txt` (conditional source inclusion)
- Modify: `patches/webkit/Source/WebCore/Sources.txt` (conditional source listing)
- Modify: `patches/webkit/Source/WebCore/Headers.cmake` (conditional header listing)

- [ ] **Step 1: Wrap WebSQL sources in CMakeLists.txt**

In `patches/webkit/Source/WebCore/CMakeLists.txt`, find the `Modules/webdatabase/` source listings and wrap them:

```cmake
if (ENABLE_WEBSQL)
  list(APPEND WebCore_SOURCES
    Modules/webdatabase/Database.cpp
    Modules/webdatabase/DatabaseManager.cpp
    Modules/webdatabase/DatabaseTracker.cpp
    Modules/webdatabase/SQLStatement.cpp
    Modules/webdatabase/SQLTransactionBackend.cpp
    # ... all other webdatabase files
  )
endif()
```

- [ ] **Step 2: Wrap ApplicationCache sources**

```cmake
if (ENABLE_APPLICATION_CACHE)
  list(APPEND WebCore_SOURCES
    loader/appcache/ApplicationCache.cpp
    loader/appcache/ApplicationCacheGroup.cpp
    loader/appcache/ApplicationCacheHost.cpp
    loader/appcache/ApplicationCacheManifestParser.cpp
    loader/appcache/ApplicationCacheResource.cpp
    loader/appcache/ApplicationCacheStorage.cpp
  )
endif()
```

- [ ] **Step 3: Wrap PCM sources in WebKit/Sources.txt**

In `patches/webkit/Source/WebKit/Sources.txt`, wrap PrivateClickMeasurement entries:

```
#if ENABLE_PRIVATE_CLICK_MEASUREMENT
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementDatabase.cpp
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementManager.cpp
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementManagerProxy.cpp
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementPersistentStore.cpp
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementSender.cpp
NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementTimer.cpp
#endif
```

Note: `Sources.txt` is a plain text file processed by CMake's `file(STRINGS)`. The `#if`/`#endif` syntax is not native CMake — we need to use CMake's `if()` block instead. The actual approach:

```cmake
if (ENABLE_PRIVATE_CLICK_MEASUREMENT)
  list(APPEND WebKit_SOURCES
    NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementDatabase.cpp
    # ...
  )
endif()
```

This requires modifying the CMakeLists.txt that processes Sources.txt, not Sources.txt itself. The correct approach is to add conditional blocks in `WebKit/CMakeLists.txt`.

- [ ] **Step 4: Wrap ITP sources conditionally**

ITP is already guarded by `#if ENABLE(TRACKING_PREVENTION)` in the source files. No CMake changes needed — the source files self-guard.

- [ ] **Step 5: Run CMake configure with all flags OFF**

```bash
cd webkit/build && cmake -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_VIDEO=OFF -DENABLE_VIDEO_LOOP=OFF -DENABLE_WEB_AUDIO=OFF \
  -DENABLE_WEB_CODECS=OFF -DENABLE_XSLT=OFF \
  -DENABLE_WEBSQL=OFF -DENABLE_APPLICATION_CACHE=OFF \
  -DENABLE_PRIVATE_CLICK_MEASUREMENT=OFF \
  ../source 2>&1 | tail -5
```

Expected: CMake configures. WebSQL, AppCache, PCM sources are excluded.

- [ ] **Step 6: Commit**

```bash
git add patches/webkit/Source/WebCore/CMakeLists.txt patches/webkit/Source/WebCore/Sources.txt patches/webkit/Source/WebKit/Sources.txt patches/webkit/Source/WebKit/CMakeLists.txt
git commit -m "feat(build): make WebSQL, AppCache, PCM sources conditional on CMake flags"
```

---

## Phase 2: IndexedDB — Remove Remaining SQLite Files

**Covers:** Already partially done (Z_IDBStore replaces SQLiteIDBBackingStore). Need to remove the SQLiteIDB* source files from compilation.

### Task 2.1: Remove SQLiteIDB* from build

**Files:**
- Modify: `patches/webkit/Source/WebCore/CMakeLists.txt` (remove SQLiteIDB* entries)
- Modify: `patches/webkit/Source/WebCore/Modules/indexeddb/server/IDBServer.cpp` (remove remaining SQLite string literals)

- [ ] **Step 1: Comment out SQLiteIDB* source files in CMakeLists.txt**

Find and wrap these in the WebCore CMakeLists.txt:

```cmake
# Zawra: SQLiteIDB files replaced by Z_IDBStore (BrowserDB-backed)
# Modules/indexeddb/server/SQLiteIDBBackingStore.cpp
# Modules/indexeddb/server/SQLiteIDBCursor.cpp
# Modules/indexeddb/server/SQLiteIDBTransaction.cpp
```

- [ ] **Step 2: Clean up IDBServer.cpp**

In `patches/webkit/Source/WebCore/Modules/indexeddb/server/IDBServer.cpp`, remove the `IndexedDB.sqlite3` string literal references (lines ~627, ~640) and replace with BrowserDB equivalents or remove the dead code.

- [ ] **Step 3: Build and verify**

```bash
./thermal_build_control.sh
```

Expected: Build succeeds. No linker errors for SQLiteIDB* symbols.

- [ ] **Step 4: Commit**

```bash
git commit -m "feat(idb): remove SQLiteIDB* source files from build, fully replaced by Z_IDBStore"
```

---

## Phase 3: WebSQL — BrowserDB Replacement

**Covers:** Replaces `Database.cpp`, `DatabaseTracker.cpp`, `SQLTransactionBackend.cpp` etc.

### Task 3.1: Add Rust FFI for WebSQL

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions to storage.rs**

```rust
// WebSQL BrowserDB bridge
// Stores (origin, db_name, version, sql, params) tuples
// Each database is identified by origin+name hash

pub extern "C" fn Z_WebSQL_Open(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
    version: i32,
) -> i32 {
    // Store database metadata in BrowserDB localstore
    // Returns NS_OK on success
}

pub extern "C" fn Z_WebSQL_Close(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
) -> i32 {
    // Mark database as closed
}

pub extern "C" fn Z_WebSQL_ExecSQL(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
    sql: *const u8, sql_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32 {
    // Execute SQL and write result JSON to buffer
    // For SELECT: returns rows as JSON array
    // For INSERT/UPDATE/DELETE: returns affected row count
}

pub extern "C" fn Z_WebSQL_GetVersion(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
) -> i32 {
    // Returns version number
}

pub extern "C" fn Z_WebSQL_SetVersion(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
    version: i32,
) -> i32 {
    // Updates version
}

pub extern "C" fn Z_WebSQL_DeleteDatabase(
    origin_hi: u64, origin_lo: u64,
    db_name: *const u8, db_name_len: u32,
) -> i32 {
    // Deletes all data for this database
}
```

- [ ] **Step 2: Build Rust**

```bash
cargo build --release
```

- [ ] **Step 3: Commit**

```bash
git add src/wpe_glue/storage.rs
git commit -m "feat(websql): add BrowserDB FFI functions for WebSQL replacement"
```

### Task 3.2: Create C++ bridge for WebSQL

**Files:**
- Create: `patches/webkit/Source/WebCore/Modules/webdatabase/ZWebSQLBridge.h`
- Create: `patches/webkit/Source/WebCore/Modules/webdatabase/ZWebSQLBridge.cpp`

- [ ] **Step 1: Create ZWebSQLBridge.h**

```cpp
#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZWebSQLBridge — BrowserDB-backed WebSQL replacement
// Routes all WebSQL operations through BrowserDB via Rust FFI.
class ZWebSQLBridge {
public:
    static int openDatabase(uint64_t originHi, uint64_t originLo,
                           const String& dbName, int version);
    static int closeDatabase(uint64_t originHi, uint64_t originLo,
                            const String& dbName);
    static int execSQL(uint64_t originHi, uint64_t originLo,
                      const String& dbName, const String& sql,
                      char* resultBuf, uint32_t resultBufLen,
                      uint32_t* resultWritten);
    static int getVersion(uint64_t originHi, uint64_t originLo,
                         const String& dbName);
    static int setVersion(uint64_t originHi, uint64_t originLo,
                         const String& dbName, int version);
    static int deleteDatabase(uint64_t originHi, uint64_t originLo,
                             const String& dbName);
};
```

- [ ] **Step 2: Create ZWebSQLBridge.cpp**

Implement each method by calling the corresponding `extern "C"` FFI function from `storage.rs`. Follow the pattern in `ZawraStorageBridge.cpp` — use `Vector<LChar>` for string marshalling, call FFI, handle errors.

- [ ] **Step 3: Add to WebCore build**

In `patches/webkit/Source/WebCore/CMakeLists.txt`, add to the WebSQL conditional block:

```cmake
if (ENABLE_WEBSQL)
  list(APPEND WebCore_SOURCES
    Modules/webdatabase/ZWebSQLBridge.cpp
    # ... existing webdatabase sources
  )
endif()
```

- [ ] **Step 4: Build and verify**

```bash
cargo run --release -p zawra-setup && ./thermal_build_control.sh
```

- [ ] **Step 5: Commit**

```bash
git add patches/webkit/Source/WebCore/Modules/webdatabase/ZWebSQLBridge.*
git commit -m "feat(websql): add ZWebSQLBridge C++ bridge for BrowserDB-backed WebSQL"
```

### Task 3.3: Patch WebSQL consumers to use ZWebSQLBridge

**Files:**
- Modify: `patches/webkit/Source/WebCore/Modules/webdatabase/Database.cpp`
- Modify: `patches/webkit/Source/WebCore/Modules/webdatabase/DatabaseTracker.cpp`
- Modify: `patches/webkit/Source/WebCore/Modules/webdatabase/SQLTransactionBackend.cpp`

- [ ] **Step 1: Patch Database.cpp**

Replace SQLite database opening with `ZWebSQLBridge::openDatabase()`. Replace SQL execution with `ZWebSQLBridge::execSQL()`. The key function is `Database::open()` and `Database::executeSQL()`.

- [ ] **Step 2: Patch DatabaseTracker.cpp**

Replace SQLite-based tracker with `ZWebSQLBridge` calls for database enumeration and deletion.

- [ ] **Step 3: Patch SQLTransactionBackend.cpp**

Replace SQLite transaction execution with `ZWebSQLBridge::execSQL()` calls.

- [ ] **Step 4: Build and verify**

```bash
./thermal_build_control.sh
```

Expected: Build succeeds. WebSQL now uses BrowserDB.

- [ ] **Step 5: Commit**

```bash
git commit -m "feat(websql): route WebSQL operations through ZWebSQLBridge to BrowserDB"
```

---

## Phase 4: ApplicationCache — BrowserDB Replacement

### Task 4.1: Add Rust FFI for AppCache

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions**

```rust
pub extern "C" fn Z_AppCache_StoreManifest(
    origin_hi: u64, origin_lo: u64,
    manifest_url: *const u8, manifest_url_len: u32,
    manifest_data: *const u8, manifest_data_len: u32,
) -> i32

pub extern "C" fn Z_AppCache_GetManifest(
    origin_hi: u64, origin_lo: u64,
    manifest_url: *const u8, manifest_url_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_AppCache_StoreResource(
    origin_hi: u64, origin_lo: u64,
    resource_url: *const u8, resource_url_len: u32,
    resource_data: *const u8, resource_data_len: u32,
) -> i32

pub extern "C" fn Z_AppCache_GetResource(
    origin_hi: u64, origin_lo: u64,
    resource_url: *const u8, resource_url_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_AppCache_DeleteOrigin(
    origin_hi: u64, origin_lo: u64,
) -> i32
```

- [ ] **Step 2: Build Rust**

```bash
cargo build --release
```

- [ ] **Step 3: Commit**

```bash
git add src/wpe_glue/storage.rs
git commit -m "feat(appcache): add BrowserDB FFI functions for ApplicationCache replacement"
```

### Task 4.2: Create C++ bridge and patch consumers

**Files:**
- Create: `patches/webkit/Source/WebCore/loader/appcache/ZAppCacheBridge.h`
- Create: `patches/webkit/Source/WebCore/loader/appcache/ZAppCacheBridge.cpp`
- Modify: `patches/webkit/Source/WebCore/loader/appcache/ApplicationCacheStorage.cpp`

- [ ] **Step 1: Create ZAppCacheBridge.h/.cpp**

Follow the same pattern as ZWebSQLBridge. Each method calls the corresponding FFI function.

- [ ] **Step 2: Patch ApplicationCacheStorage.cpp**

Replace SQLite database operations with `ZAppCacheBridge` calls.

- [ ] **Step 3: Build and verify**

```bash
./thermal_build_control.sh
```

- [ ] **Step 4: Commit**

```bash
git commit -m "feat(appcache): route ApplicationCache through ZAppCacheBridge to BrowserDB"
```

---

## Phase 5: ITP — BrowserDB Replacement

### Task 5.1: Add Rust FFI for ITP

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions**

```rust
pub extern "C" fn Z_ITP_StoreStatistics(
    origin_hi: u64, origin_lo: u64,
    data: *const u8, data_len: u32,
) -> i32

pub extern "C" fn Z_ITP_GetStatistics(
    origin_hi: u64, origin_lo: u64,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_ITP_DeleteStatistics(
    origin_hi: u64, origin_lo: u64,
) -> i32

pub extern "C" fn Z_ITP_DeleteAll(
) -> i32

pub extern "C" fn Z_ITP_GetAllOrigins(
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32
```

- [ ] **Step 2: Build Rust**

```bash
cargo build --release
```

- [ ] **Step 3: Commit**

### Task 5.2: Create C++ bridge and patch ITP consumers

**Files:**
- Create: `patches/webkit/Source/WebKit/NetworkProcess/Classifier/ZITPBridge.h`
- Create: `patches/webkit/Source/WebKit/NetworkProcess/Classifier/ZITPBridge.cpp`
- Modify: `patches/webkit/Source/WebKit/NetworkProcess/Classifier/ResourceLoadStatisticsDatabaseStore.cpp`

- [ ] **Step 1: Create ZITPBridge**

- [ ] **Step 2: Patch ResourceLoadStatisticsDatabaseStore.cpp**

This is a large file (2866 lines). The approach:
1. Replace `SQLiteStatement` usage with `ZITPBridge` calls
2. Replace `SQLiteDatabase` usage with `ZITPBridge` calls
3. Keep the `#if ENABLE(TRACKING_PREVENTION)` guard

- [ ] **Step 3: Build and verify**

- [ ] **Step 4: Commit**

---

## Phase 6: PCM — BrowserDB Replacement

### Task 6.1: Add Rust FFI for PCM

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions**

```rust
pub extern "C" fn Z_PCM_StoreUnattributed(
    data: *const u8, data_len: u32,
) -> i32

pub extern "C" fn Z_PCM_GetUnattributed(
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_PCM_StoreAttributed(
    data: *const u8, data_len: u32,
) -> i32

pub extern "C" fn Z_PCM_GetAttributed(
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_PCM_DeleteMeasurement(
    source_id: u64,
) -> i32
```

- [ ] **Step 2: Build Rust**

- [ ] **Step 3: Commit**

### Task 6.2: Create C++ bridge and patch PCM consumers

**Files:**
- Create: `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/ZPCMBridge.h`
- Create: `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/ZPCMBridge.cpp`
- Modify: `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementDatabase.cpp`
- Modify: `patches/webkit/Source/WebKit/NetworkProcess/PrivateClickMeasurement/PrivateClickMeasurementPersistentStore.cpp`

- [ ] **Step 1: Create ZPCMBridge**

- [ ] **Step 2: Patch PrivateClickMeasurementDatabase.cpp**

Replace `SQLiteStatement` and `SQLiteTransaction` usage with `ZPCMBridge` calls.

- [ ] **Step 3: Patch PrivateClickMeasurementPersistentStore.cpp**

Replace SQLite file I/O with `ZPCMBridge` calls.

- [ ] **Step 4: Build and verify**

- [ ] **Step 5: Commit**

---

## Phase 7: Push — BrowserDB Replacement

### Task 7.1: Add Rust FFI for Push

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions**

```rust
pub extern "C" fn Z_Push_StoreSubscription(
    origin_hi: u64, origin_lo: u64,
    endpoint: *const u8, endpoint_len: u32,
    p256dh: *const u8, p256dh_len: u32,
    auth: *const u8, auth_len: u32,
) -> i32

pub extern "C" fn Z_Push_GetSubscription(
    origin_hi: u64, origin_lo: u64,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_Push_DeleteSubscription(
    origin_hi: u64, origin_lo: u64,
) -> i32

pub extern "C" fn Z_Push_DeleteAll(
) -> i32
```

- [ ] **Step 2: Build Rust**

- [ ] **Step 3: Commit**

### Task 7.2: Create C++ bridge and patch Push consumer

**Files:**
- Create: `patches/webkit/Source/WebCore/Modules/push-api/ZPushBridge.h`
- Create: `patches/webkit/Source/WebCore/Modules/push-api/ZPushBridge.cpp`
- Modify: `patches/webkit/Source/WebCore/Modules/push-api/PushDatabase.cpp`

- [ ] **Step 1: Create ZPushBridge**

- [ ] **Step 2: Patch PushDatabase.cpp**

Replace `SQLiteDatabase` and `SQLiteStatement` usage with `ZPushBridge` calls.

- [ ] **Step 3: Build and verify**

- [ ] **Step 4: Commit**

---

## Phase 8: SW Registration — BrowserDB Replacement

### Task 8.1: Add Rust FFI for SW Registration

**Files:**
- Modify: `src/wpe_glue/storage.rs`

- [ ] **Step 1: Add FFI functions**

```rust
pub extern "C" fn Z_SWReg_StoreRegistration(
    scope: *const u8, scope_len: u32,
    data: *const u8, data_len: u32,
) -> i32

pub extern "C" fn Z_SWReg_GetRegistration(
    scope: *const u8, scope_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_SWReg_DeleteRegistration(
    scope: *const u8, scope_len: u32,
) -> i32

pub extern "C" fn Z_SWReg_GetAll(
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32

pub extern "C" fn Z_SWReg_DeleteAll(
) -> i32
```

- [ ] **Step 2: Build Rust**

- [ ] **Step 3: Commit**

### Task 8.2: Create C++ bridge and patch SW Registration consumer

**Files:**
- Create: `patches/webkit/Source/WebCore/workers/service/server/ZSWRegBridge.h`
- Create: `patches/webkit/Source/WebCore/workers/service/server/ZSWRegBridge.cpp`
- Modify: `patches/webkit/Source/WebCore/workers/service/server/SWRegistrationDatabase.cpp`

- [ ] **Step 1: Create ZSWRegBridge**

- [ ] **Step 2: Patch SWRegistrationDatabase.cpp**

Replace `SQLiteDatabase` and `SQLiteStatement` usage with `ZSWRegBridge` calls.

- [ ] **Step 3: Build and verify**

- [ ] **Step 4: Commit**

---

## Phase 9: Remove SQLite from Build

### Task 9.1: Remove SQLite from WebCore libraries

**Files:**
- Modify: `patches/webkit/Source/cmake/OptionsWPE.cmake` (remove `find_package(SQLite3 REQUIRED)`)
- Modify: `patches/webkit/Source/WebCore/CMakeLists.txt` (remove `SQLite::SQLite3` from `WebCore_LIBRARIES`)
- Modify: `patches/webkit/Source/WebCore/Headers.cmake` (remove SQLite headers)

- [ ] **Step 1: Remove find_package from OptionsWPE.cmake**

In `patches/webkit/Source/cmake/OptionsWPE.cmake`, comment out or remove:

```cmake
# find_package(SQLite3 REQUIRED)  # Removed: BrowserDB replaces SQLite
```

- [ ] **Step 2: Remove SQLite from WebCore_LIBRARIES**

In `patches/webkit/Source/WebCore/CMakeLists.txt`, remove `SQLite::SQLite3` from the libraries list.

- [ ] **Step 3: Remove SQLite headers from Headers.cmake**

In `patches/webkit/Source/WebCore/Headers.cmake`, remove all `platform/sql/SQLite*.h` entries.

- [ ] **Step 4: Remove platform/sql/ source files from build**

In `patches/webkit/Source/WebCore/CMakeLists.txt`, comment out all `platform/sql/SQLite*.cpp` files.

- [ ] **Step 5: Run zawra-setup**

```bash
cargo run --release -p zawra-setup
```

- [ ] **Step 6: Run CMake configure**

```bash
cd webkit/build && cmake -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_VIDEO=OFF -DENABLE_VIDEO_LOOP=OFF -DENABLE_WEB_AUDIO=OFF \
  -DENABLE_WEB_CODECS=OFF -DENABLE_XSLT=OFF \
  -DENABLE_WEBSQL=OFF -DENABLE_APPLICATION_CACHE=OFF \
  -DENABLE_PRIVATE_CLICK_MEASUREMENT=OFF \
  ../source 2>&1 | tail -10
```

Expected: CMake configures without `find_package(SQLite3)`. No SQLite library linked.

- [ ] **Step 7: Build and verify**

```bash
./thermal_build_control.sh
```

Expected: Build succeeds. No SQLite symbols in the binary. Binary size reduced.

- [ ] **Step 8: Commit**

```bash
git commit -m "feat(build): remove SQLite from WebCore — all consumers replaced by BrowserDB"
```

---

## Phase 10: Verification & Cleanup

### Task 10.1: Verify binary size reduction

- [ ] **Step 1: Check binary size before and after**

```bash
# Before (with SQLite):
ls -lh webkit/build/libWPEWebKit.so

# After (without SQLite):
ls -lh webkit/build/libWPEWebKit.so
```

- [ ] **Step 2: Verify no SQLite symbols remain**

```bash
nm -D webkit/build/libWPEWebKit.so | grep -i sqlite
```

Expected: No output (no SQLite symbols).

- [ ] **Step 3: Run MiniBrowser smoke test**

```bash
timeout 20 ./mini-browser 2>&1 | head -50
```

Expected: Browser launches, loads default page, no crashes.

- [ ] **Step 4: Checkpoint build cache**

```bash
cd webkit/build && git add -A && git commit --amend --no-edit && git gc --aggressive --prune=now
```

### Task 10.2: Update roadmap documentation

**Files:**
- Modify: `docs/BROWSERDB_ROADMAP.md`

- [ ] **Step 1: Update roadmap to reflect completion**

Mark Stage 5 as complete. Document the new CMake flags and BrowserDB replacements.

- [ ] **Step 2: Commit**

```bash
git commit -m "docs: update BrowserDB roadmap — SQLite fully removed, all consumers replaced"
```

---

## Summary

| Phase | Component | Approach | CMake Flag |
|-------|-----------|----------|------------|
| 1 | Build system | Add flags, make sources conditional | `ENABLE_WEBSQL`, `ENABLE_APPLICATION_CACHE`, `ENABLE_PRIVATE_CLICK_MEASUREMENT` |
| 2 | IndexedDB SQLiteIDB* | Remove from build (already replaced by Z_IDBStore) | N/A |
| 3 | WebSQL | BrowserDB replacement via ZWebSQLBridge | `ENABLE_WEBSQL` |
| 4 | ApplicationCache | BrowserDB replacement via ZAppCacheBridge | `ENABLE_APPLICATION_CACHE` |
| 5 | ITP | BrowserDB replacement via ZITPBridge | `ENABLE_TRACKING_PREVENTION` |
| 6 | PCM | BrowserDB replacement via ZPCMBridge | `ENABLE_PRIVATE_CLICK_MEASUREMENT` |
| 7 | Push | BrowserDB replacement via ZPushBridge | `ENABLE_SERVICE_WORKER` |
| 8 | SW Registration | BrowserDB replacement via ZSWRegBridge | `ENABLE_SERVICE_WORKER` |
| 9 | SQLite removal | Remove from build entirely | N/A |
| 10 | Verification | Binary size check, symbol check, smoke test | N/A |
