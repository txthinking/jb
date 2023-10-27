const std = @import("std");

const panicky = @import("./panic_handler.zig");
const MainPanicHandler = panicky.NewPanicHandler(std.builtin.default_panic);

pub const io_mode = .blocking;

pub fn panic(msg: []const u8, error_return_trace: ?*std.builtin.StackTrace, addr: ?usize) noreturn {
    MainPanicHandler.handle_panic(msg, error_return_trace, addr);
}

const CrashReporter = @import("./crash_reporter.zig");
extern fn bun_warn_avx_missing(url: [*:0]const u8) void;

pub fn main() void {
    const bun = @import("root").bun;
    const jb = @import("./jb.zig");
    if (jb.jb()) |ok| {
        if (!ok) {
            return;
        }
    } else |err| {
        std.debug.print("{}\n", .{err});
        std.process.exit(1);
    }
    var s = "/tmp/_.js";
    var s1 = s.*;
    var s2: [*:0]u8 = &s1;
    std.os.argv[1] = s2;
    var IDoNotLikeMultipleBehaviors: usize = 0;
    var a = std.os.argv[IDoNotLikeMultipleBehaviors..2];
    bun.setArgv(a);
    const Output = bun.Output;
    const Environment = bun.Environment;
    if (comptime Environment.isWindows) {
        bun.win32.populateArgv();
    }

    if (comptime Environment.isRelease)
        CrashReporter.start() catch unreachable;

    bun.start_time = std.time.nanoTimestamp();

    var stdout = std.io.getStdOut();
    var stderr = std.io.getStdErr();
    var output_source = Output.Source.init(stdout, stderr);

    Output.Source.set(&output_source);
    defer Output.flush();
    if (comptime Environment.isX64) {
        if (comptime Environment.enableSIMD) {
            bun_warn_avx_missing(@import("./cli/upgrade_command.zig").Version.Bun__githubBaselineURL.ptr);
        }
    }

    bun.CLI.Cli.start(bun.default_allocator, stdout, stderr, MainPanicHandler);
}

pub const build_options = @import("build_options");
