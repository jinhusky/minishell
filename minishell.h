/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 12:33:48 by jhor             ###   ########.fr       */
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

typedef enum e_expd_e
{
	SRC_LITERAL, //!quotes that input by user, meaning retains
	SRC_EXPAND, //!quotes expanded by env value, meaningless
}	t_expd_e;

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

typedef struct s_splt_ary
{
	int		in_sg;
	int		in_db;
	int		i;
	int		start;
	int		tcount;
}	t_splt_ary;

typedef struct s_expand
{
	t_expd_e	*mark;
	char		*s_array;
	size_t		count;
}	t_expand;

//KAI'S PART
typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct shell
{
	t_envp	*head;
}	t_shell;

typedef struct s_parser
{
	char		*result;
	t_token		*token;
	t_ast		*node;
	t_token		*cursor;
	t_ast		*cur_cmd;
	int			err_flag;
	char		*trim;
	int			exit_flag;
	int			malloc_flag;
	int			heredoc_flag;
	t_shell		envp_ls;
	t_envp		*ptr;
	char		*value;
	t_expand	*origin;
	int			exit_code[1];
	t_splt_ary	sp;
	t_expand	*new;
}	t_parser;

//READLINE//
void		init_program(t_token **tkn, t_ast **nd, t_parser *p);
void		main_free(t_ast *node, t_token *token, char *result, t_parser *p);
char		*trim_prompt(char *trim);
void		empty_line(t_parser *p);
int			readline_exit(t_ast *node, t_token *token, char *rslt, t_envp *ptr);

//PARSING//
void		quote_check(char *result, int *i, char quote);
t_token		*init_node(t_token *token);
void		free_append_word(t_token *head, t_token *temp);
t_token		*create_node(t_token *head, char *start, size_t end);
t_token		*append_node(t_token *head, char *start, size_t end);
t_token		*append_word_node(t_token *hd, char *srt, size_t n_srt, size_t end);
t_token		*token_word(t_token *tokens, t_parser *p, int start, int i);
t_token		*token_pipe(t_token *tokens, char *result, t_parser *p);
t_token		*token_single_operator(t_token *tokens, char *result, t_parser *p);
t_token		*token_double_operator(t_token *tokens, char *result, t_parser *p);
t_token		*tokenizer(t_token *tokens, t_parser *p);
void		ast_exit(t_token *token, t_ast *node, t_parser *p);
void		token_exit(t_token *token, char *result, t_parser *p);
void		free_tokens(t_token *tokens);
void		invalid_token(t_token *token, char *result, t_parser *p);
void		error_redir(t_token *token);
void		error_pipe(t_token *token);
void		error_quotes(char quote, t_parser *p);
t_ast		*init_ast(t_ast *node, t_parser *p, t_token *token);
t_parser	*get_token(t_parser *p);
t_token		*token_peek(t_parser *p);
t_ast		*create_treenode(t_ast *treenode, t_parser *p);
void		free_treenode(t_ast *root);
void		attach_treenode(t_ast *branch, t_ast *leaf, t_parser *p);
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
void		init_quotes(char *lexeme, char **src, char **dst);
void		strip_quotes(char *lexeme, t_parser *p);
t_ast		*parsing(t_ast *node, t_token *token, t_parser *p);
void		ft_ast_visualize(t_ast *root);

//HEREDOC//
void		ast_loop(t_ast *root, t_parser *p);

//EXPANSION//
void		expansion_engine(t_ast *root, t_parser *p);
void		set_envp(char **envp, t_shell *env);
void		free_envp(t_envp *ptr);
void		free_copies(t_expand **copies);
void		simple_command_instructor(t_ast *cmd, t_splt_ary *sp, t_parser *p);
t_expand	*init_origin(t_expand *origin);
char		**token_quote_removal(char **tkns, t_expand **cps, t_parser *p);
char		**populate_argv(int *argc, char **argv, char **tokens, t_parser *p);
void		init_expd_quotes(size_t *si, size_t *di, char *quote);
void		expd_strip_quotes(char *s, t_expd_e *mark, t_parser *p);
char		**token_quote_removal(char **tkns, t_expand **cps, t_parser *p);
void		free_argv(char **argv);
char		**populate_argv(int *argc, char **argv, char **tokens, t_parser *p);
char		*substring_split(char *result, int start, int end, t_parser *p);
t_expand	*node_copy_builder(char *result, int i, int start, t_parser *p);
t_expand	*token_mark_copy(t_parser *p, char *result, size_t start, size_t len);
t_expand	**append_expand_token(t_expand **tkns, int *count, t_expand *new, t_parser *p);
t_expand	**copy_array_split(char *result, t_splt_ary *sp, t_expand **cpy, t_parser *p);
char		*token_expandable_check(char *lxm, char *result, t_parser *p);
char		*stage_expand_check(t_ast *child, t_parser *p);
char		**token_append(char **arr, char *sub, int *count, t_parser *p);
char		**check_expand_space(char *result, t_splt_ary *sp, t_parser *p);
void		append_with_mark(char *value, t_expand *origin, int mark);
void		mark_char_literal(char *value, t_parser *p);
void		mark_char_expand(char *value, t_parser *p);
char		*token_double_only(char *lxm, size_t *i, t_parser *p);
char		*token_single_only(char *lxm, size_t *i, t_parser *p);
char		*extract_token_expand(char *lxm, size_t *i, t_parser *p);
char		*ft_expand(char *lxm, size_t start, size_t end, t_parser *p);
void		init_split(t_splt_ary *split);
void		quote_indicator(char *result, t_splt_ary *sp, t_parser *p);
char		*char_join_str_mark(char *lxm, char *result, size_t *i, t_parser *p);

#endif