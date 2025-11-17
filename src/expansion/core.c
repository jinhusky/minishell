/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2025/11/17 18:19:43 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_intsructor(t_ast *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->childcount)
	{
		if (cmd->children[i]->type == AST_WORD)
		{
			token_dollar(cmd->children[i]);
		}
		else if (cmd->children[i] == AST_ARGUMENT)
		{
			token_dollar(cmd->children[i]->children[0]);
		}
		else if(cmd->children[i]->type == AST_REDIR_IN
			|| cmd->children[i]->type == AST_REDIR_OUT
			|| cmd->children[i]->type == AST_HEREDOC
			|| cmd->children[i]->type == AST_APPEND)
		{
			redir_token_dollar(cmd->children[i]->children[0],
				cmd->children[i]->type);
		}
		i++;
	}
}

void	expansion_engine(t_ast *root)
{
	int		i;
	t_ast	*ptr;

	i = 0;
	if (root)
	while (root->children[i])
	{
		{
			ptr = root->children[i];
			command_instructor(ptr);
			i++;
		}
	}
}