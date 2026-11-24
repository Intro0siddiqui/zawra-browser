# Zawra Browser — Zig Coding Rules & Memory Safety Standards

This document defines the strict memory safety, performance, and cross-platform criteria for writing Zig code within the Zawra Browser architecture (`ui/`, `dependencies/hajr/`, and `dependencies/z-graphics/`).

All Zig code committed to this repository is verified against these rules by the automated static checker:
```bash
python3 tools/check_zig_rules.py
```

---

## 1. Core Architectural Rules

### RULE-01: Safe Enum Conversions (No Untrusted `@enumFromInt`)
- **Severity**: ERROR / WARN
- **Reason**: In Zig Safe and Debug modes, passing an integer that does not map to a declared enum tag to `@enumFromInt` produces an instant, unrecoverable panic. In `ReleaseFast`, it causes undefined behavior.
- **Rule**: Never use raw `@enumFromInt` on data originating from C-ABI, shared memory ring buffers, IPC messages, or user inputs.
- **Remedy**: Always use `std.enums.fromInt(EnumType, int_val) orelse <fallback>`.
  ```zig
  // BAD:
  const req_type = @as(RequestType, @enumFromInt(req.request_type));

  // GOOD:
  const req_type = std.enums.fromInt(RequestType, req.request_type) orelse {
      return error.InvalidRequestType;
  };
  ```

---

### RULE-02: No Static Comptime Slices Flowing Into Allocator Deallocation
- **Severity**: ERROR
- **Reason**: Passing a comptime slice literal (such as `&[_]T{}` or `"string"`) to `allocator.free()` attempts to release memory belonging to the read-only program image, causing heap corruption or aborts.
- **Rule**: Never catch allocator errors with static literals (`catch &[_]T{}`) if the resulting slice is deferred or passed to `allocator.free(slice)`.
- **Remedy**:
  ```zig
  // BAD:
  const poisoned = r.checkAllRings() catch &[_]u64{};
  defer allocator.free(poisoned); // CRASH if error occurred!

  // GOOD:
  const poisoned = r.checkAllRings() catch |err| {
      return err;
  };
  defer allocator.free(poisoned);
  ```

---

### RULE-03: Render Loop Frame Pacing (Zero Stderr Writes in Inner Loop)
- **Severity**: ERROR
- **Reason**: `std.debug.print` performs synchronous, unbuffered I/O writes to `stderr`. Invoking it inside frame loops (`render()`, `submitCommandBuffer()`, `uploadTexture()`) blocks Thread 1 for multiple milliseconds, stalls Wayland compositors (River, Sway), drops frames, and starves WebKit's GLib `GMainContext`.
- **Rule**: Synchronous `std.debug.print` is strictly forbidden in inner render and command buffer submission loops.
- **Remedy**: Gate debug traces behind `comptime` flags or remove them from hot paths entirely.

---

### RULE-04: UI Idle Dirty Gating
- **Severity**: ARCHITECTURAL
- **Reason**: Vulkan `vkWaitForFences` in `submitCommandBuffer` synchronously blocks until the GPU finishes rendering. Continuously redrawing unchanged UI consumes 100% CPU/GPU and prevents WebKit from processing DOM events or streaming video smoothly.
- **Rule**: Frame rendering in `ui/shell.zig` must only trigger when `shell_state.ui_dirty == true` (input, hover, tab switch, window resize).

---

### RULE-05: Escaping Stack Slices in IPC & Deserialization
- **Severity**: ERROR
- **Reason**: Storing deserialized message slices that point into local stack-allocated buffers (`var buf: [4096]u8 = undefined`) results in dangling pointers once the function returns.
- **Rule**: IPC message reception functions must write into caller-allocated buffers (`out_buf: []u8`) or dynamically allocate heap memory.
  ```zig
  // BAD:
  pub fn receiveMessage() Message {
      var buf: [4096]u8 = undefined;
      const len = read(fd, &buf);
      return Message.deserialize(buf[0..len]); // DANGLING POINTER!
  }

  // GOOD:
  pub fn receiveMessage(out_buf: []u8) !Message {
      const len = try read(fd, out_buf);
      return Message.deserialize(out_buf[0..len]);
  }
  ```

---

### RULE-06: C-ABI Pointer Null Checks Before `std.mem.span`
- **Severity**: WARN / ERROR
- **Reason**: Invoking `std.mem.span(ptr)` on a null C-string pointer (`?[*c]const u8`) triggers a segmentation fault.
- **Rule**: All pointers received across the C-ABI must be guarded with `if (ptr) |p|` before converting to Zig slices.
  ```zig
  // BAD:
  const url_slice = std.mem.span(c_url);

  // GOOD:
  const url_slice = if (c_url) |u| std.mem.span(u) else "";
  ```

---

### RULE-07: Clamped Buffer Slicing from Foreign Inputs
- **Severity**: ERROR
- **Reason**: Untrusted lengths from C structs or IPC headers (such as `title_len`, `payload_len`) may exceed local buffer limits and cause out-of-bounds slice panics.
- **Rule**: Always clamp slice bounds using `@min(input_len, max_buffer_len)` before slicing or copying.

---

### RULE-08: Multi-Step Pointer Allocation Safety (`errdefer` & Zeroed Memory)
- **Severity**: ERROR
- **Reason**: When allocating arrays of pointers (e.g. `c_argv`), an out-of-memory error midway leaves earlier duplicated strings leaked in memory.
- **Rule**: Zero-initialize pointer buffers (`@memset(c_argv, null)`) and install an immediate `defer` cleanup loop before populating elements.
  ```zig
  var c_argv = try allocator.alloc(?[*:0]const u8, argv.len + 1);
  @memset(c_argv, null);
  defer {
      for (c_argv[0..argv.len]) |arg| {
          if (arg) |ptr| allocator.free(std.mem.span(ptr));
      }
      allocator.free(c_argv);
  }
  for (argv, 0..) |arg, i| {
      c_argv[i] = (try allocator.dupeZ(u8, arg)).ptr;
  }
  c_argv[argv.len] = null;
  ```

---

### RULE-09: Wayland Subsurface Occlusion Principle
- **Severity**: ARCHITECTURAL
- **Reason**: Wayland `wl_subsurface` planes sit as separate hardware compositor layers over the Vulkan base window. Internal browser pages (`zawra://start`, `zawra://history`) and overlay drawers will be occluded by WebKit unless the subsurface is explicitly detached.
- **Rule**: Never resize subsurface to `0×0`. Maintain position `(260, 0)` and invoke `wpe.detachSubsurfaceBuffer()` (attaching a null `wl_buffer`) to make internal pages visible.

---

### RULE-10: Wayland Keyboard Modifier Hygiene
- **Severity**: RELIABILITY
- **Reason**: If a window loses focus while a modifier key (Shift, Ctrl, Alt) is pressed, the Wayland compositor sends `wl_keyboard.leave`. If modifiers are not cleared, subsequent key presses in other windows or upon refocus remain falsely latched.
- **Rule**: The `wl_keyboard.leave` listener must unconditionally zero all modifier tracking bits.

---

## 2. Automated Static Rule Checker

Run the checker locally before committing:
```bash
python3 tools/check_zig_rules.py
```

To format all Zig files according to standard formatting:
```bash
zig fmt ui/ dependencies/hajr/src/ dependencies/z-graphics/src/
```
