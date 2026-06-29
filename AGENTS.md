# AGENTS.md

## Project Context
**Zawra Browser** is a highly customized, headful WPE WebKit browser. It replaces standard WebKit subsystems (IPC, Network, Storage) with specialized high-performance components.

- **Goal**: Performance-optimized, sandboxed headful browser (currently testing in headless mode for faster iteration).
- **Graphics**: Render Hardware Interface (RHI) handled by **z-graphics** (Zig) for cross-platform GPU acceleration (Vulkan, Metal, D3D12). **Status: Complete & Stable** (Successfully initializes and exports Vulkan surfaces across the Hajr IPC boundary without crashing).
- **IPC & Sandbox**: Handled by **Hajr** (Zig), acting as the "Moriarty Sandbox". It provides hardware-enforced memory isolation (MPK/MTE) via lock-free ring buffers, AND OS-level syscall/filesystem isolation (Seccomp-BPF, Landlock, Seatbelt, Windows Mitigations) directly via `hajr_seal_process()`.
  - **Trace Ring + GSI**: A structured trace ring system (`src/trace/`) for observing multi-process IPC orchestration (UIProcess↔WebProcess, etc.) without touching WebKit C++ code. Every record is stamped with a **Global Sequence Index (GSI)** from a shared `memfd`-backed atomic counter, giving a cross-process total causal order across all sandbox PIDs. A background drain thread writes plain Trace Event Format JSON (readable by `ui.perfetto.dev`). An offline `log_stitcher.py` tool correlates user-space GSI events with `dmesg` kernel logs by PID. Runtime-activated via `HAJR_TRACE_FILE` env var — zero overhead when disabled.
  **⚠️ CRITICAL SANDBOX RULE:** WebKit natively uses Bubblewrap (`bwrap`) on Linux for its default sandbox. This MUST be explicitly disabled during CMake configuration (`-DENABLE_BUBBLEWRAP_SANDBOX=OFF`) so that it does not conflict with Hajr.
  **⚠️ CRITICAL STORAGE RULE:** `ENABLE_WEBSQL` and `ENABLE_APPLICATION_CACHE` MUST be `OFF` in `OptionsWPE.cmake`. Both subsystems are replaced by BrowserDB. The upstream files that unconditionally include WebSQL/AppCache headers have `#if ENABLE(WEBSQL)` / `#if ENABLE(APPLICATION_CACHE)` guards in `patches/webkit/`. **NEVER** set these to `ON` — it causes missing generated headers and rebuilds from scratch.
- **Networking**: Handled by **Z-Net** (Zig/Rust) supporting HTTP/3.
- **Storage**: Handled by **BrowserDB** (Rust) for LocalStorage and persistent data.

## Tech Stack
- **Core**: WPE WebKit (C++)
- **IPC Layer**: Zig 0.16.0
- **Network & Storage Layers**: Rust (Cargo)
- **Build System**: CMake, Ninja

## Runtime Environment
The development machine runs **Sway** (Wayland compositor). MiniBrowser creates an X11 window (via XWayland) and renders directly to the user's display. **When you run MiniBrowser, the window appears on the user's actual screen — it is NOT headless.**

- **Compositor**: Sway (Wayland) with XWayland for X11 compatibility
- **Display**: `$WAYLAND_DISPLAY` is set; X11 fallback via `$DISPLAY` (XWayland)
- **GPU**: Vulkan via `VK_INSTANCE_LAYERS` / `MESA_VK_DEVICE_SELECT` — check `vulkaninfo` or `vkcube` for available GPUs
- **Verify environment** before running tests:
  ```bash
  echo $WAYLAND_DISPLAY        # Should be "wayland-1" or similar
  echo $SWAYSOCK               # Sway IPC socket
  swaymsg -t get_outputs       # List active outputs/monitors
  xdpyinfo 2>/dev/null | head  # XWayland display info
  ```
- **Do NOT** run `sway` nested (it creates a nested compositor inside the existing Sway session). If you need to test display behavior, use the existing session.
- **Timeout**: MiniBrowser runs with `timeout 20` for diagnostic captures. The process stays alive for the full duration when IPC is working.

## Core Workflows for AI Agents

### ⚠️ Behavioral Guidelines for AI Agents: NEVER TAKE UNSOLICITED LIBERTIES ⚠️
If you encounter a blocked path, a missing dependency (like a completed subsystem not mentioned in the prompt), or a broken script, **DO NOT** unilaterally decide to write a patch, compile the dependency, or drastically alter the build environment on the user's behalf. 

Instead, you MUST:
1. Stop execution.
2. Explain exactly what is broken or missing.
3. Propose a solution to the user.
4. **WAIT for explicit permission** before executing the fix.

Agents must **never** adopt the mindset of "I just went ahead and took the liberty for you and completed the work." Always prioritize the user's explicit consent over proactive execution, especially when it involves Git history, the build system, or undocumented dependencies.

### Subagent Usage for Submodule/Dependency Changes
When making changes to submodules or dependencies (e.g., Hajr in `dependencies/hajr/`, Rust crates in `src/`), **delegate to a subagent but ask user before it as user somtimes wants to make changes with his other agent or by himself and if user mention to not touch then only tell him that this problem so user can fix it for you ** rather than editing directly. This keeps context clean and isolates dependency work.

**Debug Print Protocol:** When asking a subagent to verify where a subsystem is failing, instruct them to add `fprintf(stderr, ...)` (C++) or `std.os.linux.syscall3(.write, 2, ...)` (Zig) debug prints at the failure point. This avoids needing GDB/LLDB in headless environments and produces visible output in the build log. Always specify the prefix tag (e.g., `[CRASH-V2]`) so output can be filtered with `rg`.

**⚠️ Hajr IPC Tracing (replaces old [HAJR-DIAG] prints):** Hajr now has a structured trace ring system (`src/trace/`). The old unstructured `[HAJR-DIAG]` raw `syscall3(.write, 2, ...)` prints in `bindings.zig` have been removed. To trace IPC messages at runtime:
```bash
# Write Perfetto-compatible JSON trace (load in ui.perfetto.dev)
HAJR_TRACE_FILE=/tmp/hajr_trace.json ./zawra-browser

# Write to stderr instead
HAJR_TRACE_FILE="" ./zawra-browser

# Tracing off (default — zero overhead, one atomic null-check per IPC call)
./zawra-browser
```
The trace ring is a 1024-slot lock-free SPSC ring (64 KB) in each process. A background drain thread writes Perfetto JSON events. Detects message loss (missing `ring_recv` for a `ring_send` seq) and duplication. For adding new trace points, use `trace.IpcTracer.recordFfi()` or `trace.IpcTracer.recordIpc()` in Zig code.

**Verification Loop:** After the subagent makes changes:
1. Rebuild the dependency (`zig build`, `cargo build --release`)
2. Run `cargo run --release -p zawra-setup` to sync patches
3. Rebuild WebKit via thermal controller
4. Run MiniBrowser and `rg` for the debug print prefix to confirm the fix.

### 1. WebKit Setup (The Patch System)
We do **not** use a Git submodule for the main WebKit source to avoid repository bloat and "detached HEAD" stress. Instead, we use a custom Rust setup tool.

- **Source Code**: Official WPE WebKit stable releases (Tarball).
- **History**: 0% WebKit history is pulled, saving ~5GB of Git metadata.
- **Patching**: Files in `patches/webkit/` are overlaid onto the official source via `fs_extra::dir::copy` (full file copy, not diffs). Both new files and modified existing files are supported.
- **Patch locations**:
  - `patches/webkit/Source/WTF/` — WTF layer (RunLoop, WorkQueue, platform abstractions)
  - `patches/webkit/Source/WebKit/` — WebKit2 layer (network, IPC, build system)
  - `patches/webkit/Source/WebCore/` — WebCore layer (storage bridge, cookie/soup integration)
- **Setup Command**: 
  ```bash
  # Note: The custom setup tool overlays patches onto the WebKit source
  # THIS MUST BE RUN BEFORE COMPILING IF YOU MODIFIED ANY PATCH FILES!
  # Run from the project root. The tool is CWD-independent — it anchors
  # every path via env!("CARGO_MANIFEST_DIR"), so `cd tools/setup` is
  # unnecessary and (historically) caused a path-resolution bug.
  cargo run --release -p zawra-setup
  # or, if the binary is already built:
  ./target/release/zawra-setup
  ```

### 3. Git Workflow (PR-Based)
To maintain a stable `master` branch and ensure all code passes continuous integration, agents **MUST** use a Pull Request workflow for all changes:

1. **Branching**: Never commit directly to `master`. Create a descriptive feature branch.
   **⚠️ CRITICAL GIT RULES:**
   - **NEVER** branch directly off `main` if it only contains the `Initial commit` or lacks the `src/` directory. Always branch off the active development branch (currently `development`).
   - **NEVER** run `git add .` or `git commit -a` blindly without checking `git status`, especially on a bare branch without a `.gitignore`. This will bloat the repository with the massive `target/` directory and `.o` binaries.
   - **NEVER** run `git clean -fdx` or `git reset --hard` when switching between branches with different histories, as it will instantly vaporize untracked source files and submodules.



   ```bash
   git checkout -b feat/my-new-feature
   ```
2. **Commit & Push**:
   ```bash
   git commit -m "feat: description of changes"
   git push -u origin HEAD
   ```
3. **Open Pull Request**: Use the GitHub CLI to create the PR, providing necessary details.
   ```bash
   gh pr create --fill
   ```
4. **Verify CI**: You MUST wait for and verify that all GitHub Actions workflows pass before proceeding.
   ```bash
   gh pr checks --watch
   ```
   *If checks fail, fix the code, commit, push again, and re-verify.*
5. **Merge**: Once CI is green, merge the PR using squash to keep the history clean.
   ```bash
   gh pr merge --squash --delete-branch
   ```

### 4. Building the Project
- **Step 1: Setup submodules** (BrowserDB, Hajr, Z-Net):
  ```bash
  git submodule update --init --recursive --depth 1
  ```
- **Step 2: Compile Rust Subsystems** (Unified Workspace):
  ```bash
  # We use a unified Cargo Workspace. You can build everything from the root.
  # This populates target/release/ with the three artifacts WebKit's link
  # step needs:
  #   - libzawra_browser.a   (the FFI bridge)
  #   - libz_net_engine.a    (Z-Net networking engine)
  #   - libbrowserdb.so      (BrowserDB storage engine)
  cargo build --release
  ```
- **Step 3: Compile Zig Subsystems**:
  - Hajr: `cd dependencies/hajr && zig build`
- **Step 4: Configure & Build WebKit**:
  ```bash
  # IMPORTANT: If you edited any files in patches/webkit/, you MUST first run:
  cargo run --release -p zawra-setup
  # Then, use the thermal controller for safe burst-mode compilation:
  # IMPORTANT: Do NOT pipe thermal_build_control.sh through tail or other
  # truncation commands — the script manages its own output and truncation
  # causes the build tool to hang or lose thermal state tracking.
  ./thermal_build_control.sh
  # NOTE: A full WebKit build runs for hours. If your shell enforces a
  # command timeout, detach the script with setsid/nohup so the parent
  # shell's signal does not kill the build:
  #   setsid bash thermal_build_control.sh > /tmp/build.log 2>&1 < /dev/null &
  ```

## Project Intelligence (Knowledge Graph)

Zawra uses a **SQLite Knowledge Graph** and a unified CLI tool named **`zw`** to map the complex relationships between our custom patches and the massive WebKit source.

### Mandatory Tool Usage for Agents

**General Searching Rules:**
- **ALWAYS** use `rg` (ripgrep, run via the Bash tool) for searching file contents. It is faster and more reliable than `grep`. If `rg` is not installed on the system, fall back to `grep`.
- **ALWAYS** use `fd` in place of `find` for finding files by name.

For Zawra-specific project intelligence, agents **MUST** use the following `zw` commands instead of broad directory scans:

1.  **`./zw find <term>`**: Locate patches or FFI symbols related to a feature. **DO NOT** use this to search for upstream WebKit C++ APIs (like `WTF::String` methods). `zw` maps integration boundaries, it does not index the massive upstream WebKit source tree.
2.  **`./zw read <filename>`**: **CRITICAL.** Use this to read file contents. It will automatically detect if a Zawra patch exists for a WebKit file and output **both** the patch and the original side-by-side with clear headers. This is the fastest way to see what we've changed vs. what's original.
3.  **`./zw patches`**: List all files currently modified by Zawra.
4.  **`./zw audit`**: Run a structural audit of the build graph. It detects **double-listed source files** (linker errors), orphaned patches (files not in the build), and Zig module collisions.
5.  **`./zw update`**: Manually refresh the Knowledge Graph. (Note: Most queries now perform a **Smart Auto-Update**).
6.  **`./zw stubs`**: List detected stubs, empty function placeholders, or unimplemented code blocks.
    * **Scope**: Scans C++ patches and Rust glue code.
    * **Standard Mode (`./zw stubs`)**: Shows "high severity" stubs (naked returns, empty bodies, `not_implemented`).
    * **Paranoid Mode (`./zw stubs --severity low`)**: Also shows potential stubs that look like guard clauses (e.g., `if (!x) return nullptr;`). Use this if you suspect a hidden stub.
    * **Clean Mode (`./zw stubs --pattern empty_body`)**: Only shows functions with physically empty braces `{ }`. This has the highest precision for "gutted" functions.
    * **Purpose**: For identifying missing implementation points or platform-specific gaps.
6.  **`./zw deps <module_path>`**: **CRITICAL for feature disabling.** Scan ALL files that `#include` headers from a given module directory. Shows which files are in `patches/` (can be modified) vs `webkit/source/` (need new patches). **Always run this BEFORE disabling a CMake feature flag** to avoid cascading "header not found" build errors.
    * `./zw deps Modules/webdatabase` — check WebSQL consumers
    * `./zw deps loader/appcache` — check AppCache consumers
    * `./zw deps NetworkProcess/PrivateClickMeasurement` — check PCM consumers

### Smart Auto-Update
The `zw` tool is now autonomous. It monitors the project's **Git HEAD** and **file modification times (mtime)**. 
- If you pull a new commit or edit a source file, the next `./zw` command will automatically re-index the project in the background before showing results.
- This ensures the Knowledge Graph is never stale, even if you forget to run `update`.

### FFI & Subsystems
We maintain language bridges between Rust, Zig, and C++. To find implementation details, query the `ffi_symbols` table via `./zw ffi`.

## Advanced Tooling (LLVM-Based)
Zawra leverages the LLVM toolchain for performance and accuracy in a multi-language environment.

### 1. LLDB Debugging
**Mandatory**: Use `lldb` for debugging instead of GDB.
- **Why**: LLDB handles massive WebKit binaries significantly faster and is the native debugger for both Rust and Zig.
- **Cross-Language**: LLDB provides superior support for inspecting objects across Rust/C++ and Zig/C++ boundaries.
- **Symbol Resolution (Avoid GNU addr2line)**: Never use legacy GNU `addr2line` for mapping program counter addresses to source lines on debug WebKit builds (which consumes massive RAM and runs single-threaded endlessly). **ALWAYS** use `llvm-symbolizer` instead, e.g.:
  ```bash
  llvm-symbolizer -C -f -e /path/to/libWPEWebKit.so <address>
  ```

### 2. Compilation Database (`compile_commands.json`)
We use a JSON compilation database to provide the LSP (`clangd`) and AI agents with precise compiler flags and include paths.
- **Generation**: Always configure CMake with `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`.
- **Usage**: The root `.clangd` file is configured to skip background indexing for RAM safety, but it uses the compilation database to provide 100% accurate diagnostics for the specific files you open.

### 3. clang-scan-deps
Used for high-speed dependency analysis. In a 5GB codebase, traditional scanning is too slow. CMake and Ninja use `clang-scan-deps` automatically to manage the build graph.

## ⚠️ CRITICAL: Build Cache ⚠️

The entire `webkit/build/` directory is the **build cache**. It contains compiled objects, generated sources, dependency tracking files, and CMake state. A full WebKit rebuild takes **days** on this machine.

- **DO NOT DELETE** the `webkit/build/` directory, ever.
- **DO NOT RUN** `ninja -t clean`, `rm -rf webkit/build`, `ninja clean`, or any equivalent.
- **DO NOT** run commands that invalidate or wipe CMake state.
- The `.gitignore` in the main repo already blocks `webkit/build/`. **DO NOT override this.**
- If a build error claims a file or header is missing or empty, fix the root cause or re-run CMake — **do not** wipe and restart.

## Coding Guidelines

### WebKit Modifications
- **NEVER** commit changes directly to `webkit/source/`. This directory is explicitly untracked because it represents the extracted tarball.
- **ALWAYS** write and mirror any changes to WebKit files in the `patches/webkit/` directory.
- The `patches/webkit/` directory must exactly reflect the target path inside `webkit/source/`.
- For **new WebCore source files** (e.g. `platform/network/zawra/`), also add them to `Source/WebCore/SourcesWPE.txt` and mirror that file to patches.
- The C++ bridge (`ZawraStorageBridge`) lives in `Source/WebCore/platform/network/zawra/` and exposes static methods that call into the Rust FFI layer. Add new bridge methods for any new BrowserDB functionality that WebKit needs to call.

### FFI and Safety
- Maintain strict C-compatible FFI boundaries between Rust/Zig and C++.
- Use `hajr` for low-latency, cross-process data transfer.
- Ensure all Rust code is thread-safe as it runs within WebKit's multi-process architecture.
- FFI functions returning `i32` must use the nsresult constants (`NS_OK = 0`, `NS_ERROR_FAILURE = -2147467259`). C++ compares against -2 for failure — returning raw errno values (e.g. -5 for `WouldBlock`) causes a signal mismatch.
- **Known Sandbox Fallbacks**: When executing within a sandboxed PID namespace, dynamic pidfd lookups (`syscall(434, getppid(), 0)`) will fail with `EINVAL` (errno 22) because `getppid()` returns `0`. The system cleanly falls back to the inherited `ZAWRA_HAJR_PARENT_PIDFD` file descriptor. We are fully aware of this issue; it is currently harmless and has been left as-is, with a planned fix to resolve the warning and optimize the lookup in the future.

### Hajr Trace Ring & Global Sequence Index (GSI)
The trace system lives in `dependencies/hajr/src/trace/`.

**Files:**
- **`trace.zig`**: Core types. `TraceRecord` is 64-byte (one cache line), `TraceRing` is 1024-slot lock-free SPSC. Every record carries:
  - `timestamp_ns` — `CLOCK_MONOTONIC` nanoseconds at write time
  - `ipc_sequence` — per-channel IPC sequence number (from `IpcHeader`)
  - `gsi` — **Global Sequence Index**: a cross-process, globally unique monotonic u64 stamped atomically from a shared-memory counter. This is the primary sort key for the unified timeline — two events from different processes with GSIs 41 and 42 are causally ordered regardless of wall-clock drift.
  - `pid` — OS PID of the writing process (for kernel log correlation)
- **`gsi.zig`**: The shared GSI page. A single `memfd`-backed page containing one `atomic u64`. All processes map the same physical page and call `gsi.next()` → `fetchAdd(1, .acq_rel)`. Bootstrap: root process calls `__hajr_create_gsi_fd()` (C-ABI export in `bindings.zig`) → gets a raw fd → sets `ZAWRA_HAJR_GSI_FD=<fd>` in the env before spawning each child. Children auto-map it inside `trace.init()`.
- **`consumer.zig`**: Background drain thread. Reads slots, writes plain **Trace Event Format JSON** — a `[{"ph","ts","pid","name","args",...}]` array written directly with `std.fmt.bufPrint`. No SDK or library involved. Load the output file at `ui.perfetto.dev` to get the swimlane timeline. Output includes `gsi` in `args` for causal ordering.
- **`mod.zig`**: Public re-exports of `trace`, `consumer`, and `gsi`.
- **`tools/log_stitcher.py`** (in `dependencies/hajr/tools/`): Post-execution offline correlator. Merges the user-space Trace Event Format JSON with `dmesg` kernel logs. Correlates kernel events to user-space PIDs. Sorts the unified output by `(gsi, ts)` — GSI first for causal order, timestamp as tie-breaker for kernel events. Runs `sudo -S dmesg` non-interactively for ring verification.

**Hooks in `bindings.zig`:** `recordFfi()` called after `hajr_ring_write`/`hajr_ring_read`. `IpcTracer.init()` (which also calls `gsi.initFromEnv()`) called once in `__hajr_map_anonymous_ring_ex`.

**Runtime control:**
```bash
# Trace to file (Trace Event Format JSON — load in ui.perfetto.dev)
ZAWRA_HAJR_GSI_FD=<fd> HAJR_TRACE_FILE=/tmp/hajr_trace.json ./zawra-browser

# Trace to stderr (live debug — prefix: [hajr/trace] gsi=N ts=... pid=...)
HAJR_TRACE_FILE="" ./zawra-browser

# Tracing off — zero overhead (default)
./zawra-browser

# Post-run correlation with kernel logs
./dependencies/hajr/tools/log_stitcher.py \
  --user-log /tmp/hajr_trace.json \
  --output stitched.json          # runs sudo dmesg automatically
```

**Stderr output format (with GSI):**
```
[hajr/trace] gsi=0  ts=... pid=1234 event=ring_send    src=net_process  dst=web_process seq=1 len=64
[hajr/trace] gsi=1  ts=... pid=5678 event=ring_recv    src=net_process  dst=web_process seq=1 len=64
[hajr/trace] gsi=2  ts=... pid=5678 event=channel_send src=web_process  dst=net_process seq=2 len=16
[hajr/trace] gsi=3  ts=... pid=1234 event=ring_recv    src=web_process  dst=net_process seq=2 len=16
```
GSI gaps in a process's stream reveal exactly when another process was active between its events.

**Adding new trace points:** Call `trace.IpcTracer.recordFfi(.event_kind, data_len, seq, ring_key, ring_tier)` or `trace.IpcTracer.recordIpc(...)`. The GSI and PID are stamped automatically.


### Build Optimization
- **Linker**: Always use `mold` (`-fuse-ld=mold`) to maximize linking speed and avoid OOM crashes.
- **Concurrency**: Limit Ninja to `-j 2` or `-j 4` on resource-constrained environments.
- **Build Tool**: **ALWAYS** use Ninja (by configuring CMake with `-GNinja` and running compilation via `ninja`). Do **not** use `make` or other generators/build tools.

### z-graphics Window & Display Mapping
- **Display Preservation**: In `z-graphics` (Vulkan/X11), the X11 Display connection must be preserved and reused across `createWindow` and `createSurface` rather than being opened as a temporary local and immediately orphaned.
- **Non-blocking Event Pump**: When creating the X11 window, mapping X11 windows under Sway/Xwayland is asynchronous. Pumping events must be done using a non-blocking check (`XPending(display)`) with a sleep interval rather than a raw blocking `XNextEvent` loop, to prevent hanging the UIProcess main thread on startup.

## Definition of Done
1.  Code follows project style and safety standards.
2.  All WebKit-level changes are mirrored in `patches/webkit/`.
3.  The `tools/setup` utility successfully bootstraps the environment.
4.  MiniBrowser compiles without errors and passes smoke tests.
5.  Documentation (like this file) is updated if architecture changes.

