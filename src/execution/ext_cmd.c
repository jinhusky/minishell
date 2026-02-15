/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:15:31 by jhor              #+#    #+#             */
/*   Updated: 2026/02/15 22:16:59 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_external(t_globe *p, char **argv)
{
    char   *path_env;
    char  **paths;
    int     i;
    char   *fullpath;

	if (!argv || !argv[0])
		return ;
    if (ft_strchr(argv[0], '/')) //user/bin/ls
	{
		if (execve(argv[0], argv, p->envp_array) == -1)
		{
			process_err_msg(argv[0], p);
			exit (p->exit_code[0]);
		}
	}

	path_env = envp_value("PATH", NULL, p->envp_ls);
	if (!path_env)
		exit(EXIT_FAILURE);

	paths = ft_split(path_env, ':');
	if (!paths)
		exit (EXIT_FAILURE);

    i = 0;
	while (paths[i]) ///home/welow/.cargo/bin/cat
    {
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
		i++;
	}
	process_err_msg(argv[0], p);
	free_strv(paths); //!To test the error msg print//!hard code to print out which type of error message
	exit (p->exit_code[0]);
}