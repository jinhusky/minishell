/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:46:48 by jhor              #+#    #+#             */
/*   Updated: 2024/11/19 13:46:48 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	unsigned int	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (start + len >= s_len)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// int main()
// {
// 	char str[] = "Welcome World";

// 	printf("%s\n", ft_substr(str, 6, 7));
// }

//char	*ft_substr(char const *s, unsigned int start, size_t len)
//{
//	unsigned int	i;
//	char			*substr;
//	unsigned int	s_len;

//	if (s == NULL)
//		return (NULL);
//	s_len = ft_strlen(s);
//	if (start >= s_len)
//		len = 0;
//	else if (start + len > s_len)
//		len = s_len - start;
//	substr = (char *)malloc(sizeof(char) * (len + 1));
//	if (substr == NULL)
//		return (NULL);
//	if (start >= s_len)
//	{
//		substr[0] = '\0';
//		return(substr);
// 	}
//	i = 0;
//	while (i < len && s[start + i])
//	{
//		substr[i] = s[i + start];
//		i++;
//	}
//	substr[i] = '\0';
//	return (substr);
//}
