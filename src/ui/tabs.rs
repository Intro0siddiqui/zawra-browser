//! Zawra Tab Manager
//!
//! Manages the lifecycle of browser tabs, their associated WPE content
//! processes, and per-tab BrowserDB containers.

use std::collections::HashMap;
use std::sync::{Arc, Mutex};

/// A unique tab identifier.
pub type TabId = u64;

/// The state a tab can be in.
#[derive(Debug, Clone, PartialEq)]
pub enum TabState {
    Loading,
    Ready,
    Crashed,
    Closed,
}

/// Per-tab data.
pub struct Tab {
    pub id: TabId,
    pub url: String,
    pub title: String,
    pub state: TabState,
    /// Each tab gets its own BrowserDB container for isolated storage.
    pub container_id: String,
    /// WPE content process handle (opaque). NULL in headless mode.
    #[allow(dead_code)]
    content_proc: *mut std::ffi::c_void,
}

// SAFETY: content_proc is managed by WPE's process lifecycle.
unsafe impl Send for Tab {}
unsafe impl Sync for Tab {}

impl Tab {
    fn new(id: TabId, url: &str) -> Self {
        Tab {
            id,
            url: url.to_string(),
            title: "New Tab".to_string(),
            state: TabState::Loading,
            container_id: format!("tab_{}", id),
            content_proc: std::ptr::null_mut(),
        }
    }
}

/// Manages all tabs for a browser window.
pub struct TabManager {
    tabs: Mutex<HashMap<TabId, Tab>>,
    active_tab: Mutex<Option<TabId>>,
    next_id: std::sync::atomic::AtomicU64,
}

impl TabManager {
    pub fn new() -> Arc<Self> {
        Arc::new(TabManager {
            tabs: Mutex::new(HashMap::new()),
            active_tab: Mutex::new(None),
            next_id: std::sync::atomic::AtomicU64::new(1),
        })
    }

    /// Open a new tab navigating to `url`. Returns the new `TabId`.
    pub fn open_tab(&self, url: &str) -> TabId {
        let id = self
            .next_id
            .fetch_add(1, std::sync::atomic::Ordering::Relaxed);
        let tab = Tab::new(id, url);

        if let Ok(mut tabs) = self.tabs.lock() {
            tabs.insert(id, tab);
        }
        if let Ok(mut active) = self.active_tab.lock() {
            *active = Some(id);
        }

        eprintln!("[zawra-tabs] Opened tab #{} → {}", id, url);
        id
    }

    /// Close a tab by ID. Returns `true` if it was found.
    pub fn close_tab(&self, id: TabId) -> bool {
        let removed = self
            .tabs
            .lock()
            .map(|mut t| t.remove(&id).is_some())
            .unwrap_or(false);
        if removed {
            // If we closed the active tab, activate the most recent remaining one
            if let Ok(mut active) = self.active_tab.lock() {
                if *active == Some(id) {
                    *active = self.tabs.lock().ok().and_then(|t| t.keys().next().copied());
                }
            }
            eprintln!("[zawra-tabs] Closed tab #{}", id);
        }
        removed
    }

    /// Switch the active tab to `id`. Returns `false` if not found.
    pub fn switch_to(&self, id: TabId) -> bool {
        let exists = self
            .tabs
            .lock()
            .map(|t| t.contains_key(&id))
            .unwrap_or(false);
        if exists {
            if let Ok(mut active) = self.active_tab.lock() {
                *active = Some(id);
            }
            eprintln!("[zawra-tabs] Switched to tab #{}", id);
        }
        exists
    }

    /// Update the title of a tab (called by WPE's title changed event).
    pub fn set_title(&self, id: TabId, title: &str) {
        if let Ok(mut tabs) = self.tabs.lock() {
            if let Some(tab) = tabs.get_mut(&id) {
                tab.title = title.to_string();
                eprintln!("[zawra-tabs] Tab #{} title: {}", id, title);
            }
        }
    }

    /// Update the URL of a tab (called after navigation / redirect).
    pub fn set_url(&self, id: TabId, url: &str) {
        if let Ok(mut tabs) = self.tabs.lock() {
            if let Some(tab) = tabs.get_mut(&id) {
                tab.url = url.to_string();
            }
        }
    }

    /// Mark a tab as ready (page fully loaded).
    pub fn set_ready(&self, id: TabId) {
        if let Ok(mut tabs) = self.tabs.lock() {
            if let Some(tab) = tabs.get_mut(&id) {
                tab.state = TabState::Ready;
                eprintln!("[zawra-tabs] Tab #{} ready", id);
            }
        }
    }

    pub fn active_tab_id(&self) -> Option<TabId> {
        self.active_tab.lock().ok().and_then(|a| *a)
    }

    pub fn tab_count(&self) -> usize {
        self.tabs.lock().map(|t| t.len()).unwrap_or(0)
    }
}

impl Default for TabManager {
    fn default() -> Self {
        TabManager {
            tabs: Mutex::new(HashMap::new()),
            active_tab: Mutex::new(None),
            next_id: std::sync::atomic::AtomicU64::new(1),
        }
    }
}
