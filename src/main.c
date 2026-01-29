/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2026/01/29 22:28:11 by welow            ###   ########.fr       */
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
	p.exit_code[0] = 0;
	p.envp_ls = (t_shell *)malloc(sizeof(t_shell));
	if (!p.envp_ls)
		return (1);
	p.envp_ls->head = NULL;
	p.envp_ls->size = 0;
	while (1)
	{
		init_program(&p.token, &p.node, &p);
		set_envp(envp, p.envp_ls);
		p.ptr = p.envp_ls->head;
		//---Jerry---//
		if (p.inside_heredoc == 0)
		{
			signal(SIGINT, signal_handler);
			signal(SIGQUIT, SIG_IGN);
		}
		//---Jerry---//
		p.result = readline("minishell$ ");
		//---Jerry---//
		signal_get_code(signum, &p);
		//---Jerry---//
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
			//ft_ast_visualize(p.node);
			ast_loop(p.node, &p);
			if (p.malloc_flag == 1 || p.err_flag == 1)
			{
				main_free(p.node, p.token, p.result, &p);
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
				main_free(p.node, p.token, p.result, &p);
				continue ;
			}
			//ft_ast_visualize(p.node);
		}
		main_free(p.node, p.token, p.result, &p);
	}
	rl_clear_history();
	return (0);
}
