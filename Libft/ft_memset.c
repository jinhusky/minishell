/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:11:16 by jhor              #+#    #+#             */
/*   Updated: 2024/11/11 00:11:16 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief memory block manipulation
 * @param pointer s, integer x, size of memory n
 * @return replacement of data types values
*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	int				index;

	p = (unsigned char *)s;
	index = 0;
	while (n--)
		p[index++] = (unsigned char)c;
	return ((char *)p);
}

// int main ()
// {
// 	char str[50] = "Internationally responsive";

// 	ft_memset(str + 15, 'r', 8*sizeof(char));

// 	printf("%s\n", str);

// 	return (0);
// }