use std::fs;
use std::path::{Path, PathBuf};
use std::io::copy;
use xz2::read::XzDecoder;
use tar::Archive;

/// Recursively copy only files whose source mtime > target mtime.
/// This preserves existing .o timestamps for unchanged source files.
fn copy_newer(src: &Path, dst: &Path) -> Result<u32, Box<dyn std::error::Error>> {
    let mut copied = 0u32;
    if src.is_dir() {
        fs::create_dir_all(dst)?;
        for entry in fs::read_dir(src)? {
            let entry = entry?;
            let src_child = entry.path();
            let dst_child = dst.join(entry.file_name());
            copied += copy_newer(&src_child, &dst_child)?;
        }
    } else {
        let need_copy = if !dst.exists() {
            true
        } else {
            let src_meta = fs::metadata(&src)?;
            let dst_meta = fs::metadata(&dst)?;
            src_meta.modified()? > dst_meta.modified()?
        };
        if need_copy {
            if let Some(parent) = dst.parent() {
                fs::create_dir_all(parent)?;
            }
            fs::copy(src, dst)?;
            copied += 1;
        }
    }
    Ok(copied)
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let project_root = PathBuf::from(env!("CARGO_MANIFEST_DIR"))
        .parent()
        .and_then(|p| p.parent())
        .ok_or("Could not resolve project root from CARGO_MANIFEST_DIR")?
        .to_path_buf();

    let webkit_version = "2.42.5";
    let url = format!("https://wpewebkit.org/releases/wpewebkit-{}.tar.xz", webkit_version);
    let target_dir    = project_root.join("webkit/source");
    let patch_dir     = project_root.join("patches/webkit");
    let download_path = project_root.join("webkit_source.tar.xz");
    let sentinel      = target_dir.join("Source/WebCore/config.h");

    println!("🚀 Starting Zawra Browser Setup...");
    println!("📁 Project root: {}", project_root.display());

    // 2. Download
    if !download_path.exists() {
        println!("📥 Downloading WPE WebKit {}...", webkit_version);
        let mut response = reqwest::blocking::get(url)?;
        let mut dest = fs::File::create(&download_path)?;
        copy(&mut response, &mut dest)?;
    } else {
        println!("✅ Tarball already downloaded.");
    }

    // 3. Extract — only if source tree is missing or incomplete
    if sentinel.exists() {
        println!("✅ WebKit source tree already exists (skipping extraction).");
    } else {
        if target_dir.exists() {
            println!("🧹 Cleaning incomplete WebKit directory...");
            fs::remove_dir_all(&target_dir)?;
        }
        fs::create_dir_all(&target_dir)?;

        println!("📦 Extracting source code (this may take a minute)...");
        let tar_xz = fs::File::open(&download_path)?;
        let tar = XzDecoder::new(tar_xz);
        let mut archive = Archive::new(tar);

        for entry in archive.entries()? {
            let mut entry = entry?;
            let path = entry.path()?.to_path_buf();

            let mut components = path.components();
            components.next(); // skip wpewebkit-2.42.5/
            let stripped_path: PathBuf = components.collect();

            if stripped_path.as_os_str().is_empty() {
                continue;
            }

            let out_path = target_dir.join(&stripped_path);
            if let Some(parent) = out_path.parent() {
                fs::create_dir_all(parent)?;
            }
            entry.unpack(out_path)?;
        }
        println!("✅ Extraction complete.");
    }

    // 4. Apply Patches — only copy files that are newer than their target
    println!("🛠️ Applying Zawra Patches from {} ...", patch_dir.display());
    if patch_dir.exists() {
        let copied = copy_newer(&patch_dir, &target_dir)?;
        if copied > 0 {
            println!("✅ Applied {} updated patch file(s).", copied);
        } else {
            println!("✅ All patches up to date (no files copied).");
        }
    } else {
        return Err(format!("Patch directory not found: {}", patch_dir.display()).into());
    }

    println!("✨ Setup Complete! You can now run CMake.");

    // 5. Post-Setup Tooling: Symlink compile_commands.json if it exists
    let build_db = project_root.join("webkit/build/WPE/Debug/compile_commands.json");
    let root_db  = project_root.join("compile_commands.json");
    
    if build_db.exists() {
        println!("🔗 Linking compilation database to root...");
        if root_db.exists() || root_db.is_symlink() {
            let _ = fs::remove_file(&root_db);
        }
        #[cfg(unix)]
        std::os::unix::fs::symlink(&build_db, &root_db)?;
        println!("✅ Linked: compile_commands.json -> {}", build_db.display());
    }

    Ok(())
}
