/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:50:36 by jhor              #+#    #+#             */
/*   Updated: 2024/11/18 17:50:36 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s1;
	char	*dup;
	int		i;

	s1 = ft_strlen(s);
	dup = (char *) malloc(sizeof(char) * (s1 + 1));
	i = 0;
	if (!dup)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int main()
// {
// 	char *str = "qweasdzxc";

// 	printf("%s", ft_strdup(str));
// 	printf("\n");

// 	return (0);
// }