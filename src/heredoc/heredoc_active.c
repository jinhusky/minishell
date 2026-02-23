/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_active.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:01:33 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 20:11:44 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO create a function to traverse the AST tree and mark tokens with quotes
//TODO work out on how to implement heredoc.
//! retain the quotes after expansion to avoid unnecessary splitting and wrong semantic interpretation
//! heredoc delimiter with quotes does not expand, without it it expands.

void	init_read_content(char **lns, char **rslt, int *ttl_len, int *ln_ln)
{
	*lns = NULL;
	*rslt = NULL;
	*ttl_len = 0;
	*ln_ln = 0;
}

void	Cntrl_D_err_msg(char *delimiter, t_globe *p)
{
	ft_putstr_fd("minishell: heredoc had reached end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

char	*extend_result(char *result, int *total_len, char *lines)
{
	int	line_len;

	line_len = 0;
	line_len = ft_strlen(lines);
	result = ft_realloc(result, *total_len * sizeof(char),
		(*total_len + line_len + 2) * sizeof(char));
	ft_memcpy(result + *total_len, lines, line_len);
	*total_len = *total_len + line_len;
	result[*total_len++] = '\n';
	result[*total_len] = '\0';
	return (result);
}

int	result_is_delim(char *lines, char *delimiter)
{
	if (ft_strncmp(lines, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(lines) == ft_strlen(delimiter))
	{
		free(lines);
		return (1);
	}
	return (0);
}

int	is_eof_delim(char *lines, char *delimiter, t_globe *p)
{
	if (!lines)
	{
		Cntrl_D_err_msg(delimiter, p);
		p->exit_code[0] = 0;
		return (1);
	}
	if (ft_strncmp(lines, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(lines) == ft_strlen(delimiter))
	{
		free(lines);
		return (1);
	}
	return (0);
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
		if (is_eof_delim(lines, delimiter, p) == 1)
			break ;
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

void	strip_heredoc_quotes(char *lexeme, t_globe *p)
{
	char	quote;
	char	*src;
	char	*dst;

	init_quotes(lexeme, &src, &dst, &quote);
	while (*src)
	{
		if (*src == '\'' || *src == '"')
		{
			p->heredoc_q_flag = 1;
			if (quote == 0)
				quote = *src;
			else if (quote == *src)
				quote = 0;
			else
				*dst++ = *src;
		}
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	if (quote != 0)
		error_quotes(quote, p);
	return ;
}

int	*set_heredoc_pipe(int *hpipe, t_globe *p)
{
	if (pipe(hpipe) == -1)
	{
		p->err_flag = 1;
		ft_putendl_fd("pipe error in heredoc", 2);
		p->exit_code[0] = 2;
		return (p->exit_code);
	}
	return (hpipe);
}

pid_t	spwn_heredoc_child(pid_t kid, int rpipe, int wpipe, t_globe *p)
{
	kid = fork();
	if (kid == -1)
	{
		close(rpipe);
		close(wpipe);
		p->err_flag = 1;
		ft_putendl_fd("fork error in heredoc", 2);
		p->exit_code[0] = 2;
		return (2);
	}
	return (kid);
}

void	readline_prep(char *lexeme, int rpipe, int wpipe, t_globe *p)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(rpipe);
	strip_heredoc_quotes(lexeme, p);
	if (p->err_flag == 1)
	{
		close(wpipe);
		exit(1);
	}
}

void	read_into_pipe(char *lexeme, int wpipe, t_globe *p)
{
	char	*line;
	
	line = NULL;
	line = read_content(lexeme, p);
	if (p->malloc_flag || p->err_flag)
	{
		close(wpipe);
		exit(1);
	}
	if (!line)
		write(wpipe, "", 1);
	else
		write(wpipe, line, ft_strlen(line));
	close(wpipe);
	free(line);
	exit(0);
}

void	child_reading(t_ast *heredoc, t_globe *p)
{
	readline_prep(heredoc->children[0]->token_ref->lexeme,
		heredoc->heredoc_fd[0], heredoc->heredoc_fd[1], p);
	read_into_pipe(heredoc->children[0]->token_ref->lexeme,
		heredoc->heredoc_fd[1], p);
}

void	heredoc_engine(t_ast *heredoc, t_globe *p)
{
	pid_t	kid;
	int		status;

	status = 0;
	set_heredoc_pipe(heredoc->heredoc_fd, p);
	if (p->err_flag == 1)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	kid = spwn_heredoc_child(kid, heredoc->heredoc_fd[0],
		heredoc->heredoc_fd[1], p);
	if (p->err_flag == 1)
		return ;
	if (kid == 0)
		child_reading(heredoc, p);
	close(heredoc->heredoc_fd[1]);
	waitpid(kid, &status, 0);
	set_hd_exit_code(status, p);
}

void	find_heredoc(t_ast *child, t_globe *p)
{
	int		i;
	t_ast	*heredoc;

	i = 0;
	heredoc = NULL;
	while (i < child->childcount && child->children[i])
	{
		if (child->children[i]->type == AST_HEREDOC)
		{
			heredoc = child->children[i];
			heredoc_engine(heredoc, p);
			if (p->err_flag == 1)
				return ;
		}
		i++;
	}
}

void	heredoc_ast(t_ast *root, t_globe *p)
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
