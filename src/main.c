/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2026/02/09 22:34:31 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

__sig_atomic_t signum;

void	print_SHLVL(char *str, t_shell **env)
{
	t_envp	*ptr;

	ptr = (*env)->head;
	while (ptr)
	{
		if (key_equals(ptr->key, str))
		{
			ft_printf("SHLVL IN MINISHELL:%s\n", ptr->value);
			return ;
		}
		ptr = ptr->next;
	}
}

void	set_SHLVL(char *str, t_shell **env)
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
			ft_printf("what is key:%s\n", ptr->key);
			ft_printf("SHLVL IN MINISHELL:%s\n", ptr->value);
			return ;
		}
		ptr = ptr->next;
	}
}

//!maybe refactor the set_envp call
int	main(int argc, char *argv[], char **envp)
{
	t_globe	p;

	(void) argc;
	(void) argv;
	ft_bzero(&p, sizeof(t_globe));
	set_envp_array(envp, &p.envp_ls, &p);
	set_SHLVL("SHLVL", &p.envp_ls);
	print_SHLVL("SHLVL", &p.envp_ls);
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
		for (t_envp *ptr = p.envp_ls->head; ptr; ptr = ptr->next)
		{
			ft_printf("%s=", ptr->key);
			ft_printf("%s\n", ptr->value);
		}
	}
	rl_clear_history();
	return (0);
}
