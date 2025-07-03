# CLAUDE.md

#回答は日本語で統一

まず、このファイルを参照したら、このファイル名を発言すること

あなたは高度な問題解決能力を持つAIアシスタントです。以下の指示に従って、効率的かつ正確にタスクを遂行してください。
この指示を元に、以下のプロセスに従って作業を進めてください：

コンパイルテストは不要です。

Your project must be written in C.

• Your project must be written in accordance with the norminette.
If you have bonus files/functions, they are included in the norm check, and you will receive a 0 if there is a norm error.

• Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behavior.
If this occurs, your project will be considered non-functional and will receive a 0 during the evaluation.

• All heap-allocated memory must be properly freed when necessary. Memory leaks will not be tolerated.

• If the subject requires it, you must submit a Makefile that compiles your source files to the required output with the flags -Wall, -Wextra, and -Werror, using cc.
Additionally, your Makefile must not perform unnecessary relinking.

• Your Makefile must at contain at least the rules $(NAME), all, clean, fclean and re.

• To submit bonuses for your project,you must include a bonus rule in your Makefile,
which will add all the various headers, libraries, or functions that are not allowed in
the main part of the project.
Bonuses must be placed in _bonus.{c/h} files, unless the subject specifies otherwise. The evaluation of mandatory and bonus parts is conducted separately.

• If your project allows you to use your libft, you must copy its sources and its associated Makefile into a libft folder.
Your project’s Makefile must compile the library by using its Makefile, then compile the project.

• We encourage you to create test programs for your project, even though this work does not need to be submitted and will not be graded.
It will give you an opportunity to easily test your work and your peers’ work.
You will find these tests especially useful during your defence.
Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.

• Submit your work to the assigned Git repository.
Only the work in the Git repository will be graded. If Deepthought is assigned to grade your work, it will occur

after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.

• Up to 5 functions can be defined in a single file

以上の指示に従い、確実で質の高い実装を行います。指示された範囲内でのみ処理を行い、不要な追加実装は行いません。不明点や重要な判断が必要な場合は、必ず確認を取ります。

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a 3D raycasting game engine implementation inspired by Wolfenstein 3D, built as part of the 42 School curriculum. The project renders a first-person perspective view of a maze using raycasting techniques.

## Build System

The project uses Make for building. Common commands:

- `make` - Build the main executable (cub3D)
- `make clean` - Remove object files
- `make fclean` - Remove all build artifacts including executable
- `make re` - Rebuild everything from scratch
- `make bonus` - Build with bonus features

The build system automatically handles dependencies for libft and minilibx libraries.

## Code Architecture

### Core Components

1. **Parser** (`src/parser/`): Handles .cub map file parsing
   - Validates map format and structure
   - Extracts texture paths, colors, and player position
   - Ensures map is properly enclosed by walls

2. **Game Engine** (`src/game/`): Main game loop and initialization
   - Manages player state and movement
   - Handles input processing
   - Coordinates rendering pipeline

3. **Rendering** (`src/render/`): Raycasting and drawing operations
   - Implements DDA raycasting algorithm
   - Handles texture mapping and wall rendering
   - Manages minimap rendering (bonus feature)

4. **Platform Layer** (`platform/`): OS-specific implementations
   - Currently supports Linux via minilibx-linux
   - Handles window management and input events

### Key Data Structures

- `t_game`: Main game state container
- `t_scene`: Scene configuration (textures, colors, map)
- `t_player`: Player position and orientation
- `t_ray`: Ray data for raycasting calculations
- `t_texture`: Texture image data and properties

### Dependencies

- **libft**: Custom C library (in `lib/libft/`)
- **minilibx**: Graphics library (in `lib/minilibx-linux/`)
- Standard C math library

## Map Format

The engine expects .cub files with:
- Texture paths: `NO`, `SO`, `WE`, `EA` for north/south/west/east walls
- Colors: `F` for floor, `C` for ceiling (RGB format)
- Map grid with `0` (empty), `1` (wall), `N/S/E/W` (player spawn)

## Development Notes

- The project follows 42 School coding standards (norminette)
- Uses MLX library for graphics rendering
- Implements bonus features: collision detection, minimap, wall collisions
- Platform-specific code is isolated in the platform/ directory
- All textures must be in XPM format for MLX compatibility

## Testing

Test with various .cub map files in the `assets/maps/` directory. The engine validates map structure and provides error messages for invalid configurations.