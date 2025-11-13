/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2025/11/13 18:35:40 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_token		*token;
	t_ast		*node;
	t_parser	p;

	while (1)
	{
        (void) argc;
        (void) argv;
		init_program(&token, &node, &p);
		p.result = readline("minishell$ ");
		empty_line(&p);
		if (p.err_flag == 1)
			continue ;
		add_history(p.result);
		token = tokenizer(p.result, token);
		invalid_token(token, p.result);
		if (!p.result)
			continue ;
		node = parsing(node, token, &p);
		p.exit_flag = readline_exit(node, token, p.result);
		if (p.exit_flag == 1)
			exit (EXIT_SUCCESS);
		if (node)
			ft_ast_visualize(node);
        t_shell envp_ls;
        set_envp(envp, &envp_ls);
        t_envp *ptr = envp_ls.head;
        while (ptr)
        {
            ft_printf("%s\n", ptr->key);
            ptr = ptr->next;
        }   
		main_free(node, token, p.result);
	}
	rl_clear_history();
	return (0);
}
