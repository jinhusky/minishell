/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 23:34:15 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	*init_origin(t_expand *origin)
{
	origin = malloc(sizeof(t_expand));
	origin->s_array = NULL;
	origin->mark = NULL;
	origin->count = 0;
	return (origin);
}

void	expansion_engine(t_ast *root, t_globe *p)
{
	int			i;
	t_ast		*ptr;
	t_splt_ary	split;

	i = 0;
	if (root)
	{
		while (i < root->childcount)
		{
			{
				ptr = root->children[i];
				simple_command_instructor(ptr, &split, p);
				if (p->err_flag == 1 || p->malloc_flag == 1)
					return ;
				i++;
			}
		}
	}
}
