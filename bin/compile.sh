#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."
gcc -o tripletriad src/main.c src/pliki.c src/interfejs.c src/zasady.c -lcurses -lm
