//! Zawra Browser UI — Tab-Based Window Architecture
//!
//! This module defines the browser UI layer that sits between WPE's
//! content process and the native window system. It provides:
//!
//! - `BrowserWindow` — the top-level native window
//! - `TabManager` — creates, closes, switches tabs
//! - `AddressBar` — URL input + navigation controls
//! - `RendererEmbed` — WPE content area embedding widget

pub mod window;
pub mod tabs;
pub mod address_bar;
pub mod renderer;
