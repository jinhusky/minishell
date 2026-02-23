/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:00:52 by kationg           #+#    #+#             */
/*   Updated: 2026/02/23 23:12:39 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if exit without args then exit status is the last cmmd executed
// if exit with pipes then only exit subprocess and not shell
// shell stores the process exit status as an unsigned 8-bit value (modulo 256)

static int	get_exit_code(char *arg, t_globe *p)
{
	int	i;
	int	negative;
	int	number;

	i = 0;
	negative = 1;
	number = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			negative *= -1;
		i++;
	}
	while (arg[i])
	{
		number = number * 10 + (arg[i] - '0');
		i++;
	}
	return ((number * negative) % 256);
}

int	argv_count(char **argv, int count)
{
	while (argv[count])
		count++;
	return (count);
}

int	strisdigit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_exit(char **argv, t_globe *p)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	count = argv_count(argv, count);
	if (!strisdigit(argv[i]) && i == 1 && count == 2)
	{
		invalid_numeric_msg(argv[i], p);
		if (p->node->childcount == 1)
		{
			main_free(p->node, p->token, p->result, p);
			exit(p->exit_code[0]);
		}
		return (0);
	}
	else if (strisdigit(argv[i]) && i == 1 && count > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		p->exit_code[0] = 1;
		return (0);
	}
	return (1);
}

void	ft_exit(char **argv, t_globe *p)
{
	int	exit_code;

	if (!argv[1])
	{
		if (p->node->childcount == 1)
		{
			main_free(p->node, p->token, p->result, p);
			exit(p->exit_code[0]);
		}
	}
	else if (argv[1])
	{
		if (validate_exit(argv, p))
		{
			p->exit_code[0] = get_exit_code(argv[1], p);
			main_free(p->node, p->token, p->result, p);
			exit(p->exit_code[0]);
		}
		return ;
	}
}
