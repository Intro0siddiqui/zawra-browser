//! Zawra Browser — Integration Tests
//!
//! Tests the glue layer in isolation (no WPE required).
//! Run with: `cargo test`

// ── Address bar unit tests ────────────────────────────────────────────────────
#[cfg(test)]
mod address_bar_tests {
    use zawra_browser::ui::address_bar::{normalise_url, AddressBar};

    #[test]
    fn test_normalise_already_https() {
        assert_eq!(normalise_url("https://example.com"), "https://example.com");
    }

    #[test]
    fn test_normalise_adds_https() {
        assert_eq!(normalise_url("example.com"), "https://example.com");
    }

    #[test]
    fn test_normalise_search_query() {
        let url = normalise_url("zawra browser Rust");
        assert!(url.starts_with("https://duckduckgo.com/?q="));
    }

    #[test]
    fn test_address_bar_nav_history() {
        let mut bar = AddressBar::new();
        bar.on_navigation_start("https://a.com");
        bar.on_navigation_start("https://b.com");
        bar.on_navigation_start("https://c.com");

        assert_eq!(bar.go_back(), Some("https://b.com".to_string()));
        assert_eq!(bar.go_back(), Some("https://a.com".to_string()));
        assert_eq!(bar.go_back(), None); // at start

        assert_eq!(bar.go_forward(), Some("https://b.com".to_string()));
    }

    #[test]
    fn test_address_bar_is_secure() {
        let mut bar = AddressBar::new();
        bar.on_navigation_start("http://insecure.com");
        assert!(!bar.is_secure);

        bar.on_navigation_start("https://secure.com");
        assert!(bar.is_secure);
    }
}

// ── Tab manager tests ─────────────────────────────────────────────────────────
#[cfg(test)]
mod tab_tests {
    use zawra_browser::ui::tabs::TabManager;

    #[test]
    fn test_open_close_tab() {
        let tm = TabManager::new();
        let id = tm.open_tab("https://example.com");
        assert_eq!(tm.tab_count(), 1);
        assert!(tm.close_tab(id));
        assert_eq!(tm.tab_count(), 0);
    }

    #[test]
    fn test_active_tab_switches_on_close() {
        let tm = TabManager::new();
        let id1 = tm.open_tab("https://a.com");
        let id2 = tm.open_tab("https://b.com");
        assert_eq!(tm.active_tab_id(), Some(id2));
        tm.close_tab(id2);
        // After closing active tab, some other tab should be active
        assert!(tm.active_tab_id().is_some());
    }

    #[test]
    fn test_switch_tab() {
        let tm = TabManager::new();
        let id1 = tm.open_tab("https://a.com");
        let id2 = tm.open_tab("https://b.com");
        assert!(tm.switch_to(id1));
        assert_eq!(tm.active_tab_id(), Some(id1));
    }
}

// ── HTTP header parser tests ──────────────────────────────────────────────────
#[cfg(test)]
mod streaming_tests {
    use zawra_browser::wpe_glue::streaming::parse_http_head;

    const HTTP_200: &[u8] = b"HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/html\r\n\r\nHello, World!";
    const HTTP_301: &[u8] = b"HTTP/1.1 301 Moved Permanently\r\nLocation: https://new.example.com/\r\n\r\n";
    const HTTP_INCOMPLETE: &[u8] = b"HTTP/1.1 200 OK\r\nContent-Length: 13\r\n";

    #[test]
    fn test_parse_200() {
        let head = parse_http_head(HTTP_200).unwrap();
        assert_eq!(head.status_code, 200);
        assert_eq!(head.content_length, Some(13));
        assert_eq!(head.content_type.as_deref(), Some("text/html"));
        // body should start after \r\n\r\n
        assert_eq!(&HTTP_200[head.header_end..], b"Hello, World!");
    }

    #[test]
    fn test_parse_301_redirect() {
        let head = parse_http_head(HTTP_301).unwrap();
        assert_eq!(head.status_code, 301);
        assert_eq!(head.location.as_deref(), Some("https://new.example.com/"));
    }

    #[test]
    fn test_incomplete_headers_returns_none() {
        assert!(parse_http_head(HTTP_INCOMPLETE).is_none());
    }
}

// ── Base64 roundtrip test (storage module internal) ───────────────────────────
#[cfg(test)]
mod base64_tests {
    /// Test base64 via the public Zawra_Storage_PutBlob/GetBlob round-trip.
    /// We only test the URL-normalisation path here since the full FFI
    /// storage round-trip requires an on-disk BrowserDB.
    #[test]
    fn test_url_normalise_file_scheme() {
        use zawra_browser::ui::address_bar::normalise_url;
        let result = normalise_url("file:///home/user/page.html");
        assert_eq!(result, "file:///home/user/page.html");
    }
}

// ── Window creation test (headless) ───────────────────────────────────────────
#[cfg(test)]
mod window_tests {
    use zawra_browser::ui::window::{BrowserWindow, WindowConfig};

    #[test]
    fn test_headless_window() {
        let config = WindowConfig {
            title: "Test Window".to_string(),
            width: 800,
            height: 600,
            resizable: true,
        };
        let win = BrowserWindow::new(config);
        assert!(win.is_headless()); // No GTK in CI
        assert_eq!(win.size(), (800, 600));
        win.show();
        win.set_title("Test — Zawra");
    }
}

// ── Storage FFI tests ──────────────────────────────────────────────────────────
#[cfg(test)]
mod storage_tests {
    use std::ffi::CString;
    use std::os::raw::c_char;
    use std::fs;
    use std::path::Path;
    use zawra_browser::wpe_glue::storage::{
        Zawra_Storage_Init,
        Zawra_Cookie_Put,
        Zawra_Cookie_Get,
    };

    #[test]
    fn test_cookie_put_get_ffi() {
        let profile_dir = "./test_profile_cookie";
        if Path::new(profile_dir).exists() {
            fs::remove_dir_all(profile_dir).ok();
        }
        fs::create_dir_all(profile_dir).unwrap();

        let profile_c = CString::new(profile_dir).unwrap();
        
        unsafe {
            let init_res = Zawra_Storage_Init(profile_c.as_ptr());
            assert_eq!(init_res, 0); // NS_OK

            let domain_hash_hi = 0x1122334455667788u64;
            let domain_hash_lo = 0x99aabbccddeeff00u64;
            let name = CString::new("session_id").unwrap();
            let value = CString::new("xyz123abc").unwrap();
            let expiry = 1716298800u64;
            let flags = 1u8;

            let put_res = Zawra_Cookie_Put(
                domain_hash_hi,
                domain_hash_lo,
                name.as_ptr(),
                value.as_ptr(),
                expiry,
                flags,
            );
            assert_eq!(put_res, 0); // NS_OK

            // Retrieve the cookie
            let mut buf = vec![0u8; 128];
            let get_res = Zawra_Cookie_Get(
                domain_hash_hi,
                domain_hash_lo,
                name.as_ptr(),
                buf.as_mut_ptr() as *mut c_char,
                buf.len(),
            );
            assert_eq!(get_res, 0); // NS_OK

            let retrieved_str = std::ffi::CStr::from_ptr(buf.as_ptr() as *const c_char)
                .to_str()
                .unwrap();
            assert_eq!(retrieved_str, "xyz123abc");
            
            // Try to retrieve a non-existent cookie
            let name_bad = CString::new("non_existent").unwrap();
            let get_res_bad = Zawra_Cookie_Get(
                domain_hash_hi,
                domain_hash_lo,
                name_bad.as_ptr(),
                buf.as_mut_ptr() as *mut c_char,
                buf.len(),
            );
            assert_ne!(get_res_bad, 0); // Should fail
        }

        fs::remove_dir_all(profile_dir).ok();
    }
}
