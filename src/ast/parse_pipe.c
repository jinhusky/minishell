/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:10:25 by jhor             ###   ########.fr       */
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
	p->err_flag = 0;
	return (node);
}

void	parse_pipeline(t_ast *root, t_parser *p)
{
	t_ast	*branch;

	branch = NULL;
	if (!token_peek(p))
		return;
	if (p->cur_cmd == NULL)
	{
		branch = create_treenode(branch);
		p->cur_cmd = branch;
		attach_treenode(root, p->cur_cmd);
	}
	if (token_peek(p)->token == PIPE)
	{
		if (!root->children[0]->children)
		{
			error_pipe(p->cursor);
			free_treenode(root);
			p->err_flag = 1;
			return;
		}
		p = get_token(p);
		if (!p->cursor || token_peek(p)->token == PIPE)
		{
			error_pipe(p->cursor);
			free_treenode(root);
			p->err_flag = 1;
			return;
		}
		branch = create_treenode(branch);
		p->cur_cmd = branch;
		parse_simple_command(p->cur_cmd, p);
		attach_treenode(root, p->cur_cmd);
		if (p->err_flag == 1)
		{
			free_treenode(root);
			return;
		}
	}
	else if (token_peek(p)->token != PIPE)
	{
		parse_simple_command(p->cur_cmd, p);
		if (p->err_flag == 1)
		{
			free_treenode(root);
			return;
		}
	}
	if (token_peek(p) && token_peek(p)->token != PIPE)
		p = get_token(p);
	if (token_peek(p))
		parse_pipeline(root, p);
}

t_ast	*parsing(t_ast *node, t_token *token, t_parser *p)
{
	node = init_ast(node, p, token);
	parse_pipeline(node, p);
	if (p->err_flag == 1)
		return (NULL);
	return (node);
}
