#include "config.h"
#include "ZawraGraphicsBridge.h"
#include <cstdio>
#include <unistd.h>
#include <sys/syscall.h>
#include <wtf/Assertions.h>

#define ZLOG(msg, ...) do { \
    fprintf(stderr, "[ZAWRA-BRIDGE pid=%d tid=%d] " msg "\n", getpid(), (int)syscall(SYS_gettid), ##__VA_ARGS__); \
    fflush(stderr); \
} while(0)

#if OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)

extern "C" {
    // Declarations for Zig FFI functions from z-graphics
    bool ZG_Initialize();
    void* ZG_CreateSurface(void* window, unsigned int width, unsigned int height);
    int ZG_ExportSurfaceFD(void* handle);
    bool ZG_ExportSurfaceDMABuf(void* surface, void* info);
    void ZG_DestroySurface(void* handle);

    // Compositor FFI functions
    void* ZG_CompositorInitialize(void* surface, unsigned int width, unsigned int height);
    bool ZG_CompositorRenderLayer(void* state);
    void ZG_CompositorDestroy(void* state);
    bool ZG_CompositorResize(void* state, unsigned int width, unsigned int height);
}

namespace WebCore {

ZawraGraphicsBridge::~ZawraGraphicsBridge()
{
    if (m_compositorState) {
        ZG_CompositorDestroy(m_compositorState);
        m_compositorState = nullptr;
        m_surfaceHandle = nullptr;
    } else if (m_surfaceHandle) {
        ZG_DestroySurface(m_surfaceHandle);
        m_surfaceHandle = nullptr;
    }
}

ZawraGraphicsBridge& ZawraGraphicsBridge::singleton()
{
    static NeverDestroyed<ZawraGraphicsBridge> bridge;
    return bridge.get();
}

bool ZawraGraphicsBridge::initializeFromHostFD(int fd, uint32_t width, uint32_t height)
{
    ZLOG("initializeFromHostFD: fd=%d, size=%ux%u", fd, width, height);
    if (fd < 0) {
        ZLOG("FATAL: initializeFromHostFD called with invalid fd=%d", fd);
        return false;
    }
    m_hostFD = fd;
    m_compositorWidth = static_cast<int>(width);
    m_compositorHeight = static_cast<int>(height);

    bool initOk = ZG_Initialize();
    ZLOG("ZG_Initialize returned %s", initOk ? "true" : "false");
    if (!initOk) {
        ZLOG("FATAL: ZG_Initialize failed in initializeFromHostFD!");
        return false;
    }

    if (m_surfaceHandle) {
        ZG_BindWpeDMABuf(m_surfaceHandle, fd, width, height);
    }
    return true;
}

bool ZawraGraphicsBridge::initialize(void* windowHandle, int width, int height)
{
    ZLOG("initialize: window=%p, size=%dx%d, existingHandle=%p, hostFD=%d", windowHandle, width, height, m_surfaceHandle, m_hostFD);
    if (m_hostFD >= 0) {
        m_compositorWidth = width;
        m_compositorHeight = height;
        if (!m_surfaceHandle) {
            bool initOk = ZG_Initialize();
            if (!initOk) return false;
            void* handle = ZG_CreateSurface(windowHandle, width, height);
            if (handle) {
                m_surfaceHandle = handle;
                ZG_BindWpeDMABuf(m_surfaceHandle, m_hostFD, width, height);
            }
        }
        return true;
    }
    if (!m_surfaceHandle) {
        bool initOk = ZG_Initialize();
        ZLOG("ZG_Initialize returned %s", initOk ? "true" : "false");
        if (!initOk) {
            ZLOG("FATAL: ZG_Initialize failed!");
            return false;
        }
        void* handle = ZG_CreateSurface(windowHandle, width, height);
        ZLOG("ZG_CreateSurface returned handle=%p", handle);
        if (!handle) {
            ZLOG("FATAL: ZG_CreateSurface failed!");
            return false;
        }
        m_surfaceHandle = handle;
        m_compositorWidth = width;
        m_compositorHeight = height;

        m_compositorState = ZG_CompositorInitialize(m_surfaceHandle, width, height);
        ZLOG("ZG_CompositorInitialize returned state=%p", m_compositorState);
        if (!m_compositorState) {
            ZLOG("FATAL: ZG_CompositorInitialize returned null!");
            ZG_DestroySurface(m_surfaceHandle);
            m_surfaceHandle = nullptr;
            return false;
        }
    } else if (width != m_compositorWidth || height != m_compositorHeight) {
        ZLOG("Resize requested from %dx%d to %dx%d", m_compositorWidth, m_compositorHeight, width, height);
        if (m_compositorState) {
            bool ok = ZG_CompositorResize(m_compositorState, width, height);
            ZLOG("ZG_CompositorResize returned %s", ok ? "true" : "false");
            if (ok) {
                m_surfaceHandle = *(void**)m_compositorState;
            }
        }
        m_compositorWidth = width;
        m_compositorHeight = height;
    }
    ZLOG("initialize OK: handle=%p, size=%dx%d", m_surfaceHandle, m_compositorWidth, m_compositorHeight);
    return true;
}

int ZawraGraphicsBridge::exportCompositorFD()
{
    ZLOG("exportCompositorFD called: m_surfaceHandle=%p, m_hostFD=%d", m_surfaceHandle, m_hostFD);
    if (m_hostFD >= 0) {
        ZLOG("exportCompositorFD: returning shared hostFD=%d", m_hostFD);
        return m_hostFD;
    }
    if (!m_surfaceHandle) {
        ZLOG("FATAL ERROR: exportCompositorFD called but m_surfaceHandle is null!");
        fprintf(stderr, "FATAL ERROR: exportCompositorFD called but m_surfaceHandle is null!\n");
        fflush(stderr);
        RELEASE_ASSERT_NOT_REACHED();
    }
    ZLOG("About to call ZG_ExportSurfaceFD, handle=%p", m_surfaceHandle);
    int fd = ZG_ExportSurfaceFD(m_surfaceHandle);
    ZLOG("exportCompositorFD: handle=%p -> fd=%d", m_surfaceHandle, fd);
    if (fd < 0) {
        ZLOG("FATAL ERROR: ZG_ExportSurfaceFD failed: fd=%d", fd);
        fprintf(stderr, "FATAL ERROR: ZG_ExportSurfaceFD failed: fd=%d\n", fd);
        fflush(stderr);
        RELEASE_ASSERT_NOT_REACHED();
    }
    return fd;
}

bool ZawraGraphicsBridge::exportDMABuf(ZawraGraphicsDMABufInfo* info)
{
    ZLOG("exportDMABuf called: m_surfaceHandle=%p, info=%p", m_surfaceHandle, info);
    if (!m_surfaceHandle) {
        ZLOG("exportDMABuf failed: m_surfaceHandle is null");
        return false;
    }
    if (!info) {
        ZLOG("exportDMABuf failed: info is null");
        return false;
    }
    bool ok = ZG_ExportSurfaceDMABuf(m_surfaceHandle, static_cast<void*>(info));
    ZLOG("exportDMABuf: ZG_ExportSurfaceDMABuf returned %s", ok ? "true" : "false");
    return ok;
}

void ZawraGraphicsBridge::presentFrame()
{
    if (m_surfaceHandle) {
        ZLOG("presentFrame: handle=%p, compositorState=%p", m_surfaceHandle, m_compositorState);
        if (m_compositorState) {
            bool rendered = ZG_CompositorRenderLayer(m_compositorState);
            ZLOG("presentFrame: CompositorRenderLayer returned %s", rendered ? "true" : "false");
        }
        // Direct ZG_SwapBuffers removed: presentation is handed over to UIProcess via IPC / WPEPlatform
    }
}

void ZawraGraphicsBridge::renderLayer(void* state)
{
    void* targetState = state ? state : m_compositorState;
    if (m_surfaceHandle && targetState) {
        ZG_CompositorRenderLayer(targetState);
    }
}

} // namespace WebCore

#endif // OS(LINUX) || OS(MAC_OS_X) || OS(WINDOWS)
