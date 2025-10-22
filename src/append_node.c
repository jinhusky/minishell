/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:15 by jhor              #+#    #+#             */
/*   Updated: 2025/10/22 17:04:10 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		token_exit(temp, head);
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * ((end) + 1));
	if (!temp->lexeme)
		token_exit(temp, head);
	temp->lexeme = lexeme_malloc(temp, &i, start, &end);
	temp->next = NULL;
	trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	return (head);
}
