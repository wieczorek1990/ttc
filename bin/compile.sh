#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

# Use CMake build if build directory exists, otherwise configure first
if [ ! -d build ]; then
    mkdir -p build
    cd build
    cmake ..
    cd ..
fi

cd build
cmake --build .
cd ..

# Copy the binary to the project root for convenience
cp build/tripletriad ./tripletriad
