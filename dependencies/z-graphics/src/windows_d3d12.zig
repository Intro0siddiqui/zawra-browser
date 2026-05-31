const builtin = @import("builtin");

pub fn initInstance() ?*anyopaque {
    if (builtin.os.tag != .windows) return null;
    // Stub: D3D12 initialization logic will go here
    return null;
}
