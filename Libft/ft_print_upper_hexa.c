/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_upper_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:37:47 by jhor              #+#    #+#             */
/*   Updated: 2025/02/28 16:37:47 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//hexadecimal is taking in a int and prints out a hexadecimal 

int	ft_print_upper_hexa(unsigned int nbr)
{
	unsigned int	num;

	num = ft_print_digit(nbr, "0123456789ABCDEF");
	return (num);
}

// int main()
// {
// 	unsigned int num = 1234;
// 	ft_print_upper_hexa(num);
// }