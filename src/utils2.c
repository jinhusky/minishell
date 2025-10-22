/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:06:44 by jhor              #+#    #+#             */
/*   Updated: 2025/10/22 23:33:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_free(t_ast *node, t_token *token, char *result)
{
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (result)
		free(result);
}

void	ast_exit(t_token *token, t_ast *node, char *result)
{
	ft_putstr_fd("malloc failed\n", 2);
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (result)
		free(result);
	exit (EXIT_FAILURE);
}

void	token_exit(t_token *token, char *result)
{
	ft_putstr_fd("*tokens* malloc failed\n", 2);
	if (token)
		free_tokens(token);
	if (result)
		free(result);
	exit (EXIT_FAILURE);
}