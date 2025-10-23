/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:01:44 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:01:44 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*parse_argument(t_ast *chd_ptr, t_parser *p)
{
	t_ast	*word_ptr;
	
	word_ptr = NULL;
	chd_ptr = create_treenode(chd_ptr, p);
	if (p->malloc_flag == 1)
		return (NULL);
	chd_ptr->type = AST_ARGUMENT;
	if (!token_peek(p))
	{
		printf("*parse argument* Error: end of link-list\n");
		return (NULL);
	}
	if (token_peek(p)->token == WORD)
	{
		word_ptr = create_treenode(word_ptr, p);
		if (p->malloc_flag == 1)
			return (chd_ptr);
		parse_word(word_ptr, p);
		attach_treenode(chd_ptr, word_ptr, p);
		if (p->malloc_flag == 1)
			free_treenode(word_ptr);
	}
	return (chd_ptr);
}
