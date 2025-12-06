/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:03:35 by kationg           #+#    #+#             */
/*   Updated: 2025/12/06 22:13:20 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_argc(t_ast *cmd)
{
	int		count;
	int		i;
	t_ast	*ptr;
	
	count = 0;
	i = 0;
	//can try which ptr != NULL against childcount
	while (i < cmd->childcount)
	{
		ptr = cmd->children[i];
		if (ptr->type == AST_WORD || ptr->type == AST_ARGUMENT)
			count++;
		i++;

	}
	return (count);
}

char **build_argv_array(t_ast *cmd)
{
	int		i;
	t_ast	*child;
	char	**argv;
	
	if (!cmd || cmd->type != AST_COMMAND)
		return (NULL);
	argv = ft_calloc(count_argc(cmd) + 1, sizeof(char *));
	i = 0;
	while (i < node->childcount && node->children[i])
	{
		if (node->children[i]->type == AST_WORD)
			str = node->children[i]->token_ref->lexeme;
		else if (node->children[i]->type == AST_ARGUMENT)
			str = node->children[i]->children[0]->token_ref->lexeme;
		argv[i] = ft_strdup(str);
		i++;
	}
	return (argv);
}

char **build_envp_array(t_shell shell)
{
	t_envp	*ptr;
	int	i;
	
	i = 0;
	ptr = shell.envp_head;
	char **res;
	res = ft_calloc(shell.size + 1, sizeof(char *));
	while (ptr)
	{
		res[i] = ft_strdup(ptr->key);
		res[i] = ft_strjoin(res[i], "=");
		res[i] = ft_strjoin(res[i], ptr->value);
		ptr = ptr->next;
		i++;
	}
	return res;
}

void execute(char **envp_exec, char **argv, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	int		i;
	char	*fullpath;

	i = 0;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, envp_exec);
	else
	{
		path_env = envp_value("PATH", NULL, *shell);
		paths = ft_split(path_env, ':');
		while (paths[i])
		{
			fullpath = ft_strjoin(paths[i], "/");
			fullpath = ft_strjoin(fullpath, argv[0]);
			if (access(fullpath, F_OK) == 0)
			{
				if (execve(fullpath, argv, envp_exec) == -1)
					perror("Command not found");
				break;
			}
			i++;
		}
	}
}

void execute_pipeline(t_ast *root, t_shell *shell)
{
	char **envp_exec = build_envp_array(*shell);
	char **argv = build_argv_array(root);
	
	
	int pid = fork();
	if (pid == 0)
	{
		walk_ast_child(root);
		execute(envp_exec, argv, shell);		
	}
	else 
	{
		wait(NULL);
	}

}
