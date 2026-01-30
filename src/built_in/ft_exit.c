/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:00:52 by kationg           #+#    #+#             */
/*   Updated: 2026/01/30 18:00:15 by kationg          ###   ########.fr       */
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
        //clean (p)
        exit(p->exit_code);
    }
    if (!argv[2])
    {
        ft_printf("exit: too many arguments\n");
        p->exit_code = 1;
        return;
    }
    p->exit_code = get_exit_code(argv[1], p);
}
