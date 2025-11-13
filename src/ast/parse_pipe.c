/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/11/13 15:40:23 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*init_ast(t_ast *node, t_parser *p, t_token *token)
{
	node = malloc(sizeof(t_ast));
	if (!node)
		ast_exit(token, node, p->result);
	node->type = 0;
	node->children = NULL;
	node->childcount = 0;
	node->token_ref = NULL;
	p->cursor = token;
	p->malloc_flag = 0;
	p->err_flag = 0;
	return (node);
}

void	first_pipe(t_ast *root, t_ast *branch, t_parser *p)
{
	branch = create_treenode(branch, p);
	if (p->malloc_flag == 1)
	{
		free_treenode(root);
		return ;
	}
	p->cur_cmd = branch;
	attach_treenode(root, p->cur_cmd, p);
	if (p->malloc_flag == 1)
	{
		free_treenode(root);
		return ;
	}
}

void	pipe_checks(t_ast *root, t_ast *branch, t_parser *p)
{
	if (!root->children[0]->children)
	{
		error_pipe(p->cursor);
		p->err_flag = 1;
		return ;
	}
	p = get_token(p);
	if (!p->cursor || token_peek(p)->token == PIPE)
	{
		error_pipe(p->cursor);
		p->err_flag = 1;
		return ;
	}
	branch = create_treenode(branch, p);
	p->cur_cmd = branch;
	parse_simple_command(p->cur_cmd, p);
	attach_treenode(root, p->cur_cmd, p);
}

void	parse_pipeline(t_ast *root, t_parser *p)
{
	t_ast	*branch;

	branch = NULL;
	if (!token_peek(p))
		return ;
	if (p->cur_cmd == NULL)
	{
		first_pipe(root, branch, p);
		if (p->malloc_flag == 1)
			return ;
	}
	if (token_peek(p)->token == PIPE)
		pipe_checks(root, branch, p);
	else if (token_peek(p)->token != PIPE)
		parse_simple_command(p->cur_cmd, p);
	if (p->err_flag == 1 || p->malloc_flag == 1)
	{
		free_treenode(root);
		return ;
	}
	if (token_peek(p) && token_peek(p)->token != PIPE)
		p = get_token(p);
	if (token_peek(p))
		parse_pipeline(root, p);
}
