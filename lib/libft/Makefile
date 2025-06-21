# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 16:01:19 by kizuna            #+#    #+#              #
#    Updated: 2025/06/21 21:38:49 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

SRCS_DIR = src/
FT_IS_DIR = $(SRCS_DIR)ft_is/
FT_TO_DIR = $(SRCS_DIR)ft_to/
FT_MEM_DIR = $(SRCS_DIR)ft_mem/
FT_PUT_DIR = $(SRCS_DIR)ft_put/
FT_STR_DIR = $(SRCS_DIR)ft_str/
GNL_DIR = $(SRCS_DIR)gnl/
FT_LST_DIR = $(SRCS_DIR)ft_lst/

SRCS =	$(addprefix $(FT_IS_DIR), ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c) \
		$(addprefix $(FT_MEM_DIR), ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c) \
		$(addprefix $(FT_PUT_DIR), ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c) \
		$(addprefix $(FT_STR_DIR), ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c) \
		$(addprefix $(FT_TO_DIR), ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c) \
		$(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c get_next_line_utils2.c) \
		$(addprefix $(FT_LST_DIR), ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c)


BONUS = $(FT_LST_DIR)ft_lstnew_bonus.c \
		$(FT_LST_DIR)ft_lstadd_front_bonus.c \
		$(FT_LST_DIR)ft_lstsize_bonus.c \
		$(FT_LST_DIR)ft_lstlast_bonus.c \
		$(FT_LST_DIR)ft_lstadd_back_bonus.c \
		$(FT_LST_DIR)ft_lstdelone_bonus.c \
		$(FT_LST_DIR)ft_lstclear_bonus.c \
		$(FT_LST_DIR)ft_lstiter_bonus.c \
		$(FT_LST_DIR)ft_lstmap_bonus.c

OBJS_DIR = obj/
OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) $(dir $(OBJS))

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
