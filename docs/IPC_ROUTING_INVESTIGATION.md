# IPC routing investigation

**Status:** paused for base stabilization  
**Paused:** 2026-06-18  
**Tracks:** active black-screen / handle-routing diagnosis  
**Related backlog:** `experiments/missing-features.md` (42 open items)

This note captures the live IPC diagnostics for the black MiniBrowser screen and the `NetworkProcessConnection_SetOnLineState` routing path. The active debugging should resume after the broader base fixes are closed.

## Scope
This note captures the IPC work around the black MiniBrowser screen and the `NetworkProcessConnection_SetOnLineState` crash path.

## Main finding
The current IPC crash was caused by secondary IPC connections reusing the parent-process Hajr environment instead of their own socketpair handle.

- `Connection::createConnectionIdentifierPair()` creates a Unix socketpair.
- `platformInitialize()` was still falling back to global env vars when `identifier.handle != -1`.
- That made secondary connections like `NetworkProcess <-> WebProcess` read/write on the wrong ring pair.
- As a result, `NetworkProcessConnection_SetOnLineState` was delivered to the wrong `Connection` and hit `NetworkProcess::didReceiveMessage()`.

## Key files
- `patches/webkit/Source/WebKit/Platform/IPC/unix/ConnectionUnix.cpp`
- `patches/webkit/Source/WebKit/Platform/IPC/Connection.h`
- `patches/webkit/Source/WebKit/Platform/IPC/Connection.cpp`
- `patches/webkit/Source/WebKit/NetworkProcess/NetworkProcess.cpp`
- `patches/webkit/Source/WebKit/UIProcess/Network/NetworkProcessProxy.cpp`
- `patches/webkit/Source/WebKit/WebProcess/WebProcess.cpp`
- `/tmp/zawra_diag16.log`
- `/tmp/zawra_diag17.log`

## What was changed
### `ConnectionUnix.cpp`
- `platformInitialize()` now prefers `identifier.handle` when the connection is socketpair-backed.
- If `!m_hasHajrInfo && identifier.handle != -1`, the code now uses the descriptor from the `Identifier` instead of reading parent env vars.
- `m_fdTransferFd` is stored from the `Identifier`.
- `platformOpen()` now uses per-connection Hajr info when available.
- `sendOutputMessage()` now has a socketpair send path using `sendmsg()` + `SCM_RIGHTS`.
- `readyReadHandler()` now reads handle values from the ring and receives the actual FDs over the transfer socket.

### `Connection.h`
- Added `m_fdTransferFd` to the connection state.
- Added `hajrFdTransferFd` to `Identifier`.

### `Connection.cpp`
- `createConnectionIdentifierPair()` remains the socketpair factory for Unix IPC.

## Build state
- `cargo run --release -p zawra-setup` was run to sync patches into `webkit/source`.
- After sync, `ninja -C webkit/build/WPE/Debug -j 2 MiniBrowser` succeeded.
- The earlier compile blocker was a source/patch mismatch in `ConnectionUnix.cpp`; syncing the patch fixed it.

## Smoke test state
Command used:
- `timeout 20 ./webkit/build/WPE/Debug/bin/MiniBrowser file:///tmp/zawra/ui_shell.html > /tmp/zawra_diag17.log 2>&1`

Result:
- Exit code: `124`
- No `ASSERTION FAILED`
- No `Unhandled message NetworkProcessConnection_SetOnLineState`
- No `EGL error`
- `createWindow` succeeded once
- `exportCompositorFD` succeeded
- `SCM_RIGHTS sendmsg` succeeded for attachment-bearing messages

## Current unresolved issue
The smoke log still shows no `readyReadHandler` entries from the child processes.

That suggests the receive side is still not fully wired or not waking as expected. The most likely next area to inspect is the Hajr GSource / `readyReadHandler()` path.

## Evidence from logs
### `/tmp/zawra_diag17.log`
- `createWindow` succeeded:
  - `Z-GRAPHICS createWindow: success, window=6291457`
- `exportCompositorFD` succeeded:
  - `ZAWRA-BRIDGE exportCompositorFD: handle=... -> fd=51`
- `SCM_RIGHTS` send path worked:
  - `sendOutputMessage: SCM_RIGHTS sendmsg result=1 errno=0 fdCount=1 fdTransferFd=28`
- No IPC assertion:
  - no `Unhandled message NetworkProcessConnection_SetOnLineState`
- No EGL error:
  - no `EGL error`

## What is still likely wrong
The IPC routing fix is probably correct for the `NetworkProcessConnection_SetOnLineState` crash, but the receive path still needs validation.

The main suspect now is the Hajr receive wake path:
- `platformOpen()` attaches a `HajrSource` to the connection queue context.
- `sendOutputMessage()` signals the outbound ring.
- But the smoke log does not show `readyReadHandler` firing in the child processes.

## Recommended next step
Investigate why the inbound Hajr GSource is not waking or why `readyReadHandler()` is not logging.

Likely places to check:
- `platformOpen()` Hajr source attach path
- `readyReadHandler()` wake path
- `hajr_ring_signal()` / `hajr_ring_wait()` behavior
- whether the inbound signal fd is readable from the connection queue thread

## Commands that helped
- `cargo run --release -p zawra-setup`
- `ninja -C webkit/build/WPE/Debug -j 2 MiniBrowser`
- `timeout 20 ./webkit/build/WPE/Debug/bin/MiniBrowser file:///tmp/zawra/ui_shell.html > /tmp/zawra_diag17.log 2>&1`
- `grep -nE "Unhandled message NetworkProcessConnection_SetOnLineState|ASSERTION FAILED|createWindow|exportCompositorFD|EGL error|SCM_RIGHTS|readyReadHandler|NETCONN" /tmp/zawra_diag17.log`

## Verified Hajr-related items from `docs/missing-features.md`
- `ASSERT_NOT_REACHED` in `TextureMapperGL.cpp` filter switch default case — **true** (`patches/webkit/.../TextureMapperGL.cpp:479`).
- Cross-process surface sharing — `m_hostFileDescriptor` stored in `WebPage.cpp` but never consumed — **true** (`patches/webkit/.../WebPage.cpp:614` initializes it; no consumer found in `patches/webkit/` or `src/`).
- Hajr allocator uses `libc::malloc` — MPK/MTE completely bypassed — **partially true**: Rust FFI `Zawra_Hajr_MemAlloc` in `src/wpe_glue/init.rs:153` calls `libc::malloc(size)`, but Zig-level `hw.os.memAlloc` uses `mmap` with guard pages.
- Hajr ring pair creation has no error handling — **true** (`src/wpe_glue/init.rs:121-137` ignores failure sentinel from `__hajr_create_anonymous_ring` and passes invalid ids to `__hajr_map_anonymous_ring`).
- Hajr thread wrappers have no error handling — **true** (`dependencies/hajr/src/sandbox/bindings.zig:397-399` swallows `std.Thread.spawn(...)` error and returns an invalid handle value `0` to callers).
- 12 `[ZAWRA-DEBUG]` fprintf statements left in production patches — **true**, verified count: `ConnectionUnix.cpp:582,599,608,648`; `WebProcessProxy.cpp:306,326,365`; `BackgroundProcessResponsivenessTimer.cpp:51`; `AuxiliaryProcessProxy.cpp:61,71`; `ProcessThrottler.cpp:66,68`.

## Current conclusion
The IPC routing bug is fixed well enough to remove the `NetworkProcessConnection_SetOnLineState` crash and allow MiniBrowser to reach the graphics path. The remaining work is to prove the receive path is working end-to-end.
