/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:50:35 by jhor              #+#    #+#             */
/*   Updated: 2025/09/19 14:59:45 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_node(t_token *head, char *start, size_t end) //!fix the space problem in double quotes
{
	t_token	*temp;
	size_t		i;
	
	i = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
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
	printf("create node is: %s\n", head->lexeme);
	printf("0000000000000000000000000000000000000\n");
	return (head);
}

t_token	*append_node(t_token *head, char *start, size_t end)
{
	t_token	*temp;
	size_t		i;
	
	i = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * (end + 1));
	if (!temp->lexeme)
		return (NULL);
	t_token *temp2 = NULL;
	if (head->next != NULL)
		temp2 = head->next;
	printf("head node is null or not: %s\n", head->lexeme);
	if (temp2 != NULL)
		printf("second node is null or not: %s\n", temp2->lexeme);
	while (i < end && start[i])
	{
		temp->lexeme[i] = start[i];
		i++;
	}
	temp->lexeme[i] = '\0';
	temp->next = NULL;
	t_token *trave = NULL;
	trave = head;
	while (trave->next != NULL)
		trave = trave->next;
	trave->next = temp;
	t_token *temp3 = NULL;
	temp3 = trave->next;
	while (temp3 != NULL)
	{
		printf("new node: %s\n", temp3->lexeme);
		temp3 = temp3->next;
	}
	printf("----------------------------------------------\n");
	return (head);
}

