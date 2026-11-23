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

use std::ffi::{CStr, CString, c_char};
use std::path::PathBuf;

use crate::wpe_glue::networking::{init_net_engine, shutdown_net_engine};
use crate::wpe_glue::storage::{Z_Storage_Flush, Z_Storage_Init};

const NS_OK: i32 = 0;
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
pub unsafe extern "C" fn Z_Init_Subsystems(profile_path: *const c_char) -> i32 {
    // Ensure WEBKIT_INJECTED_BUNDLE_PATH is populated so WPEWebProcess finds libWPEInjectedBundle.so
    if std::env::var_os("WEBKIT_INJECTED_BUNDLE_PATH").is_none() {
        #[cfg(target_os = "android")]
        {
            let android_bundle_dirs = [
                std::env::var("ZAWRA_NATIVE_LIB_DIR").ok(),
                Some("/data/data/com.zawra.browser/lib".to_string()),
                Some("/data/local/tmp".to_string()),
            ];
            for maybe_dir in &android_bundle_dirs {
                if let Some(dir) = maybe_dir {
                    if std::path::Path::new(dir).is_dir() {
                        unsafe {
                            std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir);
                        }
                        break;
                    }
                }
            }
        }
        #[cfg(target_os = "macos")]
        {
            let mac_bundle_dirs = [
                std::env::current_exe().ok().and_then(|exe| {
                    exe.parent().map(|p| p.join("../Frameworks"))
                }),
                Some(PathBuf::from("/opt/homebrew/lib")),
                Some(PathBuf::from("/usr/local/lib")),
                Some(PathBuf::from("/home/intro/spectre-enviroment/browser/zawra-browser/webkit/build/lib")),
            ];
            for maybe_dir in &mac_bundle_dirs {
                if let Some(dir) = maybe_dir {
                    if dir.is_dir() {
                        unsafe {
                            std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", dir);
                        }
                        break;
                    }
                }
            }
        }
        #[cfg(not(any(target_os = "android", target_os = "macos")))]
        {
            let default_bundle = "/home/intro/spectre-enviroment/browser/zawra-browser/webkit/build/lib";
            if std::path::Path::new(default_bundle).is_dir() {
                unsafe {
                    std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", default_bundle);
                }
            }
        }
    }

    // ── 1. Resolve DB path ──────────────────────────────────────────────────
    let profile_str = if profile_path.is_null() {
        if let Ok(p) = std::env::var("ZAWRA_PROFILE") {
            p
        } else if let Ok(p) = std::env::var("ZAWRA_ANDROID_DATA_DIR") {
            PathBuf::from(p).join("profile").to_string_lossy().into_owned()
        } else {
            #[cfg(target_os = "android")]
            {
                let android_dir = PathBuf::from("/data/data/com.zawra.browser/files/profile");
                if std::fs::create_dir_all(&android_dir).is_ok() {
                    android_dir.to_string_lossy().into_owned()
                } else {
                    let fallback = PathBuf::from("/data/local/tmp/zawra_profile");
                    std::fs::create_dir_all(&fallback).ok();
                    fallback.to_string_lossy().into_owned()
                }
            }
            #[cfg(target_os = "macos")]
            {
                if let Ok(home) = std::env::var("HOME") {
                    let mac_dir = PathBuf::from(home)
                        .join("Library")
                        .join("Application Support")
                        .join("Zawra")
                        .join("profile");
                    std::fs::create_dir_all(&mac_dir).ok();
                    mac_dir.to_string_lossy().into_owned()
                } else {
                    "./zawra_profile".to_string()
                }
            }
            #[cfg(not(any(target_os = "android", target_os = "macos")))]
            {
                "./zawra_profile".to_string()
            }
        }
    } else {
        match unsafe { CStr::from_ptr(profile_path).to_str() } {
            Ok(s) => s.to_string(),
            Err(e) => {
                eprintln!("[zawra-init] Invalid UTF-8 sequence in profile_path: {}", e);
                return NS_ERROR_FAILURE;
            }
        }
    };

    let db_path: PathBuf = PathBuf::from(&profile_str).join("zawra_db");
    let db_path_str = match db_path.to_str() {
        Some(s) => s.to_string(),
        None => {
            eprintln!("[zawra-init] Database path is not valid UTF-8: {:?}", db_path);
            return NS_ERROR_FAILURE;
        }
    };

    // ── 2. Init BrowserDB ───────────────────────────────────────────────────
    let db_path_c = match CString::new(db_path_str) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("[zawra-init] Failed to create CString for DB path: {}", e);
            return NS_ERROR_FAILURE;
        }
    };
    let db_ret = unsafe { Z_Storage_Init(db_path_c.as_ptr()) };
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

    // ── 4. Init z-graphics engine ───────────────────────────────────────────
    unsafe extern "C" {
        #[link_name = "ZG_Initialize"]
        fn Z_Graphics_Initialize() -> bool;
    }
    if !unsafe { Z_Graphics_Initialize() } {
        eprintln!("[zawra] z-graphics engine init failed");
        return NS_ERROR_FAILURE;
    }
    eprintln!("[zawra] z-graphics engine initialised");

    // ── 5. Init Hajr tracing ────────────────────────────────────────────────
    unsafe extern "C" {
        fn hajr_trace_init();
    }
    unsafe { hajr_trace_init(); }
    eprintln!("[zawra] hajr trace initialized (if HAJR_TRACE_FILE set)");

    eprintln!("[zawra] Zawra_Init_Subsystems: all subsystems ready");
    NS_OK
}

/// Shut down all Zawra subsystems gracefully.
///
/// Flushes BrowserDB memtable to disk and cleans up subsystem resources.
/// Safe to call even if init was never completed.
#[unsafe(no_mangle)]
pub extern "C" fn Z_Shutdown_Subsystems() {
    eprintln!("[zawra] Shutdown requested — starting graceful subsystem teardown...");

    // 1. Flush BrowserDB memtable to disk
    let flush_ret = Z_Storage_Flush();
    if flush_ret != NS_OK {
        eprintln!("[zawra] Warning: BrowserDB flush returned error code {}", flush_ret);
    } else {
        eprintln!("[zawra] BrowserDB memtable flushed to disk successfully");
    }

    // 2. Clean up networking engine and poll thread
    shutdown_net_engine();
    eprintln!("[zawra] z-net engine poll thread stopped and resources released");

    eprintln!("[zawra] Subsystems shutdown complete");
}

/// C-ABI alias for Z_Shutdown_Subsystems.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Shutdown_Subsystems() {
    Z_Shutdown_Subsystems();
}

/// Android-specific entrypoint to initialize Zawra with an explicit data directory and injected bundle directory.
///
/// `data_dir` – directory for database and storage (e.g. `Context.getFilesDir().getAbsolutePath()`).
/// `injected_bundle_dir` – directory where `libWPEInjectedBundle.so` resides (e.g. app native lib dir).
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Android_Init(
    data_dir: *const c_char,
    injected_bundle_dir: *const c_char,
) -> i32 {
    if !injected_bundle_dir.is_null() {
        if let Ok(bundle_str) = unsafe { CStr::from_ptr(injected_bundle_dir).to_str() } {
            unsafe {
                std::env::set_var("WEBKIT_INJECTED_BUNDLE_PATH", bundle_str);
            }
        }
    }
    unsafe { Z_Init_Subsystems(data_dir) }
}

unsafe extern "C" {
    fn __hajr_create_anonymous_ring(size: usize) -> u64;
    fn __hajr_map_anonymous_ring(id: u64) -> *mut std::ffi::c_void;
    fn __hajr_map_anonymous_ring_ex(id: u64, signal_fd: i32) -> *mut std::ffi::c_void;
    fn hajr_ring_get_signal_fd(ring_ptr: *mut std::ffi::c_void) -> i32;
    fn Zawra_Hajr_MemAlloc(size: usize) -> *mut std::ffi::c_void;
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_MapBootstrapRingWithSignal(
    id: u64,
    signal_fd: i32,
) -> *mut std::ffi::c_void {
    unsafe { __hajr_map_anonymous_ring_ex(id, signal_fd) }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_GetRingSignalFD(ring_ptr: *mut std::ffi::c_void) -> i32 {
    if ring_ptr.is_null() {
        return -1;
    }
    unsafe { hajr_ring_get_signal_fd(ring_ptr) }
}

#[repr(C)]
pub struct Zawra_Hajr_RingPair {
    pub ring1_id: u64,
    pub ring2_id: u64,
    pub signal1_fd: i32,
    pub signal2_fd: i32,
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_CreateRingPair(size: usize) -> Zawra_Hajr_RingPair {
    let id1 = unsafe { __hajr_create_anonymous_ring(size) };
    let id2 = unsafe { __hajr_create_anonymous_ring(size) };

    let ring1 = unsafe { __hajr_map_anonymous_ring(id1) };
    let ring2 = unsafe { __hajr_map_anonymous_ring(id2) };

    let fd1 = unsafe { Z_Hajr_GetRingSignalFD(ring1) };
    let fd2 = unsafe { Z_Hajr_GetRingSignalFD(ring2) };

    Zawra_Hajr_RingPair {
        ring1_id: id1,
        ring2_id: id2,
        signal1_fd: fd1,
        signal2_fd: fd2,
    }
}

/// Redirected Memory Allocation for WTF (WebKit Template Framework).
///
/// Allocates `size` bytes using Hajr's mmap-guarded memory allocator (`Zawra_Hajr_MemAlloc`).
///
/// # Safety
/// This is an unsafe FFI function called by WebKit.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_MemAlloc(size: usize) -> *mut std::ffi::c_void {
    static RESOLVED_HAJR_ALLOC: std::sync::OnceLock<Option<unsafe extern "C" fn(usize) -> *mut std::ffi::c_void>> =
        std::sync::OnceLock::new();
    let alloc_fn = RESOLVED_HAJR_ALLOC.get_or_init(|| {
        #[cfg(target_os = "windows")]
        let sym = {
            extern "system" {
                fn GetModuleHandleA(lpModuleName: *const std::ffi::c_char) -> *mut std::ffi::c_void;
                fn GetProcAddress(hModule: *mut std::ffi::c_void, lpProcName: *const std::ffi::c_char) -> *mut std::ffi::c_void;
            }
            unsafe {
                let h = GetModuleHandleA(std::ptr::null());
                if !h.is_null() {
                    GetProcAddress(h, b"Zawra_Hajr_MemAlloc\0".as_ptr() as *const std::ffi::c_char)
                } else {
                    std::ptr::null_mut()
                }
            }
        };
        #[cfg(not(target_os = "windows"))]
        let sym = unsafe {
            libc::dlsym(
                libc::RTLD_DEFAULT,
                b"Zawra_Hajr_MemAlloc\0".as_ptr() as *const libc::c_char,
            )
        };
        if !sym.is_null() {
            Some(unsafe { std::mem::transmute(sym) })
        } else {
            None
        }
    });

    if let Some(f) = alloc_fn {
        let ptr = unsafe { f(size) };
        if !ptr.is_null() {
            return ptr;
        }
    }

    unsafe { Zawra_Hajr_MemAlloc(size) }
}

/// Redirected Memory Protection for WTF.
///
/// Sets memory protection on `ptr` for `size` bytes.
///
/// # Safety
/// This is an unsafe FFI function called by WebKit.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hajr_MemProtect(
    ptr: *mut std::ffi::c_void,
    size: usize,
    read: bool,
    write: bool,
) -> i32 {
    #[cfg(target_os = "windows")]
    {
        extern "system" {
            fn VirtualProtect(
                lpAddress: *mut std::ffi::c_void,
                dwSize: usize,
                flNewProtect: u32,
                lpflOldProtect: *mut u32,
            ) -> i32;
        }
        const PAGE_NOACCESS: u32 = 0x01;
        const PAGE_READONLY: u32 = 0x02;
        const PAGE_READWRITE: u32 = 0x04;

        let prot = if read && write {
            PAGE_READWRITE
        } else if read {
            PAGE_READONLY
        } else {
            PAGE_NOACCESS
        };

        let mut old_protect = 0u32;
        if unsafe { VirtualProtect(ptr, size, prot, &mut old_protect) } != 0 {
            0
        } else {
            -1
        }
    }
    #[cfg(not(target_os = "windows"))]
    {
        let mut prot = libc::PROT_NONE;
        if read {
            prot |= libc::PROT_READ;
        }
        if write {
            prot |= libc::PROT_WRITE;
        }

        if unsafe { libc::mprotect(ptr, size, prot) } == 0 {
            0
        } else {
            -1
        }
    }
}
