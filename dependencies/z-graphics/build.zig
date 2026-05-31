const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addLibrary(.{
        .name = "z-graphics",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/lib.zig"),
            .target = target,
            .optimize = optimize,
        }),
        .linkage = .static,
    });
    b.installArtifact(lib);

    const smoke_test = b.addExecutable(.{
        .name = "smoke-test",
        .root_source_file = b.path("src/smoke_test.zig"),
        .target = target,
        .optimize = optimize,
    });
    smoke_test.root_module.addImport("lib", b.createModule(.{
        .root_source_file = b.path("src/lib.zig"),
        .target = target,
        .optimize = optimize,
    }));
    b.installArtifact(smoke_test);

    const run_cmd = b.addRunArtifact(smoke_test);
    const test_step = b.step("test", "Run smoke test");
    test_step.dependOn(&run_cmd.step);
}
