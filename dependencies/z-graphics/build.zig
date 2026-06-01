const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Main module for the library
    const lib_mod = b.addModule("z-graphics", .{
        .root_source_file = b.path("src/lib.zig"),
        .target = target,
        .optimize = optimize,
    });
    // Ensure the module itself knows it might need libc (for cImport)
    lib_mod.link_libc = true;

    // Smoke test executable
    const smoke_test = b.addExecutable(.{
        .name = "smoke-test",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/smoke_test.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });

    // Link libc to the executable so @cImport can find system headers
    // Using root_module.link_libc directly as it's more stable in 0.16.0
    smoke_test.root_module.link_libc = true;

    if (target.result.os.tag == .linux) {
        // Link vulkan system library on Ubuntu
        // Using root_module.addLibraryPath/linkSystemLibrary if needed
        smoke_test.root_module.linkSystemLibrary("vulkan", .{});
    }

    smoke_test.root_module.addImport("lib", lib_mod);
    b.installArtifact(smoke_test);

    const run_cmd = b.addRunArtifact(smoke_test);
    const test_step = b.step("test", "Run smoke test");
    test_step.dependOn(&run_cmd.step);
}
