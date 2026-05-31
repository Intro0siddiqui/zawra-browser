// src/lib.zig: Zawra Graphics OS Abstraction
const builtin = @import("builtin");

const c = if (builtin.os.tag == .linux) @cImport({
    @cInclude("vulkan/vulkan.h");
}) else struct {};

pub const ZawraGraphicsHandle = *anyopaque;

pub export fn ZawraGraphics_Initialize() bool {
    return true;
}

/// Creates a surface for rendering
pub export fn ZawraGraphics_CreateSurface(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    
    if (builtin.os.tag == .linux) {
        return createLinuxVulkanSurface();
    }
    
    // Stub for other platforms until implemented
    return null;
}

fn createLinuxVulkanSurface() ?ZawraGraphicsHandle {
    // Vulkan surface creation implementation will go here.
    // For now, return null as a functional stub.
    return null;
}

pub export fn ZawraGraphics_CreateWindow(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    return null;
}
