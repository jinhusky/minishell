/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:15:09 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:57:57 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_missing_quotes(char lxm, t_globe *p)
{
	if (lxm != '"' && lxm != '$')
	{
		error_quotes('"', p);
		return ;
	}
}

char	*expand_token_double(char *lxm, char *result, size_t *end, t_globe *p)
{
	char	*value;

	value = NULL;
	value = extract_token_expand(lxm, end, p);
	if (!value || p->malloc_flag == 1)
		return (result);
	mark_char_expand(value, p);
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*init_result(char *result, t_globe *p)
{
	result = ft_strdup("");
	if (!result)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	return (result);
}

char	*token_double_statements(char *lxm, size_t *end, char *result, t_globe *p)
{
	if (lxm[*end] == '$')
	{
		result = expand_token_double(lxm, result, end, p);
		if (p->malloc_flag == 1)
			return (result);
	}
	else if (lxm[*end] && lxm[*end] != '$' && lxm[*end] != '"')
		result = char_join_str_mark(lxm, result, end, p);
	return (result);
}

char	*token_double_only(char *lxm, size_t *i, t_globe *p)
{
	size_t	end;
	char	*result;
	
	result = NULL;
	result = init_result(result, p);
	if (!result && p->malloc_flag == 1)
		return (NULL);
	result = char_join_str_mark(lxm, result, i, p);
	end = ++(*i);
	while (lxm[end] && lxm[end] != '"')
	{
		result = token_double_statements(lxm, &end, result, p);
		if (p->malloc_flag == 1)
			return (result);
		if (lxm[end] && lxm[end] != '"')
			end++;
	}
	check_missing_quotes(lxm[end], p);
	if (p->err_flag == 1)
		return (result);
	result = char_join_str_mark(lxm, result, &end, p);
	*i = end;
	return (result);
}
