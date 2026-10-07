# Walkthrough

A scene-by-scene tour of what happens, in code, as you play a session of
Endless Car Highway. Read alongside [docs/game-flow.svg](docs/game-flow.svg)
for the visual version, and [ARCHITECTURE.md](ARCHITECTURE.md) for how the
pieces are organized.

## 1. Starting the executable

```
main() → std::srand(time(NULL)) → support game{} → while(game.running()) { update(); render(); }
```

Constructing `support` runs, in order: `initWindow()` (800×600 window,
60 FPS cap), `initFonts()` (loads `assets/fonts/Raleway-Bold.ttf`),
`initText()` (sets up the one shared `uiText` object used by every menu
screen), `initVariables()` (zeroes the menu-navigation index/timer fields).

The window is open and the title screen is about to draw for the first
time — nothing has touched `data/` yet.

## 2. The title screen

Every frame, `support::update()` calls `pollEvents()` then
`updateText1(retscreen())`. `retscreen()` looks at which menu item is
highlighted (`index`, 0–3 for New Game/High Scores/Options/Controls) and
which key was last pressed or is currently held, and returns a screen
number. With nothing pressed yet, it falls through to the default case and
`screentitle()` draws the four menu items plus a green highlight rectangle
tracking `index` (moved with Up/Down via `updateObjects()`).

Press Enter on **High Scores**, **Options**, or **Controls** and you drop
into that screen's own `while` loop (see
[ARCHITECTURE.md](ARCHITECTURE.md#the-screen-state-machine) for why these
are self-contained loops rather than single frames). Each reads a file,
shows it, and returns to the title screen on Backspace:

- **High Scores** (`screenhs()`) reads `data/high scores.txt` line by line
  into the display text, and separately renders a Yes/No "Clear high
  scores" prompt (`index4`, moved with Up/Down). The choice is only acted
  on when you leave: pressing Backspace with "Yes" selected calls
  `clearhs()`, which overwrites the file with the default `1.0 .. 5.0`
  scores for all three difficulties.
- **Controls** (`screencontrol()`) just dumps `data/controls.txt` to the
  screen until Backspace.

## 3. Changing the difficulty

**Options** (`screenopt()`) is the one screen that writes to disk on every
single frame it's open, not just on exit. Each loop iteration:

1. Reads `data/difficulty.txt` to figure out which of Easy/Medium/Hard is
   currently highlighted (`index2`).
2. Lets Up/Down move `index2`.
3. Immediately rewrites `data/difficulty.txt` with whatever `index2` now
   points at.

So the difficulty is "committed" continuously as you browse — there's no
separate confirm step, and no way to back out of a change once you've moved
the highlight off the original value. Backspace just leaves the screen; the
last value you landed on is what sticks.

## 4. Starting a new game

Selecting **New Game** routes to `screenng()`, which is the entry point for
an entire run. Setup, once:

- `initGameState()` writes `data/gamestate.txt = "true"` — this file is the
  run's "is it still alive" flag, polled every frame by `checkGameState()`.
- `initUserCar()`, `initopvehicles()`, `initgameText()`, `initDecor()` build
  the player's car, clear out any leftover traffic, build the HUD text
  object, and lay out the road borders.
- `initgamevariables()` reads `data/difficulty.txt` **once** for this run
  and sets the opponent speed/spawn-rate constants from it (Easy/Medium/
  Hard each map to different base speeds and timer increments; anything
  else falls back to a Medium-like default).

Then the run's own loop begins, running until `checkGameState()` returns
false.

## 5. The gameplay loop, frame by frame

Each iteration:

1. `pollEvents()` — also where Escape closes the window, from any screen.
2. `index3` (the pause menu's Yes/No selection) is reset to 0 ("Yes").
3. If Space is currently held, drop into the pause screen (see below) until
   Backspace is pressed.
4. `updateopvehicles()` — maybe spawns a new car/truck/van in a random lane
   (never the same lane twice in a row), advances every existing vehicle
   down the screen by its difficulty-scaled speed, scores and removes any
   that scroll past the bottom (car +20, van +30, truck +50), and — every
   time the hidden `lap` counter crosses another 100 — bumps all three
   vehicle speeds and shortens the spawn timer, so the longer a run goes,
   the harder it gets.
5. `moveUsercar()` — applies Left/Right (lane change) and Up/Down (forward
   offset within `floor`/`ceiling` bounds) from the keyboard, then checks
   the player's body rectangle against every opponent's body rectangle. A
   hit writes `data/gamestate.txt = "false"` and calls `updateScores()`
   immediately, right there in the input-handling function.
6. `updatestrips()` scrolls the lane-divider strips (cosmetic only).
7. `render2()` draws everything: borders, lanes, traffic, car, score HUD,
   pause overlay if any.
8. If `index3 > 0` (meaning you paused and chose "No"), call `exitgame()`;
   otherwise call `continuegame()` (a no-op reset of the pause UI state).

## 6. Pausing, and the Yes/No that actually matters

Holding Space enters a nested loop: `while (!isKeyPressed(Backspace)) { pausescreen(); }`.
`pausescreen()` draws "GAME PAUSED. CONTINUE?" with Yes/No, lets Left/Right
move `index3` between them (`updateObjects3()`), and renders the frozen
gameplay scene underneath via `render2()`.

The Yes/No choice isn't acted on inside the pause loop itself — Backspace
always breaks out of it. What you chose only matters afterwards, back in
the main run loop's step 8: if `index3` is still 0 ("Yes") when you resume,
`continuegame()` just clears the pause UI and play continues. If you had
moved to "No" (`index3 > 0`) before pressing Backspace, `exitgame()` runs
instead — the same ending as a collision.

## 7. Ending a run and updating scores

There are exactly two ways a run ends, and both converge on
`updateScores()`:

- **Collision**, detected inline in `moveUsercar()`.
- **Voluntary quit**, via the pause menu's "No" → `exitgame()`, which also
  writes `data/gamestate.txt = "false"`.

`updateScores()` re-reads `data/difficulty.txt` to find which 5-line block
of `data/high scores.txt` belongs to the current difficulty, parses those
five scores, and — if the just-finished run's `points` beats any of
them — inserts it in rank order, shifting the rest down and dropping the
lowest. The other two difficulties' blocks are read and rewritten
untouched.

Once `checkGameState()` sees `"false"`, `screenng()`'s loop exits and
control returns up through `update()` to `main()`. The next frame,
`retscreen()` defaults back to the title screen — there's no explicit "game
over" screen; you simply land back on the main menu, with your score
already saved.

## 8. Quitting the game

Closing the window, or pressing Escape, is handled inside `pollEvents()` —
which every screen's loop calls on every iteration — so it works
identically whether you're on the title screen, browsing options, or mid-run.
`window->close()` makes `support::running()` return false, which ends
`main()`'s outer loop and the process exits normally. No cleanup beyond the
`support` destructor (`delete this->window`) is needed; nothing else holds
unmanaged resources.
