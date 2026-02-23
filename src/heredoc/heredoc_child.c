/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:40:26 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:19:12 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
