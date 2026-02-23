/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:25:51 by kationg           #+#    #+#             */
/*   Updated: 2026/02/23 23:25:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <limits.h>

void	print_pwd_error(void)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int	ft_pwd(char **argv, t_globe *p)
{
	char	*pwd;

	if (ft_strncmp(argv[0], "pwd", 3) == 0
		&& ft_strlen(argv[0]) == ft_strlen("pwd"))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			print_pwd_error();
			p->exit_code[0] = EXIT_FAILURE;
			return (p->exit_code[0]);
		}
		ft_printf("%s\n", pwd);
		free(pwd);
		p->exit_code[0] = EXIT_SUCCESS;
	}
	return (p->exit_code[0]);
}

/*
int main (void)
{
    pwd();
}
*/
