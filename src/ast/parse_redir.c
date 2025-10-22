/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:56:35 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 15:56:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	valid_redirection(t_parser *p)
{
	return ( p->cursor->token == REDIR_IN
		|| p->cursor->token == REDIR_OUT
		|| p->cursor->token == HEREDOC
		|| p->cursor->token == APPEND);
}

bool	all_redirs(t_ast *branch)
{
	int	i;

	i = 0;
	if (!branch || branch->childcount == 0)
		return (false);
	while (i < branch->childcount)
	{
		if (branch->children[i]->type != AST_REDIR_IN
		&& branch->children[i]->type != AST_REDIR_OUT
		&& branch->children[i]->type != AST_APPEND
		&& branch->children[i]->type != AST_HEREDOC)
			return (false);
		i++;
	}
	return (true);
}

void	assign_type(t_ast *chd_ptr, t_parser *p, t_token *cur_redir)
{
	if (token_peek(p)->token == WORD && cur_redir->token == REDIR_IN)
		chd_ptr->type = AST_REDIR_IN;
	else if (token_peek(p)->token == WORD && cur_redir->token == REDIR_OUT)
		chd_ptr->type = AST_REDIR_OUT;
	else if (token_peek(p)->token == WORD && cur_redir->token == HEREDOC)
		chd_ptr->type = AST_HEREDOC;
	else if (token_peek(p)->token == WORD && cur_redir->token == APPEND)
		chd_ptr->type = AST_APPEND;
}

t_ast	*parse_redirection(t_ast *chd_ptr, t_parser *p, t_token *cur_redir)
{
	t_ast	*wrd_ptr;

	wrd_ptr = NULL;
	if (!token_peek(p) || token_peek(p)->token != WORD)
	{
		error_redir(p->cursor);
		p->err_flag = 1;
		return (chd_ptr);
	}
	chd_ptr = create_treenode(chd_ptr, p);
	if (p->malloc_flag == 1)
		return (NULL);
	wrd_ptr = create_treenode(wrd_ptr, p);
	if (p->malloc_flag == 1)
	{
		free_treenode(chd_ptr);
		return (NULL);
	}
	assign_type(chd_ptr, p, cur_redir);
	parse_word(wrd_ptr, p);
	attach_treenode(chd_ptr, wrd_ptr, p);
	if (p->malloc_flag == 1)
		free_treenode(wrd_ptr);
	return (chd_ptr);
}

void	parse_maybe_redirs(t_ast *prt, t_parser *p)
{
	t_ast	*redir_chd;
	t_token	*cur_redir;

	redir_chd = NULL;
	cur_redir = NULL;
	while (token_peek(p) && valid_redirection(p))
	{
		cur_redir = p->cursor;
		p = get_token(p);
		redir_chd = parse_redirection(redir_chd, p, cur_redir);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return;
		attach_treenode(prt, redir_chd, p);
		if (p->malloc_flag == 1)
			return;
		p = get_token(p);
	}
}
