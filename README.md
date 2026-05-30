# Zawra Browser

**Zawra** is a performance-optimized, headless WPE WebKit browser designed for high-throughput and sandboxed environments. It fundamentally re-architects WebKit's core subsystems by replacing standard IPC, Networking, and Storage with specialized, low-latency engines written in Rust and Zig.

## 🏗️ Architecture

Zawra achieves its performance goals by injecting three primary custom components into the WebKit multi-process architecture:

- **IPC Layer (Hajr):** A lock-free ring-buffer implementation written in **Zig**. It replaces traditional socket-based IPC to eliminate context-switching overhead and copy-latency between the UI and Network processes.
- **Network Engine (Z-Net):** A high-performance networking layer written in **Rust**. It provides native HTTP/3 support and bypasses standard WebKit network tasks for direct, efficient data fetching.
- **Storage Backend (BrowserDB):** A custom persistent storage engine written in **Rust**. It redirects LocalStorage and IndexedDB queries to a specialized database, optimized for headless concurrent access.

## 🛠️ The Zawra Setup Tool

To keep the repository lightweight and avoid the complexity of the massive WebKit submodule, Zawra uses a **Source-only Overlay system**. 

Instead of tracking WebKit as a submodule, we use a custom Rust utility to bootstrap the environment. This utility downloads a stable WPE WebKit release and applies the Zawra patches (located in `patches/webkit/`) automatically.

## 🚀 Quick Start

### 1. Prerequisites
- **Rust** (Latest stable)
- **Zig** (0.16.0)
- **CMake** & **Ninja**
- Standard WebKit build dependencies (GLib, GStreamer, WPEBackend-fdo, etc.)

### 2. Initialization
Clone the repository and initialize the custom component submodules with a shallow clone to save space:
```bash
git clone --recursive --depth 1 https://github.com/Intro0siddiqui/zawra-browser.git
cd zawra-browser
```

### 3. Bootstrap WebKit
Zawra pulls **0% of WebKit's Git history** by downloading a stable source snapshot instead of using a submodule. This saves ~5GB of disk space. Run the Rust setup tool to download and patch the WebKit source:
```bash
cargo run --manifest-path tools/setup/Cargo.toml
```

### 4. Build Custom Dependencies
```bash
# Build Hajr (IPC)
(cd dependencies/hajr && zig build)

# Build Z-Net (Network)
(cd dependencies/z-net/rust_net && cargo build --release)

# Build BrowserDB (Storage)
(cd dependencies/Browser-db/bindings && cargo build --release)
```

### 5. Build the Browser
Configure and build the WPE MiniBrowser using "slimming" flags to disable unnecessary subsystems (Video, WebGL, etc.) and reduce binary size:
```bash
cmake -DPORT=WPE \
      -DDEVELOPER_MODE=ON \
      -DCMAKE_CXX_SCAN_FOR_MODULES=OFF \
      -DENABLE_HAJR_SANDBOX=ON \
      -DUSE_ZNET=ON \
      -DUSE_BROWSERDB=ON \
      -DENABLE_VIDEO=OFF \
      -DENABLE_WEB_AUDIO=OFF \
      -DENABLE_WEBGL=OFF \
      -DENABLE_WEB_RTC=OFF \
      -DENABLE_GAMEPAD=OFF \
      -DUSE_GSTREAMER=OFF \
      -GNinja -B WebKitBuild/WPE/Debug dependencies/WebKit

ninja -C WebKitBuild/WPE/Debug MiniBrowser -j 2
```

## 🤖 AI Development
This repository includes an [AGENTS.md](./AGENTS.md) file. If you are using an AI coding assistant (like Cursor, Windsurf, or Gemini CLI), ensure it reads that file first to understand the specific architectural mandates and the patch-based workflow of this project.

## 🗺️ Roadmap
For detailed implementation phases, zero-copy optimizations, and fuzzing strategies, see the [PLAN.md](./PLAN.md).

## 📄 License
Zawra Browser is released under the [LICENSE](./LICENSE) found in the root directory. Portions of the code (WebKit) are subject to their respective BSD/LGPL licenses.
