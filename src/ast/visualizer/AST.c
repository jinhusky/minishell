/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:42:58 by jhor              #+#    #+#             */
/*   Updated: 2025/10/05 00:42:58 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    ft_ast_visualize(t_ast *root)
{
    int i = 0;

	printf("%d\n", root->type);
    printf("|\n");
	if (root->children)
	{
    	while (i < root->childcount && root->children[i])
		{
			printf("%d, %d, %s\n", root->children[i]->type, root->children[i]->children[0]->type, root->children[i]->children[0]->token_ref->lexeme);
			i++;
		}
	}
}