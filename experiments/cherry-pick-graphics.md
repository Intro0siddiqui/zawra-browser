# Cherry-Pick Analysis: `feat/graphics-ipc-integration` → `development`

**Commit**: `62f7e2fe` — "feat: implement sandboxed graphics memory sharing IPC pipeline"
**Base**: `5be6be6d` (shared with `development`)
**`development` ahead by**: 3 commits (timer fiddles, PageClientImpl debug logging, snapshot)

## Executive Summary

**Recommendation: SKIP the entire branch. Delete it.**

The branch contains 3 categories of change:
1. **Massive rollback/downgrade** of the WebKit2 UIProcess layer — deletes 5 upstream patch files (`WebProcessProxy.cpp`, `AuxiliaryProcessProxy.cpp`, `BackgroundProcessResponsivenessTimer.cpp`, `ProcessThrottler.{cpp,h}`) and adds raw upstream copies of 4 more (`PageClient.h`, `WebPageProxy.{cpp,h,messages.in}`). This is not a cherry-pick; it's a different upstream baseline.
2. **Reverts of established `development` patterns** — removes `Zawra_LocalStorage_GetAll`, removes `Zawra_History_Increment`, simplifies the ZawraGraphicsBridge back to an older API, strips cookie parsing, removes `#include "ProcessExecutablePath.h"`, removes `SharedMemory` includes, deletes socket/process-message helpers in `ConnectionUnix.cpp`.
3. **Legitimate improvements** — `unsafe` wrapping of FFI calls in Rust, `#[allow(dead_code)]` cleanup, `WouldBlock` handling in `NetworkDataTaskZNet`, non-`atomic` state in `ZNet` (single-threaded is correct), the `BrowserDBStorageArea.cpp` source entry, and the `hajr_seal_process()` signature change.

The improvements in category 3 are real, but they are **entangled** with the regressions in categories 1-2 in the same commit. You cannot cherry-pick them independently without also pulling in the destructive changes.

Below is the file-by-file analysis.

---

## File-by-File Breakdown

### 🟢 FILES THAT COULD BE CHERRY-PICKED (individually safe)

| File | Change | Why Safe | Already on `development`? |
|------|--------|----------|---------------------------|
| `src/wpe_glue/init.rs:83-86` | `unsafe extern "C"` → `extern "C"` for hajr FFI decls | Corrects Rust-2024 extern block syntax. Pure hygiene. | No — `development` still has `unsafe extern "C"` |
| `src/wpe_glue/launcher.rs:31-32` | `app_data` → `appData` param rename + `Command`/`CommandExt` imports | Cosmetic rename + unused imports added (neither `Command` nor `CommandExt` are actually used in the diff). Harmless but moot. | No — but the rename `app_data` → `appData` changes nothing semantically |
| `src/wpe_glue/networking.rs` | Wraps all `lean_net` FFI calls in `unsafe { }` blocks | This is a correctness fix for Rust-2024 (unsafe operations must be in `unsafe` blocks). | No — `development` lacks these `unsafe` wrappers |
| `src/wpe_glue/networking.rs:150` | Moves `net_body_ring_unregister` before `is_closed` store | Fixes a subtle ordering bug (ring unregister should happen while descriptor is still valid). | No — `development` has the old order |
| `patches/webkit/Source/WebKit/NetworkProcess/znet/NetworkDataTaskZNet.cpp` | Removes `std::memory_order` atomics, adds `WouldBlock` (-5) handling in write/read loops | Correct: ZNet worker is single-threaded, atomics were cargo-cult. `WouldBlock` handling prevents tight-loop spinning. | No — `development` has the atomic version without `WouldBlock` |
| `patches/webkit/Source/WebKit/NetworkProcess/znet/NetworkDataTaskZNet.h` | `std::atomic<State>` → `State`; `std::atomic<bool>` → `bool` | Correct: single-threaded worker doesn't need atomics. | No — `development` has atomics |
| `src/wpe_glue/streaming.rs` | Adds `NS_BASE_STREAM_WOULD_BLOCK` constant, `net_read` import, `ZNetChannel`/`ZNetInputStream`/`global_engine` imports | Enables non-blocking stream reads. | No — `development` lacks these imports |
| `src/wpe_glue/factory.rs` | Removes `#[allow(dead_code)]` from all FFI vtable functions/statics | Cleanup — these are used through the vtable pointer, not by name. | No — `development` still has the suppression |
| `src/ui/renderer.rs`, `src/ui/tabs.rs` | Removes `#[allow(dead_code)]` from `web_browser`, `parent_window`, `content_proc` fields | Cleanup — these fields are now used. | No — `development` has the suppression |
| `src/lib.rs` | Removes `#[allow(non_snake_case)]` | Cleanup. | No — `development` has the suppression |
| `src/zero_copy.rs` | Adds `use std::ptr;` + doc-comment fix | Trivial hygiene. | No |
| `src/wpe_glue/storage.rs` (parts) | Simplifies `Zawra_Cache_Get`/`Zawra_Storage_GetBlob` — removes unnecessary re-alloc into cap==len box via memcpy, uses `entry.body.into_boxed_slice()` directly | The original comment's concern about allocator Layout mismatch was incorrect. `into_boxed_slice()` preserves the exact allocation; `Vec::from_raw_parts(ptr, len, len)` in `Zawra_Free_Buffer` will get the correct Layout. | No — `development` has the conservative (but slower) double-copy version |
| `src/wpe_glue/storage.rs` | `Zawra_Free_Buffer`: `Box::from_raw(slice)` → `Vec::from_raw_parts(ptr, len, len)` | Matches the new allocation strategy. | No — `development` uses `Box::from_raw` |
| `test_child.zig` | New Zig test file | Tiny, standalone Zig test. Harmless. | No |
| `thermal_build_control.sh` | New shell script | New utility for thermal-aware builds. Useful. | No |
| `thermal_release.sh` | New shell script | Same as above, release variant. Useful. | No |

### 🔴 FILES TO SKIP — destructive or already handled differently

| File | Change | Reason to Skip |
|------|--------|----------------|
| `patches/webkit/Source/WebKit/UIProcess/WebProcessProxy.cpp` | **DELETES** 2587 lines of patched WebProcessProxy | This reverts a ton of WebKit2 functionality (notification handling, badge support, service worker tracking, logging, permission changes). On `development`, this file is present as a patch. Deletion would break the build. |
| `patches/webkit/Source/WebKit/UIProcess/AuxiliaryProcessProxy.cpp` | **DELETES** 520 lines | Same — removes all auxiliary process management patching. |
| `patches/webkit/Source/WebKit/UIProcess/BackgroundProcessResponsivenessTimer.cpp` | **DELETES** 176 lines | Removes background timer patching. |
| `patches/webkit/Source/WebKit/UIProcess/ProcessThrottler.cpp` | **DELETES** 513 lines | Removes process throttling patching. |
| `patches/webkit/Source/WebKit/UIProcess/ProcessThrottler.h` | **DELETES** 241 lines | Removes throttler header patching. |
| `patches/webkit/Source/WebKit/UIProcess/PageClient.h` | **ADDS** 687 lines (upstream WPE file) | `development` doesn't have this file as a patch. Adding it would override upstream with an older/baseline copy. |
| `patches/webkit/Source/WebKit/UIProcess/WebPageProxy.cpp` | **ADDS** 12897 lines (upstream WPE file) | Same — massive upstream baseline file, not a Zawra-adapted patch. Would override whatever `development` relies on. |
| `patches/webkit/Source/WebKit/UIProcess/WebPageProxy.h` | **ADDS** 3326 lines | Same issue. |
| `patches/webkit/Source/WebKit/UIProcess/WebPageProxy.messages.in` | **ADDS** 640 lines | Same issue. |
| `patches/webkit/Source/WebKit/UIProcess/API/wpe/PageClientImpl.h` | **ADDS** 170 lines (full `PageClient` declaration) | Not on `development`. Without the rest of the page client refactor, this header may have missing dependencies. |
| `patches/webkit/zawra_graphics_integration.patch` | **ADDS** 116-line unified diff file | This is a *patch-of-a-patch* — it contains the old/deprecated `ZawraGraphics.h`, `ZawraGraphicsBridge.{cpp,h}` from an earlier API. `development` already has these files as individual patches *with a different API* (e.g., `initialize(void*,int,int)` vs constructor-init). This patch would NOT apply cleanly to the WebKit source. |
| `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraGraphicsBridge.cpp` | Removes singleton pattern (`~ZawraGraphicsBridge()`, `singleton()` static), adds callback on `initialize()` | This changes the API from `ZawraGraphicsBridge::singleton().exportCompositorFD()` to `ZawraGraphicsBridge::exportCompositorFD()`. `development` still uses the singleton. Cherry-picking this alone would break callers (`TextureMapperGL.cpp`, `PageClientImpl.cpp` use `singleton()`). |
| `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraGraphicsBridge.h` | Removes `NeverDestroyed` include, removes destructor, adds `FDExportCallback` | Tied to the .cpp changes above. |
| `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp` | `ZawraGraphicsBridge::singleton()....()` → `ZawraGraphicsBridge::...()`, removes `#include <unistd.h>`, removes `close(fd)` | Dependent on the graphics bridge API change. Remove `close(fd)` without replacing it could leak FDs. |
| `patches/webkit/Source/WebKit/UIProcess/API/wpe/PageClientImpl.cpp` | Removes destructor debug logging, `singleton().exportCompositorFD()` → `exportCompositorFD()` | Removing debug logging is actually fine, but the `singleton()` change depends on the graphics bridge API change. Cherry-pick only the logging removal if desired. |
| `patches/webkit/Source/WebCore/platform/network/zawra/ZawraStorageBridge.cpp` | **Drastic simplification** — removes all cookie attribute parsing (expiry, flags, SameSite, Secure, HttpOnly), calls `Zawra_Cookie_Put` with hardcoded 0,0 for expiry/flags. Removes `Zawra_History_Increment` extern. | This is a **functionality regression**. `development` has proper cookie parsing. Cherry-picking this would destroy cookie expiry/security-policy handling. |
| `src/wpe_glue/storage.rs` (removed functions) | **DELETES** `Zawra_LocalStorage_GetAll` and `Zawra_History_Increment` | These functions exist on `development` and the corresponding C++ bridge expects them. Removing them will cause linker errors in the `ZawraStorageBridge`. |
| `patches/webkit/Source/WebKit/Platform/IPC/unix/ConnectionUnix.cpp` | Massive rewrite: removes `readBytesFromSocket()`, `processMessage()`, `createPlatformConnection()`, `createConnectionIdentifierPair()`, removes `SharedMemory` include, removes `SOCK_SEQPACKET`/`SOCK_DGRAM` fallback, removes `hajr_ring_get_signal_fd`, removes `MSG_NOSIGNAL` — replaces with stubs | This is a **massive IPC layer simplification** that removes the standard Unix socket-based IPC fallback and the out-of-line memory message path. On `development`, these are functional. Cherry-picking would break IPC. Note: Hajr ring-buffer IPC is preserved. |
| `patches/webkit/Source/WebKit/Platform/IPC/Connection.h` | Adds `m_inboundMem`, `m_outboundMem`, `m_pendingRingMessages`, `m_ringBatchSize` fields; removes `m_hajrSignalSocket` | Depends on the ConnectionUnix.cpp changes. |
| `patches/webkit/Source/WebKit/PlatformWPE.cmake` | Changes library paths from `target/release/*` to `dependencies/*` | `development` uses the unified workspace (`target/release/`). Changing to `dependencies/` paths assumes a different build layout. |
| `patches/webkit/Source/WebCore/PlatformWPE.cmake` | Removes `vulkan` and `X11` link dependencies | On `development`, Vulkan/X11 are linked for the RHI. Removing them would break the graphics link. Adds `ZawraGraphicsBridge.cpp` sources list inside `USE_ATSPI` guard (seems wrong — graphics bridge isn't ATSPI-related). |
| `patches/webkit/Source/WebCore/SourcesWPE.txt` | Removes `ZawraStorageBridge.cpp` from source list, adds blank line | Removing `ZawraStorageBridge.cpp` from the build would cause linker errors. |
| `patches/webkit/Source/WebKit/NetworkProcess/storage/LocalStorageManager.cpp` | `makeUnique<SQLiteStorageArea>(...)` → `BrowserDBStorageArea::create(...)` | On `development`, this already uses `SQLiteStorageArea`. The `BrowserDBStorageArea` class doesn't exist in the `development` patch set (only its `.cpp` is listed in `Sources.txt` on the branch). |
| `src/wpe_glue/zero_copy_bridge.rs` | `Box::from_raw(slice).into_vec()` → `Vec::from_raw_parts(out_ptr, out_len, out_len)` | This matches the `Zawra_Free_Buffer` allocation change. Safe if done together, but the consumer (`create_zero_copy_buffer`) takes `Vec<u8>` by value, so `into_vec()` was already correct. |
| `patches/webkit/Source/WebKit/NetworkProcess/soup/NetworkDataTaskSoup.h` | Removes `SoupMessage` and `SoupMultipartInputStream` members | These are still used by the soup-based fallback on `development`. Removing them would break the soup path. |
| `patches/webkit/Source/WebKit/UIProcess/Launcher/glib/ProcessLauncherGLib.cpp` | Removes `#include "ProcessExecutablePath.h"` + `terminateProcess()` + `platformInvalidate()` | Removes process termination logic. `development` has functional `terminateProcess()` with proper sandbox-aware kill paths. |
| `patches/webkit/Source/WebKit/GPUProcess/glib/GPUProcessMainGLib.cpp` | `hajr_seal_process(HAJR_GPU_PROCESS)` → `hajr_seal_process()` | Changes the hajr FFI signature. Safe in isolation IF the hajr library matches, but `development` still passes the process type. |
| `patches/webkit/Source/WebKit/NetworkProcess/soup/NetworkProcessMainSoup.cpp` | `hajr_seal_process(HAJR_NETWORK_PROCESS)` → `hajr_seal_process()` | Same as above. |
| `patches/webkit/Source/WebKit/WebProcess/wpe/WebProcessMainWPE.cpp` | `hajr_seal_process(HAJR_WEB_PROCESS)` → `hajr_seal_process()` | Same as above. |
| `.gitignore` | Complete restructure — removes comments, changes patterns from `/target/` to `/target`, adds `webkit/source/`, `webkit/build/` | The branch's `.gitignore` is more complete (adds `webkit/build/` and `webkit/source/` which are correct). But the `development` `.gitignore` ignores `/webkit/` entirely which subsumes those. The branch version also removes proper blocking of `/target/` and `/zig-out/`. |
| `AGENTS.md` | Removes `zw` tool documentation, changes build instructions | The `zw` knowledge graph tool documentation was deleted (it exists on `development`). The build instructions were changed to reference `./thermal_build_control.sh` with individual submodule compiles instead of the unified workspace. This is a regression in documentation quality. |
| `Cargo.lock` | Massive diff — removes 3000+ lines of dependency entries | This is a different dependency resolution (perhaps from an older `cargo` or a different set of dependencies). It drops `criterion`, `tempfile`, `anyhow`, `bindgen`, `chrono`, and many others. Would break benchmarks and build tooling. |
| `Cargo.toml` | 9 lines removed (not shown in detail, but net negative) | Likely removes dependencies. Not safe to cherry-pick without understanding what was removed. |
| `PLAN.md` | New file — development plan document | Harmless new file, useful documentation. Could cherry-pick. |
| `old.cmake` | New file — 455 lines of CMake macros from WebKit | This is a fragment of the upstream `WebKitCommon.cmake` macros. Not used by the build system directly. Could be useful reference but not necessary. |
| `build.rs` | Changed — see full content in diff | Minor changes to the build script. Need closer analysis vs `development` version. |
| `tools/setup/src/main.rs` | **Major rewrite** — removes `copy_newer()` mtime-aware copy, removes project_root resolution, removes sentinel check, removes compile_commands.json symlink | This is a **regression**. The `development` version has a sophisticated `copy_newer` function that preserves `.o` timestamps to avoid unnecessary rebuilds. The branch version reverts to a simple `fs_extra::dir::copy` which overwrites unconditionally, destroying incremental build state. |
| `test_child`, `test_posix` | Binary files | Committed binaries. Should never be committed. |
