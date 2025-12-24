const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const clikr_lib = b.addStaticLibrary(.{
        .name = "clikr_lib",
        .target = target,
        .optimize = optimize,
    });

    const prod_sources = readSourcesFile(b, "build/prod_sources.txt");
    addCSources(clikr_lib, b, prod_sources);

    clikr_lib.addIncludePath(b.path("src"));
    clikr_lib.linkLibC();

    // clikr executable
    const exe = b.addExecutable(.{
        .name = "clikr",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{ .file = b.path("src/main.c"), .flags = &.{"-std=c17"} });
    exe.addIncludePath(b.path("src"));
    exe.linkLibrary(clikr_lib);
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

    const test_sources = readSourcesFile(b, "build/test_sources.txt");
    addCSources(test_exe, b, test_sources);

    test_exe.addIncludePath(b.path("external/cmocka/include"));
    test_exe.addIncludePath(b.path("src"));
    test_exe.linkLibrary(clikr_lib);
    test_exe.linkLibrary(cmocka);
    test_exe.linkLibC();

    const test_step = b.addRunArtifact(test_exe);
    const test_cmd = b.step("test", "Run tests");
    test_cmd.dependOn(&test_step.step);
}

fn addCSources(
    m: *std.Build.Step.Compile,
    b: *std.Build,
    files: []const []const u8,
) void {
    for (files) |p| {
        m.addCSourceFile(.{ .file = b.path(p), .flags = &.{"-std=c17"} });
    }
}

fn readSourcesFile(b: *std.Build, path: []const u8) []const []const u8 {
    const allocator = b.allocator;
    const content = std.fs.cwd().readFileAlloc(allocator, path, 10 * 1024) catch @panic("read sources file failed");
    defer allocator.free(content);

    var list = std.ArrayList([]const u8).init(allocator);
    var it = std.mem.splitScalar(u8, content, '\n');
    while (it.next()) |line| {
        const trimmed = std.mem.trim(u8, line, " \t\r");
        if (trimmed.len == 0) continue;
        if (trimmed[0] == '#') continue; // allow comments
        list.append(allocator.dupe(u8, trimmed) catch @panic("OOM")) catch @panic("OOM");
    }
    return list.toOwnedSlice() catch @panic("OOM");
}
