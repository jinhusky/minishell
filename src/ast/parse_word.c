/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:51:42 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 15:51:42 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	strip_quotes(char *lexeme, t_parser *p)
{
	char	quote;
	char	*src;
	char	*dst;
	
	src = NULL;
	dst = NULL;
	src = lexeme;
	dst = lexeme;
	quote = 0;
	while (*src)
	{
		if (*src == '\'' || *src == '"')
		{
			if (quote == 0)
				quote = *src;
			else if (quote == *src)
				quote = 0;
			else
				*dst++ = *src;
		}
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	if (quote != 0)
		p->err_flag = 1;
}

void	parse_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	if (p->cursor)
	{
		//TODOD: if (inside the string has open and close double quotes as well as a '$' then call function to expand)
		strip_quotes(p->cursor->lexeme, p);
		if (p->err_flag == 1)
		{
			ft_putstr_fd("bash: unexpected EOF ", 2);
			ft_putstr_fd("while looking for matching `\"'\n", 2);
			ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
			return;
		}
		branch->token_ref = p->cursor;
	}
	return;
}