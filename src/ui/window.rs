//! Zawra Browser Window
//!
//! Top-level native window wrapper. Communicates with WPE's embedding layer.
//! Falls back to a headless "virtual window" when WPE is not present.

use std::sync::{Arc, Mutex, OnceLock};
use std::ffi::{CString, c_char, c_void};

/// Configuration for the browser window.
#[derive(Debug, Clone)]
pub struct WindowConfig {
    pub title:      String,
    pub width:      u32,
    pub height:     u32,
    pub resizable:  bool,
}

impl Default for WindowConfig {
    fn default() -> Self {
        WindowConfig {
            title:     "Zawra Browser".to_string(),
            width:     1280,
            height:    800,
            resizable: true,
        }
    }
}

/// State of a browser window.
#[derive(Debug, Clone, PartialEq)]
pub enum WindowState {
    Initialising,
    Ready,
    Minimised,
    Maximised,
    Closed,
}

/// The top-level browser window.
pub struct BrowserWindow {
    config: WindowConfig,
    state:  Mutex<WindowState>,
    /// Native window handle (opaque). On Linux this is a `GtkWindow*`.
    /// NULL in headless mode.
    native_handle: *mut std::ffi::c_void,
}

// SAFETY: The native_handle is managed by GTK's event loop thread.
unsafe impl Send for BrowserWindow {}
unsafe impl Sync for BrowserWindow {}

impl BrowserWindow {
    /// Create a new browser window. In headless mode (no GTK / no WPE)
    /// this returns a valid struct with a NULL native handle.
    pub fn new(config: WindowConfig) -> Arc<Self> {
        let native = create_native_window(&config);
        Arc::new(BrowserWindow {
            config,
            state: Mutex::new(WindowState::Initialising),
            native_handle: native,
        })
    }

    /// Mark the window as ready and show it on screen.
    pub fn show(&self) {
        if let Ok(mut s) = self.state.lock() {
            *s = WindowState::Ready;
        }
        if !self.native_handle.is_null() {
            show_native_window(self.native_handle);
        } else {
            eprintln!("[zawra-ui] Window '{}' ready (headless)", self.config.title);
        }
    }

    /// Set the window title (e.g. "<page title> — Zawra Browser").
    pub fn set_title(&self, title: &str) {
        if !self.native_handle.is_null() {
            set_native_title(self.native_handle, title);
        } else {
            eprintln!("[zawra-ui] Title: {}", title);
        }
    }

    /// Return the window dimensions (width, height).
    pub fn size(&self) -> (u32, u32) {
        (self.config.width, self.config.height)
    }

    pub fn is_headless(&self) -> bool {
        self.native_handle.is_null()
    }
}

// ── Native window helpers ───────────────────────────────────────────────────

#[cfg(not(any(target_os = "android", target_os = "windows")))]
struct GtkLib {
    gtk_init: unsafe extern "C" fn(),
    gtk_window_new: unsafe extern "C" fn() -> *mut c_void,
    gtk_window_set_title: unsafe extern "C" fn(*mut c_void, *const c_char),
    gtk_window_set_default_size: unsafe extern "C" fn(*mut c_void, i32, i32),
    gtk_window_present: unsafe extern "C" fn(*mut c_void),
}

#[cfg(not(any(target_os = "android", target_os = "windows")))]
fn load_gtk() -> Option<&'static GtkLib> {
    static GTK_LIB: OnceLock<Option<GtkLib>> = OnceLock::new();
    GTK_LIB.get_or_init(|| {
        #[cfg(target_os = "macos")]
        let paths = [
            "libgtk-4.1.dylib",
            "libgtk-4.dylib",
            "/opt/homebrew/lib/libgtk-4.1.dylib",
            "/opt/homebrew/lib/libgtk-4.dylib",
            "/usr/local/lib/libgtk-4.1.dylib",
            "/usr/local/lib/libgtk-4.dylib",
            "libgtk-4.so.1",
            "libgtk-4.so",
        ];
        #[cfg(not(target_os = "macos"))]
        let paths = ["libgtk-4.so.1", "libgtk-4.so"];
        let mut handle = std::ptr::null_mut();
        for path in &paths {
            if let Ok(path_c) = CString::new(*path) {
                handle = unsafe { libc::dlopen(path_c.as_ptr(), libc::RTLD_LAZY | libc::RTLD_GLOBAL) };
                if !handle.is_null() {
                    break;
                }
            }
        }
        if handle.is_null() {
            eprintln!("[zawra-ui] Failed to load libgtk-4 dynamically");
            return None;
        }

        unsafe {
            let sym = |name: &str| -> Option<*mut c_void> {
                let name_c = CString::new(name).ok()?;
                let ptr = libc::dlsym(handle, name_c.as_ptr());
                if ptr.is_null() {
                    None
                } else {
                    Some(ptr)
                }
            };

            let gtk_init = std::mem::transmute(sym("gtk_init")?);
            let gtk_window_new = std::mem::transmute(sym("gtk_window_new")?);
            let gtk_window_set_title = std::mem::transmute(sym("gtk_window_set_title")?);
            let gtk_window_set_default_size = std::mem::transmute(sym("gtk_window_set_default_size")?);
            let gtk_window_present = std::mem::transmute(sym("gtk_window_present")?);

            Some(GtkLib {
                gtk_init,
                gtk_window_new,
                gtk_window_set_title,
                gtk_window_set_default_size,
                gtk_window_present,
            })
        }
    }).as_ref()
}

#[cfg(target_os = "windows")]
fn create_win32_window(config: &WindowConfig) -> *mut std::ffi::c_void {
    extern "system" {
        fn DefWindowProcW(
            hWnd: *mut std::ffi::c_void,
            Msg: u32,
            wParam: usize,
            lParam: isize,
        ) -> isize;
        fn GetModuleHandleW(lpModuleName: *const u16) -> *mut std::ffi::c_void;
        fn RegisterClassW(lpWndClass: *const WndClassW) -> u16;
        fn CreateWindowExW(
            dwExStyle: u32,
            lpClassName: *const u16,
            lpWindowName: *const u16,
            dwStyle: u32,
            X: i32,
            Y: i32,
            nWidth: i32,
            nHeight: i32,
            hWndParent: *mut std::ffi::c_void,
            hMenu: *mut std::ffi::c_void,
            hInstance: *mut std::ffi::c_void,
            lpParam: *mut std::ffi::c_void,
        ) -> *mut std::ffi::c_void;
    }

    #[repr(C)]
    struct WndClassW {
        style: u32,
        lpfnWndProc: unsafe extern "system" fn(*mut std::ffi::c_void, u32, usize, isize) -> isize,
        cbClsExtra: i32,
        cbWndExtra: i32,
        hInstance: *mut std::ffi::c_void,
        hIcon: *mut std::ffi::c_void,
        hCursor: *mut std::ffi::c_void,
        hbrBackground: *mut std::ffi::c_void,
        lpszMenuName: *const u16,
        lpszClassName: *const u16,
    }

    let class_name: Vec<u16> = "ZawraBrowserWindow\0".encode_utf16().collect();
    let title: Vec<u16> = config.title.encode_utf16().chain(std::iter::once(0)).collect();

    unsafe {
        let h_instance = GetModuleHandleW(std::ptr::null());
        let wnd_class = WndClassW {
            style: 0x0002 | 0x0001,
            lpfnWndProc: DefWindowProcW,
            cbClsExtra: 0,
            cbWndExtra: 0,
            hInstance: h_instance,
            hIcon: std::ptr::null_mut(),
            hCursor: std::ptr::null_mut(),
            hbrBackground: std::ptr::null_mut(),
            lpszMenuName: std::ptr::null(),
            lpszClassName: class_name.as_ptr(),
        };
        RegisterClassW(&wnd_class);

        const WS_OVERLAPPEDWINDOW: u32 = 0x00CF0000;
        const CW_USEDEFAULT: i32 = 0x80000000u32 as i32;

        CreateWindowExW(
            0,
            class_name.as_ptr(),
            title.as_ptr(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            config.width as i32,
            config.height as i32,
            std::ptr::null_mut(),
            std::ptr::null_mut(),
            h_instance,
            std::ptr::null_mut(),
        )
    }
}

#[cfg(target_os = "windows")]
fn show_win32_window(handle: *mut std::ffi::c_void) {
    extern "system" {
        fn ShowWindow(hWnd: *mut std::ffi::c_void, nCmdShow: i32) -> i32;
        fn UpdateWindow(hWnd: *mut std::ffi::c_void) -> i32;
    }
    const SW_SHOW: i32 = 5;
    unsafe {
        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
    }
}

#[cfg(target_os = "windows")]
fn set_win32_title(handle: *mut std::ffi::c_void, title: &str) {
    extern "system" {
        fn SetWindowTextW(hWnd: *mut std::ffi::c_void, lpString: *const u16) -> i32;
    }
    let title_utf16: Vec<u16> = title.encode_utf16().chain(std::iter::once(0)).collect();
    unsafe {
        SetWindowTextW(handle, title_utf16.as_ptr());
    }
}

fn create_native_window(config: &WindowConfig) -> *mut std::ffi::c_void {
    #[cfg(target_os = "android")]
    {
        let _ = config;
        return std::ptr::null_mut();
    }
    #[cfg(target_os = "windows")]
    {
        if std::env::var("ZAWRA_HEADLESS").is_ok() {
            return std::ptr::null_mut();
        }
        create_win32_window(config)
    }
    #[cfg(not(any(target_os = "android", target_os = "windows")))]
    {
        if std::env::var("ZAWRA_HEADLESS").is_ok() {
            return std::ptr::null_mut();
        }

        if let Some(gtk) = load_gtk() {
            unsafe {
                static INIT: std::sync::Once = std::sync::Once::new();
                INIT.call_once(|| {
                    (gtk.gtk_init)();
                });

                let window = (gtk.gtk_window_new)();
                if window.is_null() {
                    eprintln!("[zawra-ui] Failed to create GtkWindow");
                    return std::ptr::null_mut();
                }

                if let Ok(title_c) = CString::new(config.title.clone()) {
                    (gtk.gtk_window_set_title)(window, title_c.as_ptr());
                }
                (gtk.gtk_window_set_default_size)(window, config.width as i32, config.height as i32);

                window
            }
        } else {
            std::ptr::null_mut()
        }
    }
}

fn show_native_window(handle: *mut std::ffi::c_void) {
    #[cfg(target_os = "windows")]
    show_win32_window(handle);
    #[cfg(not(any(target_os = "android", target_os = "windows")))]
    if let Some(gtk) = load_gtk() {
        unsafe {
            (gtk.gtk_window_present)(handle);
        }
    }
}

fn set_native_title(handle: *mut std::ffi::c_void, title: &str) {
    #[cfg(target_os = "windows")]
    set_win32_title(handle, title);
    #[cfg(not(any(target_os = "android", target_os = "windows")))]
    if let Some(gtk) = load_gtk() {
        if let Ok(title_c) = CString::new(title) {
            unsafe {
                (gtk.gtk_window_set_title)(handle, title_c.as_ptr());
            }
        }
    }
}
