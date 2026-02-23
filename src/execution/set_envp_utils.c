/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:57:52 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:58:11 by jhor             ###   ########.fr       */
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
