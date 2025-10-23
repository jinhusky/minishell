/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:06:08 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:06:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	first_word(t_ast *branch, t_ast *command, t_parser *p)
{
	command = create_treenode(command, p);
	if (p->malloc_flag == 1)
		return ;
	parse_word(command, p);
	attach_treenode(branch, command, p);
	if (p->err_flag == 1 || p->malloc_flag == 1)
		return ;
	p = get_token(p);
}

void	parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	branch->type = AST_COMMAND;
	if (!branch->children && (token_peek(p)->token == REDIR_IN
			|| token_peek(p)->token == REDIR_OUT
			|| token_peek(p)->token == APPEND
			|| token_peek(p)->token == HEREDOC))
	{
		parse_maybe_redirs(branch, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return ;
	}
	if ((all_redirs(branch) == true || !branch->children)
		&& token_peek(p) && token_peek(p)->token == WORD)
	{
		first_word(branch, command, p);
		if (p->malloc_flag == 1)
			return ;
	}
	if (branch->children && token_peek(p))
		parse_components(branch, command, p);
	return ;
}
