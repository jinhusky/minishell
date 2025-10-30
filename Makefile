# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 18:00:38 by jhor              #+#    #+#              #
#    Updated: 2025/10/23 20:57:59 by jhor             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra
LDFLAGS = -lreadline
NAME = minishell
RM = rm -f

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC = src/main.c src/create_node.c src/append_node.c src/append_word_node.c \
src/ast/tokenization/tokenizer.c src/ast/tokenization/generation.c \
src/error_syntax.c src/ast/tokenization/helper_f.c src/ast/parse_pipe.c \
ast_visualizer/AST.c src/ast/helper_ast.c src/utils.c  src/utils2.c\
src/ast/parse_word.c src/ast/parse_redir.c src/ast/parse_argument.c \
src/ast/parse_component.c src/ast/parse_simple_command.c src/ast/parsing.c\

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
#    By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 13:57:14 by kationg           #+#    #+#              #
#    Updated: 2025/09/20 18:50:44 by kationg          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = built_in/ft_echo.c built_in/ft_pwd.c built_in/get_envp.c

OBJECT_SRCS = $(SRCS:.c=.o)

FLAGS = 

INCLUDES = -Iincludes -ILibft

$(NAME): $(OBJECT_SRCS)
	make -C Libft all
	cc $(FLAGS) $(INCLUDES) $(OBJECT_SRCS) Libft/libft.a -o $@

%.o : %.c
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

clean:
	make -C Libft clean
	rm -f $(OBJECT_SRCS)

fclean: clean
	make -C Libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
