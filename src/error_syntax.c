/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:09:08 by jhor              #+#    #+#             */
/*   Updated: 2025/09/22 21:17:41 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_redir(t_token *token)
{
	if (token->next == NULL)
		return;
	token = token->next;
	if (token->token == REDIR_IN || token->token == REDIR_OUT 
		|| token->token == HEREDOC || token->token == APPEND)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `\n", 2);
		ft_putstr_fd(token->lexeme, 2);
		ft_putstr_fd("'", 2);
		return;
	}
}

void	error_pipe(t_token *token)
{
	if (token->next != NULL)
		token = token->next;
	if (token->token == PIPE && token->token != WORD)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return;
	}
}

int	error_syntax(t_token *token)
{
	while (token->next != NULL)
	{
		if (*(token->lexeme) == '>' || *(token->lexeme) == '<'
			|| ft_strncmp(token->lexeme, ">>", 2) == 0
			|| ft_strncmp(token->lexeme, "<<", 2) == 0)
		{
			if (token->next == NULL)
			{
				ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
				return (2);
			}
			else if (token->next && token->next->token != WORD)
			{
				error_redir(token);
				return (2);
			}
		}
		else if (token->next->token == PIPE) //!figure out why here conditional jump
		{
			if (token->next == NULL || token->next->token == PIPE)
			{
				error_pipe(token);
				return (2);
			}
		}
		token = token->next;
	}
	return (0);
}
