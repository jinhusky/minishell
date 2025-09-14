/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:00:15 by jhor              #+#    #+#             */
/*   Updated: 2025/09/14 21:23:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	word_group(char **tokens, char *result)
// {
// 	int	i;
// 	int	j;
// 	int	quotes;

// 	i = 0;
// 	j = 0;
// 	while (tokens[j])
// 	{
// 		while (result[i])
// 		{
// 			quotes = 0;
// 			if ((result[i] >= 'A' && result[i] <= 'Z') ||
// 				(result[i] >= 'a' && result[i] <= 'z') || result[i] == '.')
// 				tokens[j] = result[i];
// 			else if ((result[i] == 34 || result[i] == 39) && quotes == 1)
// 			{
// 				tokens[j] = result[i];
// 				quotes = 0;
// 			}
// 			else if ((result[i] == 34 || result[i] == 39) && quotes == 0)
// 			{
// 				tokens[j] = result[i];
// 				quotes = 1;
// 			}
// 			else if (result[i] == ' ' && quotes != 1)
// 				break;
// 			i++;
// 		}
// 		j++;
// 	}
// }



// int	token_count(char *result)
// {
// 	int		i;
// 	int		count;
// 	char	quote;

// 	i = 0;
// 	count = 0;
// 	quote = '\0';
// 	while (result[i])
// 	{
// 		if (result[i] == ' ' || result[i] == '\t')
// 			i++;
// 		printf("$%c\n", result[i]);
// 		printf("1) %d\n", count);
// 		if (result[i] == '\'' || result[i] == '"')
// 		{
// 			quote = result[i++];
// 			if (quote != '\0')
// 				printf("%c\n", quote);
// 			while (result[i] && result[i] != quote)
// 				i++;
// 			count++;
// 			i++;
// 		}
// 		printf("$%c\n", result[i]);
// 		printf("2) %d\n", count);
// 		if (result[i] == '>')
// 		{
// 			if (result[i + 1] == '>') 
// 				i++;
// 			count++;
// 			i++;
// 		}
// 		printf("$%c\n", result[i]);
// 		printf("3) %d\n", count);
// 		if (result[i] == '<')
// 		{
// 			if (result[i + 1] == '<') 
// 				i++;
// 			count++;
// 			i++;
// 		}
// 		printf("$%c\n", result[i]);
// 		printf("4) %d\n", count);
// 		if (result[i] == '|')
// 		{
// 			count++;
// 			i++;
// 		}
// 		printf("$%c\n", result[i]);
// 		printf("5) %d\n", count);
// 		if (result[i] && result[i] != ' ')
// 		{
// 			while (result[i] && result[i] != '<' && result[i] != '>' &&
// 				result[i] != '|' && result[i] != ' ' &&
// 				result[i] != '\t' && result[i] != '\'' && result[i] != '"')
// 				i++;
// 			count++;
// 		}
// 		printf("$%c\n", result[i]);
// 		printf("6) %d\n", count);
// 	printf("-------------------\n");
// 	}
// 	return (count);
// }

// char	*ft_subnstr(char *result, size_t n)
// {
// 	size_t	i;
// 	char	*substring;

// 	substring = malloc(sizeof(char) * n + 1); 
// 	if (!substring)
// 		return NULL;
// 	i = 0;
// 	while (i < n && result[i])
// 	{
// 		substring[i] = result[i];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }

// char	**split_syntax(char *result, char **tokens)
// {
// 	int		i;
// 	char	quote;
// 	int		j;
// 	int		start;
	
// 	i = 0;
// 	quote = '\0';
// 	j = 0;
// 	while (result[i])
// 	{
// 		if (result[i] == ' ' || result[i] == '\t')
// 		{
// 			while (result[i] == ' ' || result[i] == '\t')
// 			i++;
// 		}
// 		else if (result[i] == '\'' || result[i] == '"')
// 		{
// 			quote = result[i++];
// 			start = i;
// 			while (result[i] && result[i] != quote)
// 				i++;
// 			tokens[j++] = ft_subnstr(result + start, i - start);
// 			if (result[i])
// 				i++;
// 		}
// 		else if (result[i] == '>' || result[i] == '<')
// 		{
// 			if (result[i + 1] == result[i])
// 			{
// 				tokens[j++] = ft_subnstr(result + i, 2);
// 				i += 2;
// 			}
// 			else
// 			{
// 				tokens[j++] = ft_subnstr(result + i, 1);
// 				i++;
// 			}
// 		}
// 		else if (result[i] == '|')
// 		{
// 			tokens[j++] = ft_subnstr(result + i, 1);
// 			i++;
// 		}
// 		else if (result[i])
// 		{
// 			start = i;
// 			while (result[i] && result[i] != '<' && result[i] != '>' &&
// 				result[i] != '|' && result[i] != ' ' &&
// 				result[i] != '\t' && result[i] != '\'' && result[i] != '"')
// 				i++;
// 			tokens[j++] = ft_subnstr(result + start, i - start);
// 		}
// 	}
// 	tokens[j] = NULL;
// 	return (tokens);
// }

// char **ft_tokenize(char *result)
// {
// 	char	**tokens;
// 	int		length;
// 	length = ft_strlen(result);
// 	//!how do i determine the length of the array ?
// 	token_split(&tokens, result);
// 	if (!tokens)
// 	{
// 		ft_putstr_fd("Fail to tokenize", 2);
// 		exit (127);
// 	}
// 	return (tokens);
// }

t_token *tokenize_word(char *result, t_token *tokens) //!Could change this function for other purposes
{
	int		i;
	int		start;
	
	i = 0;
	start = 0;
	while (result[i])
	{
		if (result[i] == ' ' || result[i] == '\t')
		{
			while (result[i] == ' ' || result[i] == '\t')
				i++;
		}
		else if (result[i] && result[i] != ' ')
		{
			start = i;
			while (result[i] && result[i] != '<' && result[i] != '>' &&
				result[i] != '|' && result[i] != ' ' &&
				result[i] != '\t' && result[i] != '\'' && result[i] != '"')
					i++;
			if (tokens == NULL)
				tokens = create_node(tokens, result + start, i);
			else
				tokens = append_node(tokens, result + start, i);
		}
	}
	t_token	*temp = tokens;
	while (temp != NULL)
	{
		printf("node string is %s\n", temp->lexeme);
		temp = temp->next;
	}
	return (tokens);
}


void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->lexeme);
		free(temp);
	}
	free(tokens);
}

int main(int argc, char **argv)
{
	// if (argc < 2)
	// 	return (1);
	(void)argv;
	(void)argc;
	t_token	*token;
	
	while (1)
	{
		token = NULL;
		char *result = NULL;
		result = readline("minishell$ ");
		if (!result)
			break;
		add_history(result);
		token = tokenization(result, token);
		if (!token)
		{
			ft_putstr_fd("Fail to tokenize", 2);
			exit (127);
		}
		if (ft_strncmp(result, "exit", 4) == 0)
		{
			rl_clear_history();
			free_tokens(token);
			free(result);
			exit (EXIT_SUCCESS);
		}
		// tokens = split_syntax(result, tokens);
		// char **tokens = NULL;
		// tokens = ft_tokenize(result);
		int i = 0;
		t_token *ride = NULL;
		ride = token;
		while (ride != NULL)
		{
			printf("string %d: %s$\n", i, ride->lexeme);
			ride = ride->next;
			i++;
		}
		// free_tokens(tokens);
		printf("%s\n", result);
		free_tokens(token);
		free(result);
	}
	return (0);
}
