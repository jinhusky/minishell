/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:00:52 by kationg           #+#    #+#             */
/*   Updated: 2026/02/04 14:26:56 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if exit without args then exit status is the last cmmd executed
// if exit with pipes then only exit subprocess and not shell
// shell stores the process exit status as an unsigned 8-bit value (modulo 256)

static int  get_exit_code(char *arg, t_globe *p)
{
	int i;
	int negative;
	int number;

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
	if (!ft_isdigit(arg[i]))
	{
		//clean p;
		exit(255);
	}
	while (arg[i])
	{
		number = number * 10 + (arg[i] - '0');
		i++;
	}
	return ((number *negative) % 256);
}

void	ft_exit(char **argv, t_globe *p)
{
	int exit_code;

	if (!argv[1])
	{
		main_free(p->node, p->token, p->result, p);
		exit(p->exit_code[0]);
	}
	if (!argv[2])
	{
		ft_printf("exit: too many arguments\n");
		p->exit_code[0] = 1;
		return;
	}
	p->exit_code[0] = get_exit_code(argv[1], p);
}

//exit alksfdjh 234 - it exits with bash: exit: aklsfdjh: numeric argument required
//exit 234 234 - it exits with bash: exit: too many arguments
//exit 234 askldfj - it does not exits with bash: exit: too many arguments
//exit asdf 234 asdf - it exits with bash: exit: aslkdfj: numeric argument required