/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/01/14 07:45:20 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return 1;
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return 1;
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return 1;
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return 1;
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return 1;
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return 1;
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return 1;
	return 0;
}

void build_exec_pipeline(t_ast *root, t_globe *p)
{
    //determine if its standalone builtin cmd
	
    if (root->childcount == 1 && check_is_builtin(root->argv[0]))
    {
        char *path = ft_strjoin("../../built_in/", root->argv[0]);
        execve(path, root->argv, );
    }
}
