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

const MetricStats = struct {
    avg_ms: f64,
    max_ms: f64,
    p99_ms: f64,
};

fn computeMetricStats(samples: []u64) MetricStats {
    if (samples.len == 0) {
        return .{ .avg_ms = 0.0, .max_ms = 0.0, .p99_ms = 0.0 };
    }
    std.mem.sort(u64, samples, {}, std.sort.asc(u64));
    var sum: u128 = 0;
    for (samples) |s| {
        sum += s;
    }
    const avg_ns = @as(f64, @floatFromInt(sum)) / @as(f64, @floatFromInt(samples.len));
    const max_ns = @as(f64, @floatFromInt(samples[samples.len - 1]));
    const p99_idx = (samples.len * 99) / 100;
    const p99_ns = @as(f64, @floatFromInt(samples[p99_idx]));
    return .{
        .avg_ms = avg_ns / 1_000_000.0,
        .max_ms = max_ns / 1_000_000.0,
        .p99_ms = p99_ns / 1_000_000.0,
    };
}

const LoopTelemetry = struct {
    pump_samples: [512]u64 = undefined,
    pump_count: usize = 0,
    wl_samples: [512]u64 = undefined,
    wl_count: usize = 0,
    render_samples: [512]u64 = undefined,
    render_count: usize = 0,
    loop_frames: usize = 0,
    rendered_frames: usize = 0,
    window_start_ns: i64,

    fn init(now_ns: i64) LoopTelemetry {
        return .{ .window_start_ns = now_ns };
    }

    fn recordSample(buf: *[512]u64, count: *usize, duration_ns: i64) void {
        const clamped: u64 = @intCast(@max(0, duration_ns));
        buf[count.* % buf.len] = clamped;
        count.* += 1;
    }

    fn recordPump(self: *LoopTelemetry, duration_ns: i64) void {
        recordSample(&self.pump_samples, &self.pump_count, duration_ns);
    }

    fn recordWl(self: *LoopTelemetry, duration_ns: i64) void {
        recordSample(&self.wl_samples, &self.wl_count, duration_ns);
    }

    fn recordRender(self: *LoopTelemetry, duration_ns: i64) void {
        recordSample(&self.render_samples, &self.render_count, duration_ns);
        self.rendered_frames += 1;
    }

    fn maybeReport(self: *LoopTelemetry, now_ns: i64) void {
        const elapsed_ns = now_ns - self.window_start_ns;
        if (elapsed_ns < 1_000_000_000) return;

        const elapsed_s = @as(f64, @floatFromInt(elapsed_ns)) / 1_000_000_000.0;
        const fps: usize = @intFromFloat(@round(@as(f64, @floatFromInt(self.loop_frames)) / elapsed_s));

        const pump_stats = computeMetricStats(self.pump_samples[0..@min(self.pump_count, self.pump_samples.len)]);
        const wl_stats = computeMetricStats(self.wl_samples[0..@min(self.wl_count, self.wl_samples.len)]);
        const render_stats = computeMetricStats(self.render_samples[0..@min(self.render_count, self.render_samples.len)]);

        std.debug.print(
            "[PERF-LOOP] {d} fps | pump: avg {d:.2}ms max {d:.2}ms p99 {d:.2}ms | wl: avg {d:.2}ms max {d:.2}ms | render: avg {d:.2}ms max {d:.2}ms (rendered={d})\n",
            .{
                fps,
                pump_stats.avg_ms,
                pump_stats.max_ms,
                pump_stats.p99_ms,
                wl_stats.avg_ms,
                wl_stats.max_ms,
                render_stats.avg_ms,
                render_stats.max_ms,
                self.rendered_frames,
            },
        );

        self.pump_count = 0;
        self.wl_count = 0;
        self.render_count = 0;
        self.loop_frames = 0;
        self.rendered_frames = 0;
        self.window_start_ns = now_ns;
    }
};

var global_shell_state: ?*state_mod.ShellState = null;
var pointer_captured_by_web: bool = false;

fn onPointerEvent(event_type: u32, x: f32, y: f32, button: u32, state: u32) callconv(.c) void {
    if (global_shell_state) |shell| {
        const vp = shell.layout.viewport_rect;
        const active_tab = shell.getActiveTabConst();
        const is_internal = if (active_tab) |tab| state_mod.isInternalPage(tab.getUrl()) else true;
        const web_active = vp.contains(x, y) and !is_internal and !shell.history_open;

        // Event types: 0 = motion, 1 = button down, 2 = button up, 3 = axis/scroll
        if (event_type == 1) {
            if (web_active) {
                pointer_captured_by_web = true;
                wpe.setFocus(true);
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
            } else {
                pointer_captured_by_web = false;
                shell.handleMouseDown(x, y);
                if (shell.focus != .none) {
                    wpe.setFocus(false);
                }
            }
        } else if (event_type == 0) {
            if (pointer_captured_by_web) {
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
            } else if (web_active) {
                shell.handleMouseMove(-1.0, -1.0);
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
            } else {
                shell.handleMouseMove(x, y);
            }
        } else if (event_type == 2) {
            if (pointer_captured_by_web) {
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
                pointer_captured_by_web = false;
            } else {
                shell.handleMouseUp(x, y);
            }
        } else if (event_type == 3) {
            if (web_active) {
                const local_x: f64 = @floatCast(x - vp.x);
                const local_y: f64 = @floatCast(y - vp.y);
                wpe.sendPointer(event_type, local_x, local_y, button, state);
            }
        }
    }
}

fn onScrollEvent(x: f32, y: f32, delta_x: f64, delta_y: f64, source: u32, time_ms: u32, is_stop: u32) callconv(.c) void {
    if (global_shell_state) |shell| {
        const vp = shell.layout.viewport_rect;
        const active_tab = shell.getActiveTabConst();
        const is_internal = if (active_tab) |tab| state_mod.isInternalPage(tab.getUrl()) else true;
        const web_active = vp.contains(x, y) and !is_internal and !shell.history_open;
        if (web_active) {
            const local_x: f64 = @floatCast(x - vp.x);
            const local_y: f64 = @floatCast(y - vp.y);
            wpe.sendScroll(local_x, local_y, delta_x, delta_y, source, time_ms, is_stop != 0);
        }
    }
}

fn onKeyboardEvent(key: u32, state: u32, modifiers: u32) callconv(.c) void {
    if (global_shell_state) |shell| {
        const is_down = (state == 1);
        const shift = (modifiers & 1) != 0;
        const alt = (modifiers & 2) != 0;
        const ctrl = (modifiers & 4) != 0;
        shell.shift_pressed = shift;
        shell.alt_pressed = alt;
        shell.handleKey(key, is_down, ctrl);

        // Forward keystrokes to WPE only when neither omnibar nor search_hud is focused and history drawer is closed
        if (shell.focus == .none and !shell.history_open) {
            const active_tab = shell.getActiveTabConst();
            const is_internal = if (active_tab) |tab| state_mod.isInternalPage(tab.getUrl()) else true;
            if (!is_internal) {
                wpe.sendKeyboard(key, state, modifiers);
            }
        }
    }
}

fn onPageMetadataChanged(maybe_uri: ?[]const u8, maybe_title: ?[]const u8) void {
    if (global_shell_state) |shell| {
        shell.syncNavState();
        if (shell.getActiveTab()) |tab| {
            if (maybe_uri) |uri| {
                if (uri.len > 0) {
                    tab.setUrl(uri);
                    shell.omnibar.setText(uri);
                }
            }
            if (maybe_title) |title| {
                if (title.len > 0) {
                    tab.setTitle(title);
                }
            }
        }
        shell.ui_dirty = true;
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

    // Symmetric ownership & explicit LIFO defer teardown order:
    // 1. wpe.deinit() runs first (unmaps/unrefs WPE WebView & display while surface/wl_display are alive)
    // 2. ZG_DestroySurface(surface) runs second (destroys Vulkan surface/swapchain before window)
    // 3. ZG_DestroyWindow(win) runs last (destroys Wayland window/wl_display)
    const window = if (!headless) zgraphics.ZG_CreateWindow(width, height) else null;
    defer if (window) |win| zgraphics.ZG_DestroyWindow(win);

    const surface = zgraphics.ZG_CreateSurface(window, width, height) orelse {
        std.debug.print("[ZAWRA-SHELL] ERROR: Failed to create graphics surface\n", .{});
        return error.SurfaceCreationFailed;
    };
    defer zgraphics.ZG_DestroySurface(surface);
    defer wpe.deinit();

    var shell_state = try state_mod.ShellState.init(allocator, width, height);
    defer shell_state.deinit();

    var ui_renderer = try renderer_mod.UIRenderer.init(allocator, surface);
    defer ui_renderer.deinit();

    // Register global shell state & callbacks for input
    global_shell_state = &shell_state;
    renderer_mod.setGlobalUIRenderer(&ui_renderer);
    zgraphics.ZG_SetPointerCallback(&onPointerEvent);
    zgraphics.ZG_SetScrollCallback(&onScrollEvent);
    zgraphics.ZG_SetKeyboardCallback(&onKeyboardEvent);
    wpe.setMetadataCallback(&onPageMetadataChanged);
    defer {
        wpe.setMetadataCallback(null);
        zgraphics.ZG_SetPointerCallback(null);
        zgraphics.ZG_SetScrollCallback(null);
        zgraphics.ZG_SetKeyboardCallback(null);
        renderer_mod.setGlobalUIRenderer(null);
        global_shell_state = null;
    }

    const initial_is_internal = if (target_url) |url| state_mod.isInternalPage(url) else true;
    const sub_x: i32 = 260;
    const sub_y: i32 = 0;

    if (window) |win| {
        const wl_disp = zgraphics.ZG_GetWaylandDisplay(win);
        const wl_surf = zgraphics.ZG_GetWaylandSurface(win);
        const wl_subcomp = zgraphics.ZG_GetWaylandSubcompositor(win);
        const wl_comp = zgraphics.ZG_GetWaylandCompositor(win);
        const vp_w: i32 = if (width > 260) @intCast(width - 260) else 100;
        const vp_h: i32 = @intCast(height);
        std.debug.print("[ZAWRA-SHELL] Wayland handles: disp={?*anyopaque}, surf={?*anyopaque}, subcomp={?*anyopaque}, comp={?*anyopaque}\n", .{ wl_disp, wl_surf, wl_subcomp, wl_comp });
        std.debug.print("[ZAWRA-SHELL] Initializing WebKit Wayland Subsurface ({}, {}, {}x{})...\n", .{ sub_x, sub_y, vp_w, vp_h });
        wpe.init(wl_disp, wl_surf, wl_subcomp, wl_comp, sub_x, sub_y, vp_w, vp_h) catch |err| {
            std.debug.print("[ZAWRA-SHELL] WPE init failed: {}\n", .{err});
        };
        wpe.setSubsurfaceVisible(!initial_is_internal);
    }

    if (target_url) |url| {
        shell_state.navigateToUrl(url);
    }

    std.debug.print("[ZAWRA-SHELL] UI Shell initialized successfully! Entering frame loop...\n", .{});

    var frame_count: usize = 0;
    const is_limited = (max_frames != null);
    const limit = max_frames orelse 0;
    var current_hide_subsurface: bool = initial_is_internal;
    var current_vp_x: i32 = @intFromFloat(shell_state.layout.viewport_rect.x);
    var current_vp_w: u32 = @intFromFloat(shell_state.layout.viewport_rect.w);
    var current_vp_h: u32 = @intFromFloat(shell_state.layout.viewport_rect.h);
    var telemetry = LoopTelemetry.init(getMonotonicNs());

    while (!is_limited or frame_count < limit) : (frame_count += 1) {
        // 1. Pump GLib & WebKit event loop directly on Thread 1
        const pump_start_ns = getMonotonicNs();
        wpe.pumpEvents();
        telemetry.recordPump(getMonotonicNs() - pump_start_ns);

        // 2. Poll Wayland window events (only if WPE is not initialized)
        // Once WPE is initialized, WPEDisplayWayland's GSource is the sole reader/dispatcher on wl_display
        if (window) |win| {
            const wl_start_ns = getMonotonicNs();
            if (!wpe.isInitialized()) {
                zgraphics.ZG_PollEvents(win);
            } else {
                zgraphics.ZG_Flush(win);
            }
            if (zgraphics.ZG_ShouldClose(win)) {
                std.debug.print("[ZAWRA-SHELL] Close requested by compositor (xdg_toplevel::close); exiting cleanly.\n", .{});
                break;
            }
            telemetry.recordWl(getMonotonicNs() - wl_start_ns);
            var new_w: u32 = 0;
            var new_h: u32 = 0;
            if (zgraphics.ZG_CheckWindowResize(win, &new_w, &new_h)) {
                if (new_w > 0 and new_h > 0 and (new_w != shell_state.window_width or new_h != shell_state.window_height)) {
                    shell_state.setWindowSize(new_w, new_h);
                    zgraphics.ZG_RecreateSwapchain(surface, new_w, new_h);
                    std.debug.print("[ZAWRA-SHELL] Window resized to {}x{}\n", .{ new_w, new_h });
                }
            }
        }

        // Keep WPE subsurface position and size synchronized with viewport_rect (window resize + sidebar collapse)
        const vp_rect = shell_state.layout.viewport_rect;
        const vp_x: i32 = @intFromFloat(vp_rect.x);
        const vp_w: u32 = if (vp_rect.w > 0) @intFromFloat(vp_rect.w) else 1;
        const vp_h: u32 = if (vp_rect.h > 0) @intFromFloat(vp_rect.h) else 1;
        if (vp_x != current_vp_x or vp_w != current_vp_w or vp_h != current_vp_h) {
            current_vp_x = vp_x;
            current_vp_w = vp_w;
            current_vp_h = vp_h;
            wpe.setSubsurfacePosition(vp_x, 0);
            wpe.resize(vp_w, vp_h);
        }

        // 3. Keep WebKit subsurface visibility synchronized with internal pages & drawer visibility
        const active_tab = shell_state.getActiveTabConst();
        const is_internal = if (active_tab) |tab| state_mod.isInternalPage(tab.getUrl()) else true;
        const hide_subsurface = is_internal or shell_state.history_open;
        if (hide_subsurface != current_hide_subsurface) {
            if (hide_subsurface and !current_hide_subsurface) {
                wpe.detachSubsurfaceBuffer();
            }
            current_hide_subsurface = hide_subsurface;
            wpe.setSubsurfaceVisible(!hide_subsurface);
            shell_state.ui_dirty = true;
        }

        // 4. Render Zawra UI Shell frame only when UI is dirty
        if (shell_state.ui_dirty) {
            shell_state.ui_dirty = false;
            const render_start_ns = getMonotonicNs();
            ui_renderer.render(&shell_state);
            telemetry.recordRender(getMonotonicNs() - render_start_ns);
        }

        telemetry.loop_frames += 1;
        telemetry.maybeReport(getMonotonicNs());

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

pub export fn Zawra_UI_Run(argc: c_int, argv: ?[*]const ?[*:0]const u8) c_int {
    var width: u32 = 1280;
    var height: u32 = 800;
    var headless: bool = false;
    var max_frames: ?usize = null;
    var target_url: ?[]const u8 = null;

    if (argv) |args| {
        var i: usize = 1;
        const count: usize = if (argc > 0) @intCast(argc) else 0;
        while (i < count) : (i += 1) {
            if (args[i]) |arg_ptr| {
                const arg = std.mem.span(arg_ptr);
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
    var target_url_buf: [2048]u8 = undefined;
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
            const copy_len = @min(arg.len, target_url_buf.len);
            @memcpy(target_url_buf[0..copy_len], arg[0..copy_len]);
            target_url = target_url_buf[0..copy_len];
        }
    }

    try runShell(width, height, headless, max_frames, target_url);
}
