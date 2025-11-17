/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2025/11/18 02:15:26 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*envp_value(char *k, char *v, t_shell envp)
{
	t_envp	*ptr;

	ptr = envp.envp_head;
	while(ptr)
	{
		if (ft_strncmp(ptr->key, k, ft_strlen(k)) == 0)
		{
			if (v)
				ptr->value = v;
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (false);
}

void set_envp(char **envp, t_shell *shell)
{
    int i;

    char    *delim;
    t_envp  *node;
    t_envp  *prev;
	
    i = 0;
    prev = NULL;
    while (envp[i])
    {
		
		node = malloc(sizeof(t_envp));
		if (i == 0)
			shell->envp_head = node;
		if (prev)
			prev->next = node;
        delim = ft_strchr(envp[i], '=');
        node->key = ft_substr(envp[i], 0, delim - envp[i]);
        node->value = ft_substr(envp[i],  delim - envp[i] + 1, ft_strlen(delim + 1));
		prev = node;
        i++;
    }
	shell->size = i;
	prev->next = NULL;
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
