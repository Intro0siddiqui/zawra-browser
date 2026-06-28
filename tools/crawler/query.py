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

        if p_content and t_content:
            p_inc = extract_includes(p_content)
            t_inc = extract_includes(t_content)
            dropped = t_inc - p_inc
            added = p_inc - t_inc

            print(f"\n=== DEPENDENCY AUDIT: {os.path.basename(target)} ===")
            if dropped:
                print(f"⚠️  DROPPED HEADERS (In WebKit but not in Zawra):")
                for h in sorted(dropped):
                    print(f"  - {h}")
            else:
                print("✅ All original headers preserved.")

            if added:
                print(f"➕ ADDED HEADERS (Zawra specific):")
                for h in sorted(added):
                    print(f"  - {h}")
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
    except Exception:
        current_head = "unknown"

    max_mtime = 0
    search_dirs = [PROJECT_ROOT / "patches" / "webkit", PROJECT_ROOT / "src", PROJECT_ROOT / "dependencies"]
    for s_dir in search_dirs:
        if not s_dir.exists():
            continue
        for root, _, files in os.walk(s_dir):
            if any(x in root for x in ["target", "zig-out", "zig-cache", "node_modules"]):
                continue
            for file in files:
                if file.startswith('.'):
                    continue
                path = Path(root) / file
                try:
                    m = path.stat().st_mtime
                    if m > max_mtime:
                        max_mtime = m
                except Exception:
                    continue

    needs_update = False
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT value FROM metadata WHERE key='git_head'")
        stored_head = cursor.fetchone()[0]
        cursor.execute("SELECT value FROM metadata WHERE key='max_mtime'")
        stored_mtime = float(cursor.fetchone()[0])

        if current_head != stored_head or max_mtime > stored_mtime:
            needs_update = True
    except Exception:
        needs_update = True
    finally:
        conn.close()

    if needs_update:
        print("🔄 Changes detected. Auto-updating inventory...")
        subprocess.run([sys.executable, str(Path(__file__).resolve().parent / "inventory_crawler.py")])


def build_audit():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()

    print("\n=== 🏗️  BUILD GRAPH AUDIT ===")

    cursor.execute("SELECT source_file, build_file, target_name FROM build_inventory")
    all_entries = cursor.fetchall()

    active_inventory = []
    build_file_map = {}
    for src, build, target in all_entries:
        norm_build = build.replace("patches/webkit/", "").replace("webkit/source/", "")
        if "patches/" in build:
            build_file_map[norm_build] = build

    for src, build, target in all_entries:
        if target == "WPE_SOURCES_FOR_INTROSPECTION":
            continue

        norm_build = build.replace("patches/webkit/", "").replace("webkit/source/", "")
        if norm_build in build_file_map and "webkit/source/" in build:
            continue

        active_inventory.append((src, build, target))

    print("\nChecking for duplicate source listings...")
    counts = {}
    for src, build, target in active_inventory:
        if src not in counts:
            counts[src] = []
        counts[src].append((build, target))

    dupes_found = False
    for src, locs in counts.items():
        if len(locs) > 1:
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
        rel_path = f.replace("patches/webkit/", "").replace("dependencies/", "dependencies/")
        if rel_path not in build_files_set:
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


def chain_trace(msg_name):
    if not DB_PATH.exists():
        print(f"Error: {DB_PATH} not found. Run inventory_crawler.py first.")
        return

    msg_re = re.compile(r'Messages::[A-Za-z0-9_:]*::' + re.escape(msg_name) + r'\b', re.IGNORECASE)
    send_re = re.compile(r'(?:^|[^A-Za-z:])send(?:Sync|WithAsyncReply|WithDelayedReply)?\(', re.IGNORECASE)
    handler_re = re.compile(r'didReceive(Sync)?Message\s*\(', re.IGNORECASE)
    generated_handler_re = re.compile(r'(?:handleMessage(?:Async)?|messageReceiverName|class\s+' + re.escape(msg_name) + r'|struct\s+' + re.escape(msg_name) + r'|' + re.escape(msg_name) + r'::name\(\))', re.IGNORECASE)
    actual_handler_re = re.compile(r'\b[A-Za-z0-9_:]+::' + re.escape(msg_name) + r'\s*\(', re.IGNORECASE)
    conn_re = re.compile(r'Connection::(sendSyncReply|sendMessage|processIncomingMessage|sendWithAsyncReply)|m_client->didReceiveMessage|messageReceiver\.didReceiveMessage', re.IGNORECASE)

    senders = []
    receivers = []
    declarations = []
    message_ids = []
    connections = []

    conn_db = sqlite3.connect(DB_PATH)
    cursor = conn_db.cursor()
    cursor.execute("SELECT patch_path, target_path FROM patches WHERE file_type IN ('cpp','h')")
    rows = cursor.fetchall()
    conn_db.close()

    files = []
    preferred = {}
    for p, t in rows:
        for rel in (p, t):
            if not rel:
                continue
            if rel.startswith("patches/webkit/"):
                key = rel[len("patches/webkit/"):]
                preferred[key] = rel
            elif rel.startswith("webkit/source/"):
                key = rel[len("webkit/source/"):]
                if key not in preferred:
                    preferred[key] = rel
            else:
                if rel not in preferred:
                    preferred[rel] = rel
    files.extend(preferred.values())

    generated_roots = [
        PROJECT_ROOT / "webkit" / "build" / "WPE" / "Debug" / "DerivedSources" / "WebKit",
        PROJECT_ROOT / "webkit" / "build" / "WPE" / "Release" / "DerivedSources" / "WebKit",
    ]
    for root in generated_roots:
        if root.exists():
            for path in list(root.glob("*.cpp")) + list(root.glob("*.h")):
                rel = str(path.relative_to(PROJECT_ROOT))
                if rel not in files:
                    files.append(rel)

    context_width = 4
    for rel in files:
        abs_path = PROJECT_ROOT / rel
        if not abs_path.exists():
            continue
        try:
            raw = abs_path.read_text(errors='ignore').split('\n')
        except Exception:
            continue

        file_mentions_msg = any(msg_re.search(line) for line in raw)
        if not file_mentions_msg and not rel.endswith("/Connection.cpp") and not rel.endswith("/Connection.h"):
            continue

        for i, line in enumerate(raw, 1):
            if send_re.search(line) and msg_re.search(line):
                senders.append((rel, i, line.strip()[:220]))

            if msg_re.search(line) and (generated_handler_re.search(line) or actual_handler_re.search(line)):
                declarations.append((rel, i, line.strip()[:220]))

            if file_mentions_msg and handler_re.search(line):
                lo = max(0, i - 1)
                hi = min(len(raw), i + context_width + 1)
                ctx = '\n'.join(f"    {raw[k].rstrip()}" for k in range(lo, hi))
                receivers.append((rel, i, ctx))

            if msg_re.search(line) and re.search(r'NetworkProcess[_A-Za-z0-9]*' + re.escape(msg_name), line):
                message_ids.append((rel, i, line.strip()[:220]))

            if conn_re.search(line) and (rel.endswith("/Connection.cpp") or rel.endswith("/Connection.h")):
                connections.append((rel, i, line.strip()[:180]))

    print(f"\n=== IPC Call Chain: {msg_name} ===\n")

    print("SENDER:")
    if senders:
        seen = set()
        for path, ln, text in senders[:10]:
            key = (path, text[:50])
            if key in seen:
                continue
            seen.add(key)
            print(f"  {path}:{ln}")
            print(f"    {text}")
    else:
        print(f"  (no exact sender found for '{msg_name}' in patches or generated WebKit IPC files)")

    print("\nMESSAGE DEFINITION / DISPATCH:")
    if declarations or message_ids:
        seen = set()
        for path, ln, text in (declarations + message_ids)[:12]:
            key = (path, ln, text[:50])
            if key in seen:
                continue
            seen.add(key)
            print(f"  {path}:{ln}")
            print(f"    {text}")
    else:
        print(f"  (no generated message definition or dispatch mapping found for '{msg_name}')")

    print("\nRECEIVER:")
    if receivers:
        seen = set()
        for path, ln, ctx in receivers[:10]:
            key = (path, ln)
            if key in seen:
                continue
            seen.add(key)
            print(f"  {path}:{ln}")
            print(ctx)
            print()
    else:
        print(f"  (no receiver entry point found for '{msg_name}')")

    print("CONNECTION:")
    if connections:
        seen = set()
        for path, ln, text in connections[:16]:
            key = (path, text[:50])
            if key in seen:
                continue
            seen.add(key)
            print(f"  {path}:{ln}")
            print(f"    {text}")
    else:
        print(f"  (no Connection / dispatch call site found for '{msg_name}')")

    print()


def deps(module_path):
    """Scan for all files that #include headers from a given module directory.

    Usage: zw deps <module_path>
    Example: zw deps Modules/webdatabase
             zw deps loader/appcache
             zw deps NetworkProcess/PrivateClickMeasurement

    Shows every file outside the module that includes its headers,
    categorized as PATCHES (can be modified) or UPSTREAM (need new patches).
    """
    if not DB_PATH.exists():
        print(f"Error: {DB_PATH} not found. Run inventory_crawler.py first.")
        return

    source_root = PROJECT_ROOT / "webkit" / "source" / "Source"
    patches_root = PROJECT_ROOT / "patches" / "webkit"

    if not source_root.exists():
        print(f"Error: {source_root} not found.")
        return

    module_dir = None
    for parent in ["WebCore", "WebKit", "WTF", "JavaScriptCore", "PAL"]:
        candidate = source_root / parent / module_path
        if candidate.exists():
            module_dir = candidate
            break

    if module_dir is None:
        candidate = source_root / module_path
        if candidate.exists():
            module_dir = candidate

    if module_dir is None:
        print(f"Error: Module directory not found for '{module_path}'.")
        print("Searched in:")
        for parent in ["WebCore", "WebKit", "WTF", "JavaScriptCore", "PAL"]:
            print(f"  Source/{parent}/{module_path}")
        print(f"  Source/{module_path}")
        print("\nAvailable modules:")
        for parent in ["WebCore", "WebKit"]:
            base = source_root / parent
            if not base.exists():
                continue
            for d in sorted(base.rglob("*")):
                if d.is_dir() and d.name and (d / "*.h").parent == d:
                    has_headers = any(d.glob("*.h"))
                    if has_headers:
                        rel = str(d.relative_to(source_root))
                        print(f"  {rel}")
        return

    headers = set()
    for h in module_dir.rglob("*.h"):
        headers.add(h.name)

    include_pattern = re.compile(r'^\s*#include\s+[<"]([^>"]+)[>"]', re.MULTILINE)

    consumers = []

    search_dirs = [source_root / "WebCore", source_root / "WebKit", source_root / "WTF", source_root / "JavaScriptCore"]
    search_dirs = [d for d in search_dirs if d.exists()]

    for search_dir in search_dirs:
        for root, _, files in os.walk(search_dir):
            for fname in files:
                if not (fname.endswith(".cpp") or fname.endswith(".h")):
                    continue

                fpath = Path(root) / fname
                rel = str(fpath.relative_to(source_root))

                try:
                    fpath.relative_to(module_dir)
                    continue
                except ValueError:
                    pass

                try:
                    content = fpath.read_text(errors='ignore')
                except Exception:
                    continue

                for m in include_pattern.finditer(content):
                    inc_path = m.group(1)
                    inc_basename = Path(inc_path).name

                    if inc_basename not in headers:
                        continue

                    line_num = content[:m.start()].count('\n') + 1
                    line_text = content.splitlines()[line_num - 1].strip() if line_num <= len(content.splitlines()) else ""

                    patch_match = None
                    candidate_patch = patches_root / "Source" / (str(fpath.relative_to(source_root)))
                    if candidate_patch.exists():
                        patch_match = str(candidate_patch.relative_to(PROJECT_ROOT))

                    consumers.append({
                        "file": rel,
                        "line": line_num,
                        "include": inc_path,
                        "basename": inc_basename,
                        "patch": patch_match,
                    })

    consumers.sort(key=lambda c: (c["file"], c["line"]))

    patches_files = [c for c in consumers if c["patch"]]
    upstream_files = [c for c in consumers if not c["patch"]]

    print(f"\n=== HEADER DEPENDENCY SCAN: {module_path} ===")
    print(f"Headers in module: {len(headers)}")
    print(f"Total consumers found: {len(consumers)}")
    print(f"  In patches/ (can modify): {len(patches_files)} includes across {len(set(c['file'] for c in patches_files))} files")
    print(f"  In source/ (need new patch): {len(upstream_files)} includes across {len(set(c['file'] for c in upstream_files))} files")

    if patches_files:
        print(f"\n--- PATCHES (already modifiable) ---")
        current_file = None
        for c in patches_files:
            if c["file"] != current_file:
                current_file = c["file"]
                print(f"\n  {c['patch']}:")
            print(f"    L{c['line']}: #include \"{c['include']}\"")

    if upstream_files:
        print(f"\n--- UPSTREAM (need new patches) ---")
        current_file = None
        for c in upstream_files:
            if c["file"] != current_file:
                current_file = c["file"]
                print(f"\n  {c['file']}:")
            print(f"    L{c['line']}: #include \"{c['include']}\"")

    print(f"\n{'=' * 50}")
    if upstream_files:
        print(f"⚠️  {len(set(c['file'] for c in upstream_files))} upstream files need patches before disabling this module.")
    else:
        print(f"✅ No upstream consumers — safe to disable.")
    print()


def list_patches_by_subsystem():
    if not DB_PATH.exists():
        print(f"Error: {DB_PATH} not found. Run inventory_crawler.py first.")
        return

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute("SELECT patch_path, target_path FROM patches")
    rows = cursor.fetchall()
    conn.close()

    if not rows:
        print("No patches found.")
        return

    categories = {
        "Hajr IPC & Sandbox": [],
        "Z-Net Networking": [],
        "z-graphics Vulkan RHI": [],
        "BrowserDB Storage": [],
        "Build System Config": [],
        "Other Patches": []
    }

    for patch_path, target_path in rows:
        path_lower = patch_path.lower()
        
        # 1. Build System Config
        if any(x in path_lower for x in ["cmakelists.txt", "sources.txt", "sourceswpe.txt", "headers.cmake", "optionswpe.cmake", "platformwpe.cmake"]):
            categories["Build System Config"].append((patch_path, target_path))
        # 2. Hajr IPC & Sandbox
        elif any(x in path_lower for x in ["hajr", "moriarty", "gpuprocessmainglib", "networkprocesssoup", "connection", "processlauncherglib", "webprocessglib"]):
            categories["Hajr IPC & Sandbox"].append((patch_path, target_path))
        # 3. Z-Net Networking
        elif any(x in path_lower for x in ["znet", "z_net", "networkdatatask"]):
            categories["Z-Net Networking"].append((patch_path, target_path))
        # 4. z-graphics Vulkan RHI
        elif any(x in path_lower for x in ["z_graphics", "z-graphics", "graphics/zawra"]):
            categories["z-graphics Vulkan RHI"].append((patch_path, target_path))
        # 5. BrowserDB Storage (WebSQL, AppCache, LocalStorage, IndexedDB, etc.)
        elif any(x in path_lower for x in ["webdatabase", "appcache", "indexeddb", "push-api", "localstoragemanager", "storageareabase", "browserdbstoragearea", "swregistrationdatabase", "resourceloadstatisticsdatabasestore", "privateclickmeasurement", "zawrastoragebridge", "zitpbridge", "zpcmbridge", "zswregbridge", "zwebsqlbridge", "zappcachebridge", "zpushbridge"]):
            categories["BrowserDB Storage"].append((patch_path, target_path))
        else:
            categories["Other Patches"].append((patch_path, target_path))

    print("\n===========================================")
    print("      ZAWRAS PATCH SUBSYSTEM BREAKDOWN     ")
    print("===========================================")
    for cat, items in categories.items():
        if items:
            print(f"\n📁 {cat} ({len(items)} files):")
            for p, t in sorted(items):
                print(f"  - {p}")
    print("\n===========================================")
    total = sum(len(items) for items in categories.values())
    print(f"Total Patches: {total}")
    print("===========================================\n")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:")
        print("  read <file>      (Read Patch + WebKit Original)")
        print("  find <text>      (Search patches & FFI)")
        print("  patches          (List all patches)")
        print("  ffi              (List FFI symbols)")
        print("  audit            (Run build graph audit)")
        print("  stubs            (List detected stubs / stub patterns)")
        print("  chain <MessageName>  (Trace IPC call chain)")
        print("  deps <module_path>  (Scan header deps before disabling a feature)")
        print("    e.g. zw deps Modules/webdatabase")
        print("    e.g. zw deps loader/appcache")
        print("    e.g. zw deps NetworkProcess/PrivateClickMeasurement")
    else:
        check_auto_update()
        cmd = sys.argv[1]

        if cmd == "patches":
            list_patches_by_subsystem()
        elif cmd == "ffi":
            query("SELECT symbol_name, source_file, language FROM ffi_symbols LIMIT 50")
        elif cmd == "audit":
            build_audit()
        elif cmd == "stubs":
            severity_filter = None
            pattern_filter = None
            as_json = False
            just_count = False

            args = sys.argv[2:]
            i = 0
            while i < len(args):
                arg = args[i]
                if arg == "--severity" and i + 1 < len(args):
                    severity_filter = args[i+1]
                    i += 2
                elif arg == "--pattern" and i + 1 < len(args):
                    pattern_filter = args[i+1]
                    i += 2
                elif arg == "--json":
                    as_json = True
                    i += 1
                elif arg == "--count":
                    just_count = True
                    i += 1
                else:
                    i += 1

            if just_count:
                sql = "SELECT COUNT(*) FROM stubs"
                where_clauses = []
                if severity_filter:
                    where_clauses.append(f"severity = '{severity_filter}'")
                if pattern_filter:
                    where_clauses.append(f"pattern_type = '{pattern_filter}'")
                if where_clauses:
                    sql += " WHERE " + " AND ".join(where_clauses)
                query(sql)
            elif as_json:
                import json
                conn = sqlite3.connect(DB_PATH)
                cursor = conn.cursor()
                sql = "SELECT file_path, line_number, function_name, pattern_type, severity, context FROM stubs"
                where_clauses = []
                if severity_filter:
                    where_clauses.append(f"severity = '{severity_filter}'")
                if pattern_filter:
                    where_clauses.append(f"pattern_type = '{pattern_filter}'")
                if where_clauses:
                    sql += " WHERE " + " AND ".join(where_clauses)
                cursor.execute(sql)
                rows = cursor.fetchall()
                results = []
                for r in rows:
                    results.append({
                        "file_path": r[0],
                        "line_number": r[1],
                        "function_name": r[2],
                        "pattern_type": r[3],
                        "severity": r[4],
                        "context": r[5]
                    })
                print(json.dumps(results, indent=2))
                conn.close()
            else:
                sql = "SELECT file_path, line_number, function_name, pattern_type, severity, context FROM stubs"
                where_clauses = []
                if severity_filter:
                    where_clauses.append(f"severity = '{severity_filter}'")
                if pattern_filter:
                    where_clauses.append(f"pattern_type = '{pattern_filter}'")
                if where_clauses:
                    sql += " WHERE " + " AND ".join(where_clauses)
                query(sql)
        elif cmd == "find" and len(sys.argv) > 2:
            term = f"%{sys.argv[2]}%"
            sql = f"SELECT 'PATCH' as type, patch_path as name, target_path as info FROM patches WHERE patch_path LIKE '{term}' OR target_path LIKE '{term}' UNION ALL SELECT 'FFI', symbol_name, source_file FROM ffi_symbols WHERE symbol_name LIKE '{term}'"
            query(sql)
        elif (cmd == "read" or cmd == "cat") and len(sys.argv) > 2:
            read_file(sys.argv[2])
        elif cmd == "chain" and len(sys.argv) > 2:
            chain_trace(sys.argv[2])
        elif cmd == "deps" and len(sys.argv) > 2:
            deps(sys.argv[2])
        else:
            query(cmd)
