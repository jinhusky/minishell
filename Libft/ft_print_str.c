/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:59:53 by jhor              #+#    #+#             */
/*   Updated: 2025/02/14 12:59:53 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

int	ft_print_str(char *s)
{
	size_t	len;

	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	len = ft_strlen(s);
	return (write(1, s, len));
}

//int main()
//{
//	char *str = NULL;
//	ft_print_str("");
//	ft_print_str(str);
//}