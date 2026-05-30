# Efficiency and Struggle Analysis: Stitching WPE, z-net, and BrowserDB

## 1. Efficiency Gains

### Networking (z-net)
- **HTTP/3 & QUIC**: By using `z-net`, WPE gains first-class HTTP/3 support with 0-RTT handshakes. `z-net`'s benchmarks claim <3ms latency for HTTP/3, which is significantly faster than the standard stack in WPE's current state.
- **Zig-Optimized I/O**: `z-net`'s "1 API, 3 Fast Code Paths" approach (io_uring on Linux, kqueue on macOS, IOCP on Windows) ensures the lowest possible overhead for high-concurrency scenarios.

### Storage (BrowserDB)
- **FFI Bypass (Zero-Copy)**: The "Surgery" allows JavaScript to access database results (blobs) via `ArrayBuffer` views pointing directly to BrowserDB's memory-mapped regions. This eliminates the `String` / `Uint8Array` copy-tax that usually happens in `IndexedDB`.
- **Insert Performance**: BrowserDB outperforms SQLite by ~50x for individual inserts due to its asynchronous WAL group-commits and LSM-tree architecture.

## 2. Implementation Struggle

### Complexity: High
- **Async Bridge**: Reconciling `z-net`'s event loop (Zig) with WPE's GLib-based main loop requires careful work. We recommend using a dedicated thread for the `z-net` engine and communicating via lock-free rings or IPC channels to avoid blocking the main script thread.
- **Memory Management**: The "Zero-Copy" surgery is dangerous. If BrowserDB compacts its LSM-tree and moves data while a JS `ArrayBuffer` still points to it, the browser will crash. A robust "External Memory Buffer" tracking system must be implemented in `JavaScriptCore` to pin data.
- **Trait Alignment**: WPE's networking and storage interfaces are complex and strictly typed. Mapping BrowserDB's relational-KV model to the full `IndexedDB` spec (including cursors and indices) is a multi-week engineering effort.

## 3. Recommended Path

### Phase 1: Core Integration
- **Goal**: Pre-compile `z-net` and `BrowserDB` as shared libraries and establish the build pipeline.
- **Exit Criteria**: Successful static linking and a "hello world" FFI call between Rust and the Zig/C++ components.

### Phase 2: Glue Layer Implementation
- **Goal**: Use the provided `ZNetClient` and `BrowserDbEngine` glue code to hook into WPE's traits.
- **Exit Criteria**: Passing basic fetch and single-key KV storage smoke tests.

### Phase 3: Zero-Copy Surgery
- **Goal**: Implement the `JavaScriptCore` surgery for high-frequency data (e.g., Cache API) to eliminate the copy-tax.
- **Exit Criteria**: Memory-mapped `ArrayBuffer` views in JS pointing directly to DB storage with a functional pinning mechanism.

### Phase 4: Full IndexedDB Compliance
- **Goal**: Achieve full specification compliance for the storage layer.
- **Tasks**: Implement compound indices, cursors, multi-entry indices, and database versioning logic.
- **Exit Criteria**: 100% pass rate in the `indexeddb` subset of the Web Platform Tests (WPT).

### Phase 5: Reliability & Security (Fuzzing)
- **Goal**: Harden the FFI and zero-copy bridge via coverage-guided fuzzing.
- **Tasks**: Integrate `cargo-fuzz` targeting `jsc_glue` and `znet_connector`. Focus on compaction-induced race conditions.
- **Exit Criteria**: 24 hours of continuous fuzzing on CI with zero crashes or memory safety violations (verified by ASan/TSan).

### Phase 6: Performance Stability & CI Benchmarking
- **Goal**: Detect and prevent performance regressions in the bridge and storage layers.
- **Tasks**: Implement `criterion` benchmarks for bridge latency and DB throughput. Integrate into CI with regression alerts.
- **Exit Criteria**: Automated performance reports on PRs; no regressions > 5% in latency or throughput compared to the main branch.
