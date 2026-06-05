# Hajr Integration Plan

## Objective
Finalize the Hajr integration by migrating to a pure ring IPC architecture and activating MPK/MTE hardware isolation and namespaces for sandboxed processes.

## Issue 4: Hajr IPC Hybrid to Pure Ring
- **Current State:** `ConnectionUnix.cpp` uses a Unix socket for `kick` signals and FD passing (`SCM_RIGHTS`), making it a hybrid IPC model rather than pure ring.
- **Proposed Solution:**
  - **Wakeups:** Replace the Unix socket `send()` kicks with a native Hajr lock-free event mechanism or an `eventfd` triggered via Zig (`hajr_ring_signal()`).
  - **FD Passing:** Remove FD passing logic from WebKit's `ConnectionUnix.cpp`. Instead, introduce a Hajr-brokered FFI function `hajr_ipc_send_fd()`. Hajr will manage the FD transfer transparently (e.g., using `pidfd_getfd` on Linux or a dedicated hidden internal channel) so the WebKit IPC interface is purely ring-based from WebKit's perspective.
  - **Cleanup:** Remove the socket pair creation and socket references from `ProcessLauncherGLib.cpp` and `ConnectionUnix.cpp`.

## Issue 5: MPK and Namespace Isolation
- **Current State:** `Zawra_Hajr_SpawnProcess` in Rust uses a plain `std::process::Command::spawn()` without namespaces or MPK.
- **Proposed Solution:**
  - **Zig Delegation:** Instead of duplicating OS abstraction logic in Rust, we will define a new FFI function in Hajr (`hajr_spawn_compartment()`).
  - **Namespaces:** The Zig spawner will use `std.ChildProcess` and apply OS-specific isolation (e.g., `clone` with `CLONE_NEWNS`, `CLONE_NEWUSER` on Linux or leveraging existing Seatbelt mechanisms on macOS).
  - **MPK Assignment:** The Zig spawner will allocate an MPK key (`pkey_alloc`) and apply it to the compartment, ensuring hardware memory protection is active. `Zawra_Hajr_SpawnProcess` will simply call this FFI function.
