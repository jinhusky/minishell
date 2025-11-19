/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 02:42:34 by kationg           #+#    #+#             */
/*   Updated: 2025/11/19 14:32:09 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void redirection(t_ast *node)
{
	int	new_fd;
	if (node->type == AST_REDIR_IN)
	{
		new_fd = open(node->children[0]->token_ref->lexeme, O_RDONLY);
		dup2(new_fd, STDIN_FILENO);
		close(new_fd);
	}
	
	else if (node->type == AST_REDIR_OUT)
	{
		new_fd = open(node->children[0]->token_ref->lexeme, O_WRONLY | O_CREAT | O_TRUNC ,0644);
		dup2(new_fd, STDOUT_FILENO);
		close(new_fd);
	}
	else if (node->type == AST_APPEND)
	{
		new_fd = open(node->children[0]->token_ref->lexeme, O_WRONLY| O_CREAT | O_APPEND ,0644);
		dup2(new_fd, STDOUT_FILENO);
		close(new_fd);
	}
	
}

void walk_ast(t_ast *node)
{
    int i;

    if (!node)
        return;
    redirection(node);  

    i = 0;
    while (i < node->childcount)
    {
        walk_ast(node->children[i]);
        i++;
    }
}

