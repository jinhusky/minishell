/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:21:37 by jhor              #+#    #+#             */
/*   Updated: 2024/11/13 18:21:37 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n > i && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i >= n)
		return (0);
	else
		return ((unsigned char)s1[i] - s2[i]);
}

// #include <string.h>
// int main ()
// {
// 	char str1 [] = "hello";
// 	char str2 [] = "helloX";

// 	printf("%d\n", ft_strncmp("test\200", "test\0", 6));
// 	// printf("%d\n", strncmp(str1, str2, 42) < 0);
// }