#include "config.h"

#if USE(EGL)
#include "GLContext.h"
#endif

#if USE(GBM)
#include "GBMDevice.h"
#endif

#include <wtf/text/WTFString.h>

namespace WebCore {

#if USE(EGL)

GLContext::~GLContext() = default;

GLContext* GLContext::current() { return nullptr; }

bool GLContext::makeContextCurrent() { return false; }

bool GLContext::isExtensionSupported(const char*, const char*) { return false; }

std::unique_ptr<GLContext> GLContext::createSharing(PlatformDisplay&) { return nullptr; }

GCGLContext GLContext::platformContext() const { return nullptr; }

const char* GLContext::lastErrorString() { return "Zawra Graphics: Legacy EGL disabled"; }

std::unique_ptr<GLContext> GLContext::create(GLNativeWindowType, PlatformDisplay&) { return nullptr; }
void GLContext::swapBuffers() {}

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
