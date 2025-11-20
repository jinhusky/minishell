/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:42:58 by jhor              #+#    #+#             */
/*   Updated: 2025/11/20 16:39:44 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_children(t_ast *cur_cmd)
{
	int	i;

	i = 0;
	while (i < cur_cmd->childcount && cur_cmd->children[i])
	{
		if (cur_cmd->children[i]->type == AST_WORD)
			printf(" --> (%d)Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->token_ref->lexeme);
		else if (cur_cmd->children[i]->type == AST_ARGUMENT)
			printf(" --> (%d)Type:[%d] Children Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->children[0]->type, cur_cmd->children[i]->children[0]->token_ref->lexeme);
		else if (cur_cmd->children[i]->type == AST_REDIR_IN)
			printf(" --> (%d)Type:[%d] Children Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->children[0]->type, cur_cmd->children[i]->children[0]->token_ref->lexeme);
		else if (cur_cmd->children[i]->type == AST_REDIR_OUT)
			printf(" --> (%d)Type:[%d] Children Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->children[0]->type, cur_cmd->children[i]->children[0]->token_ref->lexeme);
		else if (cur_cmd->children[i]->type == AST_APPEND)
			printf(" --> (%d)Type:[%d] Children Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->children[0]->type, cur_cmd->children[i]->children[0]->token_ref->lexeme);
		else if (cur_cmd->children[i]->type == AST_HEREDOC)
			printf(" --> (%d)Type:[%d] Children Type:[%d] Children:[%s]", (i + 1), cur_cmd->children[i]->type, cur_cmd->children[i]->children[0]->type, cur_cmd->children[i]->children[0]->token_ref->lexeme);
		i++;
	}
	printf("\n");
}

void	ft_ast_visualize(t_ast *root)
{
	int i = 0;
	t_ast *cur_cmd;

	cur_cmd = NULL;
	printf("Type:[%d](AST_PIPELINE)\n", root->type);
	if (root->children)
	{
		while (i < root->childcount && root->children[i])
		{
			printf("|\n");
			printf("Type:[%d](AST_COMMAND)\n", root->children[i]->type);
			cur_cmd = root->children[i];
			ft_print_children(cur_cmd);
			i++;
		}
	}
}
