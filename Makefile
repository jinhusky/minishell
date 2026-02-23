#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 18:00:38 by jhor              #+#    #+#              #
#    Updated: 2026/01/20 09:52:37 by kationg          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3# -fsanitize=address,leak,undefined
LDFLAGS = -lreadline
NAME = minishell
RM = rm -f

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC = src/main.c src/ast/tokenization/create_node.c \
src/ast/tokenization/append_node.c src/ast/tokenization/append_word_node.c \
src/ast/tokenization/tokenizer.c src/ast/tokenization/generation.c \
src/ast/helper/error_syntax.c src/ast/tokenization/helper_f.c \
src/ast/parse_pipe.c ast_visualizer/AST.c src/ast/helper_ast.c \
src/ast/helper/utils.c  src/ast/helper/utils2.c src/ast/parse_word.c \
src/ast/parse_redir.c src/ast/parse_argument.c src/ast/parse_component.c \
src/ast/parse_simple_command.c \
src/ast/parsing.c \
src/heredoc/heredoc_active.c src/heredoc/heredoc_expand.c \
src/heredoc/heredoc_engine.c src/heredoc/heredoc_child.c\
src/heredoc/heredoc_read_content.c \
src/expansion/expand_start.c \
src/expansion/instructor.c src/expansion/instructor_utils.c\
src/expansion/remove_quotes.c src/expansion/cmd_argv.c \
src/expansion/copy_split.c src/expansion/copy_split_utils.c\
src/expansion/expand_check.c src/expansion/expand_check_utils.c \
src/expansion/expand_split.c src/expansion/expand_split_helper.c \
src/expansion/assign_mark.c \
src/expansion/token_double.c src/expansion/token_single.c \
src/expansion/extract_expand.c src/expansion/copy_builder.c \
src/execution/set_envp.c src/execution/set_envp_utils.c\
src/execution/redirection.c src/execution/redirection_utils.c \
src/execution/exec_builtin.c src/execution/ext_cmd.c \
src/execution/single_cmd.c src/execution/signal.c \
src/execution/start_execute.c src/execution/execute_pipeline.c \
src/execution/child_execute_cmd.c src/execution/err_msg_handler.c \
src/built_in/ft_echo.c src/built_in/ft_cd.c src/built_in/ft_pwd.c \
src/built_in/ft_unset.c src/built_in/ft_env.c src/built_in/ft_exit.c \
src/built_in/ft_exit_utils.c src/built_in/ft_export.c src/built_in/ft_export_utils.c \
src/built_in/ft_export_utils2.c \

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
