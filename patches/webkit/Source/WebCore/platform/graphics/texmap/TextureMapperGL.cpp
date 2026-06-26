/*
 Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 Copyright (C) 2012 Igalia S.L.
 Copyright (C) 2012 Adobe Systems Incorporated

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "TextureMapperGL.h"
#include "../zawra/ZawraGraphicsBridge.h"
#include "PlatformDisplay.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <cstring>

#define ZLOG(msg, ...) do { \
    fprintf(stderr, "[ZAWRA-BRIDGE pid=%d tid=%d] " msg "\n", getpid(), (int)syscall(SYS_gettid), ##__VA_ARGS__); \
    fflush(stderr); \
} while(0)

extern "C" {
    bool ZawraGraphics_Initialize();
    void* ZawraGraphics_CreateSurface(void* window, unsigned int width, unsigned int height);
    void ZawraGraphics_DestroySurface(void* handle);
    void ZawraGraphics_SwapBuffers(void* handle);
    int ZawraGraphics_ExportSurfaceFD(void* handle);

    void* ZawraGraphics_BeginCommandBuffer(void* handle);
    void ZawraGraphics_CmdClearColor(void* cmd, float r, float g, float b, float a);
    void ZawraGraphics_SubmitCommandBuffer(void* handle, void* cmd);

    void* ZawraGraphics_CreatePipeline(void* handle, const void* desc);
    void ZawraGraphics_DestroyPipeline(void* handle, void* pipeline);
    void ZawraGraphics_CmdBindPipeline(void* cmd, void* pipeline);

    void* ZawraGraphics_CreateBuffer(void* handle, size_t size, unsigned int buffer_type);
    void ZawraGraphics_DestroyBuffer(void* handle, void* buffer);
    bool ZawraGraphics_UploadBuffer(void* handle, void* buffer, const void* data, size_t dataLen);
    void ZawraGraphics_CmdBindVertexBuffer(void* cmd, void* buffer, size_t offset);

    void ZawraGraphics_CmdDraw(void* cmd, unsigned int vertex_count, unsigned int instance_count, unsigned int first_vertex, unsigned int first_instance);

    void ZawraGraphics_CmdSetViewport(void* cmd, float x, float y, float width, float height, float min_depth, float max_depth);
    void ZawraGraphics_CmdSetScissor(void* cmd, int x, int y, unsigned int width, unsigned int height);

    void* ZawraGraphics_CreateTexture(void* handle, const void* desc);
    void ZawraGraphics_DestroyTexture(void* handle, void* texture);
    bool ZawraGraphics_UploadTexture(void* handle, void* texture, const void* data, size_t dataLen);
    void ZawraGraphics_BindTexture(void* cmd, void* texture, unsigned int binding);
    void* ZawraGraphics_ImportTextureFD(void* handle, int fd, const void* desc);

    void* ZawraGraphics_CreateUniformBuffer(void* handle, size_t size);
    bool ZawraGraphics_UploadUniformBuffer(void* handle, void* buffer, const void* data, size_t len);
    void ZawraGraphics_BindUniformBuffer(void* cmd, void* buffer, unsigned int binding, uint64_t offset);

    void* ZawraGraphics_CreateShaderModule(void* handle, const void* spirv, size_t spirv_len);
    void ZawraGraphics_DestroyShaderModule(void* handle, void* module);
    void* ZawraGraphics_CreatePipelineFromShaders(void* handle, void* vert, void* frag);
}

struct ZGraphicsPipelineDesc {
    const void* vertexShader;
    size_t vertexShaderLen;
    const void* fragmentShader;
    size_t fragmentShaderLen;
    uint32_t blendEnable;
    uint32_t srcColorBlendFactor;
    uint32_t dstColorBlendFactor;
    uint32_t colorBlendOp;
    uint32_t srcAlphaBlendFactor;
    uint32_t dstAlphaBlendFactor;
    uint32_t alphaBlendOp;
};

struct ZGraphicsTextureDesc {
    uint32_t format;
    uint32_t width;
    uint32_t height;
    void* externalHandle;
};

#if USE(TEXTURE_MAPPER_GL)

#include "BitmapTextureGL.h"
#include "BitmapTexturePool.h"
#include "FilterOperations.h"
#include "FloatQuad.h"
#include "FloatRoundedRect.h"
#include "GLContext.h"
#include "GraphicsContext.h"
#include "Image.h"
#include "LengthFunctions.h"
#include "NotImplemented.h"
#include "TextureMapperShaderProgram.h"
#include "Timer.h"
#include <wtf/HashMap.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/Ref.h>
#include <wtf/RefCounted.h>
#include <wtf/SetForScope.h>

#if USE(CAIRO)
#include "CairoUtilities.h"
#include "RefPtrCairo.h"
#include <cairo.h>
#include <wtf/text/CString.h>
#endif

namespace WebCore {

struct ZGraphicsUniformData {
    float modelViewMatrix[16];
    float projectionMatrix[16];
    float textureSpaceMatrix[16];
    float textureColorSpaceMatrix[16];
    float color[4];
    float yuvToRgbMatrix[16];
    float opacity;
    float filterAmount;
    float blurRadius[2];
    float shadowOffset[2];
    int32_t roundedRectCount;
    float roundedRects[96];
    float roundedRectInverseTransforms[384];
};

static void transformationMatrixToFloats(const TransformationMatrix& m, float out[16])
{
    out[0]  = static_cast<float>(m.m11());
    out[1]  = static_cast<float>(m.m21());
    out[2]  = static_cast<float>(m.m31());
    out[3]  = static_cast<float>(m.m41());
    out[4]  = static_cast<float>(m.m12());
    out[5]  = static_cast<float>(m.m22());
    out[6]  = static_cast<float>(m.m32());
    out[7]  = static_cast<float>(m.m42());
    out[8]  = static_cast<float>(m.m13());
    out[9]  = static_cast<float>(m.m23());
    out[10] = static_cast<float>(m.m33());
    out[11] = static_cast<float>(m.m43());
    out[12] = static_cast<float>(m.m14());
    out[13] = static_cast<float>(m.m24());
    out[14] = static_cast<float>(m.m34());
    out[15] = static_cast<float>(m.m44());
}

class TextureMapperGLData {
    WTF_MAKE_FAST_ALLOCATED;
public:
    explicit TextureMapperGLData(void*);
    ~TextureMapperGLData();

    void initializeStencil();
    void* getStaticVBO(const void* data, size_t size);
    void bindUniformData(const ZGraphicsUniformData& uniforms);

    Ref<TextureMapperShaderProgram> getShaderProgram(TextureMapperShaderProgram::Options options)
    {
        uint32_t key = options.toRaw();
        auto addResult = m_shaderPrograms.ensure(key,
            [options] { return TextureMapperShaderProgram::create(options); });
        return addResult.iterator->value;
    }

    void* surfaceHandle() const { return m_surfaceHandle; }
    void setSurfaceHandle(void* h) { m_surfaceHandle = h; }
    void* cmdBuffer() const { return m_cmdBuffer; }
    void setCmdBuffer(void* cmd) { m_cmdBuffer = cmd; }

    TransformationMatrix projectionMatrix;
    TextureMapper::PaintFlags PaintFlags { 0 };
    void* targetFrameBuffer { nullptr };
    bool didModifyStencil { false };
    int viewport[4] { 0, };
    double zNear { 0 };
    double zFar { 0 };
    RefPtr<BitmapTexture> currentSurface;
    const BitmapTextureGL::FilterInfo* filterInfo { nullptr };
    void* importedTexture { nullptr };

private:
    void* m_surfaceHandle { nullptr };
    void* m_cmdBuffer { nullptr };
    void* m_uniformBuffer { nullptr };
    size_t m_uniformBufferSize { 0 };
    HashMap<const void*, void*> m_vbos;
    HashMap<uint32_t, Ref<TextureMapperShaderProgram>> m_shaderPrograms;
};

TextureMapperGLData::TextureMapperGLData(void* platformContext)
    : m_surfaceHandle(nullptr)
{
}

TextureMapperGLData::~TextureMapperGLData()
{
    if (m_surfaceHandle) {
        for (auto& entry : m_vbos)
            ZawraGraphics_DestroyBuffer(m_surfaceHandle, entry.value);
        if (m_uniformBuffer)
            ZawraGraphics_DestroyBuffer(m_surfaceHandle, m_uniformBuffer);
    }
}

void TextureMapperGLData::initializeStencil()
{
    if (currentSurface) {
        static_cast<BitmapTextureGL*>(currentSurface.get())->initializeStencil();
        return;
    }

    if (didModifyStencil)
        return;

    didModifyStencil = true;
}

void* TextureMapperGLData::getStaticVBO(const void* data, size_t size)
{
    auto addResult = m_vbos.ensure(data,
        [this, data, size] {
            if (!m_surfaceHandle) return (void*)nullptr;
            void* vbo = ZawraGraphics_CreateBuffer(m_surfaceHandle, size, 1);
            if (vbo)
                ZawraGraphics_UploadBuffer(m_surfaceHandle, vbo, data, size);
            return vbo;
        });
    return addResult.iterator->value;
}

void TextureMapperGLData::bindUniformData(const ZGraphicsUniformData& uniforms)
{
    if (!m_surfaceHandle || !m_cmdBuffer)
        return;

    size_t needed = sizeof(ZGraphicsUniformData);
    if (!m_uniformBuffer || m_uniformBufferSize < needed) {
        if (m_uniformBuffer)
            ZawraGraphics_DestroyBuffer(m_surfaceHandle, m_uniformBuffer);
        m_uniformBuffer = ZawraGraphics_CreateUniformBuffer(m_surfaceHandle, needed);
        m_uniformBufferSize = needed;
    }

    if (m_uniformBuffer) {
        ZawraGraphics_UploadUniformBuffer(m_surfaceHandle, m_uniformBuffer, &uniforms, sizeof(ZGraphicsUniformData));
        ZawraGraphics_BindUniformBuffer(m_cmdBuffer, m_uniformBuffer, 0, 0);
    }
}

TextureMapperGL::TextureMapperGL()
    : m_contextAttributes(TextureMapperContextAttributes::get())
{
    ZLOG("TextureMapperGL constructor start");
    GLContext* ctx = GLContext::current();
    ZLOG("GLContext::current()=%p", ctx);
    if (ctx) {
        void* platformContext = ctx->platformContext();
        ZLOG("platformContext=%p", platformContext);
        m_data = new TextureMapperGLData(platformContext);
    } else {
        ZLOG("WARNING: GLContext::current() is NULL, using nullptr");
        m_data = new TextureMapperGLData(nullptr);
    }
#if USE(TEXTURE_MAPPER_GL)
    m_texturePool = makeUnique<BitmapTexturePool>(m_contextAttributes);
#endif

    ZLOG("TextureMapperGL constructor done (bridge init deferred to beginPainting)");
}

ClipStack& TextureMapperGL::clipStack()
{
    return data().currentSurface ? toBitmapTextureGL(data().currentSurface.get())->clipStack() : m_clipStack;
}

void TextureMapperGL::beginPainting(PaintFlags flags, BitmapTexture* surface)
{
    data().didModifyStencil = false;

    ZLOG("beginPainting: surface=%p", surface);

    if (!surface) {
        int fd = ZawraGraphicsBridge::singleton().exportCompositorFD();
        ZLOG("exportCompositorFD returned fd=%d", fd);
        if (fd >= 0) {
            void* bridgeHandle = nullptr;

            auto& platformDisplay = PlatformDisplay::sharedDisplay();
            UNUSED_PARAM(platformDisplay);

            int width = ZawraGraphicsBridge::singleton().compositorWidth();
            int height = ZawraGraphicsBridge::singleton().compositorHeight();
            ZLOG("compositor size=%dx%d", width, height);

            data().viewport[0] = 0;
            data().viewport[1] = 0;
            data().viewport[2] = width;
            data().viewport[3] = height;

            ZGraphicsTextureDesc texDesc;
            texDesc.format = 0;
            texDesc.width = static_cast<uint32_t>(width);
            texDesc.height = static_cast<uint32_t>(height);
            texDesc.externalHandle = nullptr;

            ZLOG("ImportTextureFD: fd=%d, size=%dx%d", fd, width, height);

            if (data().importedTexture) {
                void* handle = data().surfaceHandle();
                if (handle)
                    ZawraGraphics_DestroyTexture(handle, data().importedTexture);
                data().importedTexture = nullptr;
            }

            void* importedTex = ZawraGraphics_ImportTextureFD(bridgeHandle, fd, &texDesc);
            ZLOG("ImportTextureFD returned %p", importedTex);
            data().importedTexture = importedTex;

            close(fd);

            if (importedTex) {
                void* cmd = ZawraGraphics_BeginCommandBuffer(bridgeHandle);
                ZLOG("BeginCommandBuffer returned %p", cmd);
                data().setCmdBuffer(cmd);
                data().setSurfaceHandle(bridgeHandle);

                if (cmd) {
                    ZawraGraphics_CmdSetViewport(cmd, 0, 0, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f);
                    ZawraGraphics_CmdSetScissor(cmd, 0, 0, static_cast<uint32_t>(width), static_cast<uint32_t>(height));
                }
            }
        } else {
            ZLOG("exportCompositorFD FAILED (returned -1)");
        }
    }

    data().PaintFlags = flags;
    bindSurface(surface);
    ZLOG("beginPainting done");
}

void TextureMapperGL::endPainting()
{
    void* cmd = data().cmdBuffer();
    void* handle = data().surfaceHandle();
    ZLOG("endPainting: cmd=%p, handle=%p", cmd, handle);

    if (cmd && handle) {
        ZawraGraphics_SubmitCommandBuffer(handle, cmd);
        data().setCmdBuffer(nullptr);
    }

    if (ZawraGraphicsBridge::singleton().exportCompositorFD() >= 0) {
        ZLOG("calling presentFrame()");
        ZawraGraphicsBridge::singleton().presentFrame();
        ZLOG("presentFrame done");
    } else {
        ZLOG("skipping presentFrame() (no valid compositor FD)");
    }
}

void TextureMapperGL::drawBorder(const Color& color, float width, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix)
{
    if (clipStack().isCurrentScissorBoxEmpty())
        return;

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(TextureMapperShaderProgram::SolidColor);

    auto [r, g, b, a] = premultiplied(color.toColorTypeLossy<SRGBA<float>>()).resolved();
    UNUSED_PARAM(r);
    UNUSED_PARAM(g);
    UNUSED_PARAM(b);
    UNUSED_PARAM(a);
    UNUSED_PARAM(width);

    draw(targetRect, modelViewMatrix, program.get(), 0x0004, !color.isOpaque() ? ShouldBlend : 0);
}

void TextureMapperGL::drawNumber(int number, const Color& color, const FloatPoint& targetPoint, const TransformationMatrix& modelViewMatrix)
{
    int pointSize = 8;

#if USE(CAIRO)
    CString counterString = String::number(number).ascii();
    int width = counterString.length() * pointSize * 1.2;
    int height = pointSize * 1.5;

    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    auto [r, g, b, a] = color.toColorTypeLossy<SRGBA<float>>().resolved();
    cairo_set_source_rgba(cr, b, g, r, a);

    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    cairo_select_font_face(cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, pointSize);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 2, pointSize);
    cairo_show_text(cr, counterString.data());

    IntSize size(width, height);
    IntRect sourceRect(IntPoint::zero(), size);
    IntRect targetRect(roundedIntPoint(targetPoint), size);

    RefPtr<BitmapTexture> texture = acquireTextureFromPool(size);
    const unsigned char* bits = cairo_image_surface_get_data(surface);
    int stride = cairo_image_surface_get_stride(surface);
    static_cast<BitmapTextureGL*>(texture.get())->updateContents(bits, sourceRect, IntPoint::zero(), stride);
    drawTexture(*texture, targetRect, modelViewMatrix, 1.0f, AllEdges);

    cairo_surface_destroy(surface);
    cairo_destroy(cr);

#else
    UNUSED_PARAM(number);
    UNUSED_PARAM(pointSize);
    UNUSED_PARAM(targetPoint);
    UNUSED_PARAM(modelViewMatrix);
    notImplemented();
#endif
}

static TextureMapperShaderProgram::Options optionsForFilterType(FilterOperation::Type type, unsigned pass)
{
    switch (type) {
    case FilterOperation::Type::Grayscale:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::GrayscaleFilter };
    case FilterOperation::Type::Sepia:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::SepiaFilter };
    case FilterOperation::Type::Saturate:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::SaturateFilter };
    case FilterOperation::Type::HueRotate:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::HueRotateFilter };
    case FilterOperation::Type::Invert:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::InvertFilter };
    case FilterOperation::Type::Brightness:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::BrightnessFilter };
    case FilterOperation::Type::Contrast:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::ContrastFilter };
    case FilterOperation::Type::Opacity:
        return { TextureMapperShaderProgram::TextureRGB, TextureMapperShaderProgram::OpacityFilter };
    case FilterOperation::Type::Blur:
        return { TextureMapperShaderProgram::BlurFilter };
    case FilterOperation::Type::DropShadow:
        if (!pass)
            return { TextureMapperShaderProgram::AlphaBlur };
        return { TextureMapperShaderProgram::AlphaBlur, TextureMapperShaderProgram::ContentTexture, TextureMapperShaderProgram::SolidColor };
    default:
        return { };
    }
}

static const unsigned GaussianKernelHalfWidth = 11;
static const float GaussianKernelStep = 0.2;

static inline float gauss(float x)
{
    return exp(-(x * x) / 2.);
}

static float* gaussianKernel()
{
    static bool prepared = false;
    static float kernel[GaussianKernelHalfWidth] = {0, };

    if (prepared)
        return kernel;

    kernel[0] = gauss(0);
    float sum = kernel[0];
    for (unsigned i = 1; i < GaussianKernelHalfWidth; ++i) {
        kernel[i] = gauss(i * GaussianKernelStep);
        sum += 2 * kernel[i];
    }

    float scale = 1 / sum;
    for (unsigned i = 0; i < GaussianKernelHalfWidth; ++i)
        kernel[i] *= scale;

    prepared = true;
    return kernel;
}

static void prepareFilterProgram(TextureMapperShaderProgram& program, const FilterOperation& operation, unsigned pass, const IntSize& size, GLuint contentTexture)
{
    UNUSED_PARAM(program);
    UNUSED_PARAM(operation);
    UNUSED_PARAM(pass);
    UNUSED_PARAM(size);
    UNUSED_PARAM(contentTexture);
}

static TransformationMatrix colorSpaceMatrixForFlags(TextureMapperGL::Flags flags)
{
    TransformationMatrix matrix;
    if (flags & TextureMapperGL::ShouldConvertTextureBGRAToRGBA)
        matrix.setMatrix(0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    else if (flags & TextureMapperGL::ShouldConvertTextureARGBToRGBA)
        matrix.setMatrix(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);

    return matrix;
}

static void prepareRoundedRectClip(TextureMapperShaderProgram& program, const float* rects, const float* transforms, int nRects)
{
    UNUSED_PARAM(program);
    UNUSED_PARAM(rects);
    UNUSED_PARAM(transforms);
    UNUSED_PARAM(nRects);
}

void TextureMapperGL::drawTexture(const BitmapTexture& texture, const FloatRect& targetRect, const TransformationMatrix& matrix, float opacity, unsigned exposedEdges)
{
    if (!texture.isValid())
        return;

    if (clipStack().isCurrentScissorBoxEmpty())
        return;

    const BitmapTextureGL& textureGL = static_cast<const BitmapTextureGL&>(texture);
    SetForScope filterInfo(data().filterInfo, textureGL.filterInfo());

    drawTexture(textureGL.id(), textureGL.colorConvertFlags() | (textureGL.isOpaque() ? 0 : ShouldBlend), textureGL.size(), targetRect, matrix, opacity, exposedEdges);
}

void TextureMapperGL::drawTexture(GLuint texture, Flags flags, const IntSize& textureSize, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix, float opacity, unsigned exposedEdges)
{
    bool useAntialiasing = exposedEdges == AllEdges
        && !modelViewMatrix.mapQuad(targetRect).isRectilinear();

    TextureMapperShaderProgram::Options options;
    if (opacity < 1)
        options.add(TextureMapperShaderProgram::Opacity);
    if (useAntialiasing) {
        options.add(TextureMapperShaderProgram::Antialiasing);
        flags |= ShouldAntialias;
    }
    if (wrapMode() == RepeatWrap && !m_contextAttributes.supportsNPOTTextures)
        options.add(TextureMapperShaderProgram::ManualRepeat);

    RefPtr<FilterOperation> filter = data().filterInfo ? data().filterInfo->filter: nullptr;
    GLuint filterContentTextureID = 0;

    if (filter) {
        if (data().filterInfo->contentTexture)
            filterContentTextureID = toBitmapTextureGL(data().filterInfo->contentTexture.get())->id();
        options.add(optionsForFilterType(filter->type(), data().filterInfo->pass));
        if (filter->affectsOpacity())
            flags |= ShouldBlend;
    } else
        options.add(TextureMapperShaderProgram::TextureRGB);

    if (useAntialiasing || opacity < 1)
        flags |= ShouldBlend;

    if (clipStack().isRoundedRectClipEnabled()) {
        options.add(TextureMapperShaderProgram::RoundedRectClip);
        flags |= ShouldBlend;
    }

    if (flags & ShouldPremultiply)
        options.add(TextureMapperShaderProgram::Premultiply);

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    if (filter)
        prepareFilterProgram(program.get(), *filter.get(), data().filterInfo->pass, textureSize, filterContentTextureID);

    if (clipStack().isRoundedRectClipEnabled())
        prepareRoundedRectClip(program.get(), clipStack().roundedRectComponents(), clipStack().roundedRectInverseTransformComponents(), clipStack().roundedRectCount());

    drawTexturedQuadWithProgram(program.get(), texture, flags, targetRect, modelViewMatrix, opacity);
}

static void prepareTransformationMatrixWithFlags(TransformationMatrix& patternTransform, TextureMapperGL::Flags flags)
{
    if (flags & TextureMapperGL::ShouldRotateTexture90) {
        patternTransform.rotate(-90);
        patternTransform.translate(-1, 0);
    }
    if (flags & TextureMapperGL::ShouldRotateTexture180) {
        patternTransform.rotate(180);
        patternTransform.translate(-1, -1);
    }
    if (flags & TextureMapperGL::ShouldRotateTexture270) {
        patternTransform.rotate(-270);
        patternTransform.translate(0, -1);
    }
    if (flags & TextureMapperGL::ShouldFlipTexture) {
        patternTransform.flipY();
        patternTransform.translate(0, -1);
    }
}

void TextureMapperGL::drawTexturePlanarYUV(const std::array<GLuint, 3>& textures, const std::array<GLfloat, 16>& yuvToRgbMatrix, Flags flags, const IntSize& textureSize, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix, float opacity, std::optional<GLuint> alphaPlane, unsigned exposedEdges)
{
    bool useAntialiasing = exposedEdges == AllEdges
        && !modelViewMatrix.mapQuad(targetRect).isRectilinear();

    TextureMapperShaderProgram::Options options = alphaPlane ? TextureMapperShaderProgram::TextureYUVA : TextureMapperShaderProgram::TextureYUV;
    if (opacity < 1)
        options.add(TextureMapperShaderProgram::Opacity);
    if (useAntialiasing) {
        options.add(TextureMapperShaderProgram::Antialiasing);
        flags |= ShouldAntialias;
    }
    if (wrapMode() == RepeatWrap && !m_contextAttributes.supportsNPOTTextures)
        options.add(TextureMapperShaderProgram::ManualRepeat);

    RefPtr<FilterOperation> filter = data().filterInfo ? data().filterInfo->filter: nullptr;
    GLuint filterContentTextureID = 0;

    if (filter) {
        if (data().filterInfo->contentTexture)
            filterContentTextureID = toBitmapTextureGL(data().filterInfo->contentTexture.get())->id();
        options.add(optionsForFilterType(filter->type(), data().filterInfo->pass));
        if (filter->affectsOpacity())
            flags |= ShouldBlend;
    }

    if (useAntialiasing || opacity < 1)
        flags |= ShouldBlend;

    if (clipStack().isRoundedRectClipEnabled()) {
        options.add(TextureMapperShaderProgram::RoundedRectClip);
        flags |= ShouldBlend;
    }

    if (flags & ShouldPremultiply)
        options.add(TextureMapperShaderProgram::Premultiply);

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    if (filter)
        prepareFilterProgram(program.get(), *filter.get(), data().filterInfo->pass, textureSize, filterContentTextureID);

    if (clipStack().isRoundedRectClipEnabled())
        prepareRoundedRectClip(program.get(), clipStack().roundedRectComponents(), clipStack().roundedRectInverseTransformComponents(), clipStack().roundedRectCount());

    Vector<std::pair<GLuint, GLuint> > texturesAndSamplers = {
        { textures[0], program->samplerYLocation() },
        { textures[1], program->samplerULocation() },
        { textures[2], program->samplerVLocation() }
    };

    if (alphaPlane)
        texturesAndSamplers.append({*alphaPlane, program->samplerALocation() });

    void* cmd = data().cmdBuffer();
    if (cmd) {
        ZGraphicsUniformData uniforms;
        memset(&uniforms, 0, sizeof(uniforms));
        memcpy(uniforms.yuvToRgbMatrix, yuvToRgbMatrix.data(), sizeof(float) * 16);
        uniforms.opacity = opacity;
        data().bindUniformData(uniforms);

        for (unsigned i = 0; i < texturesAndSamplers.size(); ++i)
            ZawraGraphics_BindTexture(cmd, reinterpret_cast<void*>(static_cast<uintptr_t>(texturesAndSamplers[i].first)), i);
    }

    drawTexturedQuadWithProgram(program.get(), texturesAndSamplers, flags, targetRect, modelViewMatrix, opacity);
}

void TextureMapperGL::drawTextureSemiPlanarYUV(const std::array<GLuint, 2>& textures, bool uvReversed, const std::array<GLfloat, 16>& yuvToRgbMatrix, Flags flags, const IntSize& textureSize, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix, float opacity, unsigned exposedEdges)
{
    bool useAntialiasing = exposedEdges == AllEdges
        && !modelViewMatrix.mapQuad(targetRect).isRectilinear();

    TextureMapperShaderProgram::Options options = uvReversed ?
        TextureMapperShaderProgram::TextureNV21 : TextureMapperShaderProgram::TextureNV12;
    if (opacity < 1)
        options.add(TextureMapperShaderProgram::Opacity);
    if (useAntialiasing) {
        options.add(TextureMapperShaderProgram::Antialiasing);
        flags |= ShouldAntialias;
    }
    if (wrapMode() == RepeatWrap && !m_contextAttributes.supportsNPOTTextures)
        options.add(TextureMapperShaderProgram::ManualRepeat);

    RefPtr<FilterOperation> filter = data().filterInfo ? data().filterInfo->filter: nullptr;
    GLuint filterContentTextureID = 0;

    if (filter) {
        if (data().filterInfo->contentTexture)
            filterContentTextureID = toBitmapTextureGL(data().filterInfo->contentTexture.get())->id();
        options.add(optionsForFilterType(filter->type(), data().filterInfo->pass));
        if (filter->affectsOpacity())
            flags |= ShouldBlend;
    }

    if (useAntialiasing || opacity < 1)
        flags |= ShouldBlend;

    if (clipStack().isRoundedRectClipEnabled()) {
        options.add(TextureMapperShaderProgram::RoundedRectClip);
        flags |= ShouldBlend;
    }

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    if (filter)
        prepareFilterProgram(program.get(), *filter.get(), data().filterInfo->pass, textureSize, filterContentTextureID);

    if (clipStack().isRoundedRectClipEnabled())
        prepareRoundedRectClip(program.get(), clipStack().roundedRectComponents(), clipStack().roundedRectInverseTransformComponents(), clipStack().roundedRectCount());

    Vector<std::pair<GLuint, GLuint> > texturesAndSamplers = {
        { textures[0], program->samplerYLocation() },
        { textures[1], program->samplerULocation() }
    };

    void* cmd = data().cmdBuffer();
    if (cmd) {
        ZGraphicsUniformData uniforms;
        memset(&uniforms, 0, sizeof(uniforms));
        memcpy(uniforms.yuvToRgbMatrix, yuvToRgbMatrix.data(), sizeof(float) * 16);
        uniforms.opacity = opacity;
        data().bindUniformData(uniforms);

        for (unsigned i = 0; i < texturesAndSamplers.size(); ++i)
            ZawraGraphics_BindTexture(cmd, reinterpret_cast<void*>(static_cast<uintptr_t>(texturesAndSamplers[i].first)), i);
    }

    drawTexturedQuadWithProgram(program.get(), texturesAndSamplers, flags, targetRect, modelViewMatrix, opacity);
}

void TextureMapperGL::drawTexturePackedYUV(GLuint texture, const std::array<GLfloat, 16>& yuvToRgbMatrix, Flags flags, const IntSize& textureSize, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix, float opacity, unsigned exposedEdges)
{
    bool useAntialiasing = exposedEdges == AllEdges
        && !modelViewMatrix.mapQuad(targetRect).isRectilinear();

    TextureMapperShaderProgram::Options options = TextureMapperShaderProgram::TexturePackedYUV;
    if (opacity < 1)
        options.add(TextureMapperShaderProgram::Opacity);
    if (useAntialiasing) {
        options.add(TextureMapperShaderProgram::Antialiasing);
        flags |= ShouldAntialias;
    }
    if (wrapMode() == RepeatWrap && !m_contextAttributes.supportsNPOTTextures)
        options.add(TextureMapperShaderProgram::ManualRepeat);

    RefPtr<FilterOperation> filter = data().filterInfo ? data().filterInfo->filter: nullptr;
    GLuint filterContentTextureID = 0;

    if (filter) {
        if (data().filterInfo->contentTexture)
            filterContentTextureID = toBitmapTextureGL(data().filterInfo->contentTexture.get())->id();
        options.add(optionsForFilterType(filter->type(), data().filterInfo->pass));
        if (filter->affectsOpacity())
            flags |= ShouldBlend;
    }

    if (useAntialiasing || opacity < 1)
        flags |= ShouldBlend;

    if (clipStack().isRoundedRectClipEnabled()) {
        options.add(TextureMapperShaderProgram::RoundedRectClip);
        flags |= ShouldBlend;
    }

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    if (filter)
        prepareFilterProgram(program.get(), *filter.get(), data().filterInfo->pass, textureSize, filterContentTextureID);

    if (clipStack().isRoundedRectClipEnabled())
        prepareRoundedRectClip(program.get(), clipStack().roundedRectComponents(), clipStack().roundedRectInverseTransformComponents(), clipStack().roundedRectCount());

    Vector<std::pair<GLuint, GLuint> > texturesAndSamplers = {
        { texture, program->samplerLocation() }
    };

    void* cmd = data().cmdBuffer();
    if (cmd) {
        ZGraphicsUniformData uniforms;
        memset(&uniforms, 0, sizeof(uniforms));
        memcpy(uniforms.yuvToRgbMatrix, yuvToRgbMatrix.data(), sizeof(float) * 16);
        uniforms.opacity = opacity;
        data().bindUniformData(uniforms);

        ZawraGraphics_BindTexture(cmd, reinterpret_cast<void*>(static_cast<uintptr_t>(texture)), 0);
    }

    drawTexturedQuadWithProgram(program.get(), texturesAndSamplers, flags, targetRect, modelViewMatrix, opacity);
}

void TextureMapperGL::drawSolidColor(const FloatRect& rect, const TransformationMatrix& matrix, const Color& color, bool isBlendingAllowed)
{
    Flags flags = 0;
    TextureMapperShaderProgram::Options options = TextureMapperShaderProgram::SolidColor;
    if (!matrix.mapQuad(rect).isRectilinear()) {
        options.add(TextureMapperShaderProgram::Antialiasing);
        flags |= ShouldAntialias | (isBlendingAllowed ? ShouldBlend : 0);
    }

    if (clipStack().isRoundedRectClipEnabled()) {
        options.add(TextureMapperShaderProgram::RoundedRectClip);
        flags |= ShouldBlend;
    }

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    if (clipStack().isRoundedRectClipEnabled())
        prepareRoundedRectClip(program.get(), clipStack().roundedRectComponents(), clipStack().roundedRectInverseTransformComponents(), clipStack().roundedRectCount());

    auto [r, g, b, a] = premultiplied(color.toColorTypeLossy<SRGBA<float>>()).resolved();

    ZGraphicsUniformData uniforms;
    memset(&uniforms, 0, sizeof(uniforms));
    uniforms.color[0] = r;
    uniforms.color[1] = g;
    uniforms.color[2] = b;
    uniforms.color[3] = a;
    data().bindUniformData(uniforms);

    if (a < 1 && isBlendingAllowed)
        flags |= ShouldBlend;

    draw(rect, matrix, program.get(), 0x0004, flags);
}

void TextureMapperGL::clearColor(const Color& color)
{
    auto [r, g, b, a] = color.toColorTypeLossy<SRGBA<float>>().resolved();
    void* cmd = data().cmdBuffer();
    if (cmd)
        ZawraGraphics_CmdClearColor(cmd, r, g, b, a);
}

void TextureMapperGL::drawEdgeTriangles(TextureMapperShaderProgram& program)
{
    UNUSED_PARAM(program);

    static const float unitRectSideTriangles[] = {
        0, 0, 0, 0,  1, 0, 1, 0,  0.5f, 0.5f, 0.5f, 0,
        0, 0, 0, 0,  0, 1, 0, 1,  0.5f, 0.5f, 0, 0.5f,
        1, 0, 1, 0,  1, 1, 1, 1,  0.5f, 0.5f, 1, 0.5f,
        0, 1, 0, 1,  1, 1, 1, 1,  0.5f, 0.5f, 0.5f, 1
    };

    void* vbo = data().getStaticVBO(unitRectSideTriangles, sizeof(unitRectSideTriangles));
    void* cmd = data().cmdBuffer();
    if (cmd && vbo) {
        ZawraGraphics_CmdBindVertexBuffer(cmd, vbo, 0);
        ZawraGraphics_CmdDraw(cmd, 12, 1, 0, 0);
    }
}

void TextureMapperGL::drawUnitRect(TextureMapperShaderProgram& program, GLenum drawingMode)
{
    UNUSED_PARAM(program);
    UNUSED_PARAM(drawingMode);

    static const float unitRect[] = { 0, 0, 1, 0, 1, 1, 0, 1 };
    void* vbo = data().getStaticVBO(unitRect, sizeof(unitRect));
    void* cmd = data().cmdBuffer();
    if (cmd && vbo) {
        ZawraGraphics_CmdBindVertexBuffer(cmd, vbo, 0);
        ZawraGraphics_CmdDraw(cmd, 4, 1, 0, 0);
    }
}

void TextureMapperGL::draw(const FloatRect& rect, const TransformationMatrix& modelViewMatrix, TextureMapperShaderProgram& program, GLenum drawingMode, Flags flags)
{
    UNUSED_PARAM(program);
    UNUSED_PARAM(drawingMode);

    TransformationMatrix matrix(modelViewMatrix);
    matrix.multiply(TransformationMatrix::rectToRect(FloatRect(0, 0, 1, 1), rect));

    ZGraphicsUniformData uniforms;
    memset(&uniforms, 0, sizeof(uniforms));

    transformationMatrixToFloats(matrix, uniforms.modelViewMatrix);
    transformationMatrixToFloats(data().projectionMatrix, uniforms.projectionMatrix);

    if (isInMaskMode()) {
        uniforms.opacity = 0.0f;
    } else if (flags & ShouldBlend) {
        uniforms.opacity = 1.0f;
    }

    data().bindUniformData(uniforms);

    if (flags & ShouldAntialias)
        drawEdgeTriangles(program);
    else
        drawUnitRect(program, drawingMode);
}

void TextureMapperGL::drawTexturedQuadWithProgram(TextureMapperShaderProgram& program, const Vector<std::pair<GLuint, GLuint> >& texturesAndSamplers, Flags flags, const FloatRect& rect, const TransformationMatrix& modelViewMatrix, float opacity)
{
    UNUSED_PARAM(program);

    void* cmd = data().cmdBuffer();
    if (!cmd) {
        ZLOG("drawTexturedQuadWithProgram: no command buffer");
        return;
    }

    bool repeatWrap = wrapMode() == RepeatWrap && m_contextAttributes.supportsNPOTTextures;
    UNUSED_PARAM(repeatWrap);

    for (unsigned i = 0; i < texturesAndSamplers.size(); ++i) {
        auto& textureAndSampler = texturesAndSamplers[i];
        ZawraGraphics_BindTexture(cmd, reinterpret_cast<void*>(static_cast<uintptr_t>(textureAndSampler.first)), i);
    }

    TransformationMatrix patternTransform = this->patternTransform();
    prepareTransformationMatrixWithFlags(patternTransform, flags);

    TransformationMatrix matrix(modelViewMatrix);
    matrix.multiply(TransformationMatrix::rectToRect(FloatRect(0, 0, 1, 1), rect));

    ZGraphicsUniformData uniforms;
    memset(&uniforms, 0, sizeof(uniforms));
    transformationMatrixToFloats(matrix, uniforms.modelViewMatrix);
    transformationMatrixToFloats(data().projectionMatrix, uniforms.projectionMatrix);
    transformationMatrixToFloats(patternTransform, uniforms.textureSpaceMatrix);
    TransformationMatrix csm = colorSpaceMatrixForFlags(flags);
    transformationMatrixToFloats(csm, uniforms.textureColorSpaceMatrix);
    uniforms.opacity = opacity;
    data().bindUniformData(uniforms);

    if (opacity < 1)
        flags |= ShouldBlend;

    draw(rect, modelViewMatrix, program, 0x0004, flags);
}

void TextureMapperGL::drawTexturedQuadWithProgram(TextureMapperShaderProgram& program, uint32_t texture, Flags flags, const FloatRect& rect, const TransformationMatrix& modelViewMatrix, float opacity)
{
    drawTexturedQuadWithProgram(program, { { texture, program.samplerLocation() } }, flags, rect, modelViewMatrix, opacity);
}

void TextureMapperGL::drawFiltered(const BitmapTexture& sampler, const BitmapTexture* contentTexture, const FilterOperation& filter, int pass)
{
    TextureMapperShaderProgram::Options options = optionsForFilterType(filter.type(), pass);
    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(options);

    prepareFilterProgram(program.get(), filter, pass, sampler.contentSize(), contentTexture ? static_cast<const BitmapTextureGL*>(contentTexture)->id() : 0);
    FloatRect targetRect(IntPoint::zero(), sampler.contentSize());
    drawTexturedQuadWithProgram(program.get(), static_cast<const BitmapTextureGL&>(sampler).id(), 0, targetRect, TransformationMatrix(), 1);
}

static inline TransformationMatrix createProjectionMatrix(const IntSize& size, bool mirrored, double zNear, double zFar)
{
    const double nearValue = std::min(zNear + 1, 9999999.0);
    const double farValue = std::max(zFar - 1, -99999.0);
    return TransformationMatrix(2.0 / size.width(), 0, 0, 0,
        0, (mirrored ? 2.0 : -2.0) / size.height(), 0, 0,
        0, 0, 2.0 / (farValue - nearValue), 0,
        -1, mirrored ? -1 : 1, -(farValue + nearValue) / (farValue - nearValue), 1);
}

TextureMapperGL::~TextureMapperGL()
{
    delete m_data;
}

void TextureMapperGL::bindDefaultSurface()
{
    auto& viewport = data().viewport;
    void* cmd = data().cmdBuffer();
    if (cmd)
        ZawraGraphics_CmdSetViewport(cmd, viewport[0], viewport[1], viewport[2], viewport[3], 0.0f, 1.0f);
    m_clipStack.apply();
    data().currentSurface = nullptr;
    updateProjectionMatrix();
}

void TextureMapperGL::bindSurface(BitmapTexture *surface)
{
    if (!surface) {
        bindDefaultSurface();
        return;
    }

    static_cast<BitmapTextureGL*>(surface)->bindAsSurface();
    data().currentSurface = surface;
    updateProjectionMatrix();
}

BitmapTexture* TextureMapperGL::currentSurface()
{
    return data().currentSurface.get();
}

bool TextureMapperGL::beginScissorClip(const TransformationMatrix& modelViewMatrix, const FloatRect& targetRect)
{
    if (!modelViewMatrix.isAffine())
        return false;

    FloatQuad quad = modelViewMatrix.projectQuad(targetRect);
    IntRect rect = quad.enclosingBoundingBox();

    if (!quad.isRectilinear() || rect.isEmpty())
        return false;

    clipStack().intersect(rect);
    clipStack().applyIfNeeded();
    return true;
}

bool TextureMapperGL::beginRoundedRectClip(const TransformationMatrix& modelViewMatrix, const FloatRoundedRect& targetRect)
{
    if (!targetRect.isRounded() || !targetRect.isRenderable() || targetRect.isEmpty() || !modelViewMatrix.isInvertible() || !clipStack().isRoundedRectClipAllowed())
        return false;

    FloatQuad quad = modelViewMatrix.projectQuad(targetRect.rect());
    IntRect rect = quad.enclosingBoundingBox();

    clipStack().addRoundedRect(targetRect, modelViewMatrix.inverse().value());
    clipStack().intersect(rect);
    clipStack().applyIfNeeded();

    return true;
}

void TextureMapperGL::beginClip(const TransformationMatrix& modelViewMatrix, const FloatRoundedRect& targetRect)
{
    clipStack().push();
    if (beginRoundedRectClip(modelViewMatrix, targetRect))
        return;

    if (beginScissorClip(modelViewMatrix, targetRect.rect()))
        return;

    data().initializeStencil();

    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(TextureMapperShaderProgram::SolidColor);

    TransformationMatrix matrix(modelViewMatrix);
    matrix.multiply(TransformationMatrix::rectToRect(FloatRect(0, 0, 1, 1), targetRect.rect()));

    static const TransformationMatrix fullProjectionMatrix = TransformationMatrix::rectToRect(FloatRect(0, 0, 1, 1), FloatRect(-1, -1, 2, 2));

    int stencilIndex = clipStack().getStencilIndex();

    ZGraphicsUniformData uniforms;
    memset(&uniforms, 0, sizeof(uniforms));
    transformationMatrixToFloats(fullProjectionMatrix, uniforms.projectionMatrix);
    data().bindUniformData(uniforms);

    static const float unitRect[] = { 0, 0, 1, 0, 1, 1, 0, 1 };
    void* vbo = data().getStaticVBO(unitRect, sizeof(unitRect));
    void* cmd = data().cmdBuffer();
    if (cmd && vbo) {
        ZawraGraphics_CmdBindVertexBuffer(cmd, vbo, 0);
        ZawraGraphics_CmdDraw(cmd, 4, 1, 0, 0);

        ZGraphicsUniformData clipUniforms;
        memset(&clipUniforms, 0, sizeof(clipUniforms));
        transformationMatrixToFloats(data().projectionMatrix, clipUniforms.projectionMatrix);
        transformationMatrixToFloats(matrix, clipUniforms.modelViewMatrix);
        data().bindUniformData(clipUniforms);
        ZawraGraphics_CmdDraw(cmd, 4, 1, 0, 0);
    }

    clipStack().setStencilIndex(stencilIndex * 2);
    clipStack().applyIfNeeded();
}

void TextureMapperGL::endClip()
{
    clipStack().pop();
    clipStack().applyIfNeeded();
}

IntRect TextureMapperGL::clipBounds()
{
    return clipStack().current().scissorBox;
}

Ref<BitmapTexture> TextureMapperGL::createTexture()
{
    return BitmapTextureGL::create(m_contextAttributes);
}

void TextureMapperGL::setDepthRange(double zNear, double zFar)
{
    data().zNear = zNear;
    data().zFar = zFar;
    updateProjectionMatrix();
}

void TextureMapperGL::updateProjectionMatrix()
{
    bool mirrored;
    IntSize size;
    if (data().currentSurface) {
        size = data().currentSurface->size();
        mirrored = true;
    } else {
        size = IntSize(data().viewport[2], data().viewport[3]);
        mirrored = data().PaintFlags & PaintingMirrored;
    }
    data().projectionMatrix = createProjectionMatrix(size, mirrored, data().zNear, data().zFar);
}

std::unique_ptr<TextureMapper> TextureMapper::platformCreateAccelerated()
{
    return makeUnique<TextureMapperGL>();
}

void TextureMapperGL::drawTextureExternalOES(GLuint texture, Flags flags, const FloatRect& targetRect, const TransformationMatrix& modelViewMatrix, float opacity)
{
    Ref<TextureMapperShaderProgram> program = data().getShaderProgram(TextureMapperShaderProgram::Option::TextureExternalOES);
    drawTexturedQuadWithProgram(program.get(), { { texture, program->externalOESTextureLocation() } },
        flags | TextureMapperGL::ShouldUseExternalOESTextureRect, targetRect, modelViewMatrix, opacity);
}

};

#endif // USE(TEXTURE_MAPPER_GL)
