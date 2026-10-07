#!/usr/bin/env bash
# Runs the build-tree binary (not an installed copy -- see scripts/install.sh
# for that) detached from the terminal, so the shell that started it is
# freed immediately and no console sticks around behind the game window.
# The binary finds its own assets relative to its executable path, so this
# no longer needs to run from inside build/.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/build/car-racing"

if [[ ! -x "$BIN" ]]; then
    echo "Binary not found, building first..."
    "$ROOT_DIR/scripts/build.sh"
fi

setsid "$BIN" >/dev/null 2>&1 < /dev/null &
disown
