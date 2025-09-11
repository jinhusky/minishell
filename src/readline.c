/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:00:15 by jhor              #+#    #+#             */
/*   Updated: 2025/09/11 18:16:18 by jhor             ###   ########.fr       */
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

// char **token_split(char *result, char **tokens) //!Could change this function for other purposes
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	while (result[i])
// 	{
// 		if ((result[i] >= 'A' && result[i] <= 'Z') || 
// 			(result[i] >= 'a' && result[i] <= 'z') || 
// 			result[i] == 34 || result[i] == 39)
// 				word_group(&tokens, result);
// 		i++;
// 	}
// }

// if (result is queal to character "" or '', call function to handle count for quoted strings)
// if (result is equal to character a to z plus '.' and the next is a space, add one count)
// if (result is equal to character > >> < << | all add on count)



int	token_count(char *result)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = '\0';
	while (result[i])
	{
		if (result[i] == ' ' || result[i] == '\t')
			i++;
		printf("$%c\n", result[i]);
		printf("1) %d\n", count);
		if (result[i] == '\'' || result[i] == '"')
		{
			quote = result[i++];
			if (quote != '\0')
				printf("%c\n", quote);
			while (result[i] && result[i] != quote)
				i++;
			count++;
			i++;
		}
		printf("$%c\n", result[i]);
		printf("2) %d\n", count);
		if (result[i] == '>')
		{
			if (result[i + 1] == '>') 
				i++;
			count++;
			i++;
		}
		printf("$%c\n", result[i]);
		printf("3) %d\n", count);
		if (result[i] == '<')
		{
			if (result[i + 1] == '<') 
				i++;
			count++;
			i++;
		}
		printf("$%c\n", result[i]);
		printf("4) %d\n", count);
		if (result[i] == '|')
		{
			count++;
			i++;
		}
		printf("$%c\n", result[i]);
		printf("5) %d\n", count);
		if (result[i] && result[i] != ' ')
		{
			while (result[i] && result[i] != '<' && result[i] != '>' &&
				result[i] != '|' && result[i] != ' ' &&
				result[i] != '\t')
				i++;
			count++;
		}
		printf("$%c\n", result[i]);
		printf("6) %d\n", count);
	printf("-------------------\n");
	}
	return (count);
}

// char	**split_syntax(char *result, char **tokens)
// {
// 	int	i;
// 	char	quote;

// 	i = 0;
// 	quote = NULL;
// 	while (result[i])
// 	{
// 		if (result[i] == ' ' || result[i] == '\t')
// 			i++;
// 		if (result[i] == '\'' || result[i] == '"')
// 		{
// 			quote = result[i++];
// 			while (result[i] && result[i] != quote)
// 				i++;
// 			count++;
// 			i++;
// 		}
		
// 	}
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

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int main(int argc, char **argv)
{
	// if (argc < 2)
	// 	return (1);
	(void)argv;
	(void)argc;
	
	while (1)
	{
		char *result = NULL;
		int count = 0;
		result = readline("minishell$ ");
		if (!result)
		break;
		add_history(result);
		count = token_count(result);
		// char **tokens = NULL;
		// tokens = ft_tokenize(result);
		// int i = 0;
		// while (tokens[i])
		// {
		// 	printf("%s\n", tokens[i]);
		// 	i++;
		// }
		// free_tokens(tokens);
		printf("%s\n", result);
		printf("%d\n", count);
		free(result);
	}
	return (0);
}
