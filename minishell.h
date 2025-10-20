/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:37:01 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum	e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}t_token_type;

typedef enum	e_node
{
	AST_PIPELINE,
	AST_COMMAND,
	AST_ARGUMENT,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_APPEND,
	AST_HEREDOC,
	AST_WORD,
} t_node;

typedef struct s_token
{
	t_token_type	token;
	char			*lexeme;
	struct s_token	*next;
}t_token;


typedef struct s_ast {
	t_node	type;
	struct s_ast **children;
	int	childcount;
	t_token *token_ref;
} t_ast;

typedef struct	s_parser {
	t_token	*cursor;
	t_ast	*cur_cmd;
	int		err_flag;
	char	*trim;
} t_parser;

void		quote_check(char *result, int *i, char quote);
t_token		*create_node(t_token *head, char *start, size_t end);
t_token		*append_node(t_token *head, char *start, size_t end);
t_token		*append_word_node(t_token *head, char *start, size_t n_start, size_t end);
t_token		*token_word(t_token *tokens, char *result, int start, int i);
t_token		*token_pipe(t_token *tokens, char *result);
t_token		*token_single_operator(t_token *tokens, char *result);
t_token		*token_double_operator(t_token *tokens, char *result);
void		free_tokens(t_token *tokens);
char		*trim_prompt(char *trim);
void		error_redir(t_token *token);
void		error_pipe(t_token *token);
t_ast		*init_ast(t_ast *node, t_parser *p, t_token *token);
t_parser	*get_token(t_parser *p);
t_token		*token_peek(t_parser *p);
t_ast		*create_treenode(t_ast *treenode);
void		free_treenode(t_ast *root);
void		attach_treenode(t_ast *branch, t_ast *leaf);
void		parse_pipeline(t_ast *node, t_parser *p);
void		parse_simple_command(t_ast *branch, t_parser *p);
void		parse_maybe_redirs(t_ast *prt, t_parser *p);
t_ast		*parse_redirection(t_ast *chd_ptr, t_parser *p, t_token *cur_redir);
bool		valid_redirection(t_parser *p);
bool		all_redirs(t_ast *branch);
void		parse_components(t_ast *prt, t_ast *child, t_parser *p);
bool		valid_component(t_parser *p);
t_ast		*parse_argument(t_ast *chd_ptr, t_parser *p);
void		parse_word(t_ast *branch, t_parser *p);
void		strip_quotes(char *lexeme, t_parser *p);
t_ast		*parsing(t_ast *node, t_token *token, t_parser *p);
void		ft_ast_visualize(t_ast *root);

#endif