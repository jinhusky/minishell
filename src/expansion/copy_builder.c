/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:21:04 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 21:46:43 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_copy(t_expand *new)
{
	if (new)
		free(new);
	if (new->s_array)
		free(new->s_array);
	if (new->mark)
		free(new->mark);
	return ;
}

t_expand	*node_copy_builder(char *result, int i, int start, t_parser *p)
{
	char	*sub;
	t_expand *new;
	
	sub = NULL;
	new = NULL;
	sub = substring_split(result, start, i, p);
	if (p->malloc_flag == 1)
		return (NULL);
	new = token_mark_copy(p, sub, start, (i - start));
	if (!new || !new->s_array || !new->mark)
	{
		free_copies(new);
		p->malloc_flag = 1;
		return (NULL);
	}
	return (new);
}

