// src/lib.zig: Zawra Graphics OS Abstraction Stub
pub const ZawraGraphicsHandle = *anyopaque;

pub export fn ZawraGraphics_Initialize() bool { return true; }
pub export fn ZawraGraphics_CreateWindow(width: u32, height: u32) ?ZawraGraphicsHandle {
    _ = width;
    _ = height;
    return null;
}
