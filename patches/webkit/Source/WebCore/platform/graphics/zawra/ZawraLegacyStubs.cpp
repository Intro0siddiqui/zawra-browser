#include "config.h"

#if USE(EGL)
#include "GLContext.h"
#include "PlatformDisplay.h"

#if USE(LIBEPOXY)
#include "EpoxyEGL.h"
#else
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#endif

#include <cstring>
#include <mutex>
#include <wtf/ThreadSpecific.h>
#include <wtf/text/WTFString.h>

#if USE(GBM)
#include "GBMDevice.h"
#endif

namespace WebCore {

static ThreadSpecific<GLContext*>& currentContext()
{
    static ThreadSpecific<GLContext*>* context;
    static std::once_flag flag;
    std::call_once(flag, [] {
        context = new ThreadSpecific<GLContext*>();
    });
    return *context;
}

GLContext::GLContext(PlatformDisplay& display, EGLContext context, EGLSurface surface, EGLConfig config, EGLSurfaceType type)
    : m_display(display)
    , m_context(context)
    , m_surface(surface)
    , m_config(config)
    , m_type(type)
{
    RELEASE_ASSERT(m_display.eglDisplay() != EGL_NO_DISPLAY);
    RELEASE_ASSERT(context != EGL_NO_CONTEXT);
}

GLContext::~GLContext()
{
    EGLDisplay display = m_display.eglDisplay();
    if (m_context) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(display, m_context);
    }
    if (m_surface)
        eglDestroySurface(display, m_surface);
    if (this == *currentContext())
        *currentContext() = nullptr;
}

GLContext* GLContext::current()
{
    return *currentContext();
}

bool GLContext::makeContextCurrent()
{
    ASSERT(m_context);
    *currentContext() = this;
    if (eglGetCurrentContext() == m_context)
        return true;
    return eglMakeCurrent(m_display.eglDisplay(), m_surface, m_surface, m_context);
}

bool GLContext::isExtensionSupported(const char* extensionList, const char* extension)
{
    if (!extensionList)
        return false;
    int extensionLen = std::strlen(extension);
    const char* ptr = extensionList;
    while ((ptr = std::strstr(ptr, extension))) {
        if (ptr[extensionLen] == ' ' || ptr[extensionLen] == '\0')
            return true;
        ptr += extensionLen;
    }
    return false;
}

GCGLContext GLContext::platformContext() const
{
    return m_context;
}

const char* GLContext::lastErrorString()
{
    switch (eglGetError()) {
#define CASE_RETURN_STRING(name) case name: return #name
        CASE_RETURN_STRING(EGL_SUCCESS);
        CASE_RETURN_STRING(EGL_NOT_INITIALIZED);
        CASE_RETURN_STRING(EGL_BAD_ACCESS);
        CASE_RETURN_STRING(EGL_BAD_ALLOC);
        CASE_RETURN_STRING(EGL_BAD_ATTRIBUTE);
        CASE_RETURN_STRING(EGL_BAD_CONFIG);
        CASE_RETURN_STRING(EGL_BAD_CONTEXT);
        CASE_RETURN_STRING(EGL_BAD_CURRENT_SURFACE);
        CASE_RETURN_STRING(EGL_BAD_DISPLAY);
        CASE_RETURN_STRING(EGL_BAD_SURFACE);
        CASE_RETURN_STRING(EGL_BAD_MATCH);
        CASE_RETURN_STRING(EGL_BAD_PARAMETER);
        CASE_RETURN_STRING(EGL_BAD_NATIVE_PIXMAP);
        CASE_RETURN_STRING(EGL_BAD_NATIVE_WINDOW);
        CASE_RETURN_STRING(EGL_CONTEXT_LOST);
#undef CASE_RETURN_STRING
    default: return "Unknown EGL error";
    }
}

std::unique_ptr<GLContext> GLContext::create(GLNativeWindowType window, PlatformDisplay& platformDisplay)
{
    UNUSED_PARAM(window);
    return createSharing(platformDisplay);
}

void GLContext::swapBuffers()
{
    if (m_type == Surfaceless)
        return;
    ASSERT(m_surface);
    eglSwapBuffers(m_display.eglDisplay(), m_surface);
}

std::unique_ptr<GLContext> GLContext::createSharing(PlatformDisplay& platformDisplay)
{
    EGLDisplay display = platformDisplay.eglDisplay();
    if (display == EGL_NO_DISPLAY) {
        WTFLogAlways("ZawraLegacyStubs: No EGL display available");
        return nullptr;
    }

    if (eglBindAPI(EGL_OPENGL_ES_API) == EGL_FALSE) {
        WTFLogAlways("ZawraLegacyStubs: Failed to bind EGL OpenGL ES API");
        return nullptr;
    }

    EGLConfig config;
    EGLint configCount;
    EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_NONE
    };
    if (!eglChooseConfig(display, configAttribs, &config, 1, &configCount) || !configCount) {
        WTFLogAlways("ZawraLegacyStubs: Cannot find EGL config: %s", lastErrorString());
        return nullptr;
    }

    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT) {
        WTFLogAlways("ZawraLegacyStubs: Cannot create EGL context: %s", lastErrorString());
        return nullptr;
    }

    EGLint surfaceAttribs[] = { EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE };
    EGLSurface surface = eglCreatePbufferSurface(display, config, surfaceAttribs);
    if (surface == EGL_NO_SURFACE) {
        WTFLogAlways("ZawraLegacyStubs: Cannot create EGL pbuffer surface: %s", lastErrorString());
        eglDestroyContext(display, context);
        return nullptr;
    }

    return makeUnique<GLContext>(platformDisplay, context, surface, config, PbufferSurface);
}

#endif // USE(EGL)

#if USE(GBM)

GBMDevice& GBMDevice::singleton() {
    static GBMDevice* device = new GBMDevice();
    return *device;
}

void GBMDevice::initialize(const WTF::String&) {}
GBMDevice::~GBMDevice() = default;

#endif // USE(GBM)

} // namespace WebCore
