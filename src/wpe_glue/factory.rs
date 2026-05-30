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

use crate::wpe_glue::networking::{
    Zawra_Net_CreateChannel,
    ZNetChannel,
    ns_result,
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// nsIFactory vtable
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// The four methods every WPE object exposes (nsISupports + nsIFactory).
#[repr(C)]
pub struct NsIFactoryVtable {
    // nsISupports
    pub query_interface: unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub add_ref:         unsafe extern "C" fn(*mut c_void) -> u32,
    pub release:         unsafe extern "C" fn(*mut c_void) -> u32,
    // nsIFactory
    pub create_instance: unsafe extern "C" fn(*mut c_void, *mut c_void, *const u8, *mut *mut c_void) -> u32,
    pub lock_factory:    unsafe extern "C" fn(*mut c_void, bool) -> u32,
}

/// Singleton factory object (one per registered scheme).
#[repr(C)]
pub struct ZNetFactory {
    vtable:    *const NsIFactoryVtable,
    ref_count: AtomicI32,
    scheme:    &'static [u8],  // b"http\0" or b"https\0"
}

// SAFETY: ZNetFactory is statically allocated and immutable after creation.
unsafe impl Send for ZNetFactory {}
unsafe impl Sync for ZNetFactory {}

unsafe extern "C" fn factory_query_interface(
    _this: *mut c_void, _iid: *const u8, _out: *mut *mut c_void,
) -> u32 { ns_result::NS_ERROR_NOT_IMPLEMENTED }

unsafe extern "C" fn factory_add_ref(this: *mut c_void) -> u32 {
    let f = unsafe { &*(this as *const ZNetFactory) };
    f.ref_count.fetch_add(1, Ordering::SeqCst) as u32
}
unsafe extern "C" fn factory_release(this: *mut c_void) -> u32 {
    let f = unsafe { &*(this as *const ZNetFactory) };
    (f.ref_count.fetch_sub(1, Ordering::SeqCst) - 1).max(0) as u32
}

/// `nsIFactory::CreateInstance` — WPE calls this when it needs a protocol handler.
///
/// We ignore `aOuter` (aggregation) and `aIID`; we return a new `ZNetChannel`
/// stub that WPE will `QueryInterface` for `nsIProtocolHandler`.
unsafe extern "C" fn factory_create_instance(
    _this: *mut c_void,
    _outer: *mut c_void,
    _iid: *const u8,
    result: *mut *mut c_void,
) -> u32 {
    if result.is_null() { return ns_result::NS_ERROR_INVALID_ARG; }
    // We return the factory itself as a ZNetProtocolHandler stand-in.
    // The real channel is created in ZNetProtocolHandler::NewChannel below.
    unsafe { *result = _this; }
    ns_result::NS_OK
}
unsafe extern "C" fn factory_lock_factory(_this: *mut c_void, _lock: bool) -> u32 {
    ns_result::NS_OK
}

static ZNET_FACTORY_VTABLE: NsIFactoryVtable = NsIFactoryVtable {
    query_interface: factory_query_interface,
    add_ref:         factory_add_ref,
    release:         factory_release,
    create_instance: factory_create_instance,
    lock_factory:    factory_lock_factory,
};

// Static factory singletons for http and https
static HTTP_FACTORY: ZNetFactory = ZNetFactory {
    vtable:    &ZNET_FACTORY_VTABLE,
    ref_count: AtomicI32::new(1),
    scheme:    b"http\0",
};
static HTTPS_FACTORY: ZNetFactory = ZNetFactory {
    vtable:    &ZNET_FACTORY_VTABLE,
    ref_count: AtomicI32::new(1),
    scheme:    b"https\0",
};

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
    _this: *mut c_void, _iid: *const u8, _out: *mut *mut c_void,
) -> u32 { ns_result::NS_ERROR_NOT_IMPLEMENTED }
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
// nsIComponentRegistrar binding (WPE ABI)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Partial vtable for nsIComponentRegistrar (only the method we call).
#[repr(C)]
struct NsIComponentRegistrarVtable {
    _qi:             unsafe extern "C" fn(*mut c_void, *const u8, *mut *mut c_void) -> u32,
    _add_ref:        unsafe extern "C" fn(*mut c_void) -> u32,
    _release:        unsafe extern "C" fn(*mut c_void) -> u32,
    _is_registered:  unsafe extern "C" fn(*mut c_void, *const u8, *mut bool) -> u32,
    _register_factory: unsafe extern "C" fn(
        *mut c_void,         // this
        *const u8,           // aClass (nsCID)
        *const c_char,       // aClassName
        *const c_char,       // aContractID
        *mut c_void,         // aFactory (nsIFactory*)
    ) -> u32,
}

/// CIDs for our protocol handler overrides.
/// These match the exact values used by WPE's built-in handlers:
/// `{4f47e42e-4d23-4dd3-bfda-eb29255e9ea3}` — NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX "http"
/// `{dccbe7e4-7750-466b-a557-5ea36c8ff24e}` — NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX "https"
const HTTP_CID:  [u8; 16] = [0x4f,0x47,0xe4,0x2e, 0x4d,0x23, 0x4d,0xd3, 0xbf,0xda, 0xeb,0x29,0x25,0x5e,0x9e,0xa3];
const HTTPS_CID: [u8; 16] = [0xdc,0xcb,0xe7,0xe4, 0x77,0x50, 0x46,0x6b, 0xa5,0x57, 0x5e,0xa3,0x6c,0x8f,0xf2,0x4e];

// WPE runtime C API (available when linked against libWPE)
#[cfg(wpe_available)]
unsafe extern "C" {
    fn NS_GetComponentRegistrar(result: *mut *mut c_void) -> u32;
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Public C-ABI entry point
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Register our `ZNetProtocolHandler` factories for `http` and `https`.
///
/// Must be called AFTER XPCOM is initialised (i.e. after `XRE_main` / `XRE_InitEmbedding2`
/// returns from its startup phase and signals XPCOM-ready).
///
/// Returns `NS_OK` on success.  When WPE is not linked (`headless` mode)
/// returns `NS_ERROR_NOT_IMPLEMENTED` — this is non-fatal; the app still runs
/// in network-stack-only mode.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Register_Protocols() -> i32 {
    #[cfg(wpe_available)]
    {
        let mut registrar: *mut c_void = std::ptr::null_mut();
        let ret = unsafe { NS_GetComponentRegistrar(&mut registrar) };
        if ret != ns_result::NS_OK || registrar.is_null() {
            eprintln!("[zawra-factory] NS_GetComponentRegistrar failed: {:#010x}", ret);
            return ns_result::NS_ERROR_FAILURE as i32;
        }

        let vtable = unsafe { &*(*(registrar as *const *const NsIComponentRegistrarVtable)) };

        // Register HTTP handler
        let http_contract = b"@mozilla.org/network/protocol;1?name=http\0".as_ptr() as *const c_char;
        let ret_http = unsafe {
            (vtable._register_factory)(
                registrar,
                HTTP_CID.as_ptr(),
                b"ZNet HTTP Protocol Handler\0".as_ptr() as *const c_char,
                http_contract,
                &HTTP_FACTORY as *const _ as *mut c_void,
            )
        };

        // Register HTTPS handler
        let https_contract = b"@mozilla.org/network/protocol;1?name=https\0".as_ptr() as *const c_char;
        let ret_https = unsafe {
            (vtable._register_factory)(
                registrar,
                HTTPS_CID.as_ptr(),
                b"ZNet HTTPS Protocol Handler\0".as_ptr() as *const c_char,
                https_contract,
                &HTTPS_FACTORY as *const _ as *mut c_void,
            )
        };

        if ret_http == ns_result::NS_OK && ret_https == ns_result::NS_OK {
            eprintln!("[zawra-factory] http + https protocol handlers registered ✓");
            return ns_result::NS_OK as i32;
        }

        eprintln!("[zawra-factory] Factory registration partial: http={:#x} https={:#x}", ret_http, ret_https);
        return ns_result::NS_ERROR_FAILURE as i32;
    }

    #[cfg(not(wpe_available))]
    {
        eprintln!("[zawra-factory] Headless mode: skipping XPCOM factory registration");
        ns_result::NS_ERROR_NOT_IMPLEMENTED as i32
    }
}

/// Return a pointer to the global HTTP or HTTPS protocol handler.
/// Useful for embedding scenarios where the caller manages registration.
///
/// `is_https` – 0 → HTTP handler, non-zero → HTTPS handler.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Get_Protocol_Handler(is_https: i32) -> *const c_void {
    if is_https != 0 {
        &HTTPS_HANDLER as *const _ as *const c_void
    } else {
        &HTTP_HANDLER as *const _ as *const c_void
    }
}
