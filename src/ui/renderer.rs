//! Zawra Renderer Embedding
//!
//! Manages the embedding of WPE's content area inside the
//! native browser window widget. When WPE is not available (headless mode),
//! this module provides a stub that logs rendered output.

use std::ffi::{c_char, c_void, CString};
use std::sync::{Arc, Mutex};

/// The dimensions of the render viewport.
#[derive(Debug, Clone, Copy)]
pub struct Viewport {
    pub x:      i32,
    pub y:      i32,
    pub width:  u32,
    pub height: u32,
}

/// State of the renderer.
#[derive(Debug, Clone, PartialEq)]
pub enum RendererState {
    Uninitialised,
    Embedding,
    Active,
    Destroyed,
}

/// Wraps WPE's embedding widget.
pub struct RendererEmbed {
    state:         Mutex<RendererState>,
    viewport:      Mutex<Viewport>,
    /// Native WPE web browser handle
    web_browser:   *mut c_void,
    /// Native window handle used to host WPE's rendering
    parent_window: *mut c_void,
}

// SAFETY: Managed by WPE's single-threaded event loop.
unsafe impl Send for RendererEmbed {}
unsafe impl Sync for RendererEmbed {}

impl RendererEmbed {
    /// Create a new renderer embed in the given native window.
    pub fn new(parent_window: *mut c_void, viewport: Viewport) -> Arc<Self> {
        Arc::new(RendererEmbed {
            state:         Mutex::new(RendererState::Uninitialised),
            viewport:      Mutex::new(viewport),
            web_browser:   std::ptr::null_mut(),
            parent_window,
        })
    }

    /// Initialise the WPE embed. Must be called after WPE is ready.
    pub fn init(&self) -> bool {
        #[cfg(wpe_available)]
        {
            // In a real implementation:
            // 1. Create WPE view
            // 2. Set container window
            // 3. Init window
            if let Ok(mut s) = self.state.lock() {
                *s = RendererState::Embedding;
            }
            eprintln!("[zawra-renderer] WPE embed initialised (headless stub)");
            return true;
        }

        #[cfg(not(wpe_available))]
        {
            if let Ok(mut s) = self.state.lock() {
                *s = RendererState::Active;
            }
            eprintln!("[zawra-renderer] Headless mode — no WPE embed");
            true
        }
    }

    /// Navigate the embedded browser to a URL.
    pub fn navigate(&self, url: &str) {
        #[cfg(wpe_available)]
        {
            // WPE navigation
            eprintln!("[zawra-renderer] navigate → {}", url);
        }
        #[cfg(not(wpe_available))]
        {
            eprintln!("[zawra-renderer] headless navigate → {}", url);
        }
    }

    /// Resize the viewport (called when the window is resized).
    pub fn resize(&self, width: u32, height: u32) {
        if let Ok(mut vp) = self.viewport.lock() {
            vp.width  = width;
            vp.height = height;
        }
        // nsIBaseWindow::SetSize(width, height, true)
        eprintln!("[zawra-renderer] viewport resized to {}×{}", width, height);
    }

    /// Stop the current page load.
    pub fn stop(&self) {
        // nsIWebNavigation::Stop(nsIWebNavigation::STOP_ALL)
        eprintln!("[zawra-renderer] stop");
    }

    /// Reload the current page.
    pub fn reload(&self, bypass_cache: bool) {
        // nsIWebNavigation::Reload(LOAD_FLAGS_NONE or LOAD_FLAGS_BYPASS_CACHE)
        eprintln!("[zawra-renderer] reload (bypass_cache={})", bypass_cache);
    }

    pub fn go_back(&self) {
        // nsIWebNavigation::GoBack()
        eprintln!("[zawra-renderer] go_back");
    }

    pub fn go_forward(&self) {
        // nsIWebNavigation::GoForward()
        eprintln!("[zawra-renderer] go_forward");
    }

    pub fn destroy(&self) {
        if let Ok(mut s) = self.state.lock() {
            *s = RendererState::Destroyed;
        }
        eprintln!("[zawra-renderer] destroyed");
    }
}
