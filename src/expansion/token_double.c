/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:15:09 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 11:15:32 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*token_double_only(char *lxm, size_t *i, t_parser *p)
{
	// printf("in here token_double_only\n");
	size_t	end;
	char	ch[2];
	char	*value;
	char	*result;
	
	result = ft_strdup("");
	if (!result)
		return (NULL);
	value = NULL;
	// printf("*token_double_only* what is *i:%zu\n", *i);
	// printf("*token_double_only* what is *i after:%zu\n", *i);
	ch[0] = lxm[*i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	end = ++(*i);
	// printf("*token_double_only* what is end:%zu\n", end);
	// printf("*token_double_only* what is *i after:%zu\n", *i);
	while (lxm[end] && lxm[end] != '"')
	{
		// printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
		if (lxm[end] == '$')
		{
			// printf("i am in here the loop\n");
			// printf("*token_double_only* what is *i:%zu\n", *i);
			value = extract_token_expand(lxm, &end, p);
			if (!value || p->malloc_flag == 1)
				return (result);
			// printf("*token_double_only* value from extract_token_expand:%s\n", value);
			// printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
			result = ft_strjoin_free(result, value);
		}
		else if (lxm[end] && lxm[end] != '$' && lxm[end] != '"')
		{
			ch[0] = lxm[end];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
		}
		// printf("*token_double_only* result inside loop:%s\n", result);
		if (lxm[end] && lxm[end] != '"')
			end++;
	}
	// printf("*token_double_only* lxm[end] after the loop:%c\n", lxm[end]);
	if (lxm[end] != '"' && lxm[end] != '$')
	{
		error_quotes('"', p);
		return (result);
	}
	ch[1] = 0;
	ch[0] = lxm[end];
	result = ft_strjoin_free(result, ft_strdup(ch));
	*i = end;
	return (result);
}