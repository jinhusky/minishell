/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:25:52 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:46:58 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

typedef struct s_envp t_envp;
typedef struct s_shell t_shell;

typedef enum e_expd_e
{
	SRC_LITERAL, //!quotes that input by user, meaning retains
	SRC_EXPAND, //!quotes expanded by env value, meaningless
}	t_expd_e;

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

void		expansion_engine(t_ast *root, t_globe *p);
void		set_envp(char **envp, t_shell *env);
void		free_envp(t_envp *ptr);
void		free_copies(t_expand **copies);
void		simple_command_instructor(t_ast *cmd, t_splt_ary *sp, t_globe *p);
t_expand	*init_origin(t_expand *origin);
char		**token_quote_removal(char **tkns, t_expand **cps, t_globe *p);
char		**populate_argv(int *argc, char **argv, char **tokens, t_globe *p);
void		init_expd_quotes(size_t *si, size_t *di, char *quote);
void		expd_strip_quotes(char *s, t_expd_e *mark, t_globe *p);
char		**token_quote_removal(char **tkns, t_expand **cps, t_globe *p);
void		free_argv(char **argv);
char		**populate_argv(int *argc, char **argv, char **tokens, t_globe *p);
char		*substring_split(char *result, int start, int end, t_globe *p);
t_expand	*node_copy_builder(char *result, int i, int start, t_globe *p);
t_expand	*token_mark_copy(t_globe *p, char *result, size_t start, size_t len);
t_expand	**append_expand_token(t_expand **tkns, int *count, t_expand *new, t_globe *p);
t_expand	**copy_array_split(char *result, t_splt_ary *sp, t_expand **cpy, t_globe *p);
char		*token_expandable_check(char *lxm, char *result, t_globe *p);
char		*stage_expand_check(t_ast *child, t_globe *p);
char		**token_append(char **arr, char *sub, int *count, t_globe *p);
char		**check_expand_space(char *result, t_splt_ary *sp, t_globe *p);
void		append_with_mark(char *value, t_expand *origin, int mark);
void		mark_char_literal(char *value, t_globe *p);
void		mark_char_expand(char *value, t_globe *p);
char		*token_double_only(char *lxm, size_t *i, t_globe *p);
char		*token_single_only(char *lxm, size_t *i, t_globe *p);
char		*extract_token_expand(char *lxm, size_t *i, t_globe *p);
char		*ft_expand(char *lxm, size_t start, size_t end, t_globe *p);
void		init_split(t_splt_ary *split);
void		quote_indicator(char *result, t_splt_ary *sp, t_globe *p);
char		*char_join_str_mark(char *lxm, char *result, size_t *i, t_globe *p);

#endif