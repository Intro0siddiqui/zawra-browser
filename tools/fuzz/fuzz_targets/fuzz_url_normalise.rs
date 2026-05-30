#![no_main]
use libfuzzer_sys::fuzz_target;
use zawra_browser::ui::address_bar::normalise_url;

/// Fuzz the URL normalisation function.
///
/// Goals:
/// - Must never panic on any UTF-8 input.
/// - Output must always start with a valid scheme.
fuzz_target!(|data: &[u8]| {
    // Only test valid UTF-8 — URLs are always text
    if let Ok(s) = std::str::from_utf8(data) {
        let result = normalise_url(s);
        // Invariant: result must always have a scheme
        assert!(
            result.starts_with("http://")  ||
            result.starts_with("https://") ||
            result.starts_with("file://")  ||
            result.starts_with("zawra://"),
            "normalise_url returned invalid scheme for input {:?}: {:?}",
            s, result
        );
    }
});
