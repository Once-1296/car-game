#!/usr/bin/env bash
# Installs the game to a real prefix so it can be launched from anywhere --
# a PATH entry, an app launcher icon, a .desktop file -- with no dependency
# on the build directory or current working directory.
#
# Defaults to a user-level install (no root needed): ~/.local/{bin,share}.
# Pass --system for a machine-wide install to /usr/local (needs sudo).
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PREFIX="$HOME/.local"
SUDO=""

if [[ "${1:-}" == "--system" ]]; then
    PREFIX="/usr/local"
    SUDO="sudo"
fi

# The install prefix has to be known at *configure* time, not just install
# time: packaging/car-racing.desktop.in is expanded by configure_file()
# during `cmake -S -B`, so a prefix only passed to `cmake --install` would
# leave the previous (likely wrong) path baked into the installed .desktop.
cmake -S "$ROOT_DIR" -B "$ROOT_DIR/build" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$PREFIX"
cmake --build "$ROOT_DIR/build" -j"$(nproc)"

$SUDO cmake --install "$ROOT_DIR/build"

echo
echo "Installed to $PREFIX."
echo "Binary:  $PREFIX/bin/car-racing"
echo "Data:    $PREFIX/share/car-racing/"
echo "Launcher: $PREFIX/share/applications/car-racing.desktop (shows up as 'Endless Car Highway')"
if [[ "$PREFIX" == "$HOME/.local" ]]; then
    case ":$PATH:" in
        *":$HOME/.local/bin:"*) ;;
        *) echo "Note: $HOME/.local/bin isn't on your PATH -- add it, or launch via the desktop icon instead." ;;
    esac
fi
