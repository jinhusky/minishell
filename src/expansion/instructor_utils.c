/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:58:31 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:03:30 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_origin(t_expand *origin)
{
	if (origin->s_array)
		free(origin->s_array);
	if (origin->mark)
		free(origin->mark);
	if (origin)
		free(origin);
}

void	free_all(char *result, char **tokens, t_expand **copies, t_globe *p)
{
	free(result);
	if (tokens && p->malloc_flag == 1)
		free_argv(tokens);
	if (copies)
		free_copies(copies);
	free_origin(p->origin);
}
