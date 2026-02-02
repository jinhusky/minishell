/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2026/02/02 09:13:17 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	key_equals(const char *a, const char *b)
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
				ptr->value = ft_strdup(v);
			}
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return NULL;
}

void	set_envp_array(char **envp, t_shell *shell)
{
	int		i;
	char		*delim;
	t_envp		*node;
	t_envp		*prev;

	if (!shell)
		return ;
	free_envp_ls(shell);
	i = 0;
	prev = NULL;
	while (envp[i])
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		if (!node)
			return ;
		if (i == 0)
			shell->head = node;
		if (prev)
			prev->next = node;
		delim = ft_strchr(envp[i], '=');
		if (!delim)
		{
			node->key = ft_strdup(envp[i]);
			node->value = ft_strdup("");
		}
		else
		{
		node->key = ft_substr(envp[i], 0, delim - envp[i]);
		node->value = ft_substr(envp[i],  delim - envp[i] + 1, ft_strlen(delim + 1));
		}
		node->next = NULL;
		prev = node;
		i++;
	}
	shell->size = i;
}

/*
int main(int argc, char *argv[], char **envp)
{
	t_shell hey;
	set_envp(envp, &hey);
	t_envp *ptr = hey.head;
	while (ptr)
	{
		ft_printf("%s\n", ptr->key);
		ptr = ptr->next;
	}
}
*/
