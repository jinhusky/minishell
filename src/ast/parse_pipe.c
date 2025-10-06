/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/06 21:42:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//now that i have a link list of tokens, what is the next step
//i should be traversing on the link list and identify 
//what tokens it can form to be a non-terminal
//we create functions according to the grammar rules and parse  in sequences

t_ast	*init_ast(t_ast *node, t_parser *p, t_token *token)
{
	node = malloc(sizeof(t_ast));
	node->type = 0;
	node->children = NULL;
	node->childcount = 0;
	node->token_ref = NULL;
	p->cursor = token;
	return (node);
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
	t_ast	**new_children;
	int		i;

	new_children = NULL;
	i = 0;
	if (!branch || !leaf)
		return;
	printf("pass here\n");
	if (branch->children == NULL)
	{
		branch->children = malloc(sizeof(t_ast *));
		if (!branch->children)
			return;
		branch->children[0] = leaf;
		branch->childcount = 1;
	}
	else
	{
		new_children = realloc(branch->children, sizeof(t_ast *) * (branch->childcount + 1));
		if (!new_children)
			return;
		branch->children = new_children;
		branch->children[branch->childcount] = leaf;
		branch->childcount++;
	}
	return;
}

void	parse_command_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	branch->token_ref = p->cursor;
	if (!branch->token_ref)
		return;
	return;
}

// t_ast	*parse_component(t_ast *node, t_parser *p)
// {
// 	t_ast	*temp;

// 	temp = NULL;
// 	if (token_peek(p)->token == WORD)
// 	{
// 		temp = create_treenode(temp);
// 		temp->type = AST_ARGUMENT;
// 		temp->token_ref = p->cursor;
// 		//if there are already existing AST_COMMAND, link AST_WORD to AST_COMMAND
// 		// p->cursor = get_token(p);
// 	}
// 	return (temp);
// }

// t_ast	*parse_components(t_ast *node, t_parser *p)
// {
// 	if (token_peek(p)->token == WORD)
// 	{
// 		parse_component(node, p);
// 		p->cursor = get_token(p);
// 		if (token_peek(p)->token == WORD)
// 		{
// 			parse_component(node, p);
// 			attach_word();
// 		}
// 	}
// 	return (node);
// }

t_ast	*parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	branch->type = AST_COMMAND;
	if (token_peek(p)->token == WORD)
	{
		command = create_treenode(command);
		parse_command_word(command, p); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
		attach_treenode(branch, command);
	}
	return (branch);
	// p->cursor = get_token(p);
	//else if (token_peek(p)->token == WORD) //existing AST_COMMAND branch
	//	node = parse_components(); //create AST_WORD then attach to existing AST_COMMAND
}

void	parse_pipeline(t_ast *root, t_parser *p)
{
	t_ast	*branch;

	branch = NULL;
	if (token_peek(p) == NULL)
		return;
	if (token_peek(p)->token == WORD)
	{
		branch = create_treenode(branch);
		if (branch)
			printf("malloc-ed\n");
		parse_simple_command(branch, p);
		if (branch->children)
			printf("*inside parse_pipeline* %d\n", branch->type);
		attach_treenode(root, branch);
	}
	p = get_token(p);
	parse_pipeline(root, p);
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

t_ast	*parsing(t_ast *node, t_token *token, t_parser *p)
{
	node = init_ast(node, p, token);
	if (!node)
		printf("not initialized\n");
	parse_pipeline(node, p);
	if (node)
		printf("*inside parsing* %d\n", node->type);
	
	return (node);
}
