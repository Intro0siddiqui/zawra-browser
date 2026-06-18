//! Agnostic Threading Bridge
//!
//! Provides OS-agnostic threading primitives via Hajr.

use std::os::raw::{c_void, c_int};

#[cfg(target_os = "windows")]
pub type ThreadHandle = *mut c_void;

#[cfg(not(target_os = "windows"))]
pub type ThreadHandle = usize;

unsafe extern "C" {
    fn hajr_thread_create(
        func: unsafe extern "C" fn(*mut c_void) -> *mut c_void,
        arg: *mut c_void,
    ) -> ThreadHandle;

    fn hajr_thread_join(handle: ThreadHandle) -> c_int;

    fn hajr_thread_set_priority(handle: ThreadHandle, priority: u8) -> c_int;
}

/// Create a new thread using Hajr's agnostic threading API.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Thread_Create(
    func: unsafe extern "C" fn(*mut c_void) -> *mut c_void,
    arg: *mut c_void,
) -> ThreadHandle {
    unsafe { hajr_thread_create(func, arg) }
}

/// Join a thread created via Zawra_Thread_Create.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Thread_Join(handle: ThreadHandle) -> c_int {
    unsafe { hajr_thread_join(handle) }
}

/// Set the priority of a thread.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn Z_Thread_SetPriority(handle: ThreadHandle, priority: u8) -> c_int {
    unsafe { hajr_thread_set_priority(handle, priority) }
}
