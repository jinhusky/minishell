/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:50:35 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:41:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_node(t_token *head, char *start, size_t end)
{
	t_token	*temp;
	size_t		i;
	
	i = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * end + 1);
	if (!temp->lexeme)
		return (NULL);
	while (i < end && start[i])
	{
		temp->lexeme[i] = start[i];
		i++;
	}
	temp->lexeme[i] = '\0';
	temp->next = NULL;
	head = temp;
	return (head);
}

t_token	*append_node(t_token *head, char *start, size_t end)
{
	t_token	*temp;
	size_t	i;
	t_token	*trave;
	
	i = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * (end + 1));
	if (!temp->lexeme)
		return (NULL);
	while (i < end && start[i])
	{
		temp->lexeme[i] = start[i];
		i++;
	}
	temp->lexeme[i] = '\0';
	temp->next = NULL;
	trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	return (head);
}

t_token	*append_word_node(t_token *head, char *start, size_t n_start, size_t end)
{
	t_token	*temp;
	size_t	i;
	t_token	*trave;
	
	i = 0;
	temp = NULL;
	temp = malloc(sizeof(t_token));
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * (end + 1));
	if (!temp->lexeme)
		return (NULL);
	while (n_start < end && start[n_start])
	{
		temp->lexeme[i++] = start[n_start];
		n_start++;
	}
	temp->lexeme[i] = '\0';
	temp->next = NULL;
	trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	return (head);
}
