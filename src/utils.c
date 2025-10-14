/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:26:28 by jhor              #+#    #+#             */
/*   Updated: 2025/10/14 21:35:09 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_treenode(t_ast *root)
{
	int	i;

	i = 0;
	if (!root)
		return;
	while (i < root->childcount)
	{
		free_treenode(root->children[i]);
		i++;
	}
	free(root->children);
	free(root);
}