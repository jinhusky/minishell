/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_active.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:01:33 by jhor              #+#    #+#             */
/*   Updated: 2026/02/02 16:57:12 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "sys/ioctl.h"

//TODO create a function to traverse the AST tree and mark tokens with quotes
//TODO work out on how to implement heredoc.
//! retain the quotes after expansion to avoid unnecessary splitting and wrong semantic interpretation
//! heredoc delimiter with quotes does not expand, without it it expands.

void	init_read_content(char **lns, char **rslt, int *ttl_len, int *line_len)
{
	*lns = NULL;
	*rslt = NULL;
	*ttl_len = 0;
	*line_len = 0;
}

void	Cntrl_D_err_msg(char *delimiter, t_globe *p)
{
	ft_putstr_fd("minishell: heredoc had reached end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

char	*read_content(char *delimiter, t_globe *p)
{
	char	*lines;
	char	*result;
	int		total_len;
	int		line_len;

	init_read_content(&lines, &result, &total_len, &line_len);
	while (1)
	{
		lines = readline("> ");
		lines = heredoc_expand_check(lines, p);
		if (p->malloc_flag || p->err_flag)
			break ;
		if (!lines)
		{
			Cntrl_D_err_msg(delimiter, p);
			p->exit_code[0] = 0;
			break ;
		}
		if (ft_strncmp(lines, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(lines) == ft_strlen(delimiter))
		{
			free(lines);
			break;
		}
		line_len = ft_strlen(lines);
		result = ft_realloc(result, total_len * sizeof(char),
			(total_len + line_len + 2) * sizeof(char));
		ft_memcpy(result + total_len, lines, line_len);
		total_len = total_len + line_len;
		result[total_len++] = '\n';
		result[total_len] = '\0';
		free(lines);
	}
	return (result);
}

void  find_heredoc(t_ast *child, t_globe *p)
{
	int		i;
	char	*line;
	t_ast	*heredoc;
	pid_t	kid;
	int		status;

	i = 0;
	line = NULL;
	heredoc = NULL;
	status = 0;
	while (i < child->childcount && child->children[i])
  	{
	if (child->children[i]->type == AST_HEREDOC)
	{
		p->inside_heredoc = 1;
		heredoc = child->children[i];
		if (pipe(heredoc->heredoc_fd) == -1)
		{
		p->err_flag = 1;
		ft_printf("pipe error in heredoc\n");
		p->exit_code[0] = 2;
		return ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		kid = fork();
		if (kid == -1)
		{
		/* cleanup fds */
		close(heredoc->heredoc_fd[0]);
		close(heredoc->heredoc_fd[1]);
		p->err_flag = 1;
		ft_printf("fork error in heredoc\n");
		p->exit_code[0] = 2;
		return ;
		}
		if (kid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_IGN);
			/* child: write heredoc content, close write end and exit */
			close(heredoc->heredoc_fd[0]);
			strip_quotes(heredoc->children[0]->token_ref->lexeme, p);
			if (p->err_flag == 1)
			{
				close(heredoc->heredoc_fd[1]);
				_exit(1);
			}
			line = read_content(heredoc->children[0]->token_ref->lexeme, p);
			if (p->malloc_flag || p->err_flag)
			{
				close(heredoc->heredoc_fd[1]);
				_exit(1);
			}
			if (!line)
				write(heredoc->heredoc_fd[1], "", 1);
			else
				write(heredoc->heredoc_fd[1], line, ft_strlen(line));
			close(heredoc->heredoc_fd[1]);
			free(line);
			p->inside_heredoc = 0;
			_exit(0);
		}
		/* parent: close write end, keep read end for later */
		close(heredoc->heredoc_fd[1]);
		waitpid(kid, &status, 0);
		set_hd_exit_code(status, p);
	}
	i++;
	}
}

void	ast_loop(t_ast *root, t_globe *p)
{
	int		i = 0;
	t_ast	*cur_cmd;

	cur_cmd = NULL;
	if (root->children)
	{
		while (i < root->childcount && root->children[i])
		{
			cur_cmd = root->children[i];
			find_heredoc(cur_cmd, p);
			if (p->err_flag == 1)
				break ;
			i++;
		}
	}
}
