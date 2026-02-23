/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:08:11 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:08:54 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parent_clean_up(int prev_read, t_ast *root, pid_t *pids, t_globe *p)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (prev_read != STDIN_FILENO)
		close(prev_read);
	while (i < root->childcount)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	set_exit_code(status, p);
}

void	child_process(int *i, t_globe *p, int readpipe, int writepipe)
{
	if (*i < p->node->childcount - 1)
	{
		close(readpipe);
		child_execute_cmd(p->node->children[*i], p, p->prev_read, writepipe);
	}
	else
		child_execute_cmd(p->node->children[*i], p,
			p->prev_read, STDOUT_FILENO);
}

bool	fork_child(pid_t *pid, t_globe *p)
{
	*pid = fork();
	if (*pid == -1)
		return (false);
	return (true);
}

void	assign_pipe(int *i, t_globe *p, int readpipe, int writepipe)
{
	if (p->prev_read != STDIN_FILENO)
		close(p->prev_read);
	if (*i < p->node->childcount - 1)
	{
		close(writepipe);
		p->prev_read = readpipe;
	}
}

int	execute_pipeline(t_ast *root, t_globe *p)
{
	int		i;
	int		pipefd[2];
	pid_t	pids[1024];
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	while (++i < root->childcount)
	{
		if (i < root->childcount - 1 && pipe(pipefd) == -1)
			return (perror("pipe"), p->exit_code[0] = 1, 1);
		if (!fork_child(&pid, p))
			return (perror("fork"), p->exit_code[0] = 1, 1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			child_process(&i, p, pipefd[0], pipefd[1]);
		}
		pids[i] = pid;
		assign_pipe(&i, p, pipefd[0], pipefd[1]);
	}
	parent_clean_up(p->prev_read, root, pids, p);
	return (p->exit_code[0]);
}
