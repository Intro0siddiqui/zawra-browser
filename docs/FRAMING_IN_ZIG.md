# Message Framing in Zig — Architecture Proposal

## Current State: Manual Framing in C++

`ConnectionUnix.cpp` manually serializes/deserializes IPC messages:

### Send Path (`sendOutputMessage`, lines 557-608)

```cpp
// Manual serialization — 51 lines
size_t total_size = sizeof(messageInfo) + sizeof(attachmentCount) 
    + (attachmentCount * sizeof(int32_t)) + outputMessage.bodySize() + sizeof(uint32_t);
Vector<uint8_t> payload(total_size);
uint8_t* ptr = payload.data();

memcpy(ptr, &messageInfo, sizeof(messageInfo));          // Header
ptr += sizeof(messageInfo);
memcpy(ptr, &attachmentCount, sizeof(attachmentCount));  // Attachment count
ptr += sizeof(attachmentCount);
for (auto& attachment : attachments) {                   // FD handles
    int32_t handle = hajr_ipc_send_fd(m_outboundRing, attachment.value());
    memcpy(ptr, &handle, sizeof(handle));
    ptr += sizeof(handle);
}
memcpy(ptr, outputMessage.body(), outputMessage.bodySize());  // Body
uint32_t checksum = hajr_ipc_message_checksum(...);           // CRC32
memcpy(ptr + outputMessage.bodySize(), &checksum, sizeof(checksum));
hajr_ring_write(m_outboundRing, payload.data(), payload.size());
hajr_ring_signal(m_outboundRing);
```

### Receive Path (`readyReadHandler`, lines 198-301)

```cpp
// Manual deserialization — 80 lines
hajr_ring_read(m_inboundRing, &msgInfo, sizeof(msgInfo), &msgInfoBytesRead);
hajr_ring_read(m_inboundRing, &attachmentCount, sizeof(attachmentCount), &countRead);
for (uint32_t i = 0; i < attachmentCount; ++i) {
    hajr_ring_read(m_inboundRing, &handle, sizeof(handle), &handleRead);
    int fd = hajr_ipc_recv_fd(m_inboundRing, handle);
    fds.append(Attachment(fd, Attachment::Adopt));
}
uint8_t* payloadBuffer = static_cast<uint8_t*>(fastMalloc(msgInfo.bodySize()));
hajr_ring_read(m_inboundRing, payloadBuffer, msgInfo.bodySize(), &bodyBytesRead);
hajr_ring_read(m_inboundRing, &receivedChecksum, sizeof(receivedChecksum), &checksumRead);
hajr_ipc_message_checksum(...);  // Verify
```

**Total: ~130 lines of manual serialization/deserialization in C++.**

## Problem

1. **C++ complexity** — Every field is manually memcpy'd. Adding a new field requires editing both send and receive paths.
2. **No type safety** — Message format is implicit in the memcpy order.
3. **Error-prone** — Easy to get byte counts wrong, especially with wrap-around handling.
4. **Duplicates existing Hajr code** — `IpcRing` in `ipc/ipc.zig` already handles this.

## Proposed: IpcRing as the Framing Layer

### Current IpcRing Design

```zig
// ipc/ipc.zig
pub const IpcHeader = extern struct {
    msg_type: u32,        // Message type enum
    payload_len: u32,     // Payload size
    sequence: u64,        // Monotonic counter
    source_id: u64,       // Sender sandbox ID
    target_id: u64,       // Receiver sandbox ID
    timestamp: u64,       // Nanoseconds since boot
    checksum: u32,        // CRC32 of payload
    reserved: [32]u8,     // Future use
};  // 64 bytes total

pub const IpcRing = struct {
    slots: []RingSlot,    // Pre-allocated message slots
    head: atomic.Value(u64),
    tail: atomic.Value(u64),
    // ...
};

pub fn send(ring: *IpcRing, msg_type: IpcMessageType, source: u64, target: u64, payload: []const u8) !void {
    // 1. Claim slot atomically
    // 2. Write IpcHeader with type, source, target, CRC32
    // 3. Copy payload into slot
    // 4. Mark slot as occupied
}

pub fn recv(ring: *IpcRing) !IpcMessage {
    // 1. Check if slot available
    // 2. Validate CRC32
    // 3. Return header + payload
    // 4. Mark slot as free
}
```

### What Would Change

**C++ side (before):**
```cpp
// 130 lines of manual serialization
memcpy(ptr, &messageInfo, sizeof(messageInfo));
memcpy(ptr, &attachmentCount, sizeof(attachmentCount));
// ... 20 more memcpy calls ...
```

**C++ side (after):**
```cpp
// ~10 lines
IpcMessage msg = {
    .msg_type = IPC_MSG_TYPE,
    .source = myId,
    .target = peerId,
    .payload = outputMessage.body(),
    .payload_len = outputMessage.bodySize(),
};
hajr_ipc_send(m_outboundRing, &msg);

// Receive
IpcMessage received;
if (hajr_ipc_recv(m_inboundRing, &received) == 1) {
    // Process received.msg_type, received.payload
}
```

## Blockers to Adoption

### 1. Heap Allocation (Cannot Share Across Processes)

**Current:** `IpcRing.create()` uses `std.heap.page_allocator` — heap-local, not shared.

**Fix:** Switch to `memfd_create` + `mmap`:
```zig
pub fn create(slot_count: usize, max_msg_size: usize) !*IpcRing {
    const total_size = calculateTotalSize(slot_count, max_msg_size);
    const fd = std.os.linux.memfd_create("ipc-ring", .CLOEXEC);
    _ = std.os.linux.ftruncate(fd, total_size);
    const ptr = std.os.linux.mmap(null, total_size, .{ .read = true, .write = true }, 
                                   .{ .TYPE = .SHARED }, fd, 0);
    // ... initialize ring at ptr
}
```

### 2. Busy-Spinning (No Eventfd)

**Current:** `IpcRing.send()` spins up to 1M iterations waiting for a free slot.

**Fix:** Add `signal_fd` field:
```zig
pub const IpcRing = struct {
    // ... existing fields ...
    signal_fd: ?i32 = null,

    pub fn send(...) !void {
        // ... write to slot ...
        if (ring.signal_fd) |fd| {
            const one: u64 = 1;
            _ = std.os.linux.write(fd, std.mem.asBytes(&one));
        }
    }
};
```

### 3. 4KB Message Limit

**Current:** `MAX_MESSAGE_SIZE = 4096` bytes per slot.

**Fix:** Make configurable at creation time:
```zig
pub fn create(
    slot_count: usize,
    max_msg_size: usize,  // Configurable: 4096, 16384, 65536
    // ...
) !*IpcRing { ... }
```

**Trade-off:** Larger slots = more memory per ring. 64 slots × 16KB = 1MB per direction.

### 4. No FD Passing

**Current:** `C_HardenedRingBuffer` has `hajr_ipc_send_fd` / `hajr_ipc_recv_fd` via `pidfd_getfd`.

**Fix:** Add FD passing to IpcRing header or as out-of-band data.

### 5. No Poison Detection

**Current:** `IpcRing` doesn't check `poison_bit`.

**Fix:** Check in `send()` and `recv()`:
```zig
pub fn send(...) !void {
    if (ring.metadata.poison_bit.load(.acquire)) return error.Poisoned;
    // ...
}
```

## Effort Estimate

| Change | LOC | Difficulty |
|--------|-----|------------|
| memfd allocation | ~50 | Medium |
| eventfd signaling | ~30 | Easy |
| Configurable message size | ~20 | Easy |
| FD passing | ~80 | Medium |
| Poison detection | ~15 | Easy |
| C++ integration (new API) | ~100 | Medium |
| **Total** | **~295** | — |

## Recommendation

**Phase 1:** Keep `C_HardenedRingBuffer` for production IPC (it works, it's battle-tested).

**Phase 2:** Adapt `IpcRing` for **same-process, cross-thread** communication:
- JSC ↔ Hajr communication (zero-copy FFI already does this)
- Internal Hajr routing (Tier 1 → Tier 2 within same process)
- Poison protocol messages

**Phase 3:** If multi-sandbox fan-out is needed, adopt `RingRouter` with the adapted `IpcRing`.
