//! Zawra WPE Networking Bypass — Networking Glue
//!
//! This module replaces WPE's built-in networking stack with `z-net`
//! (lean-net). It achieves this by defining the binary-compatible
//! vtable layouts for:
//!
//!   - `nsISupports`          – ref-counting base
//!   - `nsIInputStream`       – readable byte stream (backed by BodyRing)
//!   - `nsIChannel`           – a single network request
//!   - `nsIProtocolHandler`   – factory that constructs channels for a URI scheme
//!
//! The C-ABI entry points at the bottom of this file are what WPE calls
//! through its component-manager after we register our factory.

use std::ffi::{CStr, CString, c_char, c_void};
use std::ptr::null_mut;
use std::sync::atomic::{AtomicBool, AtomicI32, AtomicI64, AtomicU32, AtomicU64, Ordering};
use std::sync::{Arc, Mutex, OnceLock};
use std::thread;

use lean_net::{
    BodyRingDescriptor, ConnectionHandle, NetEngineHandle, NetError, net_body_ring_register,
    net_body_ring_unregister, net_close, net_conn_bind_body_ring, net_connect, net_engine_create, net_poll, net_write,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Thread-safe wrapper for the raw *mut c_void engine handle
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Newtype wrapper so `*mut c_void` can live in a `static OnceLock`.
///
/// # Safety
/// We guarantee single-writer (via OnceLock) and that the pointer is only
/// dereferenced while the engine is alive.
struct SendSyncEngineHandle(NetEngineHandle);

// SAFETY: We uphold the invariant that the handle is only mutated from the
// dedicated poll thread, and all Rust callers hold a shared reference to the
// OnceLock which prevents concurrent destruction.
unsafe impl Send for SendSyncEngineHandle {}
unsafe impl Sync for SendSyncEngineHandle {}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Global singleton — one NetEngine shared across the whole browser process
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

static GLOBAL_NET_ENGINE: OnceLock<SendSyncEngineHandle> = OnceLock::new();
static NET_ENGINE_STARTED: AtomicBool = AtomicBool::new(false);
static NET_POLL_THREAD_STARTED: AtomicBool = AtomicBool::new(false);
static NET_POLL_THREAD_RUNNING: AtomicBool = AtomicBool::new(true);
static NET_POLL_THREAD_HANDLE: Mutex<Option<thread::JoinHandle<()>>> = Mutex::new(None);

fn ensure_net_poll_thread() {
    if NET_POLL_THREAD_STARTED.swap(true, Ordering::SeqCst) {
        return;
    }
    NET_POLL_THREAD_RUNNING.store(true, Ordering::SeqCst);
    // Background thread: continuously poll the engine for I/O events.
    let spawn_res = thread::Builder::new()
        .name("zawra-net-poll".into())
        .spawn(move || {
            while NET_POLL_THREAD_RUNNING.load(Ordering::Relaxed) {
                if let Some(wrapper) = GLOBAL_NET_ENGINE.get() {
                    // Block up to 10 ms per cycle → CPU-friendly event loop
                    net_poll(wrapper.0, 10);
                } else {
                    thread::sleep(std::time::Duration::from_millis(10));
                }
            }
        });
    match spawn_res {
        Ok(handle) => {
            if let Ok(mut lock) = NET_POLL_THREAD_HANDLE.lock() {
                *lock = Some(handle);
            }
        }
        Err(e) => {
            eprintln!("[zawra-net] failed to spawn zawra-net-poll thread: {}", e);
            NET_POLL_THREAD_STARTED.store(false, Ordering::SeqCst);
        }
    }
}

/// Initialise the global z-net engine.
/// Called once from `Zawra_Init_Subsystems`.
/// The poll thread is spawned lazily on first use to avoid pthread_create
/// failures in forked child processes.
///
/// # Safety
/// Must be called before any networking operation.
pub unsafe fn init_net_engine() -> bool {
    if NET_ENGINE_STARTED.load(Ordering::SeqCst) {
        return true;
    }

    let handle = net_engine_create();
    if handle.is_null() {
        return false;
    }

    // Store the handle globally. OnceLock guarantees single-writer.
    let _ = GLOBAL_NET_ENGINE.set(SendSyncEngineHandle(handle));
    NET_ENGINE_STARTED.store(true, Ordering::SeqCst);

    true
}

/// Shut down the global z-net engine and background polling thread.
pub fn shutdown_net_engine() {
    NET_POLL_THREAD_RUNNING.store(false, Ordering::SeqCst);
    if let Ok(mut lock) = NET_POLL_THREAD_HANDLE.lock() {
        if let Some(handle) = lock.take() {
            if let Err(e) = handle.join() {
                eprintln!("[zawra-net] warning: net-poll thread failed to join cleanly: {:?}", e);
            }
        }
    }
    NET_POLL_THREAD_STARTED.store(false, Ordering::SeqCst);
    NET_ENGINE_STARTED.store(false, Ordering::SeqCst);
}

/// Return the global engine handle. Returns null if `init_net_engine` was not called.
/// Lazily spawns the poll thread on first use.
pub fn global_engine() -> NetEngineHandle {
    ensure_net_poll_thread();
    match GLOBAL_NET_ENGINE.get() {
        Some(handle) => handle.0,
        None => std::ptr::null_mut(),
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Body-Ring slab — unique IDs for each in-flight BodyRingDescriptor
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

static NEXT_RING_ID: AtomicU64 = AtomicU64::new(1);

fn alloc_ring_id() -> u64 {
    NEXT_RING_ID.fetch_add(1, Ordering::Relaxed)
}

/// Shared-memory BodyRing + its unique id. Heap-allocated so the pointer
/// is stable across WPE's C++ callback boundaries.
pub struct OwnedBodyRing {
    pub id: u64,
    pub descriptor: Box<BodyRingDescriptor>,
    _backing: Vec<u8>, // owns the underlying buffer
}

impl OwnedBodyRing {
    /// Create a new BodyRing with `capacity` bytes of backing memory and
    /// register it with the global NetEngine.
    pub fn new(capacity: usize) -> Option<Self> {
        let mut backing = vec![0u8; capacity];
        let buf_ptr = backing.as_mut_ptr();

        let descriptor = Box::new(BodyRingDescriptor {
            buffer_ptr: buf_ptr,
            capacity,
            _pad1: [0u8; 64],
            head: AtomicU64::new(0),
            _pad2: [0u8; 64],
            tail: AtomicU64::new(0),
            _pad3: [0u8; 48],
            pause_fd: AtomicI32::new(-1),
            futex_word: AtomicU32::new(0),
            is_closed: AtomicBool::new(false),
        });

        let id = alloc_ring_id();
        let desc_ptr = &*descriptor as *const BodyRingDescriptor as *mut BodyRingDescriptor;

        let engine = global_engine();
        if engine.is_null() {
            return None;
        }
        let ret = net_body_ring_register(engine, id, desc_ptr);
        if ret != 0 {
            return None;
        }

        Some(OwnedBodyRing {
            id,
            descriptor,
            _backing: backing,
        })
    }
}

impl Drop for OwnedBodyRing {
    fn drop(&mut self) {
        let engine = global_engine();
        if !engine.is_null() {
            net_body_ring_unregister(engine, self.id);
        }
        self.descriptor.is_closed.store(true, Ordering::Release);
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsIInputStream — zero-copy read from BodyRing
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// XPCOM-style vtable for nsIInputStream (ABI-compatible layout).
/// WPE expects: [QueryInterface, AddRef, Release, Close, Available, Read, ReadSegments, IsNonBlocking]
#[repr(C)]
pub struct NsIInputStreamVtable {
    // nsISupports
    pub query_interface: unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub add_ref: unsafe extern "C" fn(*mut c_void) -> u32,
    pub release: unsafe extern "C" fn(*mut c_void) -> u32,
    // nsIInputStream
    pub close: unsafe extern "C" fn(*mut c_void) -> u32,
    pub available: unsafe extern "C" fn(*mut c_void, *mut u64) -> u32,
    pub read: unsafe extern "C" fn(*mut c_void, *mut c_char, u32, *mut u32) -> u32,
    pub read_segments:
        unsafe extern "C" fn(*mut c_void, *mut c_void, *mut c_void, u32, *mut u32) -> u32,
    pub is_non_blocking: unsafe extern "C" fn(*mut c_void, *mut bool) -> u32,
}

/// Concrete zero-copy input stream backed by an `OwnedBodyRing`.
#[repr(C)]
pub struct ZNetInputStream {
    vtable: *const NsIInputStreamVtable,
    ref_count: AtomicI32,
    ring: Arc<Mutex<OwnedBodyRing>>,
}

impl ZNetInputStream {
    fn new(ring: Arc<Mutex<OwnedBodyRing>>) -> *mut Self {
        let boxed = Box::new(ZNetInputStream {
            vtable: &ZNET_INPUT_STREAM_VTABLE,
            ref_count: AtomicI32::new(1),
            ring,
        });
        Box::into_raw(boxed)
    }

    unsafe fn from_ptr<'a>(ptr: *mut c_void) -> &'a mut Self {
        // SAFETY: Caller guarantees ptr is a valid, aligned non-null pointer to ZNetInputStream
        unsafe { &mut *(ptr as *mut ZNetInputStream) }
    }
}

// Vtable function implementations for ZNetInputStream
unsafe extern "C" fn stream_query_interface(
    this: *mut c_void,
    iid: *const u8,
    out: *mut *mut c_void,
) -> u32 {
    if out.is_null() { return ns_result::NS_ERROR_INVALID_ARG; }
    // SAFETY: out pointer is checked non-null
    unsafe { *out = std::ptr::null_mut(); }

    // SAFETY: iid is provided by XPCOM caller; match_iid checks validity
    let is_supports = unsafe { match_iid(iid, 0x00000000, 0x0000, 0x0000, [0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46]) };
    let is_stream = unsafe { match_iid(iid, 0xfa9c7f6c, 0x61b3, 0x11d4, [0x98, 0x77, 0x00, 0xc0, 0x4f, 0xa0, 0xcf, 0x4a]) };

    if is_supports || is_stream {
        // SAFETY: out is valid and non-null; stream_add_ref increments refcount
        unsafe {
            *out = this;
            stream_add_ref(this);
        }
        ns_result::NS_OK
    } else {
        ns_result::NS_NOINTERFACE
    }
}

unsafe extern "C" fn stream_add_ref(this: *mut c_void) -> u32 {
    // SAFETY: this is a valid ZNetInputStream pointer managed by XPCOM refcounting
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    s.ref_count.fetch_add(1, Ordering::SeqCst) as u32
}

unsafe extern "C" fn stream_release(this: *mut c_void) -> u32 {
    // SAFETY: this is a valid ZNetInputStream pointer
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    let prev = s.ref_count.fetch_sub(1, Ordering::SeqCst);
    if prev == 1 {
        // SAFETY: refcount reached zero, reclaim ownership of Box
        unsafe {
            let _ = Box::from_raw(this as *mut ZNetInputStream);
        }
    }
    (prev - 1).max(0) as u32
}

unsafe extern "C" fn stream_close(this: *mut c_void) -> u32 {
    // SAFETY: this is a valid ZNetInputStream pointer
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    if let Ok(guard) = s.ring.lock() {
        guard.descriptor.is_closed.store(true, Ordering::Release);
    }
    ns_result::NS_OK
}

unsafe extern "C" fn stream_available(this: *mut c_void, count: *mut u64) -> u32 {
    if count.is_null() { return ns_result::NS_ERROR_INVALID_ARG; }
    // SAFETY: this is a valid ZNetInputStream pointer
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    let ring_guard = match s.ring.lock() {
        Ok(g) => g,
        Err(_) => return ns_result::NS_ERROR_FAILURE,
    };
    let head = ring_guard.descriptor.head.load(Ordering::Acquire);
    let tail = ring_guard.descriptor.tail.load(Ordering::Acquire);
    let available = head.wrapping_sub(tail);
    // SAFETY: count pointer was checked non-null
    unsafe {
        *count = available;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn stream_read(
    this: *mut c_void,
    buf: *mut c_char,
    count: u32,
    bytes_read: *mut u32,
) -> u32 {
    if buf.is_null() || bytes_read.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: bytes_read was verified non-null
    unsafe { *bytes_read = 0; }
    // SAFETY: this is a valid ZNetInputStream pointer
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    let ring_guard = match s.ring.lock() {
        Ok(g) => g,
        Err(_) => return ns_result::NS_ERROR_FAILURE,
    };

    let head = ring_guard.descriptor.head.load(Ordering::Acquire);
    let tail = ring_guard.descriptor.tail.load(Ordering::Acquire);
    let available = head.wrapping_sub(tail) as usize;

    if available == 0 {
        return 0; // EOF
    }

    let to_copy = available.min(count as usize);
    let cap = ring_guard.descriptor.capacity;
    let tail_idx = (tail % cap as u64) as usize;
    let contiguous = cap - tail_idx;
    let first_chunk = to_copy.min(contiguous);

    // SAFETY: buffer_ptr is allocated with capacity `cap` bytes and buf has space for at least `count` bytes
    unsafe {
        std::ptr::copy_nonoverlapping(
            ring_guard.descriptor.buffer_ptr.add(tail_idx),
            buf as *mut u8,
            first_chunk,
        );
        if first_chunk < to_copy {
            std::ptr::copy_nonoverlapping(
                ring_guard.descriptor.buffer_ptr,
                (buf as *mut u8).add(first_chunk),
                to_copy - first_chunk,
            );
        }
        ring_guard
            .descriptor
            .tail
            .fetch_add(to_copy as u64, Ordering::Release);
        if ring_guard.descriptor.should_resume_reading() {
            ring_guard.descriptor.signal_resume();
        }
        *bytes_read = to_copy as u32;
    }
    0 // NS_OK
}

unsafe extern "C" fn stream_read_segments(
    _this: *mut c_void,
    _writer: *mut c_void,
    _closure: *mut c_void,
    _count: u32,
    _bytes_read: *mut u32,
) -> u32 {
    0x80004001u32 // NS_ERROR_NOT_IMPLEMENTED
}

unsafe extern "C" fn stream_is_non_blocking(_this: *mut c_void, non_blocking: *mut bool) -> u32 {
    if non_blocking.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: non_blocking checked non-null
    unsafe {
        *non_blocking = true;
    }
    0
}

static ZNET_INPUT_STREAM_VTABLE: NsIInputStreamVtable = NsIInputStreamVtable {
    query_interface: stream_query_interface,
    add_ref: stream_add_ref,
    release: stream_release,
    close: stream_close,
    available: stream_available,
    read: stream_read,
    read_segments: stream_read_segments,
    is_non_blocking: stream_is_non_blocking,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsresult constants
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[allow(non_upper_case_globals)]
pub mod ns_result {
    pub const NS_OK: u32 = 0;
    pub const NS_ERROR_FAILURE: u32 = 0x80004005;
    pub const NS_ERROR_NOT_IMPLEMENTED: u32 = 0x80004001;
    pub const NS_ERROR_INVALID_ARG: u32 = 0x80070057;
    pub const NS_NOINTERFACE: u32 = 0x80004002;
}

#[repr(C)]
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct nsID {
    pub m0: u32,
    pub m1: u16,
    pub m2: u16,
    pub m3: [u8; 8],
}

pub unsafe fn match_iid(iid: *const u8, m0: u32, m1: u16, m2: u16, m3: [u8; 8]) -> bool {
    if iid.is_null() {
        return false;
    }
    // SAFETY: Caller provides valid iid pointer conforming to XPCOM nsID layout
    let ptr = iid as *const nsID;
    unsafe {
        (*ptr).m0 == m0 && (*ptr).m1 == m1 && (*ptr).m2 == m2 && (*ptr).m3 == m3
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// HTTP Helpers (Methods, Headers, Body, Content-Type Parsing)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Parse Content-Type header value and return (mime_type, Option<charset>)
pub fn parse_content_type_header(raw: &str) -> (String, Option<String>) {
    let mut parts = raw.split(';');
    let mime = parts
        .next()
        .map(|m| m.trim().to_string())
        .unwrap_or_else(|| "application/octet-stream".to_string());
    let mut charset = None;
    for part in parts {
        let part = part.trim();
        if let Some((k, v)) = part.split_once('=') {
            if k.trim().eq_ignore_ascii_case("charset") {
                let cs = v.trim().trim_matches('"').trim_matches('\'').trim();
                if !cs.is_empty() {
                    charset = Some(cs.to_string());
                }
            }
        }
    }
    (mime, charset)
}

/// Construct full HTTP/1.1 request head string with dynamic method and serialized headers.
pub fn build_http_request(
    method: &str,
    path: &str,
    host: &str,
    custom_headers: &[(String, String)],
    body_len: Option<usize>,
) -> String {
    let valid_methods = ["GET", "POST", "PUT", "DELETE", "HEAD"];
    let method = if valid_methods.iter().any(|&m| m.eq_ignore_ascii_case(method)) {
        method.to_ascii_uppercase()
    } else {
        "GET".to_string()
    };

    let mut request = format!("{} {} HTTP/1.1\r\n", method, path);

    let mut has_host = false;
    let mut has_conn = false;
    let mut has_user_agent = false;
    let mut has_accept = false;
    let mut has_content_length = false;

    for (k, v) in custom_headers {
        let k_lower = k.to_ascii_lowercase();
        if k_lower == "host" {
            has_host = true;
        } else if k_lower == "connection" {
            has_conn = true;
        } else if k_lower == "user-agent" {
            has_user_agent = true;
        } else if k_lower == "accept" {
            has_accept = true;
        } else if k_lower == "content-length" {
            has_content_length = true;
        }
        request.push_str(&format!("{}: {}\r\n", k, v));
    }

    if !has_host {
        request.push_str(&format!("Host: {}\r\n", host));
    }
    if !has_conn {
        request.push_str("Connection: close\r\n");
    }
    if !has_user_agent {
        request.push_str("User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/18.0 Safari/605.1.15 Zawra/0.1\r\n");
    }
    if !has_accept {
        request.push_str("Accept: */*\r\n");
    }
    if let Some(len) = body_len {
        if !has_content_length {
            request.push_str(&format!("Content-Length: {}\r\n", len));
        }
    }

    request.push_str("\r\n");
    request
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ZNetChannel — nsIChannel implementation
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// XPCOM vtable layout for nsIChannel (C-ABI compatible).
#[repr(C)]
pub struct NsIChannelVtable {
    // nsISupports
    pub query_interface: unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub add_ref: unsafe extern "C" fn(*mut c_void) -> u32,
    pub release: unsafe extern "C" fn(*mut c_void) -> u32,
    // nsIRequest
    pub get_name: unsafe extern "C" fn(*mut c_void, *mut *const c_char) -> u32,
    pub is_pending: unsafe extern "C" fn(*mut c_void, *mut bool) -> u32,
    pub get_status: unsafe extern "C" fn(*mut c_void, *mut u32) -> u32,
    pub cancel: unsafe extern "C" fn(*mut c_void, u32) -> u32,
    pub suspend: unsafe extern "C" fn(*mut c_void) -> u32,
    pub resume: unsafe extern "C" fn(*mut c_void) -> u32,
    pub get_load_group: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub set_load_group: unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub get_load_flags: unsafe extern "C" fn(*mut c_void, *mut u32) -> u32,
    pub set_load_flags: unsafe extern "C" fn(*mut c_void, u32) -> u32,
    pub get_trr_mode: unsafe extern "C" fn(*mut c_void, *mut u32) -> u32,
    pub set_trr_mode: unsafe extern "C" fn(*mut c_void, u32) -> u32,
    pub cancel_with_reason: unsafe extern "C" fn(*mut c_void, u32, *const c_char) -> u32,
    // nsIChannel
    pub get_original_uri: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub set_original_uri: unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub get_uri: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub get_owner: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub set_owner: unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub get_notif_callbacks: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub set_notif_callbacks: unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub get_security_info: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub get_content_type: unsafe extern "C" fn(*mut c_void, *mut *const c_char) -> u32,
    pub set_content_type: unsafe extern "C" fn(*mut c_void, *const c_char) -> u32,
    pub get_content_charset: unsafe extern "C" fn(*mut c_void, *mut *const c_char) -> u32,
    pub set_content_charset: unsafe extern "C" fn(*mut c_void, *const c_char) -> u32,
    pub get_content_length: unsafe extern "C" fn(*mut c_void, *mut i64) -> u32,
    pub set_content_length: unsafe extern "C" fn(*mut c_void, i64) -> u32,
    pub open: unsafe extern "C" fn(*mut c_void, *mut *mut c_void) -> u32,
    pub async_open: unsafe extern "C" fn(*mut c_void, *mut c_void) -> u32,
    pub get_content_disp: unsafe extern "C" fn(*mut c_void, *mut u32) -> u32,
    pub set_content_disp: unsafe extern "C" fn(*mut c_void, u32) -> u32,
    pub get_content_disp_fn: unsafe extern "C" fn(*mut c_void, *mut *const c_char) -> u32,
    pub set_content_disp_fn: unsafe extern "C" fn(*mut c_void, *const c_char) -> u32,
}

/// The concrete nsIChannel implementation backed by a z-net connection.
#[repr(C)]
pub struct ZNetChannel {
    vtable: *const NsIChannelVtable,
    ref_count: AtomicI32,
    conn_handle: ConnectionHandle,
    body_ring: Arc<Mutex<OwnedBodyRing>>,
    url: CString,
    host: CString,
    port: u16,
    method: Mutex<String>,
    request_headers: Mutex<Vec<(String, String)>>,
    request_body: Mutex<Option<Vec<u8>>>,
    request_sent: AtomicBool,
    is_pending: AtomicBool,
    status: AtomicI32,
    pub content_len: AtomicI64,
    content_type: Mutex<CString>,
    content_charset: Mutex<CString>,
    listener: Mutex<Option<*mut c_void>>,
}

// SAFETY: ZNetChannel is only accessed through the XPCOM ref-counting
// protocol. The contained raw pointers are managed by the vtable lifecycle.
unsafe impl Send for ZNetChannel {}
unsafe impl Sync for ZNetChannel {}

impl ZNetChannel {
    pub fn new(url: &str, host: &str, port: u16) -> Option<*mut ZNetChannel> {
        // Native Zawra Shield check: Block ads, tracking, and telemetry early
        let shield = crate::shield::ZawraShield::global();
        if let crate::shield::ShieldDecision::Block { .. } =
            shield.check_network_request(url, "", "other")
        {
            eprintln!("[ZAWRA-SHIELD] 🛡️ Blocked: {}", url);
            return None;
        }

        let ring = OwnedBodyRing::new(512 * 1024)?; // 512 KB ring per channel
        let ring = Arc::new(Mutex::new(ring));

        let engine = global_engine();
        if engine.is_null() {
            return None;
        }
        let host_c = CString::new(host).ok()?;
        let url_c = CString::new(url).ok()?;
        let conn = net_connect(engine, host_c.as_ptr(), port);
        if conn.is_null() {
            return None;
        }

        {
            let ring_guard = ring.lock().ok()?;
            net_conn_bind_body_ring(engine, conn, ring_guard.id);
        }

        let default_content_type = match CString::new("application/octet-stream") {
            Ok(cs) => cs,
            Err(e) => {
                eprintln!("[zawra-net] failed to create default content type CString: {}", e);
                CString::default()
            }
        };
        let default_charset = match CString::new("UTF-8") {
            Ok(cs) => cs,
            Err(e) => {
                eprintln!("[zawra-net] failed to create default charset CString: {}", e);
                CString::default()
            }
        };

        let channel = Box::new(ZNetChannel {
            vtable: &ZNET_CHANNEL_VTABLE,
            ref_count: AtomicI32::new(1),
            conn_handle: conn,
            body_ring: ring,
            url: url_c,
            host: host_c,
            port,
            method: Mutex::new("GET".to_string()),
            request_headers: Mutex::new(Vec::new()),
            request_body: Mutex::new(None),
            request_sent: AtomicBool::new(false),
            is_pending: AtomicBool::new(false),
            status: AtomicI32::new(0),
            content_len: AtomicI64::new(-1),
            content_type: Mutex::new(default_content_type),
            content_charset: Mutex::new(default_charset),
            listener: Mutex::new(None),
        });

        Some(Box::into_raw(channel))
    }

    pub unsafe fn from_ptr<'a>(ptr: *mut c_void) -> &'a mut Self {
        // SAFETY: Caller guarantees ptr is a valid, aligned non-null pointer to a live ZNetChannel
        unsafe { &mut *(ptr as *mut ZNetChannel) }
    }

    pub fn set_method(&self, method: &str) {
        if let Ok(mut m) = self.method.lock() {
            *m = method.to_ascii_uppercase();
        }
    }

    pub fn get_method(&self) -> String {
        self.method
            .lock()
            .map(|m| m.clone())
            .unwrap_or_else(|_| "GET".to_string())
    }

    pub fn add_header(&self, name: &str, value: &str) {
        if let Ok(mut h) = self.request_headers.lock() {
            h.push((name.to_string(), value.to_string()));
        }
    }

    pub fn set_body(&self, body: Option<Vec<u8>>) {
        if let Ok(mut b) = self.request_body.lock() {
            *b = body;
        }
    }

    pub fn set_pending(&self, pending: bool) {
        self.is_pending.store(pending, Ordering::SeqCst);
    }

    pub fn parse_and_apply_content_type(&self, raw: &str) {
        let (mime, charset_opt) = parse_content_type_header(raw);
        if let Ok(c_mime) = CString::new(mime) {
            if let Ok(mut ct) = self.content_type.lock() {
                *ct = c_mime;
            }
        }
        if let Some(cs) = charset_opt {
            if let Ok(c_cs) = CString::new(cs) {
                if let Ok(mut cs_guard) = self.content_charset.lock() {
                    *cs_guard = c_cs;
                }
            }
        }
    }

    pub fn try_parse_response_headers_from_ring(&self) {
        if let Ok(ring_guard) = self.body_ring.lock() {
            let head = ring_guard.descriptor.head.load(Ordering::Acquire);
            let tail = ring_guard.descriptor.tail.load(Ordering::Acquire);
            let available = head.wrapping_sub(tail) as usize;
            if available > 0 {
                let cap = ring_guard.descriptor.capacity;
                let tail_idx = (tail % cap as u64) as usize;
                let contiguous = (cap - tail_idx).min(available);
                // SAFETY: buffer_ptr points to `cap` allocated bytes in ring descriptor
                let slice = unsafe {
                    std::slice::from_raw_parts(
                        ring_guard.descriptor.buffer_ptr.add(tail_idx),
                        contiguous,
                    )
                };
                if let Some(header_end) = slice.windows(4).position(|w| w == b"\r\n\r\n") {
                    if let Ok(header_str) = std::str::from_utf8(&slice[..header_end]) {
                        self.parse_and_apply_response_headers(header_str);
                    }
                }
            }
        }
    }

    pub fn parse_and_apply_response_headers(&self, headers_str: &str) {
        for line in headers_str.lines() {
            let line = line.trim();
            if let Some((name, val)) = line.split_once(':') {
                let name = name.trim().to_ascii_lowercase();
                let val = val.trim();
                if name == "content-type" {
                    self.parse_and_apply_content_type(val);
                } else if name == "content-length" {
                    if let Ok(len) = val.parse::<i64>() {
                        self.content_len.store(len, Ordering::SeqCst);
                    }
                }
            }
        }
    }

    fn send_http_request(&self) -> bool {
        if self.request_sent.swap(true, Ordering::SeqCst) {
            return true;
        }
        self.is_pending.store(true, Ordering::SeqCst);

        let url_str = self.url.to_string_lossy();
        let path = url_str
            .as_ref()
            .split_once("://")
            .and_then(|(_, rest)| rest.find('/').map(|i| &rest[i..]))
            .unwrap_or("/");

        let method = self.get_method();
        let host_str = self.host.to_string_lossy();
        let custom_headers = self
            .request_headers
            .lock()
            .map(|h| h.clone())
            .unwrap_or_default();
        let body_opt = self
            .request_body
            .lock()
            .map(|b| b.clone())
            .unwrap_or(None);
        let body_len = body_opt.as_ref().map(|b| b.len());

        let request = build_http_request(&method, path, &host_str, &custom_headers, body_len);

        let engine = global_engine();
        if engine.is_null() || self.conn_handle.is_null() {
            self.is_pending.store(false, Ordering::SeqCst);
            return false;
        }

        let bytes = request.as_bytes();
        let mut written = 0usize;
        let ret = net_write(
            engine,
            self.conn_handle,
            bytes.as_ptr(),
            bytes.len(),
            &mut written,
        );
        if ret != NetError::None as i32 {
            self.is_pending.store(false, Ordering::SeqCst);
            return false;
        }

        // Stream request body chunks if present
        if let Some(ref body) = body_opt {
            let mut offset = 0;
            const CHUNK_SIZE: usize = 16384; // 16KB streaming chunks
            while offset < body.len() {
                let end = (offset + CHUNK_SIZE).min(body.len());
                let chunk = &body[offset..end];
                let mut chunk_written = 0usize;
                let ret = net_write(
                    engine,
                    self.conn_handle,
                    chunk.as_ptr(),
                    chunk.len(),
                    &mut chunk_written,
                );
                if ret != NetError::None as i32 || chunk_written == 0 {
                    self.is_pending.store(false, Ordering::SeqCst);
                    return false;
                }
                offset += chunk_written;
            }
        }

        true
    }
}

// ── nsIChannel vtable functions ─────────────────────────────────────────────

unsafe extern "C" fn chan_query_interface(
    this: *mut c_void,
    iid: *const u8,
    out: *mut *mut c_void,
) -> u32 {
    if out.is_null() { return ns_result::NS_ERROR_INVALID_ARG; }
    // SAFETY: out pointer verified non-null
    unsafe { *out = std::ptr::null_mut(); }

    // SAFETY: iid is provided by XPCOM caller; match_iid verifies layout
    let is_supports = unsafe { match_iid(iid, 0x00000000, 0x0000, 0x0000, [0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46]) };
    let is_request = unsafe { match_iid(iid, 0xef6bfbd2, 0xfd46, 0x48d8, [0x96, 0xb7, 0x9f, 0x8f, 0x0f, 0xd3, 0x87, 0xfe]) };
    let is_channel = unsafe { match_iid(iid, 0xc63a0557, 0xa63d, 0x4959, [0xaf, 0x2c, 0xf6, 0xae, 0x49, 0x01, 0x46, 0xa6]) };

    if is_supports || is_request || is_channel {
        // SAFETY: out is valid and non-null; chan_add_ref increments refcount
        unsafe {
            *out = this;
            chan_add_ref(this);
        }
        ns_result::NS_OK
    } else {
        ns_result::NS_NOINTERFACE
    }
}

unsafe extern "C" fn chan_add_ref(this: *mut c_void) -> u32 {
    // SAFETY: this is a valid ZNetChannel pointer
    unsafe { ZNetChannel::from_ptr(this) }
        .ref_count
        .fetch_add(1, Ordering::SeqCst) as u32
}

unsafe extern "C" fn chan_release(this: *mut c_void) -> u32 {
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    let prev = c.ref_count.fetch_sub(1, Ordering::SeqCst);
    if prev == 1 {
        c.is_pending.store(false, Ordering::SeqCst);
        let engine = global_engine();
        if !engine.is_null() {
            net_close(engine, c.conn_handle);
        }
        // SAFETY: refcount reached zero, reclaim ownership of Box
        unsafe {
            let _ = Box::from_raw(this as *mut ZNetChannel);
        }
    }
    (prev - 1).max(0) as u32
}

unsafe extern "C" fn chan_get_name(this: *mut c_void, name: *mut *const c_char) -> u32 {
    if this.is_null() || name.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer; name is verified non-null
    unsafe {
        *name = ZNetChannel::from_ptr(this).url.as_ptr();
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_is_pending(this: *mut c_void, pending: *mut bool) -> u32 {
    if this.is_null() || pending.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    let val = c.is_pending.load(Ordering::SeqCst);
    // SAFETY: pending pointer is verified non-null
    unsafe {
        *pending = val;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_get_status(this: *mut c_void, status: *mut u32) -> u32 {
    if this.is_null() || status.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer; status is verified non-null
    unsafe {
        *status = ZNetChannel::from_ptr(this).status.load(Ordering::SeqCst) as u32;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_cancel(this: *mut c_void, status: u32) -> u32 {
    if this.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.status.store(status as i32, Ordering::SeqCst);
    c.is_pending.store(false, Ordering::SeqCst);
    let engine = global_engine();
    if !engine.is_null() {
        net_close(engine, c.conn_handle);
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_nop(_this: *mut c_void) -> u32 {
    ns_result::NS_OK
}
unsafe extern "C" fn chan_nop_u32(_this: *mut c_void, _v: u32) -> u32 {
    ns_result::NS_OK
}
unsafe extern "C" fn chan_nop_ptr_mut(_this: *mut c_void, _a: *mut c_void) -> u32 {
    ns_result::NS_OK
}
unsafe extern "C" fn chan_nop_ptr_const(_this: *mut c_void, _a: *const c_char) -> u32 {
    ns_result::NS_OK
}
unsafe extern "C" fn chan_nop_out_ptr(_this: *mut c_void, _a: *mut *mut c_void) -> u32 {
    ns_result::NS_OK
}
unsafe extern "C" fn chan_nop_out_u32(_this: *mut c_void, _a: *mut u32) -> u32 {
    ns_result::NS_OK
}

unsafe extern "C" fn chan_get_content_length(this: *mut c_void, len: *mut i64) -> u32 {
    if this.is_null() || len.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.try_parse_response_headers_from_ring();
    // SAFETY: len is verified non-null
    unsafe {
        *len = c.content_len.load(Ordering::SeqCst);
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_set_content_length(this: *mut c_void, len: i64) -> u32 {
    if this.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.content_len.store(len, Ordering::SeqCst);
    ns_result::NS_OK
}

unsafe extern "C" fn chan_get_uri(this: *mut c_void, uri: *mut *mut c_void) -> u32 {
    if uri.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: uri pointer is verified non-null
    unsafe {
        *uri = this;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_open(this: *mut c_void, input_stream: *mut *mut c_void) -> u32 {
    if this.is_null() || input_stream.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    if !c.send_http_request() {
        return ns_result::NS_ERROR_FAILURE;
    }
    let stream = ZNetInputStream::new(c.body_ring.clone());
    // SAFETY: input_stream pointer is verified non-null
    unsafe {
        *input_stream = stream as *mut c_void;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_async_open(this: *mut c_void, listener: *mut c_void) -> u32 {
    if this.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    if let Ok(mut guard) = c.listener.lock() {
        *guard = Some(listener);
    }
    if !c.send_http_request() {
        return ns_result::NS_ERROR_FAILURE;
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_get_content_type(this: *mut c_void, ct: *mut *const c_char) -> u32 {
    if this.is_null() || ct.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.try_parse_response_headers_from_ring();
    if let Ok(guard) = c.content_type.lock() {
        // SAFETY: ct pointer is verified non-null
        unsafe {
            *ct = guard.as_ptr();
        }
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_set_content_type(this: *mut c_void, ct: *const c_char) -> u32 {
    if this.is_null() || ct.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    // SAFETY: ct is verified non-null and is a valid NUL-terminated C string
    if let Ok(ct_str) = unsafe { CStr::from_ptr(ct) }.to_str() {
        c.parse_and_apply_content_type(ct_str);
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_get_content_charset(this: *mut c_void, cs: *mut *const c_char) -> u32 {
    if this.is_null() || cs.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.try_parse_response_headers_from_ring();
    if let Ok(guard) = c.content_charset.lock() {
        // SAFETY: cs pointer is verified non-null
        unsafe {
            *cs = guard.as_ptr();
        }
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_set_content_charset(this: *mut c_void, cs: *const c_char) -> u32 {
    if this.is_null() || cs.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // SAFETY: this is a valid ZNetChannel pointer
    let c = unsafe { ZNetChannel::from_ptr(this) };
    // SAFETY: cs is verified non-null and is a valid NUL-terminated C string
    if let Ok(cs_str) = unsafe { CStr::from_ptr(cs) }.to_str() {
        if let Ok(val) = CString::new(cs_str) {
            if let Ok(mut guard) = c.content_charset.lock() {
                *guard = val;
            }
        }
    }
    ns_result::NS_OK
}

unsafe extern "C" fn chan_cancel_with_reason(
    this: *mut c_void,
    status: u32,
    _reason: *const c_char,
) -> u32 {
    // SAFETY: delegates to chan_cancel
    unsafe { chan_cancel(this, status) }
}

unsafe extern "C" fn chan_nop_out_const_char(_this: *mut c_void, _out: *mut *const c_char) -> u32 {
    ns_result::NS_ERROR_NOT_IMPLEMENTED
}

static ZNET_CHANNEL_VTABLE: NsIChannelVtable = NsIChannelVtable {
    query_interface: chan_query_interface,
    add_ref: chan_add_ref,
    release: chan_release,
    get_name: chan_get_name,
    is_pending: chan_is_pending,
    get_status: chan_get_status,
    cancel: chan_cancel,
    suspend: chan_nop,
    resume: chan_nop,
    get_load_group: chan_nop_out_ptr,
    set_load_group: chan_nop_ptr_mut,
    get_load_flags: chan_nop_out_u32,
    set_load_flags: chan_nop_u32,
    get_trr_mode: chan_nop_out_u32,
    set_trr_mode: chan_nop_u32,
    cancel_with_reason: chan_cancel_with_reason,
    get_original_uri: chan_get_uri,
    set_original_uri: chan_nop_ptr_mut,
    get_uri: chan_get_uri,
    get_owner: chan_nop_out_ptr,
    set_owner: chan_nop_ptr_mut,
    get_notif_callbacks: chan_nop_out_ptr,
    set_notif_callbacks: chan_nop_ptr_mut,
    get_security_info: chan_nop_out_ptr,
    get_content_type: chan_get_content_type,
    set_content_type: chan_set_content_type,
    get_content_charset: chan_get_content_charset,
    set_content_charset: chan_set_content_charset,
    get_content_length: chan_get_content_length,
    set_content_length: chan_set_content_length,
    open: chan_open,
    async_open: chan_async_open,
    get_content_disp: chan_nop_out_u32,
    set_content_disp: chan_nop_u32,
    get_content_disp_fn: chan_nop_out_const_char,
    set_content_disp_fn: chan_nop_ptr_const,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// URL parsing helper
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn parse_url(url: &str) -> Option<(String, u16)> {
    let is_https = url.starts_with("https://");
    let default_port: u16 = if is_https { 443 } else { 80 };

    let without_scheme = url
        .strip_prefix("https://")
        .or_else(|| url.strip_prefix("http://"))?;

    let host_part = without_scheme.split('/').next().unwrap_or(without_scheme);
    if let Some(colon_pos) = host_part.rfind(':') {
        let host = &host_part[..colon_pos];
        let port: u16 = host_part[colon_pos + 1..].parse().ok()?;
        Some((host.to_string(), port))
    } else {
        Some((host_part.to_string(), default_port))
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Public C-ABI entry points (called by WPE)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Create a new ZNetChannel for the given URL.
///
/// # Safety
/// `url` must be a valid NUL-terminated UTF-8 string.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_CreateChannel(url: *const c_char) -> *mut c_void {
    if url.is_null() {
        return null_mut();
    }
    // SAFETY: url pointer is checked non-null
    let url_str = match unsafe { CStr::from_ptr(url).to_str() } {
        Ok(s) => s,
        Err(_) => return null_mut(),
    };
    let (host, port) = match parse_url(url_str) {
        Some(v) => v,
        None => return null_mut(),
    };
    match ZNetChannel::new(url_str, &host, port) {
        Some(ptr) => ptr as *mut c_void,
        None => null_mut(),
    }
}

/// Destroy a channel created by `Z_Net_CreateChannel`.
///
/// # Safety
/// `channel` must have been returned by `Z_Net_CreateChannel`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_DestroyChannel(channel: *mut c_void) {
    if channel.is_null() {
        return;
    }
    // SAFETY: channel checked non-null and comes from Z_Net_CreateChannel
    unsafe { chan_release(channel) };
}

/// Synchronously open the channel and return an `nsIInputStream*`.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_Open(channel: *mut c_void, out_stream: *mut *mut c_void) -> i32 {
    if channel.is_null() || out_stream.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: pointers checked non-null
    unsafe { chan_open(channel, out_stream) as i32 }
}

/// Asynchronously open the channel; data will arrive via the BodyRing.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_AsyncOpen(channel: *mut c_void, listener: *mut c_void) -> i32 {
    if channel.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: channel checked non-null
    unsafe { chan_async_open(channel, listener) as i32 }
}

/// Read bytes from an `nsIInputStream` obtained via `Z_Net_Open`.
///
/// # Safety
/// All pointers must be valid.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_Read(
    stream: *mut c_void,
    buf: *mut c_char,
    count: u32,
    bytes_read: *mut u32,
) -> i32 {
    if stream.is_null() || buf.is_null() || bytes_read.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: pointers checked non-null
    unsafe { stream_read(stream, buf, count, bytes_read) as i32 }
}

/// Set the HTTP request method for the channel (e.g. "GET", "POST", "PUT", "DELETE", "HEAD").
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*` and `method` a valid NUL-terminated C string.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_SetRequestMethod(
    channel: *mut c_void,
    method: *const c_char,
) -> i32 {
    if channel.is_null() || method.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: method checked non-null
    let method_str = match unsafe { CStr::from_ptr(method) }.to_str() {
        Ok(s) => s,
        Err(_) => return ns_result::NS_ERROR_INVALID_ARG as i32,
    };
    // SAFETY: channel checked non-null
    let chan = unsafe { ZNetChannel::from_ptr(channel) };
    chan.set_method(method_str);
    ns_result::NS_OK as i32
}

/// Add an HTTP request header to the channel.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`, `name` and `value` valid NUL-terminated C strings.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_SetRequestHeader(
    channel: *mut c_void,
    name: *const c_char,
    value: *const c_char,
) -> i32 {
    if channel.is_null() || name.is_null() || value.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: name and value checked non-null
    let name_str = match unsafe { CStr::from_ptr(name) }.to_str() {
        Ok(s) => s,
        Err(_) => return ns_result::NS_ERROR_INVALID_ARG as i32,
    };
    let value_str = match unsafe { CStr::from_ptr(value) }.to_str() {
        Ok(s) => s,
        Err(_) => return ns_result::NS_ERROR_INVALID_ARG as i32,
    };
    // SAFETY: channel checked non-null
    let chan = unsafe { ZNetChannel::from_ptr(channel) };
    chan.add_header(name_str, value_str);
    ns_result::NS_OK as i32
}

/// Set the HTTP request body payload for streaming.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`. If `body` is non-null, it must point to at least `len` valid bytes.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_SetRequestBody(
    channel: *mut c_void,
    body: *const u8,
    len: usize,
) -> i32 {
    if channel.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: channel checked non-null
    let chan = unsafe { ZNetChannel::from_ptr(channel) };
    if body.is_null() || len == 0 {
        chan.set_body(None);
    } else {
        // SAFETY: body checked non-null and caller guarantees len valid bytes
        let slice = unsafe { std::slice::from_raw_parts(body, len) };
        chan.set_body(Some(slice.to_vec()));
    }
    ns_result::NS_OK as i32
}

/// Query if the channel has a pending request.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*` and `pending` non-null.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_IsPending(channel: *mut c_void, pending: *mut bool) -> i32 {
    if channel.is_null() || pending.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: pointers checked non-null
    unsafe { chan_is_pending(channel, pending) as i32 }
}

/// Query the response Content-Type for the channel.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*` and `out_type` non-null.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_GetContentType(
    channel: *mut c_void,
    out_type: *mut *const c_char,
) -> i32 {
    if channel.is_null() || out_type.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: pointers checked non-null
    unsafe { chan_get_content_type(channel, out_type) as i32 }
}

/// Query the response Content-Charset for the channel.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*` and `out_charset` non-null.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Net_GetContentCharset(
    channel: *mut c_void,
    out_charset: *mut *const c_char,
) -> i32 {
    if channel.is_null() || out_charset.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    // SAFETY: pointers checked non-null
    unsafe { chan_get_content_charset(channel, out_charset) as i32 }
}
