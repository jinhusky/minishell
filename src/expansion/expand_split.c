/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:08:51 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 23:30:50 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**split_expand_tokens(char *rs, t_splt_ary *sp, char **tk, t_globe *p)
{
	char	*sub;

	sub = NULL;
	while (rs[sp->i])
	{
		quote_indicator(rs, sp, p);
		if (rs[sp->i] == ' ' && !sp->in_sg && !sp->in_db)
		{
			if (sp->i > sp->start)
			{
				sub = substring_split(rs, sp->start, sp->i, p);
				if (p->malloc_flag == 1)
					break ;
				tk = token_append(tk, sub, &sp->tcount, p);
				if (p->malloc_flag == 1)
					break ;
			}
			while (rs[sp->i] == ' ')
				sp->i++;
			sp->start = sp->i;
			continue ;
		}
		sp->i++;
	}
	return (tk);
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
