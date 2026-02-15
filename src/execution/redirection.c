/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:16:46 by jhor              #+#    #+#             */
/*   Updated: 2026/02/15 21:25:55 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_out(const char *path, int append)
{
	if (append)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

void	print_redir_err(t_ast *redir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir->token_ref->lexeme, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
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
			{
				print_redir_err(node->children[0]);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (node->type == AST_REDIR_OUT)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 0);
			if (fd < 0)
			{
				print_redir_err(node->children[0]);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (node->type == AST_APPEND)
		{
			fd = open_out(node->children[0]->token_ref->lexeme, 1);
			if (fd < 0)
			{
				print_redir_err(node->children[0]);
				return (1);
			}
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
