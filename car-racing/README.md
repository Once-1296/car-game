# Endless Car Highway — Linux Port

A top-down 4-lane car dodging game, originally built with SFML 2 in a
Windows Visual Studio project. This branch ports it to SFML 3 and a
CMake-based Linux build.

## Layout

```
car-racing/
├── src/          main.cpp, support.cpp, support.h
├── data/         bundled default save-data templates (seeded into
│                 ~/.local/share/car-racing/saves/ on first run)
├── assets/fonts/ Raleway + Asman font files
├── packaging/    car-racing.desktop template (no terminal window)
├── scripts/      build.sh / run.sh / install.sh
└── CMakeLists.txt
```

Resource paths are resolved relative to the running executable's own
location, not the working directory (see `support::initPaths()` in
`src/support.cpp`), so the game runs the same whether you launch it from
the build tree, an installed prefix, or a desktop icon. See
`ARCHITECTURE.md` for the full breakdown.

## Build

Requires SFML 3.x and a C++17 compiler.

```sh
# Arch Linux
sudo pacman -S sfml cmake

./scripts/build.sh
```

This configures and builds into `build/`, copying `assets/` and `data/`
alongside the binary for convenience when running straight out of the
build tree.

## Run (without installing)

```sh
./scripts/run.sh
```

This detaches the game from the terminal (`setsid` + `disown`), so the
shell is freed immediately instead of sitting blocked behind the game
window for the duration of the session. Save data still goes to
`~/.local/share/car-racing/saves/` either way.

## Install

For a real install — launchable from anywhere, a desktop icon, no
dependency on this directory sticking around:

```sh
./scripts/install.sh            # user-level, no root: ~/.local/{bin,share}
./scripts/install.sh --system   # machine-wide: /usr/local (needs sudo)
```

This builds, runs `cmake --install`, and drops a `Terminal=false` `.desktop`
entry so the game shows up as "Endless Car Highway" in your application
launcher. Read data (fonts, default save templates) lives under
`<prefix>/share/car-racing/`; your actual save data lives separately, under
`~/.local/share/car-racing/saves/`, so reinstalling or upgrading never
touches your scores.

## Controls

See `data/controls.txt`, or in-game via the Controls menu entry.

## Porting notes

SFML 3 changed several APIs from the SFML 2 code this was originally
written against:

- `sf::Text` has no default constructor anymore — it now requires a
  `sf::Font` at construction time, so `support::support()` initializes
  `uiText`/`uiTextgame` via a member-initializer list before the real
  font is loaded.
- `sf::VideoMode`/`sf::Rect` expose `size`/`position` as `Vector2` members
  rather than separate `width`/`height`/`getSize()` accessors.
- `sf::FloatRect::intersects()` became `findIntersection()`, returning an
  `std::optional<FloatRect>`.
- `sf::Keyboard::Key` enumerators moved under `Key::`, and event polling
  uses `pollEvent()` returning `std::optional<sf::Event>`.
