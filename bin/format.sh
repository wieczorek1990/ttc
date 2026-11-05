#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

# Find clang-format: check common locations
if command -v clang-format &>/dev/null; then
    CLANG_FORMAT="clang-format"
elif [ -x "${HOME}/Library/Python/3.13/bin/clang-format" ]; then
    CLANG_FORMAT="${HOME}/Library/Python/3.13/bin/clang-format"
elif [ -x "${HOME}/.local/bin/clang-format" ]; then
    CLANG_FORMAT="${HOME}/.local/bin/clang-format"
else
    echo "Error: clang-format not found" >&2
    exit 1
fi

for f in src/*.c src/*.h; do
    "$CLANG_FORMAT" -i "$f"
done
