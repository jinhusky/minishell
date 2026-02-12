/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2026/02/11 15:38:36 by welow            ###   ########.fr       */
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

	printf("new:%s\n", new);
	pinpoint = ft_strchr(new, '=');
	printf("pinpoint:%s\n", pinpoint);
	printf("len of new:%zu\n", ft_strlen(new));
	printf("len of new:%zu\n", ft_strlen(pinpoint));
	printf("*pinpoint:%c\n", *(pinpoint + 1));
	new_value = ft_strdup(pinpoint + 1);
	printf("new_value:%s\n", new_value);
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
				//ft_printf("value before free: %s\n", ptr->value);
				free(ptr->value);
				ptr->value = v;
				//ft_printf("value: %s\n", ptr->value);
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

void	set_envp_array(char **envp, t_shell **shell, t_globe *p)
{
	int		i;
	char	*delim;
	t_envp	*node;
	t_envp	*prev;

	*shell = NULL;
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return ;
	//ft_printf("malloc a pointer to point to head of linked-list(t_envp)\n");
	(*shell)->head = NULL;
	(*shell)->size = 0;
	i = 0;
	prev = NULL;
	while (envp[i])
	{
		node = (t_envp *)malloc(sizeof(t_envp));
		//ft_printf("malloc a linked-list(t_envp) node\n");
		if (!node)
			return ;
		if (i == 0)
			(*shell)->head = node;
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
	(*shell)->size = i;
	p->envp_ls = *shell;
	//t_envp *shell_p = p->envp_ls->head;
	//while (shell_p)
	//{
	//	ft_printf("key:%s\n", shell_p->key);
	//	ft_printf("value:%s\n", shell_p->value);
	//	shell_p = shell_p->next;
	//}
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
