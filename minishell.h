/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:29:34 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include "includes/parsing.h"
# include "includes/expansion.h"
# include "includes/execution.h"
# include "includes/builtin.h"
# include "Libft/libft.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_shell
{
	t_envp	*head;
	int		size;
}	t_shell;

typedef struct s_globe
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
	int			inside_heredoc;
	int			heredoc_q_flag;
	t_shell		*envp_ls;
	t_envp		*ptr;
	t_expand	*origin;
	int			exit_code[1];
	t_splt_ary	sp;
	char		**envp_array;
	int			prev_read;
}	t_globe;

extern __sig_atomic_t	g_signum;

void		init_program(t_token **tkn, t_ast **nd, t_globe *p);
void		main_free(t_ast *node, t_token *token, char *result, t_globe *p);
void		loop_free(t_ast *node, t_token *token, char *result, t_globe *p);
char		*trim_prompt(char *trim);
void		empty_line(t_globe *p);
int			readline_exit(t_ast *node, t_token *token, char *rslt, t_envp *ptr);

#endif
