const std = @import("std");
const zgraphics = @import("lib");
const state_mod = @import("state.zig");
const renderer_mod = @import("renderer.zig");
const wpe = @import("wpe.zig");

const SigType = @TypeOf(std.c.SIG.SEGV);

fn fatalSignalHandler(sig: SigType) callconv(.c) void {
    const sig_name: []const u8 = switch (sig) {
        std.c.SIG.SEGV => "SIGSEGV (Segmentation fault)",
        std.c.SIG.BUS => "SIGBUS (Bus error)",
        std.c.SIG.ABRT => "SIGABRT (Abort)",
        std.c.SIG.ILL => "SIGILL (Illegal instruction)",
        std.c.SIG.FPE => "SIGFPE (Floating point exception)",
        else => "Fatal Signal",
    };

    var line_buf: [256]u8 = undefined;
    const line = std.fmt.bufPrint(&line_buf, "[CRASH] Process: UIProcess | Reason: Fatal signal {d} ({s})\n", .{
        @intFromEnum(sig), sig_name,
    }) catch return;

    _ = std.c.write(2, line.ptr, line.len);

    const home = std.c.getenv("HOME");
    var path_buf: [256]u8 = undefined;
    const log_path = std.fmt.bufPrintZ(&path_buf, "{s}/.zawra/crash.log", .{
        if (home) |h| std.mem.span(h) else "/home/intro",
    }) catch return;

    const o_flags: std.c.O = @bitCast(@as(u32, 0o2101)); // O_WRONLY | O_CREAT | O_APPEND
    const fd = std.c.open(log_path.ptr, o_flags, @as(std.c.mode_t, 0o644));
    if (fd >= 0) {
        _ = std.c.write(fd, line.ptr, line.len);
        _ = std.c.close(fd);
    }

    std.debug.dumpCurrentStackTrace(.{ .first_address = @returnAddress() });

    var act: std.c.Sigaction = std.mem.zeroes(std.c.Sigaction);
    act.handler = .{ .handler = std.c.SIG.DFL };
    _ = std.c.sigaction(sig, &act, null);
    _ = std.c.raise(sig);
}

pub fn installFatalSignalHandler() void {
    const signals = [_]SigType{
        std.c.SIG.SEGV,
        std.c.SIG.BUS,
        std.c.SIG.ABRT,
        std.c.SIG.ILL,
        std.c.SIG.FPE,
    };
    var act: std.c.Sigaction = std.mem.zeroes(std.c.Sigaction);
    act.handler = .{ .handler = fatalSignalHandler };
    for (signals) |sig| {
        _ = std.c.sigaction(sig, &act, null);
    }
}

fn getMonotonicNs() i64 {
    var ts: std.os.linux.timespec = undefined;
    _ = std.os.linux.syscall2(.clock_gettime, 1, @intFromPtr(&ts));
    return @as(i64, ts.sec) * 1_000_000_000 + ts.nsec;
}

var global_shell_state: ?*state_mod.ShellState = null;

fn onPointerEvent(event_type: u32, x: f32, y: f32, button: u32, state: u32) callconv(.c) void {
    if (global_shell_state) |shell| {
        // Event types: 0 = motion, 1 = button down, 2 = button up, 3 = axis/scroll
        if (event_type == 0) {
            shell.handleMouseMove(x, y);
        } else if (event_type == 1) {
            shell.handleMouseDown(x, y);
        }

        // Viewport relative event forwarding to WPE
        const vp = shell.layout.viewport_rect;
        if (vp.contains(x, y)) {
            const active_tab = shell.getActiveTabConst();
            const is_start = if (active_tab) |tab| state_mod.isStartPage(tab.getUrl()) else true;
            if (!is_start) {
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
            }
        }
    }
}

fn onKeyboardEvent(key: u32, state: u32, ctrl: bool) callconv(.c) void {
    if (global_shell_state) |shell| {
        const is_down = (state == 1);
        shell.handleKey(key, is_down, ctrl);

        // Forward keystrokes to WPE only when neither omnibar nor search_hud is focused
        if (shell.focus == .none) {
            const active_tab = shell.getActiveTabConst();
            const is_start = if (active_tab) |tab| state_mod.isStartPage(tab.getUrl()) else true;
            if (!is_start) {
                const mods: u32 = if (ctrl) 4 else 0;
                wpe.sendKeyboard(key, state, mods);
            }
        }
    }
}

pub fn runShell(width: u32, height: u32, headless: bool, max_frames: ?usize, target_url: ?[]const u8) !void {
    installFatalSignalHandler();
    const allocator = std.heap.c_allocator;
    std.debug.print("[ZAWRA-SHELL] Initializing native Zig UI Shell ({}x{})...\n", .{ width, height });

    if (!zgraphics.ZG_Initialize()) {
        std.debug.print("[ZAWRA-SHELL] ERROR: Failed to initialize z-graphics\n", .{});
        return error.GraphicsInitFailed;
    }

    const window = if (!headless) zgraphics.ZG_CreateWindow(width, height) else null;
    const surface = zgraphics.ZG_CreateSurface(window, width, height) orelse {
        std.debug.print("[ZAWRA-SHELL] ERROR: Failed to create graphics surface\n", .{});
        return error.SurfaceCreationFailed;
    };
    defer zgraphics.ZG_DestroySurface(surface);

    var shell_state = try state_mod.ShellState.init(allocator, width, height);
    defer shell_state.deinit();

    var ui_renderer = try renderer_mod.UIRenderer.init(allocator, surface);
    defer ui_renderer.deinit();

    // Register global shell state & callbacks for input
    global_shell_state = &shell_state;
    renderer_mod.setGlobalUIRenderer(&ui_renderer);
    zgraphics.ZG_SetPointerCallback(&onPointerEvent);
    zgraphics.ZG_SetKeyboardCallback(&onKeyboardEvent);
    defer {
        zgraphics.ZG_SetPointerCallback(null);
        zgraphics.ZG_SetKeyboardCallback(null);
        renderer_mod.setGlobalUIRenderer(null);
        global_shell_state = null;
    }

    const initial_is_start = if (target_url) |url| state_mod.isStartPage(url) else true;
    const sub_x: i32 = 260;
    const sub_y: i32 = 0;

    if (window) |win| {
        const wl_disp = zgraphics.ZG_GetWaylandDisplay(win);
        const wl_surf = zgraphics.ZG_GetWaylandSurface(win);
        const wl_subcomp = zgraphics.ZG_GetWaylandSubcompositor(win);
        const vp_w: i32 = if (width > 260) @intCast(width - 260) else 100;
        const vp_h: i32 = @intCast(height);
        std.debug.print("[ZAWRA-SHELL] Wayland handles: disp={?*anyopaque}, surf={?*anyopaque}, subcomp={?*anyopaque}\n", .{ wl_disp, wl_surf, wl_subcomp });
        std.debug.print("[ZAWRA-SHELL] Initializing WebKit Wayland Subsurface ({}, {}, {}x{})...\n", .{ sub_x, sub_y, vp_w, vp_h });
        wpe.init(wl_disp, wl_surf, wl_subcomp, sub_x, sub_y, vp_w, vp_h) catch |err| {
            std.debug.print("[ZAWRA-SHELL] WPE init failed: {}\n", .{err});
        };
        wpe.setSubsurfaceVisible(!initial_is_start);
    }

    if (target_url) |url| {
        shell_state.navigateToUrl(url);
    }

    std.debug.print("[ZAWRA-SHELL] UI Shell initialized successfully! Entering frame loop...\n", .{});

    var frame_count: usize = 0;
    const is_limited = (max_frames != null);
    const limit = max_frames orelse 0;
    var current_is_start: bool = initial_is_start;

    while (!is_limited or frame_count < limit) : (frame_count += 1) {
        // 1. Pump GLib & WebKit event loop directly on Thread 1
        wpe.pumpEvents();

        // 2. Poll Wayland window events (only if WPE is not initialized)
        // Once WPE is initialized, WPEDisplayWayland's GSource is the sole reader/dispatcher on wl_display
        if (window) |win| {
            if (!wpe.isInitialized()) {
                zgraphics.ZG_PollEvents(win);
            } else {
                zgraphics.ZG_Flush(win);
            }
            var new_w: u32 = 0;
            var new_h: u32 = 0;
            if (zgraphics.ZG_CheckWindowResize(win, &new_w, &new_h)) {
                if (new_w > 0 and new_h > 0 and (new_w != shell_state.window_width or new_h != shell_state.window_height)) {
                    shell_state.setWindowSize(new_w, new_h);
                    zgraphics.ZG_RecreateSwapchain(surface, new_w, new_h);
                    if (new_w > 260) {
                        wpe.resize(new_w - 260, new_h);
                    }
                    std.debug.print("[ZAWRA-SHELL] Window resized to {}x{}\n", .{ new_w, new_h });
                }
            }
        }

        // 3. Keep WebKit subsurface visibility synchronized with Start Page visibility
        const active_tab = shell_state.getActiveTabConst();
        const is_start = if (active_tab) |tab| state_mod.isStartPage(tab.getUrl()) else true;
        if (is_start != current_is_start) {
            current_is_start = is_start;
            wpe.setSubsurfaceVisible(!is_start);
        } else if (is_start) {
            wpe.detachSubsurfaceBuffer();
        }

        // 4. Animate or update layout if needed
        shell_state.recomputeLayout();

        // 5. Render Zawra UI Shell frame (Pass 2 UI Elements: sidebar, start page, tabs)
        ui_renderer.render(&shell_state);

        if (is_limited and frame_count + 1 >= limit) break;

        // In interactive mode sleep / pump up to ~16ms (~60fps)
        if (!is_limited) {
            const start_ns = getMonotonicNs();
            const frame_budget_ns: i64 = 16 * 1000 * 1000;
            while (true) {
                const elapsed = getMonotonicNs() - start_ns;
                if (elapsed >= frame_budget_ns) break;
                if (wpe.pumpEventsSingle() == 0) {
                    const req = std.os.linux.timespec{ .sec = 0, .nsec = 1 * 1000 * 1000 };
                    _ = std.os.linux.nanosleep(&req, null);
                }
            }
        }
    }

    std.debug.print("[ZAWRA-SHELL] Frame loop finished after {} frames.\n", .{frame_count});
}

pub export fn Zawra_UI_Run(argc: c_int, argv: ?[*][*:0]const u8) c_int {
    var width: u32 = 1280;
    var height: u32 = 800;
    var headless: bool = false;
    var max_frames: ?usize = null;
    var target_url: ?[]const u8 = null;

    if (argv) |args| {
        var i: usize = 1;
        const count: usize = if (argc > 0) @intCast(argc) else 0;
        while (i < count) : (i += 1) {
            const arg = std.mem.span(args[i]);
            if (std.mem.eql(u8, arg, "--headless")) {
                headless = true;
            } else if (std.mem.eql(u8, arg, "--smoke")) {
                max_frames = 10;
            } else if (std.mem.startsWith(u8, arg, "--frames=")) {
                max_frames = std.fmt.parseInt(usize, arg[9..], 10) catch null;
            } else if (std.mem.startsWith(u8, arg, "--width=")) {
                width = std.fmt.parseInt(u32, arg[8..], 10) catch 1280;
            } else if (std.mem.startsWith(u8, arg, "--height=")) {
                height = std.fmt.parseInt(u32, arg[9..], 10) catch 800;
            } else if (!std.mem.startsWith(u8, arg, "--")) {
                target_url = arg;
            }
        }
    }

    runShell(width, height, headless, max_frames, target_url) catch |err| {
        std.debug.print("[ZAWRA-SHELL] Error: {}\n", .{err});
        return 1;
    };
    return 0;
}

pub export fn roundq(x: f128) f128 {
    return @round(x);
}

pub fn runShellFromArgs(init: std.process.Init.Minimal) !void {
    const allocator = std.heap.c_allocator;

    var args = try init.args.iterateAllocator(allocator);
    defer args.deinit();

    var width: u32 = 1280;
    var height: u32 = 800;
    var headless: bool = false;
    var max_frames: ?usize = null;
    var target_url: ?[]const u8 = null;

    _ = args.next(); // skip exe name
    while (args.next()) |arg| {
        if (std.mem.eql(u8, arg, "--headless")) {
            headless = true;
        } else if (std.mem.eql(u8, arg, "--smoke")) {
            max_frames = 10;
        } else if (std.mem.startsWith(u8, arg, "--frames=")) {
            max_frames = try std.fmt.parseInt(usize, arg[9..], 10);
        } else if (std.mem.startsWith(u8, arg, "--width=")) {
            width = try std.fmt.parseInt(u32, arg[8..], 10);
        } else if (std.mem.startsWith(u8, arg, "--height=")) {
            height = try std.fmt.parseInt(u32, arg[9..], 10);
        } else if (!std.mem.startsWith(u8, arg, "--")) {
            target_url = arg;
        }
    }

    try runShell(width, height, headless, max_frames, target_url);
}
