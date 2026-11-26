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
bool ZG_BindWpeDMABuf(void* surface, int fd, uint32_t width, uint32_t height);
int ZG_ExportSurfaceFD(void* handle);
void* ZG_CreateFramebuffer(void* handle, void* colorTexture, uint32_t width, uint32_t height, void* depthStencilRb);
void ZG_DestroyFramebuffer(void* handle, void* fb);
void* ZG_CreateRenderbuffer(void* handle, uint32_t format, uint32_t width, uint32_t height);
void ZG_DestroyRenderbuffer(void* handle, void* rb);
bool ZG_UploadTextureRegion(void* surfacePtr, void* texturePtr, int32_t x, uint32_t y, uint32_t width, uint32_t height, const uint8_t* data, uint64_t dataLen, uint32_t rowStride, uint32_t srcOffsetX, uint32_t srcOffsetY);
bool ZG_SetTextureParams(void* handle, void* texture, uint32_t minFilter, uint32_t magFilter, uint32_t wrapS, uint32_t wrapT);
uint32_t ZG_GetDeviceProperty(void* handle, uint32_t propId);
void* ZG_CreateShaderModule(void* handle, const uint32_t* code, size_t codeSize);
void ZG_DestroyShaderModule(void* handle, void* module);
void ZG_CmdClearAttachments(void* cmd, bool color, bool depth, bool stencil, float r, float g, float b, float a);
void ZG_CmdCopyTexture(void* cmd, void* src, void* dst);
void* ZG_ImportTextureFD(void* handle, int fd, const void* desc);
void* ZG_ImportTextureDMABuf(void* handle, const ZawraGraphicsDMABufInfo* info);
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
    bool initializeFromHostFD(int fd, uint32_t width, uint32_t height);
    int exportCompositorFD();
    bool hasCompositor() const { return m_surfaceHandle != nullptr || m_hostFD >= 0; }
    bool exportDMABuf(ZawraGraphicsDMABufInfo* info);
    int compositorWidth() const { return m_compositorWidth; }
    int compositorHeight() const { return m_compositorHeight; }
    int hostFD() const { return m_hostFD; }
    void presentFrame();
    void renderLayer(void* state);

private:
    void* m_surfaceHandle { nullptr };
    void* m_compositorState { nullptr };
    int m_compositorWidth { 0 };
    int m_compositorHeight { 0 };
    int m_hostFD { -1 };
};

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
