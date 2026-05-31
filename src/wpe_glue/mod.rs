//! Zawra Browser — Top-Level Module
//!
//! Organises the entire WPE integration layer:
//!
//! | Submodule          | Replaces                                        |
//! |--------------------|-------------------------------------------------|
//! | `networking`       | WPE Networking Layer (Soup/Custom)              |
//! | `storage`          | WPE Storage / WebsiteData                       |
//! | `init`             | Unified startup / shutdown entry points         |
//! | `launcher`         | dlopen libWPE, WPE bootstrap                    |
//! | `factory`          | WPE protocol registration                       |
//! | `streaming`        | BodyRing full pull-style integration            |
//! | `zero_copy_bridge` | JavaScriptCore ArrayBuffer ↔ BrowserDB          |
//!
//! ## Complete C-ABI Surface
//!
//! ### Bootstrap
//! ```c
//! int32_t Zawra_Bootstrap(const char *profile_path);
//! int32_t Zawra_Init_Subsystems(const char *profile_path);
//! void    Zawra_Shutdown_Subsystems(void);
//! void    Zawra_ProcessShutdown(void);
//! ```
//!
//! ### Protocol Factory
//! ```c
//! int32_t     Zawra_Register_Protocols(void);
//! const void *Zawra_Get_Protocol_Handler(int32_t is_https);
//! ```
//!
//! ### Networking (WPE bypass)
//! ```c
//! void   *Zawra_Net_CreateChannel(const char *url);
//! void    Zawra_Net_DestroyChannel(void *channel);
//! int32_t Zawra_Net_Open(void *channel, void **out_stream);
//! int32_t Zawra_Net_AsyncOpen(void *channel, void *listener);
//! int32_t Zawra_Net_Read(void *stream, char *buf, uint32_t count, uint32_t *bytes_read);
//! ```
//!
//! ### Streaming
//! ```c
//! int32_t Zawra_ParseHttpHead(const uint8_t *buf, size_t len,
//!                             uint16_t *status, size_t *body_offset, int64_t *content_len);
//! ```
//!
//! ### Storage (WPE bypass)
//! ```c
//! int32_t Zawra_Storage_Init(const char *profile_path);
//! int32_t Zawra_Cache_Put(...);   int32_t Zawra_Cache_Get(...);
//! int32_t Zawra_Cache_Has(uint64_t url_hi, uint64_t url_lo);
//! int32_t Zawra_Storage_PutBlob(...); int32_t Zawra_Storage_GetBlob(...);
//! int32_t Zawra_Storage_DeleteBlob(...);
//! int32_t Zawra_Cookie_Put(...);  int32_t Zawra_Cookie_Get(...);
//! int32_t Zawra_LocalStorage_Put(...); int32_t Zawra_LocalStorage_Get(...);
//! int32_t Zawra_History_Put(...);
//! int32_t Zawra_Storage_Stats(ZawraStorageStats *stats);
//! int32_t Zawra_Storage_Wipe(void);
//! void    Zawra_Free_Buffer(uint8_t *ptr, size_t len);
//! ```
//!
//! ### JavaScriptCore Zero-Copy
//! ```c
//! JSObject *Zawra_JS_CreateCacheBuffer(JSContext *cx, uint64_t url_hi, uint64_t url_lo);
//! ```

pub mod networking;
pub mod storage;
pub mod init;
pub mod launcher;
pub mod factory;
pub mod streaming;
pub mod zero_copy_bridge;
pub mod threading;
pub mod crypto;
