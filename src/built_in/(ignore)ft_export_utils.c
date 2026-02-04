/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:18:45 by welow             #+#    #+#             */
/*   Updated: 2026/01/28 22:01:22 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	export_error(char *cmd)
{
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (false);
	return (true);
}

int	check_export_arg(char *cmd, t_globe *p)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(cmd))
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			error_export_msg(cmd);
			return (p->exit_code[0] = 1, 1);
		}
	}
	return (0);
}

void	run_export(char *cmd, t_globe *p)
{

}