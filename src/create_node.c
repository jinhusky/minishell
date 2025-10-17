/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:50:35 by jhor              #+#    #+#             */
/*   Updated: 2025/10/17 16:48:12 by jhor             ###   ########.fr       */
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
	t_token	*temp2;
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
	temp2 = NULL;
	if (head->next != NULL)
		temp2 = head->next;
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
	// t_token *temp3 = NULL;
	// temp3 = trave->next;
	// while (temp3 != NULL)
	// {
	// 	printf("new node: %s\n", temp3->lexeme);
	// 	temp3 = temp3->next;
	// }
	// printf("----------------------------------------------\n");
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
