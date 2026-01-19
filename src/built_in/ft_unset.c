/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:58:02 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 09:42:04 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <cstdlib>

void	rm_env_var(t_globe *p, char *key)
{
	t_envp *curr;
	t_envp *prev;

	prev = NULL;
	curr = p->envp_ls->head;
	while (curr)
	{
		if (!ft_strncmp(key, curr->key, ft_strlen(key)))
		{
			if (prev)
				prev->next = curr->next;
			else
				p->envp_ls->head = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **argv, t_globe *p)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		p->exit_code = EXIT_SUCCESS;
		return (p->exit_code);
	}
	while (argv[i])
	{
		rm_env_var(p, argv[i]);
		i++;
	}
	return (p->exit_code);
}

