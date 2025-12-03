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

t_globe	*get_token(t_globe *p)
{
	if (p->cursor != NULL)
		p->cursor = p->cursor->next;
	return (p);
}

t_token	*token_peek(t_globe *p)
{
	return (p->cursor);
}

//TODO: pass result and token into t_globe for easier reference to free

t_ast	*create_treenode(t_ast *treenode, t_globe *p)
{
	treenode = malloc(sizeof(t_ast));
	if (!treenode)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	treenode->children = NULL;
	treenode->childcount = 0;
	treenode->token_ref = NULL;
	treenode->argc = 0;
	treenode->argv = NULL;
	treenode->type = 0;
	return (treenode);
}

void	realloc_child(t_ast **new_chld, t_ast *brch, t_ast *leaf, t_globe *p)
{
	new_chld = ft_realloc(brch->children, brch->childcount * sizeof(t_ast *),
			(brch->childcount + 1) * sizeof(t_ast *));
	if (!new_chld)
	{
		free_treenode(leaf);
		p->malloc_flag = 1;
		return ;
	}
	brch->children = new_chld;
	brch->children[brch->childcount] = leaf;
	brch->childcount++;
}

void	attach_treenode(t_ast *branch, t_ast *leaf, t_globe *p)
{
	t_ast	**new_children;

	new_children = NULL;
	if (!branch || !leaf)
		return ;
	if (branch->children == NULL)
	{
		branch->children = malloc(sizeof(t_ast *));
		if (!branch->children)
		{
			free_treenode(leaf);
			p->malloc_flag = 1;
			return ;
		}
		branch->children[0] = leaf;
		branch->childcount = 1;
	}
	else
		realloc_child(new_children, branch, leaf, p);
	return ;
}
