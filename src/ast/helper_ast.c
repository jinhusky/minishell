/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:35:30 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 15:35:30 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	attach_treenode(t_ast *branch, t_ast *leaf)
{
	t_ast	**new_children;

	new_children = NULL;
	if (!branch || !leaf)
		return;
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
