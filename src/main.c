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

int	main(int argc, char *argv[], char **envp)
{
	t_parser	p;

	(void) argc;
	(void) argv;
	while (1)
	{
		init_program(&p.token, &p.node, &p);
		set_envp(envp, &p.envp_ls);
		p.ptr = p.envp_ls.head;
		// t_envp *tmp = p.ptr;
		// while (tmp)
		// {
		// 	printf("%s=", tmp->key);
		// 	printf("%s\n", tmp->value);
		// 	tmp = tmp->next;
		// }
		p.result = readline("minishell$ ");
		empty_line(&p);
		if (p.err_flag == 1)
			continue ;
		add_history(p.result);
		p.token = tokenizer(p.result, p.token);
		invalid_token(p.token, p.result);
		if (!p.result)
			continue ;
		p.node = parsing(p.node, p.token, &p);
		p.exit_flag = readline_exit(p.node, p.token, p.result, p.ptr);
		if (p.exit_flag == 1)
			exit (EXIT_SUCCESS);
		if (p.node)
		{
			ft_ast_visualize(p.node);
			ast_loop(p.node, &p);
			expansion_engine(p.node, &p);
		}
		main_free(p.node, p.token, p.result, p.ptr);
	}
	rl_clear_history();
	return (0);
}
