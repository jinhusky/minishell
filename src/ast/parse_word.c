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

void	init_quotes(char *lexeme, char **src, char **dst)
{
	*src = NULL;
	*dst = NULL;
	*src = lexeme;
	*dst = lexeme;
}

void	error_quotes(char quote, t_parser *p)
{
	ft_putstr_fd("bash: unexpected EOF ", 2);
	ft_putstr_fd("while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
	p->err_flag = 1;
}

void	strip_quotes(char *lexeme, t_parser *p)
{
	char	quote;
	char	*src;
	char	*dst;

	init_quotes(lexeme, &src, &dst);
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
		error_quotes(quote, p);
	return ;
}

void	parse_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	if (p->cursor)
	{
		if (p->err_flag == 1)
			return ;
		branch->token_ref = p->cursor;
	}
	return ;
}
