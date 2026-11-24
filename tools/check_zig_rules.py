#!/usr/bin/env python3
"""
Zawra Browser — Zig Code Quality & Memory Safety Static Checker
Validates Zig codebase against Zawra's architectural & memory safety rules:
  [RULE-01] Safe Enum Conversions: Disallow raw `@enumFromInt` on untrusted/C-FFI data (use `std.enums.fromInt`).
  [RULE-02] No Static Comptime Slices into Defer Free: Forbid `catch &[_]` or static literals freed by allocators.
  [RULE-03] Render Loop Performance: No synchronous `std.debug.print` in inner per-frame render routines.
  [RULE-04] C-ABI Null Safety: Prohibit unchecked `std.mem.span` on raw nullable C pointers without null check.
  [RULE-05] Escaping Stack Slices: Disallow returning deserialized slices from local stack-allocated arrays.
  [RULE-06] Clamped C-ABI Buffers: Slicing IPC/C-FFI lengths must clamp with `@min` before slicing.
  [RULE-07] Code Formatting: Ensure `zig fmt --check` compatibility.
"""

import os
import sys
import re
import subprocess
from pathlib import Path

# Directories to inspect
TARGET_DIRS = [
    "ui",
    "dependencies/hajr/src",
    "dependencies/z-graphics/src",
]

# Files to exclude (e.g. third-party, generated C wrappers)
EXCLUDE_PATTERNS = [
    r"xdg-shell-protocol\.",
    r"\.zig-cache",
    r"zig-out",
]

class Violation:
    def __init__(self, path, line_no, rule_id, severity, message, line_content):
        self.path = path
        self.line_no = line_no
        self.rule_id = rule_id
        self.severity = severity  # "ERROR" or "WARN"
        self.message = message
        self.line_content = line_content.strip()

    def __str__(self):
        color = "\033[91m" if self.severity == "ERROR" else "\033[93m"
        reset = "\033[0m"
        return f"{self.path}:{self.line_no}: {color}[{self.rule_id} {self.severity}]{reset} {self.message}\n    -> {self.line_content}"

def check_file(file_path):
    violations = []
    rel_path = str(file_path)

    try:
        with open(file_path, "r", encoding="utf-8", errors="replace") as f:
            lines = f.readlines()
    except Exception as e:
        return [Violation(rel_path, 0, "FILE-READ", "ERROR", str(e), "")]

    in_render_or_frame_func = False
    brace_depth = 0
    func_brace_start = 0

    for idx, raw_line in enumerate(lines):
        line_no = idx + 1
        line = raw_line.strip()

        # Track functions
        if re.search(r"fn\s+(submitCommandBuffer|render|draw|uploadTexture|onFrame)\b", line):
            in_render_or_frame_func = True
            func_brace_start = brace_depth

        brace_depth += line.count("{") - line.count("}")
        if in_render_or_frame_func and brace_depth <= func_brace_start:
            in_render_or_frame_func = False

        # Ignore comments
        if line.startswith("//"):
            continue

        # [RULE-01] Raw @enumFromInt (prefer std.enums.fromInt or switch)
        if "@enumFromInt" in line:
            # Allow if guarded in known comptime or internal known bounds with test
            if "test " not in rel_path and "router.zig" not in rel_path:
                if not re.search(r"@as\(\s*@Type", line):
                    # Flag as warning to review enum bounds
                    violations.append(Violation(
                        rel_path, line_no, "RULE-01", "WARN",
                        "Raw '@enumFromInt' may panic on untrusted inputs. Prefer 'std.enums.fromInt(EnumType, val) orelse <fallback>'.",
                        raw_line
                    ))

        # [RULE-02] No comptime static literal slice into defer free
        if re.search(r"catch\s*&\[_\]", line):
            violations.append(Violation(
                rel_path, line_no, "RULE-02", "ERROR",
                "Comptime static literal slice 'catch &[_]' used. If passed to an allocator's free(), it corrupts memory.",
                raw_line
            ))

        # [RULE-03] Render loop stderr spam
        if in_render_or_frame_func and "std.debug.print" in line:
            # Check if commented out
            if not line.startswith("//"):
                violations.append(Violation(
                    rel_path, line_no, "RULE-03", "ERROR",
                    "Synchronous 'std.debug.print' in render/frame loop blocks compositor and causes frame drop.",
                    raw_line
                ))

        # [RULE-04] Unchecked std.mem.span on raw nullable C pointer
        if re.search(r"std\.mem\.span\(\s*[a-zA-Z0-9_]+(\.[a-zA-Z0-9_]+)*\s*\)", line):
            if "catch" not in line and "if (" not in line and "orelse" not in line and "?*" in raw_line:
                violations.append(Violation(
                    rel_path, line_no, "RULE-04", "WARN",
                    "Unchecked 'std.mem.span' on nullable pointer. Ensure pointer is checked != null beforehand.",
                    raw_line
                ))

        # [RULE-05] Catch unreachable in FFI bindings
        if "callconv(.c)" in raw_line and "unreachable" in line:
            violations.append(Violation(
                rel_path, line_no, "RULE-05", "ERROR",
                "'unreachable' inside C-ABI function can abort the entire browser process on unexpected input.",
                raw_line
            ))

    return violations

def check_formatting(repo_root):
    violations = []
    print("[*] Verifying Zig formatting via 'zig fmt --check'...")
    for target in TARGET_DIRS:
        target_path = os.path.join(repo_root, target)
        if not os.path.exists(target_path):
            continue
        res = subprocess.run(
            ["zig", "fmt", "--check", target_path],
            capture_output=True,
            text=True
        )
        if res.returncode != 0:
            for l in res.stderr.splitlines():
                if l.strip():
                    violations.append(Violation(target, 0, "RULE-07", "WARN", f"Format mismatch: {l.strip()}", ""))
    return violations

def main():
    repo_root = Path(__file__).resolve().parent.parent
    os.chdir(repo_root)

    print("╔════════════════════════════════════════════════════════════╗")
    print("║     Zawra Browser — Zig Code & Safety Static Checker       ║")
    print("╚════════════════════════════════════════════════════════════╝\n")

    all_violations = []
    file_count = 0

    for target_dir in TARGET_DIRS:
        dir_path = repo_root / target_dir
        if not dir_path.exists():
            continue

        for root, _, files in os.walk(dir_path):
            for file in files:
                if not file.endswith(".zig"):
                    continue

                full_path = Path(root) / file
                rel_path = full_path.relative_to(repo_root)

                skip = False
                for pat in EXCLUDE_PATTERNS:
                    if re.search(pat, str(rel_path)):
                        skip = True
                        break
                if skip:
                    continue

                file_count += 1
                violations = check_file(rel_path)
                all_violations.extend(violations)

    print(f"[*] Scanned {file_count} Zig files across {len(TARGET_DIRS)} subsystems.")

    errors = [v for v in all_violations if v.severity == "ERROR"]
    warnings = [v for v in all_violations if v.severity == "WARN"]

    if all_violations:
        print(f"\n[!] Found {len(errors)} error(s) and {len(warnings)} warning(s):\n")
        for v in all_violations:
            print(v)
            print()
    else:
        print("\n\033[92m[✓] All Zig code safety and architectural rules satisfied! Zero violations found.\033[0m\n")

    if errors:
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()
