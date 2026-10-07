#!/usr/bin/env bash
# Configures and builds the Linux port with CMake.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

if ! pkg-config --exists sfml-all 2>/dev/null && ! pacman -Q sfml &>/dev/null; then
    echo "SFML 3 was not detected. On Arch: sudo pacman -S sfml"
    echo "On other distros, install SFML 3.x via your package manager or build from source."
fi

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"

echo
echo "Build complete: build/car-racing"
echo "Run it with: ./scripts/run.sh"
