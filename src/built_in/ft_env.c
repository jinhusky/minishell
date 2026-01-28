/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:23:28 by kationg           #+#    #+#             */
/*   Updated: 2026/01/20 09:49:51 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **argv, t_globe *p)
{
	t_envp *ptr;

	if (argv[1] == NULL)
	{
		ptr = p->envp_ls->head;
		while (ptr)
		{
			ft_printf("%s=%s\n", ptr->key, ptr->value);
			ptr = ptr->next;
		}
	}
	p->exit_code[0] = EXIT_SUCCESS;
	return (p->exit_code[0]);
}
