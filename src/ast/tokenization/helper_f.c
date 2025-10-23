/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:06 by jhor              #+#    #+#             */
/*   Updated: 2025/10/23 20:55:05 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->lexeme)
			free(temp->lexeme);
		free(temp);
	}
	free(tokens);
}

char	*trim_prompt(char *trim)
{
	while (*trim == ' ' || *trim == '\t')
		trim++;
	return (trim);
}

void	quote_check(char *result, int *i, char quote)
{
	while (result[*i] && result[*i] != '<' && result[*i] != '>'
		&& result[*i] != '|' && result[*i] != ' ' && result[*i] != '\t')
	{
		if (result[*i] == '\'' || result[*i] == '"')
		{
			quote = result[(*i)++];
			while (result[*i] && result[*i] != quote)
				(*i)++;
			if (result[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
}

int	readline_exit(t_ast *node, t_token *token, char *result)
{
	if (ft_strncmp(result, "exit", 4) == 0)
	{
		rl_clear_history();
		free_treenode(node);
		free_tokens(token);
		free(result);
		return (1);
	}
	return (0);
}
