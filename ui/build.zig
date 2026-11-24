const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Generate shader module embedding precompiled SPIR-V binaries
    const shader_gen = b.addWriteFiles();
    _ = shader_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/ui_sdf.vert.spv"), "ui_sdf.vert.spv");
    _ = shader_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/ui_sdf.frag.spv"), "ui_sdf.frag.spv");
    const shader_zig = shader_gen.add("shaders.zig",
        \\pub const ui_sdf_vert = @embedFile("ui_sdf.vert.spv");
        \\pub const ui_sdf_frag = @embedFile("ui_sdf.frag.spv");
    );
    const shaders_mod = b.createModule(.{
        .root_source_file = shader_zig,
    });

    // z-graphics RHI module
    const zg_mod = b.createModule(.{
        .root_source_file = b.path("../dependencies/z-graphics/src/lib.zig"),
        .target = target,
        .optimize = optimize,
        .pic = true,
    });
    zg_mod.link_libc = true;
    zg_mod.addIncludePath(b.path("../dependencies/z-graphics/src/platform"));
    zg_mod.addCSourceFile(.{
        .file = b.path("../dependencies/z-graphics/src/platform/xdg-shell-protocol.c"),
        .flags = &.{},
    });
    zg_mod.linkSystemLibrary("wayland-client", .{});
    zg_mod.linkSystemLibrary("X11", .{});

    // Shaders for z-graphics
    const zg_shaders_gen = b.addWriteFiles();
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/basic.vert.spv"), "basic.vert.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/basic.frag.spv"), "basic.frag.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/shader_test.frag.spv"), "shader_test.frag.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/instanced.vert.spv"), "instanced.vert.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/compute.comp.spv"), "compute.comp.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/ui_sdf.vert.spv"), "ui_sdf.vert.spv");
    _ = zg_shaders_gen.addCopyFile(b.path("../dependencies/z-graphics/shaders/ui_sdf.frag.spv"), "ui_sdf.frag.spv");
    const zg_shaders_zig = zg_shaders_gen.add("shaders.zig",
        \\pub const vert = @embedFile("basic.vert.spv");
        \\pub const frag = @embedFile("basic.frag.spv");
        \\pub const shader_test = @embedFile("shader_test.frag.spv");
        \\pub const instanced_vert = @embedFile("instanced.vert.spv");
        \\pub const compute = @embedFile("compute.comp.spv");
        \\pub const ui_sdf_vert = @embedFile("ui_sdf.vert.spv");
        \\pub const ui_sdf_frag = @embedFile("ui_sdf.frag.spv");
    );
    const zg_shaders_mod = b.createModule(.{
        .root_source_file = zg_shaders_zig,
    });
    zg_mod.addImport("shaders", zg_shaders_mod);
    zg_mod.addImport("lib", zg_mod);

    // Zawra UI module
    const ui_mod = b.createModule(.{
        .root_source_file = b.path("shell.zig"),
        .target = target,
        .optimize = optimize,
        .pic = true,
    });
    ui_mod.addImport("shaders", shaders_mod);
    ui_mod.addImport("lib", zg_mod);
    ui_mod.link_libc = true;
    ui_mod.linkSystemLibrary("wayland-client", .{});
    ui_mod.addIncludePath(b.path("../dependencies/z-graphics/src/platform"));

    // Static library libzawra-ui.a
    const ui_lib = b.addLibrary(.{
        .linkage = .static,
        .name = "zawra-ui",
        .root_module = ui_mod,
    });
    ui_lib.bundle_compiler_rt = true;
    b.installArtifact(ui_lib);
}
