/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:58:02 by kationg           #+#    #+#             */
/*   Updated: 2026/02/05 15:47:20 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rm_env_var(t_globe *p, char *key)
{
	t_envp *curr;
	t_envp *prev;

	prev = NULL;
	curr = p->envp_ls->head;
	while (curr)
	{
		if (!ft_strncmp(key, curr->key, ft_strlen(key))
			&& ft_strlen(key) == ft_strlen(curr->key))
		{
			if (prev)
				prev->next = curr->next;
			else
				p->envp_ls->head = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			p->envp_ls->size = p->envp_ls->size - 1;
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
		p->exit_code[0] = EXIT_SUCCESS;
		return (p->exit_code[0]);
	}
	while (argv[i])
	{
		rm_env_var(p, argv[i]);
		ft_printf("size of env%d\n", p->envp_ls->size);
		i++;
	}
	return (p->exit_code[0]);
}

