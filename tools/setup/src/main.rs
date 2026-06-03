use std::fs;
use std::path::{Path, PathBuf};
use std::io::copy;
use xz2::read::XzDecoder;
use tar::Archive;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 1. Configuration
    let webkit_version = "2.42.5"; // We can automate finding this later, but 2.42.5 is a solid stable target.
    let url = format!("https://wpewebkit.org/releases/wpewebkit-{}.tar.xz", webkit_version);
    let target_dir = Path::new("webkit/source");
    let patch_dir = Path::new("patches/webkit");
    let download_path = Path::new("webkit_source.tar.xz");

    println!("🚀 Starting Zawra Browser Setup...");

    // 2. Download
    if !download_path.exists() {
        println!("📥 Downloading WPE WebKit {}...", webkit_version);
        let mut response = reqwest::blocking::get(url)?;
        let mut dest = fs::File::create(download_path)?;
        copy(&mut response, &mut dest)?;
    } else {
        println!("✅ Tarball already downloaded.");
    }

    // 3. Extract
    if target_dir.exists() {
        println!("🧹 Cleaning existing WebKit directory...");
        fs::remove_dir_all(target_dir)?;
    }
    fs::create_dir_all(target_dir)?;

    println!("📦 Extracting source code (this may take a minute)...");
    let tar_xz = fs::File::open(download_path)?;
    let tar = XzDecoder::new(tar_xz);
    let mut archive = Archive::new(tar);
    
    // WebKit tarballs extract into a subfolder like wpewebkit-2.42.5/
    // We want the contents directly in webkit/source/
    for entry in archive.entries()? {
        let mut entry = entry?;
        let path = entry.path()?.to_path_buf();
        
        // Strip the first component of the path
        let mut components = path.components();
        components.next(); // skip wpewebkit-2.42.5/
        let stripped_path: PathBuf = components.collect();
        
        if stripped_path.as_os_str().is_empty() {
            continue;
        }

        let out_path = target_dir.join(stripped_path);
        if let Some(parent) = out_path.parent() {
            fs::create_dir_all(parent)?;
        }
        entry.unpack(out_path)?;
    }

    // 4. Apply Patches
    println!("🛠️ Applying Zawra Patches...");
    if patch_dir.exists() {
        let options = fs_extra::dir::CopyOptions::new().overwrite(true);
        // Use a loop to copy contents of patches/webkit into webkit/source
        for entry in fs::read_dir(patch_dir)? {
            let entry = entry?;
            let path = entry.path();
            if path.is_dir() {
                fs_extra::dir::copy(&path, target_dir, &options)?;
            } else {
                fs_extra::file::copy(&path, target_dir.join(entry.file_name()), &fs_extra::file::CopyOptions::new().overwrite(true))?;
            }
        }
    }

    println!("✨ Setup Complete! You can now run CMake.");
    Ok(())
}
