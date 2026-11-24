//! Zawra Browser — Subsystem Initialization & Process Launcher
//!
//! Responsibilities:
//!  1. Locate WPE binaries and libraries (`WEBKIT_EXEC_PATH`, `WEBKIT_INJECTED_BUNDLE_PATH`, `ZAWRA_WPE_LIB_PATH`).
//!  2. Call `Zawra_Init_Subsystems(profile_path)` — boots z-net + BrowserDB.
//!  3. Call `Zawra_Register_Protocols()` — overrides WPE's networking handlers.
//!  4. Spawn sandboxed child compartments via `hajr`.
//!  5. Perform graceful subsystem shutdown on exit.

use std::ffi::{c_char, c_int, CString};
use std::path::PathBuf;

const NS_OK: i32 = 0;
const NS_ERROR_FAILURE: i32 = -0x7fff_ffff; // 0x80004005

unsafe extern "C" {
    fn Z_Init_Subsystems(profile_path: *const c_char) -> i32;
    fn Z_Register_Protocols() -> i32;
    fn Z_Shutdown_Subsystems();
    fn hajr_spawn_compartment(
        path: *const c_char,
        argv: *const *const c_char,
        out_socket: *mut c_int,
    ) -> c_int;
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Path Resolution
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn resolve_profile_dir() -> PathBuf {
    if let Ok(p) = std::env::var("ZAWRA_PROFILE") {
        let path = PathBuf::from(p);
        std::fs::create_dir_all(&path).ok();
        return path;
    }

    if let Some(mut home) = dirs::home_dir() {
        home.push(".zawra");
        home.push("profile");
        std::fs::create_dir_all(&home).ok();
        return home;
    }

    let fallback = PathBuf::from("./zawra_profile");
    std::fs::create_dir_all(&fallback).ok();
    fallback
}

/// Search relative to binary and known project locations for WPE libraries and binaries.
pub fn resolve_wpe_environment() -> Option<PathBuf> {
    const WPE_LIB_NAME: &str = "libWPEWebKit-2.0.so";

    // 1. Check environment overrides first
    if let Ok(env_path) = std::env::var("WPE_PATH") {
        let p = PathBuf::from(&env_path);
        if p.is_file() {
            unsafe { std::env::set_var("ZAWRA_WPE_LIB_PATH", p.to_string_lossy().as_ref()); }
            return Some(p);
        } else if p.is_dir() {
            let candidate = p.join(WPE_LIB_NAME);
            if candidate.is_file() {
                unsafe { std::env::set_var("ZAWRA_WPE_LIB_PATH", candidate.to_string_lossy().as_ref()); }
                return Some(candidate);
            }
        }
    }

    // 2. Discover relative to current executable
    if let Ok(exe_path) = std::env::current_exe() {
        let mut curr = exe_path.parent();
        while let Some(dir) = curr {
            let candidate_lib = dir.join("webkit/build/lib").join(WPE_LIB_NAME);
            if candidate_lib.is_file() {
                let candidate_bin = dir.join("webkit/build/bin");
                if candidate_bin.join("WPEWebProcess").is_file() {
                    unsafe {
                        std::env::set_var("WEBKIT_EXEC_PATH", candidate_bin.to_string_lossy().as_ref());
                        std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir.join("webkit/build/lib").to_string_lossy().as_ref());
                        std::env::set_var("ZAWRA_WPE_LIB_PATH", candidate_lib.to_string_lossy().as_ref());
                    }
                }
                return Some(candidate_lib);
            }

            let candidate_lib2 = dir.join("lib").join(WPE_LIB_NAME);
            if candidate_lib2.is_file() {
                let candidate_bin2 = dir.join("bin");
                if candidate_bin2.join("WPEWebProcess").is_file() {
                    unsafe {
                        std::env::set_var("WEBKIT_EXEC_PATH", candidate_bin2.to_string_lossy().as_ref());
                        std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir.join("lib").to_string_lossy().as_ref());
                        std::env::set_var("ZAWRA_WPE_LIB_PATH", candidate_lib2.to_string_lossy().as_ref());
                    }
                }
                return Some(candidate_lib2);
            }

            curr = dir.parent();
        }
    }

    // 3. Fallback known workspace locations
    let fallback_paths = [
        "/home/intro/spectre-enviroment/browser/zawra-browser/webkit/build/lib/libWPEWebKit-2.0.so",
        "/home/intro/spectre-enviroment/browser/zawra-browser-znet-e2e/webkit/build/lib/libWPEWebKit-2.0.so",
        "/usr/lib/x86_64-linux-gnu/libWPEWebKit-2.0.so",
        "/usr/lib64/libWPEWebKit-2.0.so",
        "/usr/lib/libWPEWebKit-2.0.so",
    ];

    for path_str in &fallback_paths {
        let p = PathBuf::from(path_str);
        if p.is_file() {
            if let Some(parent) = p.parent() {
                let bin_dir = parent.parent().map(|p| p.join("bin"));
                if let Some(b) = bin_dir {
                    if b.join("WPEWebProcess").is_file() {
                        unsafe {
                            if std::env::var_os("WEBKIT_EXEC_PATH").is_none() {
                                std::env::set_var("WEBKIT_EXEC_PATH", b.to_string_lossy().as_ref());
                            }
                            if std::env::var_os("WEBKIT_INJECTED_BUNDLE_PATH").is_none() {
                                std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", parent.to_string_lossy().as_ref());
                            }
                        }
                    }
                }
            }
            unsafe {
                std::env::set_var("ZAWRA_WPE_LIB_PATH", p.to_string_lossy().as_ref());
            }
            return Some(p);
        }
    }

    None
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Subsystem Lifecycle & Process Compartment Glue
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Initialise Zawra subsystems (z-net + BrowserDB).
pub fn bootstrap_zawra(profile_path: &str) -> bool {
    let profile_c = match CString::new(profile_path) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("[zawra-launcher] Invalid profile path: {}", e);
            return false;
        }
    };

    let ret = unsafe { Z_Init_Subsystems(profile_c.as_ptr()) };
    if ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Init_Subsystems failed: {:#010x}", ret as u32);
        return false;
    }

    let proto_ret = unsafe { Z_Register_Protocols() };
    if proto_ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Register_Protocols non-zero: {:#010x}", proto_ret as u32);
    }

    true
}

/// Hajr-powered process launcher.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_SpawnProcess(
    path: *const c_char,
    argv: *const *const c_char,
    out_socket: *mut c_int,
) -> c_int {
    if path.is_null() || argv.is_null() {
        return -1;
    }
    unsafe { hajr_spawn_compartment(path, argv, out_socket) }
}

/// Exported C-ABI bootstrap function.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Bootstrap(profile_path: *const c_char) -> i32 {
    let profile_str = if profile_path.is_null() {
        resolve_profile_dir().to_string_lossy().into_owned()
    } else {
        match unsafe { std::ffi::CStr::from_ptr(profile_path).to_str() } {
            Ok(s) => s.to_string(),
            Err(_) => resolve_profile_dir().to_string_lossy().into_owned(),
        }
    };

    if bootstrap_zawra(&profile_str) { NS_OK } else { NS_ERROR_FAILURE }
}

/// Perform a graceful shutdown.
#[unsafe(no_mangle)]
pub extern "C" fn Z_ProcessShutdown() {
    unsafe { Z_Shutdown_Subsystems() };
    eprintln!("[zawra-launcher] Process shutdown complete");
}
