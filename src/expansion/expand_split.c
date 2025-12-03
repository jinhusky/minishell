/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:08:51 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:00:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**split_expand_tokens(char *result, t_splt_ary *sp, char **tokens, t_globe *p)
{
	char	*sub;

	sub = NULL;
	while (result[sp->i])
	{
		quote_indicator(result, sp, p);
		if (result[sp->i] == ' ' && !sp->in_sg && !sp->in_db)
		{
			if (sp->i > sp->start)
			{
				sub = substring_split(result, sp->start, sp->i, p);
				if (p->malloc_flag == 1)
					break ;
				tokens = token_append(tokens, sub, &sp->tcount, p);
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
	return (tokens);
}

char	**check_expand_space(char *result, t_splt_ary *sp, t_globe *p)
{
	char	**tokens;
	char	*sub;

	tokens = NULL;
	sub = NULL;
	init_split(sp);
	tokens = split_expand_tokens(result, sp, tokens, p);
	if (sp->i > sp->start)
	{
		sub = substring_split(result, sp->start, sp->i, p);
		if (p->malloc_flag == 1)
			return (tokens);
		tokens = token_append(tokens, sub, &sp->tcount, p);
		if (p->malloc_flag == 1)
			return (tokens);
	}
	if (tokens)
		tokens[sp->tcount] = NULL;
	return (tokens);
}
