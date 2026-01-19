/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:59:28 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 09:44:31 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <cstdlib>
#include <unistd.h>

bool is_builtin(char *cmd)
{
	if (!cmd)
		return false;
	if (!(ft_strncmp(cmd, "echo", 4)) || \
		!(ft_strncmp(cmd, "cd", 2)) || \
		!(ft_strncmp(cmd, "pwd", 3)) || \
		!ft_strncmp(cmd, "export", 6) || \
		!ft_strncmp(cmd, "unset", 5) || \
		!ft_strncmp(cmd, "env", 3) || \
		!ft_strncmp(cmd, "exit", 4))
		return true;
	return false;
}

static int	run_builtin_parent(t_ast *cmd, t_globe *p)
{
	int	res;

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
	return (0);
}

void	redirect_single_cmd(t_ast *cmd)
{
	int i = 0;
	
	while (i < cmd->childcount)
	{
		apply_redirections(cmd);
		i++;
	}
}

bool	redirect_io(t_ast *root, t_globe *p)
{
	int	res;
	t_ast *ptr;

	ptr = root;
	res = true;
	if (!p)
		return res;
	ptr->saved_fd[0] = dup(STDIN_FILENO);
	ptr->saved_fd[1] = dup(STDOUT_FILENO);
	redirect_single_cmd(ptr);
	return (res);
}
void	executor(t_ast *root, t_globe *p)
{
	int	res;

	if (root->childcount > 1)
		res = prep_execution(root, p);
	//check if redirection setup properly?
	if (root->childcount == 1 && is_builtin(root->argv[0]))
	{
		redirect_io(root, p);
		run_builtin_parent(root, p);
	}
	else 
		execute_pipeline(root, p);
}

