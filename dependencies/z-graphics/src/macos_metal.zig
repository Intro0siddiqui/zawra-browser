const builtin = @import("builtin");

pub fn initInstance() ?*anyopaque {
    if (builtin.os.tag != .macos) return null;
    // Stub: Metal initialization logic will go here
    return null;
}
