/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:56:01 by jhor              #+#    #+#             */
/*   Updated: 2024/11/13 17:56:01 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p = s + ft_strlen(s);

	if (s == NULL)
		return (NULL);
	while (p >= s)
	{
		if (*p == (char)c)
		{
			return ((char *)p);
		}
		p--;
	}
	return (0);
}

// #include <string.h>
// int main()
// {
// 	const char *str = "Hello, world!";

// 	// printf("%d\n", ft_strrchr(str, 'o'));
// 	// printf("%d\n", ft_strrchr(str, 0) == str + strlen(str));
// 	printf("%s\n", ft_strrchr(str, 'o'));
// 	return 0;
// }