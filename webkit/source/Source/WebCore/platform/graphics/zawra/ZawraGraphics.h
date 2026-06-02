#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* ZawraGraphicsHandle;
typedef void* ZawraGraphicsBuffer;
typedef void* ZawraGraphicsCommandBuffer;
typedef void* ZawraGraphicsPipeline;

typedef enum {
    ZawraBufferType_Vertex = 1,
    ZawraBufferType_Index = 2,
    ZawraBufferType_Uniform = 3,
} ZawraBufferType;

typedef struct {
    const uint8_t* vertex_shader;
    size_t vertex_shader_len;
    const uint8_t* pixel_shader;
    size_t pixel_shader_len;
} ZawraPipelineDesc;

bool ZawraGraphics_Initialize();
ZawraGraphicsHandle ZawraGraphics_CreateSurface(uint32_t width, uint32_t height);
void ZawraGraphics_DestroySurface(ZawraGraphicsHandle handle);
void ZawraGraphics_SwapBuffers(ZawraGraphicsHandle handle);
int ZawraGraphics_ExportSurfaceFD(ZawraGraphicsHandle handle);

ZawraGraphicsBuffer ZawraGraphics_CreateBuffer(ZawraGraphicsHandle handle, size_t size, ZawraBufferType buffer_type);
void ZawraGraphics_DestroyBuffer(ZawraGraphicsHandle handle, ZawraGraphicsBuffer buffer);

ZawraGraphicsCommandBuffer ZawraGraphics_BeginCommandBuffer(ZawraGraphicsHandle handle);
void ZawraGraphics_CmdClearColor(ZawraGraphicsCommandBuffer cmd, float r, float g, float b, float a);
void ZawraGraphics_SubmitCommandBuffer(ZawraGraphicsHandle handle, ZawraGraphicsCommandBuffer cmd);

ZawraGraphicsPipeline ZawraGraphics_CreatePipeline(ZawraGraphicsHandle handle, const ZawraPipelineDesc* desc);
void ZawraGraphics_DestroyPipeline(ZawraGraphicsHandle handle, ZawraGraphicsPipeline pipeline);
void ZawraGraphics_CmdBindPipeline(ZawraGraphicsCommandBuffer cmd, ZawraGraphicsPipeline pipeline);

#ifdef __cplusplus
}
#endif
