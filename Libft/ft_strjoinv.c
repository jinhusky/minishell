/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:50:49 by jhor              #+#    #+#             */
/*   Updated: 2025/04/17 16:50:49 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinv(int nbr, ...)
{
	va_list	p;
	char	*str;
	char	*temp;

	va_start(p, nbr);
	str = ft_strdup("");
	while (nbr--)
	{
		temp = str;
		str = ft_strjoin(str, va_arg(p, char *));
		free (temp);
	}
	va_end(p);
	return (str);
}

// int main()
// {
// 	char *str = "Hello";
// 	char *str1 = "There";
// 	char *str2 = "BYe==";

// 	char *ulti = ft_strjoinv(3, str, str1, str2);
// 	printf("%s", ulti);
// 	free(ulti);
// }