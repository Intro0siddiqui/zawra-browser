# z-graphics <-> WebKit Integration Gap Report

> **Last Updated:** 2026-11-23  
> **Status:** Phase 1 (DMA-BUF handle alignment) & Phase 2 (8 new RHI Exports) **100% COMPLETED** in `z-graphics`.  
> **Primary Remaining Gap:** C++ WebKit side: `ZawraGraphicsBridge.h` declarations (Phase 3), WebProcess consumption of `m_hostFileDescriptor`, and C++ GL file patches (Phase 4).

---

## 1. Executive Summary & Implementation Status

All Zig-side RHI primitives in [`dependencies/z-graphics/src/`](file:///home/intro/spectre-enviroment/browser/zawra-browser/dependencies/z-graphics/src/) are implemented and verified via automated smoke tests (`zig build test`, passing in 3.2s).

```
┌────────────────────────────────────────────────────────┐
│             z-graphics RHI Implementation Status       │
├───────────────────────┬──────────────┬─────────────────┤
│ Status                │ Item Count   │ Percentage      │
├───────────────────────┼──────────────┼─────────────────┤
│ COMPLETED             │ 13           │ 56.5%           │
│ PARTIAL / IN-PROGRESS │ 5            │ 21.7%           │
│ REMAINING / FUTURE    │ 5            │ 21.7%           │
├───────────────────────┼──────────────┼─────────────────┤
│ TOTAL AUDITED         │ 23           │ 100.0%          │
└───────────────────────┴──────────────┴─────────────────┘
```

### Fixed / Completed z-graphics Issues:
| Feature / Fix | Status | Location | Evidence |
|---|:---:|---|---|
| X11 window not displaying (no event pump) | **FIXED** | `src/platform/linux_x11.zig` | Commit `9b2a1a2` |
| Blocking XNextEvent hangs UIProcess on Sway | **FIXED** | `src/platform/linux_x11.zig` | Commit `c5eafa2` |
| VkMemoryGetFdInfoKHR anonymous struct segfault | **FIXED** | `src/vulkan.zig` | Commit `c9ff864` |
| exportSurfaceFD crashes on null handle | **FIXED** | `src/lib.zig` | Commit `4bf4622` |
| VkCommandPool leak per command buffer | **FIXED** | `src/vulkan.zig` | Commit `4bf4622` |
| Brittle `*(void**)m_compositorState` ABI | **FIXED** | `src/webkit_compositor.zig` | Explicit accessor `ZG_CompositorGetSurfaceHandle` |
| DMA-BUF Handle Type Alignment (Bug 1) | **FIXED** | `src/vulkan.zig:2235-2240` | Exports with `VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT` |
| 4x MSAA & Compute Pipelines | **COMPLETED** | `src/vulkan.zig:2264, 3523` | Tested in `smoke_test.zig:1110-1150` |
| Multiple Render Targets (MRT) & Stencil | **COMPLETED** | `src/vulkan.zig:3190` | 4-attachment pipeline in `smoke_test.zig:1200-1250` |
| Wayland Direct Present | **COMPLETED** | `src/platform/linux_wayland.zig` | Direct XDG shell surface presentation |
| **Phase 2.1 Per-Texture Framebuffers** | **COMPLETED** | `src/lib.zig:972`, `vulkan.zig:6648` | `ZG_CreateFramebuffer`, `ZG_DestroyFramebuffer` |
| **Phase 2.2 Renderbuffer API** | **COMPLETED** | `src/lib.zig:959` | `ZG_CreateRenderbuffer`, `ZG_DestroyRenderbuffer` |
| **Phase 2.3 Sub-Rectangle Texture Upload** | **COMPLETED** | `src/lib.zig:295` | `ZG_UploadTextureRegion` with row pitch offset |
| **Phase 2.4 Runtime Texture Parameter Changes** | **COMPLETED** | `src/lib.zig:254` | `ZG_SetTextureParams` (Linear/Nearest, Clamp/Repeat) |
| **Phase 2.5 GPU Device Properties Query** | **COMPLETED** | `src/lib.zig:949` | `ZG_GetDeviceProperty` (`maxImageDimension2D`, NPOT) |
| **Phase 2.6 Dynamic Shader Module Lifecycle** | **COMPLETED** | `src/lib.zig:553-570` | `ZG_CreateShaderModule`, `ZG_CreatePipelineFromShaders` |
| **Phase 2.7 Clear Attachments with Buffer Mask**| **COMPLETED** | `src/lib.zig:171`, `vulkan.zig:3190` | `ZG_CmdClearAttachments` |
| **Phase 2.8 Copy Texture Region** | **COMPLETED** | `src/lib.zig:517` | `ZG_CmdCopyTexture` (64-byte pixel copy verified) |

---

## 2. Current Cross-Process Data Flow

```
UIProcess:
  PageClientImpl::hostFileDescriptor()
    → ZawraGraphicsBridge::singleton().initialize(nullptr, w, h)
        → ZG_CreateWindow(w, h)
        → ZG_CreateSurface(window, w, h)
        → ZG_CompositorInitialize(surface, w, h)
    → ZawraGraphicsBridge::singleton().exportCompositorFD()
        → ZG_ExportSurfaceFD(surface) → DMA-BUF FD exported
    → Sent via IPC to WebProcess (WebPageCreationParameters)

WebProcess:
  WebPage::WebPage()
    → Stored in m_hostFileDescriptor [WebPage.cpp:726]
    → [GAP]: Currently unread! Never forwarded to ZawraGraphicsBridge

  TextureMapperGL::beginPainting() [Fallback]
    → (lazy init) ZawraGraphicsBridge::singleton().initialize(nullptr, vw, vh)
        → WebProcess vanilla-creates its OWN Vulkan device, instance, and surface
    → ZG_ExportSurfaceFD(surface) from WebProcess-local surface
    → Import FD into EGL (EXT_image_dma_buf_import) → EGLImage → FBO
    → WebKit TextureMapper renders into overridden FBO
```

---

## 3. The Core Remaining Gap: WebProcess Host FD Consumption

### 3.1 Problem Statement
1. **Unread Host FD**: `WebPage.cpp:726` receives `m_hostFileDescriptor` from the UIProcess, but WebProcess never consumes it.
2. **Duplicate Vulkan Devices & Windows**: WebProcess initialization performs a lazy setup of `ZawraGraphicsBridge`, spinning up an independent Vulkan instance rather than binding to the parent's exported DMA-BUF handle.
3. **WebKit 2.54.3 Modernization**: WPE WebKit 2.54.3 has completely replaced the legacy `TextureMapperGL` and Cairo 2D backends with native **Google Skia (`USE_SKIA=ON`)** and **native Vulkan (`USE_VULKAN=ON` via `volk::volk`)** under the `WPEPlatform` API (`ENABLE_WPE_PLATFORM=ON`). The pre-2.54 OpenGL classes (`BitmapTextureGL.cpp`, `TextureMapperShaderProgram.cpp`) have been completely removed.

### 3.2 Solution Steps (P0 / P1 Engineering Focus)
1. **Extend `ZawraGraphicsBridge.h` (Phase 3)**:
   ```cpp
   bool initializeFromHostFD(int fd, uint32_t width, uint32_t height);
   ```
   Add declarations for all 8 Phase 2 RHI functions and texture/buffer/shader exports already implemented in `lib.zig`.
2. **Wire WebPage Host FD**:
   In `WebPage.cpp`, pass `m_hostFileDescriptor` to `ZawraGraphicsBridge::singleton().initializeFromHostFD(...)`.
3. **Bind Directly to z-graphics Viewport Quad**:
   Have WebKit's Skia/Vulkan pipeline export its rendered frame via DMA-BUF, which `z-graphics` imports directly into `wpe_texture` without intermediate offscreen blits or separate swapchains.

---

## 4. Phase 2 RHI Exports Reference (Implemented in `lib.zig`)

The following 8 RHI functions were added to `src/lib.zig` and `src/vulkan.zig`, providing full coverage for WebKit's TextureMapper requirements:

```zig
// 1. Framebuffer Management
export fn ZG_CreateFramebuffer(
    handle: ZawraGraphicsHandle,
    colorAttachment: ZawraGraphicsTexture,
    width: u32,
    height: u32,
    depthStencilAttachment: ?ZawraGraphicsTexture,
) ?ZawraGraphicsHandle;

export fn ZG_DestroyFramebuffer(
    handle: ZawraGraphicsHandle,
    fb: ZawraGraphicsHandle,
) void;

// 2. Renderbuffer Management
export fn ZG_CreateRenderbuffer(
    handle: ZawraGraphicsHandle,
    format: u32,
    width: u32,
    height: u32,
) ?ZawraGraphicsHandle;

export fn ZG_DestroyRenderbuffer(
    handle: ZawraGraphicsHandle,
    rbo: ZawraGraphicsHandle,
) void;

// 3. Sub-Rectangle Texture Upload (with Stride & Pitch)
export fn ZG_UploadTextureRegion(
    handle: ZawraGraphicsHandle,
    texture: ZawraGraphicsTexture,
    x: i32,
    y: i32,
    width: u32,
    height: u32,
    data: ?*const anyopaque,
    dataLen: usize,
    rowStride: u32,
    srcOffsetX: u32,
    srcOffsetY: u32,
) bool;

// 4. Runtime Texture Parameter Changes
export fn ZG_SetTextureParams(
    handle: ZawraGraphicsHandle,
    texture: ZawraGraphicsTexture,
    minFilter: u32,
    magFilter: u32,
    wrapS: u32,
    wrapT: u32,
) bool;

// 5. GPU Device Properties Query
export fn ZG_GetDeviceProperty(
    handle: ZawraGraphicsHandle,
    prop: u32,
) u32;

// 6. Dynamic Shader Modules & Pipeline
export fn ZG_CreateShaderModule(
    handle: ZawraGraphicsHandle,
    spirvCode: ?[*]const u8,
    codeLen: usize,
    stage: u32,
) ?ZawraGraphicsShaderModule;

export fn ZG_CreatePipelineFromShaders(
    handle: ZawraGraphicsHandle,
    vertModule: ZawraGraphicsShaderModule,
    fragModule: ZawraGraphicsShaderModule,
) ?ZawraGraphicsPipeline;

// 7. Clear Attachments with Buffer Mask
export fn ZG_CmdClearAttachments(
    cmd: ZawraGraphicsCommandBuffer,
    color: bool,
    depth: bool,
    stencil: bool,
    r: f32, g: f32, b: f32, a: f32,
) void;

// 8. Copy Texture Region
export fn ZG_CmdCopyTexture(
    cmd: ZawraGraphicsCommandBuffer,
    src: ZawraGraphicsTexture,
    dst: ZawraGraphicsTexture,
) void;
```

---

## 5. Risk & Gap Summary

| Risk / Gap | Severity | Status | Notes |
|---|:---:|:---:|---|
| WebProcess duplicates Vulkan device on lazy init | High | **OPEN (P0)** | Caused by unconsumed `m_hostFileDescriptor`. |
| `m_hostFileDescriptor` ignored in `WebPage.cpp` | High | **OPEN (P0)** | Needs `initializeFromHostFD` in `ZawraGraphicsBridge`. |
| C++ Bridge header missing Phase 2 exports | Medium | **IN PROGRESS (P1)** | All 8 functions exist in `lib.zig`; bridge declarations pending. |
| `BitmapTextureGL.cpp` raw OpenGL calls | High | **RETIRED** | Superseded by WebKit 2.54.3 native Skia/Vulkan migration. |
| `OptionsWPE.cmake` LibEpoxy dependency | Medium | **RETIRED** | Upstream WPEPlatform uses direct DMA-BUF/GBM. |
| DMA-BUF handle type mismatch | High | **FIXED** | Aligned to `VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT`. |
| Missing Renderbuffer / Framebuffer RHI | High | **FIXED** | `ZG_CreateFramebuffer` & `ZG_CreateRenderbuffer` implemented. |
| Sub-rectangle texture upload missing | High | **FIXED** | `ZG_UploadTextureRegion` implemented with row pitch. |
| Missing dynamic shader creation | High | **FIXED** | `ZG_CreateShaderModule` & `ZG_CreatePipelineFromShaders` implemented. |
| Missing clear attachments mask | Medium | **FIXED** | `ZG_CmdClearAttachments` implemented. |
| Missing texture copy region | Medium | **FIXED** | `ZG_CmdCopyTexture` implemented. |
| X11 event pump & non-blocking MapNotify | High | **FIXED** | Resolved in commits `9b2a1a2` and `c5eafa2`. |
