/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/02/24 01:14:23 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_strv(char **v)
{
	int	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

static void	rebuild_envp_array(t_globe *p)
{
	if (!p || !p->envp_ls)
		return ;
	if (p->envp_array)
		free_strv(p->envp_array);
	p->envp_array = build_envp_array(*p->envp_ls);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp(cmd, "echo", 4) == 0
		|| ft_strncmp(cmd, "cd", 2) == 0
		|| ft_strncmp(cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd, "export", 6) == 0
		|| ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "env", 3) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0)
		return (true);
	return (false);
}

char	**build_envp_array(t_shell envp_ls)
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
		tmp = ft_strjoin_free(tmp, ft_strdup("="));
		tmp = ft_strjoin_free(tmp, ft_strdup(ptr->value));
		res[i] = tmp;
		ptr = ptr->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	execute(t_ast *root, t_globe *p)
{
	int		count;
	t_ast	*cmd;

	if (!root)
		return ;
	count = root->childcount;
	if (count <= 0)
		return ;
	if (count == 1)
	{
		cmd = root->children[0];
		rebuild_envp_array(p);
		if (cmd && cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		{
			run_single_cmd_in_parent(cmd, p);
			return ;
		}
		execute_pipeline(root, p);
		return ;
	}
	rebuild_envp_array(p);
	execute_pipeline(root, p);
}
