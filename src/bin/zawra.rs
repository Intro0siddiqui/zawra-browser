//! Zawra Browser — Main Entry Point

unsafe extern "C" {
    fn Zawra_UI_Run(argc: std::ffi::c_int, argv: *const *const std::ffi::c_char) -> std::ffi::c_int;
    fn hajr_trace_set_process_kind(kind: u8);
}

fn main() {
    unsafe {
        hajr_trace_set_process_kind(1); // 1 = UIProcess
    }

    use zawra_browser::wpe_glue::launcher;

    eprintln!("╔══════════════════════════════════════╗");
    eprintln!("║       Zawra Browser — Starting       ║");
    eprintln!("╚══════════════════════════════════════╝");

    // Resolve profile directory
    let profile = std::env::var("ZAWRA_PROFILE").unwrap_or_else(|_| {
        let mut home = dirs::home_dir().unwrap_or_default();
        home.push(".zawra/profile");
        std::fs::create_dir_all(&home).ok();
        home.to_string_lossy().into_owned()
    });

    eprintln!("[zawra] Profile: {}", profile);

    // Bootstrap z-net + BrowserDB
    if !launcher::bootstrap_zawra(&profile) {
        eprintln!("[zawra] FATAL: subsystem bootstrap failed");
        std::process::exit(1);
    }
    eprintln!("[zawra] All subsystems ready ✓");

    // Configure WPE paths (WEBKIT_EXEC_PATH, WEBKIT_INJECTED_BUNDLE_PATH, ZAWRA_WPE_LIB_PATH)
    if let Some(wpe_lib) = launcher::resolve_wpe_environment() {
        eprintln!("[zawra] Discovered WPE library: {}", wpe_lib.display());
    }

    // Run the native Vulkan UI Shell on the main thread (Wayland requirement)
    let args: Vec<std::ffi::CString> = std::env::args()
        .map(|arg| std::ffi::CString::new(arg).unwrap_or_default())
        .collect();
    let c_args: Vec<*const std::ffi::c_char> = args.iter().map(|arg| arg.as_ptr()).collect();
    let exit_code = unsafe { Zawra_UI_Run(c_args.len() as std::ffi::c_int, c_args.as_ptr()) };
    eprintln!("[zawra] UI Shell exited with code {}", exit_code);

    zawra_browser::wpe_glue::init::Z_Shutdown_Subsystems();
    std::process::exit(exit_code);
}
