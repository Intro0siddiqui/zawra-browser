use lean_net::{
    net_engine_create, net_http_execute_streaming, ZNetHttpStreamCallbacks
};
use std::ffi::{c_char, c_void, CString};

struct State {
    status: u16,
    total_bytes: usize,
    first_chunk: Vec<u8>,
}

extern "C" fn on_headers(status: u16, _reason: *const c_char, count: usize, names: *const *const c_char, values: *const *const c_char, user_data: *mut c_void) {
    let s = unsafe { &mut *(user_data as *mut State) };
    s.status = status;
    println!("Headers received: status={}, count={}", status, count);
    for i in 0..count {
        unsafe {
            let k = std::ffi::CStr::from_ptr(*names.add(i)).to_string_lossy();
            let v = std::ffi::CStr::from_ptr(*values.add(i)).to_string_lossy();
            println!("  [{}] '{}': '{}' (len={})", i, k, v, v.len());
        }
    }
}

extern "C" fn on_data(chunk: *const u8, len: usize, user_data: *mut c_void) {
    let s = unsafe { &mut *(user_data as *mut State) };
    s.total_bytes += len;
    if s.first_chunk.is_empty() {
        let slice = unsafe { std::slice::from_raw_parts(chunk, len.min(100)) };
        s.first_chunk.extend_from_slice(slice);
    }
}

extern "C" fn on_complete(keep_alive: bool, _user_data: *mut c_void) {
    println!("Complete! keep_alive={}", keep_alive);
}

extern "C" fn is_cancelled(_user_data: *mut c_void) -> bool {
    false
}

fn main() {
    let engine = net_engine_create();
    let mut state = State {
        status: 0,
        total_bytes: 0,
        first_chunk: Vec::new(),
    };

    let cb = ZNetHttpStreamCallbacks {
        user_data: &mut state as *mut _ as *mut c_void,
        on_headers: Some(on_headers),
        on_data: Some(on_data),
        on_complete: Some(on_complete),
        is_cancelled: Some(is_cancelled),
    };

    let method = CString::new("GET").unwrap();
    let url = CString::new("https://www.youtube.com/").unwrap();

    let h_name = CString::new("Accept-Encoding").unwrap();
    let h_val = CString::new("identity").unwrap();
    let names = [h_name.as_ptr()];
    let values = [h_val.as_ptr()];

    let rc = net_http_execute_streaming(
        engine,
        0,
        method.as_ptr(),
        url.as_ptr(),
        std::ptr::null(),
        std::ptr::null(),
        0,
        std::ptr::null(),
        0,
        0,
        &cb,
    );
    println!("net_http_execute_streaming returned rc={}, total_bytes={}", rc, state.total_bytes);
    if !state.first_chunk.is_empty() {
        println!("First bytes: {:?}", &state.first_chunk[..state.first_chunk.len().min(50)]);
        if let Ok(s) = std::str::from_utf8(&state.first_chunk) {
            println!("First text:\n{}", s);
        }
    }
}
