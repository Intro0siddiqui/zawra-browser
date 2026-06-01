# Zawra Browser: Comprehensive Testing Plan (v1.0)

This document outlines the systematic testing strategy for the Zawra Browser, focusing on its high-performance subsystems and its integration with WebKit.

## 1. Test Tiers

### Tier 1: Subsystem Unit Testing
*Objective: Ensure individual modules (Hajr, Z-Net, BrowserDB) are robust before integration.*

- **Hajr (Zig IPC)**:
    - `zig build test`: Run core memory safety and poisoning tests.
    - Benchmark zero-copy throughput using `src/tests/benchmark.zig`.
    - Validate guard page effectiveness in `src/tests/guard_pages.zig`.
- **Z-Net (Rust Network)**:
    - `cargo test`: Run async I/O and protocol parser tests.
    - Run `performance_benchmarks.zig` (via Zig bridge) to measure request/response latency.
    - Validate security logic using `security_validation.zig`.
- **BrowserDB (Rust Storage)**:
    - Test persistence by writing/reading large datasets.
    - Verify 128-bit hash collision resistance for URLs.

### Tier 2: Integration Testing (The "Glue" Layer)
*Objective: Verify the C-ABI bridge between Rust/Zig and WebKit.*

- **Storage FFI**: Run `tests/integration.rs` (mod `storage_tests`) to confirm cookies/bookmarks are correctly marshalled between C and Rust.
- **Networking FFI**: Test the `Zawra_Net_Read` path using a local mock HTTP server.
- **Zero-Copy Bridge**: Verify that JavaScriptCore can access `BrowserDB` memory segments without copying (requires JSC test harness).

### Tier 3: Functional Testing (MiniBrowser)
*Objective: Validate end-to-end browser behavior in headless mode.*

- **Basic Navigation**: Run `./MiniBrowser https://example.com` and verify it reaches the "finished-loading" state.
- **Networking Bypass**: Monitor `Z-Net` logs while MiniBrowser is running to ensure traffic is flowing through the custom stack, not system Soup.
- **Headless Rendering**: Capture a screenshot (if enabled) or verify the DOM tree via the remote inspector.

### Tier 4: Hardware & Environmental Testing
*Objective: Ensure the system stays within thermal limits and utilizes resources efficiently.*

- **Thermal Burst Validation**: Run a 10-minute navigation loop and verify `thermal_build_control.sh` correctly pauses the process when `thermal_zone2` hits 63°C.
- **Memory Pressure**: Monitor Zswap usage during a heavy load (multiple tabs) to ensure the 4GB swapfile handles memory spikes.

## 2. Automated Test Matrix

| Command | Target | Purpose |
| :--- | :--- | :--- |
| `cargo test` | Rust Core/Glue | Unit tests for UI, Tabs, and FFI glue. |
| `cd dependencies/hajr && zig build test` | IPC Engine | Verification of hardened ring buffers. |
| `cd dependencies/z-net && zig build test` | Network Bridge | Testing the Zig-to-Rust network bridge. |
| `./webkit/build/WPE/Debug/bin/MiniBrowser --headless --automation` | Full Browser | End-to-end headless verification. |

## 3. Performance Success Criteria

- **IPC Latency**: < 10μs for 1KB payloads (Hajr).
- **Network TTFB**: < 50ms for local loopback (Z-Net).
- **Startup Time**: MiniBrowser should reach the first paint in < 300ms.
- **Thermal Stability**: CPU package temp must not exceed 68°C during sustained heavy rendering.

---
*Created on Saturday, May 30, 2026*
