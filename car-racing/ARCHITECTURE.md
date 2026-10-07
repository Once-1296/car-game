# Architecture

This document describes how `car-racing` is put together: the module
boundaries, the state machine that drives the game, and the data it persists.
See [docs/game-flow.svg](docs/game-flow.svg) for the visual state diagram and
[WALKTHROUGH.md](WALKTHROUGH.md) for a scene-by-scene playthrough of the code.

## Modules

```
src/main.cpp      Entry point. Owns the top-level loop.
src/support.h     The `support` class interface + opcar/optruck/opvan structs.
src/support.cpp   Everything: window setup, menus, gameplay, scoring, rendering.
data/*.txt        Persisted game state (see "Persisted state" below).
assets/fonts/     Raleway + Asman TrueType fonts.
```

There is a single god-class, `support`, that owns the window, every piece of
game state, and every screen. `main.cpp` is intentionally thin:

```cpp
support game;
while (game.running()) {
    game.update();
    game.render();
}
```

This is a 60 FPS fixed loop (`setFramerateLimit(60)` in `initWindow()`).
`update()` and `render()` are the only two methods `main.cpp` ever calls —
everything else is `support`'s internal business.

## The screen state machine

The game has five screens, each represented by an integer returned from
`support::retscreen()` and dispatched in `support::updateText1(int)`:

| # | Screen            | Function             |
|---|--------------------|-----------------------|
| 1 | Title / main menu  | `screentitle()`       |
| 2 | High scores        | `screenhs()`          |
| 3 | Options (difficulty) | `screenopt()`       |
| 4 | Controls help      | `screencontrol()`     |
| 5 | Gameplay           | `screenng()`          |

**Important architectural quirk:** only `screentitle()` is a single pass per
call to `support::update()`. The other four screens (`screenhs`, `screenopt`,
`screencontrol`, `screenng`) each contain their own internal `while` loop that
polls events, updates, and renders repeatedly until some exit condition (a
Backspace press, or the run ending). This means one call to `game.update()`
from `main.cpp` can block for an entire menu visit, or an entire run of
gameplay — the "outer" 60 FPS loop in `main.cpp` effectively only turns over
between screens, not within them. Each of those inner loops drives its own
render() or render2() call per iteration, so the screen still updates at the
window's frame rate; `main.cpp`'s loop just isn't the thing pacing it while
you're inside a screen.

Selection within a screen (title menu item, difficulty, high-score "clear"
prompt, pause menu) is tracked with small index variables (`index`,
`index2`, `index3`, `index4`) and a parallel array of valid vertical
positions (`ht`, `ht2`, `ht3`, `ht4`) that both drives the highlight
rectangle's position and bounds how far Up/Down/Left/Right can move it.

## Persisted state instead of in-memory state

Rather than keeping shared state in member variables that screens read
directly, several things that would normally be plain fields are instead
round-tripped through text files in `data/`:

| File                 | Written by                          | Read by |
|-----------------------|--------------------------------------|---------|
| `data/difficulty.txt` | `screenopt()` (live, on every highlight change) | `screenopt()`, `initgamevariables()`, `updateopvehicles()`, `updateScores()` |
| `data/gamestate.txt`  | `initGameState()`, `moveUsercar()` (on collision), `exitgame()` | `checkGameState()` (polled every gameplay frame) |
| `data/high scores.txt`| `updateScores()`, `clearhs()`       | `screenhs()`, `updateScores()` |
| `data/controls.txt`   | — (static reference text)           | `screencontrol()` |

This makes the difficulty and "is a run currently active" flag durable
across the whole process lifetime by construction, at the cost of a file
open/read/write on nearly every frame that needs them (`updateopvehicles()`
re-reads `difficulty.txt` every frame of gameplay, for instance). It works
fine at this scale, but it's the first thing to change if this ever needs to
scale to larger state.

## Gameplay subsystems (inside `screenng()`)

- **Traffic**: `opcar`, `optruck`, `opvan` are small structs wrapping a
  `vector<sf::RectangleShape>` (a few rectangles each: wheels, body,
  windows). `spawnopcar/optruck/opvan(int lane)` build one, and
  `updateopcar/optruck/opvan(float speed)` move each instance down the
  screen, scoring it and deleting it once it scrolls past the bottom.
  `updateopvehicles()` decides what to spawn and when, with timers that
  accelerate as `lap` (a hidden distance counter, separate from the
  displayed score) crosses multiples of 100.
- **Player car**: `initUserCar()` builds the same kind of rectangle set;
  `moveUsercar()` handles lane changes (Left/Right) and forward/back offset
  (Up/Down) within `floor`/`ceiling` bounds, then checks the player's body
  rect (`usercar[4]`) against every opponent's body rect
  (`findIntersection`) to detect a collision.
- **Road**: `spawnstrips()`/`updatestrips()` scroll four lane-divider
  strips down the screen on a timer, purely cosmetic.
- **Scoring**: `points` is the on-screen score (opponent vehicles are worth
  20/30/50 depending on type when they scroll off-screen). `updateScores()`
  reads the current difficulty, finds where `points` ranks among that
  difficulty's top 5, and rewrites `data/high scores.txt` in place.

## Rendering

Two independent render paths exist, both called directly rather than through
a shared "draw current screen" dispatcher:

- `render()` — draws `rect`/`recths` (menu highlight boxes) + `uiTexts1`.
  Used by the four non-gameplay screens.
- `render2()` — draws the road, traffic, player car, score HUD, and pause
  overlay. Used only inside `screenng()`/`pausescreen()`.

## Porting layer (SFML 2 → SFML 3)

The original code targets SFML 2 on Windows (Visual Studio). SFML 3 changed
several APIs this code depends on; the Linux port adapts to them without
changing game logic:

- `sf::Text` lost its default constructor — it now requires a `sf::Font`
  reference at construction. `support::support()` initializes `uiText` and
  `uiTextgame` via a member-initializer list against `this->font` before the
  font file is actually loaded; `setFont()` is called again once
  `initFonts()` loads the real font data, since `sf::Text` stores a pointer
  to the `Font` object rather than a copy.
- `sf::Rect`/`sf::VideoMode` expose `size`/`position` as public `Vector2`
  members, not `width`/`height`/`getSize()`.
- `sf::FloatRect::intersects()` became `findIntersection()`, returning
  `std::optional<FloatRect>`.
- Event polling returns `std::optional<sf::Event>` from `pollEvent()`
  instead of taking an out-parameter.
