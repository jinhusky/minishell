/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:00:42 by kationg           #+#    #+#             */
/*   Updated: 2026/02/23 23:06:00 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_n(char *arg)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (arg[0] == '-')
	{
		if (arg[i] == 'n')
		{
			while (arg[i] && arg[i] == 'n')
				i++;
			if (arg[i] && arg[i] != 'n')
				return (n_flag);
			n_flag = true;
		}
	}
	return (n_flag);
}

int	ft_echo(char **argv, t_globe *p)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	while (argv[i] && is_n(argv[i]))
	{
		i++;
		n_flag = true;
	}
	if (!argv[i] && !n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (!argv[i + 1] && !n_flag)
			ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
