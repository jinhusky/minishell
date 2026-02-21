/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:47:02 by welow             #+#    #+#             */
/*   Updated: 2026/02/21 23:39:22 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//!work on not mixing the heredoc signal with normal environment signal behavior
void	signal_get_code(int signa, t_globe *p)
{
	if (signa == SIGINT)
		p->exit_code[0] = 128 + signa;
	if (!p->result)
	{
		main_free(p->node, p->token, p->result, p);
		exit(p->exit_code[0]);
	}
}

void	signal_handler(int signal)
{
	signum = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_signal_handler(int signal)
{
	signum = signal;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit (128 + SIGINT);
	}
	else if (signum == SIGQUIT)
	{

	}
}

void	set_exit_code(int status, t_globe *p)
{
	if (WIFEXITED(status))
		p->exit_code[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		if (signum == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (signum == SIGINT)
			printf("\n");
		p->exit_code[0] = 128 + signum;
		signum = 0;
	}
}

void	set_hd_exit_code(int status, t_globe *p)
{
	if (WIFEXITED(status))
		p->exit_code[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		if (signum == SIGINT)
		{
			p->exit_code[0] = 128 + signum;
			p->err_flag = 1;
		}
		signum = 0;
	}
}
