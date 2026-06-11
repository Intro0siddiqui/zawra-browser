# Zawra Browser — Missing Features, TODOs, FIXMEs, HACKs, and Incomplete Code

> Generated: 2026-06-11
> Total items found: **62**
> Top 3 most important:
>   1. **Full GLContext/EGL stub (no GPU compositing)** — `ZawraLegacyStubs.cpp` returns nullptr/false for every GL method; DMA-BUF import in `TextureMapperGL.cpp` is `close(fd)` with no actual import.
>   2. **Hajr mem alloc uses libc malloc placeholder** — `Zawra_Hajr_MemAlloc()` in `init.rs` falls through to `libc::malloc` instead of Hajr's hardware-isolated allocator, defeating the entire purpose of MPK/MTE memory protection.
>   3. **Network QueryInterface returns NS_ERROR_NOT_IMPLEMENTED** — All three XPCOM objects (factory, protocol handler, channel) return NOT_IMPLEMENTED from `QueryInterface`, breaking WPE's ability to interact with the custom networking stack.

---

## Graphics / Rendering (13 items)

### 1. DMA-BUF / EGLImage import not implemented
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:213`
- **Issue:** The `beginPainting()` method has the hook to import the compositor FD, but the actual EGLImage/IOSurface import via `eglBindTexImage` / `glFramebufferTexture2D` is missing. The FD is immediately `close(fd)`'d.
- **Severity:** **BLOCKER** — without this, the z-graphics render output is never composited into WebKit's GL pipeline.

### 2. GLContext legacy stubs — all methods return nullptr/false
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraLegacyStubs.cpp:17-32`
- **Issue:** Every single `GLContext` method is a no-op stub:
  - `GLContext::current()` → nullptr
  - `GLContext::makeContextCurrent()` → false
  - `GLContext::create()` → nullptr
  - `GLContext::createSharing()` → nullptr
  - `GLContext::platformContext()` → nullptr
  - `GLContext::swapBuffers()` → empty body
  - `GLContext::lastErrorString()` → "Zawra Graphics: Legacy EGL disabled"
- **Severity:** **BLOCKER** — WebKit cannot render without EGL context management.

### 3. Window size hardcoded to 800x600
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:187-188`
- **Issue:** `ZawraGraphicsBridge::singleton().initialize(nullptr, 800, 600)` — window size is a placeholder; no code to query the actual window dimensions.
- **Severity:** **IMPORTANT** — causes incorrect viewport sizing in real browser mode.

### 4. drawNumber() falls to notImplemented() without Cairo
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:305-309`
- **Issue:** When `USE(CAIRO)` is not defined, `drawNumber()` uses `UNUSED_PARAM` for all parameters and calls `notImplemented()`.
- **Severity:** **NICE-TO-HAVE** — FPS counter rendering only.

### 5. drawNumber() FIXME — no texture atlas
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:264`
- **Issue:** Comment says "drawNumber() should save a number texture-atlas and re-use whenever possible."
- **Severity:** **NICE-TO-HAVE**

### 6. z-graphics: Windows (D3D12) and macOS (Metal) are FFI stubs only
- **Location:** `dependencies/z-graphics/TODO.md:10-13`
- **Issue:** "Windows (D3D12/Vulkan) implementation — Scaffolding/FFI Stubs" and "macOS (Metal) implementation — Scaffolding/FFI Stubs". Only Linux (Vulkan) has a real implementation.
- **Severity:** **IMPORTANT** — cross-platform support incomplete.

### 7. z-graphics TODO.md out of sync with reality
- **Location:** `dependencies/z-graphics/TODO.md`
- **Issue:** All 16 items are marked `[x]` (complete), but the actual code in `ZawraLegacyStubs.cpp` contradicts this — the GL layer is still mostly stub code.
- **Severity:** **IMPORTANT** — TODO.md is misleading.

### 8. WPE Renderer embed is a headless stub
- **Location:** `src/ui/renderer.rs:54-128`
- **Issue:** Every method (`init`, `navigate`, `stop`, `reload`, `go_back`, `go_forward`, `destroy`) just prints `eprintln!` and returns. The `#[cfg(wpe_available)]` code path is identical to the `#[cfg(not(wpe_available))]` path. No actual WPE view creation or navigation.
- **Severity:** **BLOCKER** — the browser cannot actually navigate or render pages through the Rust UI layer.

### 9. ZawraGraphicsBridge surface handle can silently fail
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraGraphicsBridge.cpp:34-44`
- **Issue:** If `ZawraGraphics_Initialize()` or `ZawraGraphics_CreateSurface()` returns false/nullptr, `initialize()` returns false but there is no fallback or error propagation to WebKit's compositor.
- **Severity:** **IMPORTANT** — silent failure leads to blank rendering.

### 10. No GBM device initialization
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraLegacyStubs.cpp:38-41`
- **Issue:** `GBMDevice::singleton()` returns a raw `new GBMDevice()` without initialization. `GBMDevice::initialize(const WTF::String&)` is an empty body.
- **Severity:** **IMPORTANT** — GBM-backed EGL won't work.

### 11. GTK native window stubs
- **Location:** `src/ui/window.rs:94-100`
- **Issue:** Section header says "Native window helpers (GTK stubs)". Functions return `std::ptr::null_mut()`.
- **Severity:** **IMPORTANT** — headless-only operation.

### 12. ASSERT_NOT_REACHED in TextureMapperGL filter switch
- **Location:** `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:339`
- **Issue:** Default case in filter operation switch hits `ASSERT_NOT_REACHED()` and returns empty set. If a new filter type is added upstream, this will crash in debug builds.
- **Severity:** **NICE-TO-HAVE**

### 13. Fullscreen API not implemented
- **Location:** `patches/webkit/Source/WebKit/UIProcess/API/wpe/PageClientImpl.cpp:353,389,394`
- **Issue:** `closeFullScreenManager()`, `beganEnterFullScreen()`, `beganExitFullScreen()` all call `notImplemented()`.
- **Severity:** **NICE-TO-HAVE**

---

## IPC / Sandbox (7 items)

### 14. Hajr memory allocator uses libc malloc placeholder
- **Location:** `src/wpe_glue/init.rs:143-151`
- **Issue:** `Zawra_Hajr_MemAlloc()` explicitly says "For now, we use a simple libc malloc or hajr equivalent if available" and falls back to `libc::malloc(size)`. The Hajr allocator is never actually called.
- **Severity:** **BLOCKER** — the whole point of Hajr integration is hardware-enforced memory isolation; this bypasses it entirely.

### 15. Hajr SignalEventLoop is a stub
- **Location:** `src/wpe_glue/init.rs:80-84`
- **Issue:** Comment says "Currently a stub that logs the signal." The function does nothing but print.
- **Severity:** **IMPORTANT** — event loop wakeup via Hajr is non-functional.

### 16. hajr_seal_process not called in all processes
- **Location:** `patches/webkit/Source/WebKit/WebProcess/wpe/WebProcessMainWPE.cpp:59`
- **Issue:** FIXME comment: "This should be probably called in other processes as well." Only the WebProcess is sealed.
- **Severity:** **IMPORTANT** — NetworkProcess, GPUProcess not sandboxed.

### 17. Hajr spawn compartment is a direct passthrough
- **Location:** `src/wpe_glue/launcher.rs:231-239`
- **Issue:** `Zawra_Hajr_SpawnProcess` directly calls `hajr_spawn_compartment` with no error handling, no fallback, no additional security setup.
- **Severity:** **IMPORTANT**

### 18. Bubblewrap sandbox disabled with no functional replacement
- **Location:** `patches/webkit/CMakeLists.txt:20-21`
- **Issue:** `ENABLE_BUBBLEWRAP_SANDBOX` is set to OFF. AGENTS.md notes this is intentional to avoid conflict with Hajr, but the Hajr `seal_process` is only called in WebProcess, leaving other processes unsandboxed.
- **Severity:** **IMPORTANT**

### 19. Hajr ring pair creation has no error handling
- **Location:** `src/wpe_glue/init.rs:118-134`
- **Issue:** `Zawra_Hajr_CreateRingPair` does not check if `__hajr_create_anonymous_ring`, `__hajr_map_anonymous_ring`, or `GetRingSignalFD` return valid values. If any fails, the returned `Zawra_Hajr_RingPair` will have 0 IDs and -1 FDs with no error indication.
- **Severity:** **IMPORTANT**

### 20. Hajr thread wrappers have no error handling
- **Location:** `src/wpe_glue/threading.rs:24-42`
- **Issue:** `Zawra_Thread_Create`, `Zawra_Thread_Join`, `Zawra_Thread_SetPriority` directly call their Hajr counterparts with no error checking or fallback.
- **Severity:** **NICE-TO-HAVE**

---

## Networking (14 items)

### 21. QueryInterface returns NS_ERROR_NOT_IMPLEMENTED for all XPCOM objects
- **Locations:**
  - `src/wpe_glue/factory.rs:62` — `factory_query_interface` → NS_ERROR_NOT_IMPLEMENTED
  - `src/wpe_glue/factory.rs:149` — `proto_query_interface` → NS_ERROR_NOT_IMPLEMENTED
  - `src/wpe_glue/networking.rs:480` — `chan_query_interface` → NS_ERROR_NOT_IMPLEMENTED
- **Issue:** WPE's XPCOM relies on `QueryInterface` to negotiate interfaces. Returning NOT_IMPLEMENTED means WPE may not be able to use these objects correctly.
- **Severity:** **BLOCKER** — WPE may fail to interact with custom protocol/channel objects.

### 22. NewURI returns NS_ERROR_NOT_IMPLEMENTED and NULL
- **Location:** `src/wpe_glue/factory.rs:174-184`
- **Issue:** `proto_new_uri` returns `NS_ERROR_NOT_IMPLEMENTED` and sets the output URI to null. Comment says "WPE's URI parser will handle the rest" — this is speculative.
- **Severity:** **IMPORTANT** — may break URL resolution in WPE.

### 23. NewChannel uses placeholder URI passthrough
- **Location:** `src/wpe_glue/factory.rs:197-198`
- **Issue:** `proto_new_channel` sets `*out_channel = uri` — passes the URI pointer directly as the channel pointer. Comment says "placeholder". Proper implementation would build an nsIChannel with proper URI.
- **Severity:** **IMPORTANT**

### 24. nop handlers fill most of channel vtable
- **Location:** `src/wpe_glue/networking.rs:525-542,601-603`
- **Issue:** `suspend`, `resume`, `get_load_group`, `set_load_group`, `get_load_flags`, `set_load_flags`, `get_trr_mode`, `set_trr_mode`, `get_owner`, `set_owner`, `get_notif_callbacks`, `set_notif_callbacks`, `get_security_info`, `get_content_disp`, `set_content_disp`, `set_content_disp_fn`, `get_content_disp_fn` — all are nop (return NS_OK without doing anything).
- **Severity:** **IMPORTANT** — load groups, security info, content disposition, suspend/resume are non-functional.

### 25. Stream data-available passes NULL input stream
- **Location:** `src/wpe_glue/streaming.rs:286-287`
- **Issue:** `fire_on_data_available` passes `null_mut()` for the input stream parameter. Comment says "WPE will call nsIChannel::Open() to get a stream separately. In a full impl we'd pass the ZNetInputStream."
- **Severity:** **IMPORTANT** — WPE must work around this.

### 26. NS_ERROR_FAILURE as u32 conflicts with nsresult convention
- **Location:** `src/wpe_glue/streaming.rs:27,242`
- **Issue:** AGENTS.md specifies that FFI returning i32 should use nsresult constants (NS_OK=0, NS_ERROR_FAILURE=-2147467259). But `streaming.rs:27` defines `NS_ERROR_FAILURE: u32 = ns_result::NS_ERROR_FAILURE` which is cast incorrectly. C++ compares against -2 for failure.
- **Severity:** **IMPORTANT** — signals may mismatch between Rust/C++ boundaries.

### 27. HTTP/1.1 only — hardcoded GET requests
- **Location:** `src/wpe_glue/networking.rs:453-457`
- **Issue:** The networking layer only supports HTTP/1.1 GET requests with a hardcoded User-Agent string. No POST, PUT, DELETE, HEAD, or other methods. No HTTP/2 or HTTP/3 support despite z-net being designed for HTTP/3.
- **Severity:** **IMPORTANT**

### 28. No TLS/HTTPS support in channel creation
- **Location:** `src/wpe_glue/networking.rs:648-663`
- **Issue:** `parse_url()` strips `https://` prefix and assigns default port 443, but the actual connection is a plain TCP socket with no TLS handshake. z-net's TLS is not integrated.
- **Severity:** **BLOCKER** — HTTPS connections are sent in cleartext.

### 29. URL parser uses unwrap_or for path
- **Location:** `src/wpe_glue/networking.rs:656`
- **Issue:** `without_scheme.split('/').next().unwrap_or(without_scheme)` — if the URL is just `http://host` with no path, this returns the host as the host_part and then splits on `:` which could produce wrong results.
- **Severity:** **NICE-TO-HAVE**

### 30. CString::new with unwrap_or_default creates empty strings on NUL bytes
- **Location:** `src/wpe_glue/networking.rs:426-427`
- **Issue:** If the URL or host contains an embedded NUL byte, `CString::new()` returns Err, and `unwrap_or_default()` produces an empty CString. This could silently create corrupt requests.
- **Severity:** **NICE-TO-HAVE**

### 31. z-net: TLS verification, session cache, PAC engine incomplete
- **Location:** `dependencies/z-net/PLAN.md:108-123`
- **Issue:** The PLAN.md documents 10+ sites where `unreachable` needs to be propagated to errors, TLS session cache is a TODO no-op, PAC engine `isInNet` panics, and proxy discovery truncates data silently.
- **Severity:** **IMPORTANT**

### 32. z-net: unreachable → propagated errors (Phase 5)
- **Location:** `dependencies/z-net/PLAN.md:127-128`
- **Issue:** "10 sites across non-core code paths" with `unreachable` that should be proper errors.
- **Severity:** **IMPORTANT**

### 33. Network content-type and charset are hardcoded
- **Location:** `src/wpe_glue/networking.rs:582-593`
- **Issue:** `chan_get_content_type` always returns `"application/octet-stream"` and `chan_get_content_charset` always returns `"UTF-8"`, regardless of actual HTTP response headers.
- **Severity:** **IMPORTANT** — MIME type detection is broken.

### 34. Channel always reports as pending
- **Location:** `src/wpe_glue/networking.rs:505-509`
- **Issue:** `chan_is_pending` always sets `*pending = true`, even after the channel is closed or cancelled.
- **Severity:** **NICE-TO-HAVE**

---

## Storage (7 items)

### 35. clearData() uses placeholder origin (0,0)
- **Location:** `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp:188-194`
- **Issue:** `clearData()` explicitly comments "Using origin 0, 0 as a placeholder since we hash the key as origin above." This means clearing data for one origin may wipe data for all origins, or do nothing.
- **Severity:** **IMPORTANT** — data isolation between origins is broken.

### 36. Cookie path not stored
- **Location:** `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp:68`
- **Issue:** Comment says "Path is informational for domain matching; not stored separately yet." Cookie path scoping is ignored.
- **Severity:** **IMPORTANT** — cookie security model is incomplete.

### 37. Cookie domain override handled elsewhere
- **Location:** `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp:69-70`
- **Issue:** Comment says "Domain override handled elsewhere if needed" — but there's no code that handles it.
- **Severity:** **IMPORTANT**

### 38. DeleteBlob is a no-op
- **Location:** `src/wpe_glue/storage.rs:260-262`
- **Issue:** `Zawra_Storage_DeleteBlob` ignores all parameters and returns NS_OK. Comment says "BrowserDB's LSM tree uses tombstones; compaction physically removes it." But it never actually marks any tombstone.
- **Severity:** **IMPORTANT** — IndexedDB blobs can never be deleted.

### 39. Crash on BrowserDB not initialized
- **Location:** `src/wpe_glue/storage.rs:32`
- **Issue:** `GLOBAL_DB.get().expect("...")` will panic with a message if `Zawra_Storage_Init` was never called. This is across all storage operations.
- **Severity:** **IMPORTANT** — easy to trigger a panic.

### 40. Cookie/History/storage queries are O(n) — no index
- **Location:** `src/wpe_glue/storage.rs` (multiple functions: `Zawra_Cookie_Get` line 386, `Zawra_Cookie_GetForDomain` line 418, `Zawra_LocalStorage_Get` line 543, `Zawra_LocalStorage_GetAll` line 478)
- **Issue:** All these functions call `get_all()` and iterate through ALL entries. For a browser with thousands of cookies/history entries, this will be extremely slow.
- **Severity:** **IMPORTANT**

### 41. Old Crypto API (Encrypt/Decrypt) always fails
- **Location:** `src/wpe_glue/crypto.rs:186-213`
- **Issue:** `Zawra_Crypto_Encrypt()` and `Zawra_Crypto_Decrypt()` take algorithm parameters but always return `NS_ERROR_FAILURE`. Only the GCM-specific variants (`Zawra_Crypto_Encrypt_GCM`, `Zawra_Crypto_Decrypt_GCM`) work.
- **Severity:** **NICE-TO-HAVE**

---

## Rust Safety / Panic Risk (8 items)

### 42. thread::spawn().expect() can crash on spawn failure
- **Locations:** `src/wpe_glue/streaming.rs:144` and `src/wpe_glue/networking.rs:83`
- **Issue:** `expect("failed to spawn zawra-async-reader thread")` and `expect("failed to spawn zawra-net-poll thread")` will panic if the OS cannot create a thread (e.g., resource exhaustion). The spawned threads are critical for networking.
- **Severity:** **IMPORTANT**

### 43. CString::new().unwrap() can panic on interior NUL
- **Location:** `src/wpe_glue/launcher.rs:179-182`
- **Issue:** `CString::new("--profile").unwrap()` and `CString::new(profile_path).unwrap()` and `CString::new("zawra-browser").unwrap()` — while these are unlikely to have NUL bytes, `profile_path` is user-controlled and could theoretically contain one.
- **Severity:** **NICE-TO-HAVE**

### 44. duration_since(UNIX_EPOCH).unwrap() can panic
- **Location:** `src/wpe_glue/storage.rs:289`
- **Issue:** If the system clock is set before the UNIX epoch (year 1970 or earlier), `SystemTime::now().duration_since(SystemTime::UNIX_EPOCH)` will return Err and the `unwrap()` will panic.
- **Severity:** **NICE-TO-HAVE**

### 45. global_engine() crash on null
- **Location:** `src/wpe_glue/networking.rs:92`
- **Issue:** `.expect("z-net engine not initialised – call Zawra_Init_Subsystems first")` — panics if networking functions are called before initialization.
- **Severity:** **IMPORTANT**

### 46. Window/GTK stubs always return null
- **Locations:** `src/ui/window.rs:100`, `src/ui/renderer.rs:48`
- **Issue:** Native window handles are null, `web_browser` is null. Any code path that dereferences these will cause UB/segfault.
- **Severity:** **IMPORTANT** — UB risk.

### 47. lib.rs contains empty mock modules
- **Location:** `src/lib.rs:24-131`
- **Issue:** `javascriptcore::jsapi::JS_NewExternalArrayBuffer` always returns null. `net_traits::request::Request::url()` returns empty string. `tokio::sync::oneshot::channel()` returns phantom channels. `storage_traits::indexeddb` types are stubs. These are mock implementations that don't function.
- **Severity:** **IMPORTANT** — any code using these will silently fail.

### 48. Many unsafe blocks without safety documentation
- **Location:** Throughout `src/wpe_glue/networking.rs` (40+ unsafe blocks), `streaming.rs`, `storage.rs`
- **Issue:** A large number of `unsafe` blocks lack clear safety invariants. For example, `ZNetChannel::from_ptr` just casts a raw pointer — if the pointer is dangling or wrong type, it's UB.
- **Severity:** **IMPORTANT** — maintenance hazard.

---

## Other — Build / Scripts / Docs / Platform (13 items)

### 49. JavaScriptCore_INSTALLED_HEADERS expands to nothing
- **Location:** `patches/webkit/Source/WebKit/PlatformWPE.cmake:573`
- **Issue:** XXX comment: "Using ${JavaScriptCore_INSTALLED_HEADERS} here expands to nothing." This likely breaks the build for JavaScript-dependent features.
- **Severity:** **BLOCKER** — build break for JSC integration.

### 50. Fake API headers target
- **Location:** `patches/webkit/Source/WebKit/PlatformWPE.cmake:251`
- **Issue:** `webkitwpe-fake-api-headers` target exists — suggests the real API headers are not connected, only fake/placeholder ones.
- **Severity:** **IMPORTANT**

### 51. Crypto: Only AES-GCM works; AES-CBC, AES-CTR not implemented
- **Location:** `src/wpe_glue/crypto.rs:10-15,29-32`
- **Issue:** `CryptoAlgo` enum defines `AesCbc=0`, `AesCtr=1`, `AesGcm=2`, `Sha256=3`, `Sha512=4` but the dispatch only handles SHA-256 (3) and SHA-512 (4). AES modes return NS_ERROR_FAILURE.
- **Severity:** **IMPORTANT**

### 52. Crypto: OneNonce panics on second use
- **Location:** `src/wpe_glue/crypto.rs:41-47`
- **Issue:** `OneNonce::advance()` calls `self.0.take().ok_or(...)` — the first call succeeds, but any second call returns `Err(ring::error::Unspecified)`. If the sealing/opening key is reused, the encrypt/decrypt will fail silently.
- **Severity:** **IMPORTANT**

### 53. No PLAN.md at project root
- **Location:** (missing) `PLAN.md`
- **Issue:** AGENTS.md references `PLAN.md` for planned features, but the file does not exist at the project root. Project planning documentation is missing.
- **Severity:** **NICE-TO-HAVE**

### 54. Shutdown is a no-op
- **Location:** `src/wpe_glue/init.rs:74-76`
- **Issue:** `Zawra_Shutdown_Subsystems()` only prints a message. No actual cleanup of z-net engine, BrowserDB, or Hajr resources occurs.
- **Severity:** **IMPORTANT** — resource leak on every browser restart.

### 55. NetworkStorageSessionSoup.cpp has multiple RELEASE_ASSERT_NOT_REACHED paths
- **Location:** `patches/webkit/Source/WebCore/platform/network/soup/NetworkStorageSessionSoup.cpp:111,139,297`
- **Issue:** Several functions have `RELEASE_ASSERT_NOT_REACHED()` which will crash in release builds if called. The patched session is fundamentally incomplete for WPE's soup networking.
- **Severity:** **IMPORTANT**

### 56. Cookie Store API FIXMEs
- **Locations:** `patches/webkit/Source/WebCore/platform/network/soup/NetworkStorageSessionSoup.cpp:406,688`
- **Issue:** "FIXME: Implement for the Cookie Store API." Two locations needing implementation.
- **Severity:** **NICE-TO-HAVE**

### 57. WPE library search is hardcoded to specific paths
- **Location:** `src/wpe_glue/launcher.rs:104-114`
- **Issue:** `find_wpe_lib()` checks 4 hardcoded paths. No support for `WPE_PATH` env var (despite the error message mentioning it). No recursive search or ldconfig-based lookup.
- **Severity:** **NICE-TO-HAVE**

### 58. wpe_main placeholder
- **Location:** `src/wpe_glue/launcher.rs:171-172`
- **Issue:** If `wpe_main` symbol is not found in the WPE library, the launcher returns 0 (success) silently. Should return an error.
- **Severity:** **NICE-TO-HAVE**

### 59. Debug fprintf spam in upstream WebKit patches
- **Locations:** Multiple patches including `ProcessThrottler.h:97,102`, `ProcessThrottler.cpp:66,68`, `WebProcessProxy.cpp:306,326,365`, `BackgroundProcessResponsivenessTimer.cpp:49`, `AuxiliaryProcessProxy.cpp:61,71`
- **Issue:** Numerous `[ZAWRA-DEBUG]` fprintf statements left in production code paths. These spam stderr on every process creation/destruction.
- **Severity:** **NICE-TO-HAVE**

### 60. Page.cpp has many upstream FIXMEs
- **Location:** `patches/webkit/Source/WebCore/page/Page.cpp`
- **Issue:** 20+ FIXMEs in the patched Page.cpp covering: fullscreen steps, post-animation frame callbacks, visibility state, media playback suspension, service worker worlds, etc. These are downstream patches that carry upstream technical debt.
- **Severity:** **NICE-TO-HAVE**

### 61. SQLiteStorageArea returns empty optionals on ASSERT_NOT_REACHED
- **Location:** `patches/webkit/Source/WebKit/NetworkProcess/storage/SQLiteStorageArea.cpp:63,206,247,293`
- **Issue:** Functions hit `ASSERT_NOT_REACHED()` and return empty `{ }` — in release builds this silently returns invalid/uninitialized data.
- **Severity:** **IMPORTANT**

### 62. Headless network stack test mode has no diagnostic server
- **Location:** `src/wpe_glue/launcher.rs:10-12`
- **Issue:** Documentation says "expose a diagnostic HTTP server so the network stack can be tested in isolation" but no such server is implemented. The headless path just returns 0.
- **Severity:** **NICE-TO-HAVE**

---

## Summary

| Category | Count |
|---|---|
| Graphics / Rendering | 13 |
| IPC / Sandbox | 7 |
| Networking | 14 |
| Storage | 7 |
| Rust Safety / Panic Risk | 8 |
| Other (Build, Scripts, Docs, Platform) | 13 |
| **Total** | **62** |

### Top 3 Most Important Issues

1. **Full GLContext/EGL stub (items 1-3)** — The entire EGL context management, DMA-BUF import, and window sizing are stubs. WebKit's compositor cannot produce rendered output. This is the most critical blocker for a functional browser.

2. **Hajr memory allocator uses libc malloc (item 14)** — The core value proposition of Hajr (hardware-enforced memory isolation via MPK/MTE) is completely bypassed. `Zawra_Hajr_MemAlloc` falls through to `libc::malloc`, providing no security benefit.

3. **Network `QueryInterface` returns `NS_ERROR_NOT_IMPLEMENTED` (item 21)** — WPE's XPCOM framework relies on QueryInterface to discover object capabilities. All three custom objects (factory, protocol handler, channel) return NOT_IMPLEMENTED, which means WPE may be unable to properly interact with the custom networking stack. Combined with the `proto_new_channel` placeholder that passes the URI pointer as the channel pointer, the networking override layer is fundamentally incomplete.

### Report File
This file: `/home/Intro/spectre-enviroment/ZAWRA-BROWSER/zawra-browser/experiments/missing-features.md`
