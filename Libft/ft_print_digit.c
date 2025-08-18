/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:26:49 by jhor              #+#    #+#             */
/*   Updated: 2025/02/14 11:26:49 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_print_digit(long long num, char *base)
{
	int	base_len;
	int	count;

	count = 0;
	base_len = ft_strlen(base);
	if (num == 0)
		return (ft_print_char('0'));
	if (num < 0)
	{
		count += ft_print_char('-');
		num = (num * -1);
	}
	if (num >= base_len)
		count += ft_print_digit(num / base_len, base);
	count += ft_print_char((base[num % base_len]));
	return (count);
}
// ft_print_char(n % base_len - '0') - it does not handle the mapping correctly
// int main()
// {
// 	long nbr1 = -12345678812;
// 	char *basee = "0123456789";
// 	long nbr = 12345678812;
// 	ft_print_digit(nbr, basee);
// 	ft_print_digit(nbr1, basee);