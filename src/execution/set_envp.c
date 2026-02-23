/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2026/02/24 01:02:40 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*envp_value(char *k, char *v, t_shell *envp)
{
	t_envp	*ptr;

	ptr = envp->head;
	while (ptr)
	{
		if (key_equals(ptr->key, k))
		{
			if (v)
			{
				free(ptr->value);
				ptr->value = v;
			}
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_shell	*init_shell(t_shell *shell)
{
	shell = NULL;
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	(shell)->head = NULL;
	(shell)->size = 0;
	return (shell);
}

void	set_key_value(int *i, t_envp **node, char **envp)
{
	char	*delim;

	delim = ft_strchr(envp[*i], '=');
	if (!delim)
	{
		(*node)->key = ft_strdup(envp[*i]);
		(*node)->value = ft_strdup("");
	}
	else
	{
		(*node)->key = ft_substr(envp[*i], 0, delim - envp[*i]);
		(*node)->value = ft_substr(envp[*i],
				delim - envp[*i] + 1, ft_strlen(delim + 1));
	}
}

t_envp	*create_envp_node(t_envp *node, t_globe *p)
{
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	return (node);
}

void	set_envp_array(char **envp, t_shell **shell, t_globe *p)
{
	int		i;
	t_envp	*node;
	t_envp	*prev;

	*shell = init_shell(*shell);
	if (*shell == NULL)
		return ;
	i = -1;
	prev = NULL;
	while (envp[++i])
	{
		node = create_envp_node(node, p);
		if (!node)
			return ;
		if (i == 0)
			(*shell)->head = node;
		if (prev)
			prev->next = node;
		set_key_value(&i, &node, envp);
		node->next = NULL;
		prev = node;
	}
	(*shell)->size = i;
	p->envp_ls = *shell;
}
