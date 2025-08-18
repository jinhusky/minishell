/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:40:24 by jhor              #+#    #+#             */
/*   Updated: 2025/02/28 16:40:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// In printf, a pointer can be print out by creating a pointer variable

unsigned long	ft_print_digit1(unsigned long n, char *base) //643
{
	unsigned int	count;
	size_t			base_len;

	count = 0;
	base_len = ft_strlen(base);
	if (n < base_len)
		return (ft_print_char(base[n]));
	if (n >= base_len)
		count += ft_print_digit1((n / base_len), base);
	return (count + ft_print_digit1((n % base_len), base));
}

unsigned long	ft_print_pointer(void *num)
{
	int	nbr;

	nbr = 0;
	if (!num)
		return (ft_print_str("(nil)"));
	ft_print_str("0x");
	nbr += ft_print_digit1((unsigned long)num, "0123456789abcdef");
	return (nbr + 2);
}

// int main()
// {
// 	long x = 5;
// 	ft_print_pointer(&x);
// 	printf("\n%p\n", &x);
// }
// declare long type call 'nbr'

// if str is null, if it is then end the function

// print out "0x" by explicitly command to print out "0x"

// print out the rest of the address by printing out the digits 

//in hexadecimals by a call fucntion (ft_print_digit)

// return 'nbr' to print out the address

// #include <stdio.h>

// int main()
// {
// 	int i = 16;
// 	//char *str = "abcdef";
// 	printf("the address of this is %p\n", 16);
// 	ft_printf("the address of this is %p\n", 16);
// }