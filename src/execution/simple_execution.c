/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:03:35 by kationg           #+#    #+#             */
/*   Updated: 2025/11/19 13:47:35 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **build_argv(t_ast *root)
{
	int	i;
	int	j;

	char *arg;
	i = 0;
	char **argv;
	t_ast *ptr;
	ptr = NULL;
	argv = ft_calloc(root->children[i]->childcount + 1, sizeof(char *));
	while (i < root->childcount && root->children[i])
	{
		ptr = root->children[i];
		if (root->children[i]->type == AST_COMMAND)
		{
			j = 0;
			while (j < ptr->childcount && ptr->children[j])
			{
				if (ptr->children[j]->type == AST_WORD)
				{
					arg = ptr->children[j]->token_ref->lexeme;
					argv[j] = ft_strdup(arg);
				}
				else if (ptr->children[j]->type == AST_ARGUMENT)
				{
					arg = ptr->children[j]->children[0]->token_ref->lexeme;
					argv[j] = ft_strdup(arg);
				}
				j++;
			}
			
		}
		i++;
	}
	return (argv);
}

char **build_envp(t_shell shell)
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
	{
		execve(argv[0], argv, envp_exec);
	}
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
				printf("%s\n", fullpath);
				if (execve(fullpath, argv, envp_exec) == -1)
					perror("Command not found");
				break;
			}
			i++;
		}
	}
}
void simple_execution(t_ast *root, t_shell *shell)
{
	(void) root;
	char **envp_exec = build_envp(*shell);
	char **argv = build_argv(root);
	for (int i = 0; argv[i]; i++)
	{
		printf("%s\n", argv[i]);
	}
	int pid = fork();
	if (pid == 0)
	{
		walk_ast(root);
		execute(envp_exec, argv, shell);		
	}
	else 
	{
		wait(NULL);
	}

}
