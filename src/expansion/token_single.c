/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:17:08 by jhor              #+#    #+#             */
/*   Updated: 2025/12/02 16:59:04 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_token_single(size_t *len, char **value, size_t *start, size_t *i)
{
	*len = 0;
	*value = NULL;
	*start = *i;
}

char *token_single_only(char *lxm, size_t *i, t_parser *p)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*value;

	init_token_single(&len, &value, &start, i);
	end = ++(*i);
	while (lxm[end] && lxm[end] != '\'')
		end++;
	if (lxm[end] != '\'')
	{
		error_quotes('\'', p);
		return (NULL);
	}
	len = end - start + 1;
	value = malloc(len + 1);
	if (!value)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	ft_memcpy(value, lxm + start, len);
	value[len] = '\0';
	*i = end;
	return (value);
}
