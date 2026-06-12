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
use std::sync::atomic::{AtomicBool, AtomicI32, AtomicU64, Ordering};
use std::sync::{Arc, Mutex, OnceLock};
use std::thread;

use lean_net::{
    BodyRingDescriptor, ConnectionHandle, NetEngineHandle, NetError, net_body_ring_register,
    net_body_ring_unregister, net_close, net_conn_bind_body_ring, net_connect, net_engine_create,
    net_engine_destroy, net_poll, net_read, net_write,
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

fn ensure_net_poll_thread() {
    if NET_POLL_THREAD_STARTED.swap(true, Ordering::SeqCst) {
        return;
    }
    // Background thread: continuously poll the engine for I/O events.
    thread::Builder::new()
        .name("zawra-net-poll".into())
        .spawn(move || {
            loop {
                if let Some(wrapper) = GLOBAL_NET_ENGINE.get() {
                    // Block up to 10 ms per cycle → CPU-friendly event loop
                    unsafe { net_poll(wrapper.0, 10) };
                } else {
                    thread::sleep(std::time::Duration::from_millis(10));
                }
            }
        })
        .expect("failed to spawn zawra-net-poll thread");
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

    let handle = unsafe { net_engine_create() };
    if handle.is_null() {
        return false;
    }

    // Store the handle globally. OnceLock guarantees single-writer.
    let _ = GLOBAL_NET_ENGINE.set(SendSyncEngineHandle(handle));
    NET_ENGINE_STARTED.store(true, Ordering::SeqCst);

    true
}

/// Return the global engine handle. Panics if `init_net_engine` was not called.
/// Lazily spawns the poll thread on first use.
pub fn global_engine() -> NetEngineHandle {
    ensure_net_poll_thread();
    GLOBAL_NET_ENGINE
        .get()
        .expect("z-net engine not initialised – call Zawra_Init_Subsystems first")
        .0
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Body-Ring slab — unique IDs for each in-flight BodyRingDescriptor
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

static NEXT_RING_ID: AtomicU64 = AtomicU64::new(1);

fn alloc_ring_id() -> u64 {
    NEXT_RING_ID.fetch_add(1, Ordering::Relaxed)
}

/// Shared-memory BodyRing + its unique id.  Heap-allocated so the pointer
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
            _pad3: [0u8; 64],
            is_closed: AtomicBool::new(false),
        });

        let id = alloc_ring_id();
        let desc_ptr = &*descriptor as *const BodyRingDescriptor as *mut BodyRingDescriptor;

        let ret = unsafe { net_body_ring_register(global_engine(), id, desc_ptr) };
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
        unsafe { net_body_ring_unregister(global_engine(), self.id) };
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
        unsafe { &mut *(ptr as *mut ZNetInputStream) }
    }
}

// Vtable function implementations for ZNetInputStream
unsafe extern "C" fn stream_query_interface(
    _this: *mut c_void,
    _iid: *const u8,
    _out: *mut *mut c_void,
) -> u32 {
    0x80004002u32 // NS_NOINTERFACE
}
unsafe extern "C" fn stream_add_ref(this: *mut c_void) -> u32 {
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    s.ref_count.fetch_add(1, Ordering::SeqCst) as u32
}
unsafe extern "C" fn stream_release(this: *mut c_void) -> u32 {
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    let prev = s.ref_count.fetch_sub(1, Ordering::SeqCst);
    if prev == 1 {
        unsafe {
            let _ = Box::from_raw(this as *mut ZNetInputStream);
        }
        return 0;
    }
    (prev - 1) as u32
}
unsafe extern "C" fn stream_close(this: *mut c_void) -> u32 {
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    if let Ok(ring) = s.ring.lock() {
        ring.descriptor.is_closed.store(true, Ordering::Release);
    }
    0 // NS_OK
}
unsafe extern "C" fn stream_available(this: *mut c_void, count: *mut u64) -> u32 {
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    if let Ok(ring) = s.ring.lock() {
        let head = ring.descriptor.head.load(Ordering::Acquire);
        let tail = ring.descriptor.tail.load(Ordering::Acquire);
        unsafe {
            *count = head.wrapping_sub(tail);
        }
    }
    0
}
unsafe extern "C" fn stream_read(
    this: *mut c_void,
    buf: *mut c_char,
    count: u32,
    bytes_read: *mut u32,
) -> u32 {
    let s = unsafe { ZNetInputStream::from_ptr(this) };
    let ring_guard = match s.ring.lock() {
        Ok(g) => g,
        Err(_) => return 0x80004005u32,
    };

    let head = ring_guard.descriptor.head.load(Ordering::Acquire);
    let tail = ring_guard.descriptor.tail.load(Ordering::Acquire);
    let available = head.wrapping_sub(tail) as usize;

    if available == 0 {
        if !ring_guard.descriptor.is_closed.load(Ordering::Acquire) {
            unsafe {
                *bytes_read = 0;
            }
            return 0x80470007u32; // NS_BASE_STREAM_WOULD_BLOCK
        }
        unsafe {
            *bytes_read = 0;
        }
        return 0; // EOF
    }

    let to_copy = available.min(count as usize);
    let tail_idx = (tail % ring_guard.descriptor.capacity as u64) as usize;
    let cap = ring_guard.descriptor.capacity;
    let contiguous = cap - tail_idx;
    let first_chunk = to_copy.min(contiguous);

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
    request_sent: AtomicBool,
    status: AtomicI32,
    pub content_len: i64,
    listener: Mutex<Option<*mut c_void>>,
}

// SAFETY: ZNetChannel is only accessed through the XPCOM ref-counting
// protocol. The contained raw pointers are managed by the vtable lifecycle.
unsafe impl Send for ZNetChannel {}
unsafe impl Sync for ZNetChannel {}

impl ZNetChannel {
    pub fn new(url: &str, host: &str, port: u16) -> Option<*mut ZNetChannel> {
        let ring = OwnedBodyRing::new(512 * 1024)?; // 512 KB ring per channel
        let ring = Arc::new(Mutex::new(ring));

        let engine = global_engine();
        let host_c = CString::new(host).ok()?;
        let conn = unsafe { net_connect(engine, host_c.as_ptr(), port) };
        if conn.is_null() {
            return None;
        }

        {
            let ring_guard = ring.lock().ok()?;
            unsafe { net_conn_bind_body_ring(engine, conn, ring_guard.id) };
        }

        let channel = Box::new(ZNetChannel {
            vtable: &ZNET_CHANNEL_VTABLE,
            ref_count: AtomicI32::new(1),
            conn_handle: conn,
            body_ring: ring,
            url: CString::new(url).unwrap_or_default(),
            host: CString::new(host).unwrap_or_default(),
            port,
            request_sent: AtomicBool::new(false),
            status: AtomicI32::new(0),
            content_len: -1,
            listener: Mutex::new(None),
        });

        Some(Box::into_raw(channel))
    }

    unsafe fn from_ptr<'a>(ptr: *mut c_void) -> &'a mut Self {
        unsafe { &mut *(ptr as *mut ZNetChannel) }
    }

    fn send_http_request(&self) -> bool {
        if self.request_sent.swap(true, Ordering::SeqCst) {
            return true;
        }
        let url_str = self.url.to_string_lossy();
        let path = url_str
            .as_ref()
            .split_once("://")
            .and_then(|(_, rest)| rest.find('/').map(|i| &rest[i..]))
            .unwrap_or("/");

        let request = format!(
            "GET {} HTTP/1.1\r\nHost: {}\r\nConnection: close\r\nUser-Agent: zawra-browser/0.1\r\nAccept: */*\r\n\r\n",
            path,
            self.host.to_string_lossy()
        );
        let bytes = request.as_bytes();
        let mut written = 0usize;
        let ret = unsafe {
            net_write(
                global_engine(),
                self.conn_handle,
                bytes.as_ptr(),
                bytes.len(),
                &mut written,
            )
        };
        ret == NetError::None as i32
    }
}

// ── nsIChannel vtable functions ─────────────────────────────────────────────

unsafe extern "C" fn chan_query_interface(
    _this: *mut c_void,
    _iid: *const u8,
    _out: *mut *mut c_void,
) -> u32 {
    ns_result::NS_ERROR_NOT_IMPLEMENTED
}

unsafe extern "C" fn chan_add_ref(this: *mut c_void) -> u32 {
    unsafe { ZNetChannel::from_ptr(this) }
        .ref_count
        .fetch_add(1, Ordering::SeqCst) as u32
}
unsafe extern "C" fn chan_release(this: *mut c_void) -> u32 {
    let c = unsafe { ZNetChannel::from_ptr(this) };
    let prev = c.ref_count.fetch_sub(1, Ordering::SeqCst);
    if prev == 1 {
        unsafe {
            let chan = Box::from_raw(this as *mut ZNetChannel);
            net_close(global_engine(), chan.conn_handle);
        }
    }
    (prev - 1).max(0) as u32
}
unsafe extern "C" fn chan_get_name(this: *mut c_void, name: *mut *const c_char) -> u32 {
    unsafe {
        *name = ZNetChannel::from_ptr(this).url.as_ptr();
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_is_pending(_this: *mut c_void, pending: *mut bool) -> u32 {
    unsafe {
        *pending = true;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_get_status(this: *mut c_void, status: *mut u32) -> u32 {
    unsafe {
        *status = ZNetChannel::from_ptr(this).status.load(Ordering::SeqCst) as u32;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_cancel(this: *mut c_void, status: u32) -> u32 {
    let c = unsafe { ZNetChannel::from_ptr(this) };
    c.status.store(status as i32, Ordering::SeqCst);
    unsafe {
        net_close(global_engine(), c.conn_handle);
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
    unsafe {
        *len = ZNetChannel::from_ptr(this).content_len;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_set_content_length(this: *mut c_void, len: i64) -> u32 {
    unsafe {
        ZNetChannel::from_ptr(this).content_len = len;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_get_uri(this: *mut c_void, uri: *mut *mut c_void) -> u32 {
    unsafe {
        *uri = this;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_open(this: *mut c_void, input_stream: *mut *mut c_void) -> u32 {
    let c = unsafe { ZNetChannel::from_ptr(this) };
    if !c.send_http_request() {
        return ns_result::NS_ERROR_FAILURE;
    }
    let stream = ZNetInputStream::new(c.body_ring.clone());
    unsafe {
        *input_stream = stream as *mut c_void;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_async_open(this: *mut c_void, listener: *mut c_void) -> u32 {
    let c = unsafe { ZNetChannel::from_ptr(this) };
    if let Ok(mut guard) = c.listener.lock() {
        *guard = Some(listener);
    }
    if !c.send_http_request() {
        return ns_result::NS_ERROR_FAILURE;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_get_content_type(_this: *mut c_void, ct: *mut *const c_char) -> u32 {
    unsafe {
        *ct = b"application/octet-stream\0".as_ptr() as *const c_char;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_get_content_charset(_this: *mut c_void, cs: *mut *const c_char) -> u32 {
    unsafe {
        *cs = b"UTF-8\0".as_ptr() as *const c_char;
    }
    ns_result::NS_OK
}
unsafe extern "C" fn chan_cancel_with_reason(
    this: *mut c_void,
    status: u32,
    _reason: *const c_char,
) -> u32 {
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
    set_content_type: chan_nop_ptr_const,
    get_content_charset: chan_get_content_charset,
    set_content_charset: chan_nop_ptr_const,
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
pub unsafe extern "C" fn Zawra_Net_CreateChannel(url: *const c_char) -> *mut c_void {
    if url.is_null() {
        return null_mut();
    }
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

/// Destroy a channel created by `Zawra_Net_CreateChannel`.
///
/// # Safety
/// `channel` must have been returned by `Zawra_Net_CreateChannel`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Net_DestroyChannel(channel: *mut c_void) {
    if channel.is_null() {
        return;
    }
    unsafe { chan_release(channel) };
}

/// Synchronously open the channel and return an `nsIInputStream*`.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Net_Open(channel: *mut c_void, out_stream: *mut *mut c_void) -> i32 {
    if channel.is_null() || out_stream.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    unsafe { chan_open(channel, out_stream) as i32 }
}

/// Asynchronously open the channel; data will arrive via the BodyRing.
///
/// # Safety
/// `channel` must be a valid `ZNetChannel*`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Net_AsyncOpen(channel: *mut c_void, listener: *mut c_void) -> i32 {
    if channel.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    unsafe { chan_async_open(channel, listener) as i32 }
}

/// Read bytes from an `nsIInputStream` obtained via `Zawra_Net_Open`.
///
/// # Safety
/// All pointers must be valid.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Net_Read(
    stream: *mut c_void,
    buf: *mut c_char,
    count: u32,
    bytes_read: *mut u32,
) -> i32 {
    if stream.is_null() || buf.is_null() || bytes_read.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG as i32;
    }
    unsafe { stream_read(stream, buf, count, bytes_read) as i32 }
}
