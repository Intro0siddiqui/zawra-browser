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

#[allow(dead_code)]
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
        assert_eq!(
            std::mem::size_of::<T>(),
            std::mem::size_of::<*mut c_void>(),
            "DynLib::sym called with non-pointer size type"
        );
        let name_c = CString::new(name).ok()?;
        #[cfg(target_os = "windows")]
        {
            extern "system" {
                fn GetProcAddress(hModule: *mut c_void, lpProcName: *const c_char) -> *mut c_void;
            }
            let ptr = unsafe { GetProcAddress(self.handle, name_c.as_ptr()) };
            if ptr.is_null() { None } else { Some(unsafe { std::mem::transmute_copy(&ptr) }) }
        }
        #[cfg(not(target_os = "windows"))]
        {
            let ptr = unsafe { libc::dlsym(self.handle, name_c.as_ptr()) };
            if ptr.is_null() { None } else { Some(unsafe { std::mem::transmute_copy(&ptr) }) }
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

#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub struct ZawraGraphicsDMABufInfo {
    pub fd: i32,
    pub width: u32,
    pub height: u32,
    pub stride: u32,
    pub offset: u32,
    pub drm_format: u32,
    pub drm_modifier: u64,
}

#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub struct ZawraPendingWpeFrame {
    pub dmabuf: ZawraGraphicsDMABufInfo,
    pub view: *mut c_void,
    pub buffer: *mut c_void,
}

unsafe impl Send for ZawraPendingWpeFrame {}
unsafe impl Sync for ZawraPendingWpeFrame {}

static PENDING_WPE_FRAME: Mutex<Option<ZawraPendingWpeFrame>> = Mutex::new(None);

/// Called by the main thread (shell.zig) each frame to retrieve any newly arrived DMA-BUF frame.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_PollPendingWpeFrame(out_frame: *mut ZawraPendingWpeFrame) -> bool {
    if out_frame.is_null() {
        return false;
    }
    if let Ok(mut lock) = PENDING_WPE_FRAME.lock() {
        if let Some(frame) = lock.take() {
            unsafe {
                *out_frame = frame;
            }
            return true;
        }
    }
    false
}

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

/// Legacy fallback: called by shell each frame to retrieve DMA-BUF frame.
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

type GObjectNewFn = unsafe extern "C" fn(
    object_type: usize,
    first_property_name: *const c_char,
    ...
) -> *mut c_void;

#[derive(Clone, Copy)]
struct WpeSymbols {
    wpe_buffer_dma_buf_get_type: unsafe extern "C" fn() -> usize,
    g_type_check_instance_is_a: unsafe extern "C" fn(*mut c_void, usize) -> i32,
    wpe_buffer_dma_buf_get_fd: unsafe extern "C" fn(*mut c_void, u32) -> i32,
    wpe_buffer_dma_buf_get_stride: unsafe extern "C" fn(*mut c_void, u32) -> u32,
    wpe_buffer_dma_buf_get_format: unsafe extern "C" fn(*mut c_void) -> u32,
    wpe_buffer_dma_buf_get_modifier: unsafe extern "C" fn(*mut c_void) -> u64,
    wpe_buffer_get_width: unsafe extern "C" fn(*mut c_void) -> i32,
    wpe_buffer_get_height: unsafe extern "C" fn(*mut c_void) -> i32,
    g_idle_add: unsafe extern "C" fn(unsafe extern "C" fn(*mut c_void) -> i32, *mut c_void) -> u32,
    webkit_web_view_load_uri: unsafe extern "C" fn(*mut c_void, *const c_char),
    wpe_toplevel_resize: unsafe extern "C" fn(*mut c_void, c_int, c_int),
    wpe_view_resized: Option<unsafe extern "C" fn(*mut c_void, c_int, c_int)>,
    wpe_view_buffer_rendered: Option<unsafe extern "C" fn(*mut c_void, *mut c_void)>,
    wpe_view_event: Option<unsafe extern "C" fn(*mut c_void, *mut c_void)>,
    wpe_event_unref: Option<unsafe extern "C" fn(*mut c_void)>,
    wpe_event_pointer_move_new: Option<unsafe extern "C" fn(u32, *mut c_void, u32, u32, u32, f64, f64, f64, f64) -> *mut c_void>,
    wpe_event_pointer_button_new: Option<unsafe extern "C" fn(u32, *mut c_void, u32, u32, u32, u32, f64, f64, u32) -> *mut c_void>,
    wpe_event_keyboard_new: Option<unsafe extern "C" fn(u32, *mut c_void, u32, u32, u32, u32, u32) -> *mut c_void>,
}

static WPE_SYMS: Mutex<Option<WpeSymbols>> = Mutex::new(None);

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// WPE Frame Reception Callback (GLib thread)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

unsafe extern "C" fn on_buffer_rendered(
    view: *mut c_void,
    buffer: *mut c_void,
    _user_data: *mut c_void,
) {
    if buffer.is_null() {
        return;
    }

    let syms = match WPE_SYMS.lock() {
        Ok(guard) => match *guard {
            Some(s) => s,
            None => return,
        },
        Err(_) => return,
    };

    unsafe {
        let dmabuf_type = (syms.wpe_buffer_dma_buf_get_type)();
        if (syms.g_type_check_instance_is_a)(buffer, dmabuf_type) == 0 {
            return;
        }

        let raw_fd = (syms.wpe_buffer_dma_buf_get_fd)(buffer, 0);
        if raw_fd < 0 {
            return;
        }

        let dup_fd = libc::dup(raw_fd);
        if dup_fd < 0 {
            return;
        }

        let stride = (syms.wpe_buffer_dma_buf_get_stride)(buffer, 0);
        let fourcc = (syms.wpe_buffer_dma_buf_get_format)(buffer);
        let modifier = (syms.wpe_buffer_dma_buf_get_modifier)(buffer);
        let width = (syms.wpe_buffer_get_width)(buffer) as u32;
        let height = (syms.wpe_buffer_get_height)(buffer) as u32;

        eprintln!(
            "[ZAWRA-GLIB] >>> DMA-BUF Frame Arrived: raw_fd={} dup_fd={} {}x{} stride={} format=0x{:x} <<<",
            raw_fd, dup_fd, width, height, stride, fourcc
        );

        if width > 0 && height > 0 {
            let dmabuf = ZawraGraphicsDMABufInfo {
                fd: dup_fd,
                width,
                height,
                stride,
                offset: 0,
                drm_format: fourcc,
                drm_modifier: modifier,
            };
            if let Ok(mut lock) = PENDING_WPE_FRAME.lock() {
                if let Some(old) = lock.take() {
                    libc::close(old.dmabuf.fd);
                    Zawra_NotifyWpeBufferRendered(old.view, old.buffer);
                }
                *lock = Some(ZawraPendingWpeFrame {
                    dmabuf,
                    view,
                    buffer,
                });
            }
            if let Ok(mut lock) = PENDING_FRAME.lock() {
                if let Some(old) = lock.take() {
                    libc::close(old.fd);
                }
                let legacy_fd = libc::dup(dup_fd);
                if legacy_fd >= 0 {
                    *lock = Some(PendingDMABuf {
                        fd: legacy_fd,
                        width,
                        height,
                        stride,
                        fourcc,
                        modifier,
                    });
                }
            }
        } else {
            libc::close(dup_fd);
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Main Thread -> GLib Thread Marshallers (g_idle_add)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

unsafe extern "C" fn idle_load_url(data: *mut c_void) -> i32 {
    let c_url = unsafe { Box::from_raw(data as *mut CString) };
    let web_view = ACTIVE_WEB_VIEW.load(Ordering::SeqCst);
    if !web_view.is_null() {
        if let Ok(guard) = WPE_SYMS.lock() {
            if let Some(syms) = *guard {
                eprintln!("[ZAWRA-GLIB] Loading URI: {:?}", c_url);
                unsafe {
                    (syms.webkit_web_view_load_uri)(web_view, c_url.as_ptr());
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
        let syms = match WPE_SYMS.lock() {
            Ok(g) => *g,
            Err(_) => None,
        };
        if let Some(syms) = syms {
            let boxed = Box::into_raw(Box::new(c_url));
            unsafe {
                (syms.g_idle_add)(idle_load_url, boxed as *mut c_void);
            }
        }
    }
}

struct ResizeMsg {
    width: i32,
    height: i32,
}

unsafe extern "C" fn idle_resize(data: *mut c_void) -> i32 {
    let msg = unsafe { Box::from_raw(data as *mut ResizeMsg) };
    let toplevel = ACTIVE_TOPLEVEL.load(Ordering::SeqCst);
    let wpe_view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);

    if let Ok(guard) = WPE_SYMS.lock() {
        if let Some(syms) = *guard {
            if !toplevel.is_null() {
                unsafe {
                    (syms.wpe_toplevel_resize)(toplevel, msg.width, msg.height);
                }
            }
            if !wpe_view.is_null() {
                if let Some(view_resize) = syms.wpe_view_resized {
                    unsafe {
                        view_resize(wpe_view, msg.width, msg.height);
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Resize hook: updates WPE viewport dimensions cleanly on the GLib thread.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_ResizeViewport(width: u32, height: u32) {
    let syms = match WPE_SYMS.lock() {
        Ok(g) => *g,
        Err(_) => None,
    };
    if let Some(syms) = syms {
        let msg = Box::new(ResizeMsg {
            width: width as i32,
            height: height as i32,
        });
        let boxed = Box::into_raw(msg);
        unsafe {
            (syms.g_idle_add)(idle_resize, boxed as *mut c_void);
        }
    }
}

/// View resized alias for River compositor layout updates.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_ViewResized(width: u32, height: u32) {
    Zawra_ResizeViewport(width, height);
}

struct RenderedMsg {
    view: *mut c_void,
    buffer: *mut c_void,
}

unsafe extern "C" fn idle_buffer_rendered(data: *mut c_void) -> i32 {
    let msg = unsafe { Box::from_raw(data as *mut RenderedMsg) };
    if !msg.view.is_null() && !msg.buffer.is_null() {
        if let Ok(guard) = WPE_SYMS.lock() {
            if let Some(syms) = *guard {
                if let Some(rendered_fn) = syms.wpe_view_buffer_rendered {
                    unsafe {
                        rendered_fn(msg.view, msg.buffer);
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Notify Rust that a WPEBuffer has finished rendering on the GPU,
/// dispatching wpe_view_buffer_rendered to the GLib main loop.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_NotifyWpeBufferRendered(view: *mut c_void, buffer: *mut c_void) {
    if view.is_null() || buffer.is_null() {
        return;
    }
    let syms = match WPE_SYMS.lock() {
        Ok(g) => *g,
        Err(_) => None,
    };
    if let Some(syms) = syms {
        let msg = Box::new(RenderedMsg { view, buffer });
        let boxed = Box::into_raw(msg);
        unsafe {
            (syms.g_idle_add)(idle_buffer_rendered, boxed as *mut c_void);
        }
    }
}

struct PointerEventMsg {
    event_type: u32,
    local_x: f64,
    local_y: f64,
    button: u32,
    #[allow(dead_code)]
    state: u32,
}

unsafe extern "C" fn idle_pointer_event(data: *mut c_void) -> i32 {
    let msg = unsafe { Box::from_raw(data as *mut PointerEventMsg) };
    let view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);
    if !view.is_null() {
        if let Ok(guard) = WPE_SYMS.lock() {
            if let Some(syms) = *guard {
                if let (Some(wpe_view_event), Some(wpe_event_unref)) = (syms.wpe_view_event, syms.wpe_event_unref) {
                    let ev: *mut c_void = match msg.event_type {
                        0 => {
                            // Motion (WPE_EVENT_POINTER_MOVE = 3)
                            syms.wpe_event_pointer_move_new.map(|f| unsafe {
                                f(3, view, 0, 0, 0, msg.local_x, msg.local_y, 0.0, 0.0)
                            }).unwrap_or(null_mut())
                        }
                        1 => {
                            // Button down (WPE_EVENT_POINTER_DOWN = 1)
                            syms.wpe_event_pointer_button_new.map(|f| unsafe {
                                f(1, view, 0, 0, 0, if msg.button == 0 { 1 } else { msg.button }, msg.local_x, msg.local_y, 1)
                            }).unwrap_or(null_mut())
                        }
                        2 => {
                            // Button up (WPE_EVENT_POINTER_UP = 2)
                            syms.wpe_event_pointer_button_new.map(|f| unsafe {
                                f(2, view, 0, 0, 0, if msg.button == 0 { 1 } else { msg.button }, msg.local_x, msg.local_y, 1)
                            }).unwrap_or(null_mut())
                        }
                        _ => null_mut(),
                    };
                    if !ev.is_null() {
                        unsafe {
                            wpe_view_event(view, ev);
                            wpe_event_unref(ev);
                        }
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Input event forwarding: pointer events (motion, button, scroll) dispatched via GLib idle
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_pointer(
    event_type: u32,
    local_x: f64,
    local_y: f64,
    button: u32,
    state: u32,
) {
    let syms = match WPE_SYMS.lock() {
        Ok(g) => *g,
        Err(_) => None,
    };
    if let Some(syms) = syms {
        let msg = Box::into_raw(Box::new(PointerEventMsg {
            event_type,
            local_x,
            local_y,
            button,
            state,
        }));
        unsafe {
            (syms.g_idle_add)(idle_pointer_event, msg as *mut c_void);
        }
    }
}

struct KeyboardEventMsg {
    key: u32,
    state: u32,
    modifiers: u32,
}

unsafe extern "C" fn idle_keyboard_event(data: *mut c_void) -> i32 {
    let msg = unsafe { Box::from_raw(data as *mut KeyboardEventMsg) };
    let view = ACTIVE_WPE_VIEW.load(Ordering::SeqCst);
    if !view.is_null() {
        if let Ok(guard) = WPE_SYMS.lock() {
            if let Some(syms) = *guard {
                if let (Some(wpe_view_event), Some(wpe_event_unref), Some(key_new)) =
                    (syms.wpe_view_event, syms.wpe_event_unref, syms.wpe_event_keyboard_new)
                {
                    let ev_type = if msg.state == 1 { 7 /* KEY_DOWN */ } else { 8 /* KEY_UP */ };
                    let ev = unsafe {
                        key_new(ev_type, view, 2 /* KEYBOARD */, 0, msg.modifiers, msg.key, msg.key)
                    };
                    if !ev.is_null() {
                        unsafe {
                            wpe_view_event(view, ev);
                            wpe_event_unref(ev);
                        }
                    }
                }
            }
        }
    }
    0 // G_SOURCE_REMOVE
}

/// Input event forwarding: keyboard events dispatched via GLib idle
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_keyboard(
    key: u32,
    state: u32,
    modifiers: u32,
) {
    let syms = match WPE_SYMS.lock() {
        Ok(g) => *g,
        Err(_) => None,
    };
    if let Some(syms) = syms {
        let msg = Box::into_raw(Box::new(KeyboardEventMsg {
            key,
            state,
            modifiers,
        }));
        unsafe {
            (syms.g_idle_add)(idle_keyboard_event, msg as *mut c_void);
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
        let g_object_new = lib.sym::<GObjectNewFn>("g_object_new");
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

        // Cache symbols for on_buffer_rendered and idle callbacks (prevents per-frame dlsym calls)
        let sym_cache = WpeSymbols {
            wpe_buffer_dma_buf_get_type: lib.sym("wpe_buffer_dma_buf_get_type").expect("wpe_buffer_dma_buf_get_type missing"),
            g_type_check_instance_is_a: lib.sym("g_type_check_instance_is_a").expect("g_type_check_instance_is_a missing"),
            wpe_buffer_dma_buf_get_fd: lib.sym("wpe_buffer_dma_buf_get_fd").expect("wpe_buffer_dma_buf_get_fd missing"),
            wpe_buffer_dma_buf_get_stride: lib.sym("wpe_buffer_dma_buf_get_stride").expect("wpe_buffer_dma_buf_get_stride missing"),
            wpe_buffer_dma_buf_get_format: lib.sym("wpe_buffer_dma_buf_get_format").expect("wpe_buffer_dma_buf_get_format missing"),
            wpe_buffer_dma_buf_get_modifier: lib.sym("wpe_buffer_dma_buf_get_modifier").expect("wpe_buffer_dma_buf_get_modifier missing"),
            wpe_buffer_get_width: lib.sym("wpe_buffer_get_width").expect("wpe_buffer_get_width missing"),
            wpe_buffer_get_height: lib.sym("wpe_buffer_get_height").expect("wpe_buffer_get_height missing"),
            g_idle_add: lib.sym("g_idle_add").expect("g_idle_add missing"),
            webkit_web_view_load_uri: webkit_web_view_load_uri.expect("webkit_web_view_load_uri missing"),
            wpe_toplevel_resize: wpe_toplevel_resize.expect("wpe_toplevel_resize missing"),
            wpe_view_resized: lib.sym("wpe_view_resized"),
            wpe_view_buffer_rendered: lib.sym("wpe_view_buffer_rendered"),
            wpe_view_event: lib.sym("wpe_view_event"),
            wpe_event_unref: lib.sym("wpe_event_unref"),
            wpe_event_pointer_move_new: lib.sym("wpe_event_pointer_move_new"),
            wpe_event_pointer_button_new: lib.sym("wpe_event_pointer_button_new"),
            wpe_event_keyboard_new: lib.sym("wpe_event_keyboard_new"),
        };
        *WPE_SYMS.lock().unwrap() = Some(sym_cache);

        // 1. Initialize Headless WPE Display
        let display = (wpe_display_headless_new.unwrap())();
        let mut err: *mut c_void = null_mut();
        let conn_res = (wpe_display_connect.unwrap())(display, &mut err);
        if conn_res == 0 {
            eprintln!("[zawra-launcher] wpe_display_connect failed");
            return NS_ERROR_FAILURE;
        }

        // 2. Instantiate WebKitWebView with headless display using Rust C-variadic call (%al = 0)
        let view_type = (webkit_web_view_get_type.unwrap())();
        let web_view = (g_object_new.unwrap())(
            view_type,
            c"display".as_ptr(),
            display,
            null_mut::<c_void>(),
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
            eprintln!("[zawra-launcher] Connecting 'buffer-rendered' signal on WPEView {:?}", wpe_view);
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
            let start_uri = b"data:text/html,<html><body style='background:%230b101b;color:%2300ffcc;font-family:sans-serif;padding:40px;'><h1>Zawra Browser</h1><p style='color:%23ffffff;'>Vulkan 60FPS + WebKit 2.54 Zero-Copy DMA-BUF Active</p></body></html>\0".as_ptr() as *const c_char;
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
