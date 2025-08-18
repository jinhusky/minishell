/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:58:29 by jhor              #+#    #+#             */
/*   Updated: 2024/11/12 16:58:29 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	destsize;
	unsigned int	srclen;
	unsigned int	i;

	destsize = size;
	srclen = ft_strlen(src);
	i = 0;
	if (destsize == 0)
		return (srclen);
	while ((i < destsize - 1) && (src[i] != '\0'))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

// int main ()
// {
// 	char src [] = "Programmming";
// 	char dest [10];

// 	printf("%lu\n", ft_strlcpy(dest, src, 3));
// }