//! Zawra Browser — Build Script
//!
//! Responsibilities:
//!  1. Detect a precompiled `libWPEBackend-fdo.so` / `libwebkit2gtk-4.0.so` in well-known locations.
//!  2. Emit `cargo:rustc-link-*` directives if found.
//!  3. If NOT found, emit a warning but allow the crate to compile in
//!     "headless / network-stack only" mode so CI can still build and test
//!     the glue layer without a full WPE install.

use std::env;
use std::path::PathBuf;

fn main() {
    // Declare known custom cfg flags to rustc check-cfg
    println!("cargo:rustc-check-cfg=cfg(wpe_available)");

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
        let target_os = env::var("CARGO_CFG_TARGET_OS").unwrap_or_default();
        if target_os == "macos" {
            dirs.push(PathBuf::from("/opt/homebrew/lib"));
            dirs.push(PathBuf::from("/usr/local/lib"));
        } else {
            dirs.push(PathBuf::from("/usr/lib"));
            dirs.push(PathBuf::from("/usr/lib/wpe-webkit-1.0"));
            dirs.push(PathBuf::from("/usr/lib64/wpe-webkit-1.0"));
            dirs.push(PathBuf::from("/usr/lib/x86_64-linux-gnu"));
            dirs.push(PathBuf::from("/usr/local/lib"));
        }

        dirs
    };

    // ── Locate libWPE (or WebKitWPE) ──────────────────────────────────────────
    let target_os = env::var("CARGO_CFG_TARGET_OS").unwrap_or_default();
    let is_macos = target_os == "macos";

    let wpe_info = search_dirs.iter().find_map(|dir| {
        let ext = if is_macos { "dylib" } else { "so" };
        let candidate = dir.join(format!("libWPEBackend-fdo.{}", ext));
        if candidate.exists() {
            return Some((dir.clone(), "WPEBackend-fdo"));
        }
        let candidate_alt = dir.join(format!("libWPEBackend-fdo-1.0.{}", ext));
        if candidate_alt.exists() {
            return Some((dir.clone(), "WPEBackend-fdo-1.0"));
        }
        if is_macos {
            let candidate_so = dir.join("libWPEBackend-fdo.so");
            if candidate_so.exists() {
                return Some((dir.clone(), "WPEBackend-fdo"));
            }
        }
        None
    });

    match wpe_info {
        Some((wpe_dir, lib_name)) => {
            println!("cargo:warning=Found WPE backend at {} (linking {})", wpe_dir.display(), lib_name);

            // Link against WPE shared objects
            println!("cargo:rustc-link-search=native={}", wpe_dir.display());
            println!("cargo:rustc-link-lib=dylib={}", lib_name);

            // Emit a cfg flag so conditional WPE code can be activated
            // println!("cargo:rustc-cfg=wpe_available");
        }
        None => {
            // No WPE found — emit a prominent warning but don't fail.
            // The glue layer, networking, and storage all compile independently.
            println!("cargo:warning=WPE backend not found. Building in headless mode.");
            println!("cargo:warning=Set WEBKIT_PATH or WPE_PATH to enable WPE linking.");
            println!("cargo:warning=Example: WPE_PATH=/usr/lib/wpe-webkit-1.0 cargo build");
        }
    }

    // ── System libs ──────────────────────────────────────────────────────────
    // dl is required for dlopen() on desktop Linux/glibc, but is part of libc/libSystem on modern Android and macOS
    if target_os != "android" && target_os != "macos" {
        println!("cargo:rustc-link-lib=dylib=dl");
    }
}
