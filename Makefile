# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 18:00:38 by jhor              #+#    #+#              #
#    Updated: 2025/09/08 13:48:20 by jhor             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra
LDFLAGS = -lreadline
NAME = minishell
RM = rm -f

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC = src/readline.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) -I. -ILibft $(OBJ) $(LIBFT) $(LDFLAGS) -o $@

all: $(NAME)

%.o : %.c
		  @$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
		@$(RM) $(OBJ)
		make clean -C $(LIBFT_DIR)

fclean:	clean
		@$(RM) $(NAME)
		make fclean -C $(LIBFT_DIR)

re: fclean $(NAME)

.PHONY: all clean fclean re
