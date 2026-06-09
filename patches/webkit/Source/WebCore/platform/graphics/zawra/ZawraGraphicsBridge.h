#pragma once

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

#include <wtf/NeverDestroyed.h>
#include <wtf/Noncopyable.h>

namespace WebCore {

class ZawraGraphicsBridge {
    WTF_MAKE_NONCOPYABLE(ZawraGraphicsBridge);
public:
    static ZawraGraphicsBridge& singleton();

    ZawraGraphicsBridge() = default;
    ~ZawraGraphicsBridge();

    bool initialize(void* windowHandle, int width, int height);
    int exportCompositorFD();
    void presentFrame();
    void renderLayer(void* state);

private:
    void* m_surfaceHandle { nullptr };
};

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
