use std::slice;
use ring::digest;
use ring::aead::{self, BoundKey, UnboundKey, Nonce, Aad, NonceSequence, SealingKey, OpeningKey};

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
pub unsafe extern "C" fn Zawra_Crypto_Digest(
    algo: u32,
    data_ptr: *const u8,
    data_len: usize,
    out_ptr: *mut u8,
) -> i32 {
    if data_ptr.is_null() || out_ptr.is_null() {
        return NS_ERROR_FAILURE;
    }
    let data = unsafe { slice::from_raw_parts(data_ptr, data_len) };
    let algorithm = match algo {
        3 => &digest::SHA256, // SHA-256
        4 => &digest::SHA512, // SHA-512
        _ => return NS_ERROR_FAILURE,
    };
    let hash = digest::digest(algorithm, data);
    unsafe {
        std::ptr::copy_nonoverlapping(hash.as_ref().as_ptr(), out_ptr, hash.as_ref().len());
    }
    NS_OK
}

struct OneNonce(Option<Nonce>);

impl NonceSequence for OneNonce {
    fn advance(&mut self) -> Result<Nonce, ring::error::Unspecified> {
        self.0.take().ok_or(ring::error::Unspecified)
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Crypto_Encrypt_GCM(
    key_ptr: *const u8,
    key_len: usize,
    iv_ptr: *const u8,
    iv_len: usize,
    aad_ptr: *const u8,
    aad_len: usize,
    plain_ptr: *const u8,
    plain_len: usize,
    out_ptr: *mut u8, // Output buffer, must be at least plain_len + tag_len
    tag_len: usize,
) -> i32 {
    if key_ptr.is_null() || iv_ptr.is_null() || plain_ptr.is_null() || out_ptr.is_null() {
        return NS_ERROR_FAILURE;
    }

    let (key_slice, iv_slice, aad_slice) = unsafe {
        (
            slice::from_raw_parts(key_ptr, key_len),
            slice::from_raw_parts(iv_ptr, iv_len),
            if aad_ptr.is_null() { &[] } else { slice::from_raw_parts(aad_ptr, aad_len) },
        )
    };

    let algorithm = match key_len {
        16 => &aead::AES_128_GCM,
        32 => &aead::AES_256_GCM,
        _ => return NS_ERROR_FAILURE, // ring does not support 192-bit keys
    };

    let unbound_key = match UnboundKey::new(algorithm, key_slice) {
        Ok(k) => k,
        Err(_) => return NS_ERROR_FAILURE,
    };

    if iv_len != 12 {
        return NS_ERROR_FAILURE; // GCM standard nonce length is 96 bits (12 bytes)
    }
    let mut nonce_bytes = [0u8; 12];
    nonce_bytes.copy_from_slice(iv_slice);
    let nonce = Nonce::assume_unique_for_key(nonce_bytes);
    let nonce_seq = OneNonce(Some(nonce));

    let mut sealing_key = SealingKey::new(unbound_key, nonce_seq);
    
    // Copy plaintext to output buffer first because seal_in_place uses it as both input and output
    unsafe {
        std::ptr::copy_nonoverlapping(plain_ptr, out_ptr, plain_len);
    }
    let out_slice = unsafe { slice::from_raw_parts_mut(out_ptr, plain_len + tag_len) };
    
    match sealing_key.seal_in_place_separate_tag(Aad::from(aad_slice), &mut out_slice[..plain_len]) {
        Ok(tag) => {
            let tag_bytes = tag.as_ref();
            if tag_bytes.len() != tag_len {
                // If the provided tag_len doesn't match what ring produced (usually 16),
                // we only copy up to tag_len if it's smaller, or fail if it's larger.
                // However, GCM usually expects a specific tag length.
                if tag_len > tag_bytes.len() {
                    return NS_ERROR_FAILURE;
                }
            }
            out_slice[plain_len..plain_len + tag_len].copy_from_slice(&tag_bytes[..tag_len]);
            NS_OK
        }
        Err(_) => NS_ERROR_FAILURE,
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn Zawra_Crypto_Decrypt_GCM(
    key_ptr: *const u8,
    key_len: usize,
    iv_ptr: *const u8,
    iv_len: usize,
    aad_ptr: *const u8,
    aad_len: usize,
    cipher_ptr: *const u8,
    cipher_len: usize, // length of ciphertext INCLUDING tag
    out_ptr: *mut u8,   // Output buffer, must be at least cipher_len - tag_len
    tag_len: usize,
) -> i32 {
    if key_ptr.is_null() || iv_ptr.is_null() || cipher_ptr.is_null() || out_ptr.is_null() {
        return NS_ERROR_FAILURE;
    }

    let (key_slice, iv_slice, aad_slice, cipher_slice) = unsafe {
        (
            slice::from_raw_parts(key_ptr, key_len),
            slice::from_raw_parts(iv_ptr, iv_len),
            if aad_ptr.is_null() { &[] } else { slice::from_raw_parts(aad_ptr, aad_len) },
            slice::from_raw_parts(cipher_ptr, cipher_len),
        )
    };

    let algorithm = match key_len {
        16 => &aead::AES_128_GCM,
        32 => &aead::AES_256_GCM,
        _ => return NS_ERROR_FAILURE,
    };

    let unbound_key = match UnboundKey::new(algorithm, key_slice) {
        Ok(k) => k,
        Err(_) => return NS_ERROR_FAILURE,
    };

    if iv_len != 12 {
        return NS_ERROR_FAILURE;
    }
    let mut nonce_bytes = [0u8; 12];
    nonce_bytes.copy_from_slice(iv_slice);
    let nonce = Nonce::assume_unique_for_key(nonce_bytes);
    let nonce_seq = OneNonce(Some(nonce));

    let mut opening_key = OpeningKey::new(unbound_key, nonce_seq);

    // Copy ciphertext to a temporary vector for decryption.
    // ring's open_in_place verifies the tag and decrypts.
    let mut in_out = cipher_slice.to_vec();
    match opening_key.open_in_place(Aad::from(aad_slice), &mut in_out) {
        Ok(plaintext) => {
            let plain_len = plaintext.len();
            if plain_len != cipher_len - tag_len {
                return NS_ERROR_FAILURE;
            }
            unsafe {
                std::ptr::copy_nonoverlapping(plaintext.as_ptr(), out_ptr, plain_len);
            }
            NS_OK
        }
        Err(_) => NS_ERROR_FAILURE,
    }
}

// Existing functions kept for compatibility if needed, but updated to use the same style
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
    NS_ERROR_FAILURE 
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
    NS_ERROR_FAILURE
}
