# Zawra Browser — Remaining Issues

> Generated: 2026-06-18 (verified by sub-agent audit)
> Total: **32 unresolved issues** (5 BrowserDB bugs resolved this session: Cookie wiring, History/bookmarks, IndexedDB backing store, Z_IDBStore cursor stubs, Cache API wrapper)

---

## RESOLVED

- Cookie wiring — 6 cookie paths fully wired via ZawraStorageBridge
- History/bookmarks — recordHistory() wired in PageClientImpl
- IndexedDB backing store — 17 working methods + cursor stubs completed
- Z_IDBStore cursor stubs — getAllRecords, getIndexRecord, openCursor, iterateCursor, getCount(index)
- Cache API wrapper — 4 FFI functions + C++ bridge intercepting NetworkCache::Storage (`NetworkCacheStorage.cpp` + `ZawraCacheBridge.h/cpp`); covers both HTTP NetworkCache and Service Worker Cache API

---

## C++ INTEGRATION LAYER (`patches/webkit/`)

- `ASSERT_NOT_REACHED` in `TextureMapperGL.cpp` filter switch default case
- Fullscreen API not implemented (`PageClientImpl.cpp`)
- Cross-process surface sharing — `m_hostFileDescriptor` stored in `WebPage.cpp` but never consumed
- `JavaScriptCore_INSTALLED_HEADERS` expands to nothing in `PlatformWPE.cmake:573`
- `webkitwpe-fake-api-headers` target exists at `PlatformWPE.cmake:251`
- `NetworkStorageSessionSoup.cpp` has 3 `RELEASE_ASSERT_NOT_REACHED()` paths (lines 111, 139, 297)
- `SQLiteStorageArea.cpp:63` has `ASSERT_NOT_REACHED()` in `sqlStatement()`
- 12 `[ZAWRA-DEBUG]` fprintf statements left in production patches

---

## RUST GLUE LAYER (`src/wpe_glue/`)

- `NewURI` returns `NS_ERROR_NOT_IMPLEMENTED` and NULL
- `NewChannel` passes URI pointer directly as channel pointer (placeholder)
- 15+ channel vtable methods are nops (suspend, resume, load groups, security info, etc.)
- Stream `fire_on_data_available` passes NULL input stream
- HTTP/1.1 only, hardcoded GET requests only
- `CString::new()` with `unwrap_or_default()` silently creates empty strings on NUL bytes
- Content-type hardcoded to `"application/octet-stream"`, charset hardcoded to `"UTF-8"`
- Channel always reports `pending = true`
- `GLOBAL_DB.get().expect(...)` panics if `Zawra_Storage_Init` never called
- Old Crypto API (AES-CBC, AES-CTR) always returns `NS_ERROR_FAILURE`
- Only AES-GCM works; AES-CBC, AES-CTR not implemented
- `thread::spawn().expect()` panics on thread exhaustion
- `CString::new().unwrap()` panics on NUL in `profile_path`
- `duration_since(UNIX_EPOCH).unwrap()` panics
- `global_engine().expect(...)` panics if used before init
- 144 `unsafe` occurrences, only 2 `// Safety:` comments
- `Zawra_Shutdown_Subsystems()` is a no-op
- WPE library search hardcoded to 4 paths
- `wpe_main` not found silently returns 0
- No diagnostic HTTP server for headless testing
- Hajr allocator uses `libc::malloc` — MPK/MTE completely bypassed
- Hajr ring pair creation has no error handling
- Hajr thread wrappers have no error handling

---

## RUST UI LAYER (`src/ui/`)

- Navigation methods (`navigate`, `stop`, `reload`, `go_back`, `go_forward`) in `renderer.rs` are stubs
- Window/GTK stubs return null — UB risk on dereference
- `lib.rs` contains empty mock modules that silently return null/empty
- `drawNumber()` falls to `notImplemented()` without Cairo
- `drawNumber()` no texture atlas reuse

---

## Z-NET (`dependencies/z-net/`)

- TLS session cache incomplete; `CertificateValidator.validateChain` returns `error.NotImplemented`
- PAC engine still incomplete (`catch {}` at `pac.zig:62`)
- WIRED TLS flag set to `false` at `tls.zig:341`
