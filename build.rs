//! Zawra Browser — Build Script
//!
//! Responsibilities:
//!  1. Detect a precompiled `libWPEBackend-fdo.so` / `libwebkit2gtk-4.0.so` in well-known locations.
//!  2. Emit `cargo:rustc-link-*` directives if found.
//!  3. If NOT found, emit a warning but allow the crate to compile in
//!     "headless / network-stack only" mode so CI can still build and test
//!     the glue layer without a full WPE install.

use std::env;
use std::path::{Path, PathBuf};

fn main() {
    // ── Re-run only when relevant files change ──────────────────────────────
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-env-changed=WPE_PATH");
    println!("cargo:rerun-if-env-changed=WEBKIT_PATH");

    // ── Search locations (precedence: env var → common install paths) ────────
    let search_dirs: Vec<PathBuf> = {
        let mut dirs = Vec::new();

        // 1. Explicit environment overrides
        if let Ok(p) = env::var("WEBKIT_PATH") {
            dirs.push(PathBuf::from(p));
        }
        if let Ok(p) = env::var("WPE_PATH") {
            dirs.push(PathBuf::from(p).join("lib"));
        }

        // 2. Common distro locations
        dirs.push(PathBuf::from("/usr/lib/wpe-webkit-1.0"));
        dirs.push(PathBuf::from("/usr/lib64/wpe-webkit-1.0"));
        dirs.push(PathBuf::from("/usr/lib/x86_64-linux-gnu"));
        dirs.push(PathBuf::from("/usr/local/lib"));

        dirs
    };

    // ── Locate libWPE (or WebKitWPE) ──────────────────────────────────────────
    let wpe_found = search_dirs.iter().find_map(|dir| {
        let candidate = dir.join("libWPEBackend-fdo.so");
        if candidate.exists() { Some(dir.clone()) } else { None }
    });

    match wpe_found {
        Some(wpe_dir) => {
            println!("cargo:warning=Found WPE backend at {}", wpe_dir.display());

            // Link against WPE shared objects
            println!("cargo:rustc-link-search=native={}", wpe_dir.display());
            println!("cargo:rustc-link-lib=dylib=WPEBackend-fdo");

            // Emit a cfg flag so conditional WPE code can be activated
            println!("cargo:rustc-cfg=wpe_available");
        }
        None => {
            // No WPE found — emit a prominent warning but don't fail.
            // The glue layer, networking, and storage all compile independently.
            println!("cargo:warning=WPE backend not found. Building in headless mode.");
            println!("cargo:warning=Set WEBKIT_PATH or WPE_PATH to enable WPE linking.");
            println!("cargo:warning=Example: WPE_PATH=/usr/lib/wpe-webkit-1.0 cargo build");
        }
    }

    // ── System libs always needed ────────────────────────────────────────────
    // dl is required for dlopen() which we use to dynamically probe WPE
    println!("cargo:rustc-link-lib=dylib=dl");
}
