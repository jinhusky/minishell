/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/01/18 21:47:28 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <linux/limits.h>

bool is_builtin(char *cmd)
{
	if (!cmd)
		return false;
	if (ft_strncmp(cmd, "echo", 4) == 0 || \
		ft_strncmp(cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd, "export", 6) == 0 || \
		ft_strncmp(cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd, "env", 3) == 0 || \
		ft_strncmp(cmd, "exit", 4) == 0)
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
	return (0);
}

/*
int	run_builtin(t_globe *p, char **argv, int in_parent)
{
	int	status;

	if (!argv || !argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "echo", 5))
		status = ft_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		status = ft_pwd();
	else if (!ft_strncmp(argv[0], "env", 4))
		status = ft_env(p);
	else if (!ft_strncmp(argv[0], "cd", 3))
		status = ft_cd(p, argv);
	else if (!ft_strncmp(argv[0], "export", 7))
		status = ft_export(p, argv);
	else if (!ft_strncmp(argv[0], "unset", 6))
		status = ft_unset(p, argv);
	else if (!ft_strncmp(argv[0], "exit", 5))
		status = ft_exit(p, argv, in_parent);
	else
		status = 0;
	p->ptr = p->envp_ls.head;
	return (status);
}
*/
static int	run_single_cmd_in_parent(t_ast *cmd, t_globe *p)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in < 0 || saved_out < 0)
	{
		p->exit_code[0] = 1;
		return (1);
	}
	status = apply_redirections(cmd);
	if (status != 0)
	{
		p->exit_code[0] = status;
		return (status);
	}
	if (!cmd->argv || !cmd->argv[0])
		status = 0;
    /*
	else
		status = run_builtin(p, cmd->argv, 1);
    

    //restore fd_in and fd_out after executing in parent process
*/
	p->exit_code[0] = status;
	return (status);
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

static void	child_execute_cmd(t_ast *cmd, t_globe *p, int in_fd, int out_fd)
{
	int	status;

	status = apply_redirections(cmd);
	if (status != 0)
		exit(status);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
    /*
	if (is_builtin(cmd->argv[0]))
		exit(run_builtin(p, cmd->argv, 0));
    */
	exec_external(p, cmd->argv);
}

static int	execute_pipeline(t_ast *root, t_globe *p)
{
	int		count;
	int		i;
	int		pipefd[2];
	int		prev_read;
	pid_t	pid;
	pid_t	last_pid;

	count = root->childcount - 1;
	last_pid = -1;
	i = 0;
	while (i < count)
	{
		if (i < count - 1 && pipe(pipefd) == -1)
		{
			perror("pipe");
			p->exit_code[0] = 1;
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			p->exit_code[0] = 1;
			return (1);
		}
		if (pid == 0)
		{
			if (i < count - 1)
			{
				close(pipefd[0]);
				child_execute_cmd(root, p, prev_read, pipefd[1]);
			}
			else
				child_execute_cmd(root, p, prev_read, STDOUT_FILENO);
		}
		last_pid = pid;
		if (prev_read != STDIN_FILENO)
			close(prev_read);
		if (i < count - 1)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
		i++;
	}
	if (prev_read != STDIN_FILENO)
		close(prev_read);
	return 0;
}

void	execute(t_ast *root, t_globe *p)
{
	int     count;
	t_ast	*cmd;

	if (!root)
		return ;
	count = root->childcount;
	if (count <= 0)
		return ;
	if (count == 1)
	{
		if (cmd && cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		{
		    run_single_cmd_in_parent(cmd, p);
			return ;
		}
		execute_pipeline(root, p);
		return ;
	}
	execute_pipeline(root, p);
}

