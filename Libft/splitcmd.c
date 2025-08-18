/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:20:30 by jhor              #+#    #+#             */
/*   Updated: 2025/07/14 22:20:30 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	wordcount(const char *str, int c)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] == c)
			j++;
		if (str[j] != c && str[j])
			count++;
		while (str[j] != c && str[j])
			j++;
	}
	return (count);
}

// int main()
// {
// 	char *str1 = "Hello world";
// 	printf("%d\n", wordcount(str1, 'o'));
// }

char	**splitcmd(char *str, char c)
{
	char	**s;
	int		i;
	int		wordlen;

	i = 0;
	if (!str)
		return (NULL);
	s = (char **)malloc(sizeof(char *) * (wordcount(str, c) + 1));
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str != c && str)
		{
			if (!ft_strchr(str, c))
				wordlen = ft_strlen(str);
			else
				wordlen = ft_strchr(str, c) - str;
			s[i] = ft_substr(str, 0, wordlen);
			i++;
			str += wordlen;
		}
	}
	s[i] = NULL;
	return (s);
}

// int main()
// {
// 	char *str1 = "Hello world over orian";
// 	char **output = splitcmd(str1, 'o');
// 	int index = 0;

// 	while (output[index])
// 	{
// 		printf("%s\n", output[index]);
// 		index++;
// 	}
// }