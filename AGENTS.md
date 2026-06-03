# AGENTS.md

## Project Context
**Zawra Browser** is a highly customized, headless WPE WebKit browser. It replaces standard WebKit subsystems (IPC, Network, Storage) with specialized high-performance components.

- **Goal**: Performance-optimized, sandboxed headful browser (currently testing in headless mode for faster iteration).
- **Graphics**: Render Hardware Interface (RHI) handled by **z-graphics** (Zig) for cross-platform GPU acceleration (Vulkan, Metal, D3D12).
- **IPC & Sandbox**: Handled by **Hajr** (Zig), acting as the "Moriarty Sandbox". It provides hardware-enforced memory isolation (MPK/MTE) via lock-free ring buffers, AND OS-level syscall/filesystem isolation (Seccomp-BPF, Landlock, Seatbelt, Windows Mitigations) directly via `hajr_seal_process()`.
- **Networking**: Handled by **Z-Net** (Zig/Rust) supporting HTTP/3.
- **Storage**: Handled by **BrowserDB** (Rust) for LocalStorage and persistent data.

## Tech Stack
- **Core**: WPE WebKit (C++)
- **IPC Layer**: Zig 0.16.0
- **Network & Storage Layers**: Rust (Cargo)
- **Build System**: CMake, Ninja

## Core Workflows for AI Agents

### ⚠️ Behavioral Guidelines for AI Agents: NEVER TAKE UNSOLICITED LIBERTIES ⚠️
If you encounter a blocked path, a missing dependency (like a completed subsystem not mentioned in the prompt), or a broken script, **DO NOT** unilaterally decide to write a patch, compile the dependency, or drastically alter the build environment on the user's behalf. 

Instead, you MUST:
1. Stop execution.
2. Explain exactly what is broken or missing.
3. Propose a solution to the user.
4. **WAIT for explicit permission** before executing the fix.

Agents must **never** adopt the mindset of "I just went ahead and took the liberty for you and completed the work." Always prioritize the user's explicit consent over proactive execution, especially when it involves Git history, the build system, or undocumented dependencies.

### 1. WebKit Setup (The Patch System)
We do **not** use a Git submodule for the main WebKit source to avoid repository bloat and "detached HEAD" stress. Instead, we use a custom Rust setup tool.

- **Source Code**: Official WPE WebKit stable releases (Tarball).
- **History**: 0% WebKit history is pulled, saving ~5GB of Git metadata.
- **Patching**: Files in `patches/webkit/` are overlaid onto the official source via `fs_extra::dir::copy` (full file copy, not diffs). Both new files and modified existing files are supported.
- **Patch locations**:
  - `patches/webkit/Source/WebKit/` — WebKit2 layer (network, IPC, build system)
  - `patches/webkit/Source/WebCore/` — WebCore layer (storage bridge, cookie/soup integration)
- **Setup Command**: 
  ```bash
  # Note: The custom setup tool overlays patches onto the WebKit source
  ./webkit/scripts/thermal_build_control.sh
  ```

### 3. Git Workflow (PR-Based)
To maintain a stable `master` branch and ensure all code passes continuous integration, agents **MUST** use a Pull Request workflow for all changes:

1. **Branching**: Never commit directly to `master`. Create a descriptive feature branch.
   **⚠️ CRITICAL GIT RULES:**
   - **NEVER** branch directly off `main` if it only contains the `Initial commit` or lacks the `src/` directory. Always branch off the active development branch (e.g., `feat/graphics-pipeline-complete`).
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
- **Step 2: Commit submodule changes** (if any):
  ```bash
  # BrowserDB, Z-Net, and Hajr are in the dependencies/ directory
  git -C dependencies/Browser-db add -A && git -C dependencies/Browser-db commit -m "..."
  git -C dependencies/z-net add -A && git -C dependencies/z-net commit -m "..."
  git -C dependencies/hajr add -A && git -C dependencies/hajr commit -m "..."
  ```
- **Step 3: Compile Subsystems**:
  - Hajr: `cd dependencies/hajr && zig build`
  - Z-Net: `cd dependencies/z-net/rust_net && cargo build --release`
  - BrowserDB: `cd dependencies/Browser-db/bindings && cargo build --release`
- **Step 4: Configure & Build WebKit**:
  ```bash
  # Use the thermal controller for safe burst-mode compilation
  ./thermal_build_control.sh
  ```

## ⚠️ CRITICAL: Build Cache & Artifact Management ⚠️

The entire `webkit/build/` directory is the **build cache**. It contains compiled objects, generated sources, dependency tracking files, and CMake state. A full WebKit rebuild takes **days** on this machine. Preserving and checkpointing these artifacts is the single most important operational concern.

### Dual-Repository Strategy

To preserve compilation progress without polluting the remote, we maintain **two separate Git repos**:

| Repo | Location | Stores | Remote | Purpose |
|------|----------|--------|--------|---------|
| **Main Repo** | `zawra-browser/` | Source, patches, configs only | GitHub (`origin`) | Distributed source history |
| **Cache Repo** | `webkit/build/` | Build artifacts (`.o`, `.dep`, DerivedSources, CMake state) | **NONE (local-only)** | Fast rebuild checkpointing |

### The Cache Repo (`webkit/build/.git`)

A **local-only** Git repository initialized inside the build directory. It is the **sole mechanism for preserving build artifacts** — there is no other backup.

#### What it MUST store (checkpoint these)
- **Compiled object files** (`.o`) — the most expensive artifacts to regenerate
- **Ninja dependency files** (`.ninja_deps`, `.d`, `.dep`) — required for incremental builds
- **DerivedSources** — generated `.h` and `.cpp` files (bindings, forwarding headers)
- **CMake state** — `CMakeCache.txt`, `CMakeFiles/`, `rules.ninja`, `build.ninja`
- **Static libraries** (`.a`) and shared objects (`.so`) — final linked products

Without these artifacts in the cache repo, **ccache is useless** — ccache caches compilation results in `~/.ccache/`, but it only stores the preprocessed compiler output, not the directory structure, dependency files, CMake configuration, or linked binaries the build system needs. The .o files, .dep files, DerivedSources, and CMake state together form a complete snapshot that makes ninja's incremental rebuild work. Checkpointing only source/patch files does nothing — source is already in the main repo or patches directory.

#### What it does NOT store
- Main WebKit source tree (that lives in `webkit/source/` — already in the tarball)
- Patches (live in `patches/webkit/` — already in the main repo)

#### Checkpointing Protocol

Always checkpoint **immediately after a successful build** and **before any destructive operation** (CMake reconfiguration, patching source files, etc.):

```bash
cd webkit/build
git add -A
git commit --amend --no-edit   # amend to keep a single rolling commit
git gc --aggressive --prune=now
```

> [!IMPORTANT]
> Use `--amend` to keep exactly **one commit** in the cache repo. Each amend replaces the previous snapshot. This avoids unbounded disk growth. Run `git gc` after each amend to repack and reclaim space.

### Restoration

If the build cache is wiped or corrupted:

```bash
cd webkit/build

# If the cache repo still exists (only working tree damaged):
git checkout -f HEAD
git gc --aggressive --prune=now

# If the cache repo is intact but build directory needs re-clone:
# (No action needed — cache repo is embedded in webkit/build/)
```

### Retention Rules (ABSOLUTE — these are not guidelines)
- **DO NOT DELETE** the `webkit/build/` directory, ever.
- **DO NOT RUN** `ninja -t clean`, `rm -rf webkit/build`, `ninja clean`, or any equivalent.
- **DO NOT** remove, prune, or garbage-collect the cache repo's objects.
- **DO NOT** run commands that invalidate or wipe CMake state unless the cache repo has been checkpointed first.
- **NEVER** `git push` the cache repo to any remote — its artifact files exceed GitHub's 100 MB file limit.
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
