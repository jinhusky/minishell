/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:22:32 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:03:23 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_builtin(t_globe *p, char **argv, int in_parent)
{
	(void)in_parent;
	if (!argv || !argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "echo", 4))
		return (ft_echo(argv, p));
	if (!ft_strncmp(argv[0], "cd", 2))
		return (ft_cd(argv, p));
	if (!ft_strncmp(argv[0], "pwd", 3))
		return (ft_pwd(argv, p));
	if (!ft_strncmp(argv[0], "export", 6))
		return (ft_export(argv, p));
	if (!ft_strncmp(argv[0], "unset", 5))
		return (ft_unset(argv, p));
	if (!ft_strncmp(argv[0], "env", 3))
		return (ft_env(argv, p));
	if (!ft_strncmp(argv[0], "exit", 4))
	{
		ft_exit(argv, p);
		return (p->exit_code[0]);
	}
	return (0);
}
