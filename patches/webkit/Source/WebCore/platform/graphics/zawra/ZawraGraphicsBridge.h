#pragma once

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

#include <cstdint>
#include <wtf/NeverDestroyed.h>
#include <wtf/Noncopyable.h>

struct ZawraGraphicsDMABufInfo {
    int fd { -1 };
    uint32_t width { 0 };
    uint32_t height { 0 };
    uint32_t stride { 0 };
    uint32_t offset { 0 };
    union {
        uint32_t drm_format { 0 };
        uint32_t format;
    };
    union {
        uint64_t drm_modifier { 0 };
        uint64_t modifier;
    };
};

extern "C" {
bool ZG_ExportSurfaceDMABuf(void* surface, void* info);
}

namespace WebCore {

using ZawraGraphicsDMABufInfo = ::ZawraGraphicsDMABufInfo;

class ZawraGraphicsBridge {
    WTF_MAKE_NONCOPYABLE(ZawraGraphicsBridge);
public:
    static ZawraGraphicsBridge& singleton();

    ZawraGraphicsBridge() = default;
    ~ZawraGraphicsBridge();

    bool initialize(void* windowHandle, int width, int height);
    int exportCompositorFD();
    bool exportDMABuf(ZawraGraphicsDMABufInfo* info);
    int compositorWidth() const { return m_compositorWidth; }
    int compositorHeight() const { return m_compositorHeight; }
    void presentFrame();
    void renderLayer(void* state);

private:
    void* m_surfaceHandle { nullptr };
    void* m_compositorState { nullptr };
    int m_compositorWidth { 0 };
    int m_compositorHeight { 0 };
};

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
