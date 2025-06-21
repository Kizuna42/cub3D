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
