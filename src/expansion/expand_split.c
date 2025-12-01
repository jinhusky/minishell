/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:08:51 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 11:09:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**check_expand_space(char *result, t_expand *origin, t_parser *p)
{
	int		in_single;
	int		in_double;
	int		i;
	int		start;
	char	**tokens;
	char	*sub;
	int		tcount;

	in_single = 0;
	in_double = 0;
	i = 0;
	start = 0;
	tokens = NULL;
	sub = NULL;
	tcount = 0;
	while (result[i])
	{
		if (result[i] == '\'' && !in_double && origin->mark[i] == SRC_LITERAL)
			in_single = !in_single;
		else if (result[i] == '"' && !in_single && origin->mark[i] == SRC_LITERAL)
			in_double = !in_double;
		// printf("*check_expand_space* in_single:%d\n", in_single);
		// printf("*check_expand_space* in_double:%d\n", in_double);
		if (result[i] == ' ' && !in_single && !in_double)
		{
			// printf("*check_expand_space* in_single inside the if statement:%d\n", in_single);
			// printf("*check_expand_space* in_double inside the if statement:%d\n", in_double);
			if (i > start)
			{
				// printf("*check_expand_space*(1) start:%d\n", start);
				// printf("*check_expand_space*(1) i:%d\n", i);
				sub = substring_split(result, start, i);
				if (!sub)
				{
					p->malloc_flag = 1;
					break ;
				}
				// printf("*check_expand_space*(1) sub:%s\n", sub);
				tokens = token_append(tokens, sub, &tcount);
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
			return (tokens);
		}
		// printf("*check_expand_space* sub:%s\n", sub);
		tokens = token_append(tokens, sub, &tcount);
		if (!tokens)
		{
			p->malloc_flag = 1;
			return (tokens);
		}
		// printf("*check_expand_space* tcount:%d\n", tcount);
	}
	if (tokens)
	{
		tokens[tcount] = NULL;
		// for (int j = 0; tokens[j]; j++)
		// 	printf("*check_expand_space* tokens[%d]:%s\n", j, tokens[j]);
		
	}
	return (tokens);
}