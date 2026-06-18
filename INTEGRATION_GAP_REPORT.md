# z-graphics <-> WebKit Integration Gap Report

Date: 2026-06-17 (Updated: 2026-06-18)

## Status: z-graphics Issues RESOLVED

The following z-graphics-side issues from the original report have been fixed:

| Issue | Status | Commit |
|-------|--------|--------|
| X11 window not displaying (no event pump) | **FIXED** | `9b2a1a2` |
| Blocking XNextEvent hangs UIProcess on Sway | **FIXED** | `c5eafa2` |
| VkMemoryGetFdInfoKHR anonymous struct segfault | **FIXED** | `c9ff864` |
| exportSurfaceFD crashes on null handle (#5) | **FIXED** | `4bf4622` |
| VkCommandPool leak per command buffer (#4) | **FIXED** | `4bf4622` |
| Brittle `*(void**)m_compositorState` ABI (#8) | **FIXED** | `4bf4622` |

**Remaining issues are on the C++ WebKit side**, not z-graphics.

---

## 1. Current Data Flow (UIProcess → WebProcess → present)

```
PageClientImpl::hostFileDescriptor() [UIProcess]
  → ZawraGraphicsBridge::singleton().initialize(nullptr, w, h)
      → ZawraGraphics_CreateWindow(w, h)               ← UIProcess creates its OWN X11 window
      → ZawraGraphics_CreateSurface(window, w, h)
      → ZawraGraphics_CompositorInitialize(surface, w, h)
  → ZawraGraphicsBridge::singleton().exportCompositorFD()
      → ZawraGraphics_ExportSurfaceFD(surface)
          → vkGetMemoryFdKHR → DMA-BUF fd
  → fd returned to WPE layer (unused today)
```

WebProcess:
```
TextureMapperGL::beginPainting() [WebProcess]
  → (lazy init) ZawraGraphicsBridge::singleton().initialize(nullptr, vw, vh)
      → ZawraGraphics_CreateWindow(vw, vh)    ← WebProcess creates its OWN X11 window (no UIProcess handle!)
      → ZawraGraphics_CreateSurface(window, vw, vh)
  → ZawraGraphics_ExportSurfaceFD(surface)     ← gets fd from WebProcess-local surface
  → import fd into EGL (EXT_image_dma_buf_import) → EGLImage → FBO override
  → WebKit TextureMapper renders into overridden FBO

TextureMapperGL::endPainting()
  → ZawraGraphicsBridge::singleton().presentFrame()
      → ZawraGraphics_CompositorRenderLayer OR SwapBuffers
          → Vulkan submit + vkQueuePresentKHR
```

Net effect: UIProcess and WebProcess **each independently create separate z-graphics surfaces** (and X11 windows) — there is no cross-process surface sharing currently.

---

## 2. Exact Code Locations Where EGL Is Still Required

### 2.1 `TextureMapperGL.cpp` (WebProcess render path)

- Lines ~274–354: `PlatformDisplay::sharedDisplay().eglDisplay()` is required.
- Lines 279–311: `EGL_LINUX_DMA_BUF_EXT`, `EGL_LINUX_DRM_FOURCC_EXT`, `EGL_DMA_BUF_PLANE*` constants and attribute construction.
- Lines 313–335: `platformDisplay.createEGLImage()` + `glEGLImageTargetTexture2DOES`.
- Lines 337–347: `glGenFramebuffers` / `glFramebufferTexture2D` to redirect the render target.
- Lines ~229–241: `glGetIntegerv(GL_FRAMEBUFFER_BINDING, ...)`, all GL state save/restore.
- Lines 33–41: `<EGL/egl.h>`, `<EGL/eglext.h>`, `<GLES2/gl2.h>` includes.

**Conclusion**: EGL is a hard runtime dependency in WebProcess if `TextureMapperGL` is used. WebKit's current accelerated path on WPE still goes through OpenGL ES 2.0 via EGL; there is no Vulkan-native TextureMapper path in this branch.

### 2.2 `ZawraLegacyStubs.cpp`

- Lines 37–182: Full `GLContext` implementation backed by EGL (`eglCreateContext`, `eglCreatePbufferSurface`, `eglMakeCurrent`, `eglSwapBuffers`).
- Lines 125–132: `GLContext::swapBuffers()` calls `eglSwapBuffers()` then `ZawraGraphicsBridge::singleton().presentFrame()`.
- This is a legacy fallback path providing EGL + GLES2 for any WebKit path that still requires `GLContext`.

---

## 3. Should WebProcess Create Its Own z-graphics Surface/Window?

**Short answer: Yes — and it already does, but incorrectly.**

Call chain today:
1. `TextureMapperGL::beginPainting()` → (lazy bridge init)
2. `ZawraGraphicsBridge::initialize(nullptr, ...)` with `nullptr` window handle
3. `lib.zig: ZawraGraphics_CreateSurface(nullptr, ...)` → `linux_vulkan.createSurface(null, ...)`
4. `linux_vulkan.zig:createSurface()` extracts `X11WindowState` via `window` pointer; when `window == null`, goes to headless branch.
5. For **non-null window**, it casts `window` to `*X11WindowState`, reads `display` + `x_window`, then calls `vkCreateXlibSurfaceKHR`.

For `nullptr`, line 878 reports "no window provided, headless mode" — but `ZawraGraphics_CreateSurface` then **vanilla-creates its own Vulkan device, instance, image, render pass, framebuffer** without an actual OS window surface. The Vulkan `VkSurfaceKHR` stays null. The image is used as a dedicated offscreen color attachment.

**Problems:**
- A fresh Vulkan instance/device is created per process, per lazy-init (roughly per WebProcess lifetime). There's no singleton Vulkan device across processes.
- `createWindow()` never participates in this WebProcess path because ZawraGraphicsBridge::initialize passes `nullptr`.
- Both UIProcess and WebProcess end up with disjoint Vulkan devices, disjoint images, and disjoint X11 connections.
- The `hostFileDescriptor` fd shipped from UIProcess is **completely ignored by the consumer** — it is assigned to `WebPage::m_hostFileDescriptor` but never forwarded to the z-graphics bridge.

---

## 4. What Is Missing for a Clean z-graphics Path

### 4.1 Primary: Use UIProcess-Side Surface Handle

**Current gap:**
- `WebPage::m_hostFileDescriptor` (patches/webkit/Source/WebKit/WebProcess/WebPage/WebPage.cpp:614) holds the fd but nothing reading it.
- `TextureMapperGL::beginPainting()` re-creates its own surface.

**Missing code:**
```cpp
// ZawraGraphicsBridge.h
bool initializeFromHostFD(int fd, int width, int height);
int  importSurfaceFD(int fd);  // existing exportCompositorFD can be repurposed

// TextureMapperGL::beginPainting()
// Need:
//   1. Read m_hostFileDescriptor (or other WebPage-side storage)
//   2. Call ZawraGraphicsBridge::singleton().initializeFromHostFD(fd, width, height)
//   3. Skip ZawraGraphics_ExportSurfaceFD + EGL import IF bridge already owns the DMA-BUF
//   4. OR keep the EGL import, but drive fd from WebPage transported IPC
```

**Resize ownership gap:**
- `PageClientImpl::hostFileDescriptor()` is invoked without tracking resize. No resize handshake exists.
- Bridge has `CompositorResize`, but no WebProcess caller drives it. Need:
  - IPC `DidChangeSize` from UIProcess → WebProcess
  - WebProcess calls `ZawraGraphics_CompositorResize()`

### 4.2 Secondary: EGL Import Persistence

**FD lifecycle in TextureMapperGL.cpp (lines ~256–357):**
```cpp
int fd = ZawraGraphicsBridge::singleton().exportCompositorFD();
// ... import into EGLImage ...
close(fd); // line 354
```
`close(fd)` runs unconditionally. If the bridge already owns the process-local handle, exporting it for EGL duplication and then immediately closing it can race with the bridge instance. This is benign for EGL because Mesa duplicates the `dma_buf`, but it's brittle and prevents implementing a non-EGL native path.

### 4.3 Tertiary: Synchronization

- No explicit cross-queue sync is present between WebKit's GL ES context and z-graphics' Vulkan queue.
- `swapBuffers()` / `CompositorRenderLayer()` uses `vkWaitForFences` (synchronize-within-device only) but no VkSemaphore signaled from GL → Vulkan.
- Mesa does internal wsi sync for EGLImage, but for a non-EGL (pure Vulkan) path, explicit semaphore handoff will be required.

### 4.4 Cross-Process Surface Ownership Model Is Undefined

- There is no documented protocol for surface lifecycle (e.g., WebProcess seeing "UIProcess gave me fd N, owns the real image lifetime; I must not re-create the surface on resize if the fd is invalidated").
- `ZawraGraphics_CompositorResize` recreates the surface (line 82–89 in ZawraGraphicsBridge.cpp: `m_surfaceHandle = *(void**)m_compositorState`). The semantics of what happens to old FDs isn't portable. No FD passthrough on resize.

### 4.5 Surface Creation Ordering

- `ZawraGraphics_Initialize()` is a noop (`return true`) in `lib.zig` line 57.
- The Vulkan instance/device is created **inside createSurface**, not in a centralized Initialize call. This means repeated `CreateSurface` calls = repeated Vulkan instance/device allocations.

---

## 5. VK_IMAGE_TILING_LINEAR vs. DRM Format Modifier Negotiation

**Short answer: Neither is used today.**

Current `linux_vulkan.zig` image create (`createSurface`, lines ~882–899):
```zig
.tiling = c.VK_IMAGE_TILING_OPTIMAL,
```
No `VK_IMAGE_TILING_LINEAR` appears anywhere in the current tree.

For the EGLPath:
- TextureMapperGL.cpp hardcodes `DRM_FORMAT_RGBA8888 = 0x41424752` — no modifier enumeration, no `EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT`. The driver falls back to linear interpretation or compiler-defined tiling assumptions.
- No `drmGetFormatModifier`, no `VK_EXT_image_drm_format_modifier` is in z-graphics FFI.

**Verdict:**
- The current `OPTIMAL` tiling works when MESA's amdgpu/intel/radeon driver can nonlinear-tile the image and EGL dma-buf importer knows the modifier. On some AMD APU configurations, OPTIMAL tiling is incompatible with what Mesa's EGL reports, leading to corruption — there is no fallback here.
- A clean path requires one of:
  - Add modifier enumeration in z-graphics (`VK_EXT_image_drm_format_modifier`) and export them alongside the fd.
  - OR switch to `VK_IMAGE_TILING_LINEAR` for an interim compatibility shim (easy but slower GPU memory layout).
  - OR bypass EGL completely with a native Vulkan `VkDevice` → `VkImage` import path and render directly into the DMA-BUF without requiring EGLImage at all.

---

## 6. Recommended Minimal Patch Plan (C++ WebKit Side)

### S1: Wire the UIProcess FD into the WebProcess Triangle (1–2 days)

1. Extend `ZawraGraphicsBridge` API:
   - `initializeFromHostFD(int fd, int width, int height)` — satisfies `hostFileDescriptor` contract.
   - `compositorFD() const` accessor for TextureMapperGL to query the bridge's own fd when host fd is unavailable (debug fallback).

2. In `PageClientImpl::hostFileDescriptor()`:
   - Keep existing surface creation (UIProcess surface is needed as primary owner for WPE's present path anyway).
   - Export fd → pass into IPC parameters to WebProcess.

3. In `WebPage.cpp`:
   - On receiving `hostFileDescriptor` in parameters, call `ZawraGraphicsBridge::singleton().initializeFromHostFD(parameters.hostFileDescriptor, viewWidth, viewHeight)`.

4. In `TextureMapperGL::beginPainting()`:
   - If bridge is already initialized via host fd, DON'T re-export; just bind the pre-existing surface handle directly (perhaps via existing EGLImage path or prepare a direct VulkanSubpass path).
   - Fallback to current `exportCompositorFD()` only if host fd not received.

5. Handle resize:
   - When view size changes in UIProcess, send IPC resize event to WebProcess.
   - WebProcess calls `ZawraGraphics_CompositorResize`.
   - Re-export new fd and emit downstream.

### S2: Eliminate WebProcess-Side Re-instantiation (1 day)

- Remove the lazy `ZawraGraphicsBridge::singleton().initialize(nullptr, ...)` call from `TextureMapperGL::beginPainting()`.
- Bridge should only be initialized once (UIProcess side before WebProcess begins rendering), or WebProcess must call via public `setHostSurfaceFD`.

### S3: Add DRM Modifier Export to z-graphics (Linux) (1–2 days)

- In `linux_vulkan.createSurface`: 
  - Query `VkDrmFormatModifierPropertiesEXT` via `vkGetPhysicalDeviceFormatProperties2KHR` for `VK_FORMAT_R8G8B8A8_UNORM`.
  - Enumerate modifiers; pick one (prefer LINEAR if EGL import requires it, else pre-tiled).
  - Export modifier counts/values via new `ZawraGraphics_GetSurfaceModifiers()` FFI or embed in `exportSurfaceFD()` (could return a small struct via copy rather than raw fd, but that's an ABI change; better to add a separate `exportDmaBufWithModifier` call).

- In `TextureMapperGL.cpp`:
  - Use `EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT` / `_HI_EXT` instead of hardcoded 0.

### S4 (Long-term): Drop EGL-Import Path Entirely

- Add a Vulkan-native TextureMapper (`TextureMapperVulkan.cpp`) in WebKit that subclasses `TextureMapper` and renders directly with `vkQueueSubmit`, bypassing GL entirely.
- WebKit compositing thread in WebProcess talks directly to the shared `z-graphics` Vulkan device. Present is a single `vkQueuePresentKHR` to a surface that is the UIProcess-owned swapchain.
- UIProcess still owns the X11 window and VkSurfaceKHR. WebProcess imports the `VkDeviceMemory` FD to create a `VkImage` on its own device, renders into it, then synchronizes via `VkSemaphore` exported via `VK_KHR_external_semaphore_fd`.

---

## 7. Recommended Long-term Transition Plan

| Phase | Goal | Key Changes |
|-------|------|-------------|
| **P1** | Stable bridge with UIProcess-owned surface | Minimal plan above (S1–S3). Get rid of WebProcess's independent X11/Vulkan instance creation. Keep EGL path for compatibility. |
| **P2** | Replace EGL-import fallback with explicit DMA-BUF import | TextureMapperGL stops EGL-image dynamics; uses only a plain Vulkan import of the DMA-BUF fd. GL exits the render-to-screen path; only used for texturing if needed, or entirely removed once TextureMapperVulkan targets the bridge's VkImage. |
| **P3** | Vulkan-native TextureMapper | Implement `TextureMapperVulkan` in WebKit. Dispose of GL context entirely in WebProcess render thread. Expose `VkDevice`/`VkPhysicalDevice` from z-graphics via additional FFI so WebKit's pipeline can bind into a shared Vulkan queue rather than import-as-image only. |
| **P4** | Single-process Vulkan via Graphics Spawn | Move WebKit's compositor to a single process with GPU-thread-bound scheduling, shrink IPC surface. UIProcess only owns the X11 window + swapchain; WebProcess render submits into a ringbuffer of imported images. Remove `ZawraGraphicsBridge` singleton and replace with a PROCESS-LOCAL handle-per-frame model. |

---

## 8. Risk Summary

| Risk | Severity | Status | Notes |
|------|----------|--------|-------|
| WebProcess currently creates its own X11 window in hidden path | High | **OPEN** | Multiple X11 connections + windows; on Sway/Xwayland this duplicates surfaces. |
| `hostFileDescriptor` fd is delivered but never consumed | High | **OPEN** | Core pipe broken; WebProcess today does not use the UIProcess surface. |
| EGL required at runtime in WebProcess | High | **OPEN** | Undermines z-graphics's platform-agnostic goal; blocks headless-only builds. |
| `VK_IMAGE_TILING_OPTIMAL` + no modifier negotiation | Medium | **OPEN** | Works on most (Mesa) drivers; can fail silently on tiling-conservative or cross-GPU dma-buf sharing. |
| Cross-queue sync (GL ↔ Vulkan) undefined | Medium | **OPEN** | Works today because Mesa performs internal sync on EGLImage import; breaks when removing EGL. |
| Resize ownership undefined | Medium | **OPEN** | CompositorResize + fd passthrough not implemented in WebKit code. |
| X11 window not displaying / MapNotify hang | High | **FIXED** | `9b2a1a2`, `c5eafa2` — event pump + non-blocking wait |
| exportSurfaceFD crash on null handle | High | **FIXED** | `4bf4622` — null guard at FFI boundary |
| VkCommandPool leak | Medium | **FIXED** | `4bf4622` — pool destroyed after submit |
| Brittle `*(void**)m_compositorState` ABI | Medium | **FIXED** | `4bf4622` — explicit `ZawraGraphics_CompositorGetSurfaceHandle` accessor |
| VkMemoryGetFdInfoKHR struct layout crash | High | **FIXED** | `c9ff864` — proper extern struct |
| Surface lifetime tied to bridge singleton, not WPEViewID | Low | **OPEN** | Singleton held forever; no per-page cleanup. Should be per-page or per-rendering-target. |
| Re-instantiating Vulkan device lazily per lazy-init | Low | **OPEN** | Wasteful; not fatal. |

---

## 9. z-graphics FFI Reference (Current)

| FFI Export | Purpose |
|------------|---------|
| `ZawraGraphics_Initialize` | No-op, returns true |
| `ZawraGraphics_CreateWindow(w, h)` | Creates X11 window, pumps MapNotify, returns `X11WindowState*` |
| `ZawraGraphics_CreateSurface(window, w, h)` | Creates Vulkan instance/device/image/renderpass, returns `VulkanSurface*` |
| `ZawraGraphics_DestroySurface` | Cleans up all Vulkan resources + X11 display |
| `ZawraGraphics_SwapBuffers` | Present via `vkQueuePresentKHR` |
| `ZawraGraphics_ExportSurfaceFD` | Export DMA-BUF fd via `vkGetMemoryFdKHR` (with null guards) |
| `ZawraGraphics_CompositorInitialize` | Init compositor state (pipeline + vertex buffer) |
| `ZawraGraphics_CompositorRenderLayer` | Record + submit draw commands |
| `ZawraGraphics_CompositorResize` | Destroy + recreate surface on resize |
| `ZawraGraphics_CompositorGetSurfaceHandle` | **NEW** — Explicit accessor for surface handle (replaces `*(void**)m_compositorState`) |
| `ZawraGraphics_CreateBuffer` | Allocate GPU buffer (vertex/index/uniform) |
| `ZawraGraphics_BeginCommandBuffer` | Allocate command pool + buffer, begin recording |
| `ZawraGraphics_SubmitCommandBuffer` | End recording, submit, wait fence, **destroy pool** (leak fixed) |

---

## 10. Raw Source References

- `patches/webkit/Source/WebKit/UIProcess/API/wpe/PageClientImpl.cpp:63-74` — UIProcess surface creation + fd export
- `patches/webkit/Source/WebKit/WebProcess/WebPage/WebPage.cpp:614` — fd received but never consumed
- `patches/webkit/Source/WebCore/platform/graphics/texmap/TextureMapperGL.cpp:217-363` — WebProcess EGL-import render path
- `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraGraphicsBridge.cpp:51-92` — Bridge init / resize logic
- `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraGraphicsBridge.h:18-23` — Public API (notably missing `initializeFromHostFD`)
- `patches/webkit/Source/WebCore/platform/graphics/zawra/ZawraLegacyStubs.cpp:37-182` — EGL + GLContext fallback stub
- `dependencies/z-graphics/src/linux_vulkan.zig` — X11 windowing + Vulkan backend (all fixes applied)
- `dependencies/z-graphics/src/lib.zig` — FFI dispatch layer
- `dependencies/z-graphics/src/webkit_compositor.zig` — Compositor state + `ZawraGraphics_CompositorGetSurfaceHandle`
