/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:39:59 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 08:45:27 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ch_main_dir(t_globe *p)
{
	char	*oldpwd;
	char	*home;
	t_shell *envp;

	envp = p->envp_ls;
	oldpwd = envp_value("OLDPW", NULL, envp);
	//add or replace oldpwd
	if (oldpwd != NULL)
		envp_value("OLDPWD", envp_value("PWD", NULL, envp), envp);
	home = envp_value("HOME", NULL, envp);
}
void	ft_cd(char **args, t_globe *p)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		p->exit_code = ch_main_dir(p);

	}
	chdir(args[1]);
}
