/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:03:50 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:03:50 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	valid_component(t_parser *p)
{
	return (p->cursor->token == WORD
		|| p->cursor->token == REDIR_IN
		|| p->cursor->token == REDIR_OUT
		|| p->cursor->token == HEREDOC
		|| p->cursor->token == APPEND);
}

void	parse_components(t_ast *prt, t_ast *child, t_parser *p)
{
	t_token	*cur_redir;

	cur_redir = NULL;
	if (!token_peek(p))
		return;
	while (token_peek(p) && valid_component(p))
	{
		if (token_peek(p)->token == WORD)
		{
			child = parse_argument(child, p);
			attach_treenode(prt, child);
		}
		else
		{
			cur_redir = p->cursor;
			p = get_token(p);
			child = parse_redirection(child, p, cur_redir);
			if (p->err_flag == 1)
				return;
			attach_treenode(prt, child);
		}
		p = get_token(p);
	}
	return;
}
