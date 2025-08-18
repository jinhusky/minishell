/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:02:47 by jhor              #+#    #+#             */
/*   Updated: 2024/11/19 23:02:47 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_strchr(set, s1[j - 1]))
		j--;
	str = (char *) malloc(sizeof(char) * (j - i + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1 + i, j - i);
	str[j - i] = '\0';
	return (str);
}
// int main()
// {
// char str[] = "abbbaafdgaWhats upafgdggdbbaaa";

// printf("%s\n", ft_strtrim(str, "abfdg"));
// }