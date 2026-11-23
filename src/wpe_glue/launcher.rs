//! Zawra Browser — WPE Launcher & Process Bootstrap
//!
//! Orchestrates the full startup sequence:
//!
//!  1. Detect and `dlopen` WPE WebKit library at runtime with dynamic path discovery.
//!  2. Call `Zawra_Init_Subsystems(profile_path)` — boots z-net + BrowserDB.
//!  3. Call `Zawra_Register_Protocols()` — overrides WPE's networking handlers.
//!  4. Run headless WPEPlatform with GMainLoop on a dedicated "webkit-glib" thread.
//!  5. Connect "buffer-rendered" signal to feed live DMA-BUF frames into Vulkan Pass 1.
//!  6. Marshal main-thread UI actions (Zawra_LoadURL, resize, input) via g_idle_add.

use std::ffi::{c_char, c_int, c_void, CString};
use std::path::PathBuf;
use std::ptr::null_mut;
use std::sync::atomic::{AtomicPtr, Ordering};
use std::sync::Mutex;

// ── nsresult ─────────────────────────────────────────────────────────────────
const NS_OK:            i32 = 0;
const NS_ERROR_FAILURE: i32 = -2147467259i32;

// ── C-ABI declarations from our glue layer ────────────────────────────────────
unsafe extern "C" {
    fn Z_Init_Subsystems(profile_path: *const c_char) -> i32;
    fn Z_Register_Protocols() -> i32;
    fn Z_Shutdown_Subsystems();
    fn hajr_spawn_compartment(
        path: *const c_char,
        argv: *const *const c_char,
        out_socket: *mut c_int,
    ) -> c_int;
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Dynamic linker wrapper
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[cfg(target_os = "windows")]
unsafe fn resolve_global_sym(name: &[u8]) -> *mut c_void {
    extern "system" {
        fn GetModuleHandleA(lpModuleName: *const c_char) -> *mut c_void;
        fn GetProcAddress(hModule: *mut c_void, lpProcName: *const c_char) -> *mut c_void;
    }
    let h = GetModuleHandleA(std::ptr::null());
    if h.is_null() {
        return std::ptr::null_mut();
    }
    GetProcAddress(h, name.as_ptr() as *const c_char)
}

#[cfg(not(target_os = "windows"))]
unsafe fn resolve_global_sym(name: &[u8]) -> *mut c_void {
    unsafe { libc::dlsym(libc::RTLD_DEFAULT, name.as_ptr() as *const _) }
}

pub struct DynLib {
    handle: *mut c_void,
}

unsafe impl Send for DynLib {}
unsafe impl Sync for DynLib {}

impl DynLib {
    fn open(path: &str) -> Option<Self> {
        #[cfg(target_os = "windows")]
        {
            extern "system" {
                fn LoadLibraryA(lpLibFileName: *const c_char) -> *mut c_void;
            }
            let path_c = CString::new(path).ok()?;
            let handle = unsafe { LoadLibraryA(path_c.as_ptr()) };
            if handle.is_null() {
                eprintln!("[zawra-launcher] LoadLibraryA({}) failed", path);
                None
            } else {
                Some(DynLib { handle })
            }
        }
        #[cfg(not(target_os = "windows"))]
        {
            let path_c = CString::new(path).ok()?;
            let handle = unsafe {
                libc::dlopen(path_c.as_ptr(), libc::RTLD_LAZY | libc::RTLD_GLOBAL)
            };
            if handle.is_null() {
                let err = unsafe { std::ffi::CStr::from_ptr(libc::dlerror()) };
                eprintln!("[zawra-launcher] dlopen({}) failed: {:?}", path, err);
                None
            } else {
                Some(DynLib { handle })
            }
        }
    }

    unsafe fn sym<T: Copy>(&self, name: &str) -> Option<T> {
        let name_c = CString::new(name).ok()?;
        #[cfg(target_os = "windows")]
        {
            extern "system" {
                fn GetProcAddress(hModule: *mut c_void, lpProcName: *const c_char) -> *mut c_void;
            }
            let ptr = unsafe { GetProcAddress(self.handle, name_c.as_ptr()) };
            if ptr.is_null() { None } else { Some(unsafe { *(ptr as *const T) }) }
        }
        #[cfg(not(target_os = "windows"))]
        {
            let ptr = unsafe { libc::dlsym(self.handle, name_c.as_ptr()) };
            if ptr.is_null() { None } else { Some(unsafe { *(ptr as *const T) }) }
        }
    }
}

impl Drop for DynLib {
    fn drop(&mut self) {
        if !self.handle.is_null() {
            #[cfg(target_os = "windows")]
            {
                extern "system" {
                    fn FreeLibrary(hLibModule: *mut c_void) -> i32;
                }
                unsafe { FreeLibrary(self.handle) };
            }
            #[cfg(not(target_os = "windows"))]
            unsafe { libc::dlclose(self.handle) };
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Path Resolution & Environment Configuration
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn resolve_profile_dir() -> PathBuf {
    if let Ok(p) = std::env::var("ZAWRA_PROFILE") {
        let path = PathBuf::from(p);
        std::fs::create_dir_all(&path).ok();
        return path;
    }

    if let Some(mut home) = dirs::home_dir() {
        home.push(".zawra");
        home.push("profile");
        std::fs::create_dir_all(&home).ok();
        return home;
    }

    let fallback = PathBuf::from("./zawra_profile");
    std::fs::create_dir_all(&fallback).ok();
    fallback
}

/// Search relative to binary and known project locations for WPE libraries and binaries.
fn resolve_wpe_environment() -> Option<PathBuf> {
    const WPE_LIB_NAME: &str = "libWPEWebKit-2.0.so";

    // 1. Check environment overrides first
    if let Ok(env_path) = std::env::var("WPE_PATH") {
        let p = PathBuf::from(&env_path);
        if p.is_file() {
            return Some(p);
        } else if p.is_dir() {
            let candidate = p.join(WPE_LIB_NAME);
            if candidate.is_file() {
                return Some(candidate);
            }
        }
    }

    // 2. Discover relative to current executable
    if let Ok(exe_path) = std::env::current_exe() {
        let mut curr = exe_path.parent();
        while let Some(dir) = curr {
            let candidate_lib = dir.join("webkit/build/lib").join(WPE_LIB_NAME);
            if candidate_lib.is_file() {
                let candidate_bin = dir.join("webkit/build/bin");
                if candidate_bin.join("WPEWebProcess").is_file() {
                    unsafe {
                        std::env::set_var("WEBKIT_EXEC_PATH", candidate_bin.to_string_lossy().as_ref());
                        std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir.join("webkit/build/lib").to_string_lossy().as_ref());
                    }
                }
                return Some(candidate_lib);
            }

            let candidate_lib2 = dir.join("lib").join(WPE_LIB_NAME);
            if candidate_lib2.is_file() {
                let candidate_bin2 = dir.join("bin");
                if candidate_bin2.join("WPEWebProcess").is_file() {
                    unsafe {
                        std::env::set_var("WEBKIT_EXEC_PATH", candidate_bin2.to_string_lossy().as_ref());
                        std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir.join("lib").to_string_lossy().as_ref());
                    }
                }
                return Some(candidate_lib2);
            }

            curr = dir.parent();
        }
    }

    // 3. Fallback known workspace locations
    let fallback_paths = [
        "/home/intro/spectre-enviroment/browser/zawra-browser/webkit/build/lib/libWPEWebKit-2.0.so",
        "/home/intro/spectre-enviroment/browser/zawra-browser-znet-e2e/webkit/build/lib/libWPEWebKit-2.0.so",
        "/usr/lib/x86_64-linux-gnu/libWPEWebKit-2.0.so",
        "/usr/lib64/libWPEWebKit-2.0.so",
        "/usr/lib/libWPEWebKit-2.0.so",
    ];

    for path_str in &fallback_paths {
        let p = PathBuf::from(path_str);
        if p.is_file() {
            if let Some(parent) = p.parent() {
                let bin_dir = parent.parent().map(|p| p.join("bin"));
                if let Some(b) = bin_dir {
                    if b.join("WPEWebProcess").is_file() {
                        unsafe {
                            if std::env::var_os("WEBKIT_EXEC_PATH").is_none() {
                                std::env::set_var("WEBKIT_EXEC_PATH", b.to_string_lossy().as_ref());
                            }
                            if std::env::var_os("WEBKIT_INJECTED_BUNDLE_PATH").is_none() {
                                std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", parent.to_string_lossy().as_ref());
                            }
                        }
                    }
                }
            }
            return Some(p);
        }
    }

    None
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Zero-Copy DMA-BUF Frame Mailbox
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Clone, Copy, Debug)]
pub struct PendingDMABuf {
    pub fd: i32,
    pub width: u32,
    pub height: u32,
    pub stride: u32,
    pub fourcc: u32,
    pub modifier: u64,
}

static PENDING_FRAME: Mutex<Option<PendingDMABuf>> = Mutex::new(None);

/// Called by the main thread (shell.zig) each frame to retrieve any newly arrived DMA-BUF frame.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_TakePendingDMABuf(
    out_fd: *mut c_int,
    out_w: *mut u32,
    out_h: *mut u32,
    out_stride: *mut u32,
    out_fourcc: *mut u32,
    out_modifier: *mut u64,
) -> bool {
    if let Ok(mut lock) = PENDING_FRAME.lock() {
        if let Some(frame) = lock.take() {
            unsafe {
                if !out_fd.is_null() { *out_fd = frame.fd; }
                if !out_w.is_null() { *out_w = frame.width; }
                if !out_h.is_null() { *out_h = frame.height; }
                if !out_stride.is_null() { *out_stride = frame.stride; }
                if !out_fourcc.is_null() { *out_fourcc = frame.fourcc; }
                if !out_modifier.is_null() { *out_modifier = frame.modifier; }
            }
            return true;
        }
    }
    false
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// WebKit & GLib Engine State
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

static WPE_LIB: Mutex<Option<DynLib>> = Mutex::new(None);
static GLIB_MAIN_LOOP: AtomicPtr<c_void> = AtomicPtr::new(null_mut());
static ACTIVE_WEB_VIEW: AtomicPtr<c_void> = AtomicPtr::new(null_mut());
static ACTIVE_WPE_VIEW: AtomicPtr<c_void> = AtomicPtr::new(null_mut());
static ACTIVE_TOPLEVEL: AtomicPtr<c_void> = AtomicPtr::new(null_mut());

/// Set the currently active WPE view handle.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_SetActiveWpeView(view: *mut c_void) {
    ACTIVE_WPE_VIEW.store(view, Ordering::SeqCst);
}

/// Get the currently active WPE view handle.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_GetActiveWpeView() -> *mut c_void {
    ACTIVE_WPE_VIEW.load(Ordering::SeqCst)
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// WPE Frame Reception Callback (GLib thread)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

unsafe extern "C" fn on_buffer_rendered(
    _view: *mut c_void,
    buffer: *mut c_void,
    _user_data: *mut c_void,
) {
    if buffer.is_null() {
        return;
    }

    if let Ok(guard) = WPE_LIB.lock() {
        if let Some(ref lib) = *guard {
            unsafe {
                let get_type: unsafe extern "C" fn() -> usize = match lib.sym("wpe_buffer_dma_buf_get_type") {
                    Some(f) => f,
                    None => return,
                };
                let is_a: unsafe extern "C" fn(*mut c_void, usize) -> i32 = match lib.sym("g_type_check_instance_is_a") {
                    Some(f) => f,
                    None => return,
                };

                let dmabuf_type = get_type();
                if is_a(buffer, dmabuf_type) == 0 {
                    return;
                }

                let get_fd: unsafe extern "C" fn(*mut c_void, u32) -> i32 = match lib.sym("wpe_buffer_dma_buf_get_fd") {
                    Some(f) => f,
                    None => return,
                };
                let get_stride: unsafe extern "C" fn(*mut c_void, u32) -> u32 = match lib.sym("wpe_buffer_dma_buf_get_stride") {
                    Some(f) => f,
                    None => return,
                };
                let get_format: unsafe extern "C" fn(*mut c_void) -> u32 = match lib.sym("wpe_buffer_dma_buf_get_format") {
                    Some(f) => f,
                    None => return,
                };
                let get_modifier: unsafe extern "C" fn(*mut c_void) -> u64 = match lib.sym("wpe_buffer_dma_buf_get_modifier") {
                    Some(f) => f,
                    None => return,
                };
                let get_width: unsafe extern "C" fn(*mut c_void) -> i32 = match lib.sym("wpe_buffer_get_width") {
                    Some(f) => f,
                    None => return,
                };
                let get_height: unsafe extern "C" fn(*mut c_void) -> i32 = match lib.sym("wpe_buffer_get_height") {
                    Some(f) => f,
                    None => return,
                };

                let raw_fd = get_fd(buffer, 0);
                let dup_fd = libc::dup(raw_fd);
                let stride = get_stride(buffer, 0);
                let fourcc = get_format(buffer);
                let modifier = get_modifier(buffer);
                let width = get_width(buffer) as u32;
                let height = get_height(buffer) as u32;

                if dup_fd >= 0 && width > 0 && height > 0 {
                    if let Ok(mut lock) = PENDING_FRAME.lock() {
                        if let Some(old) = lock.take() {
                            libc::close(old.fd);
                        }
                        *lock = Some(PendingDMABuf {
                            fd: dup_fd,
                            width,
                            height,
                            stride,
                            fourcc,
                            modifier,
                        });
                    }
                }
            }
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Main Thread -> GLib Thread Marshallers (g_idle_add)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

unsafe extern "C" fn idle_load_url(data: *mut c_void) -> i32 {
    unsafe {
        let c_url = Box::from_raw(data as *mut CString);
        let web_view = ACTIVE_WEB_VIEW.load(Ordering::SeqCst);
        if !web_view.is_null() {
            if let Ok(guard) = WPE_LIB.lock() {
                if let Some(ref lib) = *guard {
                    if let Some(load_uri) = lib.sym::<unsafe extern "C" fn(*mut c_void, *const c_char)>("webkit_web_view_load_uri") {
                        eprintln!("[ZAWRA-GLIB] Loading URI: {:?}", c_url);
                        load_uri(web_view, c_url.as_ptr());
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Navigation hook: loads the requested URL in the active WebKit view safely via GLib idle.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_LoadURL(url_ptr: *const u8, url_len: usize) {
    if url_ptr.is_null() || url_len == 0 {
        return;
    }
    let slice = unsafe { std::slice::from_raw_parts(url_ptr, url_len) };
    let url = String::from_utf8_lossy(slice);

    if let Ok(c_url) = CString::new(url.as_ref()) {
        if let Ok(guard) = WPE_LIB.lock() {
            if let Some(ref lib) = *guard {
                unsafe {
                    if let Some(idle_add) = lib.sym::<unsafe extern "C" fn(unsafe extern "C" fn(*mut c_void) -> i32, *mut c_void) -> u32>("g_idle_add") {
                        let boxed = Box::into_raw(Box::new(c_url));
                        idle_add(idle_load_url, boxed as *mut c_void);
                        return;
                    }
                }
            }
        }
    }
}

struct ResizeMsg {
    width: i32,
    height: i32,
}

unsafe extern "C" fn idle_resize(data: *mut c_void) -> i32 {
    unsafe {
        let msg = Box::from_raw(data as *mut ResizeMsg);
        let toplevel = ACTIVE_TOPLEVEL.load(Ordering::SeqCst);
        let wpe_view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);

        if let Ok(guard) = WPE_LIB.lock() {
            if let Some(ref lib) = *guard {
                if !toplevel.is_null() {
                    if let Some(toplevel_resize) = lib.sym::<unsafe extern "C" fn(*mut c_void, i32, i32)>("wpe_toplevel_resize") {
                        toplevel_resize(toplevel, msg.width, msg.height);
                    }
                }
                if !wpe_view.is_null() {
                    if let Some(view_resize) = lib.sym::<unsafe extern "C" fn(*mut c_void, i32, i32)>("wpe_view_resized") {
                        view_resize(wpe_view, msg.width, msg.height);
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Viewport resize hook: adjusts the WPE headless toplevel and view dimensions.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_ResizeViewport(width: u32, height: u32) {
    if let Ok(guard) = WPE_LIB.lock() {
        if let Some(ref lib) = *guard {
            unsafe {
                if let Some(idle_add) = lib.sym::<unsafe extern "C" fn(unsafe extern "C" fn(*mut c_void) -> i32, *mut c_void) -> u32>("g_idle_add") {
                    let boxed = Box::into_raw(Box::new(ResizeMsg {
                        width: width as i32,
                        height: height as i32,
                    }));
                    idle_add(idle_resize, boxed as *mut c_void);
                }
            }
        }
    }
}

/// Input event forwarding: pointer events (motion, button, scroll)
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_pointer(
    event_type: u32,
    local_x: f64,
    local_y: f64,
    button: u32,
    state: u32,
) {
    let view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);
    if view.is_null() { return; }
    unsafe {
        type WpePointerEventFn = unsafe extern "C" fn(*mut c_void, u32, f64, f64, u32, u32);
        let sym = resolve_global_sym(b"wpe_view_event_pointer\0");
        if !sym.is_null() {
            let func: WpePointerEventFn = std::mem::transmute(sym);
            func(view, event_type, local_x, local_y, button, state);
        }
    }
}

/// Input event forwarding: keyboard events
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_keyboard(
    key: u32,
    state: u32,
    modifiers: u32,
) {
    let view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);
    if view.is_null() { return; }
    unsafe {
        type WpeKeyboardEventFn = unsafe extern "C" fn(*mut c_void, u32, u32, u32);
        let sym = resolve_global_sym(b"wpe_view_event_keyboard\0");
        if !sym.is_null() {
            let func: WpeKeyboardEventFn = std::mem::transmute(sym);
            func(view, key, state, modifiers);
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Subsystem & Process Bootstrap
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Initialise Zawra subsystems (z-net + BrowserDB).
pub fn bootstrap_zawra(profile_path: &str) -> bool {
    let profile_c = match CString::new(profile_path) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("[zawra-launcher] Invalid profile path: {}", e);
            return false;
        }
    };

    let ret = unsafe { Z_Init_Subsystems(profile_c.as_ptr()) };
    if ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Init_Subsystems failed: {:#010x}", ret as u32);
        return false;
    }

    let proto_ret = unsafe { Z_Register_Protocols() };
    if proto_ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Register_Protocols non-zero: {:#010x}", proto_ret as u32);
    }

    true
}

/// Launch WPE on the dedicated "webkit-glib" thread running a GMainLoop.
pub fn launch_wpe(_profile_path: &str) -> i32 {
    let wpe_path = match resolve_wpe_environment() {
        Some(p) => p,
        None => {
            eprintln!("[zawra-launcher] WPE library not found — running in headless UI mode");
            return 0;
        }
    };

    let path_str = match wpe_path.to_str() {
        Some(s) => s,
        None => return NS_ERROR_FAILURE,
    };

    let lib = match DynLib::open(path_str) {
        Some(l) => l,
        None => return NS_ERROR_FAILURE,
    };

    eprintln!("[zawra-launcher] WPE library loaded from {}", wpe_path.display());

    unsafe {
        // Resolve WPEPlatform + GLib entrypoints
        let wpe_display_headless_new = lib.sym::<unsafe extern "C" fn() -> *mut c_void>("wpe_display_headless_new");
        let wpe_display_connect = lib.sym::<unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> c_int>("wpe_display_connect");
        let webkit_web_view_get_type = lib.sym::<unsafe extern "C" fn() -> usize>("webkit_web_view_get_type");
        let g_object_new = lib.sym::<unsafe extern "C" fn(usize, *const c_char, *mut c_void, *mut c_void) -> *mut c_void>("g_object_new");
        let webkit_web_view_get_wpe_view = lib.sym::<unsafe extern "C" fn(*mut c_void) -> *mut c_void>("webkit_web_view_get_wpe_view");
        let wpe_view_get_toplevel = lib.sym::<unsafe extern "C" fn(*mut c_void) -> *mut c_void>("wpe_view_get_toplevel");
        let wpe_toplevel_resize = lib.sym::<unsafe extern "C" fn(*mut c_void, c_int, c_int)>("wpe_toplevel_resize");
        let wpe_view_map = lib.sym::<unsafe extern "C" fn(*mut c_void)>("wpe_view_map");
        let webkit_web_view_load_uri = lib.sym::<unsafe extern "C" fn(*mut c_void, *const c_char)>("webkit_web_view_load_uri");
        let g_signal_connect_data = lib.sym::<unsafe extern "C" fn(*mut c_void, *const c_char, unsafe extern "C" fn(*mut c_void, *mut c_void, *mut c_void), *mut c_void, *mut c_void, c_int) -> usize>("g_signal_connect_data");
        let g_main_loop_new = lib.sym::<unsafe extern "C" fn(*mut c_void, c_int) -> *mut c_void>("g_main_loop_new");
        let g_main_loop_run = lib.sym::<unsafe extern "C" fn(*mut c_void)>("g_main_loop_run");

        if wpe_display_headless_new.is_none() || g_object_new.is_none() || g_main_loop_run.is_none() {
            eprintln!("[zawra-launcher] Required WPEPlatform / GLib symbols missing in {}", wpe_path.display());
            return NS_ERROR_FAILURE;
        }

        // 1. Initialize Headless WPE Display
        let display = (wpe_display_headless_new.unwrap())();
        let mut err: *mut c_void = null_mut();
        let conn_res = (wpe_display_connect.unwrap())(display, &mut err);
        if conn_res == 0 {
            eprintln!("[zawra-launcher] wpe_display_connect failed");
            return NS_ERROR_FAILURE;
        }

        // 2. Instantiate WebKitWebView with headless display
        let view_type = (webkit_web_view_get_type.unwrap())();
        let web_view = (g_object_new.unwrap())(
            view_type,
            b"display\0".as_ptr() as *const c_char,
            display,
            null_mut(),
        );

        if web_view.is_null() {
            eprintln!("[zawra-launcher] Failed to create WebKitWebView");
            return NS_ERROR_FAILURE;
        }

        let wpe_view = (webkit_web_view_get_wpe_view.unwrap())(web_view);
        let toplevel = (wpe_view_get_toplevel.unwrap())(wpe_view);

        // 3. Configure initial viewport size and map view
        if !toplevel.is_null() {
            (wpe_toplevel_resize.unwrap())(toplevel, 1024, 800);
        }
        if !wpe_view.is_null() {
            (wpe_view_map.unwrap())(wpe_view);
        }

        // 4. Connect "buffer-rendered" signal to receive zero-copy DMA-BUF textures
        if !wpe_view.is_null() && g_signal_connect_data.is_some() {
            (g_signal_connect_data.unwrap())(
                wpe_view,
                b"buffer-rendered\0".as_ptr() as *const c_char,
                on_buffer_rendered,
                null_mut(),
                null_mut(),
                0,
            );
        }

        ACTIVE_WEB_VIEW.store(web_view, Ordering::SeqCst);
        ACTIVE_WPE_VIEW.store(wpe_view, Ordering::SeqCst);
        ACTIVE_TOPLEVEL.store(toplevel, Ordering::SeqCst);

        // Store library handle for idle and signal callbacks
        *WPE_LIB.lock().unwrap() = Some(lib);

        // 5. Initial navigation to default page (triggers WPEWebProcess / WPENetworkProcess bootstrap)
        if let Some(load_uri) = webkit_web_view_load_uri {
            let start_uri = b"https://github.com\0".as_ptr() as *const c_char;
            load_uri(web_view, start_uri);
        }

        // 6. Run GLib Main Loop
        let loop_handle = (g_main_loop_new.unwrap())(null_mut(), 0);
        GLIB_MAIN_LOOP.store(loop_handle, Ordering::SeqCst);

        eprintln!("[zawra-launcher] WebKit GLib loop running ✓");
        (g_main_loop_run.unwrap())(loop_handle);

        0
    }
}

/// Hajr-powered process launcher.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_SpawnProcess(
    path: *const c_char,
    argv: *const *const c_char,
    out_socket: *mut c_int,
) -> c_int {
    if path.is_null() || argv.is_null() {
        return -1;
    }
    unsafe { hajr_spawn_compartment(path, argv, out_socket) }
}

/// Exported C-ABI bootstrap function.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Bootstrap(profile_path: *const c_char) -> i32 {
    let profile_str = if profile_path.is_null() {
        resolve_profile_dir().to_string_lossy().into_owned()
    } else {
        match unsafe { std::ffi::CStr::from_ptr(profile_path).to_str() } {
            Ok(s) => s.to_string(),
            Err(_) => resolve_profile_dir().to_string_lossy().into_owned(),
        }
    };

    if bootstrap_zawra(&profile_str) { NS_OK } else { NS_ERROR_FAILURE }
}

/// Perform a graceful shutdown.
#[unsafe(no_mangle)]
pub extern "C" fn Z_ProcessShutdown() {
    unsafe { Z_Shutdown_Subsystems() };
    eprintln!("[zawra-launcher] Process shutdown complete");
}
