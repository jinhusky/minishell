/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:26:28 by jhor              #+#    #+#             */
/*   Updated: 2025/11/25 07:09:55 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_treenode(t_ast *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	while (i < root->childcount)
	{
		free_treenode(root->children[i]);
		i++;
	}
	free(root->children);
	free(root);
}

void	invalid_token(t_token *token, char *result)
{
	if (!token)
		free(result);
}

void	empty_line(t_parser *p)
{
	p->trim = p->result;
	p->trim = trim_prompt(p->trim);
	if ((*p->trim) == '\0')
	{
		free(p->result);
		p->err_flag = 1;
	}
	return ;
}

void	init_program(t_token **tkn, t_ast **nd, t_parser *p)
{
	*tkn = NULL;
	*nd = NULL;
	p->result = NULL;
	p->cur_cmd = NULL;
	p->trim = NULL;
	p->exit_flag = 0;
	p->err_flag = 0;
	p->ptr = NULL;
	p->dollar_flag = 0;
	p->origin = NULL;
}
