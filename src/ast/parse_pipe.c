/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/09/30 17:22:00 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//now that i have a link list of tokens, what is the next step
//i should be traversing on the link list and identify 
//what tokens it can form to be a non-terminal
//we create functions according to the grammar rules and parse  in sequences

void	init_ast(t_ast *node, t_token *token)
{
	node = malloc(sizeof(t_ast));
	node->type = 0;
	node->children = NULL;
	node->childcount = 0;
	node->token_ref = token;
}

// work function token_peek and get_token

void	get_token(t_token *token)
{
	if (token != NULL)
		token = token->next;
}

void	token_peek(t_token *token)
{
	// return (current_token);
}

void	parse_pipeline(t_ast *node)
{
	
}
