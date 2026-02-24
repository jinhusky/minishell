/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:15:31 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 15:44:25 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_absolute(char **argv, t_globe *p)
{
	if (ft_strchr(argv[0], '/'))
	{
		if (execve(argv[0], argv, p->envp_array) == -1)
		{
			process_err_msg(argv[0], p);
			exit (p->exit_code[0]);
		}
	}
}

void	exec_relative(char **argv, char **paths, t_globe *p)
{
	int		i;
	char	*fullpath;

	i = -1;
	while (paths[++i])
	{
		fullpath = NULL;
		fullpath = ft_strdup(paths[i]);
		fullpath = ft_strjoin_free(fullpath, ft_strdup("/"));
		fullpath = ft_strjoin_free(fullpath, ft_strdup(argv[0]));
		if (access(fullpath, F_OK) == 0)
		{
			if (execve(fullpath, argv, p->envp_array) == -1)
			{
				process_err_msg(argv[0], p);
				free(paths);
				free(fullpath);
				exit (p->exit_code[0]);
			}
			break ;
		}
		free(fullpath);
	}
}

void	exec_external(t_globe *p, char **argv)
{
	char	*path_env;
	char	**paths;

	if (!argv || !argv[0])
		return ;
	exec_absolute(argv, p);
	path_env = envp_value("PATH", NULL, p->envp_ls);
	if (!path_env)
	{
		process_err_msg(argv[0], p);
		exit(p->exit_code[0]);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		exit (EXIT_FAILURE);
	exec_relative(argv, paths, p);
	process_err_msg(argv[0], p);
	free_strv(paths);
	exit (p->exit_code[0]);
}
