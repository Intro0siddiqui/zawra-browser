//! Zawra Subsystem Initialisation
//!
//! Single entry point that WPE calls at startup to initialise all
//! Zawra subsystems: `z-net` (WPE Networking bypass) and `BrowserDB` (storage bypass).
//!
//! # Startup Sequence
//!
//! 1. WPE calls `Zawra_Init_Subsystems(profile_path)`.
//! 2. We open BrowserDB at `<profile_path>/zawra_db/`.
//! 3. We create the global `NetEngine` and start its I/O poll thread.
//! 4. We return NS_OK (0) if both succeed, NS_ERROR_FAILURE otherwise.

use std::ffi::{c_char, CStr, CString};
use std::path::PathBuf;

use crate::wpe_glue::storage::Zawra_Storage_Init;
use crate::wpe_glue::networking::init_net_engine;

const NS_OK:            i32 = 0;
const NS_ERROR_FAILURE: i32 = -2147467259i32;

/// Initialise both the `z-net` engine and `BrowserDB`.
///
/// `profile_path` – NUL-terminated UTF-8 path to the WPE profile directory.
/// Returns `NS_OK` (0) on success, `NS_ERROR_FAILURE` on any error.
///
/// # Safety
/// `profile_path` must be a valid, NUL-terminated UTF-8 string that remains
/// valid for the duration of this call.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Init_Subsystems(profile_path: *const c_char) -> i32 {
    // ── 1. Resolve DB path ──────────────────────────────────────────────────
    let profile_str = if profile_path.is_null() {
        "./zawra_profile".to_string()
    } else {
        match unsafe { CStr::from_ptr(profile_path).to_str() } {
            Ok(s) => s.to_string(),
            Err(_) => return NS_ERROR_FAILURE,
        }
    };

    let db_path: PathBuf = PathBuf::from(&profile_str).join("zawra_db");
    let db_path_str = match db_path.to_str() {
        Some(s) => s.to_string(),
        None => return NS_ERROR_FAILURE,
    };

    // ── 2. Init BrowserDB ───────────────────────────────────────────────────
    let db_path_c = match CString::new(db_path_str) {
        Ok(c) => c,
        Err(_) => return NS_ERROR_FAILURE,
    };
    let db_ret = unsafe { Zawra_Storage_Init(db_path_c.as_ptr()) };
    if db_ret != NS_OK {
        eprintln!("[zawra] BrowserDB init failed with code {}", db_ret);
        return NS_ERROR_FAILURE;
    }
    eprintln!("[zawra] BrowserDB opened at {:?}", db_path_c);

    // ── 3. Init z-net engine ────────────────────────────────────────────────
    if !unsafe { init_net_engine() } {
        eprintln!("[zawra] z-net engine init failed");
        return NS_ERROR_FAILURE;
    }
    eprintln!("[zawra] z-net engine started (poll thread spawned)");
    eprintln!("[zawra] Zawra_Init_Subsystems: all subsystems ready");
    NS_OK
}

/// Shut down all Zawra subsystems gracefully.
///
/// Safe to call even if init was never completed.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Shutdown_Subsystems() {
    eprintln!("[zawra] Shutdown requested — subsystems will be released at process exit");
}
