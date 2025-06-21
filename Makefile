NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include
LIBFT_DIR = ./lib/libft
LIBFT_A = $(LIBFT_DIR)/libft.a
RM = rm -f

# --- Core Logic (Platform Independent) ---
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJS = $(SRCS:.c=.o)

# --- OS Detection and Platform Specifics ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    # macOS
	PLATFORM_DIR = platform/macos
	MLX_DIR = ./lib/minilibx_opengl_20191021
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I$(PLATFORM_DIR)
else
    # Linux
	PLATFORM_DIR = platform/linux
	MLX_DIR = ./lib/minilibx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
	CFLAGS += -I$(PLATFORM_DIR)
endif

PLATFORM_SRCS = $(wildcard $(PLATFORM_DIR)/*.c)
PLATFORM_OBJS = $(PLATFORM_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PLATFORM_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PLATFORM_OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) $(PLATFORM_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 