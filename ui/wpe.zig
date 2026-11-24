//! Zawra Browser — Direct WPE WebKit Wayland Subsurface Bridge
//!
//! Owns WPE WebKit lifecycle on Thread 1:
//! - Loads libWPEWebKit-2.0.so via std.DynLib
//! - Directly drives the Wayland subsurface lifecycle
//! - Directly forwards mouse, keyboard, resize, and URL load events
//! - Directly pumps GLib event iteration on Thread 1

const std = @import("std");
const wayland = @cImport({
    @cInclude("wayland-client.h");
});

extern "c" fn g_main_context_iteration(context: ?*anyopaque, may_block: c_int) callconv(.c) c_int;

const GObjectNewFn = *const fn (usize, [*:0]const u8, ...) callconv(.c) ?*anyopaque;

const WpeSymbols = struct {
    wpe_display_wayland_set_custom_wl_display: ?*const fn (?*anyopaque) callconv(.c) void = null,
    wpe_toplevel_wayland_set_parent_surface: ?*const fn (?*anyopaque, ?*anyopaque, c_int, c_int) callconv(.c) void = null,
    wpe_toplevel_wayland_set_subsurface_position: ?*const fn (?*anyopaque, c_int, c_int) callconv(.c) void = null,
    wpe_toplevel_wayland_get_wl_subsurface: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    wpe_toplevel_wayland_get_wl_surface: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    wpe_display_wayland_new: ?*const fn () callconv(.c) ?*anyopaque = null,
    wpe_display_connect: ?*const fn (?*anyopaque, ?*?*anyopaque) callconv(.c) c_int = null,
    webkit_web_view_get_type: ?*const fn () callconv(.c) usize = null,
    g_object_new: ?GObjectNewFn = null,
    webkit_web_view_get_wpe_view: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    wpe_view_get_toplevel: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    wpe_toplevel_resize: ?*const fn (?*anyopaque, c_int, c_int) callconv(.c) void = null,
    wpe_view_map: ?*const fn (?*anyopaque) callconv(.c) void = null,
    wpe_view_unmap: ?*const fn (?*anyopaque) callconv(.c) void = null,
    wpe_view_set_visible: ?*const fn (?*anyopaque, c_int) callconv(.c) void = null,
    wpe_view_focus_in: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_load_uri: ?*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void = null,
    wpe_view_event: ?*const fn (?*anyopaque, ?*anyopaque) callconv(.c) void = null,
    wpe_event_unref: ?*const fn (?*anyopaque) callconv(.c) void = null,
    wpe_event_pointer_move_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, f64, f64, f64, f64) callconv(.c) ?*anyopaque = null,
    wpe_event_pointer_button_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, u32, f64, f64, u32) callconv(.c) ?*anyopaque = null,
    wpe_event_keyboard_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, u32, u32) callconv(.c) ?*anyopaque = null,
    g_signal_connect_data: ?*const fn (
        instance: ?*anyopaque,
        detailed_signal: [*:0]const u8,
        c_handler: ?*const anyopaque,
        data: ?*anyopaque,
        destroy_data: ?*anyopaque,
        connect_flags: c_int,
    ) callconv(.c) c_ulong = null,
    webkit_web_view_get_settings: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    webkit_settings_set_user_agent: ?*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void = null,
    webkit_settings_set_enable_developer_extras: ?*const fn (?*anyopaque, c_int) callconv(.c) void = null,
    webkit_web_view_get_uri: ?*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8 = null,
    webkit_web_view_get_title: ?*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8 = null,
};

var wpe_lib: ?std.DynLib = null;
var syms: WpeSymbols = .{};

var web_view: ?*anyopaque = null;
var wpe_view: ?*anyopaque = null;
var toplevel: ?*anyopaque = null;
var subsurface: ?*anyopaque = null;
var child_surface: ?*anyopaque = null;
var initialized: bool = false;

pub fn isInitialized() bool {
    return initialized;
}

fn openWpeLibrary() !std.DynLib {
    // 1. Check explicit environment override
    if (std.c.getenv("ZAWRA_WPE_LIB_PATH")) |env_path| {
        if (std.DynLib.open(std.mem.span(env_path))) |lib| return lib else |_| {}
    }
    if (std.c.getenv("WPE_PATH")) |wpe_path| {
        if (std.DynLib.open(std.mem.span(wpe_path))) |lib| return lib else |_| {}
    }

    // 2. Known local build directories
    const fallbacks = [_][]const u8{
        "/home/intro/spectre-enviroment/browser/zawra-browser/webkit/build/lib/libWPEWebKit-2.0.so",
        "libWPEWebKit-2.0.so",
        "libWPEWebKit-2.0.so.1",
        "/usr/lib/libWPEWebKit-2.0.so",
        "/usr/lib64/libWPEWebKit-2.0.so",
        "/usr/lib/x86_64-linux-gnu/libWPEWebKit-2.0.so",
    };

    for (fallbacks) |path| {
        if (std.DynLib.open(path)) |lib| {
            return lib;
        } else |_| {}
    }

    return error.WpeLibraryNotFound;
}

fn appendCrashLog(process_name: []const u8, reason: []const u8) void {
    const home_dir: []const u8 = if (std.c.getenv("HOME")) |h| std.mem.span(h) else "/home/intro";
    var log_path_buf: [256]u8 = undefined;
    const log_path = std.fmt.bufPrintZ(&log_path_buf, "{s}/.zawra/crash.log", .{home_dir}) catch return;

    const file = std.c.fopen(log_path.ptr, "a") orelse return;
    defer _ = std.c.fclose(file);

    var line_buf: [256]u8 = undefined;
    const line = std.fmt.bufPrint(&line_buf, "[CRASH] Process: {s} | Reason: {s}\n", .{
        process_name, reason,
    }) catch return;

    _ = std.c.fwrite(line.ptr, 1, line.len, file);
}

pub const GError = extern struct {
    domain: u32,
    code: c_int,
    message: ?[*:0]const u8,
};

fn onWebProcessTerminated(
    _: ?*anyopaque,
    reason: c_int,
    _: ?*anyopaque,
) callconv(.c) void {
    // WebKit 2.54 WebKitWebProcessTerminationReason:
    // 0 = WEBKIT_WEB_PROCESS_CRASHED
    // 1 = WEBKIT_WEB_PROCESS_EXCEEDED_MEMORY_LIMIT
    // 2 = WEBKIT_WEB_PROCESS_TERMINATED_BY_API
    if (reason == 2) {
        std.debug.print("[ZAWRA-WPE] Web process cleanly terminated by API (tab closed or navigated).\n", .{});
        return;
    }

    const reason_str: []const u8 = switch (reason) {
        0 => "WEBKIT_WEB_PROCESS_CRASHED (Abnormal signal, abort, or GPF)",
        1 => "WEBKIT_WEB_PROCESS_EXCEEDED_MEMORY_LIMIT (OOM)",
        else => "UNKNOWN_TERMINATION_REASON",
    };

    std.debug.print(
        "\n" ++
        "╔═════════════════════════════════════════════════════════════════════╗\n" ++
        "║ [ZAWRA-CRASH] WebKit Child Process Terminated!                      ║\n" ++
        "║   Process : WPEWebProcess                                           ║\n" ++
        "║   Reason  : {s:<48}║\n" ++
        "║   Code    : {d:<48}║\n" ++
        "║   LogFile : ~/.zawra/crash.log                                      ║\n" ++
        "╚═════════════════════════════════════════════════════════════════════╝\n",
        .{ reason_str, reason },
    );

    appendCrashLog("WPEWebProcess", reason_str);
}

const ExitPacket = extern struct {
    pid: u32,
    status: u32,
};

extern "c" fn hajr_get_supervisor_status_fd(process_type: u32) callconv(.c) c_int;

pub fn checkSupervisorStatus() void {
    const fd = hajr_get_supervisor_status_fd(0); // 0 = web process
    if (fd < 0) return;

    var pfd = [_]std.os.linux.pollfd{.{
        .fd = fd,
        .events = std.os.linux.POLL.IN | std.os.linux.POLL.HUP | std.os.linux.POLL.ERR,
        .revents = 0,
    }};
    const poll_res = std.os.linux.syscall3(.poll, @intFromPtr(&pfd), 1, 0);
    if (poll_res > 0 and (pfd[0].revents & (std.os.linux.POLL.IN | std.os.linux.POLL.HUP)) != 0) {
        var packet: ExitPacket = undefined;
        const n = std.os.linux.syscall3(.read, @as(usize, @intCast(fd)), @intFromPtr(&packet), @sizeOf(ExitPacket));
        if (@as(isize, @bitCast(n)) == @sizeOf(ExitPacket)) {
            if (std.posix.W.IFSIGNALED(packet.status)) {
                const sig = @intFromEnum(std.posix.W.TERMSIG(packet.status));
                const sig_name: []const u8 = switch (sig) {
                    31 => "SIGSYS (Seccomp policy denial)",
                    11 => "SIGSEGV (Segmentation fault)",
                    6 => "SIGABRT (Abort / Assertion failure)",
                    9 => "SIGKILL (Killed)",
                    else => "SIGNAL",
                };
                std.debug.print(
                    "\n" ++
                    "╔═════════════════════════════════════════════════════════════════════╗\n" ++
                    "║ [HAJR-SUPERVISOR] WebKit Child Process Terminated by Signal!        ║\n" ++
                    "║   Process : WPEWebProcess (PID {d:<39})║\n" ++
                    "║   Signal  : {d:<4} ({s:<42})║\n" ++
                    "║   LogFile : ~/.zawra/crash.log                                      ║\n" ++
                    "╚═════════════════════════════════════════════════════════════════════╝\n",
                    .{ packet.pid, sig, sig_name },
                );
                var reason_buf: [128]u8 = undefined;
                const reason = std.fmt.bufPrint(&reason_buf, "Terminated by signal {d} ({s})", .{ sig, sig_name }) catch "Signal termination";
                appendCrashLog("WPEWebProcess", reason);
            } else if (std.posix.W.IFEXITED(packet.status)) {
                const code = std.posix.W.EXITSTATUS(packet.status);
                if (code != 0) {
                    std.debug.print("[HAJR-SUPERVISOR] WPEWebProcess exited with error code {d}\n", .{code});
                    var reason_buf: [128]u8 = undefined;
                    const reason = std.fmt.bufPrint(&reason_buf, "Exited with code {d}", .{code}) catch "Non-zero exit";
                    appendCrashLog("WPEWebProcess", reason);
                }
            }
        }
    }
}

fn onLoadFailed(
    _: ?*anyopaque,
    load_event: c_int,
    failing_uri: ?[*:0]const u8,
    gerror: ?*const GError,
    _: ?*anyopaque,
) callconv(.c) c_int {
    _ = load_event;
    const uri_str = if (failing_uri) |u| std.mem.span(u) else "<unknown-uri>";
    const err_msg = if (gerror) |ge| if (ge.message) |m| std.mem.span(m) else "No error message" else "No GError info";
    const err_code = if (gerror) |ge| ge.code else 0;

    std.debug.print(
        "\n[ZAWRA-LOAD-FAIL] Failed to load URL: '{s}'\n" ++
        "  Error code: {d}\n" ++
        "  Reason:     {s}\n",
        .{ uri_str, err_code, err_msg },
    );
    return 0; // Return FALSE to allow default handling
}

pub const MetadataCallback = *const fn (maybe_uri: ?[]const u8, maybe_title: ?[]const u8) void;
var metadata_callback: ?MetadataCallback = null;

pub fn setMetadataCallback(cb: ?MetadataCallback) void {
    metadata_callback = cb;
}

pub fn syncPageMetadata() void {
    if (web_view) |view| {
        var current_uri: ?[]const u8 = null;
        if (syms.webkit_web_view_get_uri) |get_uri_fn| {
            if (get_uri_fn(view)) |u| {
                current_uri = std.mem.span(u);
            }
        }
        var current_title: ?[]const u8 = null;
        if (syms.webkit_web_view_get_title) |get_title_fn| {
            if (get_title_fn(view)) |t| {
                current_title = std.mem.span(t);
            }
        }
        if (metadata_callback) |cb| {
            cb(current_uri, current_title);
        }
    }
}

fn onLoadChanged(
    _: ?*anyopaque,
    load_event: c_int,
    _: ?*anyopaque,
) callconv(.c) void {
    const event_name = switch (load_event) {
        0 => "STARTED",
        1 => "REDIRECTED",
        2 => "COMMITTED",
        3 => "FINISHED",
        else => "UNKNOWN",
    };
    std.debug.print("[ZAWRA-LOAD] Page load state: {s} ({d})\n", .{ event_name, load_event });
    if (load_event == 2 or load_event == 3) {
        syncPageMetadata();
    }
}

pub fn init(
    wl_display: ?*anyopaque,
    wl_surface: ?*anyopaque,
    wl_subcompositor: ?*anyopaque,
    x: i32,
    y: i32,
    width: i32,
    height: i32,
) !void {
    if (initialized) return;

    var lib = try openWpeLibrary();
    wpe_lib = lib;

    syms = WpeSymbols{
        .wpe_display_wayland_set_custom_wl_display = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_display_wayland_set_custom_wl_display"),
        .wpe_toplevel_wayland_set_parent_surface = lib.lookup(*const fn (?*anyopaque, ?*anyopaque, c_int, c_int) callconv(.c) void, "wpe_toplevel_wayland_set_parent_surface"),
        .wpe_toplevel_wayland_set_subsurface_position = lib.lookup(*const fn (?*anyopaque, c_int, c_int) callconv(.c) void, "wpe_toplevel_wayland_set_subsurface_position"),
        .wpe_toplevel_wayland_get_wl_subsurface = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?*anyopaque, "wpe_toplevel_wayland_get_wl_subsurface"),
        .wpe_toplevel_wayland_get_wl_surface = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?*anyopaque, "wpe_toplevel_wayland_get_wl_surface"),
        .wpe_display_wayland_new = lib.lookup(*const fn () callconv(.c) ?*anyopaque, "wpe_display_wayland_new"),
        .wpe_display_connect = lib.lookup(*const fn (?*anyopaque, ?*?*anyopaque) callconv(.c) c_int, "wpe_display_connect"),
        .webkit_web_view_get_type = lib.lookup(*const fn () callconv(.c) usize, "webkit_web_view_get_type"),
        .g_object_new = lib.lookup(GObjectNewFn, "g_object_new"),
        .webkit_web_view_get_wpe_view = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?*anyopaque, "webkit_web_view_get_wpe_view"),
        .wpe_view_get_toplevel = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?*anyopaque, "wpe_view_get_toplevel"),
        .wpe_toplevel_resize = lib.lookup(*const fn (?*anyopaque, c_int, c_int) callconv(.c) void, "wpe_toplevel_resize"),
        .wpe_view_map = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_view_map"),
        .wpe_view_unmap = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_view_unmap"),
        .wpe_view_set_visible = lib.lookup(*const fn (?*anyopaque, c_int) callconv(.c) void, "wpe_view_set_visible"),
        .wpe_view_focus_in = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_view_focus_in"),
        .webkit_web_view_load_uri = lib.lookup(*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void, "webkit_web_view_load_uri"),
        .wpe_view_event = lib.lookup(*const fn (?*anyopaque, ?*anyopaque) callconv(.c) void, "wpe_view_event"),
        .wpe_event_unref = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_event_unref"),
        .wpe_event_pointer_move_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, f64, f64, f64, f64) callconv(.c) ?*anyopaque, "wpe_event_pointer_move_new"),
        .wpe_event_pointer_button_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, u32, f64, f64, u32) callconv(.c) ?*anyopaque, "wpe_event_pointer_button_new"),
        .wpe_event_keyboard_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, u32, u32) callconv(.c) ?*anyopaque, "wpe_event_keyboard_new"),
        .g_signal_connect_data = lib.lookup(*const fn (?*anyopaque, [*:0]const u8, ?*const anyopaque, ?*anyopaque, ?*anyopaque, c_int) callconv(.c) c_ulong, "g_signal_connect_data"),
    };

    std.debug.print("[ZAWRA-WPE] Attached Wayland handles: disp={?*anyopaque}, surf={?*anyopaque}, subcomp={?*anyopaque}\n", .{ wl_display, wl_surface, wl_subcompositor });

    // 1. Configure parent surface for subsurface attachment
    if (syms.wpe_display_wayland_set_custom_wl_display) |f| f(wl_display);
    if (syms.wpe_toplevel_wayland_set_parent_surface) |f| f(wl_surface, wl_subcompositor, x, y);

    // 2. Initialize Wayland WPE display
    const display_new_fn = syms.wpe_display_wayland_new orelse return error.MissingSymbol;
    const display = display_new_fn() orelse return error.DisplayCreateFailed;

    if (syms.wpe_display_connect) |connect_fn| {
        var err: ?*anyopaque = null;
        if (connect_fn(display, &err) == 0) {
            std.debug.print("[ZAWRA-WPE] wpe_display_connect failed\n", .{});
            return error.DisplayConnectFailed;
        }
    }

    // 3. Create WebKitWebView
    const view_type_fn = syms.webkit_web_view_get_type orelse return error.MissingSymbol;
    const g_object_new_fn = syms.g_object_new orelse return error.MissingSymbol;

    const view_type = view_type_fn();
    const created_view = g_object_new_fn(view_type, "display", display, @as(?*anyopaque, null)) orelse return error.WebViewCreateFailed;
    web_view = created_view;

    if (syms.g_signal_connect_data) |connect_sig| {
        _ = connect_sig(created_view, "web-process-terminated", @ptrCast(&onWebProcessTerminated), null, null, 0);
        _ = connect_sig(created_view, "load-failed", @ptrCast(&onLoadFailed), null, null, 0);
        _ = connect_sig(created_view, "load-changed", @ptrCast(&onLoadChanged), null, null, 0);
        std.debug.print("[ZAWRA-WPE] Connected process lifecycle & load observability signals\n", .{});
    }

    if (syms.webkit_web_view_get_wpe_view) |f| {
        wpe_view = f(created_view);
    }
    if (syms.wpe_view_get_toplevel) |f| {
        toplevel = f(wpe_view);
    }
    if (syms.wpe_toplevel_wayland_get_wl_subsurface) |f| {
        if (toplevel) |top| subsurface = f(top);
    }
    if (syms.wpe_toplevel_wayland_get_wl_surface) |f| {
        if (toplevel) |top| child_surface = f(top);
    }

    std.debug.print("[ZAWRA-WPE] web_view={?*anyopaque}, wpe_view={?*anyopaque}, toplevel={?*anyopaque}, subsurface={?*anyopaque}, child_surface={?*anyopaque}\n", .{
        web_view, wpe_view, toplevel, subsurface, child_surface,
    });

    if (toplevel) |top| {
        if (syms.wpe_toplevel_resize) |f| f(top, width, height);
    }
    if (wpe_view) |view| {
        if (syms.wpe_view_map) |f| f(view);
        if (syms.wpe_view_focus_in) |f| f(view);
    }

    initialized = true;
    std.debug.print("[ZAWRA-WPE] WebKit Wayland Subsurface initialized successfully\n", .{});
}

pub fn pumpEvents() void {
    var budget: usize = 0;
    while (g_main_context_iteration(null, 0) != 0) {
        budget += 1;
        if (budget >= 256) break;
    }
    checkSupervisorStatus();
}

pub fn pumpEventsSingle() c_int {
    return g_main_context_iteration(null, 0);
}

pub fn detachSubsurfaceBuffer() void {
    if (child_surface) |cs| {
        const wl_surf: *wayland.wl_surface = @ptrCast(@alignCast(cs));
        wayland.wl_surface_attach(wl_surf, null, 0, 0);
        wayland.wl_surface_commit(wl_surf);
    }
}

pub fn loadUrl(url: []const u8) void {
    const view = web_view orelse return;
    const load_fn = syms.webkit_web_view_load_uri orelse return;

    var buf: [2048:0]u8 = undefined;
    if (url.len >= buf.len) {
        std.debug.print("[ZAWRA-WPE] URL too long ({} bytes)\n", .{url.len});
        return;
    }
    @memcpy(buf[0..url.len], url);
    buf[url.len] = 0;

    std.debug.print("[ZAWRA-WPE] Loading URL: {s}\n", .{buf[0..url.len]});
    load_fn(view, &buf);
}

pub fn resize(width: u32, height: u32) void {
    const top = toplevel orelse return;
    if (syms.wpe_toplevel_resize) |f| {
        f(top, @intCast(width), @intCast(height));
    }
}

pub fn setSubsurfacePosition(x: i32, y: i32) void {
    const top = toplevel orelse return;
    if (syms.wpe_toplevel_wayland_set_subsurface_position) |f| {
        f(top, x, y);
    }
}

pub fn setSubsurfaceVisible(visible: bool) void {
    const view = wpe_view orelse return;
    if (visible) {
        if (syms.wpe_view_set_visible) |f| f(view, 1);
        if (syms.wpe_view_map) |f| f(view);
        if (syms.wpe_view_focus_in) |f| f(view);
    } else {
        if (syms.wpe_view_unmap) |f| f(view);
        if (syms.wpe_view_set_visible) |f| f(view, 0);
        if (child_surface) |cs| {
            const wl_surf: *wayland.wl_surface = @ptrCast(@alignCast(cs));
            wayland.wl_surface_attach(wl_surf, null, 0, 0);
            wayland.wl_surface_commit(wl_surf);
        }
    }
}

pub fn sendPointer(event_type: u32, local_x: f64, local_y: f64, button: u32, state: u32) void {
    _ = state;
    const view = wpe_view orelse return;
    const event_fn = syms.wpe_view_event orelse return;
    const unref_fn = syms.wpe_event_unref orelse return;

    const ev: ?*anyopaque = switch (event_type) {
        0 => if (syms.wpe_event_pointer_move_new) |f|
            f(3, view, 0, 0, 0, local_x, local_y, 0.0, 0.0)
        else
            null,
        1 => if (syms.wpe_event_pointer_button_new) |f|
            f(1, view, 0, 0, 0, if (button == 0) 1 else button, local_x, local_y, 1)
        else
            null,
        2 => if (syms.wpe_event_pointer_button_new) |f|
            f(2, view, 0, 0, 0, if (button == 0) 1 else button, local_x, local_y, 1)
        else
            null,
        else => null,
    };

    if (ev) |e| {
        event_fn(view, e);
        unref_fn(e);
    }
}

pub fn sendKeyboard(key: u32, state: u32, modifiers: u32) void {
    const view = wpe_view orelse return;
    const event_fn = syms.wpe_view_event orelse return;
    const unref_fn = syms.wpe_event_unref orelse return;
    const key_new = syms.wpe_event_keyboard_new orelse return;

    const ev_type: u32 = if (state == 1) 7 else 8;
    const ev = key_new(ev_type, view, 2, 0, modifiers, key, key);
    if (ev) |e| {
        event_fn(view, e);
        unref_fn(e);
    }
}
