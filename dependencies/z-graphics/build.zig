const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib_mod = b.addModule("z-graphics", .{
        .root_source_file = b.path("src/lib.zig"),
        .target = target,
        .optimize = optimize,
    });
    lib_mod.link_libc = true;
    if (target.result.os.tag == .linux) {
        // Use a more robust way to find headers or just add it only if it exists
        if (std.fs.accessAbsolute("/usr/include/vulkan", .{})) |_| {
            lib_mod.addIncludePath(b.path("/usr/include"));
        } else |_| {
            // Fallback or just ignore, if it's missing it will fail later
        }
    }

    const smoke_test = b.addExecutable(.{
        .name = "smoke-test",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/smoke_test.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    smoke_test.root_module.link_libc = true;
    smoke_test.root_module.addImport("lib", lib_mod);
    b.installArtifact(smoke_test);

    const run_cmd = b.addRunArtifact(smoke_test);
    const test_step = b.step("test", "Run smoke test");
    test_step.dependOn(&run_cmd.step);
}
