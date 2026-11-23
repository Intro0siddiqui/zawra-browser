//! Zawra Browser — Main Entry Point

unsafe extern "C" {
    fn Zawra_UI_Run(argc: std::ffi::c_int, argv: *const *const std::ffi::c_char) -> std::ffi::c_int;
}

fn main() {
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

    // Launch WPE on dedicated "webkit-glib" thread (spawns WebProcess, NetworkProcess)
    let profile_clone = profile.clone();
    std::thread::Builder::new()
        .name("webkit-glib".to_string())
        .spawn(move || {
            let code = launcher::launch_wpe(&profile_clone);
            eprintln!("[zawra] WPE exited with code {}", code);
        })
        .expect("Failed to spawn webkit-glib thread");

    // Run the native Vulkan UI Shell on the main thread (Wayland requirement)
    let exit_code = unsafe { Zawra_UI_Run(0, std::ptr::null()) };
    eprintln!("[zawra] UI Shell exited with code {}", exit_code);

    zawra_browser::wpe_glue::init::Z_Shutdown_Subsystems();
    std::process::exit(exit_code);
}
