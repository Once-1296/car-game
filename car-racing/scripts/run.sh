#!/usr/bin/env bash
# Launches the built game detached from the terminal, so the shell that
# started it is freed immediately and no console sticks around behind the
# game window. Use packaging/car-racing.desktop instead for a desktop/app
# launcher icon that never touches a terminal at all.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/build/car-racing"

if [[ ! -x "$BIN" ]]; then
    echo "Binary not found, building first..."
    "$ROOT_DIR/scripts/build.sh"
fi

cd "$ROOT_DIR/build"
setsid "$BIN" >/dev/null 2>&1 < /dev/null &
disown
