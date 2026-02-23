/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:02:13 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:04:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*char_join_str_mark(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	ch[2];
	char	*lit;

	lit = NULL;
	ch[0] = lxm[*i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	lit = ft_strdup(ch);
	if (!lit)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	mark_char_literal(ch, p);
	free(lit);
	return (result);
}

char	*find_expand_token(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	*value;

	value = NULL;
	value = extract_token_expand(lxm, i, p);
	if (p->malloc_flag == 1)
	{
		free(result);
		return (NULL);
	}
	mark_char_expand(value, p);
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*token_single_op(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	*value;

	value = NULL;
	value = token_single_only(lxm, i, p);
	if (p->err_flag == 1)
	{
		p->exit_code[0] = 2;
		free(value);
		free(result);
		return (NULL);
	}
	else if (p->malloc_flag == 1)
	{
		free(value);
		free(result);
		return (NULL);
	}
	mark_char_literal(value, p);
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*token_double_op(char *lxm, char *result, size_t *i, t_globe *p)
{
	char	*value;

	value = NULL;
	value = token_double_only(lxm, i, p);
	if (p->err_flag == 1)
	{
		p->exit_code[0] = 2;
		free(value);
		free(result);
		return (NULL);
	}
	else if (p->malloc_flag == 1)
	{
		free(value);
		free(result);
		return (NULL);
	}
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*expandable_loop_condition(char *lxm, char *result, size_t *i,
	t_globe *p)
{
	if (lxm[*i] == '$')
	{
		result = find_expand_token(lxm, result, i, p);
		if (p->malloc_flag == 1)
			return (result);
	}
	else if (lxm[*i] == '\'')
	{
		result = token_single_op(lxm, result, i, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return (result);
	}
	else if (lxm[*i] == '"')
	{
		result = token_double_op(lxm, result, i, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return (result);
	}
	return (result);
}
