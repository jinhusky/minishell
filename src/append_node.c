/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:15 by jhor              #+#    #+#             */
/*   Updated: 2025/10/23 20:39:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_node(t_token *token)
{
	token->token = 0;
	token->lexeme = NULL;
	token->next = NULL;
	return (token);
}

char	*lexeme_malloc(t_token *token, size_t *i, char *start, size_t *end)
{
	while (*i < (*end) && start[*i])
	{
		token->lexeme[*i] = start[*i];
		(*i)++;
	}
	token->lexeme[*i] = '\0';
	return (token->lexeme);
}

t_token	*append_node(t_token *head, char *start, size_t end)
{
	t_token	*temp;
	size_t	i;
	t_token	*trave;

	i = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
	{
		free_append_word(head, temp);
		return (NULL);
	}
	temp = init_node(temp);
	temp->lexeme = malloc(sizeof(char) * ((end) + 1));
	if (!temp->lexeme)
	{
		free_append_word(head, temp);
		return (NULL);
	}
	temp->lexeme = lexeme_malloc(temp, &i, start, &end);
	trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	return (head);
}
