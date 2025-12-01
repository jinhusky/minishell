/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:38:14 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 10:54:46 by jhor             ###   ########.fr       */
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

t_expand	**append_expand_token(t_expand **tkns, int *count, t_expand *orgn)
{
	tkns = ft_realloc(tkns, (*count) * sizeof(t_expand *),
		(*count + 2) * sizeof(t_expand *));
	if (!tkns)
		return NULL;
	tkns[*count] = orgn;
	(*count)++;
	tkns[*count] = NULL;
	return (tkns);
}

t_expand	*token_mark_copy(t_expand *origin, char *result, size_t start, size_t end)
{
	size_t		len;
	t_expand	*new;

	len = end - start;
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
	ft_memcpy(new->mark, origin->mark + start, sizeof(int) * len);
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
	t_expand	**tokens;
	char		*sub;
	int			tcount;

	in_single = 0;
	in_double = 0;
	i = 0;
	start = 0;
	tokens = NULL;
	sub = NULL;
	tcount = 0;
	if (p->malloc_flag == 1)
		return (tokens);
	while (result[i])
	{
		if (result[i] == '\'' && !in_double && p->origin->mark[i] == SRC_LITERAL)
			in_single = !in_single;
		else if (result[i] == '"' && !in_single && p->origin->mark[i] == SRC_LITERAL)
			in_double = !in_double;
		// printf("*check_expand_space* in_single:%d\n", in_single);
		// printf("*check_expand_space* in_double:%d\n", in_double);
		if (result[i] == ' ' && !in_single && !in_double)
		{
			printf("*check_expand_space* in_single inside the if statement:%d\n", in_single);
			printf("*check_expand_space* in_double inside the if statement:%d\n", in_double);
			if (i > start)
			{
				printf("*check_expand_space*(1) start:%d\n", start);
				printf("*check_expand_space*(1) i:%d\n", i);
				sub = substring_split(result, start, i);
				if (!sub)
				{
					p->malloc_flag = 1;
					break ;
				}
				printf("*check_expand_space*(1) sub:%s\n", sub);
				t_expand *new = token_mark_copy(p->origin, sub, start, i);
				if (!new || !new->s_array || !new->mark)
				{
					p->malloc_flag = 1;
					break ;
				}
				tokens = append_expand_token(tokens, &tcount, new);
				if (!tokens)
				{
					p->malloc_flag = 1;
					break ;
				}
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
			free_copies(tokens);
			return (tokens);
		}
		printf("*check_expand_space* sub:%s\n", sub);
		t_expand * new = token_mark_copy(p->origin, sub, start, i);
		if (!new || !new->s_array || !new->mark)
		{
			p->malloc_flag = 1;
			free_copies(tokens);
			return (tokens);
		}
		tokens = append_expand_token(tokens, &tcount, new);
		if (!tokens)
		{
			p->malloc_flag = 1;
			free_copies(tokens);
			return (tokens);
		}
		printf("*check_expand_space* tcount:%d\n", tcount);
	}
	if (tokens && p->malloc_flag != 1)
		tokens[tcount] = NULL;
	else if (p->malloc_flag == 1)
	{
		free_copies(tokens);
		return (NULL);
	}
	for (int j = 0; j < tcount; j++)
	{
		printf("*copy_array_split* tokens[%d]:%s\n", j, tokens[j]->s_array);
		printf("*copy_array_split* count[%d]:%zu\n", j, tokens[j]->count);
		// for (size_t r = 0; r < tokens[j]->count; r++)
		// 	printf("*copy_array_split* mark[%d]:%d\n", j, tokens[j]->mark[r]);
	}
	cpy = tokens;
	return (cpy);
}
