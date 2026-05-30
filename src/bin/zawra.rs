//! Zawra Browser — Main Entry Point

fn main() {
    use zawra_browser::wpe_glue::launcher;

    eprintln!("╔══════════════════════════════════════╗");
    eprintln!("║       Zawra Browser — Starting       ║");
    eprintln!("╚══════════════════════════════════════╝");

    // Resolve profile directory
    let profile = std::env::var("ZAWRA_PROFILE")
        .unwrap_or_else(|_| {
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

    // Launch WPE (no-op if libWPE not found)
    let exit_code = launcher::launch_wpe(&profile);
    eprintln!("[zawra] WPE exited with code {}", exit_code);

    zawra_browser::wpe_glue::init::Zawra_Shutdown_Subsystems();
    std::process::exit(exit_code);
}
