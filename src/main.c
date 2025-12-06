/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 20:24:31 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_token		*token;
	t_ast		*node;
	t_parser	p;
    
    (void) argc;
    (void) argv;
	t_shell shell;
	set_envp(envp, &shell);
	/*
	t_envp *ptr = shell.envp_head;
	
	while (ptr)	
	{
		ft_printf("%s",ptr->key);
		ft_printf("=");
		ft_printf("%s\n", ptr->value);	
		ptr = ptr->next;
	}
	ft_printf("%d\n", shell.size);
	*/
	while (1)
	{
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
		{
			ft_ast_visualize(node);
			ast_loop(node, &p);
			execute_pipeline(node, &shell);
		}
		main_free(node, token, p.result);
	}
	rl_clear_history();
	return (0);
}
