//! JavaScriptCore Zero-Copy ArrayBuffer Integration
//!
//! This module surgically maps BrowserDB-resident memory (cache blobs, IndexedDB
//! values) directly into JavaScriptCore's heap as `ArrayBuffer` objects without
//! any data copy.
//!
//! ## How It Works
//!
//! 1. BrowserDB returns a raw pointer + length for a cached blob.
//! 2. We call `JS_NewExternalArrayBuffer(cx, size, ptr, deleter, user_data)`.
//! 3. JavaScriptCore uses the buffer in-place — no memcpy.
//! 4. When the JS GC collects the `ArrayBuffer`, it calls our `deleter` which
//!    decrements the BrowserDB pin and allows the memory to be reclaimed.
//!
//! ## Pin Registry
//!
//! BrowserDB blobs that are "pinned" (live inside a JS ArrayBuffer) must not
//! be freed by the compaction thread.  We maintain a global `DashMap<u64, Arc<Vec<u8>>>`
//! that holds `Arc` references to keep the buffer alive until JS is done.

use std::collections::HashMap;
use std::ffi::c_void;
use std::sync::{Mutex, OnceLock};

use crate::javascriptcore::jsapi::{JSContext, JSObject, JS_NewExternalArrayBuffer};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Pin registry — keeps BrowserDB blobs alive while JavaScriptCore uses them
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Global registry of pinned blobs. Key = `blob_id`, value = owned buffer.
static PIN_REGISTRY: OnceLock<Mutex<HashMap<u64, Vec<u8>>>> = OnceLock::new();

fn pin_registry() -> &'static Mutex<HashMap<u64, Vec<u8>>> {
    PIN_REGISTRY.get_or_init(|| Mutex::new(HashMap::new()))
}

/// Pin a blob buffer so it won't be freed while JavaScriptCore holds it.
/// Returns the `blob_id` to pass as `user_data` to the ArrayBuffer deleter.
pub fn pin_blob(blob_id: u64, data: Vec<u8>) {
    if let Ok(mut reg) = pin_registry().lock() {
        reg.insert(blob_id, data);
    }
}

/// Release a blob pin — called by the JavaScriptCore GC deleter.
/// This is the concrete implementation of the `extern "Rust"` declaration in
/// `zero_copy.rs`.
pub fn release_pin(blob_id: u64) {
    if let Ok(mut reg) = pin_registry().lock() {
        reg.remove(&blob_id);
    }
}

/// Required by the `extern "Rust" { fn release_browserdb_pin(blob_id: u64); }`
/// declaration in `zero_copy.rs`.
#[unsafe(no_mangle)]
pub unsafe extern "Rust" fn release_browserdb_pin(blob_id: u64) {
    release_pin(blob_id);
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Custom deleter — called by JavaScriptCore GC
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// JavaScriptCore calls this when the `ArrayBuffer` is GC'd.
/// `_contents` is the buffer pointer (we don't use it — the Vec owns the data).
/// `user_data` is a heap-allocated `Box<u64>` containing the `blob_id`.
unsafe extern "C" fn browserdb_gc_deleter(
    _contents: *mut c_void,
    user_data: *mut c_void,
) {
    if !user_data.is_null() {
        // Reclaim the Box<u64> we allocated in `create_zero_copy_buffer`.
        let blob_id = unsafe { *Box::from_raw(user_data as *mut u64) };
        release_pin(blob_id);
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Public API
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Map a BrowserDB blob directly into JavaScriptCore as an `ArrayBuffer`
/// without copying.
///
/// ## Arguments
/// - `cx`       — The active `JSContext`.
/// - `data`     — Owned `Vec<u8>` of the blob bytes (will be pinned).
/// - `blob_id`  — Unique ID used to unpin when the GC collects the buffer.
///
/// ## Returns
/// A `*mut JSObject` pointing to a `JS::ArrayBuffer`, or `null` on failure.
/// The returned object's memory is owned by JavaScriptCore; the underlying
/// bytes are owned by Rust's pin registry until GC release.
///
/// # Safety
/// `cx` must be a valid JavaScriptCore `JSContext` on the current thread.
pub unsafe fn create_zero_copy_buffer(
    cx: *mut JSContext,
    mut data: Vec<u8>,
    blob_id: u64,
) -> *mut JSObject {
    let size = data.len();
    let ptr  = data.as_mut_ptr();

    // Pin first — JavaScriptCore might GC before we return if we pin after.
    pin_blob(blob_id, data);

    // Heap-allocate the blob_id for user_data (freed in browserdb_gc_deleter).
    let user_data = Box::into_raw(Box::new(blob_id)) as *mut c_void;

    unsafe {
        JS_NewExternalArrayBuffer(
            cx,
            size,
            ptr as *mut c_void,
            Some(browserdb_gc_deleter),
            user_data,
        )
    }
}

/// C-ABI version — WPE's IndexedDB / Cache API C++ layer can call this
/// directly to obtain an `ArrayBuffer*` from a BrowserDB cache entry.
///
/// Returns `null` if BrowserDB doesn't have the entry or WPE is headless.
///
/// # Safety
/// `cx` must be a valid `JSContext*`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_JS_CreateCacheBuffer(
    cx:          *mut JSContext,
    url_hash_hi: u64,
    url_hash_lo: u64,
) -> *mut JSObject {
    use crate::wpe_glue::storage::Zawra_Cache_Get;
    use std::ptr::null_mut;

    if cx.is_null() { return null_mut(); }

    let mut out_ptr: *mut u8 = null_mut();
    let mut out_len: usize   = 0;

    let ret = unsafe { Zawra_Cache_Get(url_hash_hi, url_hash_lo, &mut out_ptr, &mut out_len) };
    if ret != 0 || out_ptr.is_null() { return null_mut(); }

    // Reconstruct the Box<[u8]> that Zawra_Cache_Get leaked (see storage.rs).
    // Must reconstruct as the same kind of allocation — Box<[u8]>, not
    // Vec<u8> — to keep the allocator Layout consistent. create_zero_copy_buffer
    // takes a Vec<u8> by value but only reads its length and pointer, so it
    // is safe to pass it a Vec that wraps a Box<[u8]>'s data.
    let data = unsafe {
        let slice = std::ptr::slice_from_raw_parts_mut(out_ptr, out_len);
        Box::from_raw(slice).into_vec()
    };

    // Use a hash of the URL as the blob_id
    let blob_id = ((url_hash_hi as u128) << 64 | url_hash_lo as u128) as u64;

    unsafe { create_zero_copy_buffer(cx, data, blob_id) }
}
