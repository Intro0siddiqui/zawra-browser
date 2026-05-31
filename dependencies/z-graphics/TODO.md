# z-graphics Implementation TODO

- [x] Initialize project structure and CI
- [x] Functional smoke test for FFI
- [ ] Implement `z_graphics_create_surface`
    - [ ] Define platform-agnostic surface struct
    - [ ] Linux (Vulkan) implementation
    - [ ] Windows (D3D12/Vulkan) implementation
    - [ ] macOS (Metal) implementation
- [ ] Implement `z_graphics_swap_buffers`
- [ ] Integrate with WebKit compositor
