/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_conten.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:42:28 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:43:00 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_read_content(char **lns, char **rslt, int *ttl_len, int *ln_ln)
{
	*lns = NULL;
	*rslt = NULL;
	*ttl_len = 0;
	*ln_ln = 0;
}

void	cntrl_d_err_msg(char *delimiter, t_globe *p)
{
	ft_putstr_fd("minishell: heredoc had reached end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

int	is_eof_delim(char *lines, char *delimiter, t_globe *p)
{
	if (!lines)
	{
		cntrl_d_err_msg(delimiter, p);
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
