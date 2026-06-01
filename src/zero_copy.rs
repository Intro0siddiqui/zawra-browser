use crate::javascriptcore::jsapi::{JSContext, JSObject, JS_NewExternalArrayBuffer};
use std::ptr;

/// A Rust function defined elsewhere that manages the lifecycle of BrowserDB pins.
unsafe extern "Rust" {
    fn release_browserdb_pin(blob_id: u64);
}

/// Custom deleter for external array buffers.
/// Standardized on `blob_id` approach to avoid Rust ABI issues and safely
/// manage memory reclamation across the FFI boundary.
unsafe extern "C" fn browserdb_buffer_deleter(
    _contents: *mut libc::c_void,
    user_data: *mut libc::c_void,
) {
    if !user_data.is_null() {
        // Fix for Problem 1: Reclaim the Box from the raw pointer.
        // This ensures that the memory allocated by Rust's Box is freed
        // using Rust's allocator, not libc::free, preventing heap corruption.
        let blob_id_ptr = user_data as *mut u64;
        
        // SAFETY: We previously allocated this as a Box<u64>
        let blob_id = unsafe { *Box::from_raw(blob_id_ptr) };

        // Fix for Problem 2: Call the Rust registry function to release the pin.
        // We use the raw u64 blob_id for simplicity and ABI safety.
        unsafe { release_browserdb_pin(blob_id) };
    }
}

/// Surgical function to map BrowserDB memory directly to JS.
///
/// # Arguments
/// * `cx` - The JS context.
/// * `data_ptr` - Pointer to the raw BrowserDB memory.
/// * `size` - Size of the memory region.
/// * `blob_id` - Unique identifier for the blob in BrowserDB, used for pinning.
pub unsafe fn create_zero_copy_buffer(
    cx: *mut JSContext,
    data_ptr: *mut u8,
    size: usize,
    blob_id: u64,
) -> *mut JSObject {
    // We box the blob_id to pass it as user_data. This memory will be
    // managed by our browserdb_buffer_deleter to ensure allocator consistency.
    let user_data = Box::into_raw(Box::new(blob_id)) as *mut libc::c_void;

    // Map BrowserDB memory directly to JS via an ExternalArrayBuffer.
    // This eliminates copying overhead but requires careful lifecycle management.
    // SAFETY: JS_NewExternalArrayBuffer expects a valid data pointer and deleter.
    unsafe {
        JS_NewExternalArrayBuffer(
            cx,
            size,
            data_ptr as *mut libc::c_void,
            Some(browserdb_buffer_deleter),
            user_data,
        )
    }
}
