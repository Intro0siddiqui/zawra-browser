#include "config.h"
#include "ZawraGraphicsBridge.h"

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

extern "C" {
    // Declarations for Zig FFI functions from z-graphics
    bool ZawraGraphics_Initialize();
    void* ZawraGraphics_CreateSurface(void* window, unsigned int width, unsigned int height);
    void ZawraGraphics_SwapBuffers(void* handle);
    int ZawraGraphics_ExportSurfaceFD(void* handle);
}

namespace WebCore {

static void* g_surfaceHandle = nullptr;

void ZawraGraphicsBridge::initialize(void* windowHandle, int width, int height)
{
    if (!g_surfaceHandle) {
        ZawraGraphics_Initialize();
        g_surfaceHandle = ZawraGraphics_CreateSurface(windowHandle, width, height);
    }
}

int ZawraGraphicsBridge::exportCompositorFD()
{
    if (g_surfaceHandle) {
        return ZawraGraphics_ExportSurfaceFD(g_surfaceHandle);
    }
    return -1;
}

void ZawraGraphicsBridge::presentFrame()
{
    if (g_surfaceHandle) {
        ZawraGraphics_SwapBuffers(g_surfaceHandle);
    }
}

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
