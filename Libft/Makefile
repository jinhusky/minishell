# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 16:12:35 by jhor              #+#    #+#              #
#    Updated: 2025/07/23 18:55:40 by jhor             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
RM = rm -f

SRC1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_atol.c 

SRC2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstiter.c ft_strjoinv.c ft_print_char.c ft_print_digit.c ft_print_str.c \
ft_print_lower_hexa.c ft_print_pointer.c ft_print_upper_hexa.c ft_printf.c \
get_next_line.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

$(NAME): $(OBJ1) $(OBJ2)
	@ar -rcs $(NAME) $(OBJ1) $(OBJ2)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ1) $(OBJ2)

fclean: clean
	@$(RM) $(NAME)

# need to add bonus?
re: fclean $(NAME)

.PHONY: all clean fclean re