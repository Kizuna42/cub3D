# cub3D - 42 School Project

## 1. Project Overview

This project, `cub3D`, is a 42 school assignment focused on creating a 3D graphical representation of a maze from a first-person perspective using the principles of RayCasting. The goal is to parse a scene description file (`.cub`) and render a dynamic view of the maze, allowing the user to navigate through it.

### Core Objectives

- **Parse Scene Files:** Accurately parse `.cub` files containing texture paths, color settings, and a map layout.
- **Render with RayCasting:** Implement a RayCasting engine to render the maze walls with correct textures, perspective, and depth.
- **Player Navigation:** Enable smooth movement and camera rotation using keyboard inputs.
- **Cross-Platform Compatibility:** Ensure the program works flawlessly on both macOS (for development) and Linux (for submission).
- **Adherence to 42's Rules:** The project must comply with `norminette`, use only allowed functions, have no memory leaks, and include a specific `Makefile`.

## 2. Our Approach & Strategy

To balance development speed and final compatibility, we adopt a hybrid development strategy.

- **Development Environment:** macOS with `minilibx_opengl` for a fast and efficient coding workflow.
- **Validation Environment:** Linux on a VM (UTM) with `minilibx-linux` to guarantee compatibility with the submission environment.
- **Abstraction Layer:** OS-dependent code is isolated in the `platform/` directory to keep the core logic in `src/` platform-agnostic. This is key to our strategy.

## 3. Team & Roles

- **KIZUNA:** Project Management, core logic implementation (with AI assistance), and technical lead.
- **KANA:** Asset creation (textures, maps), test case design, and implementation support.

## 4. Development Rules & Workflow

To maintain code quality and streamline collaboration, we adhere to the following rules.

### Definition of "Done"

A task in `PROJECT_PLAN.md` is considered complete only when:

1. The code is **`norminette`-compliant** (excluding `TODO`/`FIXME` comments).
2. The project **compiles successfully on both macOS and Linux** with `-Wall -Wextra -Werror`.
3. The implemented feature passes all relevant **functional tests**.
4. All changes are **pushed** to the remote repository.

### Git Workflow

- Always run `git pull` before starting work.
- `push` your changes frequently to keep the remote repository up-to-date.
- Commit messages should be clear and descriptive (e.g., `feat(parser): Implement map validation`).

### Code & Comments

- **Memory:** No memory leaks are permitted. All allocated memory must be freed.
- **Functions:** A maximum of 5 functions are allowed per file.
- **Comments:** Use `// TODO: [description]` for pending tasks and `// FIXME: [description]` for known issues. These comments are temporarily exempt from `norminette` checks.

For a detailed step-by-step process, please refer to [docs/DEVELOPMENT_FLOW.md](docs/DEVELOPMENT_FLOW.md).

## 5. Building and Running

### Prerequisites

#### macOS

- Xcode Command Line Tools
- No additional packages required (minilibx_opengl included)

#### Linux

Before building on Linux, ensure you have the required dependencies:

```bash
# Check dependencies (recommended)
./check_linux_deps.sh

# Manual installation for Ubuntu/Debian:
sudo apt update
sudo apt install libx11-dev libxext-dev zlib1g-dev gcc make

# Manual installation for CentOS/RHEL/Fedora:
sudo yum install libX11-devel libXext-devel zlib-devel gcc make
# or for newer versions:
sudo dnf install libX11-devel libXext-devel zlib-devel gcc make
```

### Building

```bash
# Clone the repository
git clone https://github.com/Kizuna42/cub3D.git
cd cub3D

# Build (works on both macOS and Linux)
make

# Clean build files
make clean

# Full clean (removes executable)
make fclean

# Rebuild everything
make re
```

### Running

```bash
# Run the game
./cub3D assets/maps/test.cub

# Controls:
# W/S     - Move forward/backward
# A/D     - Move left/right
# ←/→     - Rotate left/right
# ESC     - Exit
```

### Troubleshooting

#### Linux Build Issues

If you encounter build errors on Linux:

1. **Missing dependencies:** Run `./check_linux_deps.sh` to check required packages
2. **minilibx test build fails:** This is normal - the main library will still build correctly
3. **Permission errors:** Ensure you have write permissions in the project directory

#### Common Issues

- **Black screen:** Check that texture files exist and are readable
- **Segmentation fault:** Ensure the map file is valid and properly formatted
- **Compilation errors:** Verify all dependencies are installed and `norminette` compliant
