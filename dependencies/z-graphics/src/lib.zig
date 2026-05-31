// src/lib.zig: Zawra Graphics OS Abstraction
const builtin = @import("builtin");
const linux_vulkan = if (builtin.os.tag == .linux) @import("linux_vulkan.zig") else struct {};

pub const ZawraGraphicsHandle = *anyopaque;

pub export fn ZawraGraphics_Initialize() bool {
    return true;
}

/// Creates a surface for rendering
pub export fn ZawraGraphics_CreateSurface(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    
    if (builtin.os.tag == .linux) {
        // Now calling into the real Vulkan initialization
        return linux_vulkan.initInstance();
    } else if (builtin.os.tag == .macos) {
        return createMacOSMetalSurface();
    } else if (builtin.os.tag == .windows) {
        return createWindowsD3D12Surface();
    }
    
    return null;
}

fn createMacOSMetalSurface() ?ZawraGraphicsHandle {
    // Metal surface creation implementation stub
    return null;
}

fn createWindowsD3D12Surface() ?ZawraGraphicsHandle {
    // D3D12 surface creation implementation stub
    return null;
}

pub export fn ZawraGraphics_CreateWindow(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    return null;
}
