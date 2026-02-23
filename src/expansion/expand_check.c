/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:46:29 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:03:55 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*token_expandable_check(char *lxm, char *result, t_globe *p)
{
	size_t	i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (i < ft_strlen(lxm))
	{
		if (lxm[i] != '$' && lxm[i] != '\'' && lxm[i] != '"')
		{
			result = char_join_str_mark(lxm, result, &i, p);
			if (!result)
				return (NULL);
		}
		else
		{
			result = expandable_loop_condition(lxm, result, &i, p);
			if (!result && p->malloc_flag == 1)
				return (NULL);
			else if (p->err_flag == 1)
				return (NULL);
		}
		i++;
	}
	return (result);
}

char	*stage_expand_check(t_ast *child, t_globe *p)
{
	char	*str;
	char	*result;

	result = NULL;
	if (child->type == AST_WORD)
	{
		str = child->token_ref->lexeme;
		result = token_expandable_check(str, result, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return (result);
	}
	return (result);
}
