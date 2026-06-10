# Branch Analysis

## feat/graphics-ipc-integration

**Commit count (unique vs `development`):** 1

**Commit:** `62f7e2fe` — `feat: implement sandboxed graphics memory sharing IPC pipeline`

**Analysis date:** 2026-06-10

### What the branch implements

A refactored graphics IPC pipeline with three main themes:

1. **Graphics Bridge refactor** — `ZawraGraphicsBridge` is changed from a `NeverDestroyed` singleton pattern to a callback-based design. Methods `singleton()`, `exportCompositorFD()`, and `presentFrame()` are called statically instead of through `singleton()`. An `FDExportCallback` is added and invoked when the compositor FD is exported. The destructor body (which called `ZawraGraphics_DestroySurface`) was removed since the surface lifecycle is now managed externally.

2. **Patch reorganization** — Several patch files were deleted from `patches/webkit/` (e.g., `WebProcessProxy.cpp`, `AuxiliaryProcessProxy.cpp`, `BackgroundProcessResponsivenessTimer.cpp`, `ProcessThrottler.cpp/.h`) that had been patches on `development`. New patch files were added that were previously only in the untracked WebKit source tree (`WebPageProxy.cpp`, `WebPageProxy.h`, `WebPageProxy.messages.in`, `PageClient.h`, `PageClientImpl.h`, `AcceleratedSurfaceLibWPE.cpp`). This effectively moves those files into the patch overlay system.

3. **IPC & Storage improvements** — Hajr ring buffer integration was enhanced in `ConnectionUnix.cpp` with batched message flushing. `LocalStorageManager` was patched to use `BrowserDBStorageArea` instead of `SQLiteStorageArea`. Connection cleanup was improved (empty socket set types, signal on shutdown). The `zawra_graphics_integration.patch` was added (a legacy patch for the old graphics API surface).

4. **Rust-side cleanup** — Removed `#[allow(dead_code)]` annotations, changed `unsafe extern "C"` to `extern "C"` throughout, removed the `Zawra_LocalStorage_GetAll` function, fixed zero-copy buffer allocation to use `Vec::from_raw_parts` instead of `Box::from_raw`. Removed the workspace section from `Cargo.toml`. Simplified `build.rs`.

5. **Artifacts added** — `PLAN.md`, `old.cmake`, `test_child`/`test_child.zig`/`test_posix`, `thermal_build_control.sh`, `thermal_release.sh`.

### Is this code already on `development`?

**No.** The graphics bridge on `development` still uses the old singleton pattern with `NeverDestroyed` and `~ZawraGraphicsBridge()`. The `BrowserDBStorageArea` usage is not present. The patch reorganization (deleting/adding patch files) is unique. The Rust workspace removal and `build.rs` simplification are not on `development`.

However, the `development` branch has its own `feat/graphics-pipeline-complete` merged, which shares the overall goal of graphics pipeline integration but takes a different approach (keeping the singleton pattern, different IPC changes).

### Would merging it break anything?

**Yes, almost certainly.** Several red flags:

- **Cargo.toml workspace removal** — The branch removes `[workspace]` entirely, which would break the Cargo workspace resolution for `tools/setup`, `z-net/engine`, `Browser-db/bindings`, and `fuzz`. These would no longer be compilable via `cargo build --release` from the root.

- **Graphics bridge ABI change** — Making `~ZawraGraphicsBridge() = default` removes the `ZawraGraphics_DestroySurface` cleanup call, which would leak GPU surface memory. The singleton pattern removal changes the initialization contract — all callers would need updating.

- **Patch deletion/creation mismatch** — Deleting patches like `WebProcessProxy.cpp` from `patches/webkit/` means the `zawra-setup` tool would no longer apply those patches to the WebKit source. If the upstream `webkit/source/` tree still needs those modifications, the build would fail. Conversely, adding huge upstream files like `WebPageProxy.cpp` (13K lines) as patch files would overwrite the extracted upstream version entirely — this is not normal patch workflow and suggests the files were accidentally or prematurely copied into patches.

- **`hajr_seal_process` signature change** — `NetworkProcessMainSoup.cpp` changes `hajr_seal_process(unsigned int)` to `hajr_seal_process()` (no argument), which would be a link error if Hajr expects the typed version.

- **`BrowserDBStorageArea.h` include** — The `LocalStorageManager.cpp` patch includes `BrowserDBStorageArea.h` which may not exist as a patch and may not be in the WebKit source tree, causing a compile error.

### Recommendation: **Delete**

The branch represents an exploratory refactor that was abandoned mid-way. The graphics bridge changes are superseded by the approach on `development` (`feat/graphics-pipeline-complete`). The patch reorganization is dangerous (deleting needed patches while adding raw upstream files). The `Cargo.toml` workspace removal breaks the build. The ABI/API changes are incompatible with the rest of the codebase.

If any specific changes from this branch are needed (e.g., the `BrowserDBStorageArea` integration), they should be cherry-picked individually into a proper feature branch based on `development`.

## fix/integration-final

**Commit count (unique vs `development`):** 11

**Commits (chronological):**

| # | Commit | Message | Scope |
|---|--------|---------|-------|
| 1 | `fc3e8d94` | chore(portability): finalize macOS M2 fallbacks for Pure Ring IPC | Hajr submodule |
| 2 | `54e4225b` | fix(hajr): finalize stability fixes for IPC and isolation | Hajr submodule |
| 3 | `b8fc9ea5` | ci: enable workflows for fix/integration-final | CI config |
| 4 | `f78df15c` | fix(hajr): sync with submodule portability fixes | Hajr submodule |
| 5 | `c9380a5b` | fix(hajr): final portability synchronization | Hajr submodule |
| 6 | `68e4987e` | fix(hajr): finalize CI-compatible portability fixes | Hajr submodule |
| 7 | `b31ae274` | fix(hajr): unwrap optional child.id synchronization | Hajr submodule |
| 8 | `85e06a46` | fix(hajr): finalize CI-compatible portability synchronization | Hajr submodule |
| 9 | `89bfd4dd` | fix(hajr): sync with submodule Windows portability fixes | Hajr submodule |
| 10 | `46bab772` | fix(rust): address lint warnings for wpe_glue/init.rs | Rust source |
| 11 | `6892d012` | chore(rust): address remaining unused imports and formatting warnings | Rust + patches + infra |

**Merge base with `development`:** `6d90bc4a` — `chore: update hajr submodule pointer to include pure ring IPC and isolation`

**Hajr submodule delta:** `508fafef` → `df044538` (upstream diff: `fix(windows): guard mmap/lseek behind OS check` → `fix(portability): resolve Windows handle and PID type issues`)

---

### What the branch does

This branch is a **consolidation/simplification pass** over the codebase with three categories of change:

#### 1. Hajr submodule synchronisation (7 commits)
Iterative submodule pointer bumps to pull in upstream Hajr portability fixes (Windows handle types, PID types, macOS M2 fallbacks, CI compatibility). The 7 commits essentially converge on the same target `df044538` through trial-and-error.

#### 2. Rust lint & safety fixes (2 commits: `46bab772`, `6892d012`)
- Removes all `#[allow(dead_code)]` annotations from factory.rs, renderer.rs, tabs.rs, init.rs, zero_copy.rs
- Changes `unsafe extern "C"` → `extern "C"` in `wpe_glue/init.rs` and `wpe_glue/launcher.rs`
- Wraps raw FFI calls in `unsafe { }` blocks in `networking.rs` (`net_poll`, `net_write`, `net_read`, `net_close`, `net_connect`, `net_engine_create`, `net_body_ring_register`, `net_body_ring_unregister`)
- **Critical fix**: Changes `Zawra_Free_Buffer` from `Box::from_raw(slice)` back to `Vec::from_raw_parts(ptr, len, len)` — this fixes an allocator Layout mismatch that would cause heap corruption
- Removes dead functions `Zawra_LocalStorage_GetAll` and `Zawra_History_Increment` from `storage.rs`
- Adds missing imports (`CString`, `c_char`, `CStr`, `NetError`, `net_read`, `net_engine_destroy`, `Command`, `CommandExt`, etc.)
- Moves `net_body_ring_unregister` before `is_closed` store in `OwnedBodyRing::drop` (ordering fix)
- Adds `NS_BASE_STREAM_WOULD_BLOCK` constant to `streaming.rs`

#### 3. WebKit patch simplification (in `6892d012`)
- **`ConnectionUnix.cpp`**: Removed checksum verification (`hajr_ipc_message_checksum`, `hajr_ipc_verify_checksum`), removed `hajr_ring_get_signal_fd`, removed `readBytesFromSocket` and `processMessage()`, removed `createPlatformConnection`, removed `platformPrepareForOpen`. Added batched ring signalling (`m_pendingRingMessages` / `m_ringBatchSize`). Simplified attachment fd handling.
- **`Connection.h`**: Added `m_inboundMem`, `m_outboundMem`, `m_pendingRingMessages`, `m_ringBatchSize`, `m_hajrRings` fields. Removed `m_hajrSignalSocket`.
- **`ZawraGraphicsBridge`**: Removed singleton pattern and `NeverDestroyed`. Made methods static. Removed `~ZawraGraphicsBridge()` destructor body. Removed `ZawraGraphics_DestroySurface` call.
- **`TextureMapperGL.cpp`**: Uses static calls instead of `singleton()`. Removed `close(fd)`.
- **`PageClientImpl.cpp`**: Removed debug logging in destructor. Uses static `ZawraGraphicsBridge::exportCompositorFD()`.
- **`ProcessLauncherGLib.cpp`**: Removed `terminateProcess()` and `platformInvalidate()`.
- **`WebProcessProxy.cpp`, `AuxiliaryProcessProxy.cpp`, `ProcessThrottler.cpp/.h`, `BackgroundProcessResponsivenessTimer.cpp`**: Entire files deleted from patches (massive simplification — removes process throttling, responsiveness tracking, web process cache logic, service worker context management, speech recognition, etc.).
- **`NetworkDataTaskZNet`**: Removed `std::atomic<State>` and `std::atomic<bool>` — reverted to plain members (reintroduces data races). Added `WouldBlock` (-5) handling with `net_poll` for both read and write loops.
- **`hajr_seal_process`**: Changed signature from `hajr_seal_process(unsigned int)` to `hajr_seal_process()` across `GPUProcessMainGLib.cpp`, `NetworkProcessMainSoup.cpp`, `WebProcessMainWPE.cpp`.
- **`ZawraStorageBridge.cpp`**: Removed cookie expiry/flags parsing, stubbed `incrementHistoryVisit`.
- **`LocalStorageManager.cpp`**: Changed from `SQLiteStorageArea` to `BrowserDBStorageArea`.
- **Library paths**: Changed from `target/release/` to `dependencies/*/target/release/` in `PlatformWPE.cmake`.
- **`PlatformWPE.cmake` (WebCore)**: Removed `vulkan` and `X11` library deps, added `ZawraGraphicsBridge.cpp` to sources under ATSPI guard.
- **`SourcesWPE.txt`**: Moved `ZawraStorageBridge.cpp` out of sources, added blank line.
- **`zawra_graphics_integration.patch`**: New patch file (alternative graphics API surface using singleton + `ZawraGraphics_Initialize`).

#### 4. Infrastructure changes (same commit `6892d012`)
- **`.gitignore`**: Completely rewritten — simpler entries, removes `webkit/` and `zig-out` ignores, adds `webkit/source/` and `webkit/build/`.
- **`Cargo.toml`**: Removed entire `[workspace]` section (breaks unified workspace builds).
- **`build.rs`**: Removed `cargo::rustc-check-cfg`, cleaned up unused `PathBuf` import.
- **`AGENTS.md`**: Removed the entire "Project Intelligence" section (zw tool documentation), simplified build instructions (removed `cargo run --release -p zawra-setup`, references to `zw`, LLDB notes). Changed setup command to `./webkit/scripts/thermal_build_control.sh`.
- **`tools/setup/src/main.rs`**: Rewritten — removed incremental/copy-newer logic, always cleans and re-extracts WebKit source. Uses relative paths instead of `CARGO_MANIFEST_DIR`-anchored paths.
- **New files**: `PLAN.md` (project roadmap), `thermal_build_control.sh` (build thermal controller), `thermal_release.sh` (release variant), `old.cmake` (archived CMake macros).
- **Deleted files**: `ui_shell.css`, `ui_shell.html`.

---

### Is this code already on `development`?

**No.** Not a single commit is shared. The merge base is `6d90bc4a` (Hajr submodule update), and all 11 commits are unique to this branch.

However, `development` has its own parallel evolution:
- `development` HEAD has `hajr` at `508fafef` (the old commit before the Windows fix)
- `development` has its own `NetworkDataTaskZNet` with `std::atomic` members (intact)
- `development` still has `Zawra_LocalStorage_GetAll` and `Zawra_History_Increment` (intact)
- `development` still uses the singleton pattern for `ZawraGraphicsBridge`
- `development` keeps the `[workspace]` in `Cargo.toml`
- `development` has `WebProcessProxy.cpp` etc. still patched in

---

### Would merging any of these commits break anything?

**Yes, multiple categories of breakage:**

| Risk Level | Issue | Location |
|------------|-------|----------|
| **HIGH** | `Cargo.toml` workspace removal breaks `cargo build --release` from root | `Cargo.toml` |
| **HIGH** | `std::atomic` removal in `NetworkDataTaskZNet` reintroduces data races (main thread + worker thread touch `m_state`/`m_isCancelled`) | `NetworkDataTaskZNet.cpp/.h` |
| **HIGH** | `hajr_seal_process()` signature change requires matching Hajr submodule — if only patches but not submodule are merged, link error | `*ProcessMain*.cpp` |
| **HIGH** | `BrowserDBStorageArea` include in `LocalStorageManager.cpp` — file must exist in patch tree or upstream source, likely compile error | `LocalStorageManager.cpp` |
| **MED** | Checksum removal in `ConnectionUnix.cpp` removes message integrity verification (security) | `ConnectionUnix.cpp` |
| **MED** | Deletion of `WebProcessProxy.cpp` etc. from patches means those modifications are lost | `patches/webkit/UIProcess/` |
| **MED** | Library path changes (`target/release/` → `dependencies/*/target/release/`) may not match actual build layout | `PlatformWPE.cmake` |
| **MED** | `.gitignore` rewrite may accidentally track previously-ignored artifacts | `.gitignore` |
| **LOW** | `ZawraStorageBridge` cookie parsing removed — all cookies stored with expiry=0, flags=0 | `ZawraStorageBridge.cpp` |
| **LOW** | `AGENTS.md` truncated — loses `zw` tool usage documentation | `AGENTS.md` |
| **LOW** | `old.cmake` and `PLAN.md` added to repo root (noise) | root directory |

**Would NOT break:**
- Rust lint fixes (safe, no behavior change)
- `Zawra_Free_Buffer` allocator fix (corrects rather than breaks)
- `unsafe { }` wrapping of FFI calls (safety improvement)
- `WouldBlock` handling in `NetworkDataTaskZNet` (adds robustness)
- Hajr submodule bump (brings new fixes, no API break visible)
- Batched ring signalling in `ConnectionUnix.cpp` (performance, not correctness)

---

### Recommendation by commit

| Commit | Should Cherry-Pick? | Rationale |
|--------|--------------------|-----------|
| `fc3e8d94` — macOS M2 fallbacks | **Cherry-pick** | Hajr portability improvements, low risk |
| `54e4225b` — IPC/isolation stability | **Cherry-pick** | Hajr stability fixes |
| `b8fc9ea5` — CI workflows | **Skip** | Branch-specific CI, not useful on `development` |
| `f78df15c` — sync portability fixes | **Cherry-pick** (squash with above) | Hajr submodule bump converges on same target |
| `c9380a5b` — final portability sync | **Skip** (duplicate of above) | Iterative commit that converges to same `df044538` |
| `68e4987e` — CI-compatible fixes | **Skip** (duplicate) | Covered by final Hajr bump |
| `b31ae274` — unwrap child.id | **Skip** (duplicate) | Covered by final Hajr bump |
| `85e06a46` — CI sync | **Skip** (duplicate) | Covered by final Hajr bump |
| `89bfd4dd` — Windows portability | **Cherry-pick** only the final effective diff | This is the commit that actually moves hajr to `df044538` |
| `46bab772` — Rust lint for init.rs | **Cherry-pick** | Safe, improves code quality |
| `6892d012` — Rust + patches cleanup | **DO NOT CHERRY-PICK AS A WHOLE** | Contains both critical fixes AND breaking changes. Extract: |
| | → Cherry-pick: `Zawra_Free_Buffer` allocator fix | Corrects heap corruption bug |
| | → Cherry-pick: `unsafe { }` wrapping of FFI calls | Safety improvement |
| | → Cherry-pick: `WouldBlock` handling in ZNet | Robustness improvement |
| | → Cherry-pick: Missing import additions | Fixes compile errors on other platforms |
| | → Cherry-pick: `net_body_ring_unregister` ordering fix | Correctness fix |
| | → Skip: `std::atomic` removal | Reintroduces data races |
| | → Skip: Checksum removal | Removes security verification |
| | → Skip: Hajr `seal_process` signature change | Requires matching Hajr submodule |
| | → Skip: `Cargo.toml` workspace removal | Breaks workspace build |
| | → Skip: `.gitignore` rewrite | Overly aggressive |
| | → Skip: `AGENTS.md` truncation | Loses documentation |
| | → Skip: WebKit patch deletions | Removes necessary patches |
| | → Skip: `ZawraStorageBridge` cookie stripping | Loses cookie metadata |

### Overall recommendation: **Delete the branch after cherry-picking**

The branch is a mix of valuable fixes (allocator correction, WouldBlock handling, Rust safety/lint, Hajr submodule bump) and destructive simplification (checksum removal, atomic removal, workspace removal, patch deletion). The good parts are small enough to cherry-pick individually. The bad parts would break the build or reintroduce bugs on `development`.

**Upstream Havr bump to cherry-pick:** `git cherry-pick 89bfd4dd` (or just `git -C dependencies/hajr fetch && git -C dependencies/hajr checkout df044538`)
