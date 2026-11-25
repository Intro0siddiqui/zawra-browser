# Memory Safety & Debugging Notes

## Fil-C for C/C++ Memory Bug Finding
- **Tool**: **Fil-C** (memory-safe C/C++ compiler & runtime by Filip Pizlo) — detects use-after-free, out-of-bounds reads/writes, and invalid pointer/capability dereferences at runtime.
- **Target use case in Zawra**: Auditing C++ FFI and WebKit glue code (e.g., `webkit/source/Source/WebKit/NetworkProcess/znet/NetworkDataTaskZNet.cpp` and `WebKit` C++ ↔ Rust/Zig FFI boundaries) when tracking down `SIGSEGV` (signal 11) or subtle lifetime/cancellation bugs.
