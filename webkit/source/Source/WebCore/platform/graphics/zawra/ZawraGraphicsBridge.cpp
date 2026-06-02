#include "config.h"
#include "ZawraGraphicsBridge.h"

#include <wtf/NeverDestroyed.h>

namespace WebCore {

ZawraGraphicsBridge& ZawraGraphicsBridge::singleton()
{
    static NeverDestroyed<ZawraGraphicsBridge> bridge;
    return bridge;
}

ZawraGraphicsBridge::ZawraGraphicsBridge()
{
    if (ZawraGraphics_Initialize()) {
        m_surface = ZawraGraphics_CreateSurface(1920, 1080); // Default size, should be dynamic
    }
}

ZawraGraphicsBridge::~ZawraGraphicsBridge()
{
    if (m_surface)
        ZawraGraphics_DestroySurface(m_surface);
}

} // namespace WebCore
