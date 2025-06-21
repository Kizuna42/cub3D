# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#              #
#    Updated: 2025/06/21 21:56:42 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables ---
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Directories ---
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = lib/libft
MLX_DIR = lib/minilibx_opengl_20191021

# --- Includes ---
INCLUDES = -I include -I $(LIBFT_DIR) -I $(MLX_DIR)

# --- Sources ---
SRC_FILES = main.c \
            parser/parser.c \
            parser/parser_utils.c \
            parser/parser_map.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# --- Objects ---
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- Libraries ---
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LDFLAGS = -L $(LIBFT_DIR) -L $(MLX_DIR)
LDLIBS = -lft -lmlx -framework OpenGL -framework AppKit

# --- OS Specifics ---
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	# Linux specific settings if any
endif
ifeq ($(UNAME_S),Darwin)
	PLATFORM_HOOKS_SRC = platform/macos/platform_hooks.c
endif
PLATFORM_HOOKS_OBJ = $(PLATFORM_HOOKS_SRC:.c=.o)
OBJS += $(PLATFORM_HOOKS_OBJ)


# --- Rules ---
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PLATFORM_HOOKS_OBJ): $(PLATFORM_HOOKS_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR) $(PLATFORM_HOOKS_OBJ)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR) $(PLATFORM_HOOKS_OBJ)
	@rm -f $(NAME)

re: fclean all 