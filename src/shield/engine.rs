//! Zawra Sieve — Native adblocking, scriptlet injection, and tracking protection engine.
//!
//! Powered by Brave's native `adblock` crate (MPL-2.0). Provides sub-microsecond
//! network request blocking, cosmetic element-hiding CSS injection, `document_start`
//! scriptlet injection (`json-prune`, `set-constant`, `abort-on-property-read`, `noopjs`),
//! per-domain toggles/whitelisting, external filter-list/resource loading from
//! `$XDG_DATA_HOME/zawra/filters/` (or `~/.local/share/zawra/filters/`), and C-ABI FFI
//! exports (`Zawra_Sieve_*`) for UIProcess (Zig/WPE) and WPENetworkProcess (C++).

use std::collections::HashMap;
use std::ffi::{c_char, CStr, CString};
use std::fs;
use std::path::{Path, PathBuf};
use std::ptr;
use std::sync::atomic::{AtomicU64, Ordering};
use std::sync::OnceLock;

use adblock::cosmetic_filter_cache::UrlSpecificResources;
use adblock::lists::{FilterSet, ParseOptions};
use adblock::request::Request;
use adblock::resources::{MimeType, PermissionMask, Resource, ResourceType};
use adblock::Engine;
use base64::engine::general_purpose::STANDARD as BASE64_STANDARD;
use base64::Engine as _;
use dashmap::DashMap;

/// Estimated bandwidth saved per blocked ad request (50 KB).
pub const ESTIMATED_BYTES_PER_BLOCKED_REQUEST: u64 = 50 * 1024;

/// Decision made by Zawra Sieve for a network request.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum ShieldDecision {
    /// Request is safe and allowed to proceed.
    Allow,
    /// Request was blocked by an adblock filter rule.
    Block { filter: String },
    /// Request should be redirected to an alternate resource or data URI.
    Redirect(String),
}

/// Snapshot of Zawra Sieve operational statistics.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct ShieldStats {
    pub blocked_count: u64,
    pub total_requests: u64,
    pub bytes_saved_estimate: u64,
}

/// Cosmetic element-hiding CSS and `document_start` scriptlet payload for a page URL.
#[derive(Debug, Clone, PartialEq, Eq, Default)]
pub struct CosmeticResources {
    /// Combined CSS rules (`selector1, selector2 { display: none !important; }`) if any.
    pub css: Option<String>,
    /// JavaScript scriptlet payload to inject at `document_start`, if any.
    pub injected_script: Option<String>,
}

/// Alias branding the native adblock engine as `ZawraSieve` while preserving `ZawraShield`.
pub type ZawraSieve = ZawraShield;

/// Global singleton instance of Zawra Sieve.
static GLOBAL_SHIELD: OnceLock<ZawraShield> = OnceLock::new();

/// Built-in default filter rules covering major ad exchanges, trackers, telemetry,
/// YouTube ad endpoints, YouTube `json-prune` / `set-constant` scriptlets, and cosmetic hiding.
pub const DEFAULT_FILTER_RULES: &str = r#"
! ==============================================================================
! Zawra Sieve - Built-in Native Protection Rules
! ==============================================================================

! --- Major Ad Networks & Tracking Exchanges ---
||doubleclick.net^
||googleads.g.doubleclick.net^
||googleads.g.doubleclick.net/pagead/id$xhr,redirect=nooptext
||ad.doubleclick.net^
||static.doubleclick.net^
||static.doubleclick.net/instream/ad_status.js^$script,xhr,redirect=doubleclick_instream_ad_status.js
||pagead2.googlesyndication.com^
||googleadservices.com^
||googlesyndication.com^
||adservice.google.com^
||s0.2mdn.net^
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

! --- YouTube Network Ad Endpoints ---
||youtube.com/pagead/
||youtube.com/api/stats/ads
||youtube.com/api/stats/qoe?*adformat=
||youtube.com/ptracking
||youtube.com/get_midroll_info
||youtube.com/youtubei/v1/player/ad_break
||youtube.com/youtubei/v1/log_event
! Preserve core video stream delivery
@@||googlevideo.com/videoplayback

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

! --- YouTube Scriptlets (document_start) ---
youtube.com##+js(json-prune, adPlacements playerAds adSlots auxiliaryUi.messageRenderers.enforcementMessageViewModel playerResponse.adPlacements playerResponse.playerAds playerResponse.adSlots playerResponse.auxiliaryUi.messageRenderers.enforcementMessageViewModel)
youtube.com##+js(set-constant, google_ad_status, 1)
youtube.com##+js(set-constant, Object.prototype.adBlocksFound, 0)
youtube.com##+js(set-constant, Object.prototype.hasAllowedInstreamAd, true)
youtube.com##+js(set-constant, yt.config_.openPopupConfig.supportedPopups.adBlockMessageViewModel, false)
youtube.com##+js(set-constant, ytInitialPlayerResponse.adPlacements, undefined)
youtube.com##+js(set-constant, ytInitialPlayerResponse.playerAds, undefined)
youtube.com##+js(set-constant, ytInitialPlayerResponse.adSlots, undefined)
youtube.com##+js(set-constant, playerResponse.adPlacements, undefined)
youtube.com##+js(set-constant, ytInitialPlayerResponse.auxiliaryUi.messageRenderers.enforcementMessageViewModel, undefined)

! --- YouTube Cosmetic Ad Containers ---
youtube.com##ytd-enforcement-message-view-model
youtube.com##tp-yt-paper-dialog:has(ytd-enforcement-message-view-model)
youtube.com##.video-ads
youtube.com##.ytp-ad-module
youtube.com##.ytp-ad-overlay-container
youtube.com##.ytp-ad-player-overlay
youtube.com##.ytp-ad-progress-list
youtube.com##ytd-ad-slot-renderer
youtube.com##ytd-banner-promo-renderer
youtube.com##ytd-companion-slot-renderer
youtube.com##ytd-display-ad-renderer
youtube.com##ytd-in-feed-ad-layout-renderer
youtube.com##ytd-promoted-sparkles-web-renderer
youtube.com##ytd-promoted-video-renderer
youtube.com###player-ads
youtube.com###masthead-ad

! --- Generic Cosmetic Element Hiding Rules ---
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

/// Built-in `json-prune` scriptlet implementation (hooks `JSON.parse` and `Response.prototype.json`).
const SCRIPTLET_JSON_PRUNE: &str = r#"function jsonPrune(rawPrunePaths = '', rawNeedlePaths = '') {
    /* json-prune */
    if (!rawPrunePaths) { return; }
    const prunePaths = rawPrunePaths.split(/ +/).map(p => p.split('.')).filter(p => p.length > 0);
    const needlePaths = rawNeedlePaths ? rawNeedlePaths.split(/ +/).map(p => p.split('.')).filter(p => p.length > 0) : [];
    const hasPath = (obj, path) => {
        let cur = obj;
        for (let i = 0; i < path.length; i++) {
            if (cur === null || typeof cur !== 'object' || !(path[i] in cur)) { return false; }
            cur = cur[path[i]];
        }
        return true;
    };
    const deletePath = (obj, path) => {
        if (obj === null || typeof obj !== 'object') { return; }
        let cur = obj;
        for (let i = 0; i < path.length - 1; i++) {
            const key = path[i];
            if (cur === null || typeof cur !== 'object') { return; }
            if (key === '[]' && Array.isArray(cur)) {
                const rest = path.slice(i + 1);
                for (let j = 0; j < cur.length; j++) { deletePath(cur[j], rest); }
                return;
            }
            if (!(key in cur)) { return; }
            cur = cur[key];
        }
        const last = path[path.length - 1];
        if (cur !== null && typeof cur === 'object' && last in cur) {
            delete cur[last];
        }
    };
    const pruneObject = (root) => {
        if (root === null || typeof root !== 'object') { return root; }
        if (needlePaths.length > 0 && !needlePaths.every(np => hasPath(root, np))) {
            return root;
        }
        for (let i = 0; i < prunePaths.length; i++) {
            deletePath(root, prunePaths[i]);
        }
        return root;
    };
    const origParse = JSON.parse;
    JSON.parse = function(...args) {
        const result = origParse.apply(this, args);
        try { return pruneObject(result); } catch (_) { return result; }
    };
    if (typeof Response !== 'undefined' && Response.prototype && Response.prototype.json) {
        const origJson = Response.prototype.json;
        Response.prototype.json = function(...args) {
            return origJson.apply(this, args).then(data => {
                try { return pruneObject(data); } catch (_) { return data; }
            });
        };
    }
    if (typeof Response !== 'undefined' && Response.prototype && Response.prototype.text) {
        const origText = Response.prototype.text;
        Response.prototype.text = function(...args) {
            return origText.apply(this, args).then(txt => {
                if (typeof txt !== 'string' || txt.length < 2 || (txt[0] !== '{' && txt[0] !== '[')) {
                    return txt;
                }
                if (txt.indexOf('adPlacements') === -1 && txt.indexOf('playerAds') === -1 && txt.indexOf('adSlots') === -1 && txt.indexOf('enforcementMessageViewModel') === -1) {
                    return txt;
                }
                try {
                    const parsed = origParse(txt);
                    pruneObject(parsed);
                    return JSON.stringify(parsed);
                } catch (_) {
                    return txt;
                }
            });
        };
    }
    if (typeof XMLHttpRequest !== 'undefined' && XMLHttpRequest.prototype) {
        const respDesc = Object.getOwnPropertyDescriptor(XMLHttpRequest.prototype, 'responseText');
        if (respDesc && respDesc.get) {
            const origGet = respDesc.get;
            Object.defineProperty(XMLHttpRequest.prototype, 'responseText', {
                configurable: true,
                get() {
                    const txt = origGet.call(this);
                    if (typeof txt !== 'string' || txt.length < 2 || (txt[0] !== '{' && txt[0] !== '[')) {
                        return txt;
                    }
                    if (txt.indexOf('adPlacements') === -1 && txt.indexOf('playerAds') === -1 && txt.indexOf('adSlots') === -1 && txt.indexOf('enforcementMessageViewModel') === -1) {
                        return txt;
                    }
                    try {
                        const parsed = origParse(txt);
                        pruneObject(parsed);
                        return JSON.stringify(parsed);
                    } catch (_) {
                        return txt;
                    }
                }
            });
        }
    }
}"#;

/// Built-in `set-constant` scriptlet implementation.
const SCRIPTLET_SET_CONSTANT: &str = r#"function setConstant(chain = '', cValue = '') {
    /* set-constant */
    if (!chain) { return; }
    let val;
    if (cValue === 'undefined') { val = undefined; }
    else if (cValue === 'false') { val = false; }
    else if (cValue === 'true') { val = true; }
    else if (cValue === 'null') { val = null; }
    else if (cValue === "''" || cValue === '') { val = ''; }
    else if (cValue === 'noopFunc') { val = function() {}; }
    else if (cValue === 'trueFunc') { val = function() { return true; }; }
    else if (cValue === 'falseFunc') { val = function() { return false; }; }
    else if (cValue === 'emptyObj') { val = {}; }
    else if (cValue === 'emptyArr') { val = []; }
    else if (/^-?\d+(\.\d+)?$/.test(cValue)) { val = Number(cValue); }
    else { val = cValue; }

    const parts = chain.split('.');
    const applyOn = (owner, idx) => {
        if (owner === null || (typeof owner !== 'object' && typeof owner !== 'function')) { return; }
        const prop = parts[idx];
        if (idx === parts.length - 1) {
            try {
                Object.defineProperty(owner, prop, {
                    configurable: true,
                    get() { return val; },
                    set() {}
                });
            } catch (_) {}
            return;
        }
        let current = owner[prop];
        if (current !== undefined && current !== null) {
            applyOn(current, idx + 1);
        } else {
            try {
                const prevDesc = Object.getOwnPropertyDescriptor(owner, prop);
                const hooks = (prevDesc && prevDesc.get && prevDesc.get.__zawraHooks) ? prevDesc.get.__zawraHooks : [];
                hooks.push((v) => {
                    if (v !== null && (typeof v === 'object' || typeof v === 'function')) {
                        applyOn(v, idx + 1);
                    }
                });
                if (!prevDesc || !prevDesc.get || !prevDesc.get.__zawraHooks) {
                    let stored = current;
                    const getter = function() { return stored; };
                    getter.__zawraHooks = hooks;
                    Object.defineProperty(owner, prop, {
                        configurable: true,
                        get: getter,
                        set(v) {
                            stored = v;
                            for (let i = 0; i < hooks.length; i++) {
                                hooks[i](v);
                            }
                        }
                    });
                }
            } catch (_) {}
        }
    };
    applyOn(window, 0);
}"#;

/// Built-in `abort-on-property-read` scriptlet implementation.
const SCRIPTLET_ABORT_ON_PROPERTY_READ: &str = r#"function abortOnPropertyRead(chain = '') {
    /* abort-on-property-read */
    if (!chain) { return; }
    const magic = 'zawraSieveAbort_' + Math.random().toString(36).slice(2);
    const abort = () => { throw new ReferenceError(magic); };
    const parts = chain.split('.');
    const trap = (owner, idx) => {
        if (owner === null || (typeof owner !== 'object' && typeof owner !== 'function')) { return; }
        const prop = parts[idx];
        if (idx === parts.length - 1) {
            try {
                Object.defineProperty(owner, prop, {
                    configurable: true,
                    get: abort,
                    set() {}
                });
            } catch (_) {}
            return;
        }
        let current = owner[prop];
        if (current !== undefined && current !== null) {
            trap(current, idx + 1);
        } else {
            try {
                Object.defineProperty(owner, prop, {
                    configurable: true,
                    get() { return current; },
                    set(v) {
                        current = v;
                        if (v !== null && (typeof v === 'object' || typeof v === 'function')) {
                            trap(v, idx + 1);
                        }
                    }
                });
            } catch (_) {}
        }
    };
    trap(window, 0);
}"#;

/// Built-in `noopjs` redirect and scriptlet resource.
const SCRIPTLET_NOOPJS: &str = "/* noopjs */\n(function() {})();";

/// Built-in `doubleclick_instream_ad_status.js` redirect resource (prevents YouTube anti-adblock error).
const REDIRECT_DOUBLECLICK_AD_STATUS: &str = "window.google_ad_status = 1;\n";

/// Returns the built-in scriptlet and redirect resources bundled with Zawra Sieve.
pub fn builtin_resources() -> Vec<Resource> {
    vec![
        Resource {
            name: "doubleclick_instream_ad_status.js".to_string(),
            aliases: vec!["doubleclick-instream-ad-status.js".to_string()],
            kind: ResourceType::Mime(MimeType::ApplicationJavascript),
            content: BASE64_STANDARD.encode(REDIRECT_DOUBLECLICK_AD_STATUS),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
        Resource {
            name: "nooptext".to_string(),
            aliases: vec!["noop.txt".to_string()],
            kind: ResourceType::Mime(MimeType::TextPlain),
            content: BASE64_STANDARD.encode(""),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
        Resource {
            name: "json-prune.js".to_string(),
            aliases: vec!["json-prune".to_string()],
            kind: ResourceType::Mime(MimeType::ApplicationJavascript),
            content: BASE64_STANDARD.encode(SCRIPTLET_JSON_PRUNE),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
        Resource {
            name: "set-constant.js".to_string(),
            aliases: vec!["set-constant".to_string(), "set.js".to_string()],
            kind: ResourceType::Mime(MimeType::ApplicationJavascript),
            content: BASE64_STANDARD.encode(SCRIPTLET_SET_CONSTANT),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
        Resource {
            name: "abort-on-property-read.js".to_string(),
            aliases: vec![
                "abort-on-property-read".to_string(),
                "aopr.js".to_string(),
            ],
            kind: ResourceType::Mime(MimeType::ApplicationJavascript),
            content: BASE64_STANDARD.encode(SCRIPTLET_ABORT_ON_PROPERTY_READ),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
        Resource {
            name: "noopjs.js".to_string(),
            aliases: vec!["noopjs".to_string(), "noop.js".to_string()],
            kind: ResourceType::Mime(MimeType::ApplicationJavascript),
            content: BASE64_STANDARD.encode(SCRIPTLET_NOOPJS),
            dependencies: vec![],
            permission: PermissionMask::default(),
        },
    ]
}

/// Resolves the user filter directory: `$XDG_DATA_HOME/zawra/filters` if `XDG_DATA_HOME`
/// is set and non-empty, otherwise `~/.local/share/zawra/filters`.
pub fn resolve_filters_dir() -> Option<PathBuf> {
    if let Ok(xdg) = std::env::var("XDG_DATA_HOME") {
        let trimmed = xdg.trim();
        if !trimmed.is_empty() {
            return Some(PathBuf::from(trimmed).join("zawra").join("filters"));
        }
    }
    dirs::home_dir().map(|home| home.join(".local").join("share").join("zawra").join("filters"))
}

/// Loads user `.txt` / `.list` filter files and optional `resources.json` from `filters_dir`.
fn load_external_filters_and_resources(
    filters_dir: &Path,
    filter_set: &mut FilterSet,
    resources: &mut Vec<Resource>,
) {
    if !filters_dir.is_dir() {
        return;
    }

    // Load user filter lists (*.txt, *.list) in deterministic sorted order.
    if let Ok(entries) = fs::read_dir(filters_dir) {
        let mut filter_paths: Vec<PathBuf> = entries
            .flatten()
            .map(|e| e.path())
            .filter(|p| {
                p.is_file()
                    && matches!(
                        p.extension().and_then(|ext| ext.to_str()),
                        Some("txt" | "list")
                    )
            })
            .collect();
        filter_paths.sort();

        for path in filter_paths {
            if let Ok(content) = fs::read_to_string(&path) {
                filter_set.add_filter_list(content, ParseOptions::default());
            }
        }
    }

    // Load optional user resources.json and merge over built-ins by canonical name.
    let resources_json = filters_dir.join("resources.json");
    if resources_json.is_file() {
        if let Ok(raw) = fs::read_to_string(&resources_json) {
            if let Ok(external_resources) = serde_json::from_str::<Vec<Resource>>(&raw) {
                let mut by_name: HashMap<String, Resource> = resources
                    .drain(..)
                    .map(|r| (r.name.clone(), r))
                    .collect();
                for res in external_resources {
                    by_name.insert(res.name.clone(), res);
                }
                *resources = by_name.into_values().collect();
            }
        }
    }
}

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

/// The core Zawra Sieve protection engine (exported as both `ZawraShield` and `ZawraSieve`).
pub struct ZawraShield {
    engine: Engine,
    domain_toggles: DashMap<String, bool>,
    pub blocked_count: AtomicU64,
    pub total_requests: AtomicU64,
    pub bytes_saved_estimate: AtomicU64,
}

impl ZawraShield {
    /// Returns the process-wide singleton `ZawraSieve` / `ZawraShield` instance.
    pub fn global() -> &'static ZawraShield {
        GLOBAL_SHIELD.get_or_init(Self::new)
    }

    /// Initializes a new `ZawraSieve` instance using the built-in default rules & scriptlets,
    /// augmented with any user filter lists (`*.txt`, `*.list`) and `resources.json` found in
    /// `$XDG_DATA_HOME/zawra/filters/` (or `~/.local/share/zawra/filters/`).
    pub fn new() -> Self {
        let mut filter_set = FilterSet::new(true);
        filter_set.add_filter_list(DEFAULT_FILTER_RULES.to_string(), ParseOptions::default());

        let mut resources = builtin_resources();
        if let Some(dir) = resolve_filters_dir() {
            load_external_filters_and_resources(&dir, &mut filter_set, &mut resources);
        }

        let mut engine = Engine::new_with_filter_set(filter_set);
        engine.use_resources(resources);

        Self {
            engine,
            domain_toggles: DashMap::new(),
            blocked_count: AtomicU64::new(0),
            total_requests: AtomicU64::new(0),
            bytes_saved_estimate: AtomicU64::new(0),
        }
    }

    /// Initializes a new `ZawraSieve` instance from a specific filters directory (for testing
    /// or isolated profiles), layered on top of `DEFAULT_FILTER_RULES` and `builtin_resources()`.
    pub fn new_with_filters_dir(filters_dir: &Path) -> Self {
        let mut filter_set = FilterSet::new(true);
        filter_set.add_filter_list(DEFAULT_FILTER_RULES.to_string(), ParseOptions::default());

        let mut resources = builtin_resources();
        load_external_filters_and_resources(filters_dir, &mut filter_set, &mut resources);

        let mut engine = Engine::new_with_filter_set(filter_set);
        engine.use_resources(resources);

        Self {
            engine,
            domain_toggles: DashMap::new(),
            blocked_count: AtomicU64::new(0),
            total_requests: AtomicU64::new(0),
            bytes_saved_estimate: AtomicU64::new(0),
        }
    }

    /// Initializes a new `ZawraSieve` instance with custom rule text and built-in scriptlets.
    pub fn new_with_rules(rules: &str) -> Self {
        let mut filter_set = FilterSet::new(true); // true = debug mode preserves rule text
        filter_set.add_filter_list(rules.to_string(), ParseOptions::default());
        let mut engine = Engine::new_with_filter_set(filter_set);
        engine.use_resources(builtin_resources());

        Self {
            engine,
            domain_toggles: DashMap::new(),
            blocked_count: AtomicU64::new(0),
            total_requests: AtomicU64::new(0),
            bytes_saved_estimate: AtomicU64::new(0),
        }
    }

    /// Check if a network request should be allowed, blocked, or redirected (defaults to `"GET"`).
    pub fn check_network_request(
        &self,
        url: &str,
        source_url: &str,
        request_type: &str,
    ) -> ShieldDecision {
        self.check_network_request_with_method(url, source_url, request_type, "GET")
    }

    /// Check if a network request should be allowed, blocked, or redirected using the real
    /// `http_method`, `source_url`, and `request_type`.
    pub fn check_network_request_with_method(
        &self,
        url: &str,
        source_url: &str,
        request_type: &str,
        http_method: &str,
    ) -> ShieldDecision {
        self.total_requests.fetch_add(1, Ordering::Relaxed);

        // Check if sieve is disabled for the source domain or target URL
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

        let method = if http_method.trim().is_empty() {
            "GET"
        } else {
            http_method.trim()
        };

        let req = match Request::new(&full_url, &full_source, req_type, method) {
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

    /// Enable or disable Zawra Sieve for a specific domain (or subdomain).
    pub fn set_enabled_for_domain(&self, domain: &str, enabled: bool) {
        let norm = normalize_domain(domain);
        if !norm.is_empty() {
            self.domain_toggles.insert(norm, enabled);
        }
    }

    /// Query whether Zawra Sieve is active for a domain. Defaults to `true`.
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

    /// Returns raw `adblock::cosmetic_filter_cache::UrlSpecificResources` for a page URL,
    /// respecting per-domain toggles.
    pub fn url_cosmetic_resources(&self, url: &str) -> UrlSpecificResources {
        if !self.is_enabled_for_domain(url) {
            return UrlSpecificResources::empty();
        }

        let full_url = if !url.contains("://") {
            format!("https://{}", url)
        } else {
            url.to_string()
        };

        self.engine.url_cosmetic_resources(&full_url)
    }

    /// Returns BOTH cosmetic element-hiding CSS (`hide_selectors`) AND scriptlet JS
    /// (`injected_script`) for the given page URL.
    pub fn get_cosmetic_resources(&self, url: &str) -> CosmeticResources {
        if !self.is_enabled_for_domain(url) {
            return CosmeticResources::default();
        }

        let resources = self.url_cosmetic_resources(url);

        let css = if resources.hide_selectors.is_empty() {
            None
        } else {
            let mut selectors: Vec<_> = resources.hide_selectors.into_iter().collect();
            selectors.sort();
            Some(format!("{} {{ display: none !important; }}", selectors.join(", ")))
        };

        let injected_script = if resources.injected_script.trim().is_empty() {
            None
        } else {
            Some(resources.injected_script)
        };

        CosmeticResources {
            css,
            injected_script,
        }
    }

    /// Convenience helper returning only cosmetic element-hiding CSS for `url`.
    pub fn get_cosmetic_css(&self, url: &str) -> Option<String> {
        self.get_cosmetic_resources(url).css
    }

    /// Convenience helper returning only the `document_start` injected scriptlet JS for `url`.
    pub fn get_injected_script(&self, url: &str) -> Option<String> {
        self.get_cosmetic_resources(url).injected_script
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

// ============================================================================
// Zawra Sieve C-ABI FFI Exports
// ============================================================================

/// Helper to safely decode an optional C string pointer into a Rust `&str`.
///
/// # Safety
/// If `ptr` is non-null, it must point to a valid, NUL-terminated C string.
unsafe fn cstr_to_str<'a>(ptr: *const c_char) -> Option<&'a str> {
    if ptr.is_null() {
        return None;
    }
    unsafe { CStr::from_ptr(ptr) }.to_str().ok()
}

/// Returns a heap-allocated, NUL-terminated CSS stylesheet string for hiding ad elements on `url`,
/// or `NULL` if `url` is null/invalid or no cosmetic selectors apply.
///
/// # Ownership
/// Any non-null pointer returned by this function is owned by the caller and MUST be released
/// via `Zawra_Sieve_FreeString`.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Sieve_GetCosmeticCss(url: *const c_char) -> *mut c_char {
    let Some(url_str) = (unsafe { cstr_to_str(url) }) else {
        return ptr::null_mut();
    };
    if url_str.is_empty() {
        return ptr::null_mut();
    }
    match ZawraSieve::global().get_cosmetic_css(url_str) {
        Some(css) => CString::new(css).map_or(ptr::null_mut(), CString::into_raw),
        None => ptr::null_mut(),
    }
}

/// Returns a heap-allocated, NUL-terminated JavaScript scriptlet string to inject at
/// `document_start` for `url`, or `NULL` if `url` is null/invalid or no scriptlets apply.
///
/// # Ownership
/// Any non-null pointer returned by this function is owned by the caller and MUST be released
/// via `Zawra_Sieve_FreeString`.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Sieve_GetInjectedScript(url: *const c_char) -> *mut c_char {
    let Some(url_str) = (unsafe { cstr_to_str(url) }) else {
        return ptr::null_mut();
    };
    if url_str.is_empty() {
        return ptr::null_mut();
    }
    match ZawraSieve::global().get_injected_script(url_str) {
        Some(js) => CString::new(js).map_or(ptr::null_mut(), CString::into_raw),
        None => ptr::null_mut(),
    }
}

/// Evaluates whether a network request should be allowed, blocked, or redirected.
///
/// - `url`: target request URL (required; if null/invalid, returns `0` = Allow).
/// - `source_url`: first-party/document URL (optional; null treated as `""`).
/// - `request_type`: resource type such as `"script"`, `"image"`, `"xmlhttprequest"`,
///   `"document"`, `"other"` (optional; null treated as `"other"`).
/// - `http_method`: HTTP verb such as `"GET"`, `"POST"` (optional; null treated as `"GET"`).
///
/// # Return values
/// - `0`: Allow
/// - `1`: Block
/// - `2`: Redirect
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Sieve_CheckRequest(
    url: *const c_char,
    source_url: *const c_char,
    request_type: *const c_char,
    http_method: *const c_char,
) -> i32 {
    let Some(url_str) = (unsafe { cstr_to_str(url) }) else {
        return 0;
    };
    if url_str.is_empty() {
        return 0;
    }
    let source_str = unsafe { cstr_to_str(source_url) }.unwrap_or("");
    let type_str = unsafe { cstr_to_str(request_type) }.unwrap_or("other");
    let method_str = unsafe { cstr_to_str(http_method) }.unwrap_or("GET");

    match ZawraSieve::global().check_network_request_with_method(
        url_str,
        source_str,
        type_str,
        method_str,
    ) {
        ShieldDecision::Allow => 0,
        ShieldDecision::Block { .. } => 1,
        ShieldDecision::Redirect(_) => 2,
    }
}

/// Evaluates a request and, if it resolves to a `ShieldDecision::Redirect(data_url)`,
/// returns a heap-allocated NUL-terminated string formatted as `"<mime>\n<body>"`.
/// Returns `NULL` otherwise. Caller MUST free non-null pointers via `Zawra_Sieve_FreeString`.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Sieve_GetRedirectPayload(
    url: *const c_char,
    source_url: *const c_char,
    request_type: *const c_char,
    http_method: *const c_char,
) -> *mut c_char {
    let Some(url_str) = (unsafe { cstr_to_str(url) }) else {
        return ptr::null_mut();
    };
    if url_str.is_empty() {
        return ptr::null_mut();
    }
    let source_str = unsafe { cstr_to_str(source_url) }.unwrap_or("");
    let type_str = unsafe { cstr_to_str(request_type) }.unwrap_or("other");
    let method_str = unsafe { cstr_to_str(http_method) }.unwrap_or("GET");

    let ShieldDecision::Redirect(data_url) = ZawraSieve::global().check_network_request_with_method(
        url_str,
        source_str,
        type_str,
        method_str,
    ) else {
        return ptr::null_mut();
    };

    let Some(rest) = data_url.strip_prefix("data:") else {
        return ptr::null_mut();
    };
    let Some((meta, encoded)) = rest.split_once(',') else {
        return ptr::null_mut();
    };
    let mime = meta.strip_suffix(";base64").unwrap_or(meta);
    let mime = if mime.is_empty() { "text/plain" } else { mime };
    let decoded = if meta.ends_with(";base64") {
        match BASE64_STANDARD.decode(encoded) {
            Ok(bytes) => String::from_utf8_lossy(&bytes).into_owned(),
            Err(_) => return ptr::null_mut(),
        }
    } else {
        encoded.to_string()
    };

    let payload = format!("{mime}\n{decoded}");
    CString::new(payload).map_or(ptr::null_mut(), CString::into_raw)
}

/// Frees a C string previously returned by `Zawra_Sieve_GetCosmeticCss` or
/// `Zawra_Sieve_GetInjectedScript`.
///
/// # Safety
/// Passing `NULL` is a safe no-op. Any non-null pointer MUST have been allocated by a
/// `Zawra_Sieve_Get*` function and MUST NOT be freed more than once.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Sieve_FreeString(ptr: *mut c_char) {
    if ptr.is_null() {
        return;
    }
    unsafe {
        drop(CString::from_raw(ptr));
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
    fn test_youtube_network_ad_blocking_and_playback_allowed() {
        let sieve = ZawraSieve::new();
        let yt_watch = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

        // YouTube ad endpoints must be blocked (with real HTTP methods)
        let blocked_urls = [
            ("https://www.youtube.com/pagead/adview?ai=123", "xmlhttprequest", "GET"),
            ("https://www.youtube.com/api/stats/ads?ad_id=1", "ping", "POST"),
            ("https://www.youtube.com/ptracking?pltype=adhost", "xmlhttprequest", "GET"),
            ("https://googleads.g.doubleclick.net/pagead/viewthroughconversion/123/", "script", "GET"),
            ("https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js", "script", "GET"),
        ];
        for (url, req_type, method) in blocked_urls {
            let decision = sieve.check_network_request_with_method(url, yt_watch, req_type, method);
            assert!(
                matches!(decision, ShieldDecision::Block { .. }),
                "Expected YouTube ad URL `{}` ({} {}) to be blocked, got {:?}",
                url,
                method,
                req_type,
                decision
            );
        }

        // Core YouTube watch page and googlevideo.com stream chunks must be allowed
        assert_eq!(
            sieve.check_network_request_with_method(yt_watch, "", "document", "GET"),
            ShieldDecision::Allow
        );
        assert_eq!(
            sieve.check_network_request_with_method(
                "https://rr1---sn-4g5e6nsz.googlevideo.com/videoplayback?expire=1700000000&itag=248",
                yt_watch,
                "media",
                "GET"
            ),
            ShieldDecision::Allow
        );
    }

    #[test]
    fn test_youtube_cosmetic_and_scriptlet_resources() {
        let sieve = ZawraSieve::new();
        let yt_watch = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

        let raw = sieve.url_cosmetic_resources(yt_watch);
        assert!(
            !raw.injected_script.is_empty(),
            "Expected non-empty injected_script for YouTube watch URL"
        );
        assert!(
            raw.injected_script.contains("json-prune"),
            "Expected injected_script to contain json-prune"
        );
        assert!(
            raw.injected_script.contains("adPlacements"),
            "Expected injected_script to prune adPlacements"
        );
        assert!(
            !raw.hide_selectors.is_empty(),
            "Expected non-empty cosmetic hide_selectors for YouTube watch URL"
        );

        let cosmetic = sieve.get_cosmetic_resources(yt_watch);
        let css = cosmetic.css.expect("Expected cosmetic CSS for YouTube");
        assert!(css.contains("display: none !important;"));
        assert!(css.contains("ytd-ad-slot-renderer") || css.contains(".ytp-ad-module"));

        let js = cosmetic
            .injected_script
            .expect("Expected injected_script in get_cosmetic_resources for YouTube");
        assert!(js.contains("json-prune"));
        assert!(js.contains("adPlacements"));
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

        let cosmetic = shield.get_cosmetic_resources("https://example.com");
        let css = cosmetic
            .css
            .expect("Should generate CSS for example.com");

        assert!(css.contains("display: none !important;"));
        assert!(css.contains(".sponsor-box"));
        assert!(css.contains("#ad-banner"));

        // If domain is whitelisted, no cosmetic rules or scripts should be injected
        shield.set_enabled_for_domain("example.com", false);
        assert_eq!(
            shield.get_cosmetic_resources("https://example.com"),
            CosmeticResources::default()
        );
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
    fn test_ffi_roundtrip_and_null_safety() {
        // Null safety checks
        assert!(Zawra_Sieve_GetCosmeticCss(ptr::null()).is_null());
        assert!(Zawra_Sieve_GetInjectedScript(ptr::null()).is_null());
        assert_eq!(
            Zawra_Sieve_CheckRequest(ptr::null(), ptr::null(), ptr::null(), ptr::null()),
            0
        );
        // Freeing null must be a safe no-op
        Zawra_Sieve_FreeString(ptr::null_mut());

        // Valid YouTube watch URL: CSS + injected script round-trip
        let yt_url = CString::new("https://www.youtube.com/watch?v=dQw4w9WgXcQ").unwrap();

        let css_ptr = Zawra_Sieve_GetCosmeticCss(yt_url.as_ptr());
        assert!(!css_ptr.is_null(), "Expected non-null CSS pointer for YouTube");
        let css_str = unsafe { CStr::from_ptr(css_ptr) }.to_str().unwrap();
        assert!(css_str.contains("display: none !important;"));
        Zawra_Sieve_FreeString(css_ptr);

        let js_ptr = Zawra_Sieve_GetInjectedScript(yt_url.as_ptr());
        assert!(!js_ptr.is_null(), "Expected non-null injected script pointer for YouTube");
        let js_str = unsafe { CStr::from_ptr(js_ptr) }.to_str().unwrap();
        assert!(js_str.contains("json-prune"));
        assert!(js_str.contains("adPlacements"));
        Zawra_Sieve_FreeString(js_ptr);

        // Network request check via FFI (ad blocked, videoplayback allowed)
        let ad_url = CString::new("https://www.youtube.com/pagead/adview?ai=1").unwrap();
        let req_type = CString::new("xmlhttprequest").unwrap();
        let method = CString::new("GET").unwrap();
        assert_eq!(
            Zawra_Sieve_CheckRequest(
                ad_url.as_ptr(),
                yt_url.as_ptr(),
                req_type.as_ptr(),
                method.as_ptr()
            ),
            1
        );

        let video_url = CString::new("https://rr1---sn-abc.googlevideo.com/videoplayback?itag=248").unwrap();
        let media_type = CString::new("media").unwrap();
        assert_eq!(
            Zawra_Sieve_CheckRequest(
                video_url.as_ptr(),
                yt_url.as_ptr(),
                media_type.as_ptr(),
                method.as_ptr()
            ),
            0
        );
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
