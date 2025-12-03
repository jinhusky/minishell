/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:06:44 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:00:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_envp(t_envp *ptr)
{
	t_envp *tmp;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	main_free(t_ast *node, t_token *token, char *result, t_globe *p)
{
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (p->ptr)
		free_envp(p->ptr);
	if (result)
		free(result);
}

void	ast_exit(t_token *token, t_ast *node, t_globe *p)
{
	ft_putstr_fd("malloc failed\n", 2);
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (p->result)
		free(p->result);
	return ;
}

void	token_exit(t_token *token, char *result, t_globe *p)
{
	ft_putstr_fd("*tokens* malloc failed\n", 2);
	if (token)
		free_tokens(token);
	if (result)
		free(result);
	p->malloc_flag = 1;
	return ;
}
