/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:27:27 by jhor              #+#    #+#             */
/*   Updated: 2025/11/28 11:52:40 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_token	*token_word(t_token *tokens, t_parser *p, int start, int i)
{
	if (tokens == NULL)
		tokens = create_node(tokens, p->result, i);
	else
		tokens = append_word_node(tokens, p->result, start, i);
	if (tokens == NULL)
		token_exit(tokens, p->result, p);
	return (tokens);
}

t_token	*token_pipe(t_token *tokens, char *result, t_parser *p)
{
	if (tokens == NULL)
		tokens = create_node(tokens, result, 1);
	else
		tokens = append_node(tokens, result, 1);
	if (tokens == NULL)
		token_exit(tokens, result, p);
	return (tokens);
}

t_token	*token_single_operator(t_token *tokens, char *result, t_parser *p)
{
	if (tokens == NULL && *result == '<')
		tokens = create_node(tokens, result, 1);
	else if (tokens != NULL && *result == '<')
		tokens = append_node(tokens, result, 1);
	else if (tokens == NULL && *result == '>')
		tokens = create_node(tokens, result, 1);
	else if (tokens != NULL && *result == '>')
		tokens = append_node(tokens, result, 1);
	if (tokens == NULL)
		token_exit(tokens, result, p);
	return (tokens);
}

t_token	*token_double_operator(t_token *tokens, char *result, t_parser *p)
{
	int	i;

	i = 0;
	if (tokens == NULL && result[i] == '<' && result[i + 1] == '<')
		tokens = create_node(tokens, result, 2);
	else if (tokens != NULL && result[i] == '<' && result[i + 1] == '<')
		tokens = append_node(tokens, result, 2);
	else if (tokens == NULL && result[i] == '>' && result[i + 1] == '>')
		tokens = create_node(tokens, result, 2);
	else if (tokens != NULL && result[i] == '>' && result[i + 1] == '>')
		tokens = append_node(tokens, result, 2);
	if (tokens == NULL)
		token_exit(tokens, result, p);
	return (tokens);
}
