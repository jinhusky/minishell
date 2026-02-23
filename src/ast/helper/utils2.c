/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:06:44 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 22:59:15 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_envp(t_envp *ptr)
{
	t_envp	*tmp;

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

void	loop_free(t_ast *node, t_token *token, char *result, t_globe *p)
{
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (p && p->envp_array)
	{
		free_strv(p->envp_array);
		p->envp_array = NULL;
	}
	if (p)
		p->ptr = NULL;
	if (result)
		free(result);
}

void	main_free(t_ast *node, t_token *token, char *result, t_globe *p)
{
	if (node)
		free_treenode(node);
	if (token)
		free_tokens(token);
	if (p && p->envp_ls)
	{
		if (p->envp_ls->head)
		{
			free_envp(p->envp_ls->head);
			p->envp_ls->head = NULL;
			p->envp_ls->size = 0;
		}
		free(p->envp_ls);
		p->envp_ls = NULL;
	}
	if (p && p->envp_array)
	{
		free_strv(p->envp_array);
		p->envp_array = NULL;
	}
	if (p)
		p->ptr = NULL;
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
