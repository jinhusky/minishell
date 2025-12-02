/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:15:09 by jhor              #+#    #+#             */
/*   Updated: 2025/12/02 16:52:17 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*char_join_str(char *lxm, char *result, char ch[2], size_t i)
{
	ch[0] = lxm[i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	return (result);
}

void	check_missing_quotes(char lxm, t_parser *p)
{
	if (lxm != '"' && lxm != '$')
	{
		error_quotes('"', p);
		return ;
	}
}

char	*expand_token_double(char *lxm, char *result, size_t *end, t_parser *p)
{
	char	*value;

	value = NULL;
	value = extract_token_expand(lxm, end, p);
	if (!value || p->malloc_flag == 1)
		return (result);
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*init_result(char *result, t_parser *p)
{
	result = ft_strdup("");
	if (!result)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	return (result);
}

char	*token_double_only(char *lxm, size_t *i, t_parser *p)
{
	size_t	end;
	char	ch[2];
	char	*result;
	
	result = NULL;
	result = init_result(result, p);
	if (!result && p->malloc_flag == 1)
		return (NULL);
	result = char_join_str(lxm, result, ch, *i);
	end = ++(*i);
	while (lxm[end] && lxm[end] != '"')
	{
		if (lxm[end] == '$')
		{
			result = expand_token_double(lxm, result, &end, p);
			if (p->malloc_flag == 1)
				return (result);
		}
		else if (lxm[end] && lxm[end] != '$' && lxm[end] != '"')
			result = char_join_str(lxm, result, ch, end);
		if (lxm[end] && lxm[end] != '"')
			end++;
	}
	check_missing_quotes(lxm[end], p);
	if (p->err_flag == 1)
		return (result);
	result = char_join_str(lxm, result, ch, end);
	*i = end;
	return (result);
}
