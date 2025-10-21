/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:00:15 by jhor              #+#    #+#             */
/*   Updated: 2025/10/21 15:57:43 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_token	*tokenize_operator(char *result, t_token *tokens, int *i)
{
	if (result[*i] != '|' && (result[*i] == '>' || result[*i] == '<'))
	{
		if (result[*i + 1] && result[*i + 1] == result[*i])
		{
			tokens = token_double_operator(tokens, result + *i);
			*i += 2;
		}
		else if (result[*i + 1] && result[*i + 1] != result[*i])
		{
			tokens = token_single_operator(tokens, result + *i);
			(*i)++;
		}
		else if (result[*i + 1] == '\0')
		{
			tokens = token_single_operator(tokens, result + *i);
			(*i)++;
		}
	}
	else if (result[*i] == '|')
	{
		tokens = token_pipe(tokens, result + *i);
		(*i)++;
	}
	return (tokens);
}

void	assign_enum(t_token *token)
{
	while (token != NULL)
	{
		if (ft_strncmp(token->lexeme, ">>", 2) == 0)
			token->token = APPEND;
		else if (ft_strncmp(token->lexeme, "<<", 2) == 0)
			token->token = HEREDOC;
		else if (ft_strncmp(token->lexeme, ">", 1) == 0)
			token->token = REDIR_OUT;
		else if (ft_strncmp(token->lexeme, "<", 1) == 0)
			token->token = REDIR_IN;
		else if (*(token->lexeme) == '|')
			token->token = PIPE;
		else 
			token->token = WORD;
		token = token->next;
	}
}

t_token	*tokenizer(char *result, t_token *tokens)
{
	int		i;
	int		start;
	char	quote;
	
	i = 0;
	start = 0;
	quote = '\0';
	while (result[i])
	{
		if (result[i] == ' ' || result[i] == '\t')
		{
			while (result[i] == ' ' || result[i] == '\t')
				i++;
		}
		else if (result[i] == '|' || result[i] == '<' || result[i] == '>')
			tokens = tokenize_operator(result, tokens, &i);
		else if (result[i] && result[i] != ' ')
		{
			start = i;
			quote_check(result, &i, quote);
			tokens = token_word(tokens, result, start, i);
		}
	}
	assign_enum(tokens);
	return (tokens);
}

