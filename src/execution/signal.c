/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:20:45 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 17:16:30 by jhor             ###   ########.fr       */
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
	g_signum = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_signal_handler(int signal)
{
	g_signum = signal;
	if (g_signum == SIGINT)
	{
		write(1, "\n", 1);
		exit (128 + SIGINT);
	}
	else if (g_signum == SIGQUIT)
		return ;
}

void	set_exit_code(int status, t_globe *p)
{
	if (WIFEXITED(status))
		p->exit_code[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signum = WTERMSIG(status);
		if (g_signum == SIGQUIT)
			ft_printf("Quit (core dumped)\n");
		else if (g_signum == SIGINT)
			ft_printf("\n");
		p->exit_code[0] = 128 + g_signum;
		g_signum = 0;
	}
}

void	set_hd_exit_code(int status, t_globe *p)
{
	if (WIFEXITED(status))
		p->exit_code[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signum = WTERMSIG(status);
		if (g_signum == SIGINT)
		{
			p->exit_code[0] = 128 + g_signum;
			p->err_flag = 1;
		}
		g_signum = 0;
	}
}
