/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2026/02/22 01:35:03 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	key_equals(const char *a, const char *b)
{
	size_t	la;
	size_t	lb;

	if (!a || !b)
		return (0);
	la = ft_strlen(a);
	lb = ft_strlen(b);
	if (la != lb)
		return (0);
	return (ft_strncmp(a, b, la) == 0);
}

void	free_envp_ls(t_shell *shell)
{
	t_envp	*ptr;
	t_envp	*tmp;

	if (!shell)
		return ;
	ptr = shell->head;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	shell->head = NULL;
	shell->size = 0;
}

char	*extract_key(char *eq_pos, char *k)
{
	char	*pinpoint;
	pinpoint = ft_strchr(k, '=');
	eq_pos = ft_substr(k, 0, ft_strlen(k) - ft_strlen(pinpoint));
	return (eq_pos);
}

char	*replace_value(char *new)
{
	char	*new_value;
	char	*pinpoint;

	pinpoint = ft_strchr(new, '=');
	new_value = ft_strdup(pinpoint + 1);
	return (new_value);
}

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
	return NULL;
}

char	*export_envp_value(char *k, char *v, t_shell *envp)
{
	t_envp	*ptr;
	char	*eq_pos;

	ptr = envp->head;
	eq_pos = 0;
	eq_pos = extract_key(eq_pos, k);
	while (ptr)
	{
		if (key_equals(ptr->key, eq_pos))
		{
			if (v)
			{
				free(ptr->value);
				ptr->value = replace_value(v);
			}
			free(eq_pos);
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	free(eq_pos);
	return NULL;
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
		(*node)->value = ft_substr(envp[*i],  delim - envp[*i] + 1, ft_strlen(delim + 1));
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
