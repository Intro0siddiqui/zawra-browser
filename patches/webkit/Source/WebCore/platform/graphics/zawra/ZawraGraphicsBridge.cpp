#include "config.h"
#include "ZawraGraphicsBridge.h"
#include <cstdio>
#include <unistd.h>
#include <sys/syscall.h>

#define ZLOG(msg, ...) do { \
    fprintf(stderr, "[ZAWRA-BRIDGE pid=%d tid=%d] " msg "\n", getpid(), (int)syscall(SYS_gettid), ##__VA_ARGS__); \
    fflush(stderr); \
} while(0)

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

extern "C" {
    // Declarations for Zig FFI functions from z-graphics
    bool ZawraGraphics_Initialize();
    void* ZawraGraphics_CreateSurface(void* window, unsigned int width, unsigned int height);
    void ZawraGraphics_SwapBuffers(void* handle);
    int ZawraGraphics_ExportSurfaceFD(void* handle);
    void ZawraGraphics_DestroySurface(void* handle);
    bool ZawraGraphics_CompositorRenderLayer(void* state);
}

namespace WebCore {

ZawraGraphicsBridge::~ZawraGraphicsBridge()
{
    if (m_surfaceHandle) {
        ZawraGraphics_DestroySurface(m_surfaceHandle);
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
        bool initOk = ZawraGraphics_Initialize();
        ZLOG("ZawraGraphics_Initialize returned %s", initOk ? "true" : "false");
        if (!initOk) {
            ZLOG("FATAL: ZawraGraphics_Initialize failed!");
            return false;
        }
        void* handle = ZawraGraphics_CreateSurface(windowHandle, width, height);
        ZLOG("ZawraGraphics_CreateSurface returned handle=%p", handle);
        if (!handle) {
            ZLOG("FATAL: ZawraGraphics_CreateSurface failed!");
            return false;
        }
        m_surfaceHandle = handle;
        m_compositorWidth = width;
        m_compositorHeight = height;
    }
    ZLOG("initialize OK: handle=%p, size=%dx%d", m_surfaceHandle, m_compositorWidth, m_compositorHeight);
    return true;
}

int ZawraGraphicsBridge::exportCompositorFD()
{
    ZLOG("exportCompositorFD called: m_surfaceHandle=%p", m_surfaceHandle);
    if (m_surfaceHandle) {
        ZLOG("About to call ZawraGraphics_ExportSurfaceFD, handle=%p", m_surfaceHandle);
        int fd = ZawraGraphics_ExportSurfaceFD(m_surfaceHandle);
        ZLOG("exportCompositorFD: handle=%p -> fd=%d", m_surfaceHandle, fd);
        return fd;
    }
    ZLOG("exportCompositorFD: no surface handle");
    return -1;
}

void ZawraGraphicsBridge::presentFrame()
{
    if (m_surfaceHandle) {
        ZLOG("presentFrame: handle=%p", m_surfaceHandle);
        ZawraGraphics_SwapBuffers(m_surfaceHandle);
        ZLOG("presentFrame: SwapBuffers done");
    }
}

void ZawraGraphicsBridge::renderLayer(void* state)
{
    if (m_surfaceHandle && state) {
        ZawraGraphics_CompositorRenderLayer(state);
    }
}

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
