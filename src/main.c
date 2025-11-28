/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2025/11/14 13:07:18 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//!p->exit_code logic is not correct, how to make it so the next prompt has the exit code and not have leaks (could use stack memory)
int	main(int argc, char *argv[], char **envp)
{
	t_parser	p;

	(void) argc;
	(void) argv;
	p.exit_code[0] = 0;
	while (1)
	{
		init_program(&p.token, &p.node, &p);
		set_envp(envp, &p.envp_ls);
		p.ptr = p.envp_ls.head;
		p.result = readline("minishell$ ");
		empty_line(&p);
		if (p.err_flag == 1)
			continue ;
		add_history(p.result);
		p.token = tokenizer(p.token, &p);
		invalid_token(p.token, p.result, &p);
		if (p.malloc_flag == 1)
			continue ;
		p.node = parsing(p.node, p.token, &p);
		p.exit_flag = readline_exit(p.node, p.token, p.result, p.ptr);
		if (p.exit_flag == 1)
			exit (EXIT_SUCCESS);
		if (p.node)
		{
			ft_ast_visualize(p.node);
			ast_loop(p.node, &p);
			if (p.err_flag == 1)
			{
				main_free(p.node, p.token, p.result, &p);
				continue ;
			}
			expansion_engine(p.node, &p);
			if (p.err_flag == 1 || p.malloc_flag == 1)
			{
				main_free(p.node, p.token, p.result, &p);
				continue ;
			}
			ft_ast_visualize(p.node);
		}
		main_free(p.node, p.token, p.result, &p);
	}
	rl_clear_history();
	return (0);
}
