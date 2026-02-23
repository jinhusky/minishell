/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:38:14 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 23:44:28 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_copies(t_expand **copies)
{
	int	i;

	i = 0;
	while (copies[i])
	{
		free(copies[i]->s_array);
		free(copies[i]->mark);
		free(copies[i]);
		i++;
	}
	free(copies);
}

t_expand	*token_mark_copy(t_globe *p, char *result, size_t start, size_t len)
{
	t_expand	*new;

	new = malloc(sizeof(t_expand));
	if (!new)
		return (NULL);
	new->s_array = NULL;
	new->s_array = malloc(sizeof(char) * (len + 1));
	if (!new->s_array)
		return (NULL);
	ft_memcpy(new->s_array, result, len);
	new->s_array[len] = '\0';
	new->mark = NULL;
	new->mark = malloc(sizeof(int) * len);
	if (!new->mark)
		return (NULL);
	ft_memcpy(new->mark, p->origin->mark + start, sizeof(int) * len);
	new->count = len;
	free(result);
	return (new);
}

void	init_split(t_splt_ary *split)
{
	split->in_sg = 0;
	split->in_db = 0;
	split->i = 0;
	split->start = 0;
	split->tcount = 0;
}

t_expand	**last_copy_split(char *result, t_splt_ary *sp, t_expand **cpy,
	t_globe *p)
{
	t_expand	*new;

	new = NULL;
	if (sp->i > sp->start)
	{
		new = node_copy_builder(result, sp->i, sp->start, p);
		if (p->malloc_flag == 1)
		{
			free_copies(cpy);
			return (cpy);
		}
		cpy = append_expand_token(cpy, &sp->tcount, new, p);
		if (p->malloc_flag == 1)
			return (cpy);
	}
	return (cpy);
}

t_expand	**copy_array_split(char *result, t_splt_ary *sp, t_expand **cpy,
	t_globe *p)
{
	t_expand	*new;

	init_split(sp);
	new = NULL;
	if (p->malloc_flag == 1)
		return (cpy);
	cpy = copy_split_engine(result, sp, cpy, p);
	if (p->malloc_flag == 1)
		return (cpy);
	cpy = last_copy_split(result, sp, cpy, p);
	if (p->malloc_flag == 1)
		return (cpy);
	if (cpy)
		cpy[sp->tcount] = NULL;
	return (cpy);
}
