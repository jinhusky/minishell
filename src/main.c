/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:56:57 by jhor              #+#    #+#             */
/*   Updated: 2025/10/21 15:56:57 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    main_free(t_ast *node, t_token *token, char *result)
{
    if (node)
		free_treenode(node);		
    if (token)
        free_tokens(token);
    if (result)
	    free(result);
}

int main()
{
	char		*result;
	t_token		*token;
	t_ast		*node;
	t_parser	p;
	
	while (1)
	{
        init_program(&token, &result, &node, &p);
		result = readline("minishell$ ");
        empty_line(&p, result);
	    if (p.err_flag == 1)
            continue;
        add_history(result);
		token = tokenizer(result, token);
        invalid_token(token, result);
        if (!result)
            continue;
		node = parsing(node, token, &p);
        p.exit_flag = readline_exit(node, token, result);
		if (p.exit_flag == 1)
		    exit (EXIT_SUCCESS);
		if (node)
			ft_ast_visualize(node);
        main_free(node, token, result);
	}
	rl_clear_history();
	return (0);
}
