/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:02:13 by jhor              #+#    #+#             */
/*   Updated: 2025/12/02 19:14:27 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*char_join_str_mark(char *lxm, char *result, size_t *i, t_parser *p)
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

char	*find_expand_token(char *lxm, char *result, size_t *i, t_parser *p)
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

char	*token_single_op(char *lxm, char *result, size_t *i, t_parser *p)
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

char	*token_double_op(char *lxm, char *result, size_t *i, t_parser *p)
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
	mark_char_literal(value, p);
	result = ft_strjoin_free(result, value);
	return (result);
}

char	*expandable_loop_condition(char *lxm, char *result, size_t *i, t_parser *p)
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
			return (NULL);
	}
	else if (lxm[*i] == '"')
	{
		result = token_double_op(lxm, result, i, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return (NULL);
	}
	return (result);
}

char	*token_expandable_check(char *lxm, char *result, t_parser *p)
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
		result = expandable_loop_condition(lxm, result, &i, p);
		if (!result && p->malloc_flag == 1)
			return (NULL);
		else if (p->err_flag == 1)
			return (NULL);
		i++;
	}
	return (result);
}

char	*stage_expand_check(t_ast *child, t_parser *p)
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
