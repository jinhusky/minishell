/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:05:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

__sig_atomic_t	g_signum;

void	set_shlvl(char *str, t_shell **env)
{
	t_envp	*ptr;

	ptr = (*env)->head;
	while (ptr)
	{
		if (key_equals(ptr->key, str))
		{
			if (ptr->value)
				*(ptr->value) = *(ptr->value) + 1;
			else
				ptr->value = "1";
			return ;
		}
		ptr = ptr->next;
	}
}

void	set_envp_shlvl_exitcode(char **envp, t_globe *p)
{
	set_envp_array(envp, &p->envp_ls, p);
	if (p->malloc_flag == 1)
	{
		if (p->envp_ls)
			free_envp_ls(p->envp_ls);
		ft_putendl_fd("minishell: env error", 2);
		exit (1);
	}
	set_shlvl("SHLVL", &p->envp_ls);
	p->exit_code[0] = 0;
}

void	minishell_core(t_globe *p)
{
	p->token = tokenizer(p->token, p);
	if (!p->token || p->malloc_flag == 1)
	{
		if (p->result)
			free(p->result);
		if (p->token)
			free(p->token);
		return ;
	}
	p->node = parsing(p->node, p->token, p);
	if (p->malloc_flag == 1 || p->err_flag == 1)
		return ;
	if (p->node)
	{
		heredoc_ast(p->node, p);
		if (p->malloc_flag == 1 || p->err_flag == 1)
			return ;
		expansion_engine(p->node, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return ;
		execute(p->node, p);
	}
}

void	check_signal_postreadline(t_globe *p)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	p->result = readline("minishell$ ");
	signal_get_code(g_signum, p);
}

int	main(int argc, char *argv[], char **envp)
{
	t_globe	p;

	(void) argc;
	(void) argv;
	ft_bzero(&p, sizeof(t_globe));
	set_envp_shlvl_exitcode(envp, &p);
	while (1)
	{
		init_program(&p.token, &p.node, &p);
		check_signal_postreadline(&p);
		empty_line(&p);
		if (p.err_flag == 1)
			continue ;
		add_history(p.result);
		minishell_core(&p);
		if (p.malloc_flag == 1 || p.err_flag == 1)
		{
			loop_free(p.node, p.token, p.result, &p);
			continue ;
		}
		loop_free(p.node, p.token, p.result, &p);
	}
	rl_clear_history();
	return (0);
}
