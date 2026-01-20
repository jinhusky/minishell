/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:59:28 by kationg           #+#    #+#             */
/*   Updated: 2026/01/20 09:16:42 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <cstdlib>
#include <unistd.h>

bool is_builtin(char *cmd)
{
	if (!cmd)
		return false;
	if (!ft_strncmp(cmd, "echo", 4) || \
		!(ft_strncmp(cmd, "cd", 2)) || \
		!(ft_strncmp(cmd, "pwd", 3)) || \
		!ft_strncmp(cmd, "export", 6) || \
		!ft_strncmp(cmd, "unset", 5) || \
		!ft_strncmp(cmd, "env", 3) || \
		!ft_strncmp(cmd, "exit", 4))
		return true;
	return false;
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


static int	run_builtin_parent(t_ast *cmd, t_globe *p)
{
	int	res;

	res = false;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (res);
	if (!ft_strncmp(cmd->argv[0], "echo", 4))
		res = ft_echo(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "cd", 2))
		res = ft_cd(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 3))
		res = ft_pwd(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "export", 6))
		res = ft_export(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "unset", 5))
		res = ft_unset(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "env", 3))
		res = ft_env(cmd->argv, p);
	else if (!ft_strncmp(cmd->argv[0], "exit", 4))
		res = ft_exit(cmd->argv, p);
	return (res);

}

static bool	prep_execution(t_ast *root, t_globe *p)
{
	if (!root || !p)
		return (EXIT_SUCCESS);
	//do we check whether infile + outfile set correctly?
	int i = 0;

	while (i < root->childcount - 1)
	{
		if (pipe(root->children[i]->pipe_fd) != 0)
		{
			//free_all_data
			return (false);
		}
		i++;
	}
}

static int	open_out(const char *path, int append)
{
	if (append)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	apply_redirections(t_ast *cmd)
{
	int		fd;
	int		i;
	t_ast	*node;

	if (!cmd || !cmd->children)
		return (0);
	i = 0;
	while (i < cmd->childcount && cmd->children[i])
	{
		node = cmd->children[i];
		fd = -1;
		if (node->type == AST_REDIR_IN)
		{
			fd = open(node->children[0]->token_ref->lexeme, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (node->type == AST_REDIR_OUT)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 0);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->type == AST_APPEND)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->type == AST_HEREDOC)
		{
			dup2(node->heredoc_fd[0], STDIN_FILENO);
			close(node->heredoc_fd[0]);
		}
		i++;
	}
	return (1);
}


bool	redirect_io(t_ast *root, t_globe *p)
{
	int	res;

	res = true;
	if (!p)
		return (res);
	root->saved_fd[0] = dup(STDIN_FILENO);
	root->saved_fd[1] = dup(STDOUT_FILENO);
	apply_redirections(root);
	return (res);
}

bool	restore_io(t_ast *root, t_globe *p)
{
    if (root->saved_fd[0])
    {
        if (dup2(root->saved_fd[0], STDIN_FILENO) == -1)
            return false;
        close(root->saved_fd[0]);
    }
     if (root->saved_fd[1])
    {
        if (dup2(root->saved_fd[1], STDOUT_FILENO) == -1)
            return false;
        close(root->saved_fd[1]);
    }
    
    return true;
}
int	exec_external(t_globe *p, char **argv)
{

    char   *path_env;
    char  **paths;
    int     i;
    char   *fullpath;

    if (!argv || !argv[0])
		//need to replace with exit code(error)
        return 0;

    if (ft_strchr(argv[0], '/'))
        execve(argv[0], argv, p->envp_array);

    
    path_env = envp_value("PATH", NULL, p->envp_ls);
    if (!path_env)
        execve(argv[0], argv, p->envp_array);

    paths = ft_split(path_env, ':');
    if (!paths)
        execve(argv[0], argv, p->envp_array);

    i = 0;
    while (paths[i])
    {
        fullpath = ft_strdup(paths[i]);
        fullpath = ft_strjoin(fullpath, "/");
        fullpath = ft_strjoin(fullpath, argv[0]);

        if (access(fullpath, X_OK) == 0)
        {
            execve(fullpath, argv, p->envp_array);
            perror("execve");
            _exit(127);
        }
        free(fullpath);
        i++;
    }
}

bool	set_pipes(t_ast *node)
{
	int	i;
	t_ast *ptr;

	i = 0;
	ptr = node;	
	while (i < ptr->childcount - 1)
	{
		if (i == 0)
		{
			dup2(ptr->children[i]->pipe_fd[1], STDOUT_FILENO);
		}
		else 
		{
			dup2(ptr->children[i - 1]->pipe_fd[0], STDIN_FILENO);
			dup2(ptr->children[i]->pipe_fd[1], STDOUT_FILENO);
		}
		i++;
	}
}


static int	execute_pipeline(t_ast *root, t_globe *p)
{
	int	i;
	t_ast *ptr;

	i = 0;
	ptr = root->children[i];
	while (i < root->childcount - 1)
	{
		ptr->pid = fork();
		if (ptr->pid == -1)
		{
			ft_printf("fork failture");
			return (EXIT_FAILURE);
		}
		else if (ptr->pid == 0)
		{
			child_execute_cmd(ptr, p);
		}
		i++;
	}
	return ()
}

void	executor(t_ast *root, t_globe *p)
{
	int	res;

	if (p->envp_ls)
		p->envp_array = build_envp_array(t_shell envp_ls);
	if (root->childcount > 1)
		res = prep_execution(root, p);
	//check if redirection setup properly?
	if (root->childcount == 1 && is_builtin(root->children[0]->argv[0]))
	{
		redirect_io(root, p);
		run_builtin_parent(root, p);
		restore_io(root, p);
	}
	else 
		execute_pipeline(root, p);
}
