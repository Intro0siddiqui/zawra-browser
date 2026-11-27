//! Browser Cookie Importer (Brave / Firefox -> WebKit NetworkStorageSession)
//!
//! Reads cookies from Brave (Chromium `Cookies` SQLite + Linux `v10`/`v11`
//! AES-128-CBC decryption) or Firefox (`cookies.sqlite`) and inserts them
//! exclusively into WebKit via the registered `webkit_cookie_manager_add_cookie`
//! callback (never into `z-net`'s `CookieJar`).

use std::ffi::{c_char, c_int, c_void, CStr, CString};
use std::fs;
use std::num::NonZeroU32;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicPtr, Ordering};
use std::time::{SystemTime, UNIX_EPOCH};

use ring::pbkdf2;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ImportedCookie {
    pub name: String,
    pub value: String,
    pub domain: String,
    pub path: String,
    /// Relative max-age in seconds (`-1` for session cookies).
    pub max_age: i64,
    pub is_secure: bool,
    pub is_http_only: bool,
}

/// Callback registered by `ui/wpe.zig` to insert a cookie into
/// `WebKitCookieManager` via `webkit_cookie_manager_add_cookie`.
pub type WebKitCookieInserterFn = extern "C" fn(
    name: *const c_char,
    value: *const c_char,
    domain: *const c_char,
    path: *const c_char,
    max_age: i64,
    is_secure: c_int,
    is_http_only: c_int,
);

static WEBKIT_INSERTER: AtomicPtr<c_void> = AtomicPtr::new(std::ptr::null_mut());

#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Register_WebKit_Cookie_Inserter(cb: Option<WebKitCookieInserterFn>) {
    let ptr = match cb {
        Some(f) => f as *mut c_void,
        None => std::ptr::null_mut(),
    };
    WEBKIT_INSERTER.store(ptr, Ordering::Release);
}

fn import_marker_path() -> PathBuf {
    if let Ok(profile) = std::env::var("ZAWRA_PROFILE") {
        if !profile.is_empty() {
            return PathBuf::from(profile).join(".cookie_import_done");
        }
    }
    let mut home = dirs::home_dir().unwrap_or_default();
    home.push(".zawra/profile/.cookie_import_done");
    home
}

fn mark_import_done() {
    let marker = import_marker_path();
    if let Some(parent) = marker.parent() {
        let _ = fs::create_dir_all(parent);
    }
    let _ = fs::write(&marker, b"1\n");
}

pub fn find_brave_cookies_db() -> Option<PathBuf> {
    let home = dirs::home_dir()?;
    let base = home.join(".config/BraveSoftware/Brave-Browser");
    for profile in ["Default", "Profile 1", "Profile 2"] {
        let candidate = base.join(profile).join("Cookies");
        if candidate.is_file() {
            return Some(candidate);
        }
    }
    None
}

pub fn find_firefox_cookies_db() -> Option<PathBuf> {
    let home = dirs::home_dir()?;
    let base = home.join(".mozilla/firefox");
    let entries = fs::read_dir(&base).ok()?;
    let mut fallback: Option<PathBuf> = None;
    for entry in entries.flatten() {
        let path = entry.path();
        if !path.is_dir() {
            continue;
        }
        let db = path.join("cookies.sqlite");
        if !db.is_file() {
            continue;
        }
        let name = path.file_name().and_then(|s| s.to_str()).unwrap_or("");
        if name.contains("default-release") {
            return Some(db);
        }
        if fallback.is_none() {
            fallback = Some(db);
        }
    }
    fallback
}

/// Returns `1` if no import/skip marker exists and Brave or Firefox cookies are present.
#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Should_Prompt_Cookie_Import() -> c_int {
    if import_marker_path().exists() {
        return 0;
    }
    if find_brave_cookies_db().is_some() || find_firefox_cookies_db().is_some() {
        1
    } else {
        0
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn Zawra_Mark_Cookie_Import_Skipped() {
    mark_import_done();
}

/// Import cookies from `"brave"` or `"firefox"` into WebKit's `WebKitCookieManager`.
/// Returns the number of cookies inserted, or `-1` on error.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Import_Cookies(source: *const c_char) -> c_int {
    if source.is_null() {
        return -1;
    }
    let src_str = unsafe { CStr::from_ptr(source) }.to_string_lossy();
    let cookies = match src_str.trim().to_ascii_lowercase().as_str() {
        "brave" => match read_brave_cookies() {
            Ok(c) => c,
            Err(e) => {
                eprintln!("[zawra-import] Brave cookie read failed: {}", e);
                return -1;
            }
        },
        "firefox" => match read_firefox_cookies() {
            Ok(c) => c,
            Err(e) => {
                eprintln!("[zawra-import] Firefox cookie read failed: {}", e);
                return -1;
            }
        },
        other => {
            eprintln!("[zawra-import] Unknown browser source '{}'", other);
            return -1;
        }
    };

    let inserter_ptr = WEBKIT_INSERTER.load(Ordering::Acquire);
    if inserter_ptr.is_null() {
        eprintln!("[zawra-import] WebKitCookieManager inserter is not registered");
        return -1;
    }
    let inserter: WebKitCookieInserterFn = unsafe { std::mem::transmute(inserter_ptr) };

    let mut inserted: c_int = 0;
    for cookie in &cookies {
        let Ok(c_name) = CString::new(cookie.name.as_str()) else { continue };
        let Ok(c_val) = CString::new(cookie.value.as_str()) else { continue };
        let Ok(c_dom) = CString::new(cookie.domain.as_str()) else { continue };
        let Ok(c_path) = CString::new(cookie.path.as_str()) else { continue };
        inserter(
            c_name.as_ptr(),
            c_val.as_ptr(),
            c_dom.as_ptr(),
            c_path.as_ptr(),
            cookie.max_age,
            if cookie.is_secure { 1 } else { 0 },
            if cookie.is_http_only { 1 } else { 0 },
        );
        inserted += 1;
    }

    mark_import_done();
    eprintln!(
        "[zawra-import] Imported {} cookies from {} into WebKit NetworkStorageSession",
        inserted, src_str
    );
    inserted
}

// ---------------------------------------------------------------------------
// Dynamic libsqlite3 loader (avoids extra build/crate dependencies)
// ---------------------------------------------------------------------------

const SQLITE_OK: c_int = 0;
const SQLITE_ROW: c_int = 100;
const SQLITE_OPEN_READONLY: c_int = 0x0000_0001;

type Sqlite3OpenV2Fn = unsafe extern "C" fn(*const c_char, *mut *mut c_void, c_int, *const c_char) -> c_int;
type Sqlite3CloseFn = unsafe extern "C" fn(*mut c_void) -> c_int;
type Sqlite3PrepareV2Fn = unsafe extern "C" fn(*mut c_void, *const c_char, c_int, *mut *mut c_void, *mut *const c_char) -> c_int;
type Sqlite3StepFn = unsafe extern "C" fn(*mut c_void) -> c_int;
type Sqlite3FinalizeFn = unsafe extern "C" fn(*mut c_void) -> c_int;
type Sqlite3ColumnTextFn = unsafe extern "C" fn(*mut c_void, c_int) -> *const u8;
type Sqlite3ColumnBlobFn = unsafe extern "C" fn(*mut c_void, c_int) -> *const c_void;
type Sqlite3ColumnBytesFn = unsafe extern "C" fn(*mut c_void, c_int) -> c_int;
type Sqlite3ColumnInt64Fn = unsafe extern "C" fn(*mut c_void, c_int) -> i64;

struct SqliteApi {
    _handle: *mut c_void,
    open_v2: Sqlite3OpenV2Fn,
    close: Sqlite3CloseFn,
    prepare_v2: Sqlite3PrepareV2Fn,
    step: Sqlite3StepFn,
    finalize: Sqlite3FinalizeFn,
    column_text: Sqlite3ColumnTextFn,
    column_blob: Sqlite3ColumnBlobFn,
    column_bytes: Sqlite3ColumnBytesFn,
    column_int64: Sqlite3ColumnInt64Fn,
}

impl SqliteApi {
    fn load() -> Result<Self, String> {
        unsafe {
            let mut handle = std::ptr::null_mut();
            for lib in [b"libsqlite3.so.0\0".as_slice(), b"libsqlite3.so\0".as_slice()] {
                handle = libc::dlopen(lib.as_ptr() as *const c_char, libc::RTLD_LAZY);
                if !handle.is_null() {
                    break;
                }
            }
            if handle.is_null() {
                return Err("Could not dlopen libsqlite3.so.0".to_string());
            }

            macro_rules! sym {
                ($name:literal, $ty:ty) => {{
                    let ptr = libc::dlsym(handle, concat!($name, "\0").as_ptr() as *const c_char);
                    if ptr.is_null() {
                        libc::dlclose(handle);
                        return Err(format!("Missing sqlite3 symbol {}", $name));
                    }
                    std::mem::transmute::<*mut c_void, $ty>(ptr)
                }};
            }

            Ok(Self {
                _handle: handle,
                open_v2: sym!("sqlite3_open_v2", Sqlite3OpenV2Fn),
                close: sym!("sqlite3_close", Sqlite3CloseFn),
                prepare_v2: sym!("sqlite3_prepare_v2", Sqlite3PrepareV2Fn),
                step: sym!("sqlite3_step", Sqlite3StepFn),
                finalize: sym!("sqlite3_finalize", Sqlite3FinalizeFn),
                column_text: sym!("sqlite3_column_text", Sqlite3ColumnTextFn),
                column_blob: sym!("sqlite3_column_blob", Sqlite3ColumnBlobFn),
                column_bytes: sym!("sqlite3_column_bytes", Sqlite3ColumnBytesFn),
                column_int64: sym!("sqlite3_column_int64", Sqlite3ColumnInt64Fn),
            })
        }
    }

    unsafe fn col_str(&self, stmt: *mut c_void, col: c_int) -> String {
        unsafe {
            let ptr = (self.column_text)(stmt, col);
            if ptr.is_null() {
                return String::new();
            }
            CStr::from_ptr(ptr as *const c_char).to_string_lossy().into_owned()
        }
    }

    unsafe fn col_blob(&self, stmt: *mut c_void, col: c_int) -> Vec<u8> {
        unsafe {
            let len = (self.column_bytes)(stmt, col);
            if len <= 0 {
                return Vec::new();
            }
            let ptr = (self.column_blob)(stmt, col);
            if ptr.is_null() {
                return Vec::new();
            }
            std::slice::from_raw_parts(ptr as *const u8, len as usize).to_vec()
        }
    }
}

impl Drop for SqliteApi {
    fn drop(&mut self) {
        if !self._handle.is_null() {
            unsafe { libc::dlclose(self._handle) };
        }
    }
}

struct TempDbCopy {
    path: PathBuf,
}

impl TempDbCopy {
    fn create(src: &Path) -> Result<Self, String> {
        let pid = std::process::id();
        let nanos = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .map(|d| d.as_nanos())
            .unwrap_or(0);
        let dst = std::env::temp_dir().join(format!("zawra_cookie_import_{}_{}.sqlite", pid, nanos));
        fs::copy(src, &dst).map_err(|e| format!("Failed to copy {:?}: {}", src, e))?;
        Ok(Self { path: dst })
    }
}

impl Drop for TempDbCopy {
    fn drop(&mut self) {
        let _ = fs::remove_file(&self.path);
    }
}

// ---------------------------------------------------------------------------
// Brave / Chromium reader + Linux v10/v11 AES-128-CBC decryption
// ---------------------------------------------------------------------------

fn derive_linux_v10_v11_key(password: &[u8]) -> [u8; 16] {
    let mut key = [0u8; 16];
    pbkdf2::derive(
        pbkdf2::PBKDF2_HMAC_SHA1,
        NonZeroU32::new(1).unwrap(),
        b"saltysalt",
        password,
        &mut key,
    );
    key
}

fn lookup_brave_v11_password() -> Vec<u8> {
    for args in [
        ["lookup", "application", "brave"].as_slice(),
        ["lookup", "xdg:schema", "chrome_libsecret_os_crypt_password_v2", "application", "brave"].as_slice(),
    ] {
        if let Ok(out) = std::process::Command::new("secret-tool").args(args).output() {
            if out.status.success() && !out.stdout.is_empty() {
                let mut pw = out.stdout;
                while matches!(pw.last(), Some(b'\n' | b'\r')) {
                    pw.pop();
                }
                if !pw.is_empty() {
                    return pw;
                }
            }
        }
    }
    b"peanuts".to_vec()
}

pub fn decrypt_chromium_linux_cookie(
    encrypted: &[u8],
    v10_key: &[u8; 16],
    v11_key: &[u8; 16],
    db_version: i64,
) -> Option<String> {
    if encrypted.len() < 3 {
        return None;
    }
    let key = match &encrypted[..3] {
        b"v10" => v10_key,
        b"v11" => v11_key,
        _ => return None,
    };
    let ciphertext = &encrypted[3..];
    let mut plaintext = aes_128_cbc_decrypt_pkcs7(key, &[0x20u8; 16], ciphertext)?;
    // Chromium DB >= v24 prepends a 32-byte SHA-256 host_key hash.
    if db_version >= 24 && plaintext.len() >= 32 {
        plaintext.drain(..32);
    }
    String::from_utf8(plaintext).ok()
}

fn read_brave_cookies() -> Result<Vec<ImportedCookie>, String> {
    let db_path = find_brave_cookies_db().ok_or("Brave Cookies DB not found")?;
    let copy = TempDbCopy::create(&db_path)?;
    let sqlite = SqliteApi::load()?;

    let c_path = CString::new(copy.path.to_string_lossy().as_ref()).map_err(|_| "invalid path")?;
    let mut db: *mut c_void = std::ptr::null_mut();
    unsafe {
        if (sqlite.open_v2)(c_path.as_ptr(), &mut db, SQLITE_OPEN_READONLY, std::ptr::null()) != SQLITE_OK {
            return Err("sqlite3_open_v2 failed for Brave Cookies".to_string());
        }
    }

    let mut db_version: i64 = 0;
    unsafe {
        let q = CString::new("SELECT value FROM meta WHERE key = 'version'").unwrap();
        let mut stmt: *mut c_void = std::ptr::null_mut();
        if (sqlite.prepare_v2)(db, q.as_ptr(), -1, &mut stmt, std::ptr::null_mut()) == SQLITE_OK {
            if (sqlite.step)(stmt) == SQLITE_ROW {
                db_version = sqlite.col_str(stmt, 0).parse::<i64>().unwrap_or(0);
            }
            (sqlite.finalize)(stmt);
        }
    }

    let v10_key = derive_linux_v10_v11_key(b"peanuts");
    let v11_pw = lookup_brave_v11_password();
    let v11_key = derive_linux_v10_v11_key(&v11_pw);

    let now_unix = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .map(|d| d.as_secs() as i64)
        .unwrap_or(0);

    let mut cookies = Vec::new();
    unsafe {
        let q = CString::new(
            "SELECT host_key, name, value, encrypted_value, path, expires_utc, is_secure, is_httponly FROM cookies",
        )
        .unwrap();
        let mut stmt: *mut c_void = std::ptr::null_mut();
        if (sqlite.prepare_v2)(db, q.as_ptr(), -1, &mut stmt, std::ptr::null_mut()) != SQLITE_OK {
            (sqlite.close)(db);
            return Err("sqlite3_prepare_v2 failed for Brave cookies table".to_string());
        }

        while (sqlite.step)(stmt) == SQLITE_ROW {
            let domain = sqlite.col_str(stmt, 0);
            let name = sqlite.col_str(stmt, 1);
            let plain_val = sqlite.col_str(stmt, 2);
            let enc_val = sqlite.col_blob(stmt, 3);
            let path = sqlite.col_str(stmt, 4);
            let expires_utc = (sqlite.column_int64)(stmt, 5);
            let is_secure = (sqlite.column_int64)(stmt, 6) != 0;
            let is_http_only = (sqlite.column_int64)(stmt, 7) != 0;

            let value = if !plain_val.is_empty() {
                plain_val
            } else if let Some(dec) = decrypt_chromium_linux_cookie(&enc_val, &v10_key, &v11_key, db_version) {
                dec
            } else {
                continue;
            };

            let max_age = chromium_expires_to_max_age(expires_utc, now_unix);
            if max_age == 0 {
                continue;
            }
            cookies.push(ImportedCookie {
                name,
                value,
                domain,
                path: if path.is_empty() { "/".to_string() } else { path },
                max_age,
                is_secure,
                is_http_only,
            });
        }
        (sqlite.finalize)(stmt);
        (sqlite.close)(db);
    }

    Ok(cookies)
}

fn read_firefox_cookies() -> Result<Vec<ImportedCookie>, String> {
    let db_path = find_firefox_cookies_db().ok_or("Firefox cookies.sqlite not found")?;
    let copy = TempDbCopy::create(&db_path)?;
    let sqlite = SqliteApi::load()?;

    let c_path = CString::new(copy.path.to_string_lossy().as_ref()).map_err(|_| "invalid path")?;
    let mut db: *mut c_void = std::ptr::null_mut();
    unsafe {
        if (sqlite.open_v2)(c_path.as_ptr(), &mut db, SQLITE_OPEN_READONLY, std::ptr::null()) != SQLITE_OK {
            return Err("sqlite3_open_v2 failed for Firefox cookies.sqlite".to_string());
        }
    }

    let now_unix = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .map(|d| d.as_secs() as i64)
        .unwrap_or(0);

    let mut cookies = Vec::new();
    unsafe {
        let q = CString::new(
            "SELECT host, name, value, path, expiry, isSecure, isHttpOnly FROM moz_cookies",
        )
        .unwrap();
        let mut stmt: *mut c_void = std::ptr::null_mut();
        if (sqlite.prepare_v2)(db, q.as_ptr(), -1, &mut stmt, std::ptr::null_mut()) != SQLITE_OK {
            (sqlite.close)(db);
            return Err("sqlite3_prepare_v2 failed for moz_cookies".to_string());
        }

        while (sqlite.step)(stmt) == SQLITE_ROW {
            let domain = sqlite.col_str(stmt, 0);
            let name = sqlite.col_str(stmt, 1);
            let value = sqlite.col_str(stmt, 2);
            let path = sqlite.col_str(stmt, 3);
            let expiry = (sqlite.column_int64)(stmt, 4);
            let is_secure = (sqlite.column_int64)(stmt, 5) != 0;
            let is_http_only = (sqlite.column_int64)(stmt, 6) != 0;

            let max_age = if expiry <= 0 {
                -1
            } else {
                let rem = expiry - now_unix;
                if rem <= 0 {
                    continue;
                }
                rem
            };

            cookies.push(ImportedCookie {
                name,
                value,
                domain,
                path: if path.is_empty() { "/".to_string() } else { path },
                max_age,
                is_secure,
                is_http_only,
            });
        }
        (sqlite.finalize)(stmt);
        (sqlite.close)(db);
    }

    Ok(cookies)
}

/// Convert Chromium `expires_utc` (microseconds since 1601-01-01) to `SoupCookie` `max_age`.
pub fn chromium_expires_to_max_age(expires_utc: i64, now_unix_secs: i64) -> i64 {
    if expires_utc <= 0 {
        return -1; // session cookie
    }
    const WINDOWS_TO_UNIX_EPOCH_SECS: i64 = 11_644_473_600;
    let unix_secs = (expires_utc / 1_000_000) - WINDOWS_TO_UNIX_EPOCH_SECS;
    let rem = unix_secs - now_unix_secs;
    if rem <= 0 {
        0
    } else {
        rem
    }
}

// ---------------------------------------------------------------------------
// Minimal pure-Rust AES-128-CBC + PKCS#7 decryptor (FIPS-197)
// ---------------------------------------------------------------------------

#[rustfmt::skip]
const SBOX: [u8; 256] = [
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16,
];

#[rustfmt::skip]
const INV_SBOX: [u8; 256] = [
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d,
];

const RCON: [u8; 10] = [0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36];

#[inline]
fn xtime(a: u8) -> u8 {
    (a << 1) ^ (((a >> 7) & 1) * 0x1b)
}

#[inline]
fn gmul(mut a: u8, mut b: u8) -> u8 {
    let mut p = 0u8;
    for _ in 0..8 {
        if (b & 1) != 0 {
            p ^= a;
        }
        a = xtime(a);
        b >>= 1;
    }
    p
}

fn aes128_key_expansion(key: &[u8; 16]) -> [[u8; 16]; 11] {
    let mut w = [0u8; 176];
    w[..16].copy_from_slice(key);
    for i in 4..44 {
        let mut temp = [w[(i - 1) * 4], w[(i - 1) * 4 + 1], w[(i - 1) * 4 + 2], w[(i - 1) * 4 + 3]];
        if i % 4 == 0 {
            temp = [
                SBOX[temp[1] as usize] ^ RCON[i / 4 - 1],
                SBOX[temp[2] as usize],
                SBOX[temp[3] as usize],
                SBOX[temp[0] as usize],
            ];
        }
        for j in 0..4 {
            w[i * 4 + j] = w[(i - 4) * 4 + j] ^ temp[j];
        }
    }
    let mut rk = [[0u8; 16]; 11];
    for r in 0..11 {
        rk[r].copy_from_slice(&w[r * 16..(r + 1) * 16]);
    }
    rk
}

fn aes128_decrypt_block(rk: &[[u8; 16]; 11], block: &[u8; 16]) -> [u8; 16] {
    let mut s = *block;
    for i in 0..16 {
        s[i] ^= rk[10][i];
    }
    for round in (1..10).rev() {
        // InvShiftRows
        s = [
            s[0], s[13], s[10], s[7],
            s[4], s[1], s[14], s[11],
            s[8], s[5], s[2], s[15],
            s[12], s[9], s[6], s[3],
        ];
        // InvSubBytes
        for b in &mut s {
            *b = INV_SBOX[*b as usize];
        }
        // AddRoundKey
        for i in 0..16 {
            s[i] ^= rk[round][i];
        }
        // InvMixColumns
        for c in 0..4 {
            let idx = c * 4;
            let (s0, s1, s2, s3) = (s[idx], s[idx + 1], s[idx + 2], s[idx + 3]);
            s[idx]     = gmul(s0, 0x0e) ^ gmul(s1, 0x0b) ^ gmul(s2, 0x0d) ^ gmul(s3, 0x09);
            s[idx + 1] = gmul(s0, 0x09) ^ gmul(s1, 0x0e) ^ gmul(s2, 0x0b) ^ gmul(s3, 0x0d);
            s[idx + 2] = gmul(s0, 0x0d) ^ gmul(s1, 0x09) ^ gmul(s2, 0x0e) ^ gmul(s3, 0x0b);
            s[idx + 3] = gmul(s0, 0x0b) ^ gmul(s1, 0x0d) ^ gmul(s2, 0x09) ^ gmul(s3, 0x0e);
        }
    }
    // Final round
    s = [
        s[0], s[13], s[10], s[7],
        s[4], s[1], s[14], s[11],
        s[8], s[5], s[2], s[15],
        s[12], s[9], s[6], s[3],
    ];
    for b in &mut s {
        *b = INV_SBOX[*b as usize];
    }
    for i in 0..16 {
        s[i] ^= rk[0][i];
    }
    s
}

pub fn aes_128_cbc_decrypt_pkcs7(key: &[u8; 16], iv: &[u8; 16], ciphertext: &[u8]) -> Option<Vec<u8>> {
    if ciphertext.is_empty() || ciphertext.len() % 16 != 0 {
        return None;
    }
    let rk = aes128_key_expansion(key);
    let mut out = Vec::with_capacity(ciphertext.len());
    let mut prev = *iv;
    for chunk in ciphertext.chunks_exact(16) {
        let block: [u8; 16] = chunk.try_into().ok()?;
        let dec = aes128_decrypt_block(&rk, &block);
        for i in 0..16 {
            out.push(dec[i] ^ prev[i]);
        }
        prev = block;
    }
    let pad = *out.last()? as usize;
    if pad == 0 || pad > 16 || pad > out.len() {
        return None;
    }
    if !out[out.len() - pad..].iter().all(|&b| b as usize == pad) {
        return None;
    }
    out.truncate(out.len() - pad);
    Some(out)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_aes_128_cbc_pkcs7_nist_and_v10_decrypt() {
        // Known AES-128-CBC ciphertext for "hello_zawra" with v10 key ("peanuts") and IV (' ' * 16)
        let key = derive_linux_v10_v11_key(b"peanuts");
        assert_eq!(
            key,
            [
                0xfd, 0x62, 0x1f, 0xe5, 0xa2, 0xb4, 0x02, 0x53,
                0x9d, 0xfa, 0x14, 0x7c, 0xa9, 0x27, 0x27, 0x78
            ]
        );

        // NIST SP 800-38A F.2.2 CBC-AES128.Decrypt block 1
        let nist_key: [u8; 16] = [
            0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
        ];
        let nist_iv: [u8; 16] = [
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        ];
        let nist_ct: [u8; 16] = [
            0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
            0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
        ];
        let rk = aes128_key_expansion(&nist_key);
        let dec = aes128_decrypt_block(&rk, &nist_ct);
        let mut pt = [0u8; 16];
        for i in 0..16 {
            pt[i] = dec[i] ^ nist_iv[i];
        }
        assert_eq!(
            pt,
            [
                0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
            ]
        );
    }

    #[test]
    fn test_chromium_expires_conversion() {
        assert_eq!(chromium_expires_to_max_age(0, 1_700_000_000), -1);
        let future_utc = (1_700_000_000 + 11_644_473_600 + 3600) * 1_000_000;
        assert_eq!(chromium_expires_to_max_age(future_utc, 1_700_000_000), 3600);
        let past_utc = (1_700_000_000 + 11_644_473_600 - 10) * 1_000_000;
        assert_eq!(chromium_expires_to_max_age(past_utc, 1_700_000_000), 0);
    }
}
