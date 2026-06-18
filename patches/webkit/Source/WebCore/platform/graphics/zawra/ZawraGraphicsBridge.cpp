#include "config.h"
#include "ZawraGraphicsBridge.h"
#include <cstdio>
#include <unistd.h>
#include <sys/syscall.h>
#include <wtf/Assertions.h>

#define ZLOG(msg, ...) do { \
    fprintf(stderr, "[ZAWRA-BRIDGE pid=%d tid=%d] " msg "\n", getpid(), (int)syscall(SYS_gettid), ##__VA_ARGS__); \
    fflush(stderr); \
} while(0)

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

extern "C" {
    // Declarations for Zig FFI functions from z-graphics
    bool ZawraGraphics_Initialize();
    void* ZawraGraphics_CreateWindow(unsigned int width, unsigned int height);
    void* ZawraGraphics_CreateSurface(void* window, unsigned int width, unsigned int height);
    void ZawraGraphics_SwapBuffers(void* handle);
    int ZawraGraphics_ExportSurfaceFD(void* handle);
    void ZawraGraphics_DestroySurface(void* handle);

    // Compositor FFI functions
    void* ZawraGraphics_CompositorInitialize(void* surface, unsigned int width, unsigned int height);
    bool ZawraGraphics_CompositorRenderLayer(void* state);
    void ZawraGraphics_CompositorDestroy(void* state);
    bool ZawraGraphics_CompositorResize(void* state, unsigned int width, unsigned int height);
}

namespace WebCore {

ZawraGraphicsBridge::~ZawraGraphicsBridge()
{
    if (m_compositorState) {
        Z_Graphics_CompositorDestroy(m_compositorState);
        m_compositorState = nullptr;
        m_surfaceHandle = nullptr;
    } else if (m_surfaceHandle) {
        Z_Graphics_DestroySurface(m_surfaceHandle);
        m_surfaceHandle = nullptr;
    }
}

ZawraGraphicsBridge& ZawraGraphicsBridge::singleton()
{
    static NeverDestroyed<ZawraGraphicsBridge> bridge;
    return bridge.get();
}

bool ZawraGraphicsBridge::initialize(void* windowHandle, int width, int height)
{
    ZLOG("initialize: window=%p, size=%dx%d, existingHandle=%p", windowHandle, width, height, m_surfaceHandle);
    if (!m_surfaceHandle) {
        bool initOk = Z_Graphics_Initialize();
        ZLOG("ZawraGraphics_Initialize returned %s", initOk ? "true" : "false");
        if (!initOk) {
            ZLOG("FATAL: ZawraGraphics_Initialize failed!");
            return false;
        }
        void* actualWindow = windowHandle;
        if (!actualWindow) {
            actualWindow = Z_Graphics_CreateWindow(width, height);
            ZLOG("ZawraGraphics_CreateWindow returned window=%p", actualWindow);
        }
        void* handle = Z_Graphics_CreateSurface(actualWindow, width, height);
        ZLOG("ZawraGraphics_CreateSurface returned handle=%p", handle);
        if (!handle) {
            ZLOG("FATAL: ZawraGraphics_CreateSurface failed!");
            return false;
        }
        m_surfaceHandle = handle;
        m_compositorWidth = width;
        m_compositorHeight = height;

        m_compositorState = Z_Graphics_CompositorInitialize(m_surfaceHandle, width, height);
        ZLOG("ZawraGraphics_CompositorInitialize returned state=%p", m_compositorState);
        if (!m_compositorState) {
            ZLOG("FATAL: ZawraGraphics_CompositorInitialize returned null!");
            Z_Graphics_DestroySurface(m_surfaceHandle);
            m_surfaceHandle = nullptr;
            return false;
        }
    } else if (width != m_compositorWidth || height != m_compositorHeight) {
        ZLOG("Resize requested from %dx%d to %dx%d", m_compositorWidth, m_compositorHeight, width, height);
        if (m_compositorState) {
            bool ok = Z_Graphics_CompositorResize(m_compositorState, width, height);
            ZLOG("ZawraGraphics_CompositorResize returned %s", ok ? "true" : "false");
            if (ok) {
                m_surfaceHandle = *(void**)m_compositorState;
            }
        }
        m_compositorWidth = width;
        m_compositorHeight = height;
    }
    ZLOG("initialize OK: handle=%p, size=%dx%d", m_surfaceHandle, m_compositorWidth, m_compositorHeight);
    return true;
}

int ZawraGraphicsBridge::exportCompositorFD()
{
    ZLOG("exportCompositorFD called: m_surfaceHandle=%p", m_surfaceHandle);
    if (!m_surfaceHandle) {
        ZLOG("FATAL ERROR: exportCompositorFD called but m_surfaceHandle is null!");
        fprintf(stderr, "FATAL ERROR: exportCompositorFD called but m_surfaceHandle is null!\n");
        fflush(stderr);
        RELEASE_ASSERT_NOT_REACHED();
    }
    ZLOG("About to call ZawraGraphics_ExportSurfaceFD, handle=%p", m_surfaceHandle);
    int fd = Z_Graphics_ExportSurfaceFD(m_surfaceHandle);
    ZLOG("exportCompositorFD: handle=%p -> fd=%d", m_surfaceHandle, fd);
    if (fd < 0) {
        ZLOG("FATAL ERROR: ZawraGraphics_ExportSurfaceFD failed: fd=%d", fd);
        fprintf(stderr, "FATAL ERROR: ZawraGraphics_ExportSurfaceFD failed: fd=%d\n", fd);
        fflush(stderr);
        RELEASE_ASSERT_NOT_REACHED();
    }
    return fd;
}

void ZawraGraphicsBridge::presentFrame()
{
    if (m_surfaceHandle) {
        ZLOG("presentFrame: handle=%p, compositorState=%p", m_surfaceHandle, m_compositorState);
        if (m_compositorState) {
            bool rendered = Z_Graphics_CompositorRenderLayer(m_compositorState);
            ZLOG("presentFrame: CompositorRenderLayer returned %s", rendered ? "true" : "false");
        } else {
            Z_Graphics_SwapBuffers(m_surfaceHandle);
            ZLOG("presentFrame: SwapBuffers done");
        }
    }
}

void ZawraGraphicsBridge::renderLayer(void* state)
{
    void* targetState = state ? state : m_compositorState;
    if (m_surfaceHandle && targetState) {
        Z_Graphics_CompositorRenderLayer(targetState);
    }
}

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
