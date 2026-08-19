# cub3d

A Linux raycasting project inspired by the classic Wolfenstein 3D renderer. The project parses `.cub` scene files, loads XPM textures, and renders a first-person 3D view using MiniLibX.

The repository contains two implementations:

- `MAN/`: mandatory raycaster with textured walls and keyboard movement.
- `BONUS/`: enhanced version with a minimap, mouse look, doors, and animated textures.

## Requirements

- Linux
- A C compiler such as `cc`
- `make`
- X11 development libraries: `libX11` and `libXext`
- MiniLibX for Linux, available as `minilibx-linux/` inside both `MAN/` and `BONUS/`

The Makefiles link with `-lmlx -lXext -lX11 -lm`. If MiniLibX is not present, add or build it in the relevant directory before compiling.

## Build And Run

Build the mandatory version:

```sh
cd MAN
make
./cub3d text.cub
```

Build the bonus version:

```sh
cd BONUS
make
./cub3d_bonus text.cub
```

The program requires exactly one argument, and the argument must use the `.cub` extension. Run `make clean` to remove object files, `make fclean` to remove object files and the executable, or `make re` to rebuild from scratch.

## Controls

### Mandatory

| Key                 | Action                  |
| ------------------- | ----------------------- |
| `W` / `S`           | Move forward / backward |
| `A` / `D`           | Strafe left / right     |
| Left / Right arrows | Turn left / right       |
| `ESC`               | Exit                    |

### Bonus

The bonus build supports all mandatory controls plus:

| Key            | Action                                        |
| -------------- | --------------------------------------------- |
| Mouse movement | Turn the view                                 |
| `SPACE`        | Open or close the door in front of the player |
| Hold `E`       | Trigger the animation                         |

## Map File Format

A `.cub` file contains four wall textures, floor and ceiling colors, and a closed map. Texture paths must point to `.xpm` files.

```text
NO images/north.xpm
SO images/south.xpm
WE images/west.xpm
EA images/east.xpm

F 60,60,60
C 30,30,30

111111
100001
10N001
100001
111111
```

Map characters:

- `1`: wall
- `0`: walkable space
- `N`, `S`, `E`, `W`: player start position and facing direction; exactly one is required
- ` `: spaces used as part of the map layout
- `D`: door, supported by the bonus build

The map must be enclosed by walls, contain exactly one player start, and appear after the texture and color definitions. Paths are resolved from the directory where the executable is run, so the example above expects the `images/` directory to be available from `MAN/` or `BONUS/`.

## Project Structure

```text
MAN/
  Makefile              Mandatory build
  main.c                Main loop and 3D rendering setup
  rays.c, 3dmap.c       Raycasting and wall projection
  player.c               Input and player movement
  Parsing/               Scene and map parsing
  images/                XPM textures

BONUS/
  Makefile              Bonus build
  main_bonus.c           Main loop with bonus rendering
  minimap_bonus.c        Minimap rendering
  door_mouse_bonus.c     Doors and mouse look
  animation_bonuc.c      Animated textures
  Parsing/               Scene and map parsing
  images/                XPM textures and animation assets
```

## Notes

- The window is configured for `1240 x 1240` pixels.
- The renderer uses a 60-degree field of view.
- The bonus build expects `images/door.xpm` and `images/anim0.xpm` through `images/anim3.xpm` in its asset directory.
