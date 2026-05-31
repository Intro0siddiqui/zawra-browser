const std = @import("std");
const builtin = @import("builtin");
const c = if (builtin.os.tag == .linux) @cImport({
    @cInclude("vulkan/vulkan.h");
}) else struct {};

pub fn initInstance() ?*anyopaque {
    // Stub: returning null as we haven't implemented backend surface creation yet.
    // This allows the smoke test to pass without linking Vulkan libraries.
    return null;
}
