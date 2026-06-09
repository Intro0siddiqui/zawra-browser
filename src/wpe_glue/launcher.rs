//! Zawra Browser — WPE Launcher & Process Bootstrap
//!
//! Orchestrates the full startup sequence:
//!
//!  1.  Detect and `dlopen` WPE libraries at runtime.
//!  2.  Call `Zawra_Init_Subsystems(profile_path)` — boots z-net + BrowserDB.
//!  3.  Call `Zawra_Register_Protocols()` — overrides WPE's networking handlers.
//!  4.  Invoke WPE's own entry point.
//!
//! When WPE is not available (CI / headless mode), we still boot z-net and
//! BrowserDB and expose a diagnostic HTTP server so the network stack can be
//! tested in isolation.

use std::ffi::{c_char, c_int, c_void, CString};
use std::path::PathBuf;
use std::ptr::null_mut;

// ── nsresult ─────────────────────────────────────────────────────────────────
const NS_OK:              i32 = 0;
const NS_ERROR_FAILURE:   i32 = -2147467259i32;

// ── C-ABI declarations from our glue layer ────────────────────────────────────
unsafe extern "C" {
    fn Zawra_Init_Subsystems(profile_path: *const c_char) -> i32;
    fn Zawra_Register_Protocols() -> i32;
    fn Zawra_Shutdown_Subsystems();
}

// ── WPE function types (resolved via dlopen at runtime) ────────────────

/// Signature of WPE's entry point.
type WpeMainFn = unsafe extern "C" fn(argc: c_int, argv: *mut *mut c_char, app_data: *const c_void) -> c_int;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Dynamic linker wrapper
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

struct DynLib {
    handle: *mut c_void,
}

impl DynLib {
    /// Open a shared library by path. Returns `None` if the file doesn't exist
    /// or `dlopen` fails.
    fn open(path: &str) -> Option<Self> {
        let path_c = CString::new(path).ok()?;
        let handle = unsafe {
            libc::dlopen(path_c.as_ptr(), libc::RTLD_LAZY | libc::RTLD_GLOBAL)
        };
        if handle.is_null() {
            let err = unsafe { std::ffi::CStr::from_ptr(libc::dlerror()) };
            eprintln!("[zawra-launcher] dlopen({}) failed: {:?}", path, err);
            None
        } else {
            Some(DynLib { handle })
        }
    }

    /// Resolve a symbol by name. Returns `None` if not found.
    unsafe fn sym<T: Copy>(&self, name: &str) -> Option<T> {
        let name_c = CString::new(name).ok()?;
        let ptr = unsafe { libc::dlsym(self.handle, name_c.as_ptr()) };
        if ptr.is_null() { None } else { Some(unsafe { *(ptr as *const T) }) }
    }
}

impl Drop for DynLib {
    fn drop(&mut self) {
        if !self.handle.is_null() {
            unsafe { libc::dlclose(self.handle) };
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Profile directory resolution
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Returns the Zawra profile directory, creating it if needed.
/// Priority: `$ZAWRA_PROFILE` env var → `~/.zawra/profile` → `./zawra_profile`
fn resolve_profile_dir() -> PathBuf {
    if let Ok(p) = std::env::var("ZAWRA_PROFILE") {
        let path = PathBuf::from(p);
        std::fs::create_dir_all(&path).ok();
        return path;
    }

    if let Some(mut home) = dirs::home_dir() {
        home.push(".zawra");
        home.push("profile");
        if std::fs::create_dir_all(&home).is_ok() {
            return home;
        }
    }

    let fallback = PathBuf::from("./zawra_profile");
    std::fs::create_dir_all(&fallback).ok();
    fallback
}

/// Search common locations for WPE libraries, return the directory path.
fn find_wpe_lib() -> Option<PathBuf> {
    let candidates = [
        "/usr/lib/wpe-webkit-1.0/libWPEBackend-fdo.so",
        "/usr/lib64/wpe-webkit-1.0/libWPEBackend-fdo.so",
        "/usr/lib/x86_64-linux-gnu/libWPEBackend-fdo.so",
        "/usr/local/lib/libWPEBackend-fdo.so",
    ];
    candidates.iter().find_map(|c| {
        if std::path::Path::new(c).exists() { Some(PathBuf::from(c)) } else { None }
    })
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Zawra process bootstrap
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Initialise Zawra subsystems (z-net + BrowserDB).
/// Returns `true` on success.
pub fn bootstrap_zawra(profile_path: &str) -> bool {
    let profile_c = match CString::new(profile_path) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("[zawra-launcher] Invalid profile path: {}", e);
            return false;
        }
    };

    let ret = unsafe { Zawra_Init_Subsystems(profile_c.as_ptr()) };
    if ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Init_Subsystems failed: {:#010x}", ret as u32);
        return false;
    }

    let proto_ret = unsafe { Zawra_Register_Protocols() };
    if proto_ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Register_Protocols failed: {:#010x}", proto_ret as u32);
        // Non-fatal — WPE will fall back to default networking for now
    }

    true
}

/// Launch WPE via its entry point. Returns exit code.
///
/// If WPE library is not found, logs a warning and returns 0 (headless mode).
pub fn launch_wpe(profile_path: &str) -> i32 {
    let wpe_path = match find_wpe_lib() {
        Some(p) => p,
        None => {
            eprintln!("[zawra-launcher] WPE library not found — running in headless mode");
            eprintln!("[zawra-launcher] Install WPE or set WPE_PATH to enable WPE");
            return 0;
        }
    };

    let lib = match DynLib::open(wpe_path.to_str().unwrap_or("")) {
        Some(l) => l,
        None => {
            eprintln!("[zawra-launcher] Failed to dlopen {}", wpe_path.display());
            return NS_ERROR_FAILURE;
        }
    };

    // Resolve wpe_main or equivalent
    let wpe_main: WpeMainFn = match unsafe { lib.sym("wpe_main") } {
        Some(f) => f,
        None => {
            eprintln!("[zawra-launcher] wpe_main not found — using placeholder");
            return 0;
        }
    };

    eprintln!("[zawra-launcher] WPE found at {} — launching", wpe_path.display());

    // Build argc/argv to pass to WPE (mirrors what firefox-bin does)
    let profile_flag = CString::new("--profile").unwrap();
    let profile_val  = CString::new(profile_path).unwrap();
    let mut argv: Vec<*mut c_char> = vec![
        CString::new("zawra-browser").unwrap().into_raw(),
        profile_flag.into_raw(),
        profile_val.into_raw(),
        null_mut(),
    ];

    let exit_code = unsafe { wpe_main(3, argv.as_mut_ptr(), null_mut()) };
    exit_code
}

/// Exported C-ABI bootstrap function — called by embedding code or tests.
///
/// # Safety
/// `profile_path` must be a valid NUL-terminated string or NULL (uses default).
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Bootstrap(profile_path: *const c_char) -> i32 {
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
pub extern "C" fn Zawra_ProcessShutdown() {
    unsafe { Zawra_Shutdown_Subsystems() };
    eprintln!("[zawra-launcher] Process shutdown complete");
}

unsafe extern "C" {
    fn hajr_spawn_compartment(
        path: *const c_char,
        argv: *const *const c_char,
        out_socket: *mut c_int,
    ) -> c_int;
}

/// Hajr-powered process launcher.
/// Replaces GLib's GSubprocessLauncher to break the GLib dependency.
///
/// # Safety
/// `path` and `argv` must be valid NUL-terminated strings.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Hajr_SpawnProcess(
    path: *const c_char,
    argv: *const *const c_char,
    out_socket: *mut c_int,
) -> c_int {
    if path.is_null() || argv.is_null() {
        return -1;
    }
    unsafe { hajr_spawn_compartment(path, argv, out_socket) }
}
