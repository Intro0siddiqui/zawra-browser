#include "config.h"
#include "ZawraGraphicsBridge.h"

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
    if (!m_surfaceHandle) {
        if (!ZawraGraphics_Initialize()) {
            return false;
        }
        void* handle = ZawraGraphics_CreateSurface(windowHandle, width, height);
        if (!handle) {
            return false;
        }
        m_surfaceHandle = handle;
        m_compositorWidth = width;
        m_compositorHeight = height;
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
