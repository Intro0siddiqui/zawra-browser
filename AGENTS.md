# AGENTS.md

## Project Context
**Zawra Browser** is a highly customized, headful WPE WebKit browser. It replaces standard WebKit subsystems (IPC, Network, Storage) with specialized high-performance components.

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

### 2. Apply WebKit Patches
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

### 1. Behavioral Limits (Strictly Enforced)
*   **NO UNSOLICITED LIBERTIES:** Stop execution and ask user for permission if you encounter missing dependencies, compile blockers, or broken scripts. Do not write unilateral patches.
*   **Submodule changes:** Ask user before modifying code inside `dependencies/`.

### 2. Sandbox & Feature Disabling
*   **Bubblewrap:** Must be disabled in CMake configuration (`-DENABLE_BUBBLEWRAP_SANDBOX=OFF`) to prevent conflicting with Hajr.
*   **WebSQL & AppCache:** Must remain `OFF` in `OptionsWPE.cmake` (replaced by BrowserDB). Always check downstream header consumers using `./zw deps <module>` before editing feature flags.
*   **Build Cache:** Never delete `webkit/build/` or run clean commands. Wiping the cache causes days of recompilation.

### 3. LLVM Debugging
*   Use `lldb` for cross-language (Rust/Zig/C++) debugging.
*   Always map addresses using `llvm-symbolizer` instead of slow legacy GNU `addr2line`.

### 4. Code integrations
*   Never write to `webkit/source/` directly. Put all WebKit patches in `patches/webkit/` matching the source structure.
*   FFI functions returning `i32` must map to `nsresult` (`NS_OK = 0`, `NS_ERROR_FAILURE = -2147467259`).

---

## 🔍 Project Intelligence (`zw` Tool)
Use the unified CLI command `./zw` to map integration boundaries:
*   `./zw find <term>`: Search integration boundary symbols.
*   `./zw read <filename>`: Read C++ file side-by-side with its patch.
*   `./zw patches`: List modified WebKit files.
*   `./zw audit`: Structural graph audit (checks double-listed files).
*   `./zw stubs`: View unimplemented placeholders/stubs.
