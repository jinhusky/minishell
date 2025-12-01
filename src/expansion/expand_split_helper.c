/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:05:14 by jhor              #+#    #+#             */
/*   Updated: 2025/12/01 11:05:51 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**token_append(char **arr, char *sub, int *count)
{
	char	**new;
	int		i;

	new = NULL;
	i = 0;
	new = malloc(sizeof(char *) * (*count + 2));
	if (!new)
	{
		free(arr);
		return (NULL);
	}
	while (i < *count)
	{
		new[i] = arr[i];
		i++;
	}
	new[i++] = sub;
	new[i] = NULL;
	free(arr);
	(*count)++;
	return (new);
}

char	*substring_split(char *result, int start, int end)
{
	char	*str;
	int		i;
	
	str = NULL;
	i = 0;
	// printf("*substring_split* end:%d\n", end);
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = result[start];
		start++;
		i++;
	}
	str[i] = '\0';
	// printf("*substring_split* str:%s\n", str);
	return (str);
}