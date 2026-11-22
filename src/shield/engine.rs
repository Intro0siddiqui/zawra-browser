//! Zawra Shield — Native adblocking and tracking protection engine.
//!
//! Powered by Brave's native `adblock` crate (MPL-2.0). Provides sub-microsecond
//! network request blocking, cosmetic element-hiding CSS injection, per-domain
//! toggles/whitelisting, and live bandwidth/request statistics.

use std::sync::atomic::{AtomicU64, Ordering};
use std::sync::OnceLock;
use dashmap::DashMap;

use adblock::lists::{FilterSet, ParseOptions};
use adblock::request::Request;
use adblock::Engine;

/// Estimated bandwidth saved per blocked ad request (50 KB).
pub const ESTIMATED_BYTES_PER_BLOCKED_REQUEST: u64 = 50 * 1024;

/// Decision made by Zawra Shield for a network request.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum ShieldDecision {
    /// Request is safe and allowed to proceed.
    Allow,
    /// Request was blocked by an adblock filter rule.
    Block { filter: String },
    /// Request should be redirected to an alternate resource or data URI.
    Redirect(String),
}

/// Snapshot of shield operational statistics.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct ShieldStats {
    pub blocked_count: u64,
    pub total_requests: u64,
    pub bytes_saved_estimate: u64,
}

/// Global singleton instance of Zawra Shield.
static GLOBAL_SHIELD: OnceLock<ZawraShield> = OnceLock::new();

/// Built-in default filter rules covering major ad exchanges, trackers, telemetry, and cosmetic hiding.
pub const DEFAULT_FILTER_RULES: &str = r#"
! ==============================================================================
! Zawra Browser Native Shield - Built-in Protection Rules
! ==============================================================================

! --- Major Ad Networks & Tracking Exchanges ---
||doubleclick.net^
||googleads.g.doubleclick.net^
||pagead2.googlesyndication.com^
||googleadservices.com^
||googlesyndication.com^
||adservice.google.com^
||adnxs.com^
||adroll.com^
||ads.yahoo.com^
||criteo.com^
||criteo.net^
||taboola.com^
||outbrain.com^
||rubiconproject.com^
||pubmatic.com^
||openx.net^
||casalemedia.com^
||advertising.com^
||moatads.com^
||amazon-adsystem.com^
||ads.twitter.com^
||ads.linkedin.com^
||bidswitch.net^
||smartadserver.com^
||popads.net^
||propellerads.com^

! --- Telemetry, Analytics & Tracking Beacons ---
||google-analytics.com^
||analytics.google.com^
||googletagmanager.com^
||googletagservices.com^
||stats.g.doubleclick.net^
||pixel.facebook.com^
||connect.facebook.net/*/fbevents.js
||facebook.com/tr/$image
||scorecardresearch.com^
||quantserve.com^
||hotjar.com^
||clarity.ms^
||telemetry.mozilla.org^
||segment.io^
||segment.com/analytics.js
||mixpanel.com^
||amplitude.com^
||browser-intake-datadoghq.com^
||newrelic.com/nr-*.js

! --- Cosmetic Element Hiding Rules ---
##.ad-banner
##.adsbygoogle
###ad-container
###sponsored-ad
##.sponsored-post
##.taboola-ad
##.outbrain-ad
##div[class*="sponsored"]
##div[id*="google_ads"]
##.advertisement
"#;

/// Normalizes a domain name, URL, or host string into a clean lowercase domain.
pub fn normalize_domain(input: &str) -> String {
    let s = input.trim();
    if s.is_empty() {
        return String::new();
    }
    // Strip scheme if present
    let s = if let Some(idx) = s.find("://") {
        &s[idx + 3..]
    } else {
        s
    };
    // Strip path, query, fragment
    let host_part = s.split(&['/', '?', '#'][..]).next().unwrap_or(s);
    // Strip port
    let host = if let Some(colon_pos) = host_part.rfind(':') {
        if host_part.contains(']') {
            host_part
        } else {
            &host_part[..colon_pos]
        }
    } else {
        host_part
    };
    host.trim_matches('.').to_ascii_lowercase()
}

/// The core Zawra Shield protection engine.
pub struct ZawraShield {
    engine: Engine,
    domain_toggles: DashMap<String, bool>,
    pub blocked_count: AtomicU64,
    pub total_requests: AtomicU64,
    pub bytes_saved_estimate: AtomicU64,
}

impl ZawraShield {
    /// Returns the process-wide singleton `ZawraShield` instance.
    pub fn global() -> &'static ZawraShield {
        GLOBAL_SHIELD.get_or_init(Self::new)
    }

    /// Initializes a new `ZawraShield` instance using the default built-in filter rules.
    pub fn new() -> Self {
        Self::new_with_rules(DEFAULT_FILTER_RULES)
    }

    /// Initializes a new `ZawraShield` instance with custom rule text.
    pub fn new_with_rules(rules: &str) -> Self {
        let mut filter_set = FilterSet::new(true); // true = debug mode preserves rule text
        filter_set.add_filter_list(rules.to_string(), ParseOptions::default());
        let engine = Engine::new_with_filter_set(filter_set);

        Self {
            engine,
            domain_toggles: DashMap::new(),
            blocked_count: AtomicU64::new(0),
            total_requests: AtomicU64::new(0),
            bytes_saved_estimate: AtomicU64::new(0),
        }
    }

    /// Check if a network request should be allowed, blocked, or redirected.
    pub fn check_network_request(
        &self,
        url: &str,
        source_url: &str,
        request_type: &str,
    ) -> ShieldDecision {
        self.total_requests.fetch_add(1, Ordering::Relaxed);

        // Check if shield is disabled for the source domain or target URL
        if !source_url.is_empty() && !self.is_enabled_for_domain(source_url) {
            return ShieldDecision::Allow;
        }
        if !self.is_enabled_for_domain(url) {
            return ShieldDecision::Allow;
        }

        // Prepare full URL for adblock request parser
        let full_url = if !url.contains("://") {
            format!("https://{}", url)
        } else {
            url.to_string()
        };

        let full_source = if !source_url.is_empty() && !source_url.contains("://") {
            format!("https://{}", source_url)
        } else {
            source_url.to_string()
        };

        let req_type = if request_type.is_empty() {
            "other"
        } else {
            request_type
        };

        let req = match Request::new(&full_url, &full_source, req_type, "GET") {
            Ok(r) => r,
            Err(_) => return ShieldDecision::Allow,
        };

        let blocker_result = self.engine.check_network_request(&req);

        if blocker_result.should_block() {
            self.blocked_count.fetch_add(1, Ordering::Relaxed);
            self.bytes_saved_estimate
                .fetch_add(ESTIMATED_BYTES_PER_BLOCKED_REQUEST, Ordering::Relaxed);

            if let Some(redirect) = blocker_result.redirect {
                ShieldDecision::Redirect(redirect)
            } else {
                let filter = blocker_result
                    .filter
                    .as_ref()
                    .and_then(|f| f.raw_line.clone())
                    .or_else(|| blocker_result.filter.as_ref().map(|f| f.to_string()))
                    .unwrap_or_else(|| "matched adblock rule".to_string());
                ShieldDecision::Block { filter }
            }
        } else if let Some(redirect) = blocker_result.redirect {
            ShieldDecision::Redirect(redirect)
        } else {
            ShieldDecision::Allow
        }
    }

    /// Enable or disable shielding for a specific domain (or subdomain).
    pub fn set_enabled_for_domain(&self, domain: &str, enabled: bool) {
        let norm = normalize_domain(domain);
        if !norm.is_empty() {
            self.domain_toggles.insert(norm, enabled);
        }
    }

    /// Query whether shielding is active for a domain. Defaults to `true`.
    pub fn is_enabled_for_domain(&self, domain: &str) -> bool {
        let norm = normalize_domain(domain);
        if norm.is_empty() {
            return true;
        }
        // Direct match check
        if let Some(entry) = self.domain_toggles.get(&norm) {
            return *entry;
        }
        // Hierarchical domain check (e.g. sub.domain.com -> domain.com)
        let mut current = norm.as_str();
        while let Some(dot_idx) = current.find('.') {
            let parent = &current[dot_idx + 1..];
            if let Some(entry) = self.domain_toggles.get(parent) {
                return *entry;
            }
            current = parent;
        }
        true
    }

    /// Clear all domain toggles and whitelist entries.
    pub fn clear_domain_toggles(&self) {
        self.domain_toggles.clear();
    }

    /// Returns cosmetic element-hiding CSS rules for the given page URL.
    pub fn get_cosmetic_resources(&self, url: &str) -> Option<String> {
        if !self.is_enabled_for_domain(url) {
            return None;
        }

        let full_url = if !url.contains("://") {
            format!("https://{}", url)
        } else {
            url.to_string()
        };

        let resources = self.engine.url_cosmetic_resources(&full_url);
        if resources.hide_selectors.is_empty() {
            return None;
        }

        let mut selectors: Vec<_> = resources.hide_selectors.into_iter().collect();
        selectors.sort();
        let css = format!("{} {{ display: none !important; }}", selectors.join(", "));
        Some(css)
    }

    /// Returns a snapshot of the live shielding metrics.
    pub fn stats(&self) -> ShieldStats {
        ShieldStats {
            blocked_count: self.blocked_count.load(Ordering::Relaxed),
            total_requests: self.total_requests.load(Ordering::Relaxed),
            bytes_saved_estimate: self.bytes_saved_estimate.load(Ordering::Relaxed),
        }
    }

    /// Number of blocked network requests.
    pub fn blocked_count(&self) -> u64 {
        self.blocked_count.load(Ordering::Relaxed)
    }

    /// Total number of network requests checked.
    pub fn total_requests(&self) -> u64 {
        self.total_requests.load(Ordering::Relaxed)
    }

    /// Estimated network bandwidth saved (bytes).
    pub fn bytes_saved_estimate(&self) -> u64 {
        self.bytes_saved_estimate.load(Ordering::Relaxed)
    }

    /// Reset all live counters back to zero.
    pub fn reset_stats(&self) {
        self.blocked_count.store(0, Ordering::Relaxed);
        self.total_requests.store(0, Ordering::Relaxed);
        self.bytes_saved_estimate.store(0, Ordering::Relaxed);
    }
}

impl Default for ZawraShield {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_block_ad_domains() {
        let shield = ZawraShield::new();

        // DoubleClick ad URL
        let decision = shield.check_network_request(
            "https://googleads.g.doubleclick.net/pagead/ads",
            "https://news.ycombinator.com",
            "script",
        );
        match decision {
            ShieldDecision::Block { filter } => {
                assert!(!filter.is_empty(), "Filter rule description should not be empty");
            }
            other => panic!("Expected DoubleClick ad to be blocked, got {:?}", other),
        }

        // Google Analytics collection endpoint
        let decision = shield.check_network_request(
            "https://analytics.google.com/collect",
            "https://example.com",
            "ping",
        );
        match decision {
            ShieldDecision::Block { filter } => {
                assert!(!filter.is_empty(), "Filter rule description should not be empty");
            }
            other => panic!("Expected Google Analytics to be blocked, got {:?}", other),
        }

        // Facebook tracking pixel
        let decision = shield.check_network_request(
            "https://pixel.facebook.com/tr/?id=123456",
            "https://shopping.com",
            "image",
        );
        assert!(matches!(decision, ShieldDecision::Block { .. }));

        // Criteo ad tracker
        let decision = shield.check_network_request(
            "https://static.criteo.net/js/ld/ld.js",
            "https://shopping.com",
            "script",
        );
        assert!(matches!(decision, ShieldDecision::Block { .. }));
    }

    #[test]
    fn test_allow_standard_content() {
        let shield = ZawraShield::new();

        // Wikipedia Zig page
        let decision = shield.check_network_request(
            "https://wikipedia.org/wiki/Zig",
            "",
            "document",
        );
        assert_eq!(decision, ShieldDecision::Allow);

        // GitHub main page
        let decision = shield.check_network_request(
            "https://github.com",
            "",
            "document",
        );
        assert_eq!(decision, ShieldDecision::Allow);

        // Rust-lang official site
        let decision = shield.check_network_request(
            "https://www.rust-lang.org/learn",
            "",
            "document",
        );
        assert_eq!(decision, ShieldDecision::Allow);
    }

    #[test]
    fn test_whitelist_exemption() {
        let shield = ZawraShield::new();

        let ad_url = "https://googleads.g.doubleclick.net/pagead/ads";

        // Initially blocked
        let initial = shield.check_network_request(ad_url, "", "script");
        assert!(matches!(initial, ShieldDecision::Block { .. }));

        // Disable shielding for parent domain
        shield.set_enabled_for_domain("doubleclick.net", false);
        assert!(!shield.is_enabled_for_domain("doubleclick.net"));
        assert!(!shield.is_enabled_for_domain("googleads.g.doubleclick.net"));

        // Now request is allowed due to whitelist exemption
        let after_whitelist = shield.check_network_request(ad_url, "", "script");
        assert_eq!(after_whitelist, ShieldDecision::Allow);

        // Re-enable shielding
        shield.set_enabled_for_domain("doubleclick.net", true);
        assert!(shield.is_enabled_for_domain("doubleclick.net"));

        let after_reenable = shield.check_network_request(ad_url, "", "script");
        assert!(matches!(after_reenable, ShieldDecision::Block { .. }));

        // Whitelist by source URL
        shield.set_enabled_for_domain("trustedsite.com", false);
        let from_trusted = shield.check_network_request(
            ad_url,
            "https://trustedsite.com/article",
            "script",
        );
        assert_eq!(from_trusted, ShieldDecision::Allow);
    }

    #[test]
    fn test_cosmetic_rule_generation() {
        let custom_rules = r#"
! Specific site cosmetic rules
example.com##.sponsor-box
example.com###ad-banner
##div[class*="sponsored"]
"#;
        let shield = ZawraShield::new_with_rules(custom_rules);

        let css = shield
            .get_cosmetic_resources("https://example.com")
            .expect("Should generate CSS for example.com");

        assert!(css.contains("display: none !important;"));
        assert!(css.contains(".sponsor-box"));
        assert!(css.contains("#ad-banner"));

        // If domain is whitelisted, no cosmetic rules should be injected
        shield.set_enabled_for_domain("example.com", false);
        assert_eq!(shield.get_cosmetic_resources("https://example.com"), None);
    }

    #[test]
    fn test_statistics_tracking() {
        let shield = ZawraShield::new();
        shield.reset_stats();

        assert_eq!(shield.total_requests(), 0);
        assert_eq!(shield.blocked_count(), 0);
        assert_eq!(shield.bytes_saved_estimate(), 0);

        // 1 allowed request
        shield.check_network_request("https://wikipedia.org/wiki/Zig", "", "document");
        assert_eq!(shield.total_requests(), 1);
        assert_eq!(shield.blocked_count(), 0);
        assert_eq!(shield.bytes_saved_estimate(), 0);

        // 1 blocked request
        shield.check_network_request(
            "https://googleads.g.doubleclick.net/pagead/ads",
            "https://example.com",
            "script",
        );
        assert_eq!(shield.total_requests(), 2);
        assert_eq!(shield.blocked_count(), 1);
        assert_eq!(shield.bytes_saved_estimate(), ESTIMATED_BYTES_PER_BLOCKED_REQUEST);

        let stats = shield.stats();
        assert_eq!(stats.total_requests, 2);
        assert_eq!(stats.blocked_count, 1);
        assert_eq!(stats.bytes_saved_estimate, ESTIMATED_BYTES_PER_BLOCKED_REQUEST);
    }

    #[test]
    fn test_global_singleton() {
        let shield = ZawraShield::global();
        let decision = shield.check_network_request(
            "https://analytics.google.com/collect",
            "",
            "ping",
        );
        assert!(matches!(decision, ShieldDecision::Block { .. }));
    }
}
