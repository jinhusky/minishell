/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/02/02 22:42:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <linux/limits.h>
#include <sys/wait.h>

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
		tmp = ft_strjoin_free(tmp, ft_strdup("="));
		tmp = ft_strjoin_free(tmp, ft_strdup(ptr->value));
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
			if (fd < 0)
				return (1); //apply exit code to open redirection fail
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (node->type == AST_REDIR_OUT)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 0);
			if (fd < 0)
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->type == AST_APPEND)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 1);
			if (fd < 0)
				return (1);
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

static int	run_builtin(t_globe *p, char **argv, int in_parent)
{
	(void)in_parent;
	if (!argv || !argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "echo", 4))
		return (ft_echo(argv, p));
	if (!ft_strncmp(argv[0], "cd", 2))
		return (ft_cd(argv, p));
	if (!ft_strncmp(argv[0], "pwd", 3))
		return (ft_pwd(argv, p));
	if (!ft_strncmp(argv[0], "export", 6))
		return (ft_export(argv, p));
	if (!ft_strncmp(argv[0], "unset", 5))
		return (ft_unset(argv, p));
	if (!ft_strncmp(argv[0], "env", 3))
		return (ft_env(argv, p));
	if (!ft_strncmp(argv[0], "exit", 4))
		ft_exit(argv, p);
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
		status = 1;
	else if (!cmd->argv || !cmd->argv[0])
		status = 0;
	else
		status = run_builtin(p, cmd->argv, 1);
	dup2(saved_in, STDIN_FILENO); //why need to restore fds when running single builtin cmds. Restore fds in parent to align in fds
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
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
		return 0;

    if (ft_strchr(argv[0], '/')) //user/bin/ls
        execve(argv[0], argv, p->envp_array);

    path_env = envp_value("PATH", NULL, p->envp_ls);
    if (!path_env)
        execve(argv[0], argv, p->envp_array); //!handle exit when execve failed and free all the memory. Leak issues with child process in execution

	paths = ft_split(path_env, ':');
	if (!paths)
		execve(argv[0], argv, p->envp_array);

    i = 0;
	while (paths[i]) ///home/welow/.cargo/bin/cat
    {
        fullpath = ft_strdup(paths[i]);
        fullpath = ft_strjoin_free(fullpath, ft_strdup("/"));
        fullpath = ft_strjoin_free(fullpath, ft_strdup(argv[0]));

        if (access(fullpath, X_OK) == 0)
        {
            execve(fullpath, argv, p->envp_array);
            perror("execve");
        }
		free(fullpath);
        i++;
    }
	free_strv(paths);
	perror(argv[0]);//!hard code to print out which type of error message
	return (0);
}

static void	child_execute_cmd(t_ast *cmd, t_globe *p, int in_fd, int out_fd)
{
	int	status;

	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO); //pipe[0] --> STDIN
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	status = apply_redirections(cmd);
	if (status != 0) //exit code then exit for redirection failure
		exit(status);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(run_builtin(p, cmd->argv, 0));
	exec_external(p, cmd->argv);
}

static int	execute_pipeline(t_ast *root, t_globe *p)
{
	int		count;
	int		i;
	int		pipefd[2];
	int		prev_read;
	pid_t	pids[1024];
	int		status;
	pid_t	pid;

	status = 0;
	//---Jerry---//
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	//---Jerry---//
	count = root->childcount;
	if (count <= 0)
		return (0);
	prev_read = STDIN_FILENO; //ask chatgpt
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
			//---Jerry---//
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			//---Jerry---//
			if (i < count - 1)
			{
				close(pipefd[0]);
				child_execute_cmd(root->children[i], p, prev_read, pipefd[1]);
			}
			else //single pipe
				child_execute_cmd(root->children[i], p, prev_read, STDOUT_FILENO);
		}
		pids[i] = pid;
		if (prev_read != STDIN_FILENO)
			close(prev_read);
		if (i < count - 1)
		{
			close(pipefd[1]); //write end of pipe
			prev_read = pipefd[0]; //read end of pipe
		}
		i++;
	}
	if (prev_read != STDIN_FILENO)
		close(prev_read);
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	//---Jerry---//
	set_exit_code(status, p); //This function gets the exit status of child or signal and return
	//---Jerry---//
	return (p->exit_code[0]);
}

void	execute(t_ast *root, t_globe *p)
{
	int	count;
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

