#pragma once

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

#include <wtf/Noncopyable.h>

namespace WebCore {

class ZawraGraphicsBridge {
    WTF_MAKE_NONCOPYABLE(ZawraGraphicsBridge);
public:
    ZawraGraphicsBridge() = default;
    ~ZawraGraphicsBridge() = default;

    bool initialize(void* windowHandle, int width, int height);
    int exportCompositorFD();
    void presentFrame();
    void renderLayer(void* state);

private:
    void* m_surfaceHandle { nullptr };
};

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
