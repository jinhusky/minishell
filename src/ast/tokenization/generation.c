/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:27:27 by jhor              #+#    #+#             */
/*   Updated: 2025/10/22 17:05:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_token	*token_word(t_token *tokens, char *result, int start, int i)
{
	if (tokens == NULL)
		tokens = create_node(tokens, result, i);
	else
		tokens = append_word_node(tokens, result, start, i);
	return (tokens);
}

t_token	*token_pipe(t_token *tokens, char *result)
{
	if (tokens == NULL)
		tokens = create_node(tokens, result, 1);
	else
		tokens = append_node(tokens, result, 1);
	return (tokens);
}

t_token	*token_single_operator(t_token *tokens, char *result)
{
	if (tokens == NULL && *result == '<')
		tokens = create_node(tokens, result, 1);
	else if (tokens != NULL && *result == '<')
		tokens = append_node(tokens, result, 1);
	else if (tokens == NULL && *result == '>')
		tokens = create_node(tokens, result, 1);
	else if (tokens != NULL && *result == '>')
		tokens = append_node(tokens, result, 1);
	return (tokens);
}

t_token	*token_double_operator(t_token *tokens, char *result)
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
	return (tokens);
}
