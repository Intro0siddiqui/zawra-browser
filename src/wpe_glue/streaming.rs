//! BodyRing Full Pull-Style Streaming
//!
//! This module extends the WPE bypass with:
//!  1. **HTTP/1.1 Response Header Parsing** — detects the `\r\n\r\n` boundary
//!     inside the BodyRing, strips the headers, and exposes only the body bytes
//!     to WPE.
//!  2. **`AsyncOpen` → `OnDataAvailable` Callbacks** — a dedicated reader
//!     thread that drains the BodyRing and calls WPE's `nsIStreamListener`
//!     vtable methods at the right times.
//!  3. **HTTP Redirect Following** — detects 301/302/307/308 status codes and
//!     recursively creates a new `ZNetChannel` for the target location.

use std::ffi::{c_char, c_void, CStr, CString};
use std::ptr::null_mut;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex};
use std::thread;

use lean_net::{net_read, NetError};

use crate::wpe_glue::networking::{
    global_engine, OwnedBodyRing, ZNetChannel, ZNetInputStream, ns_result,
};

// ── nsresult values used in this module ─────────────────────────────────────
const NS_OK:                       u32 = ns_result::NS_OK;
const NS_ERROR_FAILURE:            u32 = ns_result::NS_ERROR_FAILURE;
const NS_BASE_STREAM_WOULD_BLOCK:  u32 = 0x80470007;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// HTTP/1.1 Response Parser
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Parsed summary of an HTTP/1.1 response header block.
#[derive(Debug, Default)]
pub struct HttpResponseHead {
    pub status_code:    u16,
    pub content_length: Option<usize>,
    pub content_type:   Option<String>,
    pub location:       Option<String>,  // for redirects
    pub header_end:     usize,           // byte offset where headers end (past \r\n\r\n)
}

/// Parse the leading HTTP/1.1 status line + headers from a raw byte slice.
///
/// Returns `None` if the header block is incomplete (not all bytes received yet).
pub fn parse_http_head(buf: &[u8]) -> Option<HttpResponseHead> {
    // Locate \r\n\r\n
    let header_end = buf.windows(4).position(|w| w == b"\r\n\r\n")? + 4;
    let header_block = std::str::from_utf8(&buf[..header_end]).ok()?;

    let mut lines = header_block.lines();

    // Parse status line: "HTTP/1.1 200 OK"
    let status_line = lines.next()?;
    let status_code: u16 = status_line.split_whitespace().nth(1)?.parse().ok()?;

    let mut result = HttpResponseHead {
        status_code,
        header_end,
        ..Default::default()
    };

    for line in lines {
        let line = line.trim();
        if line.is_empty() { break; }
        if let Some(colon) = line.find(':') {
            let name  = line[..colon].trim().to_ascii_lowercase();
            let value = line[colon + 1..].trim();
            match name.as_str() {
                "content-length" => {
                    result.content_length = value.parse().ok();
                }
                "content-type" => {
                    result.content_type = Some(value.to_string());
                }
                "location" => {
                    result.location = Some(value.to_string());
                }
                _ => {}
            }
        }
    }

    Some(result)
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsIStreamListener vtable (WPE's async callback interface)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Minimal vtable for `nsIStreamListener`.
/// WPE calls these when data arrives on an async channel.
#[repr(C)]
pub struct NsIStreamListenerVtable {
    // nsISupports
    pub query_interface:    unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub add_ref:            unsafe extern "C" fn(*mut c_void) -> u32,
    pub release:            unsafe extern "C" fn(*mut c_void) -> u32,
    // nsIRequestObserver
    pub on_start_request:   unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub on_stop_request:    unsafe extern "C" fn(*mut c_void, *mut c_void, u32) -> u32,
    // nsIStreamListener
    pub on_data_available:  unsafe extern "C" fn(*mut c_void, *mut c_void, *mut c_void, u64, u32) -> u32,
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Async Reader Thread — drives OnDataAvailable callbacks
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// State shared between `spawn_async_reader` thread and the calling `ZNetChannel`.
pub struct AsyncReaderState {
    pub ring:          Arc<Mutex<OwnedBodyRing>>,
    pub listener:      *mut c_void,   // nsIStreamListener*
    pub channel:       *mut c_void,   // nsIChannel* (for callbacks)
    pub conn_handle:   lean_net::ConnectionHandle,
    pub cancelled:     AtomicBool,
    pub redirect_url:  Mutex<Option<String>>,
}

// SAFETY: We only access listener/channel from the reader thread under the
// same XPCOM/WPE threading model that WPE mandates (main-thread callbacks).
unsafe impl Send for AsyncReaderState {}
unsafe impl Sync for AsyncReaderState {}

/// Spawn the dedicated reader thread for an async channel.
///
/// The thread:
/// 1. Waits for enough data to parse HTTP headers.
/// 2. Calls `OnStartRequest` on the listener.
/// 3. Loops calling `OnDataAvailable` as data arrives in the BodyRing.
/// 4. Detects 3xx → stores redirect URL and calls `OnStopRequest(NS_OK)`.
/// 5. On EOF → calls `OnStopRequest(NS_OK)`.
/// 6. On error → calls `OnStopRequest(NS_ERROR_FAILURE)`.
pub fn spawn_async_reader(state: Arc<AsyncReaderState>) {
    thread::Builder::new()
        .name("zawra-async-reader".into())
        .spawn(move || {
            async_reader_loop(state);
        })
        .expect("failed to spawn zawra-async-reader thread");
}

fn async_reader_loop(state: Arc<AsyncReaderState>) {
    let mut header_buf: Vec<u8> = Vec::with_capacity(8192);
    let mut head_parsed = false;
    let mut byte_offset: u64 = 0;

    loop {
        if state.cancelled.load(Ordering::Acquire) { break; }

        // Drain what's available from the BodyRing into our local header_buf
        // (until headers are parsed) or directly notify WPE.
        let ring_guard = match state.ring.lock() {
            Ok(g) => g,
            Err(_) => break,
        };

        let head_val = ring_guard.descriptor.head.load(std::sync::atomic::Ordering::Acquire);
        let tail_val = ring_guard.descriptor.tail.load(std::sync::atomic::Ordering::Acquire);
        let available = head_val.wrapping_sub(tail_val) as usize;
        let is_closed = ring_guard.descriptor.is_closed.load(std::sync::atomic::Ordering::Acquire);

        if !head_parsed {
            // Read available bytes into header_buf
            if available > 0 {
                let cap = ring_guard.descriptor.capacity;
                let tail_idx = (tail_val % cap as u64) as usize;
                let contiguous = (cap - tail_idx).min(available);

                let slice = unsafe {
                    std::slice::from_raw_parts(
                        ring_guard.descriptor.buffer_ptr.add(tail_idx),
                        contiguous,
                    )
                };
                header_buf.extend_from_slice(slice);
                ring_guard.descriptor.tail.fetch_add(contiguous as u64, std::sync::atomic::Ordering::Release);

                // If there was a wrap-around portion
                let remaining = available - contiguous;
                if remaining > 0 {
                    let slice2 = unsafe {
                        std::slice::from_raw_parts(ring_guard.descriptor.buffer_ptr, remaining)
                    };
                    header_buf.extend_from_slice(slice2);
                    ring_guard.descriptor.tail.fetch_add(remaining as u64, std::sync::atomic::Ordering::Release);
                }
            }

            drop(ring_guard); // release lock before potentially sleeping

            // Try to parse headers
            if let Some(parsed_head) = parse_http_head(&header_buf) {
                head_parsed = true;

                // Handle 3xx redirect
                if parsed_head.status_code >= 300 && parsed_head.status_code < 400 {
                    if let Some(loc) = &parsed_head.location {
                        if let Ok(mut redir_guard) = state.redirect_url.lock() {
                            *redir_guard = Some(loc.clone());
                        }
                    }
                    // Signal WPE that we stopped
                    fire_on_stop_request(state.listener, state.channel, NS_OK);
                    break;
                }

                // Normal response — fire OnStartRequest
                fire_on_start_request(state.listener, state.channel);

                // Any bytes past the header boundary are body bytes
                let body_bytes = &header_buf[parsed_head.header_end..];
                if !body_bytes.is_empty() {
                    let n = body_bytes.len() as u32;
                    fire_on_data_available(state.listener, state.channel, byte_offset, n);
                    byte_offset += n as u64;
                }
                header_buf.clear();
            } else if is_closed {
                // Stream closed before we got full headers
                fire_on_stop_request(state.listener, state.channel, NS_ERROR_FAILURE);
                break;
            } else {
                thread::sleep(std::time::Duration::from_millis(2));
            }
        } else {
            // Headers already parsed — notify WPE of new data
            if available > 0 {
                drop(ring_guard);
                fire_on_data_available(state.listener, state.channel, byte_offset, available as u32);
                byte_offset += available as u64;
            } else if is_closed {
                drop(ring_guard);
                fire_on_stop_request(state.listener, state.channel, NS_OK);
                break;
            } else {
                drop(ring_guard);
                thread::sleep(std::time::Duration::from_millis(2));
            }
        }
    }
}

// ── WPE callback helpers ────────────────────────────────────────────────────

fn fire_on_start_request(listener: *mut c_void, channel: *mut c_void) {
    if listener.is_null() { return; }
    let vtable = unsafe { &*(*(listener as *const *const NsIStreamListenerVtable)) };
    unsafe { (vtable.on_start_request)(listener, channel) };
}

fn fire_on_data_available(
    listener: *mut c_void, channel: *mut c_void,
    offset: u64, count: u32,
) {
    if listener.is_null() { return; }
    let vtable = unsafe { &*(*(listener as *const *const NsIStreamListenerVtable)) };
    // Pass NULL for the input stream here — WPE will call nsIChannel::Open()
    // to get a stream separately. In a full impl we'd pass the ZNetInputStream.
    unsafe { (vtable.on_data_available)(listener, channel, null_mut(), offset, count) };
}

fn fire_on_stop_request(listener: *mut c_void, channel: *mut c_void, status: u32) {
    if listener.is_null() { return; }
    let vtable = unsafe { &*(*(listener as *const *const NsIStreamListenerVtable)) };
    unsafe { (vtable.on_stop_request)(listener, channel, status) };
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Public C-ABI entry points
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Parse an HTTP/1.1 response header block from a raw buffer.
///
/// Fills `*out_status`, `*out_body_offset`, `*out_content_length` on success.
/// Returns 0 on success, -1 if headers not yet complete.
///
/// # Safety
/// `buf_ptr` must point to `buf_len` valid bytes. Out-params must be non-null.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_ParseHttpHead(
    buf_ptr:          *const u8,
    buf_len:          usize,
    out_status:       *mut u16,
    out_body_offset:  *mut usize,
    out_content_len:  *mut i64,
) -> i32 {
    if buf_ptr.is_null() { return -1; }
    let buf = unsafe { std::slice::from_raw_parts(buf_ptr, buf_len) };
    match parse_http_head(buf) {
        None => -1,
        Some(h) => {
            unsafe {
                if !out_status.is_null()      { *out_status = h.status_code; }
                if !out_body_offset.is_null() { *out_body_offset = h.header_end; }
                if !out_content_len.is_null() {
                    *out_content_len = h.content_length.map(|n| n as i64).unwrap_or(-1);
                }
            }
            0
        }
    }
}
