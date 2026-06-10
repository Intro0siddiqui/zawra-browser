# Cherry-Pick Analysis: `fix/integration-final` → `development`

**Analysis Date**: 2026-06-10
**Merge-base**: `6d90bc4a` (chore: update hajr submodule pointer to include pure ring IPC and isolation)
**`development` ahead by**: 4 commits (timer fiddles, PageClientImpl debug logging, current-snapshot feat, submodule updates)
**`fix/integration-final` ahead by**: 11 commits (accumulated Hajr syncs, lint fixes, IPC stability)

---

## Executive Summary

**Verdict**: Do NOT cherry-pick whole commits. Cherry-pick **individual file changes** only. The two branches have diverged significantly — `development` has 5 large patch files (WebProcessProxy.cpp, AuxiliaryProcessProxy.cpp, ProcessThrottler.{cpp,h}, BackgroundProcessResponsivenessTimer.cpp) that `fix/integration-final` lacks entirely, while `fix/integration-final` has 11 commits with mixed Hajr submodule noise and genuine Rust/C++ fixes.

The useful changes fall into 3 categories:
1. **Rust safety fixes** — wrapping FFI calls in `unsafe { }` blocks, fixing extern block safety, removing dead-code suppressions
2. **Bugfixes** — OwnedBodyRing Drop ordering, storage allocation simplification, non-atomic ZNet state (single-threaded correctness)
3. **Cleanup** — formatting, unused import removal, doc comment fixes

---

## Commit-by-Commit Breakdown

### 1. `fc3e8d94` — chore(portability): finalize macOS M2 fallbacks
| File | Change | Analysis |
|------|--------|----------|
| conductor/tracks/hajr-integration/plan.md | **DELETE** | Private design doc; not on `development` path. **Skip.** |
| docs/OS_AGNOSTIC_ANALYSIS.md | **DELETE** | Same. **Skip.** |
| docs/OS_AGNOSTIC_ROADMAP.md | **DELETE** | Same. **Skip.** |
| docs/SQLITE_REMOVAL_PLAN.md | **DELETE** | Same. **Skip.** |
| dependencies/Browser-db | Submodule pointer | `development` has its own pointer. **Skip.** |
| dependencies/hajr | Submodule pointer | Intermediate pointer, superseded by later commits. **Skip.** |
| dependencies/z-graphics | Submodule pointer | `development` has its own pointer. **Skip.** |
| src/wpe_glue/init.rs | +`use std::ffi::c_void;` +`use std::ptr;` | **Already on `development`** (verified). **Skip.** |

**Verdict**: **SKIP entire commit**. Only the init.rs imports are potentially useful, and they're already present on development.

---

### 2. `54e4225b` — fix(hajr): finalize stability fixes for IPC and isolation
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate pointer, superseded. **Skip.** |
| patches/.../ConnectionUnix.cpp | Error checking for hajr_ring_read, attachment validation, flushes pending messages on invalidate | **Already on `development`** — development has the same error handling (PARTIAL MESSAGE INFO READ, attachment count checks, body read failure). The `development` version is actually *more comprehensive* (includes checksum verification, RCE-attempt detection). **Skip.** |
| src/wpe_glue/init.rs | Remove `hajr_ring_map_with_signal`, `hajr_ring_get_signal_fd` extern decls | These are removed on fix/integration-final but are present in `development`'s extern block. Removing them would break `development`'s build. **Skip.** |

**Verdict**: **SKIP entire commit**. Development already has stronger error handling in ConnectionUnix.cpp. The init.rs extern removals would break development which still uses those functions.

---

### 3. `f78df15c` — fix(hajr): sync with submodule portability fixes
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate, superseded. **Skip.** |
| patches/.../SourcesWPE.txt | + `ZawraLegacyStubs.cpp` | **Already on `development`** (verified). **Skip.** |

**Verdict**: **SKIP**. Both changes already present on development.

---

### 4. `b8fc9ea5` — ci: enable workflows for fix/integration-final
| File | Change | Analysis |
|------|--------|----------|
| .github/workflows/ci.yml | Add `fix/integration-final` to trigger/push branches | **Already on `development`** — the CI file is identical on both branches. **Skip.** |

**Verdict**: **SKIP**.

---

### 5. `c9380a5b` — fix(hajr): final portability synchronization
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate pointer. **Skip.** |

**Verdict**: **SKIP**.

---

### 6. `68e4987e` — fix(hajr): finalize CI-compatible portability fixes
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate pointer. **Skip.** |

**Verdict**: **SKIP**.

---

### 7. `b31ae274` — fix(hajr): unwrap optional child.id synchronization
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate pointer. **Skip.** |
| src/wpe_glue/init.rs | Remove `Zawra_Hajr_CreateBootstrapRing` and `Zawra_Hajr_MapBootstrapRing` | These functions are duplicates of existing ring functionality. **Potentially useful cleanup** but needs review — check if anything on `development` calls them. **Needs review.** |

**Verdict**: **NEEDS REVIEW**. The init.rs cleanup removing duplicated FFI functions is a legitimate simplification, but must verify nothing calls them from C++ side.

---

### 8. `85e06a46` — fix(hajr): finalize CI-compatible portability synchronization
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | Intermediate pointer. **Skip.** |

**Verdict**: **SKIP**.

---

### 9. `89bfd4dd` — fix(hajr): sync with submodule Windows portability fixes
| File | Change | Analysis |
|------|--------|----------|
| dependencies/hajr | Submodule pointer | **FINAL** hajr pointer on fix/integration-final. Needs comparison with `development`'s hajr pointer. **Needs review.** |

**Verdict**: **NEEDS REVIEW**. The final hajr submodule pointer may or may not be ahead of development's.

---

### 10. `46bab772` — fix(rust): address lint warnings for wpe_glue/init.rs
| File | Change | Analysis |
|------|--------|----------|
| src/wpe_glue/init.rs | Reorder imports, add `unsafe { }` around FFI calls (libc::malloc, libc::mprotect), reformat parameter lists, change `unsafe extern "C"` → `extern "C"` | **NOT on `development`** — development still has `unsafe extern "C"` for extern blocks, missing `unsafe` wrappers. Pure lint/safety fix. **Safe to cherry-pick** the init.rs changes. |

**Verdict**: **CHERRY-PICK** — file-level cherry-pick of `src/wpe_glue/init.rs` changes. Low risk, pure hygiene.

---

### 11. `6892d012` — chore(rust): address remaining unused imports and formatting warnings
This is the most substantive commit. File-by-file:

| File | Change | Already on dev? | Verdict |
|------|--------|-----------------|---------|
| `build.rs` | Remove `rustc-check-cfg`, add `use std::path::Path` | **No** (dev still has rustc-check-cfg) | **Cherry-pick** — harmless cleanup |
| `src/bin/zawra.rs` | Formatting (unwrap_or_else reformat) | **Yes** (identical on both branches) | **Skip** |
| `src/lib.rs` | Remove `#[allow(non_snake_case)]`, reorder `pub use` | **No** (dev still has the allow) | **Cherry-pick** — dead attribute removal |
| `src/ui/renderer.rs` | Remove `#[allow(dead_code)]`, add `CString`/`c_char` imports | **No** (dev still has dead_code attr) | **Cherry-pick** — cleanup |
| `src/ui/tabs.rs` | Remove `#[allow(dead_code)]`, add `use browserdb::BrowserDB` | **No** (dev still has dead_code attr) | **Cherry-pick** — cleanup + necessary import |
| `src/wpe_glue/networking.rs` | Wrap all FFI calls in `unsafe { }`, add `net_engine_destroy`, `net_read` imports, reorder OwnedBodyRing Drop (unregister before close) | **No** — dev lacks unsafe blocks and has old Drop ordering | **Cherry-pick** — **IMPORTANT**: safety fix + ordering bugfix |
| `src/wpe_glue/streaming.rs` | Add `CStr`/`CString`/`c_char` imports, `NS_BASE_STREAM_WOULD_BLOCK`, `net_read`, `ZNetChannel`/`ZNetInputStream`/`global_engine` imports | **No** — dev lacks all these | **Cherry-pick** — enables non-blocking stream reads |
| `src/zero_copy.rs` | Add `use std::ptr;`, fix `//` → `///` doc comment | **No** (dev lacks `use std::ptr`) | **Cherry-pick** — trivial hygiene |

**Verdict**: **CHERRY-PICK** — this commit contains most of the valuable changes. Apply file-by-file.

---

## Files Deserving Individual Cherry-Pick Attention

These files appear in the `git diff development..fix/integration-final` but are NOT part of any of the 11 commits — they represent divergent branch histories. Each needs individual assessment:

### Cherry-Pick Candidates (non-commit files)

| File | Diff Direction | Assessment |
|------|---------------|------------|
| `src/wpe_glue/storage.rs` | fix/integration-final simplifies allocations (direct `into_boxed_slice()`, `Vec::from_raw_parts` in `Zawra_Free_Buffer`), removes `Zawra_LocalStorage_GetAll` and `Zawra_History_Increment` | **Cherry-pick** — the allocation simplification is correct (the old double-copy was over-cautious). The removal of `Zawra_LocalStorage_GetAll` and `Zawra_History_Increment` needs review — are they used anywhere on `development`? |
| `src/wpe_glue/zero_copy_bridge.rs` | Uses `Vec::from_raw_parts` directly instead of reconstructing via `Box::from_raw(slice).into_vec()` | **Cherry-pick** — matches the new allocation strategy in storage.rs |
| `src/wpe_glue/launcher.rs` | Adds unused `Command`/`CommandExt` imports, renames `app_data` → `appData`, changes `unsafe extern "C"` → `extern "C"` for hajr decls | **Cherry-pick partially** — the `extern "C"` fix is good. The unused imports are harmless but unnecessary. |
| `src/wpe_glue/factory.rs` | Removes `#[allow(dead_code)]` from FFI vtable functions | **Cherry-pick** — these are used via vtable pointer, not by name |
| `patches/.../ZawraGraphicsBridge.cpp` | Removes singleton/destructor/destroy — simplifies to static methods | **SKIP** — `development` has the full singleton pattern with surface lifecycle. Reverting would break graphics pipeline. |
| `patches/.../ZawraGraphicsBridge.h` | Removes `NeverDestroyed` include, singleton decl, non-default destructor | **SKIP** — same reason as above |
| `patches/.../ZawraLegacyStubs.cpp` | **DELETED** on fix/integration-final | **SKIP** — `development` still needs these stubs |
| `patches/.../ZawraStorageBridge.cpp` | Strips cookie parsing (expiry, flags), removes `Zawra_History_Increment` call | **SKIP** — `development` has the full cookie parsing implementation. The removal is a regression. |
| `patches/.../GPUProcessMainGLib.cpp` | `hajr_seal_process()` signature change (removes process_type arg) | **SKIP** — `development` uses typed sealed processes. Would break. |
| `patches/.../NetworkProcessMainSoup.cpp` | Same as above | **SKIP** |
| `patches/.../WebProcessMainWPE.cpp` | Same as above | **SKIP** |
| `patches/.../NetworkDataTaskZNet.cpp` | Removes atomics, adds WouldBlock (-5) handling | **Cherry-pick** — ZNet worker is single-threaded, atomics were cargo-cult. WouldBlock handling prevents tight loops. |
| `patches/.../NetworkDataTaskZNet.h` | `std::atomic<State>` → `State` | **Cherry-pick** — matches above |
| `patches/.../Connection.h` | Adds ring batching fields (`m_pendingRingMessages`, `m_ringBatchSize`), removes `m_hajrSignalSocket` | **Needs review** — the batching is a performance improvement but the GSocket removal may conflict with development's approach |
| `patches/.../ProcessLauncherGLib.cpp` | Removes `terminateProcess()`, `platformInvalidate()`, simplifies launch | **Needs review** — launch simplification is useful, but terminate removal would break cleanup. |
| `patches/.../PageClientImpl.cpp` | Removes debug logging destructor, changes to static method call | **Cherry-pick** — the debug logging was for dev; static call aligns with simplified ZawraGraphicsBridge |
| `patches/.../LocalStorageManager.cpp` | `SQLiteStorageArea` → `BrowserDBStorageArea::create()` | **Cherry-pick** — this is the intended BrowserDB integration |
| `patches/.../Sources.txt` | + `BrowserDBStorageArea.cpp` | **Cherry-pick** — needed for the above |
| `patches/.../NetworkDataTaskSoup.h` | Removes `SoupMessage` and `SoupMultipartInputStream` members | **Skip** — these are used by Soup networking |
| `patches/.../PlatformWPE.cmake` (WebCore) | Removes `vulkan` and `X11` libs, adds ZawraGraphicsBridge.cpp | **Needs review** — X11 removal may break on some systems |
| `patches/.../PlatformWPE.cmake` (WebKit) | Changes lib paths (z-net, browserdb) to dependency dirs | **Needs review** — these paths need to match actual build layout |
| `patches/.../TextureMapperGL.cpp` | Change (likely one-line) | Needs review |
| `.gitignore` | Changed | Needs review — likely branch-specific ignores |
| `AGENTS.md` | Changed | **Skip** — development has the correct AGENTS.md |
| `Cargo.lock` | Large diff | **Skip** — let Cargo resolve deps |
| `Cargo.toml` | Changed | **Skip** — development's Cargo.toml is authoritative |
| `PLAN.md` | **NEW** on fix/integration-final | **Skip** — private planning doc |
| `old.cmake` | **NEW** on fix/integration-final | **Needs review** — appears to be a backup CMake file |
| `tools/setup/src/main.rs` | Simplified (removes mtime-based patching, removes compile_commands.json symlink, uses fs_extra instead) | **Needs review** — the simplification removes useful incremental patching |
| `zawra_graphics_integration.patch` | **NEW** on fix/integration-final | **Skip** — this is a generated patch file, not a source change |
| `thermal_build_control.sh` | **NEW** | **Cherry-pick** — useful utility script |
| `thermal_release.sh` | **NEW** | **Cherry-pick** — useful utility script |
| `ui_shell.css` | **DELETED** on fix/integration-final | **Skip** — these are kept on development |
| `ui_shell.html` | **DELETED** on fix/integration-final | **Skip** — same |

---

## Hajr Submodule Pointer

```
development:    (exists, has its own pointer — see git show development:dependencies/hajr)
fix/integration-final: 89bfd4dd points to d3ed51b7093786838a555a9826206ef82bec9b30
```

The Hajr submodule is tracked independently on each branch through their respective commit histories. The fix/integration-final pointer chain goes through 6 intermediate submodule updates (fc3e8d94 → 54e4225b → f78df15c → c9380a5b → 68e4987e → b31ae274 → 85e06a46 → 89bfd4dd). Each branch should use its own submodule strategy — **do not cherry-pick submodule pointer changes** between branches as they represent different integration states.

---

## Final Recommendations

### Files to Cherry-Pick (safe, useful, not on development)

1. **`src/wpe_glue/init.rs`** — from commit 46bab772: add `unsafe { }` wrappers for FFI calls, `extern "C"` fix, import reordering
2. **`src/wpe_glue/networking.rs`** — from commit 6892d012: `unsafe { }` FFI wrappers, `net_engine_destroy`/`net_read` imports, OwnedBodyRing Drop ordering fix
3. **`src/wpe_glue/streaming.rs`** — from commit 6892d012: `NS_BASE_STREAM_WOULD_BLOCK`, streaming imports
4. **`src/wpe_glue/storage.rs`** — allocation simplification (direct `into_boxed_slice()`, `Vec::from_raw_parts`)
5. **`src/wpe_glue/zero_copy_bridge.rs`** — `Vec::from_raw_parts` instead of `Box::from_raw(slice).into_vec()`
6. **`src/wpe_glue/launcher.rs`** — `extern "C"` fix for hajr decls
7. **`src/wpe_glue/factory.rs`** — remove `#[allow(dead_code)]` from vtable functions
8. **`src/lib.rs`** — remove `#[allow(non_snake_case)]`
9. **`src/ui/renderer.rs`** — remove `#[allow(dead_code)]`, add imports
10. **`src/ui/tabs.rs`** — remove `#[allow(dead_code)]`, add `BrowserDB` import
11. **`src/zero_copy.rs`** — add `use std::ptr;`, fix doc comment
12. **`build.rs`** — remove `rustc-check-cfg`
13. **`patches/.../NetworkDataTaskZNet.cpp`** — non-atomic state, WouldBlock handling
14. **`patches/.../NetworkDataTaskZNet.h`** — non-atomic fields
15. **`patches/.../LocalStorageManager.cpp`** — BrowserDBStorageArea integration
16. **`patches/.../Sources.txt`** — + BrowserDBStorageArea.cpp
17. **`patches/.../PageClientImpl.cpp`** — remove debug logging, static method call
18. **`thermal_build_control.sh`** — new utility
19. **`thermal_release.sh`** — new utility

### Files to Skip (would break things or are already on development)

1. All `dependencies/hajr`, `dependencies/Browser-db`, `dependencies/z-graphics` submodule pointer changes
2. All docs/ and conductor/ deletions (private planning docs, not on development's path)
3. `conductor/tracks/hajr-integration/plan.md` deletion
4. `patches/.../ZawraGraphicsBridge.{cpp,h}` — singleton/destructor simplification would regress development
5. `patches/.../ZawraLegacyStubs.cpp` deletion — development needs these stubs
6. `patches/.../ZawraStorageBridge.cpp` — stripped cookie parsing is a regression
7. `patches/.../GPUProcessMainGLib.cpp`, `NetworkProcessMainSoup.cpp`, `WebProcessMainWPE.cpp` — `hajr_seal_process()` signature change incompatible with development
8. `patches/.../NetworkDataTaskSoup.h` — SoupMessage removal would break Soup networking
9. `.github/workflows/ci.yml` — already on development
10. `src/bin/zawra.rs` — already on development
11. `ui_shell.css`, `ui_shell.html` — kept on development
12. `Cargo.lock`, `Cargo.toml` — development's versions are authoritative
13. `AGENTS.md` — development's version is authoritative
14. `PLAN.md`, `old.cmake`, `zawra_graphics_integration.patch` — not source changes
15. `patches/.../ConnectionUnix.cpp` — error handling already on development (with more checks)
16. `patches/.../AuxiliaryProcessProxy.cpp`, `BackgroundProcessResponsivenessTimer.cpp`, `ProcessThrottler.{cpp,h}`, `WebProcessProxy.cpp` — these exist only on development

### Needs Review

1. **`src/wpe_glue/init.rs`** (from b31ae274) — removal of `Zawra_Hajr_CreateBootstrapRing`/`Zawra_Hajr_MapBootstrapRing`: verify nothing on development calls these
2. **`patches/.../Connection.h`** — ring batching fields: useful but check compatibility
3. **`patches/.../ProcessLauncherGLib.cpp`** — launch simplification: useful but terminateProcess removal needs verification
4. **`patches/.../PlatformWPE.cmake`** (both) — path changes and library removals: must match actual build layout
5. **`tools/setup/src/main.rs`** — simplification loses incremental patching capability
6. **`dependencies/hajr`** (final pointer 89bfd4dd) — compare with development's pointer to see if ahead/behind
7. **`src/wpe_glue/storage.rs`** removals (`Zawra_LocalStorage_GetAll`, `Zawra_History_Increment`) — verify these aren't used by development's C++ bridge

### Recommended Cherry-Pick Order

1. **`build.rs`** and `src/zero_copy.rs` — trivial, no conflicts
2. **`src/lib.rs`**, `src/ui/renderer.rs`, `src/ui/tabs.rs`, `src/wpe_glue/factory.rs` — attribute cleanup, safe
3. **`src/wpe_glue/launcher.rs`** — `extern "C"` fix
4. **`src/wpe_glue/init.rs`** — unsafe wrappers + lint fixes
5. **`src/wpe_glue/networking.rs`** — unsafe wrappers + Drop ordering fix (critical bugfix)
6. **`src/wpe_glue/streaming.rs`** — non-blocking stream support
7. **`src/wpe_glue/storage.rs`** + `zero_copy_bridge.rs` — allocation simplification (must do together)
8. **`patches/.../NetworkDataTaskZNet.{cpp,h}`** — non-atomic state + WouldBlock
9. **`patches/.../LocalStorageManager.cpp`** + `Sources.txt` — BrowserDB integration
10. **`patches/.../PageClientImpl.cpp`** — cleanup
11. **`thermal_build_control.sh`**, `thermal_release.sh` — new utilities (any order)

After cherry-picking, verify the Rust side compiles with `cargo build` and the patch setup runs with `cargo run --release -p zawra-setup`.
