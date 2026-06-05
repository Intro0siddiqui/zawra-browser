#include "config.h"
#include "ZawraGraphicsBridge.h"

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

extern "C" {
    // Declarations for Zig FFI functions from z-graphics
    bool ZawraGraphics_Initialize();
    void* ZawraGraphics_CreateSurface(void* window, unsigned int width, unsigned int height);
    void ZawraGraphics_SwapBuffers(void* handle);
    int ZawraGraphics_ExportSurfaceFD(void* handle);
    bool ZawraGraphics_CompositorRenderLayer(void* state);
}

namespace WebCore {

bool ZawraGraphicsBridge::initialize(void* windowHandle, int width, int height)
{
    static bool s_initialized = false;
    if (!s_initialized) {
        if (!ZawraGraphics_Initialize()) {
            return false;
        }
        s_initialized = true;
    }

    if (m_width != width || m_height != height) {
        void* handle = ZawraGraphics_CreateSurface(windowHandle, width, height);
        if (!handle) {
            return false;
        }
        m_surfaceHandle = handle;
        m_width = width;
        m_height = height;
    }
    return true;
}

int ZawraGraphicsBridge::exportCompositorFD()
{
    if (m_surfaceHandle) {
        return ZawraGraphics_ExportSurfaceFD(m_surfaceHandle);
    }
    return -1;
}

void ZawraGraphicsBridge::presentFrame()
{
    if (m_surfaceHandle) {
        ZawraGraphics_SwapBuffers(m_surfaceHandle);
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
