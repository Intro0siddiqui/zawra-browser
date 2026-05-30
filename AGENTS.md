# AGENTS.md

## Project Context
**Zawra Browser** is a highly customized, headless WPE WebKit browser. It replaces standard WebKit subsystems (IPC, Network, Storage) with specialized high-performance components.

- **Goal**: Performance-optimized, sandboxed browser for headless environments.
- **IPC**: Handled by **Hajr** (Zig) using lock-free ring buffers.
- **Networking**: Handled by **Z-Net** (Rust) supporting HTTP/3.
- **Storage**: Handled by **BrowserDB** (Rust) for LocalStorage and persistent data.

## Tech Stack
- **Core**: WPE WebKit (C++)
- **IPC Layer**: Zig 0.16.0
- **Network & Storage Layers**: Rust (Cargo)
- **Build System**: CMake, Ninja

## Core Workflows for AI Agents

### 1. WebKit Setup (The Patch System)
We do **not** use a Git submodule for the main WebKit source to avoid repository bloat and "detached HEAD" stress. Instead, we use a custom Rust setup tool.

- **Source Code**: Official WPE WebKit stable releases (Tarball).
- **History**: 0% WebKit history is pulled, saving ~5GB of Git metadata.
- **Patching**: Files in `patches/webkit/` are overlaid onto the official source via `fs_extra::dir::copy` (full file copy, not diffs). Both new files and modified existing files are supported.
- **Patch locations**:
  - `webkit/patches/Source/WebKit/` — WebKit2 layer (network, IPC, build system)
  - `webkit/patches/Source/WebCore/` — WebCore layer (storage bridge, cookie/soup integration)
- **Setup Command**: 
  ```bash
  # Note: The custom setup tool overlays patches onto the WebKit source
  ./webkit/scripts/thermal_build_control.sh
  ```

### 2. Building the Project
- **Step 1: Setup submodules** (BrowserDB, Hajr, Z-Net):
  ```bash
  git submodule update --init --recursive --depth 1
  ```
- **Step 2: Commit submodule changes** (if any):
  ```bash
  # BrowserDB, Z-Net, and Hajr are in the subsystems/ directory
  git -C subsystems/browser-db add -A && git -C subsystems/browser-db commit -m "..."
  git -C subsystems/z-net add -A && git -C subsystems/z-net commit -m "..."
  git -C subsystems/hajr add -A && git -C subsystems/hajr commit -m "..."
  ```
- **Step 3: Compile Subsystems**:
  - Hajr: `cd subsystems/hajr && zig build`
  - Z-Net: `cd subsystems/z-net/rust_net && cargo build --release`
  - BrowserDB: `cd subsystems/browser-db/bindings && cargo build --release`
- **Step 4: Configure & Build WebKit**:
  ```bash
  # Use the thermal controller for safe burst-mode compilation
  ./thermal_build_control.sh
  ```

## ⚠️ CRITICAL: Build Cache Management ⚠️

### Local Cache Git Storage
The WebKit build cache (`webkit/build/`) is **ignored** by the main repository to prevent bloating the remote GitHub repository (GitHub blocks files >100MB). 

To preserve compilation progress while maintaining a clean main history, we use a **dual-repository strategy**:
1.  **Main Repo**: Stores only source code, patches, and configurations. History is kept extremely lean (last 2 commits).
2.  **Cache Repo**: A separate, **local-only** Git repository initialized inside `webkit/build/`.
    -   This repo is used purely for **compressed storage** and **checkpoints**.
    -   **Rule**: Keep only the **last commit** in the cache repo history to save space. Use `git commit --amend` or periodic `git gc`.
    -   To checkpoint your local progress:
        ```bash
        cd webkit/build
        git add .
        git commit -m "Checkpoint: Step X completed"
        ```

### Retention Rules
- **DO NOT DELETE THE BUILD CACHE / `webkit/build` DIRECTORY under any circumstances!**
- **NEVER** run commands that wipe the build cache (e.g. `rm -rf webkit/build`, `ninja clean`, etc.).
- Compiling WebKit from scratch takes days on this machine. Deleting the build cache is a massive setback.
- If a build error claims a file or header is missing or empty, manually fix it or re-run CMake; do not delete the directory.

## Coding Guidelines

### WebKit Modifications
- **NEVER** commit changes directly to `dependencies/WebKit/`.
- **ALWAYS** mirror any changes to WebKit files in the `patches/webkit/` directory.
- The `patches/webkit/` directory must exactly reflect the target path inside `dependencies/WebKit/`.
- For **new WebCore source files** (e.g. `platform/network/zawra/`), also add them to `Source/WebCore/SourcesWPE.txt` and mirror that file to patches.
- The C++ bridge (`ZawraStorageBridge`) lives in `Source/WebCore/platform/network/zawra/` and exposes static methods that call into the Rust FFI layer. Add new bridge methods for any new BrowserDB functionality that WebKit needs to call.

### FFI and Safety
- Maintain strict C-compatible FFI boundaries between Rust/Zig and C++.
- Use `hajr` for low-latency, cross-process data transfer.
- Ensure all Rust code is thread-safe as it runs within WebKit's multi-process architecture.
- FFI functions returning `i32` must use the nsresult constants (`NS_OK = 0`, `NS_ERROR_FAILURE = -2147467259`). C++ compares against -2 for failure — returning raw errno values (e.g. -5 for `WouldBlock`) causes a signal mismatch.

### Build Optimization
- **Linker**: Always use `LLD` (via `DEVELOPER_MODE=ON`) to avoid OOM crashes.
- **Concurrency**: Limit Ninja to `-j 2` or `-j 4` on resource-constrained environments.
- **Build Tool**: **ALWAYS** use Ninja (by configuring CMake with `-GNinja` and running compilation via `ninja`). Do **not** use `make` or other generators/build tools.

## Definition of Done
1.  Code follows project style and safety standards.
2.  All WebKit-level changes are mirrored in `patches/webkit/`.
3.  The `tools/setup` utility successfully bootstraps the environment.
4.  MiniBrowser compiles without errors and passes smoke tests.
5.  Documentation (like this file) is updated if architecture changes.
