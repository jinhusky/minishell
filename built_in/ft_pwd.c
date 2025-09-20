/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:25:51 by kationg           #+#    #+#             */
/*   Updated: 2025/09/20 18:46:07 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>
#include <linux/limits.h>

void    pwd(void)
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)))
        ft_printf("%s", buffer);
    else 
        perror("PWD error:");
}

/*
int main (void)
{
    pwd();
}
*/
