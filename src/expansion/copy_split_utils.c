/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:38:49 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:03:44 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	**append_expand_token(t_expand **tkns, int *cnt, t_expand *new,
	t_globe *orgn)
{
	tkns = ft_realloc(tkns, (*cnt) * sizeof(t_expand *),
			(*cnt + 2) * sizeof(t_expand *));
	if (!tkns)
	{
		if (tkns)
			free_copies(tkns);
		orgn->malloc_flag = 1;
		return (NULL);
	}
	tkns[*cnt] = new;
	(*cnt)++;
	tkns[*cnt] = NULL;
	return (tkns);
}

void	quote_indicator(char *result, t_splt_ary *sp, t_globe *p)
{
	if (result[sp->i] == '\'' && !sp->in_db
		&& p->origin->mark[sp->i] == SRC_LITERAL)
		sp->in_sg = !sp->in_sg;
	else if (result[sp->i] == '"' && !sp->in_sg
		&& p->origin->mark[sp->i] == SRC_LITERAL)
		sp->in_db = !sp->in_db;
}

t_expand	**copy_split_engine(char *result, t_splt_ary *sp, t_expand **cpy,
	t_globe *p)
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
				new = node_copy_builder(result, sp->i, sp->start, p);
				if (p->malloc_flag == 1)
					break ;
				cpy = append_expand_token(cpy, &sp->tcount, new, p);
				if (p->malloc_flag == 1)
					break ;
			}
			while (result[sp->i] == ' ')
				sp->i++;
			sp->start = sp->i;
			continue ;
		}
		sp->i++;
	}
	return (cpy);
}
