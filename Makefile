# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#              #
#    Updated: 2025/06/22 01:53:21 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./lib/libft

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
LIB_DIR = lib
LIBFT_DIR = $(LIB_DIR)/libft

# OS Detection
UNAME_S := $(shell uname -s)

# Core source files
CORE_SRCS = main.c \
			parser/parse_file.c \
			parser/parse_file_utils.c \
			parser/parser_utils.c \
			parser/parse_map.c \
			parser/parse_map_utils.c \
			parser/parse_textures.c \
			parser/parse_colors.c \
			parser/validate_map.c \
			game/init.c \
			game/init_utils.c \
			game/game_loop.c \
			game/movement.c \
			game/cleanup.c \
			render/raycasting.c \
			render/draw.c \
			render/draw_utils.c \
			render/texture.c \
			render/texture_utils.c \
			utils/error.c \
			utils/math.c \
			utils/libft_utils.c

# Platform-specific source files
ifeq ($(UNAME_S), Darwin)
	PLATFORM_SRCS = platform/macos/platform_hooks.c platform/macos/platform_close.c
else
	PLATFORM_SRCS = platform/linux/platform_hooks.c platform/linux/platform_close.c
endif

# Add src directory prefix to core sources
SRCS = $(addprefix $(SRC_DIR)/, $(CORE_SRCS)) $(PLATFORM_SRCS)
OBJS = $(addprefix $(OBJ_DIR)/, $(CORE_SRCS:.c=.o)) $(PLATFORM_SRCS:%.c=$(OBJ_DIR)/%.o)

# Platform-specific settings
ifeq ($(UNAME_S), Darwin)
	# macOS
	MLX_DIR = $(LIB_DIR)/minilibx_opengl_20191021
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_INCLUDES = -I$(MLX_DIR)
else
	# Linux (assuming anything else is Linux)
	MLX_DIR = $(LIB_DIR)/minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	MLX_INCLUDES = -I$(MLX_DIR)
endif

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Compile core source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) -c $< -o $@

# Compile platform-specific files
$(OBJ_DIR)/platform/%.o: platform/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft built successfully!$(RESET)"

# Build minilibx
$(MLX_LIB):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ minilibx built successfully!$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable and libraries...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

# Rebuild everything
re: fclean all

# Bonus rule (for future bonus features)
bonus: $(NAME)

# Non-file targets
.PHONY: all clean fclean re bonus 