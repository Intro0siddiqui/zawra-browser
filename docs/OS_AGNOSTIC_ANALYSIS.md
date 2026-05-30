# Zawra Browser: OS-Specific vs. Agnostic Analysis

This document provides a technical breakdown of the architectural dependencies within the Zawra Browser project as of May 2026. It analyzes the relationship between the universal browser engine and the platform-specific "glue" that connects it to the operating system.

## 1. Architectural Composition

WebKit (and by extension, Zawra) follows a **Core + Port** architecture. The project is divided into an OS-agnostic core and a series of "Ports" that handle platform-specific integration.

### Source Tree Breakdown (May 2026)
| Component | File Count | Percentage | Description |
| :--- | :--- | :--- | :--- |
| **Agnostic Core** | ~23,620 | **97.2%** | JavaScriptCore, WebCore (HTML/CSS), and WTF. Pure C++. |
| **Linux/WPE Port** | ~614 | **2.5%** | GLib API, Soup Network, WPE Backend, Wayland/Unix IPC. |
| **Foreign Ports** | ~78 | **0.3%** | Win32/Cocoa/CoreFoundation remnants (unused in current build). |
| **Total** | **24,312** | **100%** | The complete source tree for the WPE port. |

## 2. The Role of the "Glue" Layer (The 2.5%)

The **Linux/WPE Port** is the layer currently being compiled. This 2.5% of the codebase is what makes the browser "alive" on an Artix Linux system.

### Key OS-Specific Dependencies
- **GLib/GObject**: Used for the external API layer. This is why tools like `glib-mkenums` are required; they translate C++ enums into the system's GType registration system.
- **WPE (Web Platform for Embedded)**: The bridge between the renderer and the hardware/GPU.
- **Unix Domain Sockets**: The standard transport for IPC (partially replaced by Zawra's **Hajr** ring buffers for higher performance).
- **Z-Net**: Zawra's custom networking engine, which interfaces with Linux-native networking primitives.

## 3. Portability Implications

### Cross-Platform Potential
Because **97.2%** of the project is OS-agnostic, the engine is theoretically portable. However, the current build is locked to the Linux ecosystem due to the WPE Port.

- **To run on Windows**: The 2.5% "glue" would need to be replaced with a **Win32/DirectX Port**.
- **To run on macOS**: The 2.5% "glue" would need to be replaced with a **Cocoa/Metal Port**.

### Why GLib?
The choice of GLib as the primary API glue for Zawra was based on **Headless Efficiency**. GLib provides a stable, lightweight event loop and object model that is ideal for high-throughput server environments, which is the primary target for the Zawra Browser.

## 4. Current Build Requirements
To successfully link the browser on a Linux system, the following system-level "Translation Tools" must be present:
1. **`glib-mkenums`**: Translates C++ headers into GObject type-registration source code.
2. **`glib-compile-resources`**: Bundles icons, shaders, and XML into binary blobs for the executable.

---
*Verified on Friday, May 29, 2026*
