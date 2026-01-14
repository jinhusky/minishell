/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/01/14 08:09:03 by kationg          ###   ########.fr       */
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

char **build_envp_array(t_shell envp_ls)
{
	t_envp	*ptr;	
	char	**res;
	int		i;
	char	*tmp;

	ptr = envp_ls.head;
	res = (char **)ft_calloc(envp_ls.size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (ptr)
	{
		tmp = ft_strdup(ptr->key);
		tmp = ft_strjoin(tmp, "=");
		tmp = ft_strjoin(tmp, ptr->value);

		res[i] = tmp;
		ptr = ptr->next;
		i++;
	}
	res[i] = NULL;
	return (res);
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
