/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:50:35 by jhor              #+#    #+#             */
/*   Updated: 2025/10/22 22:00:51 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*first_lexeme(t_token *token, int *i, char *start, size_t **end)
{
	while (*i < *end && start[*i])
	{
		token->lexeme[*i] = start[*i];
		(*i)++;
	}
	token->lexeme[*i] = '\0';
	return (token->lexeme);
}

t_token	*create_node(t_token *head, char *start, size_t end)
{
	t_token	*temp;
	size_t	i;
	int		flag;
	
	i = 0;
	flag = 0;
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->token = 0;
	temp->lexeme = NULL;
	temp->lexeme = malloc(sizeof(char) * end + 1);
	if (!temp->lexeme)
	{
		free(temp);
		return (NULL);
	}
	temp->lexeme = first_lexeme(temp, &i, start, &end);
	temp->next = NULL;
	head = temp;
	return (head);
}

