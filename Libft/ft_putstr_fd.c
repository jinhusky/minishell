/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:50:04 by jhor              #+#    #+#             */
/*   Updated: 2024/11/23 22:50:04 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

// int main()
// {
// 	char str[] = "Hello, there!";

// 	int fd = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);

// 	ft_putstr_fd(str, fd);
// }