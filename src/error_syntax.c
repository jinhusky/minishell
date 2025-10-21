/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:09:08 by jhor              #+#    #+#             */
/*   Updated: 2025/10/21 18:09:59 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_redir(t_token *token)
{
	if (!token)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (token->token == REDIR_IN || token->token == REDIR_OUT 
		|| token->token == HEREDOC || token->token == APPEND 
		|| token->token == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->lexeme, 2);
		ft_putstr_fd("'\n", 2);
	}
		return;
}

void	error_pipe(t_token *token)
{
	if (!token)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (token->token == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	return;
}
