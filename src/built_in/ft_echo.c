/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:00:42 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 08:54:59 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_n(char *arg)
{
    int     i;
    bool    n_flag;

    i = 1;
    n_flag = false;
    if (arg[0] == '-')
    {
        while (arg[i] == 'n')
            i++;
        if (arg[i + 1] == 0)
            n_flag = true;
    }
    return (n_flag);

}

int ft_echo(char **argv, t_globe *p)
{
    int     i;
    bool    n_flag;

    n_flag = false;
    i = 0;
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
/*
#include <stdio.h>
int main(void)
{
    char *test1[] = {"-nnn", "-nnnnnnnnnnnnnnnnnnnn", "-n" ,"n", "bro" ,NULL};
    char *test2[] = {"-nnnnnnnn", "--nnn", "bruh", NULL};
    char *test3[] = {"echo", "-nnnn", "-n", "hey there", NULL};
    ft_echo(test1);
 ft_echo(test2);
 ft_echo(test3);

}
*/
