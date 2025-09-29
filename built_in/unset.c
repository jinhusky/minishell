/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:58:02 by kationg           #+#    #+#             */
/*   Updated: 2025/09/29 14:28:32 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	unset(char **cmd, t_shell *shell)
{
	
	t_envp	*ptr;
	t_envp	*prev;

	ptr = shell->head;
	prev = NULL;
	cmd++;
	int	i;
	while (ptr)
	{
		i = 0;
		while (cmd[i])
		{
			
			if (strncmp(cmd[i], ptr->key, ft_strlen(ptr->key)) == 0)
				prev->next = ptr->next;
			i++;
		}
		prev = ptr;
		ptr = ptr->next;
	}

}

