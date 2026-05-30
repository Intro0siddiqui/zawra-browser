use std::os::raw::{c_char, c_int};
use std::slice;

// Standard NS error codes used by WebKit
const NS_OK: i32 = 0;
const NS_ERROR_FAILURE: i32 = -1;

#[repr(u32)]
pub enum CryptoAlgo {
    AesCbc = 0,
    AesCtr = 1,
    AesGcm = 2,
    Sha256 = 3,
    Sha512 = 4,
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Crypto_Encrypt(
    _algo:   u32,
    _key_ptr: *const u8,
    _key_len: usize,
    _iv_ptr:  *const u8,
    _iv_len:  usize,
    _in_ptr:  *const u8,
    _in_len:  usize,
    _out_ptr: *mut u8,
    _out_len: *mut usize,
) -> i32 {
    NS_ERROR_FAILURE // Fallback to gcrypt for now
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Crypto_Decrypt(
    _algo:   u32,
    _key_ptr: *const u8,
    _key_len: usize,
    _iv_ptr:  *const u8,
    _iv_len:  usize,
    _in_ptr:  *const u8,
    _in_len:  usize,
    _out_ptr: *mut u8,
    _out_len: *mut usize,
) -> i32 {
    NS_ERROR_FAILURE // Fallback to gcrypt for now
}
