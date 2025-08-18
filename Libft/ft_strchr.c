/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:51 by jhor              #+#    #+#             */
/*   Updated: 2024/11/26 17:34:21 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (0);
}

// int main() {
// 	const char *str = "Hello, world!";
// 	char *ptr = ft_strchr(str, 'o');

// 	if (*ptr != '\0') {
// 		printf("%s\n", ptr);
// 	}
// 	return 0;
// }
