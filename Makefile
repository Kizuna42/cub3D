# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#              #
#    Updated: 2025/06/21 23:44:35 by kizuna           ###   ########.fr        #
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

# Core source files (platform independent)
CORE_SRCS = main.c \
			parser/parse_file.c \
			parser/parse_map.c \
			parser/parse_textures.c \
			parser/parse_colors.c \
			parser/validate_map.c \
			game/init.c \
			game/cleanup.c \
			render/raycasting.c \
			render/draw.c \
			utils/error.c \
			utils/math.c \
			utils/libft_utils.c

# Add src directory prefix to core sources
SRCS = $(addprefix $(SRC_DIR)/, $(CORE_SRCS))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# OS Detection
UNAME_S := $(shell uname -s)

# Platform-specific settings
ifeq ($(UNAME_S), Darwin)
	# macOS
	PLATFORM_DIR = platform/macos
	MLX_DIR = $(LIB_DIR)/minilibx_opengl_20191021
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	PLATFORM_INCLUDES = -I$(PLATFORM_DIR) -I$(MLX_DIR)
else
	# Linux (assuming anything else is Linux)
	PLATFORM_DIR = platform/linux
	MLX_DIR = $(LIB_DIR)/minilibx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	PLATFORM_INCLUDES = -I$(PLATFORM_DIR) -I$(MLX_DIR)
endif

# Platform-specific source files
PLATFORM_SRCS = $(wildcard $(PLATFORM_DIR)/*.c)
PLATFORM_OBJS = $(PLATFORM_SRCS:$(PLATFORM_DIR)/%.c=$(OBJ_DIR)/platform_%.o)

# All object files
ALL_OBJS = $(OBJS) $(PLATFORM_OBJS)

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

$(NAME): $(LIBFT) $(MLX_DIR) $(ALL_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(ALL_OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Compile core source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(PLATFORM_INCLUDES) -c $< -o $@

# Compile platform-specific source files
$(OBJ_DIR)/platform_%.o: $(PLATFORM_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling platform-specific $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(PLATFORM_INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft built successfully!$(RESET)"

# Build minilibx (if needed)
$(MLX_DIR):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ minilibx built successfully!$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
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

# Debug info
debug:
	@echo "$(BLUE)=== Build Configuration ===$(RESET)"
	@echo "OS: $(UNAME_S)"
	@echo "Platform dir: $(PLATFORM_DIR)"
	@echo "MLX dir: $(MLX_DIR)"
	@echo "MLX flags: $(MLX_FLAGS)"
	@echo "Core sources: $(CORE_SRCS)"
	@echo "Platform sources: $(PLATFORM_SRCS)" 