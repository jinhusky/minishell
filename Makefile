# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
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
