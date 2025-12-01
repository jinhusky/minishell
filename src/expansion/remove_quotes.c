/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:20:54 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 17:15:38 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_expd_quotes(size_t *si, size_t *di, char *quote)
{
	*si = 0;
	*di = 0;
	*quote = 0;
}

void	expd_strip_quotes(char *s, t_expd_e *mark, t_parser *p)
{
	size_t	si;
	size_t	di;
	char	quote;
	char	c;

	init_expd_quotes(&si, &di, &quote);
	while ((c = s[si]) != '\0')
	{
		// printf("what is character:%c\n", c);
		// printf("what is mark:%d\n", mark[si]);
		if ((c == '\'' || c == '"') && mark[si] == SRC_LITERAL)
		{
			if (quote == 0)
				quote = c;
			else if (quote == c)
				quote = 0;
			else
				s[di++] = c;
		}
		else
			s[di++] = c;
		si++;
	}
	s[di] = '\0';
	if (quote != 0)
		error_quotes(quote, p);
}

char	**token_quote_removal(char **tkns, t_expand **cps, t_parser *p)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!tkns)
		return (tkns);
	if (p->malloc_flag == 1)
		return (tkns);
	while (tkns[i])
	{
		ptr = tkns[i];
		expd_strip_quotes(ptr, cps[i]->mark, p);
		if (p->err_flag == 1)
			return (tkns);
		i++;
	}
	return (tkns);
}
