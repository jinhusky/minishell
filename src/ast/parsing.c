/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:01:54 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 15:00:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*parsing(t_ast *node, t_token *token, t_globe *p)
{
	if (!token)
		return (NULL);
	node = init_ast(node, p, token);
	parse_pipeline(node, p);
	if (p->err_flag == 1 || p->malloc_flag == 1)
		return (NULL);
	return (node);
}
