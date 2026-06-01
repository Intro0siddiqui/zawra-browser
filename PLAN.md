# Zawra Browser Project Plan

This document outlines the development phases for the Zawra Browser, focusing on the integration of WPE, z-net, and BrowserDB.

## Phase 1: Core Integration [x] (Completed)
- **Goal**: Pre-compile `z-net` and `BrowserDB` as shared libraries and establish the build pipeline.
- **Exit Criteria**: Successful static linking and a "hello world" FFI call between Rust and the Zig/C++ components.

## Phase 2: WPE & Native Engine Integration [x] (Completed)
- **Goal**: Wire the native `z-net` and `Browser-db` implementations (stored in `dependencies/`) directly into the browser core and WPE's networking/storage layers.
- **Exit Criteria**: Passing basic fetch via `z-net` and single-key KV storage smoke tests via `Browser-db`.

## Phase 3: Zero-Copy Optimization [/] (In Progress)
- **Goal**: Implement the `JavaScriptCore` surgery for high-frequency data (e.g., Cache API) to eliminate the copy-tax.
- **Exit Criteria**: Memory-mapped `ArrayBuffer` views in JS pointing directly to DB storage with a functional pinning mechanism.

## Phase 4: Full IndexedDB Compliance [ ] (Pending)
- **Goal**: Achieve full specification compliance for the storage layer.
- **Tasks**:
    - Implement compound indices, cursors, multi-entry indices.
    - Implement database versioning and migration logic.
- **Exit Criteria**: 100% pass rate in the `indexeddb` subset of the Web Platform Tests (WPT).

## Phase 5: Reliability & Security (Coverage-Guided Fuzzing) [ ] (Pending)
- **Goal**: Harden the FFI and zero-copy bridge via coverage-guided fuzzing.
- **Tasks**:
    - Integrate `cargo-fuzz` targeting `jsc_glue` and `znet_connector`.
    - Focus on compaction-induced race conditions and FFI data marshalling edge cases.
- **Exit Criteria**: 24 hours of continuous fuzzing on CI with zero crashes or memory safety violations (verified by ASan/TSan).

## Phase 6: Performance Stability & CI Benchmarks [ ] (Pending)
- **Goal**: Detect and prevent performance regressions in the bridge and storage layers.
- **Tasks**:
    - Implement `criterion` benchmarks for bridge latency (FFI overhead) and DB throughput (IOPS).
    - Integrate benchmarks into the CI pipeline with regression alerts.
- **Exit Criteria**: Automated performance reports on PRs; no regressions > 5% in latency or throughput compared to the main branch.
