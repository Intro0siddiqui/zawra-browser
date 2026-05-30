# Zawra Browser: OS Agnostic Roadmap

This document outlines the strategy for evolving the Zawra Browser from a Linux-centric WPE port into a truly OS-agnostic engine capable of running on Windows, macOS, and Linux with minimal code changes.

## 1. The Challenge: Beyond Hardware Agnosticism
WPE is successfully **hardware agnostic** because it uses `libwpe` to interface with different GPUs. However, it is not **OS agnostic** because the WPE Port of WebKit is built on the **GLib/GObject** stack, which is native only to Linux.

## 2. Phase 1: Abstracting the Event Loop (The "De-GLib" Initiative)
Currently, Zawra relies on GLib for its main loop and object lifecycle. To be OS agnostic, we must move these to WebKit's native **WTF (Web Template Framework)** abstractions.

- **Tasks**:
    - Replace `GMainLoop` with `WTF::RunLoop`.
    - Replace `GObject` API wrappers with a pure C++ or Rust-based API.
    - **Target**: Ensure `MiniBrowser` can start without `libglib-2.0.so`.

## 3. Phase 2: Cross-Platform IPC (Unified Hajr)
Zawra's performance comes from the **Hajr** ring buffers. These currently use `mmap` and Unix Domain Sockets for the initial handshake.

- **Tasks**:
    - Implement a Windows backend for Hajr using **Shared Memory (CreateFileMapping)** and **Named Pipes**.
    - Implement a macOS backend using **Mach Ports**.
    - Ensure the Rust handshake logic in `src/wpe_glue/init.rs` detects the OS and chooses the appropriate transport.

## 4. Phase 3: The Platform Abstraction Layer (PAL)
We must expand the use of WebKit's **PAL** to hide OS-specific details for Networking and Crypto.

- **Tasks**:
    - **Networking**: Ensure **Z-Net** (Rust) is the primary transport on all OSs, bypassing `libsoup` (Linux) and `NSURLSession` (Apple).
    - **Crypto**: Route all `WebCrypto` calls to the Rust Crypto engine, bypassing `libgcrypt` (Linux) and `CommonCrypto` (Apple).

## 5. Phase 4: Graphics Backends
Leverage the WPE architecture to create non-Linux display backends.

- **Tasks**:
    - **Windows**: Create a `WPEBackend-Windows` that renders to a **DirectX/DXGI** surface.
    - **macOS**: Create a `WPEBackend-macOS` that renders to a **Metal/Layer** surface.

## 6. Summary of Architectural Shifts
| Component | Current (Linux) | Agnostic Target |
| :--- | :--- | :--- |
| **Event Loop** | GLib GMainLoop | WTF::RunLoop |
| **API Layer** | GObject | Rust-FFI / C++ |
| **IPC** | Unix Sockets + Hajr | Named Pipes/Mach + Hajr |
| **Storage** | SQLite + BrowserDB | 100% BrowserDB |
| **Networking** | Soup + Z-Net | 100% Z-Net |

---
*Created on Saturday, May 30, 2026*
