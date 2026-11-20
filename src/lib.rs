// Zawra Browser (2026 Edition)
//
// Architecture:
//   - wpe_glue:   Integration layer that replaces WPE's networking and
//                 storage with z-net and BrowserDB respectively.
//   - ui:         Browser window, tab manager, address bar, renderer embed.
//   - lean_net:   z-net Rust network engine (zero-copy BodyRing I/O)
//   - browserdb:  LSM-tree storage engine (history, cache, cookies, blobs)

/// WPE integration glue — networking bypass (z-net) + storage bypass (BrowserDB)
pub mod wpe_glue;

/// Browser UI — window, tabs, address bar, renderer embedding
pub mod ui;

// Expose the real engines at crate root for direct use by other modules
pub use browserdb;
pub use lean_net;

// JavaScriptCore zero-copy ArrayBuffer bridge (jsc_glue)
pub mod zero_copy;


