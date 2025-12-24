const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // clikr executable
    const exe = b.addExecutable(.{
        .name = "clikr",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{ .file = b.path("src/main.c"), .flags = &.{"-std=c17"} });
    exe.linkLibC();
    b.installArtifact(exe);

    // Build cmocka as a static lib
    const cmocka = b.addStaticLibrary(.{
        .name = "cmocka",
        .target = target,
        .optimize = optimize,
    });

    // Add cmocka sources
    cmocka.addIncludePath(b.path("external/cmocka/include"));
    cmocka.addCSourceFile(.{ .file = b.path("external/cmocka/src/cmocka.c"), .flags = &.{"-std=c17"} });
    cmocka.linkLibC();

    // Test executable
    const test_exe = b.addExecutable(.{ .name = "clikr_tests", .target = target, .optimize = optimize });
    test_exe.addCSourceFile(.{ .file = b.path("tests/test_main.c"), .flags = &.{"-std=c17"} });
    test_exe.addIncludePath(b.path("external/cmocka/include"));
    test_exe.linkLibrary(cmocka);
    test_exe.linkLibC();

    const test_step = b.addRunArtifact(test_exe);
    const test_cmd = b.step("test", "Run tests");
    test_cmd.dependOn(&test_step.step);
}
