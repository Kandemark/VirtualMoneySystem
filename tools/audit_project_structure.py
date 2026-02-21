#!/usr/bin/env python3
"""Audit empty files and module linkage hygiene for VirtualMoneySystem."""
from __future__ import annotations

from collections import defaultdict
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

CODE_EXTS = {".cpp", ".cc", ".c", ".h", ".hpp", ".py", ".kt", ".json", ".md"}
IGNORE_PREFIXES = {
    ".git/",
    "build/",
    "logs/",
    "vendor/",
    "lib/",
}


def ignored(rel: str) -> bool:
    return any(rel.startswith(prefix) for prefix in IGNORE_PREFIXES)


def collect_empty_files() -> list[str]:
    out: list[str] = []
    for p in ROOT.rglob("*"):
        if not p.is_file():
            continue
        rel = p.relative_to(ROOT).as_posix()
        if ignored(rel):
            continue
        if p.suffix not in CODE_EXTS:
            continue
        if p.stat().st_size == 0:
            out.append(rel)
    return sorted(out)


def collect_module_index() -> dict[str, list[str]]:
    modules: dict[str, list[str]] = defaultdict(list)
    for p in ROOT.rglob("*"):
        if not p.is_file() or p.suffix not in {".cpp", ".h", ".hpp"}:
            continue
        rel = p.relative_to(ROOT).as_posix()
        if ignored(rel):
            continue
        top = rel.split("/", 1)[0]
        modules[top].append(rel)
    return {k: sorted(v) for k, v in sorted(modules.items())}


def collect_cross_module_includes() -> dict[str, set[str]]:
    include_re = re.compile(r'^\s*#\s*include\s+["<]([^">]+)[">]', re.MULTILINE)
    links: dict[str, set[str]] = defaultdict(set)
    for p in ROOT.rglob("*.cpp"):
        rel = p.relative_to(ROOT).as_posix()
        if ignored(rel):
            continue
        src_mod = rel.split("/", 1)[0] if "/" in rel else "root"
        text = p.read_text(errors="ignore")
        for m in include_re.finditer(text):
            inc = m.group(1)
            # Resolve include relative to source file when possible.
            candidate = (p.parent / inc).resolve()
            try:
                rel_inc = candidate.relative_to(ROOT).as_posix()
            except Exception:
                rel_inc = inc

            if "/" not in rel_inc:
                continue
            dst_mod = rel_inc.split("/", 1)[0]
            if dst_mod in {"..", ".", "usr", "opt"}:
                continue
            if dst_mod != src_mod:
                links[src_mod].add(dst_mod)
    return links


def main() -> int:
    empty = collect_empty_files()
    modules = collect_module_index()
    links = collect_cross_module_includes()

    report = ROOT / "docs" / "project_audit.md"
    lines: list[str] = []
    lines.append("# Project Audit: Empty Files & Module Linkage\n")
    lines.append(f"Generated from repository scan at `{ROOT}`.\n")

    lines.append("## Empty Files (excluding build/logs/vendor/lib)\n")
    lines.append(f"Total empty files detected: **{len(empty)}**\n")
    if empty:
        for rel in empty:
            lines.append(f"- `{rel}`")
    else:
        lines.append("- None")

    lines.append("\n## Module Inventory\n")
    for mod, files in modules.items():
        lines.append(f"- `{mod}`: {len(files)} code/header files")

    lines.append("\n## Cross-Module Include Connectivity (from .cpp files)\n")
    if not links:
        lines.append("- No cross-module includes detected.")
    else:
        for src in sorted(links):
            dst = ", ".join(sorted(links[src]))
            lines.append(f"- `{src}` -> {dst}")

    lines.append("\n## Recommended Next Steps\n")
    lines.append("1. Prioritize implementing non-empty content for empty `.cpp/.h/.hpp` business modules first (ignore logs/docs placeholders).")
    lines.append("2. Keep generated docs synced by running this audit script before release.")
    lines.append("3. Add this audit to CI and fail on newly introduced empty code files.")

    report.write_text("\n".join(lines) + "\n")
    print(f"Wrote {report.relative_to(ROOT)}")
    print(f"Empty files: {len(empty)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
