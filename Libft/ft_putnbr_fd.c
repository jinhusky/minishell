/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:47:34 by jhor              #+#    #+#             */
/*   Updated: 2024/11/23 20:47:34 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	nbr = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd((char)(nbr % 10) + '0', fd);
}

// int main ()
// {
//  // Open the file with write-only access. If it doesn't exist, create it.
// 	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	// Check if the file opened successfully
// 	if (fd == -1) {
// 		perror("Error opening file");
// 		return 1;
// 	}

// 	// Write the number -42 to the file
// 	ft_putnbr_fd(-42, fd);

// 	// Close the file
// 	close(fd);

// 	return 0;
// }