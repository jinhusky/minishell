/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_word_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:49:26 by jhor              #+#    #+#             */
/*   Updated: 2025/10/22 17:02:52 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*word_malloc(t_token *token, char *start, size_t *n_start, size_t *end)
{
	size_t	i;

	i = 0;
	while (*n_start < *end && start[*n_start])
	{
		token->lexeme[i++] = start[*n_start];
		(*n_start)++;
	}
	token->lexeme[i] = '\0';
	return (token->lexeme);
}

t_token	*append_word_node(t_token *head, char *start, size_t n_start, size_t end)
{
	t_token	*temp;
	t_token	*trave;
	
	temp = NULL;
	temp = malloc(sizeof(t_token));
	if (!temp)
		token_exit(temp, head);
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * (end + 1));
	if (!temp->lexeme)
		token_exit(temp, head);
	word_malloc(temp, start, &n_start, &end);
	temp->next = NULL;
	trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	return (head);
}
