# AGENTS.md

## Project Context
**Zawra Browser** is a highly customized WPE WebKit browser built to function like modern browsers (both headful and headless). It replaces standard WebKit subsystems (IPC, Network, Storage) with specialized high-performance components.

*   **Graphics**: Render Hardware Interface (RHI) handled by **z-graphics** (Zig) for Vulkan GPU acceleration.
*   **IPC & Sandbox**: Handled by **Hajr** (Zig), providing memory isolation (MPK/MTE) and syscall/filesystem isolation (`hajr_seal_process()`).
*   **Networking**: Handled by **Z-Net** (Zig/Rust) supporting HTTP/3.
*   **Storage**: Handled by **BrowserDB** (Rust) replacing LocalStorage/IndexedDB.

---

## 🛠️ Quick Reference: Commands & Workflows

### 1. Build Subsystems
```bash
# Setup submodules
git submodule update --init --recursive --depth 1

# Build Rust Engines
cargo build --release

# Build Zig IPC
cd dependencies/hajr && zig build
```

### ### 2. Apply WebKit Patches
```bash
# Mirror patches to Source tree (Run from root)
cargo run --release -p zawra-setup
```

### 3. Build WPE WebKit
```bash
# Compile via burst-mode thermal controller
./thermal_build_control.sh
```

### 4. Git PR-Based Workflow (Proactively ask user before pushing changes)
1.  **Branch off active development** (never direct to master, never branch from main if incomplete).
2.  **Double-check status** before adding to prevent target/ or bin/ pollution.
3.  Commit, push, and open PR via `gh pr create --fill`.
4.  Merge using squash once CI passes.

---

## ⚙️ Runtime & Environment

*   **Display**: Runs on **Sway (Wayland)** with XWayland for X11 graphics. 
*   **Headless Tests**: Clear environment variables (`WAYLAND_DISPLAY="" DISPLAY=""`) to force `z-graphics` into headless mode and bypass window mapping.
*   **Hajr IPC Tracing**: Activated via `HAJR_TRACE_FILE` env var.
    ```bash
    # Trace to Perfetto JSON
    HAJR_TRACE_FILE=/tmp/hajr_trace.json ./zawra-browser
    # Trace to stderr
    HAJR_TRACE_FILE="" ./zawra-browser
    ```

---

## ⚠️ Critical Policies & Guidelines

### 1. Behavioral Limits & Subagent Delegation (Strictly Enforced)
*   **NO UNSOLICITED LIBERTIES:** Stop execution and ask user for permission if you encounter missing dependencies, compile blockers, or broken scripts. Do not write unilateral patches.
*   **Submodule changes & Delegation:** Ask user before making changes inside `dependencies/`. The user might prefer to handle edits themselves or with other tools. If you must delegate submodule adjustments to a subagent, ask the user first. If they reject or ask not to touch it, halt and describe the problem so the user can fix it.

### 2. Sandbox & Feature Disabling
*   **Bubblewrap:** Must be disabled in CMake configuration (`-DENABLE_BUBBLEWRAP_SANDBOX=OFF`) to prevent conflicting with Hajr.
*   **WebSQL & AppCache:** Must remain `OFF` in `OptionsWPE.cmake` (replaced by BrowserDB). Always check downstream header consumers (e.g., via `rg`) before editing feature flags.

### 3. Build Cache Rules (ABSOLUTE)
*   **NEVER DELETE** the `webkit/build/` directory. Wiping the cache causes days of recompilation.
*   **NEVER RUN** `ninja -t clean`, `rm -rf webkit/build`, `ninja clean`, or equivalent cache-clearing operations.
*   If a build error claims a file or header is missing or empty, fix the root cause or re-run CMake. Do not wipe and restart.

### 4. LLVM Debugging & Tooling
*   Use `lldb` for cross-language (Rust/Zig/C++) debugging.
*   Always map addresses using `llvm-symbolizer` instead of slow legacy GNU `addr2line`.
*   **Compilation Database (`compile_commands.json`)**: Configure CMake with `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`. The root `.clangd` skips background indexing but provides diagnostics for open files.
*   **clang-scan-deps**: Used by CMake and Ninja for high-speed dependency analysis.

### 5. Code integrations
*   Never write to `webkit/source/` directly. Put all WebKit patches in `patches/webkit/` matching the source structure.
*   FFI functions returning `i32` must map to `nsresult` (`NS_OK = 0`, `NS_ERROR_FAILURE = -2147467259`).

### 6. Hajr Trace Ring & Global Sequence Index (GSI)
The trace system lives in `dependencies/hajr/src/trace/`.
*   **`trace.zig`**: `TraceRecord` (64-byte) and `TraceRing` (1024-slot lock-free SPSC). Stamped with wall time, IPC sequence, PID, and **GSI** (Global Sequence Index).
*   **`gsi.zig`**: Shared `memfd`-backed atomic counter giving a causal order across sandbox PIDs via atomic fetchAdd.
*   **`consumer.zig`**: Writes plain **Trace Event Format JSON** to `HAJR_TRACE_FILE`. Load in `ui.perfetto.dev`.
*   **`tools/log_stitcher.py`**: Offline correlator that merges GSI JSON events with `dmesg` kernel logs.

### 7. z-graphics Window & Display Mapping
*   **Display Preservation**: In `z-graphics` (Vulkan/X11), the X11 Display connection must be preserved and reused across `createWindow` and `createSurface` rather than being opened as a temporary local and immediately orphaned.
*   **Non-blocking Event Pump**: When creating the X11 window, mapping X11 windows under Sway/Xwayland is asynchronous. Pumping events must be done using a non-blocking check (`XPending(display)`) with a sleep interval rather than a raw blocking `XNextEvent` loop, to prevent hanging the UIProcess main thread on startup.

### 8. WebKit 2.54+ C++ Migration Gotchas
*   **Deprecated Macros**: Replace legacy `WTF_MAKE_FAST_ALLOCATED;` with `#include <wtf/FastMalloc.h>` and `WTF_DEPRECATED_MAKE_FAST_ALLOCATED(Class);`. Avoid `WTF_MAKE_TZONE_ALLOCATED` on custom stubs as it requires IsoSubspace definitions.
*   **WTFMove vs std::move**: WebKit 2.54 deprecated `WTFMove` in favor of standard `std::move`.
*   **Smart Pointers**: `Ref<T>` and `UniqueRef<T>` no longer support `.` operator method forwarding; use `->`.
*   **ThreadSafeWeakPtr**: Classes held weakly across multiple threads must inherit from `ThreadSafeRefCountedAndCanMakeThreadSafeWeakPtr<T>`.

### 9. Zero-SQLite Engine Independence
*   **WebSQL Decoupling**: All 18 WebSQL stub classes in `Source/WebCore/Modules/webdatabase/` completely decouple WebKit from `libsqlite3`, ensuring 0 SQLite engine symbols in `libWPEWebKit-2.0.so`.
*   **SQLiteFileSystem Pure Abstraction**: `SQLiteFileSystem` is backed purely by `WebCore::FileSystem` primitives in `Source/WebCore/platform/sql/SQLiteFileSystem.cpp` without any `sqlite3_*` engine calls.

### 10. Subsystem Bootstrap & Process Role Tagging
The startup sequence across `WebProcessMainWPE`, `NetworkProcessMainSoup`, `GPUProcessMainGLib`, and `MiniBrowser`:
1.  **Tag Process Role**: Call `hajr_trace_set_process_kind(kind)`:
    *   `1`: UI Process
    *   `2`: Web Process
    *   `3`: Network Process
    *   `4`: GPU Process
2.  **Bootstrap Subsystems**: Call `Z_Init_Subsystems("/tmp/zawra-profile")`, which automatically initializes `BrowserDB`, `z-net`, `z-graphics`, and invokes `hajr_trace_init()` to bind Hajr trace rings if `HAJR_TRACE_FILE` is defined.

### 11. IPC Side-Channel Handling
*   **CLOEXEC Preservation**: Side-channel sockets created in `ProcessLauncherGLib.cpp` must maintain correct `CLOEXEC` handling so file descriptor passing via `SCM_RIGHTS` does not drop before the child process completes its socket handshake.
*   **Executable Resolution**: In `Source/WebKit/Shared/glib/ProcessExecutablePathGLib.cpp`, auxiliary processes must always resolve via `WEBKIT_EXEC_PATH` and the executable directory in both developer and release builds.

### 12. IPC Ring Buffers, Descriptors & Memory Conventions
*   **Attachment LIFO Reversal for Decoder**: WebKit's `IPC::Decoder` consumes attachments using `takeLastAttachment()` (popping from the back in LIFO order). Any IPC bridge populating the attachment vector must map them in reverse order: `attachments[count - i - 1] = UnixFileDescriptor { fd, Adopt };`. Writing in forward order causes the decoder to receive attachments in inverted order.
*   **Negative FDs (-1) in SCM_RIGHTS**: Linux kernel `sendmsg` with `SCM_RIGHTS` returns `EBADF` (`errno=9`) if ANY file descriptor in `msg_control` is negative (`-1`) or closed. WebKit routinely creates null attachments with `fd = -1`. The sender must filter attachments, count valid descriptors (`>= 0`), allocate `CMSG_SPACE` only for valid descriptors, and omit `sendmsg` entirely if `validFdCount == 0`.
*   **Secondary IPC Connection Isolation**: Auxiliary processes (`WebProcess`, `NetworkProcess`, `GPUProcess`) receive bootstrap ring file descriptors via environment variables (`ZAWRA_HAJR_*`). The primary `platformOpen()` must immediately call `unsetenv()` on all `ZAWRA_HAJR_*` variables once read so that secondary internal child socketpairs (e.g. `NetworkProcessConnection`) do not hijack the bootstrap rings and corrupt memory.
*   **1MB Ring Inlining vs Out-of-Line SharedMemory**: Hajr provides 1MB circular shared-memory ring buffers. Avoid WebKit's legacy 4KB out-of-line threshold by setting `maxInlineSize = (512 * 1024)` for Hajr connections. This eliminates unnecessary POSIX shared memory allocations and descriptor overhead for inline messages.
*   **Debugging Seccomp Traps (`HAJR_SEAL_DEBUG=1`)**: When debugging auxiliary process crashes, run with `HAJR_SEAL_DEBUG=1`. This instructs Hajr's Seccomp filter to use `SECCOMP_RET_LOG` instead of `SECCOMP_RET_KILL_PROCESS`, logging the blocked syscall to `dmesg` without killing the process. Always inspect `dmesg` when processes exit unexpectedly.

### 13. Kernel & Sudo Diagnostic Playbook (Process Hangs, Seccomp & EventFD)
*   **Sudo & Root Capabilities**: Sudo access is available for kernel and process diagnosis (`sudo` commands).
*   **Inspecting Blocked/Stalled Threads**: When any WebKit process (`WPENetworkProcess`, `WPEWebProcess`, `WPEGPUProcess`, `MiniBrowser`) appears hung, stalls, or fails to respond to IPC:
    *   **Do NOT guess.** Read the exact kernel syscall and FD state directly:
        ```bash
        sudo cat /proc/<pid>/task/<tid>/syscall
        ```
        (Syscall `0` = `sys_read`, `232` = `epoll_wait`, `202` = `futex`).
    *   **Check EventFD counters**:
        ```bash
        sudo cat /proc/<pid>/fdinfo/<fd>
        ```
        If `eventfd-count: 0`, the reader is blocked waiting for signals. Verify the sender's outbound signal FD matches the receiver's inbound signal FD.
*   **Seccomp Auditing (`sudo dmesg`)**:
    *   When running with `HAJR_SEAL_DEBUG=1`, inspect kernel messages to see any blocked or audited syscalls:
        ```bash
        sudo dmesg | rg -i '(audit|seccomp|hajr)'
        ```
*   **PID Namespace Trace Isolation**:
    *   Auxiliary processes run in dedicated Linux user/PID namespaces where `getpid() == 1`.
    *   Never name trace files using raw PIDs alone (e.g. `/tmp/zawra.<pid>.json`). Always qualify trace files with the process kind (`ui`, `net`, `web`, `gpu`) or host PID to prevent child processes from clobbering each other's traces.
