/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:09:08 by jhor              #+#    #+#             */
/*   Updated: 2025/10/20 16:12:34 by jhor             ###   ########.fr       */
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

// int	error_syntax(t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		if (*(token->lexeme) == '>' || *(token->lexeme) == '<'
// 			|| ft_strncmp(token->lexeme, ">>", 2) == 0
// 			|| ft_strncmp(token->lexeme, "<<", 2) == 0)
// 		{
// 			printf("current token lexeme is: %s\n", token->lexeme);
// 			printf("current token enum is: %d\n", token->token);
// 			if (token->next == NULL)
// 			{
// 				ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
// 				return (2);
// 			}
// 			else
// 			{
// 				token = token->next;
// 				printf("current token lexeme is: %s\n", token->lexeme);
// 				printf("current token enum is: %d\n", token->token);
// 				printf("i am here in error handling redir\n");
// 				error_redir(token);
// 				return (2);
// 			}
// 		}
// 		else if (*(token->lexeme) == '|')
// 		{
// 			if (token->next == NULL || token->next->token == PIPE)
// 			{
// 				error_pipe(token);
// 				return (2);
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }
