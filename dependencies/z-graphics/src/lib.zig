// src/lib.zig: Zawra Graphics OS Abstraction Stub
pub const ZawraGraphicsHandle = *anyopaque;

pub export fn ZawraGraphics_Initialize() bool { return true; }

/// Creates a surface for rendering
pub export fn ZawraGraphics_CreateSurface(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    // Stub: returning null as we haven't implemented backend surface creation yet
    return null;
}

pub export fn ZawraGraphics_CreateWindow(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    return null;
}
