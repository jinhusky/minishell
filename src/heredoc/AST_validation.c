/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:01:33 by jhor              #+#    #+#             */
/*   Updated: 2025/11/12 20:00:04 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO create a function to traverse the AST tree and mark tokens with quotes
//TODO work out on how to implement heredoc.
//! retain the quotes after expansion to avoid unnecessary splitting and wrong semantic interpretation
//! heredoc delimiter with quotes does not expand, without it it expands.

char	*read_content(char *delimiter)
{
	char *lines;

	while (1)
	{
		lines = readline("> ");
		if (!lines)
			break;
		if (ft_strncmp(lines, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(lines);
			break;
		}
		
	}
}