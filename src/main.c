/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2026/02/05 19:59:15 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

__sig_atomic_t signum;

//!maybe refactor the set_envp call
int	main(int argc, char *argv[], char **envp)
{
	t_globe	p;

	(void) argc;
	(void) argv;
	ft_bzero(&p, sizeof(t_globe));
	set_envp_array(envp, &p.envp_ls, &p);
	p.exit_code[0] = 0;
	while (1)
	{
		init_program(&p.token, &p.node, &p);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		p.result = readline("minishell$ ");
		signal_get_code(signum, &p);
		empty_line(&p);
		if (p.err_flag == 1)
			continue ;
		add_history(p.result);
		p.token = tokenizer(p.token, &p);
		invalid_token(p.token, p.result, &p);
		if (p.malloc_flag == 1)
			continue ;
		p.node = parsing(p.node, p.token, &p);
		if (p.malloc_flag == 1 || p.err_flag == 1)
		{
			ft_printf("i am in here\n");
			loop_free(p.node, p.token, p.result, &p);
			continue ;
		}
		//p.exit_flag = readline_exit(p.node, p.token, p.result, p.ptr);
		if (p.exit_flag == 1)
			exit (EXIT_SUCCESS);
		if (p.node)
		{
			//ft_ast_visualize(p.node);
			ast_loop(p.node, &p);
			if (p.malloc_flag == 1 || p.err_flag == 1)
			{
				ft_printf("i am in here\n");
				loop_free(p.node, p.token, p.result, &p);
				continue ;
			}
			expansion_engine(p.node, &p);
            /*
			t_ast *ptr;
            for (int i = 0; i < p.node->childcount; i++)
			{
				ptr = p.node->children[i];
				for (int j = 0; ptr->argv[j]; j++)
				{
					printf("%s ", ptr->argv[j]);
				}
				printf("\n");
			}
            */
			execute(p.node, &p);
			if (p.err_flag == 1 || p.malloc_flag == 1)
			{
				loop_free(p.node, p.token, p.result, &p);
				continue ;
			}
			//ft_ast_visualize(p.node);
		}
		//ft_printf("I am here to loop again\n");
		loop_free(p.node, p.token, p.result, &p);
	}
	rl_clear_history();
	return (0);
}
