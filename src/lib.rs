// Zawra Browser (2026 Edition)
//
// Architecture:
//   - wpe_glue:   Integration layer that replaces WPE's networking and
//                 storage with z-net and BrowserDB respectively.
//   - ui:         Browser window, tab manager, address bar, renderer embed.
//   - lean_net:   z-net Rust network engine (zero-copy BodyRing I/O)
//   - browserdb:  LSM-tree storage engine (history, cache, cookies, blobs)

/// WPE integration glue — networking bypass (z-net) + storage bypass (BrowserDB)
pub mod wpe_glue;

/// Browser UI — window, tabs, address bar, renderer embedding
pub mod ui;

// Expose the real engines at crate root for direct use by other modules
pub use browserdb;
pub use lean_net;

// JavaScriptCore zero-copy ArrayBuffer bridge (jsc_glue)
pub mod zero_copy;

// Mocking external dependencies that aren't available in this standalone environment
pub mod javascriptcore {
    pub mod jsapi {
        pub enum JSContext {}
        pub enum JSObject {}
        pub type JSExternalArrayBufferContentsDeleter =
            unsafe extern "C" fn(*mut libc::c_void, *mut libc::c_void);

        #[allow(non_snake_case)]
        pub unsafe fn JS_NewExternalArrayBuffer(
            _cx: *mut JSContext,
            _size: usize,
            _contents: *mut libc::c_void,
            _deleter: Option<JSExternalArrayBufferContentsDeleter>,
            _user_data: *mut libc::c_void,
        ) -> *mut JSObject {
            std::ptr::null_mut()
        }
    }
}

pub mod net_traits {
    pub mod request {
        pub struct Request;
        impl Request {
            pub fn url(&self) -> String {
                String::new()
            }
        }
    }
    pub mod response {
        pub struct Response;
        pub enum ResponseBody {
            Empty,
        }
        impl Response {
            pub fn new(_url: String, _body: ResponseBody) -> Self {
                Response
            }
        }
    }
    pub enum NetworkError {}
}

pub mod storage_traits {
    pub mod indexeddb {
        pub enum CreateObjectResult {
            ObjectStoreCreated,
        }
        pub struct KeyPath;
        pub struct KeyRange {
            pub lower: Option<Key>,
            pub upper: Option<Key>,
            pub lower_open: bool,
            pub upper_open: bool,
        }
        pub struct Key;
        impl Key {
            pub fn encode(&self) -> Vec<u8> {
                vec![]
            }
        }
    }
}

pub mod malloc_size_of {
    pub trait MallocSizeOf {
        fn size_of(&self, ops: &mut MallocSizeOfOps) -> usize;
    }
    pub struct MallocSizeOfOps;
}

pub mod tokio {
    pub mod sync {
        pub mod oneshot {
            pub struct Sender<T>(std::marker::PhantomData<T>);
            pub struct Receiver<T>(std::marker::PhantomData<T>);
            pub fn channel<T>() -> (Sender<T>, Receiver<T>) {
                (
                    Sender(std::marker::PhantomData),
                    Receiver(std::marker::PhantomData),
                )
            }
        }
    }
}

pub mod engines {
    pub use crate::crate_internal::engines::*;
}

pub mod crate_internal {
    pub mod engines {
        pub trait KvsEngine {
            type Error;
            fn create_store(
                &self,
                name: &str,
                key_path: Option<crate::storage_traits::indexeddb::KeyPath>,
                auto_increment: bool,
            ) -> Result<crate::storage_traits::indexeddb::CreateObjectResult, Self::Error>;
            fn process_transaction(
                &self,
                transaction: KvsTransaction,
                on_complete: Box<dyn FnOnce() + Send + 'static>,
            );
        }
        pub struct KvsTransaction;
    }
}
