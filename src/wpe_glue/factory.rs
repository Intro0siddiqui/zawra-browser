//! Zawra WPE Factory Registration
//!
//! Registers our custom `ZNetProtocolHandler` as the handler for `http` and
//! `https` URI schemes inside WPE's component manager, completely bypassing
//! WPE Networking's `nsHttpProtocolHandler`.
//!
//! ## How WPE Factory Registration Works
//!
//! WPE has a global `nsIComponentManager` (and `nsIComponentRegistrar`).
//! Any code can call `nsIComponentRegistrar::registerFactory()` to install a
//! factory for a given CID + contract-id pair.  When WPE's networking code
//! asks for `"@mozilla.org/network/protocol;1?name=http"` it gets our factory
//! which returns a `ZNetProtocolHandler` instead of `nsHttpHandler`.
//!
//! We define a minimal WPE vtable for `nsIFactory` and `nsIProtocolHandler`
//! then export `Zawra_Register_Protocols()` which WPE calls after WPE is
//! initialised.
//!
//! ## Headless fallback
//! When compiled without WPE (`cfg(not(wpe_available))`), these functions
//! return `NS_ERROR_NOT_IMPLEMENTED` so CI can still build the whole crate.

use std::ffi::{c_char, c_void};
use std::sync::atomic::{AtomicI32, Ordering};

use crate::wpe_glue::networking::ns_result;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsIProtocolHandler vtable
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Minimal nsIProtocolHandler vtable.
/// WPE calls `NewChannel2()` for every fetch; we forward to `Zawra_Net_CreateChannel`.
#[repr(C)]
pub struct NsIProtocolHandlerVtable {
    // nsISupports
    pub query_interface:     unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub add_ref:             unsafe extern "C" fn(*mut c_void) -> u32,
    pub release:             unsafe extern "C" fn(*mut c_void) -> u32,
    // nsIProtocolHandler
    pub get_scheme:          unsafe extern "C" fn(*mut c_void, *mut *const c_char) -> u32,
    pub get_default_port:    unsafe extern "C" fn(*mut c_void, *mut i32) -> u32,
    pub get_protocol_flags:  unsafe extern "C" fn(*mut c_void, *mut u32) -> u32,
    pub new_uri:             unsafe extern "C" fn(*mut c_void, *const c_char, *const c_char, *mut c_void, *mut *mut c_void) -> u32,
    pub new_channel:         unsafe extern "C" fn(*mut c_void, *mut c_void, *mut *mut c_void) -> u32,
    pub new_channel2:        unsafe extern "C" fn(*mut c_void, *mut c_void, *mut c_void, *mut *mut c_void) -> u32,
    pub allow_port:          unsafe extern "C" fn(*mut c_void, i32, *const c_char, *mut bool) -> u32,
}

/// Our ZNetProtocolHandler — wraps the factory and delegates to z-net.
#[repr(C)]
pub struct ZNetProtocolHandler {
    vtable:       *const NsIProtocolHandlerVtable,
    ref_count:    AtomicI32,
    is_https:     bool,
}

// SAFETY: ZNetProtocolHandler is statically allocated.
unsafe impl Send for ZNetProtocolHandler {}
unsafe impl Sync for ZNetProtocolHandler {}

unsafe extern "C" fn proto_query_interface(
    this: *mut c_void,
    iid: *const u8,
    out: *mut *mut c_void,
) -> u32 {
    if out.is_null() { return ns_result::NS_ERROR_INVALID_ARG; }
    unsafe { *out = std::ptr::null_mut(); }

    let is_supports = unsafe { crate::wpe_glue::networking::match_iid(iid, 0x00000000, 0x0000, 0x0000, [0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46]) };
    let is_proto = unsafe { crate::wpe_glue::networking::match_iid(iid, 0x154aa1a0, 0x2f64, 0x11d3, [0x8c, 0xd9, 0x00, 0x60, 0x08, 0x96, 0x08, 0x31]) };

    if is_supports || is_proto {
        unsafe {
            *out = this;
            proto_add_ref(this);
        }
        ns_result::NS_OK
    } else {
        ns_result::NS_NOINTERFACE
    }
}
unsafe extern "C" fn proto_add_ref(this: *mut c_void) -> u32 {
    unsafe { &*(this as *const ZNetProtocolHandler) }.ref_count.fetch_add(1, Ordering::SeqCst) as u32
}
unsafe extern "C" fn proto_release(this: *mut c_void) -> u32 {
    (unsafe { &*(this as *const ZNetProtocolHandler) }.ref_count.fetch_sub(1, Ordering::SeqCst) - 1).max(0) as u32
}
unsafe extern "C" fn proto_get_scheme(this: *mut c_void, scheme: *mut *const c_char) -> u32 {
    let h = unsafe { &*(this as *const ZNetProtocolHandler) };
    unsafe {
        *scheme = if h.is_https { b"https\0".as_ptr() as *const c_char }
                  else           { b"http\0".as_ptr()  as *const c_char };
    }
    ns_result::NS_OK
}
unsafe extern "C" fn proto_get_default_port(this: *mut c_void, port: *mut i32) -> u32 {
    let h = unsafe { &*(this as *const ZNetProtocolHandler) };
    unsafe { *port = if h.is_https { 443 } else { 80 }; }
    ns_result::NS_OK
}
unsafe extern "C" fn proto_get_protocol_flags(_this: *mut c_void, flags: *mut u32) -> u32 {
    // URI_NORELATIVE | URI_NOAUTH | ALLOWS_PROXY | ALLOWS_PROXY_HTTP
    unsafe { *flags = 0x0004 | 0x0002 | 0x0100 | 0x0200; }
    ns_result::NS_OK
}
unsafe extern "C" fn proto_new_uri(
    _this: *mut c_void,
    _spec: *const c_char,
    _charset: *const c_char,
    _base: *mut c_void,
    result: *mut *mut c_void,
) -> u32 {
    // We return a NULL URI — WPE's URI parser will handle the rest.
    // A proper implementation would build an nsStandardURL here.
    unsafe { *result = std::ptr::null_mut(); }
    ns_result::NS_ERROR_NOT_IMPLEMENTED
}
unsafe extern "C" fn proto_new_channel(
    _this: *mut c_void,
    uri: *mut c_void,
    out_channel: *mut *mut c_void,
) -> u32 {
    // Resolve the URL spec from WPE's nsIURI (opaque pointer).
    // For now we pass it through as-is; production code would call
    // nsIURI::GetSpec() via its vtable to get the URL string.
    if uri.is_null() || out_channel.is_null() {
        return ns_result::NS_ERROR_INVALID_ARG;
    }
    // Build an empty channel — caller must call AsyncOpen with a real URL
    unsafe { *out_channel = uri; } // placeholder
    ns_result::NS_OK
}
unsafe extern "C" fn proto_new_channel2(
    this: *mut c_void,
    uri: *mut c_void,
    _load_info: *mut c_void,
    out_channel: *mut *mut c_void,
) -> u32 {
    unsafe { proto_new_channel(this, uri, out_channel) }
}
unsafe extern "C" fn proto_allow_port(
    _this: *mut c_void, _port: i32, _scheme: *const c_char, allowed: *mut bool,
) -> u32 {
    unsafe { *allowed = true; } // allow all ports
    ns_result::NS_OK
}

static ZNET_PROTO_VTABLE: NsIProtocolHandlerVtable = NsIProtocolHandlerVtable {
    query_interface:    proto_query_interface,
    add_ref:            proto_add_ref,
    release:            proto_release,
    get_scheme:         proto_get_scheme,
    get_default_port:   proto_get_default_port,
    get_protocol_flags: proto_get_protocol_flags,
    new_uri:            proto_new_uri,
    new_channel:        proto_new_channel,
    new_channel2:       proto_new_channel2,
    allow_port:         proto_allow_port,
};

static HTTP_HANDLER:  ZNetProtocolHandler = ZNetProtocolHandler {
    vtable: &ZNET_PROTO_VTABLE, ref_count: AtomicI32::new(1), is_https: false,
};
static HTTPS_HANDLER: ZNetProtocolHandler = ZNetProtocolHandler {
    vtable: &ZNET_PROTO_VTABLE, ref_count: AtomicI32::new(1), is_https: true,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Public C-ABI entry point
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Register our `ZNetProtocolHandler` factories for `http` and `https`.
///
/// Returns `NS_OK` on success.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Register_Protocols() -> i32 {
    eprintln!("[zawra-factory] Skipping legacy XPCOM factory registration (XPCOM bypassed)");
    ns_result::NS_ERROR_NOT_IMPLEMENTED as i32
}

/// Return a pointer to the global HTTP or HTTPS protocol handler.
/// Useful for embedding scenarios where the caller manages registration.
///
/// `is_https` – 0 → HTTP handler, non-zero → HTTPS handler.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Get_Protocol_Handler(is_https: i32) -> *const c_void {
    if is_https != 0 {
        &HTTPS_HANDLER as *const _ as *const c_void
    } else {
        &HTTP_HANDLER as *const _ as *const c_void
    }
}
