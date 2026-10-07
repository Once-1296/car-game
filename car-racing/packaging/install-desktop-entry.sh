#!/usr/bin/env bash
# Installs a desktop launcher icon (Terminal=false) so the game can be
# started without ever opening a terminal window.
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DEST="$HOME/.local/share/applications/car-racing.desktop"

mkdir -p "$(dirname "$DEST")"
sed "s|@INSTALL_DIR@|$ROOT_DIR|g" "$ROOT_DIR/packaging/car-racing.desktop.in" > "$DEST"
chmod +x "$DEST"

echo "Installed launcher: $DEST"
echo "Build the game first with scripts/build.sh if you haven't already."
echo "The game should now show up in your application launcher as 'Endless Car Highway'."
