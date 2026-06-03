#pragma once

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

#include <wtf/Noncopyable.h>

namespace WebCore {

class ZawraGraphicsBridge {
    WTF_MAKE_NONCOPYABLE(ZawraGraphicsBridge);
public:
    static void initialize(void* windowHandle, int width, int height);
    static int exportCompositorFD();
    static void presentFrame();

private:
    ZawraGraphicsBridge() = delete;
};

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
