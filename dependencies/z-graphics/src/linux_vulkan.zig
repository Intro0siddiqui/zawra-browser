const std = @import("std");
const builtin = @import("builtin");

pub fn initInstance() ?*anyopaque {
    if (builtin.os.tag != .linux) return null;
    return @ptrFromInt(0x1); // Return dummy handle
}
