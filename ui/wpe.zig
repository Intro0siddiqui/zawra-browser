//! Zawra Browser — Direct WPE WebKit Wayland Subsurface Bridge
//!
//! Owns WPE WebKit lifecycle on Thread 1:
//! - Loads libWPEWebKit-2.0.so via std.DynLib
//! - Directly drives the Wayland subsurface lifecycle
//! - Directly forwards mouse, keyboard, resize, and URL load events
//! - Directly pumps GLib event iteration on Thread 1

const std = @import("std");
const builtin = @import("builtin");
const wayland = @cImport({
    @cInclude("wayland-client.h");
});

extern "c" fn g_main_context_iteration(context: ?*anyopaque, may_block: c_int) callconv(.c) c_int;

fn mock_g_main_context_iteration(_: ?*anyopaque, _: c_int) callconv(.c) c_int {
    return 0;
}

const g_main_context_iteration_fn = if (builtin.is_test) mock_g_main_context_iteration else g_main_context_iteration;

extern "c" fn Zawra_History_Record(url: [*:0]const u8, title: [*:0]const u8) callconv(.c) i32;

fn mock_Zawra_History_Record(_: [*:0]const u8, _: [*:0]const u8) callconv(.c) i32 {
    return 0;
}

const history_record_fn = if (builtin.is_test) mock_Zawra_History_Record else Zawra_History_Record;

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
    wpe_view_focus_out: ?*const fn (?*anyopaque) callconv(.c) void = null,
    g_object_unref: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_load_uri: ?*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void = null,
    wpe_view_event: ?*const fn (?*anyopaque, ?*anyopaque) callconv(.c) void = null,
    wpe_event_unref: ?*const fn (?*anyopaque) callconv(.c) void = null,
    wpe_event_pointer_move_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, f64, f64, f64, f64) callconv(.c) ?*anyopaque = null,
    wpe_event_pointer_button_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, u32, f64, f64, u32) callconv(.c) ?*anyopaque = null,
    wpe_event_scroll_new: ?*const fn (?*anyopaque, u32, u32, u32, f64, f64, c_int, c_int, f64, f64) callconv(.c) ?*anyopaque = null,
    wpe_event_keyboard_new: ?*const fn (u32, ?*anyopaque, u32, u32, u32, u32, u32) callconv(.c) ?*anyopaque = null,
    g_signal_connect_data: ?*const fn (
        instance: ?*anyopaque,
        detailed_signal: [*:0]const u8,
        c_handler: ?*const anyopaque,
        data: ?*anyopaque,
        destroy_data: ?*anyopaque,
        connect_flags: c_int,
    ) callconv(.c) c_ulong = null,
    g_signal_handler_disconnect: ?*const fn (instance: ?*anyopaque, handler_id: c_ulong) callconv(.c) void = null,
    webkit_web_view_get_settings: ?*const fn (?*anyopaque) callconv(.c) ?*anyopaque = null,
    webkit_settings_set_user_agent: ?*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void = null,
    webkit_settings_set_enable_developer_extras: ?*const fn (?*anyopaque, c_int) callconv(.c) void = null,
    webkit_web_view_get_uri: ?*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8 = null,
    webkit_web_view_get_title: ?*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8 = null,
    webkit_web_view_reload: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_reload_bypass_cache: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_go_back: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_go_forward: ?*const fn (?*anyopaque) callconv(.c) void = null,
    webkit_web_view_can_go_back: ?*const fn (?*anyopaque) callconv(.c) c_int = null,
    webkit_web_view_can_go_forward: ?*const fn (?*anyopaque) callconv(.c) c_int = null,
};

// Intentionally kept loaded for the process lifetime: GLib/GType registers static
// types and class structs that cannot be safely unloaded via dlclose().
var wpe_lib: ?std.DynLib = null;
var gobject_lib: ?std.DynLib = null;
var syms: WpeSymbols = .{};

pub var global_web_view: ?*anyopaque = null;
var web_view: ?*anyopaque = null;
var wpe_view: ?*anyopaque = null;
var wpe_display: ?*anyopaque = null;
var toplevel: ?*anyopaque = null;
var subsurface: ?*anyopaque = null;
var child_surface: ?*anyopaque = null;
var wl_compositor_handle: ?*anyopaque = null;
var signal_handler_ids: [5]c_ulong = .{ 0, 0, 0, 0, 0 };
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

fn mock_hajr_get_supervisor_status_fd(_: u32) callconv(.c) c_int {
    return -1;
}

const getSupervisorStatusFd = if (builtin.is_test) mock_hajr_get_supervisor_status_fd else hajr_get_supervisor_status_fd;

pub fn checkSupervisorStatus() void {
    const fd = getSupervisorStatusFd(0); // 0 = web process
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

fn getMonotonicNs() i64 {
    var ts: std.os.linux.timespec = undefined;
    _ = std.os.linux.syscall2(.clock_gettime, 1, @intFromPtr(&ts));
    return @as(i64, ts.sec) * 1_000_000_000 + ts.nsec;
}

var nav_t0_ns: i64 = 0;
var nav_started_ms: f64 = 0.0;
var nav_committed_ms: f64 = 0.0;
var nav_finished_ms: f64 = 0.0;
var nav_url_buf: [2048]u8 = undefined;
var nav_url_len: usize = 0;

fn recordHistoryTimed(url: [*:0]const u8, title: [*:0]const u8) void {
    const start_ns = getMonotonicNs();
    _ = history_record_fn(url, title);
    const elapsed_ns = getMonotonicNs() - start_ns;
    const elapsed_ms = @as(f64, @floatFromInt(@max(0, elapsed_ns))) / 1_000_000.0;
    std.debug.print("[PERF-FFI] Zawra_History_Record took {d:.3} ms\n", .{elapsed_ms});
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

    if (load_event == 0 or load_event == 2 or load_event == 3) {
        const now_ns = getMonotonicNs();
        if (load_event == 0 and nav_t0_ns == 0) {
            nav_t0_ns = now_ns;
            nav_started_ms = 0.0;
            nav_committed_ms = 0.0;
            nav_finished_ms = 0.0;
        }
        const elapsed_ms: f64 = if (nav_t0_ns > 0)
            @as(f64, @floatFromInt(@max(0, now_ns - nav_t0_ns))) / 1_000_000.0
        else
            0.0;
        switch (load_event) {
            0 => nav_started_ms = elapsed_ms,
            2 => nav_committed_ms = elapsed_ms,
            3 => nav_finished_ms = elapsed_ms,
            else => {},
        }
        var current_url: []const u8 = if (nav_url_len > 0) nav_url_buf[0..nav_url_len] else "<unknown>";
        if (web_view) |view| {
            if (syms.webkit_web_view_get_uri) |get_uri_fn| {
                if (get_uri_fn(view)) |u| {
                    const u_slice = std.mem.span(u);
                    if (u_slice.len > 0) {
                        current_url = u_slice;
                    }
                }
            }
        }
        std.debug.print("[PERF-NAV] {s} | started={d:.1}ms committed={d:.1}ms finished={d:.1}ms\n", .{
            current_url, nav_started_ms, nav_committed_ms, nav_finished_ms,
        });
        if (load_event == 3) {
            nav_t0_ns = 0;
        }
    }

    if (load_event == 2 or load_event == 3) {
        syncPageMetadata();
    }
    if (load_event == 3) {
        if (web_view) |view| {
            if (syms.webkit_web_view_get_uri) |get_uri_fn| {
                if (get_uri_fn(view)) |u| {
                    const u_slice = std.mem.span(u);
                    if (u_slice.len > 0 and !std.mem.startsWith(u8, u_slice, "zawra://") and !std.mem.startsWith(u8, u_slice, "about:")) {
                        var title_ptr: [*:0]const u8 = "";
                        if (syms.webkit_web_view_get_title) |get_title_fn| {
                            if (get_title_fn(view)) |t| {
                                title_ptr = t;
                            }
                        }
                        recordHistoryTimed(u, title_ptr);
                    }
                }
            }
        }
    }
}

fn onNotifyUri(
    _: ?*anyopaque,
    _: ?*anyopaque,
    _: ?*anyopaque,
) callconv(.c) void {
    syncPageMetadata();
}

fn onNotifyTitle(
    _: ?*anyopaque,
    _: ?*anyopaque,
    _: ?*anyopaque,
) callconv(.c) void {
    syncPageMetadata();
    if (web_view) |view| {
        if (syms.webkit_web_view_get_uri) |get_uri_fn| {
            if (get_uri_fn(view)) |u| {
                const u_slice = std.mem.span(u);
                if (u_slice.len > 0 and !std.mem.startsWith(u8, u_slice, "zawra://") and !std.mem.startsWith(u8, u_slice, "about:")) {
                    if (syms.webkit_web_view_get_title) |get_title_fn| {
                        if (get_title_fn(view)) |t| {
                            recordHistoryTimed(u, t);
                        }
                    }
                }
            }
        }
    }
}

fn applyEmptyInputRegion() void {
    const comp_ptr = wl_compositor_handle orelse return;
    const cs_ptr = child_surface orelse return;
    const wl_comp: *wayland.wl_compositor = @ptrCast(@alignCast(comp_ptr));
    const wl_surf: *wayland.wl_surface = @ptrCast(@alignCast(cs_ptr));
    const empty_region = wayland.wl_compositor_create_region(wl_comp) orelse return;
    wayland.wl_surface_set_input_region(wl_surf, empty_region);
    wayland.wl_surface_commit(wl_surf);
    wayland.wl_region_destroy(empty_region);
}

pub fn init(
    wl_display: ?*anyopaque,
    wl_surface: ?*anyopaque,
    wl_subcompositor: ?*anyopaque,
    wl_compositor: ?*anyopaque,
    x: i32,
    y: i32,
    width: i32,
    height: i32,
) !void {
    if (initialized) return;

    var lib = wpe_lib orelse try openWpeLibrary();
    wpe_lib = lib;

    var unref_fn = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "g_object_unref");
    if (unref_fn == null) {
        if (gobject_lib) |*glib| {
            unref_fn = glib.lookup(*const fn (?*anyopaque) callconv(.c) void, "g_object_unref");
        }
    }
    if (unref_fn == null) {
        const gobj_names = [_][]const u8{ "libgobject-2.0.so.0", "libgobject-2.0.so" };
        for (gobj_names) |name| {
            if (std.DynLib.open(name)) |glib| {
                var mut_glib = glib;
                unref_fn = mut_glib.lookup(*const fn (?*anyopaque) callconv(.c) void, "g_object_unref");
                if (unref_fn != null) {
                    gobject_lib = mut_glib;
                    break;
                }
                mut_glib.close();
            } else |_| {}
        }
    }

    var sig_disconnect_fn = lib.lookup(*const fn (?*anyopaque, c_ulong) callconv(.c) void, "g_signal_handler_disconnect");
    if (sig_disconnect_fn == null) {
        if (gobject_lib) |*glib| {
            sig_disconnect_fn = glib.lookup(*const fn (?*anyopaque, c_ulong) callconv(.c) void, "g_signal_handler_disconnect");
        }
    }

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
        .wpe_view_focus_out = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_view_focus_out"),
        .g_object_unref = unref_fn,
        .webkit_web_view_load_uri = lib.lookup(*const fn (?*anyopaque, [*:0]const u8) callconv(.c) void, "webkit_web_view_load_uri"),
        .wpe_view_event = lib.lookup(*const fn (?*anyopaque, ?*anyopaque) callconv(.c) void, "wpe_view_event"),
        .wpe_event_unref = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "wpe_event_unref"),
        .wpe_event_pointer_move_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, f64, f64, f64, f64) callconv(.c) ?*anyopaque, "wpe_event_pointer_move_new"),
        .wpe_event_pointer_button_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, u32, f64, f64, u32) callconv(.c) ?*anyopaque, "wpe_event_pointer_button_new"),
        .wpe_event_scroll_new = lib.lookup(*const fn (?*anyopaque, u32, u32, u32, f64, f64, c_int, c_int, f64, f64) callconv(.c) ?*anyopaque, "wpe_event_scroll_new"),
        .wpe_event_keyboard_new = lib.lookup(*const fn (u32, ?*anyopaque, u32, u32, u32, u32, u32) callconv(.c) ?*anyopaque, "wpe_event_keyboard_new"),
        .g_signal_connect_data = lib.lookup(*const fn (?*anyopaque, [*:0]const u8, ?*const anyopaque, ?*anyopaque, ?*anyopaque, c_int) callconv(.c) c_ulong, "g_signal_connect_data"),
        .g_signal_handler_disconnect = sig_disconnect_fn,
        .webkit_web_view_get_settings = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?*anyopaque, "webkit_web_view_get_settings"),
        .webkit_settings_set_enable_developer_extras = lib.lookup(*const fn (?*anyopaque, c_int) callconv(.c) void, "webkit_settings_set_enable_developer_extras"),
        .webkit_web_view_get_uri = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8, "webkit_web_view_get_uri"),
        .webkit_web_view_get_title = lib.lookup(*const fn (?*anyopaque) callconv(.c) ?[*:0]const u8, "webkit_web_view_get_title"),
        .webkit_web_view_reload = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "webkit_web_view_reload"),
        .webkit_web_view_reload_bypass_cache = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "webkit_web_view_reload_bypass_cache"),
        .webkit_web_view_go_back = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "webkit_web_view_go_back"),
        .webkit_web_view_go_forward = lib.lookup(*const fn (?*anyopaque) callconv(.c) void, "webkit_web_view_go_forward"),
        .webkit_web_view_can_go_back = lib.lookup(*const fn (?*anyopaque) callconv(.c) c_int, "webkit_web_view_can_go_back"),
        .webkit_web_view_can_go_forward = lib.lookup(*const fn (?*anyopaque) callconv(.c) c_int, "webkit_web_view_can_go_forward"),
    };

    errdefer {
        deinit();
        wl_compositor_handle = null;
        syms = .{};
    }

    wl_compositor_handle = wl_compositor;

    std.debug.print("[ZAWRA-WPE] Attached Wayland handles: disp={?*anyopaque}, surf={?*anyopaque}, subcomp={?*anyopaque}, comp={?*anyopaque}\n", .{ wl_display, wl_surface, wl_subcompositor, wl_compositor });

    // 1. Configure parent surface for subsurface attachment
    // Sole-reader contract: once WPEDisplayWayland connects to wl_display, its GLib GSource
    // becomes the sole reader/dispatcher on wl_display; callers must not call ZG_PollEvents.
    if (syms.wpe_display_wayland_set_custom_wl_display) |f| f(wl_display);
    if (syms.wpe_toplevel_wayland_set_parent_surface) |f| f(wl_surface, wl_subcompositor, x, y);

    // 2. Initialize Wayland WPE display
    const display_new_fn = syms.wpe_display_wayland_new orelse return error.MissingSymbol;
    const display = display_new_fn() orelse return error.DisplayCreateFailed;
    wpe_display = display;

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
    global_web_view = created_view;

    if (syms.webkit_web_view_get_settings) |get_settings_fn| {
        if (get_settings_fn(created_view)) |settings| {
            if (syms.webkit_settings_set_enable_developer_extras) |set_dev_extras_fn| {
                set_dev_extras_fn(settings, 1);
            }
        }
    }

    if (syms.g_signal_connect_data) |connect_sig| {
        signal_handler_ids[0] = connect_sig(created_view, "web-process-terminated", @ptrCast(&onWebProcessTerminated), null, null, 0);
        signal_handler_ids[1] = connect_sig(created_view, "load-failed", @ptrCast(&onLoadFailed), null, null, 0);
        signal_handler_ids[2] = connect_sig(created_view, "load-changed", @ptrCast(&onLoadChanged), null, null, 0);
        signal_handler_ids[3] = connect_sig(created_view, "notify::uri", @ptrCast(&onNotifyUri), null, null, 0);
        signal_handler_ids[4] = connect_sig(created_view, "notify::title", @ptrCast(&onNotifyTitle), null, null, 0);
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
    if (subsurface) |sub| {
        const wl_sub: *wayland.wl_subsurface = @ptrCast(@alignCast(sub));
        wayland.wl_subsurface_set_desync(wl_sub);
    }
    applyEmptyInputRegion();

    initialized = true;
    std.debug.print("[ZAWRA-WPE] WebKit Wayland Subsurface initialized successfully\n", .{});
}

pub fn deinit() void {
    if (!initialized and web_view == null and wpe_view == null and wpe_display == null and subsurface == null and child_surface == null) {
        return;
    }

    if (wpe_view) |view| {
        if (syms.wpe_view_unmap) |f| f(view);
    }

    if (web_view) |wv| {
        if (syms.g_signal_handler_disconnect) |disconnect_sig| {
            for (&signal_handler_ids) |*id| {
                if (id.* != 0) {
                    disconnect_sig(wv, id.*);
                    id.* = 0;
                }
            }
        }
    }

    if (syms.g_object_unref) |unref_fn| {
        if (web_view) |wv| {
            unref_fn(wv);
        }
        if (wpe_display) |disp| {
            unref_fn(disp);
        }
    }

    var i: usize = 0;
    while (i < 16) : (i += 1) {
        if (g_main_context_iteration_fn(null, 0) == 0) break;
    }

    global_web_view = null;
    web_view = null;
    wpe_view = null;
    wpe_display = null;
    toplevel = null;
    subsurface = null;
    child_surface = null;
    wl_compositor_handle = null;
    signal_handler_ids = .{ 0, 0, 0, 0, 0 };
    initialized = false;
    syms = .{};
}

pub fn pumpEvents() void {
    const start_ns = getMonotonicNs();
    const max_budget_ns: i64 = 5_000_000;
    var budget: usize = 0;
    while (g_main_context_iteration_fn(null, 0) != 0) {
        budget += 1;
        if (budget >= 256) break;
        if (getMonotonicNs() - start_ns >= max_budget_ns) break;
    }
    checkSupervisorStatus();
}

pub fn pumpEventsSingle() c_int {
    return g_main_context_iteration_fn(null, 0);
}

pub fn detachSubsurfaceBuffer() void {
    if (child_surface) |cs| {
        const wl_surf: *wayland.wl_surface = @ptrCast(@alignCast(cs));
        wayland.wl_surface_attach(wl_surf, null, 0, 0);
        wayland.wl_surface_commit(wl_surf);
    }
}

pub fn loadUrl(url: []const u8) void {
    if (std.mem.startsWith(u8, url, "zawra://") or std.mem.startsWith(u8, url, "about:")) {
        return;
    }
    const view = web_view orelse return;
    const load_fn = syms.webkit_web_view_load_uri orelse return;

    var buf: [2048:0]u8 = undefined;
    if (url.len >= buf.len) {
        std.debug.print("[ZAWRA-WPE] URL too long ({} bytes)\n", .{url.len});
        return;
    }
    @memcpy(buf[0..url.len], url);
    buf[url.len] = 0;

    nav_t0_ns = getMonotonicNs();
    nav_started_ms = 0.0;
    nav_committed_ms = 0.0;
    nav_finished_ms = 0.0;
    @memcpy(nav_url_buf[0..url.len], url);
    nav_url_len = url.len;

    std.debug.print("[ZAWRA-WPE] Loading URL: {s}\n", .{buf[0..url.len]});
    load_fn(view, &buf);
}

pub var test_reload_count: u32 = 0;
pub var test_reload_bypass_count: u32 = 0;
pub var test_back_count: u32 = 0;
pub var test_forward_count: u32 = 0;

pub fn reload() void {
    test_reload_count += 1;
    const view = global_web_view orelse web_view orelse return;
    if (syms.webkit_web_view_reload) |f| {
        std.debug.print("[ZAWRA-WPE] Reloading page\n", .{});
        f(view);
    }
}

pub fn reloadBypassCache() void {
    test_reload_bypass_count += 1;
    const view = global_web_view orelse web_view orelse return;
    if (syms.webkit_web_view_reload_bypass_cache) |f| {
        std.debug.print("[ZAWRA-WPE] Reloading page (bypass cache)\n", .{});
        f(view);
    }
}

pub fn goBack() void {
    test_back_count += 1;
    const view = global_web_view orelse web_view orelse return;
    if (syms.webkit_web_view_go_back) |f| {
        std.debug.print("[ZAWRA-WPE] Going back\n", .{});
        f(view);
    }
}

pub fn goForward() void {
    test_forward_count += 1;
    const view = global_web_view orelse web_view orelse return;
    if (syms.webkit_web_view_go_forward) |f| {
        std.debug.print("[ZAWRA-WPE] Going forward\n", .{});
        f(view);
    }
}

pub fn canGoBack() bool {
    const view = global_web_view orelse web_view orelse return false;
    if (syms.webkit_web_view_can_go_back) |f| {
        return f(view) != 0;
    }
    return false;
}

pub fn canGoForward() bool {
    const view = global_web_view orelse web_view orelse return false;
    if (syms.webkit_web_view_can_go_forward) |f| {
        return f(view) != 0;
    }
    return false;
}

pub fn resize(width: u32, height: u32) void {
    const top = toplevel orelse return;
    if (syms.wpe_toplevel_resize) |f| {
        f(top, @intCast(width), @intCast(height));
    }
    applyEmptyInputRegion();
}

pub fn setFocus(focused: bool) void {
    const view = wpe_view orelse return;
    if (focused) {
        if (syms.wpe_view_focus_in) |f| f(view);
    } else {
        if (syms.wpe_view_focus_out) |f| f(view);
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
            f(2, view, 0, 0, 0, if (button == 0) 1 else button, local_x, local_y, 0)
        else
            null,
        3 => if (syms.wpe_event_scroll_new) |f| blk: {
            // `button` carries wl_pointer axis (0 = vertical, 1 = horizontal);
            // `state` carries wl_fixed_t (24.8 signed fixed point). WPE negates Wayland axis deltas.
            const fixed_val: i32 = @bitCast(state);
            const delta: f64 = -@as(f64, @floatFromInt(fixed_val)) / 256.0;
            const delta_x: f64 = if (button == 1) delta else 0.0;
            const delta_y: f64 = if (button == 0) delta else 0.0;
            break :blk f(view, 0, 0, 0, delta_x, delta_y, 1, 0, local_x, local_y);
        } else null,
        else => null,
    };

    if (ev) |e| {
        event_fn(view, e);
        unref_fn(e);
    }
}

pub fn sendScroll(local_x: f64, local_y: f64, delta_x: f64, delta_y: f64, source: u32, time_ms: u32, is_stop: bool) void {
    const view = wpe_view orelse return;
    const event_fn = syms.wpe_view_event orelse return;
    const unref_fn = syms.wpe_event_unref orelse return;
    const scroll_new_fn = syms.wpe_event_scroll_new orelse return;

    // `precise_deltas = 1` for Wayland wl_fixed_t pixel deltas; `is_stop = 1` triggers
    // WebKit kinetic/momentum coasting when `source == WPE_INPUT_SOURCE_TOUCHPAD` (4).
    const ev = scroll_new_fn(
        view,
        source,
        time_ms,
        0,
        delta_x,
        delta_y,
        1,
        if (is_stop) 1 else 0,
        local_x,
        local_y,
    ) orelse return;
    event_fn(view, ev);
    unref_fn(ev);
}

pub fn evdevToKeysym(key: u32, shift: bool) u32 {
    // 1. Special & Navigation Keys
    switch (key) {
        // Return / Enter
        28 => return 0xff0d, // KEY_ENTER -> XK_Return
        96 => return 0xff8d, // KEY_KPENTER -> XK_KP_Enter
        // Backspace
        14 => return 0xff08, // KEY_BACKSPACE -> XK_BackSpace
        // Tab
        15 => return if (shift) 0xfe20 else 0xff09, // KEY_TAB -> XK_ISO_Left_Tab / XK_Tab
        // Linefeed
        101 => return 0xff0a, // KEY_LINEFEED -> XK_Linefeed
        // Escape
        1 => return 0xff1b, // KEY_ESC -> XK_Escape
        // Space
        57 => return 0x0020, // KEY_SPACE -> XK_space
        // Delete & Insert
        111 => return 0xffff, // KEY_DELETE -> XK_Delete
        110 => return 0xff63, // KEY_INSERT -> XK_Insert
        // Directional arrows
        105 => return 0xff51, // KEY_LEFT -> XK_Left
        103 => return 0xff52, // KEY_UP -> XK_Up
        106 => return 0xff53, // KEY_RIGHT -> XK_Right
        108 => return 0xff54, // KEY_DOWN -> XK_Down
        // Navigation block
        102 => return 0xff50, // KEY_HOME -> XK_Home
        107 => return 0xff57, // KEY_END -> XK_End
        104 => return 0xff55, // KEY_PAGEUP -> XK_Page_Up
        109 => return 0xff56, // KEY_PAGEDOWN -> XK_Page_Down
        // Modifiers
        42 => return 0xffe1, // KEY_LEFTSHIFT -> XK_Shift_L
        54 => return 0xffe2, // KEY_RIGHTSHIFT -> XK_Shift_R
        29 => return 0xffe3, // KEY_LEFTCTRL -> XK_Control_L
        97 => return 0xffe4, // KEY_RIGHTCTRL -> XK_Control_R
        56 => return 0xffe9, // KEY_LEFTALT -> XK_Alt_L
        100 => return 0xffea, // KEY_RIGHTALT -> XK_Alt_R
        125 => return 0xffeb, // KEY_LEFTMETA -> XK_Super_L
        126 => return 0xffec, // KEY_RIGHTMETA -> XK_Super_R
        58 => return 0xffe5, // KEY_CAPSLOCK -> XK_Caps_Lock
        // Keypad numbers & operations
        82 => return 0xffb0, // KEY_KP0 -> XK_KP_0
        79 => return 0xffb1, // KEY_KP1 -> XK_KP_1
        80 => return 0xffb2, // KEY_KP2 -> XK_KP_2
        81 => return 0xffb3, // KEY_KP3 -> XK_KP_3
        75 => return 0xffb4, // KEY_KP4 -> XK_KP_4
        76 => return 0xffb5, // KEY_KP5 -> XK_KP_5
        77 => return 0xffb6, // KEY_KP6 -> XK_KP_6
        71 => return 0xffb7, // KEY_KP7 -> XK_KP_7
        72 => return 0xffb8, // KEY_KP8 -> XK_KP_8
        73 => return 0xffb9, // KEY_KP9 -> XK_KP_9
        83 => return 0xffae, // KEY_KPDOT -> XK_KP_Decimal
        98 => return 0xffaf, // KEY_KPSLASH -> XK_KP_Divide
        55 => return 0xffaa, // KEY_KPASTERISK -> XK_KP_Multiply
        74 => return 0xffad, // KEY_KPMINUS -> XK_KP_Subtract
        78 => return 0xffab, // KEY_KPPLUS -> XK_KP_Add
        117 => return 0xffbd, // KEY_KPEQUAL -> XK_KP_Equal
        // Function keys
        59 => return 0xffbe, // KEY_F1
        60 => return 0xffbf, // KEY_F2
        61 => return 0xffc0, // KEY_F3
        62 => return 0xffc1, // KEY_F4
        63 => return 0xffc2, // KEY_F5
        64 => return 0xffc3, // KEY_F6
        65 => return 0xffc4, // KEY_F7
        66 => return 0xffc5, // KEY_F8
        67 => return 0xffc6, // KEY_F9
        68 => return 0xffc7, // KEY_F10
        87 => return 0xffc8, // KEY_F11
        88 => return 0xffc9, // KEY_F12
        else => {},
    }

    // 2. Letters A-Z / a-z
    const letter: u32 = switch (key) {
        16 => 'q',
        17 => 'w',
        18 => 'e',
        19 => 'r',
        20 => 't',
        21 => 'y',
        22 => 'u',
        23 => 'i',
        24 => 'o',
        25 => 'p',
        30 => 'a',
        31 => 's',
        32 => 'd',
        33 => 'f',
        34 => 'g',
        35 => 'h',
        36 => 'j',
        37 => 'k',
        38 => 'l',
        44 => 'z',
        45 => 'x',
        46 => 'c',
        47 => 'v',
        48 => 'b',
        49 => 'n',
        50 => 'm',
        else => 0,
    };
    if (letter != 0) {
        if (shift) {
            return letter - 32; // 'A'..'Z'
        } else {
            return letter;      // 'a'..'z'
        }
    }

    // 3. Number row (1..0) and punctuation
    if (!shift) {
        switch (key) {
            2 => return '1',
            3 => return '2',
            4 => return '3',
            5 => return '4',
            6 => return '5',
            7 => return '6',
            8 => return '7',
            9 => return '8',
            10 => return '9',
            11 => return '0',
            12 => return '-',
            13 => return '=',
            26 => return '[',
            27 => return ']',
            43 => return '\\',
            39 => return ';',
            40 => return '\'',
            41 => return '`',
            51 => return ',',
            52 => return '.',
            53 => return '/',
            86 => return '<', // KEY_102ND (ISO)
            else => {},
        }
    } else {
        switch (key) {
            2 => return '!',
            3 => return '@',
            4 => return '#',
            5 => return '$',
            6 => return '%',
            7 => return '^',
            8 => return '&',
            9 => return '*',
            10 => return '(',
            11 => return ')',
            12 => return '_',
            13 => return '+',
            26 => return '{',
            27 => return '}',
            43 => return '|',
            39 => return ':',
            40 => return '"',
            41 => return '~',
            51 => return '<',
            52 => return '>',
            53 => return '?',
            86 => return '>', // KEY_102ND (ISO shifted)
            else => {},
        }
    }

    // 4. Fallback: if already an ASCII or keysym value
    if (key >= 32 and key <= 126) {
        return key;
    }
    if (key >= 0xff00) {
        return key;
    }

    return 0;
}

pub fn sendKeyboard(key: u32, state: u32, modifiers: u32) void {
    const view = wpe_view orelse return;
    const event_fn = syms.wpe_view_event orelse return;
    const unref_fn = syms.wpe_event_unref orelse return;
    const key_new = syms.wpe_event_keyboard_new orelse return;

    const ev_type: u32 = if (state == 1) 7 else 8;
    const shift = (modifiers & (1 << 0)) != 0;
    const alt = (modifiers & (1 << 1)) != 0;
    const ctrl = (modifiers & (1 << 2)) != 0;

    var wpe_modifiers: u32 = 0;
    if (ctrl) wpe_modifiers |= (1 << 0); // WPE_MODIFIER_KEYBOARD_CONTROL
    if (shift) wpe_modifiers |= (1 << 1); // WPE_MODIFIER_KEYBOARD_SHIFT
    if (alt) wpe_modifiers |= (1 << 2);   // WPE_MODIFIER_KEYBOARD_ALT

    const hardware_keycode: u32 = key + 8;
    const keysym: u32 = evdevToKeysym(key, shift);

    const ev = key_new(ev_type, view, 2, 0, wpe_modifiers, hardware_keycode, keysym);
    if (ev) |e| {
        event_fn(view, e);
        unref_fn(e);
    }
}

test "evdevToKeysym printable and navigation mapping" {
    // Letters
    try std.testing.expectEqual(@as(u32, 'a'), evdevToKeysym(30, false));
    try std.testing.expectEqual(@as(u32, 'A'), evdevToKeysym(30, true));
    try std.testing.expectEqual(@as(u32, 'z'), evdevToKeysym(44, false));
    try std.testing.expectEqual(@as(u32, 'Z'), evdevToKeysym(44, true));

    // Digits and shifted symbols
    try std.testing.expectEqual(@as(u32, '1'), evdevToKeysym(2, false));
    try std.testing.expectEqual(@as(u32, '!'), evdevToKeysym(2, true));
    try std.testing.expectEqual(@as(u32, '0'), evdevToKeysym(11, false));
    try std.testing.expectEqual(@as(u32, ')'), evdevToKeysym(11, true));

    // Punctuation
    try std.testing.expectEqual(@as(u32, '-'), evdevToKeysym(12, false));
    try std.testing.expectEqual(@as(u32, '_'), evdevToKeysym(12, true));
    try std.testing.expectEqual(@as(u32, '['), evdevToKeysym(26, false));
    try std.testing.expectEqual(@as(u32, '{'), evdevToKeysym(26, true));
    try std.testing.expectEqual(@as(u32, ' '), evdevToKeysym(57, false));

    // Return & Backspace & Tab
    try std.testing.expectEqual(@as(u32, 0xff0d), evdevToKeysym(28, false)); // XK_Return
    try std.testing.expectEqual(@as(u32, 0xff08), evdevToKeysym(14, false)); // XK_BackSpace
    try std.testing.expectEqual(@as(u32, 0xff09), evdevToKeysym(15, false)); // XK_Tab
    try std.testing.expectEqual(@as(u32, 0xfe20), evdevToKeysym(15, true));  // XK_ISO_Left_Tab

    // Navigation
    try std.testing.expectEqual(@as(u32, 0xff51), evdevToKeysym(105, false)); // XK_Left
    try std.testing.expectEqual(@as(u32, 0xff52), evdevToKeysym(103, false)); // XK_Up
    try std.testing.expectEqual(@as(u32, 0xff53), evdevToKeysym(106, false)); // XK_Right
    try std.testing.expectEqual(@as(u32, 0xff54), evdevToKeysym(108, false)); // XK_Down
    try std.testing.expectEqual(@as(u32, 0xff50), evdevToKeysym(102, false)); // XK_Home
    try std.testing.expectEqual(@as(u32, 0xff57), evdevToKeysym(107, false)); // XK_End
    try std.testing.expectEqual(@as(u32, 0xff55), evdevToKeysym(104, false)); // XK_Page_Up
    try std.testing.expectEqual(@as(u32, 0xff56), evdevToKeysym(109, false)); // XK_Page_Down
    try std.testing.expectEqual(@as(u32, 0xffff), evdevToKeysym(111, false)); // XK_Delete
    try std.testing.expectEqual(@as(u32, 0xff63), evdevToKeysym(110, false)); // XK_Insert
    try std.testing.expectEqual(@as(u32, 0xff1b), evdevToKeysym(1, false));   // XK_Escape

    // Keypad
    try std.testing.expectEqual(@as(u32, 0xff8d), evdevToKeysym(96, false)); // XK_KP_Enter
    try std.testing.expectEqual(@as(u32, 0xffb0), evdevToKeysym(82, false)); // XK_KP_0
    try std.testing.expectEqual(@as(u32, 0xffb9), evdevToKeysym(73, false)); // XK_KP_9
    try std.testing.expectEqual(@as(u32, 0xffab), evdevToKeysym(78, false)); // XK_KP_Add

    // Modifiers & Function Keys
    try std.testing.expectEqual(@as(u32, 0xffe1), evdevToKeysym(42, false)); // XK_Shift_L
    try std.testing.expectEqual(@as(u32, 0xffe3), evdevToKeysym(29, false)); // XK_Control_L
    try std.testing.expectEqual(@as(u32, 0xffe9), evdevToKeysym(56, false)); // XK_Alt_L
    try std.testing.expectEqual(@as(u32, 0xffbe), evdevToKeysym(59, false)); // XK_F1
    try std.testing.expectEqual(@as(u32, 0xffc9), evdevToKeysym(88, false)); // XK_F12
}
