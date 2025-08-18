/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:46:45 by jhor              #+#    #+#             */
/*   Updated: 2024/11/18 21:46:45 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if (*substr == '\0')
		return ((char *)str);
	i = 0;
	while (i < n && str[i] != '\0')
	{
		if (str[i] == substr[0])
		{
			j = 0;
			while (str[i + j] == substr[j] && substr[j] != '\0' && i + j < n)
				j++;
			if (substr[j] == '\0')
				return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	char str1 []= "Welcome Home";
// 	char substr1 [] = "come";

// 	printf("%s", ft_strnstr(str1, substr1, 10));
// }