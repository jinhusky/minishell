/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:24:50 by jhor              #+#    #+#             */
/*   Updated: 2024/11/28 21:26:26 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* @brief counting str char
* @param char string
* @return return i when finish counting
*/

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main ()
// {
// 	char *str1 = "abcdefuirythgnblkyasd";
// 	printf("%ld\n", ft_strlen(str1));
// 	return (0);
// }