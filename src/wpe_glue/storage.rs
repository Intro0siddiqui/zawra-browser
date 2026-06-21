//! Zawra Storage Bypass — BrowserDB ↔ WPE Storage / WebsiteData Glue
//!
//! This module replaces WPE's SQLite-backed storage engines with BrowserDB.
//! It exposes a flat C-ABI that WPE's layer calls instead of its own
//! storage / WebsiteData SQLite bindings.
//!
//! ## Subsystems covered
//!
//! | WPE subsystem                 | BrowserDB backing           |
//! |-------------------------------|-----------------------------|
//! | IndexedDB blobs               | `LocalStoreTable`           |
//! | localStorage / sessionStorage | `LocalStoreTable`           |
//! | Cookies (state manager)       | `CookiesTable`              |
//! | HTTP Cache (RFC 7234)         | `CacheTable`                |
//! | Navigation history            | `HistoryTable`              |
//! | Browser settings              | `SettingsTable`             |

use std::ffi::{c_char, CStr};
use std::sync::OnceLock;

use browserdb::{
    BrowserDB, BookmarkEntry, CookieEntry, CacheEntry, HistoryEntry, LocalStoreEntry,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Global BrowserDB singleton
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

static GLOBAL_DB: OnceLock<BrowserDB> = OnceLock::new();

fn db() -> &'static BrowserDB {
    GLOBAL_DB.get().expect("BrowserDB not initialised – call Zawra_Storage_Init first")
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsresult constants (mirror WPE/XPCOM)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const NS_OK:              i32 = 0;
const NS_ERROR_FAILURE:   i32 = -2147467259i32;
const NS_ERROR_NOT_FOUND: i32 = -2147023878i32;
const NS_ERROR_INVALID_ARG: i32 = -2147024809i32;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Statistics struct (C-ABI safe)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// C-ABI layout for storage stats returned to WPE's quota reporter.
#[repr(C)]
pub struct ZawraStorageStats {
    pub total_entries:      u64,
    pub history_entries:    u64,
    pub cookie_entries:     u64,
    pub cache_entries:      u64,
    pub localstore_entries: u64,
    pub settings_entries:   u64,
    pub memory_usage_mb:    u64,
    pub disk_usage_mb:      u64,
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Initialisation
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Open (or create) the BrowserDB at `profile_path`.
///
/// # Safety
/// `profile_path` must be a valid NUL-terminated UTF-8 path string.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_Init(profile_path: *const c_char) -> i32 {
    if profile_path.is_null() { return NS_ERROR_INVALID_ARG; }
    let path_str = match unsafe { CStr::from_ptr(profile_path).to_str() } {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    eprintln!("[ZAWRA-RUST] Storage_Init: {}", path_str);
    match BrowserDB::open(path_str) {
        Ok(db_instance) => {
            let _ = GLOBAL_DB.set(db_instance);
            NS_OK
        }
        Err(e) => {
            eprintln!("[ZAWRA-RUST] Storage_Init with lock failed: {}. Retrying without locking...", e);
            match BrowserDB::open_without_locking(path_str) {
                Ok(db_instance) => {
                    let _ = GLOBAL_DB.set(db_instance);
                    NS_OK
                }
                Err(e2) => {
                    eprintln!("[ZAWRA-RUST] Storage_Init FAILED: {}", e2);
                    NS_ERROR_FAILURE
                }
            }
        },
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// HTTP Cache (RFC 7234)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Store a cache entry.
///
/// # Safety
/// `headers`, `etag` are NUL-terminated strings; `body_ptr` points to
/// `body_len` bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cache_Put(
    url_hash_hi:  u64,
    url_hash_lo:  u64,
    headers:      *const c_char,
    etag:         *const c_char,
    last_mod:     u64,
    body_ptr:     *const u8,
    body_len:     usize,
) -> i32 {
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);

    let headers_str = if headers.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(headers).to_string_lossy().into_owned() }
    };
    let etag_str = if etag.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(etag).to_string_lossy().into_owned() }
    };
    let body = unsafe { std::slice::from_raw_parts(body_ptr, body_len).to_vec() };

    let entry = CacheEntry {
        url_hash,
        headers: headers_str,
        body,
        etag: etag_str,
        last_modified: last_mod as u128,
    };

    match db().cache().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve a cached response body.
///
/// On success writes a heap-allocated buffer pointer to `*out_ptr` and its
/// length to `*out_len`. Free with `Zawra_Free_Buffer`.
///
/// # Safety
/// `out_ptr` and `out_len` must be valid non-null pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cache_Get(
    url_hash_hi: u64,
    url_hash_lo: u64,
    out_ptr:     *mut *mut u8,
    out_len:     *mut usize,
) -> i32 {
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    match db().cache().get(url_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(entry)) => {
            let mut body = entry.body.into_boxed_slice();
            unsafe {
                *out_len = body.len();
                *out_ptr = body.as_mut_ptr();
            }
            std::mem::forget(body);
            NS_OK
        }
    }
}

/// Check whether a URL is present in the cache (fast path — no body copy).
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cache_Has(url_hash_hi: u64, url_hash_lo: u64) -> i32 {
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    match db().cache().get(url_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(_)) => NS_OK,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// IndexedDB / QuotaManager blob storage
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Store a structured-clone blob (IndexedDB PUT / QuotaManager write).
///
/// # Safety
/// `key` is NUL-terminated; `data_ptr` points to `data_len` bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_PutBlob(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
    data_ptr:       *const u8,
    data_len:       usize,
) -> i32 {
    if key.is_null() || data_ptr.is_null() { return NS_ERROR_INVALID_ARG; }

    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };
    let data = unsafe { std::slice::from_raw_parts(data_ptr, data_len) };

    // Encode the blob as base64 to fit in LocalStoreEntry.value
    let mut encoded = String::with_capacity(data_len * 4 / 3 + 4);
    encode_base64_into(data, &mut encoded);

    let entry = LocalStoreEntry { origin_hash, key: key_str, value: encoded };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve a structured-clone blob (IndexedDB GET).
///
/// On success writes a heap-allocated buffer to `*out_ptr`/`*out_len`.
/// Free with `Zawra_Free_Buffer`.
///
/// # Safety
/// `key`, `out_ptr`, `out_len` must be valid non-null pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_GetBlob(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
    out_ptr:        *mut *mut u8,
    out_len:        *mut usize,
) -> i32 {
    if key.is_null() || out_ptr.is_null() || out_len.is_null() {
        return NS_ERROR_INVALID_ARG;
    }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };

    match db().localstore().get(origin_hash, &key_str) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(entry)) => {
            let decoded = match decode_base64(entry.value.as_bytes()) {
                Some(d) => d,
                None => return NS_ERROR_FAILURE,
            };
            let mut boxed = decoded.into_boxed_slice();
            unsafe {
                *out_len = boxed.len();
                *out_ptr = boxed.as_mut_ptr();
            }
            std::mem::forget(boxed);
            NS_OK
        }
    }
}

/// Delete a structured-clone blob (IndexedDB DELETE).
///
/// # Safety
/// `key` must be a valid NUL-terminated string.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_DeleteBlob(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
) -> i32 {
    if key.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };
    match db().localstore().remove(origin_hash, &key_str) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Bookmarks Store
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Bookmark_Put(
    url_hash_hi: u64,
    url_hash_lo: u64,
    url:         *const c_char,
    title:       *const c_char,
    folder:      *const c_char,
) -> i32 {
    if url.is_null() || title.is_null() { return NS_ERROR_INVALID_ARG; }
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    let url_str = unsafe { CStr::from_ptr(url).to_string_lossy().into_owned() };
    let title_str = unsafe { CStr::from_ptr(title).to_string_lossy().into_owned() };
    let folder_str = if folder.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(folder).to_string_lossy().into_owned() }
    };
    eprintln!("[ZAWRA-RUST] Bookmark_Put: {} ({})", url_str, title_str);
    let entry = BookmarkEntry {
        url_hash,
        url: url_str,
        title: title_str,
        folder: folder_str,
        created_at: std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).unwrap().as_secs(),
    };
    match db().bookmarks().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Bookmark_Delete(
    url_hash_hi: u64,
    url_hash_lo: u64,
) -> i32 {
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    match db().bookmarks().delete(url_hash) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Bookmark_GetAll(
    out_buf:        *mut c_char,
    out_buf_len:    usize,
) -> i32 {
    if out_buf.is_null() || out_buf_len == 0 { return NS_ERROR_INVALID_ARG; }
    match db().bookmarks().get_all() {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            let mut combined = String::new();
            for e in entries {
                combined.push_str(&format!("{}|{}|{}\n", e.url, e.title, e.folder));
            }
            let bytes = combined.as_bytes();
            let copy_len = bytes.len().min(out_buf_len - 1);
            unsafe {
                std::ptr::copy_nonoverlapping(bytes.as_ptr() as *const c_char, out_buf, copy_len);
                *out_buf.add(copy_len) = 0;
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Cookie Store
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Store a single cookie.
///
/// # Safety
/// `name`, `value`, `path`, and `domain` must be valid NUL-terminated strings.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_Put(
    domain_hash_hi: u64,
    domain_hash_lo: u64,
    name:           *const c_char,
    value:          *const c_char,
    path:           *const c_char,
    domain:         *const c_char,
    expiry:         u64,
    flags:          u8,
) -> i32 {
    if name.is_null() || value.is_null() { return NS_ERROR_INVALID_ARG; }
    let domain_hash = ((domain_hash_hi as u128) << 64) | (domain_hash_lo as u128);
    let name_str  = unsafe { CStr::from_ptr(name).to_string_lossy().into_owned() };
    let value_str = unsafe { CStr::from_ptr(value).to_string_lossy().into_owned() };
    let path_str = if path.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(path).to_string_lossy().into_owned() }
    };
    let domain_str = if domain.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(domain).to_string_lossy().into_owned() }
    };
    let entry = CookieEntry {
        domain_hash,
        name: name_str,
        value: value_str,
        path: path_str,
        domain: domain_str,
        expiry,
        flags,
    };
    match db().cookies().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve a cookie by domain hash and name.
///
/// On success copies the NUL-terminated value into `out_buf`.
///
/// # Safety
/// `name`, `out_buf` must be valid; `out_buf_len` must be its allocated capacity.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_Get(
    domain_hash_hi: u64,
    domain_hash_lo: u64,
    name:           *const c_char,
    out_buf:        *mut c_char,
    out_buf_len:    usize,
) -> i32 {
    if name.is_null() || out_buf.is_null() || out_buf_len == 0 {
        return NS_ERROR_INVALID_ARG;
    }
    let domain_hash = ((domain_hash_hi as u128) << 64) | (domain_hash_lo as u128);
    let name_str = match unsafe { CStr::from_ptr(name).to_str() } {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };

    match db().cookies().get(domain_hash, &name_str) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(entry)) => {
            let bytes = entry.value.as_bytes();
            let copy_len = bytes.len().min(out_buf_len - 1);
            unsafe {
                std::ptr::copy_nonoverlapping(
                    bytes.as_ptr() as *const c_char,
                    out_buf,
                    copy_len,
                );
                *out_buf.add(copy_len) = 0;
            }
            NS_OK
        }
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_GetForDomain(
    domain_hash_hi: u64,
    domain_hash_lo: u64,
    path:           *const c_char,
    out_buf:        *mut c_char,
    out_buf_len:    usize,
) -> i32 {
    if out_buf.is_null() || out_buf_len == 0 { return NS_ERROR_INVALID_ARG; }
    let domain_hash = ((domain_hash_hi as u128) << 64) | (domain_hash_lo as u128);
    let path_str = if path.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(path).to_string_lossy().into_owned() }
    };
    match db().cookies().get_by_domain(domain_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            let filtered: Vec<&CookieEntry> = if path_str.is_empty() {
                entries.iter().collect()
            } else {
                entries.iter().filter(|e| {
                    e.path.is_empty() || e.path == "/" || path_str.starts_with(&e.path)
                }).collect()
            };
            if filtered.is_empty() { return NS_ERROR_NOT_FOUND; }
            let combined: String = filtered.iter()
                .map(|e| format!("{}={}", e.name, e.value))
                .collect::<Vec<_>>()
                .join("; ");
            let bytes = combined.as_bytes();
            let copy_len = bytes.len().min(out_buf_len - 1);
            unsafe {
                std::ptr::copy_nonoverlapping(bytes.as_ptr() as *const c_char, out_buf, copy_len);
                *out_buf.add(copy_len) = 0;
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
/// Delete all cookies for a domain.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_DeleteForDomain(
    domain_hash_hi: u64,
    domain_hash_lo: u64,
) -> i32 {
    let domain_hash = ((domain_hash_hi as u128) << 64) | (domain_hash_lo as u128);
    match db().cookies().get_by_domain(domain_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            for entry in entries {
                let _ = db().cookies().delete(domain_hash, &entry.name);
            }
            NS_OK
        }
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_Delete(
    domain_hash_hi: u64,
    domain_hash_lo: u64,
    name: *const c_char,
) -> i32 {
    if name.is_null() {
        return NS_ERROR_INVALID_ARG;
    }
    let domain_hash = ((domain_hash_hi as u128) << 64) | (domain_hash_lo as u128);
    let name_str = match unsafe { CStr::from_ptr(name) }.to_str() {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    match db().cookies().delete(domain_hash, name_str) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Cookie_DeleteAll() -> i32 {
    match db().cookies().get_all() {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            for entry in &entries {
                let _ = db().cookies().delete(entry.domain_hash, &entry.name);
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// localStorage / sessionStorage
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Get all localStorage items for an origin, serialized as "key|value\n" lines.
///
/// # Safety
/// `out_buf` must be valid and `out_buf_len` must be its capacity.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_LocalStorage_GetAll(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    out_buf:        *mut c_char,
    out_buf_len:    usize,
) -> i32 {
    if out_buf.is_null() || out_buf_len == 0 { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    match db().localstore().get_by_origin(origin_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            let mut combined = String::new();
            for e in entries {
                combined.push_str(&format!("{}|{}\n", e.key, e.value));
            }
            let bytes = combined.as_bytes();
            let copy_len = bytes.len().min(out_buf_len - 1);
            unsafe {
                std::ptr::copy_nonoverlapping(bytes.as_ptr() as *const c_char, out_buf, copy_len);
                *out_buf.add(copy_len) = 0;
            }
            NS_OK
        }
    }
}

/// Write a localStorage item.
///
/// # Safety
/// `key` and `value` must be valid NUL-terminated strings.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_LocalStorage_Put(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
    value:          *const c_char,
) -> i32 {
    if key.is_null() || value.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };
    let value_str = unsafe { CStr::from_ptr(value).to_string_lossy().into_owned() };


    let entry = LocalStoreEntry {
        origin_hash,
        key:   key_str,
        value: value_str,
    };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Read a localStorage item, copying the NUL-terminated value into `out_buf`.
///
/// # Safety
/// `key`, `out_buf` must be valid; `out_buf_len` must be its capacity.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_LocalStorage_Get(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
    out_buf:        *mut c_char,
    out_buf_len:    usize,
) -> i32 {
    if key.is_null() || out_buf.is_null() || out_buf_len == 0 {
        return NS_ERROR_INVALID_ARG;
    }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };


    match db().localstore().get(origin_hash, &key_str) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(entry)) => {
            let bytes = entry.value.as_bytes();
            let copy_len = bytes.len().min(out_buf_len - 1);
            unsafe {
                std::ptr::copy_nonoverlapping(
                    bytes.as_ptr() as *const c_char,
                    out_buf,
                    copy_len,
                );
                *out_buf.add(copy_len) = 0;
            }
            NS_OK
        }
    }
}
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_LocalStorage_Delete(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    key:            *const c_char,
) -> i32 {
    if key.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let key_str = unsafe { CStr::from_ptr(key).to_string_lossy().into_owned() };

    match db().localstore().remove(origin_hash, &key_str) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_LocalStorage_Clear(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
) -> i32 {
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);

    match db().localstore().clear_origin(origin_hash) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Navigation History
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Increment the visit count for a history entry by `delta`.
///
/// # Safety
/// Caller must ensure hi/lo form a valid URL hash.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_History_Increment(
    url_hash_hi: u64,
    url_hash_lo: u64,
    delta:       i64,
) -> i32 {
    let url_hash = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    match db().history().increment(url_hash, delta) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Record a navigation history entry.
///
/// # Safety
/// `url` and `title` must be valid NUL-terminated strings.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_History_Put(
    url_hash_hi: u64,
    url_hash_lo: u64,
    url:         *const c_char,
    title:       *const c_char,
    timestamp:   u64,
) -> i32 {
    if url.is_null() { return NS_ERROR_INVALID_ARG; }
    let url_hash  = ((url_hash_hi as u128) << 64) | (url_hash_lo as u128);
    let url_str   = unsafe { CStr::from_ptr(url).to_string_lossy().into_owned() };
    let title_str = if title.is_null() { String::new() } else {
        unsafe { CStr::from_ptr(title).to_string_lossy().into_owned() }
    };
    eprintln!("[ZAWRA-RUST] History_Put: {} -> {}", url_str, title_str);
    let entry = HistoryEntry {
        timestamp: timestamp as u128,
        url: url_str,
        url_hash,
        title: title_str,
        visit_count: 1,
    };
    match db().history().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Quota Reporter
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Fill `*stats` with current database statistics.
///
/// # Safety
/// `stats` must be a valid non-null pointer to a `ZawraStorageStats`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_Stats(stats: *mut ZawraStorageStats) -> i32 {
    if stats.is_null() { return NS_ERROR_INVALID_ARG; }
    match db().stats() {
        Err(_) => NS_ERROR_FAILURE,
        Ok(s) => {
            unsafe {
                (*stats) = ZawraStorageStats {
                    total_entries:      s.total_entries,
                    history_entries:    s.history_entries,
                    cookie_entries:     s.cookie_entries,
                    cache_entries:      s.cache_entries,
                    localstore_entries: s.localstore_entries,
                    settings_entries:   s.settings_entries,
                    memory_usage_mb:    s.memory_usage_mb,
                    disk_usage_mb:      s.disk_usage_mb,
                };
            }
            NS_OK
        }
    }
}

/// Wipe ALL storage (panic-mode / "clear site data").
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Storage_Wipe() -> i32 {
    match db().wipe() {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Binary Key-Value Store (IndexedDB backing)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Store a binary value by key.
///
/// # Safety
/// `key` and `value` point to `key_len`/`value_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_IDBStore_Put(
    key_ptr:    *const u8,
    key_len:    usize,
    value_ptr:  *const u8,
    value_len:  usize,
) -> i32 {
    if key_ptr.is_null() || value_ptr.is_null() {
        return NS_ERROR_INVALID_ARG;
    }
    let key = unsafe { std::slice::from_raw_parts(key_ptr, key_len) }.to_vec();
    let value = unsafe { std::slice::from_raw_parts(value_ptr, value_len) }.to_vec();
    match db().binarystore().put(key, value) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve a binary value by key.
///
/// On success writes a heap-allocated buffer to `*out_ptr`/`*out_len`.
/// Free with `Z_Free_Buffer`.
///
/// # Safety
/// `out_ptr` and `out_len` must be valid non-null pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_IDBStore_Get(
    key_ptr:    *const u8,
    key_len:    usize,
    out_ptr:    *mut *mut u8,
    out_len:    *mut usize,
) -> i32 {
    if key_ptr.is_null() || out_ptr.is_null() || out_len.is_null() {
        return NS_ERROR_INVALID_ARG;
    }
    let key = unsafe { std::slice::from_raw_parts(key_ptr, key_len) };
    match db().binarystore().get(key) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(value)) => {
            let mut boxed = value.into_boxed_slice();
            unsafe {
                *out_len = boxed.len();
                *out_ptr = boxed.as_mut_ptr();
            }
            std::mem::forget(boxed);
            NS_OK
        }
    }
}

/// Delete a binary value by key.
///
/// # Safety
/// `key` points to `key_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_IDBStore_Delete(
    key_ptr:    *const u8,
    key_len:    usize,
) -> i32 {
    if key_ptr.is_null() {
        return NS_ERROR_INVALID_ARG;
    }
    let key = unsafe { std::slice::from_raw_parts(key_ptr, key_len) };
    match db().binarystore().delete(key) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Scan all keys/values matching a prefix.
///
/// Serializes results as flat buffer:
///   [key_len:4][key...][value_len:4][value...]
/// repeated for each matching entry.
/// If output buffer overflows, returns NS_ERROR_FAILURE.
///
/// # Safety
/// `prefix` points to `prefix_len` bytes; `out_buf`/`out_buf_len` must be valid.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_IDBStore_ScanPrefix(
    prefix_ptr: *const u8,
    prefix_len: usize,
    out_buf:    *mut u8,
    out_buf_len: usize,
) -> i32 {
    if prefix_ptr.is_null() || out_buf.is_null() || out_buf_len == 0 {
        return NS_ERROR_INVALID_ARG;
    }
    let prefix = unsafe { std::slice::from_raw_parts(prefix_ptr, prefix_len) };
    match db().binarystore().scan_prefix(prefix) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            let mut cursor: usize = 0;
            let buf = unsafe { std::slice::from_raw_parts_mut(out_buf, out_buf_len) };
            for (key, value) in &entries {
                let remaining = out_buf_len - cursor;
                let needed = 8 + key.len() + value.len(); // 4+4 for lengths
                if remaining < needed {
                    return NS_ERROR_FAILURE;
                }
                let key_len_32 = key.len() as u32;
                let val_len_32 = value.len() as u32;
                buf[cursor..cursor+4].copy_from_slice(&key_len_32.to_le_bytes());
                cursor += 4;
                buf[cursor..cursor+key.len()].copy_from_slice(key);
                cursor += key.len();
                buf[cursor..cursor+4].copy_from_slice(&val_len_32.to_le_bytes());
                cursor += 4;
                buf[cursor..cursor+value.len()].copy_from_slice(value);
                cursor += value.len();
            }
            NS_OK
        }
    }
}

/// Clear ALL entries in the binary store.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_IDBStore_Clear() -> i32 {
    // Clear all entries by iterating and deleting each one
    match db().binarystore().all_entries() {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            for (key, _) in &entries {
                let _ = db().binarystore().delete(key);
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Hashing utility
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Hash_String(
    input: *const c_char,
    out_hi: *mut u64,
    out_lo: *mut u64,
) {
    if input.is_null() || out_hi.is_null() || out_lo.is_null() { return; }
    let s = unsafe { CStr::from_ptr(input).to_bytes() };
    let mut hash: u128 = 0x6c62272e07bb014262b821756295c58d;
    for &b in s {
        hash ^= b as u128;
        hash = hash.wrapping_mul(0x1000000000000000000013b);
    }
    unsafe {
        *out_hi = (hash >> 64) as u64;
        *out_lo = hash as u64;
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Memory management
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Free a buffer previously returned by `Zawra_Cache_Get` or
/// `Zawra_Storage_GetBlob`.
///
/// # Safety
/// `ptr` and `len` must match a previously returned buffer.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Free_Buffer(ptr: *mut u8, len: usize) {
    if !ptr.is_null() && len > 0 {
        unsafe { let _ = Vec::from_raw_parts(ptr, len, len); }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// NetworkCache KV Store (via BinaryStore with 0xCA namespace)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const CACHE_NAMESPACE: u8 = 0xCA;

fn cache_key(hash: &[u8]) -> Vec<u8> {
    let mut key = Vec::with_capacity(1 + hash.len());
    key.push(CACHE_NAMESPACE);
    key.extend_from_slice(hash);
    key
}

/// Store a cache record by SHA1 hash.
///
/// # Safety
/// `hash_ptr`/`data_ptr` must point to `hash_len`/`data_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_CacheStore_Store(
    hash_ptr: *const u8,
    hash_len: usize,
    data_ptr: *const u8,
    data_len: usize,
) -> i32 {
    if hash_ptr.is_null() || data_ptr.is_null() || hash_len != 20 {
        return NS_ERROR_INVALID_ARG;
    }
    let hash = unsafe { std::slice::from_raw_parts(hash_ptr, hash_len) };
    let data = unsafe { std::slice::from_raw_parts(data_ptr, data_len) };
    let key = cache_key(hash);
    match db().binarystore().put(key, data.to_vec()) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve a cache record by SHA1 hash.
///
/// On success writes a heap-allocated buffer to `*out_ptr`/`*out_len`.
/// Free with `Z_Free_Buffer`.
///
/// # Safety
/// `out_ptr`/`out_len` must be valid non-null pointers.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_CacheStore_Retrieve(
    hash_ptr: *const u8,
    hash_len: usize,
    out_ptr: *mut *mut u8,
    out_len: *mut usize,
) -> i32 {
    if hash_ptr.is_null() || out_ptr.is_null() || out_len.is_null() || hash_len != 20 {
        return NS_ERROR_INVALID_ARG;
    }
    let hash = unsafe { std::slice::from_raw_parts(hash_ptr, hash_len) };
    let key = cache_key(hash);
    match db().binarystore().get(&key) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => NS_ERROR_NOT_FOUND,
        Ok(Some(value)) => {
            let mut boxed = value.into_boxed_slice();
            unsafe {
                *out_len = boxed.len();
                *out_ptr = boxed.as_mut_ptr();
            }
            std::mem::forget(boxed);
            NS_OK
        }
    }
}

/// Delete a cache record by SHA1 hash.
///
/// # Safety
/// `hash_ptr` must point to `hash_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_CacheStore_Delete(
    hash_ptr: *const u8,
    hash_len: usize,
) -> i32 {
    if hash_ptr.is_null() || hash_len != 20 {
        return NS_ERROR_INVALID_ARG;
    }
    let hash = unsafe { std::slice::from_raw_parts(hash_ptr, hash_len) };
    let key = cache_key(hash);
    match db().binarystore().delete(&key) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Clear all cache entries.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_CacheStore_Clear() -> i32 {
    let prefix = [CACHE_NAMESPACE];
    match db().binarystore().scan_prefix(&prefix) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            for (key, _) in &entries {
                let _ = db().binarystore().delete(key);
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// WebSQL BrowserDB bridge
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Open (or create) a WebSQL database via BrowserDB localstore.
///
/// Stores database metadata at key "ws:meta:<origin>:<db_name>".
///
/// # Safety
/// `db_name` must point to `db_name_len` valid UTF-8 bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_Open(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    db_name: *const c_char,
    db_name_len: u32,
    version: i32,
) -> i32 {
    if db_name.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let name = match unsafe { CStr::from_ptr(db_name).to_str() } {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let key = format!("ws:meta:{}:{}", origin_hash, name);
    let value = version.to_string();
    let entry = LocalStoreEntry {
        origin_hash,
        key,
        value,
    };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Close a WebSQL database (no-op, data persists in BrowserDB).
///
/// # Safety
/// `db_name` must point to `db_name_len` valid UTF-8 bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_Close(
    _origin_hash_hi: u64,
    _origin_hash_lo: u64,
    _db_name: *const c_char,
    _db_name_len: u32,
) -> i32 {
    NS_OK
}

/// Execute SQL against a WebSQL database.
///
/// For now, returns an empty JSON array `[]` as the result.
/// Full SQL execution would require a SQL parser.
///
/// # Safety
/// `db_name` and `sql` must point to valid UTF-8 bytes.
/// `result_buf` must have `result_buf_len` bytes of capacity.
/// `result_written` must be a valid pointer.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_ExecSQL(
    _origin_hash_hi: u64,
    _origin_hash_lo: u64,
    _db_name: *const c_char,
    _db_name_len: u32,
    _sql: *const c_char,
    _sql_len: u32,
    result_buf: *mut u8,
    result_buf_len: u32,
    result_written: *mut u32,
) -> i32 {
    if result_buf.is_null() || result_written.is_null() { return NS_ERROR_INVALID_ARG; }
    let empty = b"[]";
    let len = std::cmp::min(empty.len(), result_buf_len as usize);
    unsafe {
        std::ptr::copy_nonoverlapping(empty.as_ptr(), result_buf, len);
        *result_written = len as u32;
    }
    NS_OK
}

/// Get the stored version for a WebSQL database.
///
/// Returns the version as an i32, or -1 if not found.
///
/// # Safety
/// `db_name` must point to `db_name_len` valid UTF-8 bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_GetVersion(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    db_name: *const c_char,
    db_name_len: u32,
) -> i32 {
    if db_name.is_null() { return -1; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let name = match unsafe { CStr::from_ptr(db_name).to_str() } {
        Ok(s) => s,
        Err(_) => return -1,
    };
    let key = format!("ws:meta:{}:{}", origin_hash, name);
    match db().localstore().get(origin_hash, &key) {
        Ok(Some(entry)) => {
            entry.value.parse::<i32>().unwrap_or(-1)
        }
        _ => -1,
    }
}

/// Set the version for a WebSQL database.
///
/// # Safety
/// `db_name` must point to `db_name_len` valid UTF-8 bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_SetVersion(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    db_name: *const c_char,
    db_name_len: u32,
    version: i32,
) -> i32 {
    if db_name.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let name = match unsafe { CStr::from_ptr(db_name).to_str() } {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let key = format!("ws:meta:{}:{}", origin_hash, name);
    let value = version.to_string();
    let entry = LocalStoreEntry {
        origin_hash,
        key,
        value,
    };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Delete a WebSQL database and all its data.
///
/// # Safety
/// `db_name` must point to `db_name_len` valid UTF-8 bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_WebSQL_DeleteDatabase(
    origin_hash_hi: u64,
    origin_hash_lo: u64,
    db_name: *const c_char,
    db_name_len: u32,
) -> i32 {
    if db_name.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hash_hi as u128) << 64) | (origin_hash_lo as u128);
    let name = match unsafe { CStr::from_ptr(db_name).to_str() } {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let key = format!("ws:meta:{}:{}", origin_hash, name);
    match db().localstore().remove(origin_hash, &key) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ApplicationCache Bridge (deprecated window.applicationCache API)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Store an application cache manifest.
///
/// # Safety
/// `manifest_url` must point to `manifest_url_len` valid UTF-8 bytes.
/// `manifest_data` must point to `manifest_data_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_AppCache_StoreManifest(
    origin_hi: u64, origin_lo: u64,
    manifest_url: *const u8, manifest_url_len: u32,
    manifest_data: *const u8, manifest_data_len: u32,
) -> i32 {
    if manifest_url.is_null() || manifest_data.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hi as u128) << 64) | (origin_lo as u128);
    let url = match std::str::from_utf8(unsafe { std::slice::from_raw_parts(manifest_url, manifest_url_len as usize) }) {
        Ok(s) => s.to_owned(),
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let data = unsafe { std::slice::from_raw_parts(manifest_data, manifest_data_len as usize) };
    let encoded = {
        let mut s = String::with_capacity(data.len() * 4 / 3 + 4);
        encode_base64_into(data, &mut s);
        s
    };
    let key = format!("ac:manifest:{}", url);
    let entry = LocalStoreEntry { origin_hash, key, value: encoded };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve an application cache manifest.
///
/// On success copies the manifest data into `result_buf`.
///
/// # Safety
/// `manifest_url` must point to `manifest_url_len` valid UTF-8 bytes.
/// `result_buf` must have `result_buf_len` bytes of capacity.
/// `result_written` must be a valid pointer.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_AppCache_GetManifest(
    origin_hi: u64, origin_lo: u64,
    manifest_url: *const u8, manifest_url_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32 {
    if manifest_url.is_null() || result_buf.is_null() || result_written.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hi as u128) << 64) | (origin_lo as u128);
    let url = match std::str::from_utf8(unsafe { std::slice::from_raw_parts(manifest_url, manifest_url_len as usize) }) {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let key = format!("ac:manifest:{}", url);
    match db().localstore().get(origin_hash, &key) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => {
            unsafe { *result_written = 0; }
            NS_ERROR_NOT_FOUND
        }
        Ok(Some(entry)) => {
            let decoded = match decode_base64(entry.value.as_bytes()) {
                Some(d) => d,
                None => return NS_ERROR_FAILURE,
            };
            let len = std::cmp::min(decoded.len(), result_buf_len as usize);
            unsafe {
                std::ptr::copy_nonoverlapping(decoded.as_ptr(), result_buf, len);
                *result_written = len as u32;
            }
            NS_OK
        }
    }
}

/// Store an application cache resource.
///
/// # Safety
/// `resource_url` must point to `resource_url_len` valid UTF-8 bytes.
/// `resource_data` must point to `resource_data_len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_AppCache_StoreResource(
    origin_hi: u64, origin_lo: u64,
    resource_url: *const u8, resource_url_len: u32,
    resource_data: *const u8, resource_data_len: u32,
) -> i32 {
    if resource_url.is_null() || resource_data.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hi as u128) << 64) | (origin_lo as u128);
    let url = match std::str::from_utf8(unsafe { std::slice::from_raw_parts(resource_url, resource_url_len as usize) }) {
        Ok(s) => s.to_owned(),
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let data = unsafe { std::slice::from_raw_parts(resource_data, resource_data_len as usize) };
    let encoded = {
        let mut s = String::with_capacity(data.len() * 4 / 3 + 4);
        encode_base64_into(data, &mut s);
        s
    };
    let key = format!("ac:resource:{}", url);
    let entry = LocalStoreEntry { origin_hash, key, value: encoded };
    match db().localstore().insert(&entry) {
        Ok(_) => NS_OK,
        Err(_) => NS_ERROR_FAILURE,
    }
}

/// Retrieve an application cache resource.
///
/// On success copies the resource data into `result_buf`.
///
/// # Safety
/// `resource_url` must point to `resource_url_len` valid UTF-8 bytes.
/// `result_buf` must have `result_buf_len` bytes of capacity.
/// `result_written` must be a valid pointer.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_AppCache_GetResource(
    origin_hi: u64, origin_lo: u64,
    resource_url: *const u8, resource_url_len: u32,
    result_buf: *mut u8, result_buf_len: u32,
    result_written: *mut u32,
) -> i32 {
    if resource_url.is_null() || result_buf.is_null() || result_written.is_null() { return NS_ERROR_INVALID_ARG; }
    let origin_hash = ((origin_hi as u128) << 64) | (origin_lo as u128);
    let url = match std::str::from_utf8(unsafe { std::slice::from_raw_parts(resource_url, resource_url_len as usize) }) {
        Ok(s) => s,
        Err(_) => return NS_ERROR_INVALID_ARG,
    };
    let key = format!("ac:resource:{}", url);
    match db().localstore().get(origin_hash, &key) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(None) => {
            unsafe { *result_written = 0; }
            NS_ERROR_NOT_FOUND
        }
        Ok(Some(entry)) => {
            let decoded = match decode_base64(entry.value.as_bytes()) {
                Some(d) => d,
                None => return NS_ERROR_FAILURE,
            };
            let len = std::cmp::min(decoded.len(), result_buf_len as usize);
            unsafe {
                std::ptr::copy_nonoverlapping(decoded.as_ptr(), result_buf, len);
                *result_written = len as u32;
            }
            NS_OK
        }
    }
}

/// Delete all application cache data for an origin.
///
/// # Safety
/// `origin_hi` and `origin_lo` must form a valid origin hash.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_AppCache_DeleteOrigin(
    origin_hi: u64, origin_lo: u64,
) -> i32 {
    let origin_hash = ((origin_hi as u128) << 64) | (origin_lo as u128);
    match db().localstore().get_by_origin(origin_hash) {
        Err(_) => NS_ERROR_FAILURE,
        Ok(entries) => {
            for entry in entries {
                if entry.key.starts_with("ac:manifest:") || entry.key.starts_with("ac:resource:") {
                    let _ = db().localstore().remove(origin_hash, &entry.key);
                }
            }
            NS_OK
        }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Internal: minimal base64 (no external dependency)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const BASE64_CHARS: &[u8] =
    b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

fn encode_base64_into(data: &[u8], out: &mut String) {
    for chunk in data.chunks(3) {
        let b0 = chunk[0] as u32;
        let b1 = if chunk.len() > 1 { chunk[1] as u32 } else { 0 };
        let b2 = if chunk.len() > 2 { chunk[2] as u32 } else { 0 };
        let c = (b0 << 16) | (b1 << 8) | b2;
        out.push(BASE64_CHARS[((c >> 18) & 63) as usize] as char);
        out.push(BASE64_CHARS[((c >> 12) & 63) as usize] as char);
        out.push(if chunk.len() > 1 { BASE64_CHARS[((c >> 6) & 63) as usize] as char } else { '=' });
        out.push(if chunk.len() > 2 { BASE64_CHARS[(c & 63) as usize] as char } else { '=' });
    }
}

fn decode_base64(data: &[u8]) -> Option<Vec<u8>> {
    fn v(c: u8) -> Option<u32> {
        match c {
            b'A'..=b'Z' => Some((c - b'A') as u32),
            b'a'..=b'z' => Some((c - b'a' + 26) as u32),
            b'0'..=b'9' => Some((c - b'0' + 52) as u32),
            b'+' => Some(62),
            b'/' => Some(63),
            b'=' => Some(0),
            _ => None,
        }
    }
    if data.len() % 4 != 0 { return None; }
    let mut out = Vec::with_capacity(data.len() * 3 / 4);
    for chunk in data.chunks(4) {
        let a = v(chunk[0])? ; let b = v(chunk[1])?;
        let c = v(chunk[2])? ; let d = v(chunk[3])?;
        let w = (a << 18) | (b << 12) | (c << 6) | d;
        out.push(((w >> 16) & 0xff) as u8);
        if chunk[2] != b'=' { out.push(((w >> 8) & 0xff) as u8); }
        if chunk[3] != b'=' { out.push((w & 0xff) as u8); }
    }
    Some(out)
}
