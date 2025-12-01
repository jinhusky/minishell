/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:02:13 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 11:02:29 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*token_expandable_check(char *lxm, char *result, t_parser *p)
{
	size_t	i;
	char	ch[2];
	char	*lit;
	char	*value;
	
	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	// printf("*token_is_expandable* string passed:%s\n", lxm);
	// if (iter_dollar(lxm) == 1)
	// {
	// 	p->dollar_flag = 1;
	// 	result = ft_strjoin_free(result, ft_strdup("$"));
	// 	for (int i = 0; result[i]; i++)
	// 		printf("iter_dollar %c",result[i]);
	// 	return (result);
	// }
	while (i < ft_strlen(lxm))
	{
		// printf("*token_expandable_check* lxm[i]:%c\n", lxm[i]);
		// printf("*token_expandable_check* i:%zu\n", i);
		if (lxm[i] != '$' && lxm[i] != '\'' && lxm[i] != '"')
		{
			ch[0] = lxm[i];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
			lit = ft_strdup(ch);
			if (!lit)
				return (NULL);
			mark_char_literal(lit, p);
			free(lit);
			// for (size_t o = 0; o < p->origin->count; o++)
			// {
			// 	printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
			// 	printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			// }
		}
		if (lxm[i] == '$')
		{
			value = extract_token_expand(lxm, &i, p);
			mark_char_expand(value, p);
			// for (size_t o = 0; o < p->origin->count; o++)
			// {
			// 	printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
			// 	printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			// }
			result = ft_strjoin_free(result, value);
			// printf("*token_expandable_check* result:%s\n", result);
			// printf("*token_expandable_check* iterator passed back from extract_token_expand:%zu\n", i);
		}
		else if (lxm[i] == '\'')
		{
			value = token_single_only(lxm, &i, p);
			if (p->err_flag == 1 || p->malloc_flag == 1)
			{
				p->exit_code[0] = 2;
				free(value);
				free(result);
				return (NULL);
			}
			mark_char_literal(value, p);
			// for (size_t o = 0; o < p->origin->count; o++)
			// {
			// 	printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
			// 	printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			// }
			result = ft_strjoin_free(result, value);
			// printf("*token_expandable_check* single quotes result:%s\n", result);
		}
		else if (lxm[i] == '"')
		{
			value = token_double_only(lxm, &i, p);
			if (p->err_flag == 1 || p->malloc_flag == 1)
			{
				p->exit_code[0] = 2;
				free(value);
				free(result);
				return (NULL);
			}
			mark_char_literal(value, p);
			// for (size_t o = 0; o < p->origin->count; o++)
			// {
			// 	printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
			// 	printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			// }
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* double quotes result:%s\n", result);
			printf("*token_expandable_check* after double quotes i:%zu\n", i);
		}
		i++;
	}
	printf("*token_expandable_check* final result:%s\n", result);
	return (result);
}

char	*stage_expand_check(t_ast *child, t_parser *p)
{
	char	*str;
	char	*result;
	
	result = NULL;
	printf("in here token_quotes\n");
	if (child->type == AST_WORD)
	{
		str = child->token_ref->lexeme;
		result = token_expandable_check(str, result, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return (result);
		printf("*token_single_quotes* final result:%s\n", result);
		// for (size_t o = 0; o < p->origin->count; o++)
		// {
		// 	printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
		// 	printf("*token_expandable_check* current mark:%d\n", p->origin->mark[o]);
		// }
	}
	return (result);
}