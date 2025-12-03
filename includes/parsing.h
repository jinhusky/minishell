/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:10:32 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:26:26 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef enum e_node
{
	AST_PIPELINE,
	AST_COMMAND,
	AST_ARGUMENT,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_APPEND,
	AST_HEREDOC,
	AST_WORD,
}	t_node;

typedef struct s_token
{
	t_token_type	token;
	char			*lexeme;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_node			type;
	struct s_ast	**children;
	int				childcount;
	t_token			*token_ref;
	int				argc;
	char			**argv;
	int				heredoc_fd[2];
}	t_ast;

typedef struct s_globe t_globe;

void		quote_check(char *result, int *i, char quote);
t_token		*init_node(t_token *token);
void		free_append_word(t_token *head, t_token *temp);
t_token		*create_node(t_token *head, char *start, size_t end);
t_token		*append_node(t_token *head, char *start, size_t end);
t_token		*append_word_node(t_token *hd, char *srt, size_t n_srt, size_t end);
t_token		*token_word(t_token *tokens, t_globe *p, int start, int i);
t_token		*token_pipe(t_token *tokens, char *result, t_globe *p);
t_token		*token_single_operator(t_token *tokens, char *result, t_globe *p);
t_token		*token_double_operator(t_token *tokens, char *result, t_globe *p);
t_token		*tokenizer(t_token *tokens, t_globe *p);
void		ast_exit(t_token *token, t_ast *node, t_globe *p);
void		token_exit(t_token *token, char *result, t_globe *p);
void		free_tokens(t_token *tokens);
void		invalid_token(t_token *token, char *result, t_globe *p);
void		error_redir(t_token *token);
void		error_pipe(t_token *token);
void		error_quotes(char quote, t_globe *p);
t_ast		*init_ast(t_ast *node, t_globe *p, t_token *token);
t_globe	*get_token(t_globe *p);
t_token		*token_peek(t_globe *p);
t_ast		*create_treenode(t_ast *treenode, t_globe *p);
void		free_treenode(t_ast *root);
void		attach_treenode(t_ast *branch, t_ast *leaf, t_globe *p);
void		parse_pipeline(t_ast *node, t_globe *p);
void		parse_simple_command(t_ast *branch, t_globe *p);
void		parse_maybe_redirs(t_ast *prt, t_globe *p);
t_ast		*parse_redirection(t_ast *chd_ptr, t_globe *p, t_token *cur_redir);
bool		valid_redirection(t_globe *p);
bool		all_redirs(t_ast *branch);
void		parse_components(t_ast *prt, t_ast *child, t_globe *p);
bool		valid_component(t_globe *p);
t_ast		*parse_argument(t_ast *chd_ptr, t_globe *p);
void		parse_word(t_ast *branch, t_globe *p);
void		init_quotes(char *lexeme, char **src, char **dst);
void		strip_quotes(char *lexeme, t_globe *p);
t_ast		*parsing(t_ast *node, t_token *token, t_globe *p);
void		ft_ast_visualize(t_ast *root);
void		ast_loop(t_ast *root, t_globe *p);

#endif