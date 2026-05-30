//! Zawra Browser Window
//!
//! Top-level native window wrapper. Communicates with WPE's embedding layer.
//! Falls back to a headless "virtual window" when WPE is not present.

use std::sync::{Arc, Mutex};

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

// ── Native window helpers (GTK stubs) ────────────────────────────────────────

fn create_native_window(_config: &WindowConfig) -> *mut std::ffi::c_void {
    // When GTK4 is available this would call:
    //   gtk_window_new() → gtk_widget_show_all()
    // For now return NULL — all operations degrade gracefully.
    std::ptr::null_mut()
}

fn show_native_window(_handle: *mut std::ffi::c_void) {
    // gtk_widget_show_all(handle);
}

fn set_native_title(_handle: *mut std::ffi::c_void, title: &str) {
    // gtk_window_set_title(handle, title);
    eprintln!("[zawra-ui] set_title: {}", title);
}
