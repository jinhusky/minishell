/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/04 18:35:55 by jhor             ###   ########.fr       */
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

t_ast	*create_treenode(t_ast *treenode)
{
	treenode = malloc(sizeof(t_ast));
	if (!treenode)
		return (NULL);
	treenode->children = NULL;
	treenode->childcount = 0;
	treenode->token_ref = NULL;
	treenode->type = 0;
	return (treenode);
}

void	assign_treenode(t_ast *branch, t_parser *p) //potentially not needed
{
	if (token_peek(p)->token == WORD && branch->childcount == 0)
		branch->type = AST_WORD;
	else if (token_peek(p)->token == WORD && branch->childcount > 0)
		branch->type = AST_COMMAND;
	return;
}

void	attach_treenode(t_ast *branch, t_ast *leaf) //continue here
{
	if (!branch || !leaf)
		return;
	branch->children = malloc(sizeof(char *) * 1);
	if (!branch->children)
		return;
	while (*(branch->children))
	{
		
	}
}

t_ast	*parse_command_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	branch->children = malloc(sizeof(char *) * 1);
	if (!branch->children)
		return (NULL);
	//assign the token lexeme into children array
	return (branch);
}

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

t_ast	*parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	if (token_peek(p)->token == WORD)
	{
		command = create_treenode(command);
		command = parse_command_word(command, p); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
		attach_treenode(branch, command);
	}
	return (branch);
	// p->cursor = get_token(p);
	//else if (token_peek(p)->token == WORD) //existing AST_COMMAND branch
	//	node = parse_components(); //create AST_WORD then attach to existing AST_COMMAND
}

t_ast	*parse_pipeline(t_ast *root, t_parser *p)
{
	t_ast	*branch;

	branch = NULL;
	root = create_treenode(root);
	if (token_peek(p)->token == WORD)
	{
		branch = create_treenode(branch);
		branch = parse_simple_command(branch, p);
		attach_treenode(root, branch);
	}
	p = get_token(p);
	return (root);
	//if token_peek is WORD then call parse_simple_command;
	//get_token to get the next token;
	//if token_peek is REDIRECTION then call parse_simple_command;
	//if token_peek is PIPE then get_token to consume and call parse_simple_command
	// else if (token_peek(p)->token == REDIR_IN || 
	// 	token_peek(p)->token == REDIR_OUT ||
	// 	token_peek(p)->token == HEREDOC || token_peek(p)->token == APPEND)
	// 	parse_simple_command();
	// if (token_peek(p)->token == PIPE)
	// {
	// 	p->cursor = get_token(p);
	// 	parse_simple_command();
	// }
	// if (!token_peek(p))
		// error_handle;
}

void	parsing(t_ast *node, t_token *token, t_parser *p)
{
	init_ast(node, token, p);
	parse_pipeline(node, p);
}
