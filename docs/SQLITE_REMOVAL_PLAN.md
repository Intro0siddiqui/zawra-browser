# SQLite Surgical Removal Plan

## Executive Summary

SQLite is a hardcoded WebKit dependency that compiles ~30 `.cpp` files on every build. Zawra Browser does **not** use SQLite — it replaces storage with **BrowserDB** (Rust). Removing SQLite saves compile time and eliminates dead code.

Web SQL Database (`window.openDatabase`) is **already disabled by default** (`DeprecatedGlobalSettings::m_webSQLEnabled = false`). The module is dead weight.

## Approach

Remove SQLite **layer by layer**, compiling after each layer to catch regressions early.

---

## Layer Dependency Map

| Layer | Subsystem | Files | Risk | Notes |
|-------|-----------|-------|------|-------|
| 1 | Web SQL Database | 17 cpp + 26 h + 11 idl | Low | Deprecated API, already disabled by default |
| 2 | IndexedDB SQLite backend | 3 cpp + IDBServer.cpp | Medium | BrowserDB replaces this |
| 3 | Service Workers + Push API | 2 cpp | Low | Guarded by `ENABLE(SERVICE_WORKER)` |
| 4 | AppCache | 1 cpp | Low | Deprecated API |
| 5 | platform/sql/ core | 7 cpp | High | Foundation layer, removed last |
| 6 | WebKit layer (ITP, LocalStorage, etc.) | ~15 cpp | High | Privacy/storage features |

## BrowserDB Replacement Analysis

| SQLite Consumer | BrowserDB covers it? | Action |
|----------------|---------------------|--------|
| LocalStorage (`SQLiteStorageArea`) | Yes | Already replaced |
| IndexedDB backend | Yes | Already replaced |
| Web SQL Database | No | Disable entirely (deprecated) |
| Service Worker registration | Possible | Future BrowserDB table |
| Push API database | Possible | Future BrowserDB table |
| AppCache | No | Disable entirely (deprecated) |
| ITP/ResourceLoadStatistics | Possible | Future BrowserDB table |
| Icon Database | No | Disable or use BrowserDB |

---

## Layer 1: Web SQL Database [x] (COMPLETED)

### Files to Remove from Sources.txt (lines 437-453)

```
Modules/webdatabase/ChangeVersionWrapper.cpp
Modules/webdatabase/Database.cpp
Modules/webdatabase/DatabaseAuthorizer.cpp
Modules/webdatabase/DatabaseContext.cpp
Modules/webdatabase/DatabaseManager.cpp
Modules/webdatabase/DatabaseTask.cpp
Modules/webdatabase/DatabaseThread.cpp
Modules/webdatabase/DatabaseTracker.cpp
Modules/webdatabase/LocalDOMWindowWebDatabase.cpp
Modules/webdatabase/OriginLock.cpp
Modules/webdatabase/SQLResultSet.cpp
Modules/webdatabase/SQLResultSetRowList.cpp
Modules/webdatabase/SQLStatement.cpp
Modules/webdatabase/SQLTransaction.cpp
Modules/webdatabase/SQLTransactionBackend.cpp
Modules/webdatabase/SQLTransactionCoordinator.cpp
Modules/webdatabase/SQLTransactionStateMachine.cpp
```

### Critical Cross-Dependency: DatabaseAuthorizer.h

`platform/sql/SQLiteAuthorizer.cpp` and `platform/sql/SQLiteDatabase.cpp` both include `DatabaseAuthorizer.h` from `Modules/webdatabase/`. Must move to `platform/sql/` before removal.

### External Files to Patch

| File | Change |
|------|--------|
| `page/ChromeClient.h` | Remove `#include "DatabaseDetails.h"`, remove `exceededDatabaseQuota()` virtual method |
| `loader/FrameLoader.cpp` | Remove `#include "DatabaseManager.h"`, remove `stopDatabases()` call |
| `bindings/js/JSLocalDOMWindowCustom.cpp` | Remove `openDatabase` binding and include |
| `page/SettingsBase.cpp` | Remove stale `#include "Database.h"` |
| `dom/ScriptExecutionContext.cpp` | Remove `#include "DatabaseContext.h"` |
| `bindings/js/WebCoreBuiltinNames.h` | Remove `macro(openDatabase)` |
| `inspector/InspectorController.cpp` | Remove `InspectorDatabaseAgent` instantiation |
| `inspector/CommandLineAPIHost.cpp/h` | Remove Database includes and `databaseId()` method |
| `inspector/InstrumentingAgents.h` | Remove `InspectorDatabaseAgent` forward decl and macro |
| `inspector/agents/InspectorDOMStorageAgent.cpp` | Remove `#include "Database.h"` |

### Inspector Files to Stub

| File | Action |
|------|--------|
| `inspector/agents/InspectorDatabaseAgent.cpp` | Gut implementation, keep empty shell |
| `inspector/agents/InspectorDatabaseAgent.h` | Keep header, remove Database dependencies |
| `inspector/InspectorDatabaseResource.cpp` | Gut implementation |
| `inspector/InspectorDatabaseResource.h` | Keep header, remove Database dependencies |
| `inspector/InspectorInstrumentation.h` | Remove `didOpenDatabase()` methods |
| `inspector/InspectorInstrumentation.cpp` | Remove `didOpenDatabaseImpl()` |

### CMake Changes

- `Source/WebCore/CMakeLists.txt`: Remove `Modules/webdatabase` from include dirs (line 73), IDL dirs (line 241), and IDL files (lines 760-770)
- `Source/WebCore/Headers.cmake`: Remove 5 public headers (lines 617-621)

---

## Layer 2: IndexedDB SQLite Backend

**Status**: Pending analysis (next phase)

## Layer 3: Service Workers + Push API

**Action**: Set `ENABLE_SERVICE_WORKER=OFF` in cmake. Already guarded.

## Layer 4: AppCache

**Action**: Remove from Sources.txt. Deprecated API, no feature guard exists.

## Layer 5: platform/sql/ Core

**Action**: Remove all 7 `.cpp` files once all consumers are gone. Also remove `find_package(SQLite3)` from CMake.

## Layer 6: WebKit Layer SQLite

**Status**: Pending analysis (requires BrowserDB integration for ITP, etc.)
