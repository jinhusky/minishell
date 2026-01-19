/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:25:51 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 09:15:08 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <cstdlib>
#include <limits.h>
#include <linux/limits.h>

int	ft_pwd(char **argv, t_globe *p)
{
	int	i;
	char *pwd;
	
	i = 1;
	if (!argv[i])
	{
		pwd = getcwd(NULL, 0);
		ft_printf("%s\n", pwd);
		free(pwd);
		p->exit_code = EXIT_SUCCESS;
	}
	else 
	{
		ft_printf("pwd: %s: No such file or directory\n", argv[i]);
		p->exit_code = EXIT_FAILURE;
	}
	return (p->exit_code);
}

/*
int main (void)
{
    pwd();
}
*/
