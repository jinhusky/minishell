/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:00:42 by kationg           #+#    #+#             */
/*   Updated: 2025/09/20 14:35:41 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_n(char *argv)
{
    int     i;
    bool    n_flag;

    i = 1;
    n_flag = false;
    if (argv[0] == '-')
    {
        while (argv[i] == 'n')
            i++;
        if (argv[i + 1] == 0)
            n_flag = true;
    }
    return (n_flag);

}

int ft_echo(char *args[])
{
    int     i;
    bool    n_flag;

    n_flag = false;
    i = 0;
    while (args[i] && is_n(args[i]))
    {
        i++;
        n_flag = true;
    }
    if (!args[i] && !n_flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        if (!args[i + 1] && !n_flag)
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
