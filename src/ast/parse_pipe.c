/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/01 17:54:44 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//now that i have a link list of tokens, what is the next step
//i should be traversing on the link list and identify 
//what tokens it can form to be a non-terminal
//we create functions according to the grammar rules and parse  in sequences

void	init_ast(t_ast *node, t_parser *p, t_token *token)
{
	node = malloc(sizeof(t_ast));
	node->type = 0;
	node->children = NULL;
	node->childcount = 0;
	node->token_ref = token;
	p->cursor = token;
}

t_parser	*get_token(t_parser *p)
{
	if (p->cursor != NULL)
		p->cursor = p->cursor->next;
	return (p);
}

t_token	*token_peek(t_parser *p)
{
	return (p->cursor);
}

t_ast	*create_treenode(t_ast *temp)
{
	temp = malloc(sizeof(t_ast));
	if (!temp)
		return (NULL);
	temp->children = NULL;
	temp->childcount = 0;
	temp->token_ref = NULL;
	temp->type = 0;
	return (temp);
}
t_ast	*parse_command(t_ast *node, t_parser *p); //sees token is a WORD, malloc AST_COMMAND && AST_WORD

t_ast	*parse_component(t_ast *node, t_parser *p)
{
	t_ast	*temp;

	temp = NULL;
	if (token_peek(p)->token == WORD)
	{
		temp = create_treenode(temp);
		temp->type = AST_ARGUMENT;
		temp->token_ref = p->cursor->lexeme;
		//if there are already existing AST_COMMAND, link AST_WORD to AST_COMMAND
		p->cursor = get_token(p);
	}
	return (temp);
}

t_ast	*parse_components(t_ast *node, t_parser *p)
{
	if (token_peek(p)->token == WORD)
	{
		parse_component(node, p);
		p->cursor = get_token(p);
		if (token_peek(p)->token == WORD)
		{
			parse_component(node, p);
			attach_word();
		}
	}
	return (node);
}

t_ast	*parse_simple_command(t_ast *node, t_parser *p)
{
	if (token_peek(p)->token == WORD && check_children(node) == 0) //check whether there are existing AST_COMMAND
		node = parsing_command(); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
	else if (token_peek(p)->token == WORD && check_children(node) == 1) //existing AST_COMMAND branch
		node = parsing_components(); //create AST_WORD then attach to existing AST_COMMAND
	p->cursor = get_token(p);
	return (node);
	
}

t_ast	*parse_pipeline(t_ast *node, t_parser *p)
{
	//if token_peek is WORD then call parse_simple_command;
	//get_token to get the next token;
	//if token_peek is REDIRECTION then call parse_simple_command;
	//if token_peek is PIPE then get_token to consume and call parse_simple_command
	if (token_peek(p)->token == WORD)
		parse_simple_command(node, p);
	// else if (token_peek(p)->token == REDIR_IN || 
	// 	token_peek(p)->token == REDIR_OUT ||
	// 	token_peek(p)->token == HEREDOC || token_peek(p)->token == APPEND)
	// 	parse_simple_command();
	p->cursor = get_token(p);
	// if (token_peek(p)->token == PIPE)
	// {
	// 	p->cursor = get_token(p);
	// 	parse_simple_command();
	// }
	if (!token_peek(p))
		// error_handle;
	return (node);
}

void	parsing(t_ast *node, t_token *token, t_parser *p)
{
	init_ast(node, token, p);
	parse_pipeline(node, p);
}
