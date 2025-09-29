/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:35:12 by kationg           #+#    #+#             */
/*   Updated: 2025/09/29 14:26:05 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envp_value(char *k, char *v, t_shell *envp, char *arg)
{
	t_envp	*ptr;

	ptr = envp->head;
	while(ptr)
	{
		if (ft_strncmp(ptr->key, k, ft_strlen(k)) == 0)
		{
			if (v)
				ptr->value = v;
		}
		ptr = ptr->next;
	}
	t_envp *node = malloc(sizeof(t_envp));
    char *delim = ft_strchr(arg, '=');
    node->key = ft_substr(arg, 0, delim - arg);
    node->value = ft_substr(arg,  delim - arg + 1, ft_strlen(delim + 1));
	node->next = NULL;
	ptr->next = node;

}

//its wrong i have yet to account for multiple env vars
/*
 *
 *
 *
 *
 */
void	export(char **args, t_shell *envp_lst)
{
	//if there is no assignment (=) then we should not handle
	if (!ft_strchr(args[1], '='))
		return;
	//we only handle create new env var or edit env var value
	char	**split = ft_split(args[1], '=');
	envp_value(split[0], split[1], envp_lst, args[1]);
}
