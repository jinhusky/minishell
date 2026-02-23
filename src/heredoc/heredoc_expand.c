/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:24:10 by jhor             #+#    #+#             */
/*   Updated: 2026/01/28 15:24:10 by jhor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_expand_line(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	*value;

	value = NULL;
	value = extract_token_expand(lxm, i, p);
	if (p->malloc_flag == 1)
	{
		free(result);
		return (NULL);
	}
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*char_join_str(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	ch[2];
	char	*lit;

	lit = NULL;
	ch[0] = lxm[*i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	lit = ft_strdup(ch);
	if (!lit)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	free(lit);
	return (result);
}

int	invalid_result(char *result, t_globe *p)
{
	if (!result && p->malloc_flag == 1)
		return (1);
	else if (p->err_flag == 1)
		return (1);
	return (0);
}

char	*line_expandable_check(char *line, t_globe *p)
{
	size_t	i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (i < ft_strlen(line))
	{
		if (line[i] != '$')
		{
			result = char_join_str(line, result, &i, p);
			if (!result)
				return (NULL);
		}
		else
		{
			result = find_expand_line(line, result, &i, p);
			if (invalid_result(result, p) == 1)
				return (NULL);
		}
		i++;
	}
	free(line);
	return (result);
}

char	*heredoc_expand_check(char *line, t_globe *p)
{
	if (!line)
		return (NULL);
	if (p->heredoc_q_flag == 0)
		line = line_expandable_check(line, p);
	return (line);
}
