/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:30:26 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:19:02 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*set_heredoc_pipe(int *hpipe, t_globe *p)
{
	if (pipe(hpipe) == -1)
	{
		p->err_flag = 1;
		ft_putendl_fd("pipe error in heredoc", 2);
		p->exit_code[0] = 2;
		return (p->exit_code);
	}
	return (hpipe);
}

pid_t	spwn_heredoc_child(pid_t kid, int rpipe, int wpipe, t_globe *p)
{
	kid = fork();
	if (kid == -1)
	{
		close(rpipe);
		close(wpipe);
		p->err_flag = 1;
		ft_putendl_fd("fork error in heredoc", 2);
		p->exit_code[0] = 2;
		return (2);
	}
	return (kid);
}

void	child_reading(t_ast *heredoc, t_globe *p)
{
	readline_prep(heredoc->children[0]->token_ref->lexeme,
		heredoc->heredoc_fd[0], heredoc->heredoc_fd[1], p);
	read_into_pipe(heredoc->children[0]->token_ref->lexeme,
		heredoc->heredoc_fd[1], p);
}

void	heredoc_engine(t_ast *heredoc, t_globe *p)
{
	pid_t	kid;
	int		status;

	status = 0;
	set_heredoc_pipe(heredoc->heredoc_fd, p);
	if (p->err_flag == 1)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	kid = spwn_heredoc_child(kid, heredoc->heredoc_fd[0],
			heredoc->heredoc_fd[1], p);
	if (p->err_flag == 1)
		return ;
	if (kid == 0)
		child_reading(heredoc, p);
	close(heredoc->heredoc_fd[1]);
	waitpid(kid, &status, 0);
	set_hd_exit_code(status, p);
}

void	find_heredoc(t_ast *child, t_globe *p)
{
	int		i;
	t_ast	*heredoc;

	i = 0;
	heredoc = NULL;
	while (i < child->childcount && child->children[i])
	{
		if (child->children[i]->type == AST_HEREDOC)
		{
			heredoc = child->children[i];
			heredoc_engine(heredoc, p);
			if (p->err_flag == 1)
				return ;
		}
		i++;
	}
}
