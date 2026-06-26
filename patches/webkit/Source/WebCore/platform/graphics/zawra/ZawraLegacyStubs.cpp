#include "config.h"

#if USE(EGL)
#include "GLContext.h"
#include "PlatformDisplay.h"

#include <cstring>
#include <mutex>
#include <wtf/ThreadSpecific.h>
#include <wtf/text/WTFString.h>
#include "ZawraGraphicsBridge.h"



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
}

GLContext::~GLContext()
{
    if (this == *currentContext())
        *currentContext() = nullptr;
}

GLContext* GLContext::current()
{
    return *currentContext();
}

bool GLContext::makeContextCurrent()
{
    *currentContext() = this;
    return true;
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
    return "No error (Vulkan backend)";
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
    ZawraGraphicsBridge::singleton().presentFrame();
}

std::unique_ptr<GLContext> GLContext::createSharing(PlatformDisplay& platformDisplay)
{
    UNUSED_PARAM(platformDisplay);
    return makeUnique<GLContext>(platformDisplay, nullptr, nullptr, nullptr, PbufferSurface);
}

GLContext::ScopedGLContextCurrent::ScopedGLContextCurrent(GLContext& context)
    : m_context(context)
{
    m_previous.glContext = *currentContext();
    m_previous.context = nullptr;
    m_previous.display = nullptr;
    m_previous.readSurface = nullptr;
    m_previous.drawSurface = nullptr;
    m_context.makeContextCurrent();
}

GLContext::ScopedGLContextCurrent::~ScopedGLContextCurrent()
{
    if (m_previous.glContext) {
        m_previous.glContext->makeContextCurrent();
        return;
    }

    m_context.unmakeContextCurrent();
    *currentContext() = m_previous.glContext;
}

bool GLContext::unmakeContextCurrent()
{
    if (this != *currentContext())
        return false;

    *currentContext() = nullptr;

    return true;
}

#endif // USE(EGL)



} // namespace WebCore
