//! Zawra Address Bar
//!
//! URL input widget + navigation controls (back, forward, reload, stop).
//! Parses user input, normalises URLs, and initiates navigation via
//! the WPE content process.

/// Navigation action requested by the user.
#[derive(Debug, Clone, PartialEq)]
pub enum NavAction {
    Navigate(String), // Load a URL
    Back,
    Forward,
    Reload,
    Stop,
    NewTab,
    CloseTab,
}

/// State of the address bar.
#[derive(Debug, Clone)]
pub struct AddressBar {
    pub current_url:    String,
    pub input_text:     String,
    pub is_secure:      bool,    // true → show 🔒
    pub is_loading:     bool,
    pub can_go_back:    bool,
    pub can_go_forward: bool,
    history_back:       Vec<String>,
    history_forward:    Vec<String>,
}

impl AddressBar {
    pub fn new() -> Self {
        AddressBar {
            current_url:    String::new(),
            input_text:     String::new(),
            is_secure:      false,
            is_loading:     false,
            can_go_back:    false,
            can_go_forward: false,
            history_back:   Vec::new(),
            history_forward: Vec::new(),
        }
    }

    /// Called when the user presses Enter in the address bar.
    /// Returns the `NavAction` to execute.
    pub fn commit_input(&mut self) -> NavAction {
        let raw = self.input_text.trim().to_string();
        let url = normalise_url(&raw);
        self.input_text = url.clone();
        NavAction::Navigate(url)
    }

    /// Called by WPE when navigation to a new URL starts.
    pub fn on_navigation_start(&mut self, url: &str) {
        if !self.current_url.is_empty() {
            self.history_back.push(self.current_url.clone());
            self.history_forward.clear();
        }
        self.current_url   = url.to_string();
        self.input_text    = url.to_string();
        self.is_loading    = true;
        self.is_secure     = url.starts_with("https://");
        self.can_go_back   = !self.history_back.is_empty();
        self.can_go_forward = false;
        eprintln!("[zawra-addr] → {}", url);
    }

    /// Called when the page finishes loading.
    pub fn on_page_loaded(&mut self) {
        self.is_loading = false;
        eprintln!("[zawra-addr] ✓ {}", self.current_url);
    }

    /// Execute a back navigation. Returns the URL to load, or None if at start.
    pub fn go_back(&mut self) -> Option<String> {
        if let Some(prev) = self.history_back.pop() {
            self.history_forward.push(self.current_url.clone());
            self.current_url   = prev.clone();
            self.input_text    = prev.clone();
            self.can_go_back   = !self.history_back.is_empty();
            self.can_go_forward = true;
            Some(prev)
        } else {
            None
        }
    }

    /// Execute a forward navigation.
    pub fn go_forward(&mut self) -> Option<String> {
        if let Some(next) = self.history_forward.pop() {
            self.history_back.push(self.current_url.clone());
            self.current_url   = next.clone();
            self.input_text    = next.clone();
            self.can_go_back   = true;
            self.can_go_forward = !self.history_forward.is_empty();
            Some(next)
        } else {
            None
        }
    }
}

impl Default for AddressBar {
    fn default() -> Self { Self::new() }
}

/// Normalise user-typed text into a valid URL.
///
/// Rules:
/// - If it looks like a URL (contains `.` and no spaces, or starts with a
///   scheme) → prepend `https://` if no scheme present.
/// - Otherwise → treat as a search query and format as a DuckDuckGo URL.
pub fn normalise_url(input: &str) -> String {
    let trimmed = input.trim();

    // Already has a scheme
    if trimmed.starts_with("http://")
        || trimmed.starts_with("https://")
        || trimmed.starts_with("file://")
        || trimmed.starts_with("zawra://")
    {
        return trimmed.to_string();
    }

    // Looks like a hostname (no spaces, has a dot)
    if !trimmed.contains(' ') && trimmed.contains('.') {
        return format!("https://{}", trimmed);
    }

    // Search query
    let encoded: String = trimmed
        .chars()
        .map(|c| match c {
            'A'..='Z' | 'a'..='z' | '0'..='9' | '-' | '_' | '.' | '~' => c.to_string(),
            ' ' => "+".to_string(),
            _ => format!("%{:02X}", c as u32),
        })
        .collect();

    format!("https://duckduckgo.com/?q={}", encoded)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_normalise_url_scheme_passthrough() {
        assert_eq!(normalise_url("https://example.com"), "https://example.com");
        assert_eq!(normalise_url("http://example.com"), "http://example.com");
    }

    #[test]
    fn test_normalise_url_adds_https() {
        assert_eq!(normalise_url("example.com"), "https://example.com");
        assert_eq!(normalise_url("github.com/rust-lang"), "https://github.com/rust-lang");
    }

    #[test]
    fn test_normalise_url_search_query() {
        let result = normalise_url("what is zawra browser");
        assert!(result.starts_with("https://duckduckgo.com/?q="));
        assert!(result.contains("zawra"));
    }

    #[test]
    fn test_address_bar_back_forward() {
        let mut bar = AddressBar::new();
        bar.on_navigation_start("https://a.com");
        bar.on_navigation_start("https://b.com");
        assert_eq!(bar.go_back(), Some("https://a.com".to_string()));
        assert_eq!(bar.go_forward(), Some("https://b.com".to_string()));
    }
}
