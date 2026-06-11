#!/usr/bin/env python3
import sqlite3
import sys
import os
import subprocess
import re
from pathlib import Path

DB_NAME = "zawra_inventory.db"
DB_PATH = Path(__file__).resolve().parent / DB_NAME
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent

def query(sql):
    if not DB_PATH.exists():
        print(f"Error: {DB_PATH} not found. Run inventory_crawler.py first.")
        return

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    try:
        cursor.execute(sql)
        rows = cursor.fetchall()
        if not rows:
            print("No results found.")
            return

        cols = [description[0] for description in cursor.description]
        widths = [len(col) for col in cols]
        for row in rows:
            for i, val in enumerate(row):
                widths[i] = max(widths[i], len(str(val)))

        fmt = " | ".join(f"{{:<{w}}}" for w in widths)
        print(fmt.format(*cols))
        print("-+-".join("-" * w for w in widths))
        for row in rows:
            print(fmt.format(*(str(v) for v in row)))
            
    except Exception as e:
        print(f"SQL Error: {e}")
    finally:
        conn.close()

def extract_includes(content):
    # Matches #include <...> or #include "..." only at start of line
    return set(re.findall(r'^\s*#include\s+[<"]([^>"]+)[>"]', content, re.MULTILINE))

def read_file(term):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    sql = f"SELECT patch_path, target_path FROM patches WHERE patch_path LIKE '%{term}%' OR target_path LIKE '%{term}%' LIMIT 1"
    cursor.execute(sql)
    res = cursor.fetchone()
    conn.close()

    if res:
        patch, target = res
        patch_path = PROJECT_ROOT / patch
        target_path = PROJECT_ROOT / target

        p_content = patch_path.read_text(errors='ignore') if patch_path.exists() else ""
        t_content = target_path.read_text(errors='ignore') if target_path.exists() else ""

        # --- Dependency Audit ---
        if p_content and t_content:
            p_inc = extract_includes(p_content)
            t_inc = extract_includes(t_content)
            dropped = t_inc - p_inc
            added = p_inc - t_inc
            
            print(f"\n=== DEPENDENCY AUDIT: {os.path.basename(target)} ===")
            if dropped:
                print(f"⚠️  DROPPED HEADERS (In WebKit but not in Zawra):")
                for h in sorted(dropped): print(f"  - {h}")
            else:
                print("✅ All original headers preserved.")
            
            if added:
                print(f"➕ ADDED HEADERS (Zawra specific):")
                for h in sorted(added): print(f"  - {h}")
            print("==========================================\n")

        if patch_path.exists():
            print(f"--- [ZAWRAS PATCH] {patch} ---")
            print(p_content)
        
        if target_path.exists():
            print(f"\n--- [ORIGINAL WEBKIT] {target} ---")
            print(t_content)
    else:
        print(f"No file matching '{term}' found in database.")

def check_auto_update():
    if not DB_PATH.exists():
        subprocess.run([sys.executable, str(Path(__file__).resolve().parent / "inventory_crawler.py")])
        return

    try:
        current_head = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=PROJECT_ROOT).decode().strip()
    except:
        current_head = "unknown"

    max_mtime = 0
    search_dirs = [PROJECT_ROOT / "patches" / "webkit", PROJECT_ROOT / "src", PROJECT_ROOT / "dependencies"]
    for s_dir in search_dirs:
        if not s_dir.exists(): continue
        for root, _, files in os.walk(s_dir):
            if any(x in root for x in ["target", "zig-out", "zig-cache", "node_modules"]): continue
            for file in files:
                if file.startswith('.'): continue
                path = Path(root) / file
                try:
                    m = path.stat().st_mtime
                    if m > max_mtime: max_mtime = m
                except: continue

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT value FROM metadata WHERE key='git_head'")
        stored_head = cursor.fetchone()[0]
        cursor.execute("SELECT value FROM metadata WHERE key='max_mtime'")
        stored_mtime = float(cursor.fetchone()[0])
        
        if current_head != stored_head or max_mtime > stored_mtime:
            print("🔄 Changes detected. Auto-updating inventory...")
            subprocess.run([sys.executable, str(Path(__file__).resolve().parent / "inventory_crawler.py")])
    except:
        # Fallback if metadata table is missing or corrupt
        subprocess.run([sys.executable, str(Path(__file__).resolve().parent / "inventory_crawler.py")])
    finally:
        conn.close()

def build_audit():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    print("\n=== 🏗️  BUILD GRAPH AUDIT ===")
    
    # Get all entries and deduplicate by origin (patches override upstream)
    cursor.execute("SELECT source_file, build_file, target_name FROM build_inventory")
    all_entries = cursor.fetchall()
    
    # Filter: if the same build file exists in patches/ and webkit/source/, 
    # the patches version is the one that actually exists at build time.
    active_inventory = []
    
    # Map from normalized build file path (Source/...) to its origin
    build_file_map = {}
    for src, build, target in all_entries:
        norm_build = build.replace("patches/webkit/", "").replace("webkit/source/", "")
        if "patches/" in build:
            build_file_map[norm_build] = build
    
    for src, build, target in all_entries:
        # Ignore metadata-only variables
        if target == "WPE_SOURCES_FOR_INTROSPECTION":
            continue
            
        norm_build = build.replace("patches/webkit/", "").replace("webkit/source/", "")
        # If there is a patch for this build file, and we are looking at the upstream one, skip it
        if norm_build in build_file_map and "webkit/source/" in build:
            continue
        
        active_inventory.append((src, build, target))

    # 1. Detect Duplicates
    print("\nChecking for duplicate source listings...")
    counts = {}
    for src, build, target in active_inventory:
        if src not in counts: counts[src] = []
        counts[src].append((build, target))
    
    dupes_found = False
    for src, locs in counts.items():
        if len(locs) > 1:
            # ONLY flag if at least one of the locations is a Zawra patch
            has_zawra = any("patches/" in b for b, t in locs)
            if not has_zawra:
                continue

            unique_locs = set(locs)
            if len(unique_locs) > 1:
                print(f"❌ CRITICAL: File listed multiple times in build graph:")
                print(f"  - {src}")
                for b, t in unique_locs:
                    print(f"    In {b} (Target: {t})")
                dupes_found = True
    
    if not dupes_found:
        print("✅ No duplicate source listings found.")

    # 2. Detect Orphans (Source files not in build graph)
    print("\nChecking for orphaned source files (present but not built)...")
    cursor.execute("""
        SELECT patch_path FROM patches 
        WHERE file_type IN ('cpp', 'c', 'zig') 
        AND is_full_replacement = 1
    """)
    filesystem_files = [row[0] for row in cursor.fetchall()]
    
    build_files_set = {src for src, b, t in active_inventory}
    
    orphans = []
    for f in filesystem_files:
        # Normalize patches/webkit/Source/... to Source/...
        # or dependencies/...
        rel_path = f.replace("patches/webkit/", "").replace("dependencies/", "dependencies/")
        if rel_path not in build_files_set:
            # For dependencies, the path in build_inventory is relative to the dep root
            found = False
            for bf in build_files_set:
                if f.endswith(bf):
                    found = True
                    break
            if not found:
                orphans.append(f)
    
    if orphans:
        print("⚠️  WARNING: Orphaned source files (present in Zawra but not in any build file):")
        for o in sorted(orphans):
            print(f"  - {o}")
    else:
        print("✅ All source files are accounted for in the build graph.")

    print("============================\n")
    conn.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:")
        print("  read <file>      (Read Patch + WebKit Original)")
        print("  find <text>      (Search everything)")
        print("  patches          (List all patches)")
        print("  ffi              (List FFI symbols)")
        print("  audit            (Run build graph audit)")
    else:
        check_auto_update()
        cmd = sys.argv[1]
        
        if cmd == "patches":
            query("SELECT patch_path, target_path FROM patches")
        elif cmd == "ffi":
            query("SELECT symbol_name, source_file, language FROM ffi_symbols LIMIT 50")
        elif cmd == "audit":
            build_audit()
        elif cmd == "find" and len(sys.argv) > 2:
            term = f"%{sys.argv[2]}%"
            sql = f"SELECT 'PATCH' as type, patch_path as name, target_path as info FROM patches WHERE patch_path LIKE '{term}' OR target_path LIKE '{term}' UNION ALL SELECT 'FFI', symbol_name, source_file FROM ffi_symbols WHERE symbol_name LIKE '{term}'"
            query(sql)
        elif (cmd == "read" or cmd == "cat") and len(sys.argv) > 2:
            read_file(sys.argv[2])
        else:
            query(cmd)
