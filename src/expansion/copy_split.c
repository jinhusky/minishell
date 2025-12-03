/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:38:14 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:00:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_copies(t_expand **copies)
{
	int	i = 0;
	while(copies[i])
	{
		free(copies[i]->s_array);
		free(copies[i]->mark);
		free(copies[i]);
		i++;
	}
	free(copies);
}

t_expand	**append_expand_token(t_expand **tkns, int *cnt, t_expand *new, t_globe *orgn)
{
	tkns = ft_realloc(tkns, (*cnt) * sizeof(t_expand *),
		(*cnt + 2) * sizeof(t_expand *));
	if (!tkns)
	{
		if (tkns)
			free_copies(tkns);
		orgn->malloc_flag = 1;
		return NULL;
	}
	tkns[*cnt] = new;
	(*cnt)++;
	tkns[*cnt] = NULL;
	return (tkns);
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

void	quote_indicator(char *result, t_splt_ary *sp, t_globe *p)
{
	if (result[sp->i] == '\'' && !sp->in_db && p->origin->mark[sp->i] == SRC_LITERAL)
		sp->in_sg = !sp->in_sg;
	else if (result[sp->i] == '"' && !sp->in_sg && p->origin->mark[sp->i] == SRC_LITERAL)
		sp->in_db = !sp->in_db;
}

t_expand	**copy_split_engine(char *result, t_splt_ary *sp, t_expand **cpy, t_globe *p)
{
	t_expand	*new;

	new = NULL;
	while (result[sp->i])
	{
		quote_indicator(result, sp, p);
		if (result[sp->i] == ' ' && !sp->in_sg && !sp->in_db)
		{
			if (sp->i > sp->start)
			{
				new = node_copy_builder(result, sp->i, sp->start, p); //!continue on the while loop
				if (p->malloc_flag == 1)
					break ;
				cpy = append_expand_token(cpy, &sp->tcount, new, p);
				if (p->malloc_flag == 1)
					break ;
			}
			while (result[sp->i] == ' ')
				sp->i++;
			sp->start = sp->i;
			continue;
		}
		sp->i++;
	}
	return (cpy);
}

t_expand	**last_copy_split(char *result, t_splt_ary *sp, t_expand **cpy, t_globe *p)
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

t_expand	**copy_array_split(char *result, t_splt_ary *sp, t_expand **cpy, t_globe *p)
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
