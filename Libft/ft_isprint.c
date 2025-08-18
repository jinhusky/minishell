/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:46:45 by jhor              #+#    #+#             */
/*   Updated: 2024/11/26 17:49:49 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief check printable characters
 * @param c character
 * @return 1 is true or 0 false
*/

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*int main ()
{
	int a = ' ';
	int b = '~';

	printf("%d", ft_isprint(a));
	printf("%d", ft_isprint(b));
}*/