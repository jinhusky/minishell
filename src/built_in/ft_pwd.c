/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:25:51 by kationg           #+#    #+#             */
/*   Updated: 2026/01/20 09:49:29 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <limits.h>

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
		p->exit_code[0] = EXIT_SUCCESS;
	}
	else 
	{
		ft_printf("pwd: %s: No such file or directory\n", argv[i]);
		p->exit_code[0] = EXIT_FAILURE;
	}
	return (p->exit_code[0]);
}

/*
int main (void)
{
    pwd();
}
*/
