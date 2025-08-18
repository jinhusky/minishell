/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:23:35 by jhor              #+#    #+#             */
/*   Updated: 2024/11/23 14:23:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//edge case to check for NULL in str
//count the length of str
//allocate memory space to input the result str
//edge check if the memory allocation is successful
//identify while the s is not empty
//loop through the string
//apply the function to each character in the new string
//retrun result str if successful and NULL if fail

#include "libft.h"

char	evenupper(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c - 32);
	return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*newstr;
	int		i;

	len = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	newstr = (char *)malloc((sizeof(char)) * (len + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

// int main()
// {
// 	char str[] = "hello there";
// 	char *result = ft_strmapi(str, evenupper);

// 	printf("%s\n", result);
// }