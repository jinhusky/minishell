/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:33:51 by jhor              #+#    #+#             */
/*   Updated: 2024/11/11 14:33:51 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//handles overlapping issues when copying from src to dest 

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	unsigned int	i;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	i = 0;
	if (pdest <= psrc)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	else if (pdest > psrc)
	{
		i = n;
		while (i > 0)
		{
			pdest[i - 1] = psrc[i - 1];
			i--;
		}
	}
	return (dest);
}

// void *ft_memmove(void *dest, const void *src, size_t n)
// {
//     unsigned char *pdest;//     unsigned char *psrc;

//     // Check for NULL pointers
//     if (!dest && !src)
//         return (NULL);

//     pdest = (unsigned char *)dest;
//     psrc = (unsigned char *)src;

//     // Handle overlapping memory regions
//     if (pdest < psrc)
//     {
//         // Copy from left to right (forward)
//         for (size_t i = 0; i < n; i++)
//             pdest[i] = psrc[i];
//     }
//     else if (pdest > psrc)
//     {
//         // Copy from right to left (backward) to handle overlapping
//         for (size_t i = n - 1; i > 0; i--)
//             pdest[i] = psrc[i];
//     }
//     return (dest);
// }

// #include <string.h>
// int main()
// {
// 	char str[] = "Hello";

// 	ft_memmove(str + 3, str, 3);
// 	// memmove(str + 1, str, 1);

// 	printf("%s\n", str + 3);
// }