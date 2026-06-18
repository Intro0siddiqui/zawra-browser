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

// ── Native window helpers (GTK / Wayland dynamically loaded) ──────────────────

struct GtkLib {
    gtk_init: unsafe extern "C" fn(),
    gtk_window_new: unsafe extern "C" fn() -> *mut c_void,
    gtk_window_set_title: unsafe extern "C" fn(*mut c_void, *const c_char),
    gtk_window_set_default_size: unsafe extern "C" fn(*mut c_void, i32, i32),
    gtk_window_present: unsafe extern "C" fn(*mut c_void),
}

fn load_gtk() -> Option<&'static GtkLib> {
    static GTK_LIB: OnceLock<Option<GtkLib>> = OnceLock::new();
    GTK_LIB.get_or_init(|| {
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

fn create_native_window(config: &WindowConfig) -> *mut std::ffi::c_void {
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

fn show_native_window(handle: *mut std::ffi::c_void) {
    if let Some(gtk) = load_gtk() {
        unsafe {
            (gtk.gtk_window_present)(handle);
        }
    }
}

fn set_native_title(handle: *mut std::ffi::c_void, title: &str) {
    if let Some(gtk) = load_gtk() {
        if let Ok(title_c) = CString::new(title) {
            unsafe {
                (gtk.gtk_window_set_title)(handle, title_c.as_ptr());
            }
        }
    }
}
