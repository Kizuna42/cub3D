# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#              #
#    Updated: 2025/06/21 19:10:28 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I lib/libft
# For debugging, you can use: CFLAGS += -g

# --- Source Files ---
CORE_SRCS_DIR = src/
# TODO: Add your source files here as they are created
# Example: CORE_SRCS = main.c parser.c ...
CORE_SRCS = main.c parser/parser.c
SRCS_LIST = $(addprefix $(CORE_SRCS_DIR), $(CORE_SRCS))

# --- Libft ---
LIBFT_DIR = lib/libft/
LIBFT = $(LIBFT_DIR)libft.a

# --- OS Detection and Platform Specifics ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# macOS
	PLATFORM_DIR = platform/macos/
	MLX_DIR = lib/minilibx_opengl_20191021/
	# MLX can also be `lib/minilibx_mms_20200219/` for Metal version
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I$(PLATFORM_DIR) -I$(MLX_DIR)
else
	# Linux (assuming anything else is Linux)
	PLATFORM_DIR = platform/linux/
	MLX_DIR = lib/minilibx-linux/
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	CFLAGS += -I$(PLATFORM_DIR) -I$(MLX_DIR)
endif

PLATFORM_SRCS_LIST = $(wildcard $(PLATFORM_DIR)*.c)
SRCS = $(SRCS_LIST) $(PLATFORM_SRCS_LIST)
OBJS = $(SRCS:.c=.o)

# --- Build Rules ---
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 