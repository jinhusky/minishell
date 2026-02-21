/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:04:58 by kationg           #+#    #+#             */
/*   Updated: 2026/02/21 22:33:36 by jhor             ###   ########.fr       */
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

void	print_err_mssg(char *cmd, char *err_mssg)
{
	char *str;

	str = strdup("minishell :");
	if (cmd)
	{
		str = ft_strjoin_free(str, ft_strdup(cmd));
		str = ft_strjoin_free(str, ft_strdup(" :"));
	}
	str = ft_strjoin_free(str, ft_strdup(err_mssg));
	ft_putendl_fd(str, 2);
	free(str);
	return ;
}

void	remove_dot_slash(char *arg, char **raw)
{
	*raw = ft_substr(arg, 2, (ft_strlen(arg) - 2 + 1));
	return ;
}

bool	slash_exist(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (true);
	return (false);
}

int	process_fdir(char *arg)
{
	char		*raw;
	struct stat	statbuf;

	if (stat(arg, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			print_err_mssg(arg, "Is a directory");
			return (126);
		}
		else if (S_ISREG(statbuf.st_mode))
		{
			if (arg[0] == '.' && arg[1] == '/')
				remove_dot_slash(arg, &raw);
			if (open(raw, O_RDONLY | O_WRONLY) == -1)
				print_err_mssg(arg, "Permission denied");
			free(raw);
			return (126);
		}
	}
	else
		print_err_mssg(arg, "No such file or directory");
	return (127);
}

void	process_err_msg(char *arg, t_globe *p)
{
	int	errnum;

	errnum = 0;
	if (slash_exist(arg))
	{
		errnum = process_fdir(arg);
		p->exit_code[0] = errnum;
		return ;
	}
	else
		print_err_mssg(arg, "Command not found");
		p->exit_code[0] = 127;
	return ;
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

void	parent_clean_up(int prev_read, t_ast *root, pid_t *pids, t_globe *p)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (prev_read != STDIN_FILENO)
		close(prev_read);
	while (i < root->childcount)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	set_exit_code(status, p); //This function gets the exit status of child or signal and return
}

void	child_process(int *i, t_globe *p, int readpipe, int writepipe)
{
	if (*i < p->node->childcount - 1)
	{
		close(readpipe);
		child_execute_cmd(p->node->children[*i], p, p->prev_read, writepipe);
	}
	else //single pipe
		child_execute_cmd(p->node->children[*i], p, p->prev_read, STDOUT_FILENO);
}

bool	fork_child(pid_t *pid, t_globe *p)
{
	*pid = fork();
	if (*pid == -1)
		return (false);
	return (true);
}

void	assign_pipe(int *i, t_globe *p, int readpipe, int writepipe)
{
	if (p->prev_read != STDIN_FILENO) //close previous exec SC read_end pipe
		close(p->prev_read);
	if (*i < p->node->childcount - 1)
	{
		close(writepipe); //write end of pipe
		p->prev_read = readpipe; //read end of pipe
	}
}

static int	execute_pipeline(t_ast *root, t_globe *p)
{
	int		i;
	int		pipefd[2];
	pid_t	pids[1024];
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	while (++i < root->childcount)
	{
		if (i < root->childcount - 1 && pipe(pipefd) == -1)
			return (perror("pipe"), p->exit_code[0] = 1, 1);
		if (!fork_child(&pid, p))
			return (perror("fork"), p->exit_code[0] = 1, 1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			child_process(&i, p, pipefd[0], pipefd[1]);
		}
		pids[i] = pid;
		assign_pipe(&i, p, pipefd[0], pipefd[1]);
	}
	parent_clean_up(p->prev_read, root, pids, p);
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

