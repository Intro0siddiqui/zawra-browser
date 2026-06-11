#!/usr/bin/env python3
import sqlite3
import os
import re
import subprocess
from pathlib import Path

DB_NAME = "zawra_inventory.db"
DB_PATH = Path(__file__).resolve().parent / DB_NAME
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent

def init_db():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute("DROP TABLE IF EXISTS patches")
    cursor.execute("DROP TABLE IF EXISTS ffi_symbols")
    cursor.execute("DROP TABLE IF EXISTS build_inventory")
    cursor.execute("DROP TABLE IF EXISTS metadata")
    cursor.execute("""
        CREATE TABLE patches (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patch_path TEXT,
            target_path TEXT,
            file_type TEXT,
            is_full_replacement BOOLEAN
        )
    """)
    cursor.execute("""
        CREATE TABLE ffi_symbols (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            source_file TEXT,
            symbol_name TEXT,
            language TEXT,
            direction TEXT -- 'imported', 'exported', or 'defined'
        )
    """)
    cursor.execute("""
        CREATE TABLE build_inventory (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            source_file TEXT,
            build_file TEXT,
            target_name TEXT
        )
    """)
    cursor.execute("""
        CREATE TABLE metadata (
            key TEXT PRIMARY KEY,
            value TEXT
        )
    """)
    conn.commit()
    return conn

def crawl_build_files(conn):
    cursor = conn.cursor()
    
    # 1. Parse build files in both patches/ and webkit/source/
    search_roots = [
        (PROJECT_ROOT / "patches" / "webkit", "zawra"),
        (PROJECT_ROOT / "webkit" / "source", "upstream")
    ]
    
    # Platform exclusion list for Upstream
    exclude_platforms = ["GTK", "Cocoa", "PlayStation", "Windows", "Win", "Mac", "iOS", "Java", "Android", "JSCOnly", "WinCairo", "ApplePay"]

    # Track visited cmake/sources files to avoid re-processing via includes
    visited_cmake = set()
    visited_sources_txt = set()

    def _parse_sources_txt(path, base_path_override, rel_build_file, target_name):
        """Parse a Sources*.txt file, using base_path_override for path resolution."""
        try:
            real_path = path.resolve()
        except Exception:
            real_path = None
        if real_path and real_path in visited_sources_txt:
            return
        if real_path:
            visited_sources_txt.add(real_path)
        content = path.read_text(errors='ignore')
        for line in content.splitlines():
            line = line.strip()
            if not line or line.startswith("//") or line.startswith("#"):
                continue
            src_file = line.split()[0]
            full_src_path = (base_path_override / src_file)
            cursor.execute(
                "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                (str(full_src_path), str(rel_build_file), target_name)
            )

    def _parse_cmake_file(path, base_path_in_webkit, origin, depth=0):
        """Parse a cmake file: list(APPEND), set(), add_library(), add_executable(),
           and follow include() + UNIFIED_SOURCE_LIST_FILES references."""
        if depth > 10:
            return

        try:
            real_path = path.resolve()
        except Exception:
            return
        if real_path in visited_cmake:
            return
        visited_cmake.add(real_path)

        if not path.exists():
            return

        rel_build_file = path.relative_to(PROJECT_ROOT)
        content = path.read_text(errors='ignore')

        # --- A. list(APPEND TARGET file1 file2 ...) ---
        list_append = re.compile(
            r'list\s*\(\s*APPEND\s+([a-zA-Z0-9_]+)\s+([^)]+)\)',
            re.IGNORECASE | re.DOTALL,
        )
        for match in list_append.finditer(content):
            target = match.group(1)
            if any(x in target for x in [
                "INCLUDE_DIRECTORIES", "FRAMEWORK_HEADERS", "DEFINITIONS",
                "LIBRARIES", "SYSTEM_INCLUDE", "INTERFACE",
            ]):
                continue

            files_str = match.group(2)

            # --- B. Follow UNIFIED_SOURCE_LIST_FILES references ---
            if "UNIFIED_SOURCE_LIST" in target:
                for ref in files_str.split():
                    ref = ref.strip().strip('"').strip("'")
                    if not ref or ref.startswith("$"):
                        continue
                    ref_path = base_path_in_webkit / ref
                    for sr, _ in search_roots:
                        candidate = sr / ref_path
                        if candidate.exists():
                            _parse_sources_txt(candidate, base_path_in_webkit,
                                                rel_build_file, f"{origin}_UNIFIED_LIST")
                            break
                continue

            # Existing logic for other targets
            for src_file in files_str.split():
                src_file = src_file.strip().strip('"').strip("'")
                if not src_file or src_file.startswith("$"):
                    if "${WEBCORE_DIR}" in src_file:
                        src_file = src_file.replace("${WEBCORE_DIR}/", "")
                        full_src_path = Path("Source/WebCore") / src_file
                    elif "${WEBKIT_DIR}" in src_file:
                        src_file = src_file.replace("${WEBKIT_DIR}/", "")
                        full_src_path = Path("Source/WebKit") / src_file
                    else:
                        continue
                else:
                    full_src_path = (base_path_in_webkit / src_file)

                cursor.execute(
                    "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                    (str(full_src_path), str(rel_build_file), target)
                )

        # --- C. set(VARNAME file1 file2 ...) for source-list variables ---
        set_pattern = re.compile(
            r'set\s*\(\s*([a-zA-Z0-9_]+)\s+([^)]+)\)',
            re.IGNORECASE | re.DOTALL,
        )
        for match in set_pattern.finditer(content):
            target = match.group(1)
            if not any(x in target.upper() for x in ["SOURCES", "SOURCE_FILES"]):
                continue
            if any(x in target for x in [
                "INCLUDE", "DEFINITIONS", "LIBRARIES", "PROPERTIES",
                "COMPILE", "OPTIONS", "DEPENDENCIES", "FRAMEWORK",
            ]):
                continue

            files_str = match.group(2)
            raw_files = [f.strip().strip('"').strip("'") for f in files_str.split()]
            has_plain_path = any(
                f and not f.startswith("$") for f in raw_files
            )
            if not has_plain_path:
                continue

            for src_file in raw_files:
                if not src_file or src_file.startswith("$"):
                    if "${WEBCORE_DIR}" in src_file:
                        src_file = src_file.replace("${WEBCORE_DIR}/", "")
                        full_src_path = Path("Source/WebCore") / src_file
                    elif "${WEBKIT_DIR}" in src_file:
                        src_file = src_file.replace("${WEBKIT_DIR}/", "")
                        full_src_path = Path("Source/WebKit") / src_file
                    elif "${BMALLOC_DIR}" in src_file:
                        src_file = src_file.replace("${BMALLOC_DIR}/", "")
                        full_src_path = base_path_in_webkit / src_file
                    else:
                        continue
                else:
                    full_src_path = base_path_in_webkit / src_file

                cursor.execute(
                    "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                    (str(full_src_path), str(rel_build_file), target)
                )

        # --- C (cont). add_library(name [SHARED|STATIC|...] file1 file2 ...) ---
        add_lib_pattern = re.compile(
            r'add_library\s*\(\s*([a-zA-Z0-9_]+)\s+'
            r'(?:SHARED|STATIC|MODULE|OBJECT|INTERFACE)\s+([^)]+)\)',
            re.IGNORECASE | re.DOTALL,
        )
        for match in add_lib_pattern.finditer(content):
            target = match.group(1)
            files_str = match.group(2)
            for src_file in files_str.split():
                src_file = src_file.strip().strip('"').strip("'")
                if not src_file or src_file.startswith("$"):
                    continue
                full_src_path = base_path_in_webkit / src_file
                cursor.execute(
                    "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                    (str(full_src_path), str(rel_build_file), target)
                )

        # --- C (cont). add_executable(name [EXCLUDE_FROM_ALL] file1 file2 ...) ---
        add_exec_pattern = re.compile(
            r'add_executable\s*\(\s*([a-zA-Z0-9_]+)\s+'
            r'(?:EXCLUDE_FROM_ALL\s+)?([^)]+)\)',
            re.IGNORECASE | re.DOTALL,
        )
        for match in add_exec_pattern.finditer(content):
            target = match.group(1)
            files_str = match.group(2)
            for src_file in files_str.split():
                src_file = src_file.strip().strip('"').strip("'")
                if not src_file or src_file.startswith("$"):
                    continue
                full_src_path = base_path_in_webkit / src_file
                cursor.execute(
                    "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                    (str(full_src_path), str(rel_build_file), target)
                )

        # --- A (cont). Trace include() directives ---
        include_pattern = re.compile(
            r'include\s*\(\s*([a-zA-Z0-9_/.\\-]+\.cmake)\s*\)',
            re.IGNORECASE,
        )
        for match in include_pattern.finditer(content):
            inc_path = match.group(1).replace("\\", "/")
            resolved = base_path_in_webkit / inc_path
            for sr, _ in search_roots:
                candidate = sr / resolved
                if candidate.exists():
                    _parse_cmake_file(candidate, base_path_in_webkit, origin, depth + 1)
                    break

    for build_root, origin in search_roots:
        if not build_root.exists(): continue
        for root, _, files in os.walk(build_root):
            for file in files:
                # Filter upstream files to only relevant platforms
                if origin == "upstream":
                    # Keep if it contains WPE or is a core file
                    is_platform_specific = any(p in file for p in exclude_platforms)
                    if is_platform_specific and "WPE" not in file:
                        continue
                    
                    # Additional folder-based exclusion for PlayStation/Cocoa etc
                    if any(p in root for p in exclude_platforms):
                        if "WPE" not in root: continue
                
                # Sources*.txt
                if file.startswith("Sources") and file.endswith(".txt"):
                    path = Path(root) / file
                    rel_build_file = path.relative_to(PROJECT_ROOT)
                    try:
                        parts = path.parts
                        if "Source" in parts:
                            idx = parts.index("Source")
                            base_path_in_webkit = Path(*parts[idx:-1])
                        else: base_path_in_webkit = Path(".")
                    except: base_path_in_webkit = Path(".")
                    
                    _parse_sources_txt(path, base_path_in_webkit, rel_build_file, f"{origin}_UNIFIED_LIST")
                
                # *.cmake / CMakeLists.txt
                elif file.endswith(".cmake") or file == "CMakeLists.txt":
                    path = Path(root) / file
                    try:
                        parts = path.parts
                        if "Source" in parts:
                            idx = parts.index("Source")
                            base_path_in_webkit = Path(*parts[idx:-1])
                        else: base_path_in_webkit = Path(".")
                    except: base_path_in_webkit = Path(".")

                    _parse_cmake_file(path, base_path_in_webkit, origin)

    # 2. Parse build.zig files
    for root, _, files in os.walk(PROJECT_ROOT / "dependencies"):
        if "build.zig" in files:
            path = Path(root) / "build.zig"
            rel_build_file = path.relative_to(PROJECT_ROOT)
            rel_dep_root = path.parent.relative_to(PROJECT_ROOT)
            content = path.read_text(errors='ignore')
            zig_files = re.findall(r'"([^"]+\.zig)"', content)
            for zf in zig_files:
                full_zf_path = rel_dep_root / zf
                cursor.execute(
                    "INSERT INTO build_inventory (source_file, build_file, target_name) VALUES (?, ?, ?)",
                    (str(full_zf_path), str(rel_build_file), "zig_target")
                )
    conn.commit()

def get_metadata():
    try:
        head = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=PROJECT_ROOT).decode().strip()
    except:
        head = "unknown"
    
    max_mtime = 0
    search_dirs = [PROJECT_ROOT / "patches" / "webkit", PROJECT_ROOT / "src", PROJECT_ROOT / "dependencies"]
    for s_dir in search_dirs:
        if not s_dir.exists(): continue
        for root, _, files in os.walk(s_dir):
            for file in files:
                path = Path(root) / file
                try:
                    mtime = path.stat().st_mtime
                    if mtime > max_mtime:
                        max_mtime = mtime
                except:
                    continue
    return head, max_mtime

def crawl_patches(conn):
    cursor = conn.cursor()
    patch_root = PROJECT_ROOT / "patches" / "webkit"
    cpp_func = re.compile(r'(?:[a-zA-Z0-9_:]+\s+)+([a-zA-Z0-9_:]+)\s*\([^;]*\)\s*\{')
    cpp_keywords = {'if', 'while', 'for', 'switch', 'return', 'else', 'sizeof', 'static_cast'}

    for root, _, files in os.walk(patch_root):
        for file in files:
            full_patch_path = Path(root) / file
            # Skip hidden files or specific directories if needed
            if any(part.startswith('.') for part in full_patch_path.parts):
                continue

            rel_patch_path = full_patch_path.relative_to(PROJECT_ROOT)
            rel_to_patch_root = full_patch_path.relative_to(patch_root)
            target_path = Path("webkit/source") / rel_to_patch_root
            
            is_patch_file = file.endswith(".patch")
            cursor.execute(
                "INSERT INTO patches (patch_path, target_path, file_type, is_full_replacement) VALUES (?, ?, ?, ?)",
                (str(rel_patch_path), str(target_path), file.split('.')[-1], not is_patch_file)
            )

            if file.endswith((".cpp", ".h", ".c", ".patch")):
                try:
                    content = full_patch_path.read_text(errors='ignore')
                    # Detect extern "C" blocks
                    extern_block_match = re.search(r'extern\s+"C"\s*\{([\s\S]*?)\}', content)
                    if extern_block_match:
                        block_content = extern_block_match.group(1)
                        for match in re.finditer(r'[\w\*]+\s+([\w]+)\s*\(', block_content):
                            cursor.execute(
                                "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                (str(rel_patch_path), match.group(1), 'cpp', 'imported')
                            )

                    lines = content.splitlines() if is_patch_file else [content]
                    for text in lines:
                        if is_patch_file and (not text.startswith("+") or text.startswith("+++")):
                            continue
                        target_text = text[1:] if is_patch_file else text
                        for match in cpp_func.finditer(target_text):
                            full_name = match.group(1)
                            simple_name = full_name.split('::')[-1]
                            if simple_name not in cpp_keywords:
                                cursor.execute(
                                    "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                    (str(rel_patch_path), simple_name, 'cpp', 'defined')
                                )
                except Exception as e:
                    print(f"Error parsing patch content {rel_patch_path}: {e}")
    conn.commit()

def crawl_ffi(conn):
    cursor = conn.cursor()
    # Patterns
    rust_import = re.compile(r'extern\s+"C"\s*\{([\s\S]*?)\}')
    rust_export = re.compile(r'pub\s+(?:unsafe\s+)?extern\s+"C"\s+fn\s+([a-zA-Z0-9_]+)')
    
    zig_export = re.compile(r'export\s+fn\s+([a-zA-Z0-9_]+)')
    zig_extern = re.compile(r'extern\s+fn\s+([a-zA-Z0-9_]+)')

    search_dirs = [PROJECT_ROOT / "src", PROJECT_ROOT / "dependencies"]
    for s_dir in search_dirs:
        if not s_dir.exists(): continue
        for root, _, files in os.walk(s_dir):
            for file in files:
                # Skip build artifacts or ignored dirs
                if "target" in root or "zig-out" in root or "zig-cache" in root:
                    continue
                
                if file.endswith(".rs") or file.endswith(".zig"):
                    path = Path(root) / file
                    rel_path = path.relative_to(PROJECT_ROOT)
                    lang = "rust" if file.endswith(".rs") else "zig"
                    try:
                        content = path.read_text(errors='ignore')
                        if lang == "rust":
                            # 1. Detect Imports (extern "C" blocks)
                            for block_match in rust_import.finditer(content):
                                block = block_match.group(1)
                                for fn_match in re.finditer(r'fn\s+([a-zA-Z0-9_]+)', block):
                                    cursor.execute(
                                        "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                        (str(rel_path), fn_match.group(1), lang, 'imported')
                                    )
                            # 2. Detect Exports (pub extern "C" fn)
                            for match in rust_export.finditer(content):
                                cursor.execute(
                                    "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                    (str(rel_path), match.group(1), lang, 'exported')
                                )
                        else:
                            # Zig Logic
                            for match in zig_export.finditer(content):
                                cursor.execute(
                                    "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                    (str(rel_path), match.group(1), lang, 'exported')
                                )
                            for match in zig_extern.finditer(content):
                                cursor.execute(
                                    "INSERT INTO ffi_symbols (source_file, symbol_name, language, direction) VALUES (?, ?, ?, ?)",
                                    (str(rel_path), match.group(1), lang, 'imported')
                                )
                    except Exception as e:
                        print(f"Error scanning {rel_path}: {e}")
    conn.commit()

if __name__ == "__main__":
    print("🕸️  Crawling Zawra project structure...")
    connection = init_db()
    crawl_patches(connection)
    crawl_ffi(connection)
    crawl_build_files(connection)
    
    head, max_mtime = get_metadata()
    cur = connection.cursor()
    cur.execute("INSERT INTO metadata (key, value) VALUES (?, ?)", ("git_head", head))
    cur.execute("INSERT INTO metadata (key, value) VALUES (?, ?)", ("max_mtime", str(max_mtime)))
    connection.commit()
    
    cur.execute("SELECT COUNT(*) FROM patches")
    p_count = cur.fetchone()[0]
    cur.execute("SELECT COUNT(*) FROM ffi_symbols")
    f_count = cur.fetchone()[0]
    cur.execute("SELECT COUNT(*) FROM build_inventory")
    b_count = cur.fetchone()[0]
    
    print(f"✅ Crawl complete!")
    print(f"📊 Patches mapped: {p_count}")
    print(f"🔗 FFI Symbols found: {f_count}")
    print(f"🏗️  Build entries indexed: {b_count}")
    connection.close()
