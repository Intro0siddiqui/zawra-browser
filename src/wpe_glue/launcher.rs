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
    fn Z_Init_Subsystems(profile_path: *const c_char) -> i32;
    fn Z_Register_Protocols() -> i32;
    fn Z_Shutdown_Subsystems();
}

// ── WPE function types (resolved via dlopen at runtime) ────────────────

/// Signature of WPE's entry point.
type WpeMainFn = unsafe extern "C" fn(argc: c_int, argv: *mut *mut c_char, appData: *const c_void) -> c_int;

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
/// Priority: `$ZAWRA_PROFILE` env var → `$ZAWRA_ANDROID_DATA_DIR` (Android) → `~/.zawra/profile` (Desktop) → `./zawra_profile`
fn resolve_profile_dir() -> PathBuf {
    if let Ok(p) = std::env::var("ZAWRA_PROFILE") {
        let path = PathBuf::from(p);
        std::fs::create_dir_all(&path).ok();
        return path;
    }

    if let Ok(p) = std::env::var("ZAWRA_ANDROID_DATA_DIR") {
        let path = PathBuf::from(p).join("profile");
        std::fs::create_dir_all(&path).ok();
        return path;
    }

    #[cfg(target_os = "android")]
    {
        let app_dir = PathBuf::from("/data/data/com.zawra.browser/files/profile");
        if std::fs::create_dir_all(&app_dir).is_ok() {
            return app_dir;
        }
        let fallback = PathBuf::from("/data/local/tmp/zawra_profile");
        std::fs::create_dir_all(&fallback).ok();
        return fallback;
    }

    #[cfg(not(target_os = "android"))]
    {
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
}

/// Search common locations for WPE libraries, returning the path to the library.
/// Checks WPE_PATH, WEBKIT_EXEC_PATH, relative ../../webkit/build/lib/, and system paths.
fn find_wpe_lib() -> Option<PathBuf> {
    #[cfg(target_os = "macos")]
    const WPE_LIB_NAMES: &[&str] = &[
        "libWPEBackend-fdo.dylib",
        "libWPEBackend-fdo-1.0.dylib",
        "libWPEBackend-fdo.so",
        "libWPEWebKit-2.0.dylib",
        "libWPEWebKit-2.0.so",
        "libWPEWebKit-1.0.dylib",
        "libWPEWebKit-1.0.so",
    ];

    #[cfg(not(target_os = "macos"))]
    const WPE_LIB_NAMES: &[&str] = &[
        "libWPEBackend-fdo.so",
        "libWPEWebKit-2.0.so",
        "libWPEWebKit-1.0.so",
    ];

    // 1. Check WPE_PATH environment variable
    if let Ok(wpe_env) = std::env::var("WPE_PATH") {
        let path = PathBuf::from(&wpe_env);
        if path.is_file() {
            return Some(path);
        } else if path.is_dir() {
            for name in WPE_LIB_NAMES {
                let candidate = path.join(name);
                if candidate.is_file() {
                    return Some(candidate);
                }
            }
        }
    }

    // 2. Check WEBKIT_EXEC_PATH environment variable
    if let Ok(exec_env) = std::env::var("WEBKIT_EXEC_PATH") {
        let path = PathBuf::from(&exec_env);
        if path.is_file() {
            return Some(path);
        } else if path.is_dir() {
            for name in WPE_LIB_NAMES {
                let candidate = path.join(name);
                if candidate.is_file() {
                    return Some(candidate);
                }
            }
            let lib_dir = path.join("lib");
            if lib_dir.is_dir() {
                for name in WPE_LIB_NAMES {
                    let candidate = lib_dir.join(name);
                    if candidate.is_file() {
                        return Some(candidate);
                    }
                }
            }
        }
    }

    // 3. Check relative ../../webkit/build/lib/ and local build locations
    let relative_candidates = [
        "../../webkit/build/lib/libWPEBackend-fdo.dylib",
        "../../webkit/build/lib/libWPEWebKit-2.0.dylib",
        "../../webkit/build/lib/libWPEBackend-fdo.so",
        "../../webkit/build/lib/libWPEWebKit-2.0.so",
        "webkit/build/lib/libWPEBackend-fdo.dylib",
        "webkit/build/lib/libWPEWebKit-2.0.dylib",
        "webkit/build/lib/libWPEBackend-fdo.so",
        "webkit/build/lib/libWPEWebKit-2.0.so",
        "../zawra-browser/webkit/build/lib/libWPEBackend-fdo.dylib",
        "../zawra-browser/webkit/build/lib/libWPEWebKit-2.0.dylib",
        "../zawra-browser/webkit/build/lib/libWPEBackend-fdo.so",
        "../zawra-browser/webkit/build/lib/libWPEWebKit-2.0.so",
    ];
    for c in &relative_candidates {
        let p = PathBuf::from(c);
        if p.is_file() {
            return Some(p);
        }
    }

    // 4. Android native library search paths
    let android_candidates = [
        std::env::var("ZAWRA_NATIVE_LIB_DIR").ok().map(PathBuf::from),
        Some(PathBuf::from("/data/data/com.zawra.browser/lib")),
        Some(PathBuf::from("/data/local/tmp")),
    ];
    for maybe_dir in &android_candidates {
        if let Some(dir) = maybe_dir {
            if dir.is_dir() {
                for name in WPE_LIB_NAMES {
                    let candidate = dir.join(name);
                    if candidate.is_file() {
                        return Some(candidate);
                    }
                }
            }
        }
    }

    // 5. Fallback to standard system paths (Desktop Linux & macOS)
    #[cfg(target_os = "macos")]
    {
        let macos_candidates = [
            "/opt/homebrew/lib/libWPEBackend-fdo.dylib",
            "/opt/homebrew/lib/libWPEWebKit-2.0.dylib",
            "/usr/local/lib/libWPEBackend-fdo.dylib",
            "/usr/local/lib/libWPEWebKit-2.0.dylib",
            "/opt/homebrew/lib/libWPEBackend-fdo.so",
            "/opt/homebrew/lib/libWPEWebKit-2.0.so",
        ];
        for c in &macos_candidates {
            let p = PathBuf::from(c);
            if p.is_file() {
                return Some(p);
            }
        }
    }

    #[cfg(not(any(target_os = "android", target_os = "macos")))]
    {
        let system_candidates = [
            "/usr/lib/wpe-webkit-1.0/libWPEBackend-fdo.so",
            "/usr/lib64/wpe-webkit-1.0/libWPEBackend-fdo.so",
            "/usr/lib/x86_64-linux-gnu/libWPEBackend-fdo.so",
            "/usr/local/lib/libWPEBackend-fdo.so",
            "/usr/lib/x86_64-linux-gnu/libWPEWebKit-2.0.so",
            "/usr/lib64/libWPEWebKit-2.0.so",
            "/usr/lib/libWPEWebKit-2.0.so",
        ];
        for c in &system_candidates {
            let p = PathBuf::from(c);
            if p.is_file() {
                return Some(p);
            }
        }
    }

    None
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

    let ret = unsafe { Z_Init_Subsystems(profile_c.as_ptr()) };
    if ret != NS_OK {
        eprintln!("[zawra-launcher] Zawra_Init_Subsystems failed: {:#010x}", ret as u32);
        return false;
    }

    let proto_ret = unsafe { Z_Register_Protocols() };
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

    let path_str = match wpe_path.to_str() {
        Some(s) => s,
        None => {
            eprintln!("[zawra-launcher] WPE path is not valid UTF-8: {}", wpe_path.display());
            return NS_ERROR_FAILURE;
        }
    };

    let lib = match DynLib::open(path_str) {
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
    let profile_flag = match CString::new("--profile") {
        Ok(s) => s,
        Err(e) => {
            eprintln!("[zawra-launcher] Failed to create --profile CString: {}", e);
            return -1;
        }
    };
    let profile_val = match CString::new(profile_path) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("[zawra-launcher] Invalid profile_path with interior NUL: {}", e);
            return -1;
        }
    };
    let prog_name = match CString::new("zawra-browser") {
        Ok(s) => s,
        Err(e) => {
            eprintln!("[zawra-launcher] Failed to create prog_name CString: {}", e);
            return -1;
        }
    };
    let mut argv: Vec<*mut c_char> = vec![
        prog_name.into_raw(),
        profile_flag.into_raw(),
        profile_val.into_raw(),
        null_mut(),
    ];

    let exit_code = unsafe { wpe_main(3, argv.as_mut_ptr(), null_mut()) };
    unsafe {
        let _ = CString::from_raw(argv[0]);
        let _ = CString::from_raw(argv[1]);
        let _ = CString::from_raw(argv[2]);
    }
    exit_code
}

/// Exported C-ABI bootstrap function — called by embedding code or tests.
///
/// # Safety
/// `profile_path` must be a valid NUL-terminated string or NULL (uses default).
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

static ACTIVE_WPE_VIEW: std::sync::atomic::AtomicPtr<c_void> =
    std::sync::atomic::AtomicPtr::new(std::ptr::null_mut());

/// Set the currently active WPE view handle.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_SetActiveWpeView(view: *mut c_void) {
    ACTIVE_WPE_VIEW.store(view, std::sync::atomic::Ordering::SeqCst);
}

/// Get the currently active WPE view handle.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_GetActiveWpeView() -> *mut c_void {
    ACTIVE_WPE_VIEW.load(std::sync::atomic::Ordering::SeqCst)
}

/// Navigation hook: loads the requested URL in the active WPE view.
///
/// # Safety
/// `url_ptr` must point to a buffer of at least `url_len` bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_LoadURL(url_ptr: *const u8, url_len: usize) {
    if url_ptr.is_null() || url_len == 0 {
        return;
    }
    let url_slice = unsafe { std::slice::from_raw_parts(url_ptr, url_len) };
    let url = String::from_utf8_lossy(url_slice);
    eprintln!("[ZAWRA-WPE] Zawra_LoadURL: {}", url);

    let view = ACTIVE_WPE_VIEW.load(std::sync::atomic::Ordering::SeqCst);
    if let Ok(c_url) = CString::new(url.as_ref()) {
        unsafe {
            // Dynamic resolution of wpe_view_load_url or webkit_web_view_load_uri
            type WpeViewLoadUrlFn = unsafe extern "C" fn(*mut c_void, *const c_char);
            let sym = libc::dlsym(libc::RTLD_DEFAULT, b"wpe_view_load_url\0".as_ptr() as *const _);
            if !sym.is_null() {
                let func: WpeViewLoadUrlFn = std::mem::transmute(sym);
                func(view, c_url.as_ptr());
                return;
            }
            let sym2 = libc::dlsym(libc::RTLD_DEFAULT, b"webkit_web_view_load_uri\0".as_ptr() as *const _);
            if !sym2.is_null() {
                let func2: WpeViewLoadUrlFn = std::mem::transmute(sym2);
                func2(view, c_url.as_ptr());
                return;
            }
        }
    }
}

/// Input event forwarding: pointer events (motion, button, scroll)
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_pointer(
    event_type: u32,
    local_x: f64,
    local_y: f64,
    button: u32,
    state: u32,
) {
    let view = ACTIVE_WPE_VIEW.load(std::sync::atomic::Ordering::SeqCst);
    unsafe {
        type WpePointerEventFn = unsafe extern "C" fn(*mut c_void, u32, f64, f64, u32, u32);
        let sym = libc::dlsym(libc::RTLD_DEFAULT, b"wpe_view_event_pointer\0".as_ptr() as *const _);
        if !sym.is_null() {
            let func: WpePointerEventFn = std::mem::transmute(sym);
            func(view, event_type, local_x, local_y, button, state);
            return;
        }
    }
}

/// Input event forwarding: keyboard events
#[unsafe(no_mangle)]
pub unsafe extern "C" fn wpe_view_event_keyboard(
    key: u32,
    state: u32,
    modifiers: u32,
) {
    let view = ACTIVE_WPE_VIEW.load(std::sync::atomic::Ordering::SeqCst);
    unsafe {
        type WpeKeyboardEventFn = unsafe extern "C" fn(*mut c_void, u32, u32, u32);
        let sym = libc::dlsym(libc::RTLD_DEFAULT, b"wpe_view_event_keyboard\0".as_ptr() as *const _);
        if !sym.is_null() {
            let func: WpeKeyboardEventFn = std::mem::transmute(sym);
            func(view, key, state, modifiers);
            return;
        }
    }
}
