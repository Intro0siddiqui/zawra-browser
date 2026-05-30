#![no_main]
use libfuzzer_sys::fuzz_target;
use zawra_browser::wpe_glue::streaming::parse_http_head;

/// Fuzz the HTTP/1.1 response header parser.
///
/// Goals:
/// - Must never panic on any input.
/// - Must never return garbage offsets (header_end > input length).
fuzz_target!(|data: &[u8]| {
    if let Some(head) = parse_http_head(data) {
        // Invariant: header_end must be within the input slice
        assert!(head.header_end <= data.len(), "header_end out of bounds");
        // Invariant: status code must be in HTTP range
        assert!(head.status_code >= 100 && head.status_code < 600,
                "status_code {} out of HTTP range", head.status_code);
        // Invariant: content_length must be non-negative if present
        if let Some(cl) = head.content_length {
            assert!(cl < usize::MAX / 2, "suspicious content_length");
        }
    }
    // None is always valid — just means headers not complete
});
