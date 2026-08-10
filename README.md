# cub3D

A first-person 3D maze renderer built in C with [MinilibX](https://github.com/42paris/minilibx-linux), inspired by *Wolfenstein 3D*. This is a project from the 42 School curriculum: the program parses a custom `.cub` scene file and renders a real-time raycasted view of the described maze, with textured walls, colored floor/ceiling, player movement, wall collision, and a 2D minimap.

## Overview

cub3D reproduces the classic grid-based raycasting technique used by early first-person games. Given a `.cub` scene file describing wall textures, floor/ceiling colors, and a 2D ASCII map, the engine:

1. Parses and validates the scene file (syntax, textures, colors, map shape).
2. Initializes a player position and facing direction from the map's spawn marker (`N`/`S`/`E`/`W`).
3. Casts one ray per screen column using the Digital Differential Analysis (DDA) algorithm to find the nearest wall.
4. Projects each wall hit into a vertical textured stripe, choosing the texture based on which face of the wall was hit (north/south/east/west).
5. Redraws the frame every loop tick while handling keyboard input for movement, rotation, and window close/quit events.

## Features

- **Raycasting engine** — per-pixel-column DDA wall detection using a camera-plane + direction-vector model (no fisheye distortion, since wall distance is computed as the *perpendicular* distance to the camera plane rather than the raw ray length).
- **Directional wall textures** — separate `.xpm` textures for north, south, east, and west-facing walls, selected per ray based on which axis (x-side or y-side) was hit and the ray's direction.
- **Floor and ceiling colors** — two independently configurable solid RGB colors, drawn as the top/bottom halves of each frame.
- **Player movement** — `W`/`A`/`S`/`D` for forward/backward/strafe movement, `←`/`→` arrow keys to rotate the view (rotation is applied to both the direction and camera-plane vectors).
- **Clean shutdown** — `ESC` or clicking the window's close button releases all MinilibX/image resources and exits the program.
- **Smooth window management** — rendering runs through MinilibX's loop hook, so the window keeps updating correctly across focus changes, minimizing, etc.
- **`.cub` scene parser** — a two-pass parser that:
  - accepts texture (`NO`, `SO`, `WE`, `EA`) and color (`F`, `C`) declarations in any order, separated by one or more blank/whitespace lines;
  - requires the ASCII map to be the last element in the file;
  - rejects duplicate texture/color declarations, missing elements, malformed RGB values, and non-`.xpm` texture paths;
  - preserves the map exactly as written (including interior spaces) rather than normalizing it.
- **Map validation** — every walkable (`0`) tile must have walls (not the map border or open space) on all sides, checked with both a direct neighbor scan and a recursive flood fill from the player's spawn tile, so any oddly-shaped (non-rectangular) maze is accepted as long as it is fully enclosed by `1` walls.
- **Bonus: wall collision** — the player's movement is blocked from entering wall tiles using a small radius check around the target position, so walls cannot be walked through or clipped into.
- **Bonus: 2D minimap** — a top-left overlay showing the wall layout of the maze and the player's current position, redrawn every frame alongside the 3D view.
- **Explicit error reporting** — any invalid usage or malformed scene file prints `Error` followed by a specific message to `stderr` and exits without crashing (invalid args, unreadable file, bad `.cub`/`.xpm` extension, unclosed map, duplicate declarations, out-of-range RGB values, etc.).

## Architecture & Implementation

### Tech stack

- **Language:** C (compiled with `-Wall -Wextra -Werror`)
- **Graphics:** [MinilibX](https://github.com/42paris/minilibx-linux) (X11-based), included as a git submodule
- **Standard library helpers:** a custom `libft` (string/memory/list utilities, `get_next_line`), built and linked as a static library
- **Windowing backend:** X11 (via XQuartz on macOS, native X11 on Linux)

### DDA raycasting

For each screen column, a ray direction is derived from the player's direction vector and camera plane. The algorithm then steps through grid cells one axis at a time (`side_dist_x`/`side_dist_y` vs. `delta_dist_x`/`delta_dist_y`), tracking which axis was stepped last (`side`) until a `1` (wall) tile is hit. The perpendicular wall distance (not the raw Euclidean ray length) is used to compute wall height, which avoids the "fisheye" lens distortion common to naive raycasters.

The camera plane vector has a magnitude of 0.66 relative to a unit direction vector, the standard raycasting convention that yields a horizontal field of view of roughly 66°.

### Texture selection and mapping

The hit `side` (x-axis vs. y-axis) together with the ray's direction determines which of the four directional textures (north/south/east/west) is sampled. The exact hit position along the wall is used to compute the horizontal texture coordinate, with the sampling direction flipped depending on which side of the wall was approached, so textures don't appear mirrored.

### Map parsing

Parsing is two-phase: the parser first walks the file collecting texture/color declarations (in any order, allowing blank-line separation), then locates and parses the trailing map block. The map array is validated for closure using both a per-tile neighbor check and a recursive flood fill from the player's spawn position, so it correctly accepts non-rectangular, arbitrarily shaped mazes as long as they're fully enclosed by walls.

### Movement and collision

Collision detection samples several points on a small radius around the player's prospective next position and rejects movement on either axis independently if any sampled point falls inside a wall tile, giving wall-sliding behavior instead of a hard stop.

### Platform layer

Key handling and window-close events are routed through a small platform abstraction (`platform_init`/`platform_handle_keypress`/`platform_close_window`) that maps raw X11 keycodes to the engine's own key constants, keeping the rendering/game logic independent of the windowing backend's raw event codes.

### Repository layout

```
src/
  parser/   .cub scene file parsing and validation (textures, colors, map, flood fill)
  game/     game loop, initialization, movement, cleanup
  render/   raycasting, wall/floor/ceiling drawing, texture sampling, minimap
  utils/    error reporting and small math/libft helpers
platform/linux/   MinilibX/X11 event hooks and window lifecycle
include/          cub3d.h (shared types/prototypes), keycodes.h
lib/libft/        custom libc-style helper library
lib/minilibx-linux/   MinilibX graphics library (git submodule)
assets/maps/      sample .cub scene files (valid and intentionally invalid, for testing)
assets/textures/  sample .xpm wall textures
```

## Build & Usage

### Requirements

- `cc` / a C compiler and `make`
- X11 development headers/libraries
  - Linux: `libxext-dev libx11-dev` (or your distro's equivalent)
  - macOS: [XQuartz](https://www.xquartz.org/) (provides `/opt/X11`)
- `git` (the MinilibX library is vendored as a submodule)

### Clone and build

```sh
git clone --recursive https://github.com/Kizuna42/cub3D
cd cub3D
# if you cloned without --recursive:
git submodule update --init --recursive

make
```

`make` builds `libft`, MinilibX, and the project sources, producing a `cub3D` executable in the repository root. The Makefile also supports:

- `make clean` — remove object files
- `make fclean` — remove object files and the compiled executable/libraries
- `make re` — `fclean` followed by a full rebuild
- `make bonus` — build the same `cub3D` binary (the collision and minimap features are compiled in by default, not gated behind a separate flag)

### Run

```sh
./cub3D <path/to/map.cub>
```

Example, using one of the sample maps shipped in this repository:

```sh
./cub3D assets/maps/test.cub
```

### Controls

| Key | Action |
| --- | --- |
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate the view left / right |
| `Esc` | Quit |
| Window close button | Quit |

## Notes

- No screenshots are included in this README; refer to the sample scene files under `assets/maps/` to try the renderer directly.
- `assets/maps/good/`, `assets/maps/bad/`, and `assets/maps/reference/` contain sample `.cub` files used to exercise both valid maze layouts and the parser's error handling.
- `subject.txt` and `evaluation.txt` in the repository root are the original 42 School project subject and evaluation checklist.
