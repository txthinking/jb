const std = @import("std");

pub fn jb(allocator: std.mem.Allocator, name: []u8) !bool {
    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);
    const stdout = std.io.getStdOut().writer();
    const help =
        \\
        \\jb = javascript + bash
        \\
        \\$ jb /path/to/file.js
        \\$ jb https://example.com/file.js
        \\$ jb '$`ls -l`'
        \\
        \\v20231203
        \\
        \\https://github.com/txthinking/jb
        \\
    ;
    if (args.len == 1) {
        try stdout.print(help, .{});
        return false;
    }
    const arg = args[1][0..args[1].len];

    if (std.mem.eql(u8, arg, "help") or std.mem.eql(u8, arg, "--help") or std.mem.eql(u8, arg, "-h") or std.mem.eql(u8, arg, "version") or std.mem.eql(u8, arg, "--version") or std.mem.eql(u8, arg, "-v")) {
        try stdout.print(help, .{});
        return false;
    }

    var f = try std.fs.createFileAbsolute(name, .{ .truncate = true });
    defer f.close();

    var b = try allocator.alloc(u8, 1024 * 1024);
    defer allocator.free(b);
    const n = try fetch(allocator, arg, b);
    var it = std.mem.splitScalar(u8, b[0..n], '\n');

    var wrote = false;
    while (it.next()) |v| {
        var v1 = std.mem.trim(u8, v, " \t\r");
        if (std.mem.startsWith(u8, v1, "#!")) {
            continue;
        }
        if (!wrote and std.mem.startsWith(u8, v1, "/*")) {
            return error.DoNotUseBlockCommentsOnJSFile;
        }
        if (!wrote and v1.len != 0 and !std.mem.startsWith(u8, v1, "//") and !std.mem.startsWith(u8, v1, "import")) {
            const js = @embedFile("./jb.js");
            _ = try f.write(js);
            _ = try f.write("\n");
            wrote = true;
        }
        _ = try f.write(v);
        _ = try f.write("\n");
    }
    return true;
}

pub fn fetch(allocator: std.mem.Allocator, url: []const u8, b: []u8) !usize {
    if (std.mem.startsWith(u8, url, "http://") or std.mem.startsWith(u8, url, "https://")) {
        const uri = try std.Uri.parse(url);
        var client: std.http.Client = .{ .allocator = allocator };
        defer client.deinit();
        try client.loadDefaultProxies();
        var req = try client.open(.GET, uri, .{ .allocator = allocator }, .{});
        defer req.deinit();
        try req.send(.{});
        try req.wait();
        if (req.response.status != std.http.Status.ok) {
            return error.ResponseNotStatusOk;
        }
        const n = try req.readAll(b);
        if (n == b.len) {
            return error.ScriptTooLong;
        }
        return n;
    }
    if (std.fs.cwd().readFile(url, b)) |b1| {
        if (b1.len == b.len) {
            return error.ScriptTooLong;
        }
        return b1.len;
    } else |err| switch (err) { // why force me to use else :(
        error.FileNotFound => {},
        else => |leftover_err| return leftover_err,
    }
    if (url.len >= b.len) {
        return error.ScriptTooLong;
    }
    @memcpy(b[0..url.len], url);
    return url.len;
}

test "simple test" {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var b = try allocator.alloc(u8, 10);
    defer allocator.free(b);
    std.debug.print("{b}\n", .{b});
}
