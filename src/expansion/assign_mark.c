/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_mark.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:13:22 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:00:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_with_mark(char *value, t_expand *origin, int mark)
{
	size_t	o_len;
	size_t	len;
	size_t	new_len;
	size_t	i;

	o_len = origin->count;
	len = ft_strlen(value);
	new_len = o_len + len;
	i = 0;
	origin->s_array = ft_realloc(origin->s_array, o_len * sizeof(char *),
		(new_len  + 1) * sizeof(char *));
	ft_memcpy(origin->s_array + o_len, value, len);
	origin->s_array[new_len] = '\0';
	origin->mark = ft_realloc(origin->mark, o_len * sizeof(int),
		(new_len + 1) * sizeof(int));
	while (i < len)
	{
		origin->mark[o_len + i] = mark;
		i++;
	}
	origin->count = new_len;
}

void	mark_char_literal(char *value, t_globe *p)
{
	append_with_mark(value, p->origin, SRC_LITERAL);
}

void	mark_char_expand(char *value, t_globe *p)
{
	append_with_mark(value, p->origin, SRC_EXPAND);
}
