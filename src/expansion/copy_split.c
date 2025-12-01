/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:38:14 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 21:52:24 by jhor             ###   ########.fr       */
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

t_expand	**append_expand_token(t_expand **tkns, int *count, t_parser *orgn)
{
	tkns = ft_realloc(tkns, (*count) * sizeof(t_expand *),
		(*count + 2) * sizeof(t_expand *));
	if (!tkns)
	{
		if (tkns)
			free_copies(tkns);
		orgn->malloc_flag = 1;
		return NULL;
	}
	tkns[*count] = orgn->origin;
	(*count)++;
	tkns[*count] = NULL;
	return (tkns);
}

t_expand	*token_mark_copy(t_parser *p, char *result, size_t start, size_t len)
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

t_expand	**copy_array_split(char *result, t_expand **cpy, t_parser *p)
{
	int			in_single;
	int			in_double;
	int			i;
	int			start;
	int			tcount;

	in_single = 0;
	in_double = 0;
	i = 0;
	start = 0;
	tcount = 0;
	if (p->malloc_flag == 1)
		return (cpy);
	while (result[i])
	{
		if (result[i] == '\'' && !in_double && p->origin->mark[i] == SRC_LITERAL)
			in_single = !in_single;
		else if (result[i] == '"' && !in_single && p->origin->mark[i] == SRC_LITERAL)
			in_double = !in_double;
		if (result[i] == ' ' && !in_single && !in_double)
		{
			if (i > start)
			{
				p->new = node_copy_builder(result, i, start, p); //!continue on the while loop
				if (p->malloc_flag == 1)
					break ;
				cpy = append_expand_token(cpy, &tcount, p);
				if (p->malloc_flag == 1)
					break ;
			}
			while (result[i] == ' ')
				i++;
			start = i;
			continue;
		}
		i++;
	}
	if (i > start)
	{
		sub = substring_split(result, start, i);
		if (!sub)
		{
			p->malloc_flag = 1;
			free_copies(cpy);
			return (cpy);
		}
		// printf("*check_expand_space* sub:%s\n", sub);
		t_expand * new = token_mark_copy(p->origin, sub, start, i);
		if (!new || !new->s_array || !new->mark)
		{
			p->malloc_flag = 1;
			free_copies(cpy);
			return (cpy);
		}
		cpy = append_expand_token(cpy, &tcount, new);
		if (!cpy)
		{
			p->malloc_flag = 1;
			free_copies(cpy);
			return (cpy);
		}
		// printf("*check_expand_space* tcount:%d\n", tcount);
	}
	if (cpy && p->malloc_flag != 1)
		cpy[tcount] = NULL;
	else if (p->malloc_flag == 1)
	{
		free_copies(cpy);
		return (NULL);
	}
	return (cpy);
}
