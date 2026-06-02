#pragma once

#include "ZawraGraphics.h"
#include <wtf/Noncopyable.h>
#include <wtf/UniqueRef.h>

namespace WebCore {

class ZawraGraphicsBridge {
    WTF_MAKE_NONCOPYABLE(ZawraGraphicsBridge);
public:
    static ZawraGraphicsBridge& singleton();

    ZawraGraphicsBridge();
    ~ZawraGraphicsBridge();

    ZawraGraphicsHandle surface() const { return m_surface; }
    int exportFD() const { return ZawraGraphics_ExportSurfaceFD(m_surface); }
    void swap() { ZawraGraphics_SwapBuffers(m_surface); }

private:
    ZawraGraphicsHandle m_surface { nullptr };
};

} // namespace WebCore
