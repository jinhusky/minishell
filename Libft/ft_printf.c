/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:07:12 by jhor              #+#    #+#             */
/*   Updated: 2025/02/28 15:07:12 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_specifiers(char format, va_list *list)
{
	if (format == 'c')
		return (ft_print_char(va_arg(*list, int)));
	else if (format == 'p')
		return (ft_print_pointer(va_arg(*list, char *)));
	else if (format == 'u')
		return (ft_print_digit(va_arg(*list, unsigned int), "0123456789"));
	else if (format == 's')
		return (ft_print_str(va_arg(*list, char *)));
	else if (format == 'd')
		return (ft_print_digit(va_arg(*list, int), "0123456789"));
	else if (format == 'i')
		return (ft_print_digit(va_arg(*list, int), "0123456789"));
	else if (format == 'x')
		return (ft_print_lower_hexa(va_arg(*list, int)));
	else if (format == 'X')
		return (ft_print_upper_hexa(va_arg(*list, int)));
	else if (format == '%')
		return (ft_print_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	list;

	va_start(list, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i])
				count += format_specifiers(format[i], &list);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(list);
	return (count);
}

// int main()
// {
// 	char *str = NULL;

// 	ft_printf("%s\n", str);
// }

// int main()
// {
	// char *str = "13245";

	// ft_printf("%p\n", str);
	// printf("%p\n", str);

	// char c = 'c';
	// ft_printf("%c\n", c);
	// printf("%c\n", c);

	// unsigned int nbr = 1234;
	// ft_printf("%u\n", nbr);
	// printf("%u\n", nbr);

	// char *s = "Hello!";
	// ft_printf("%s\n", s);
	// printf("%s\n", s);

	// int nbr1 = 84587485;
	// int nbr2 = -84587485;
	// ft_printf("%d\n%d\n", nbr1, nbr2);
	// printf("%d\n%d", nbr1, nbr2);

	// int nbr2 = 8748;
	// ft_printf("%i\n", nbr2);
	// printf("%i\n", nbr2);

	// int lhexa = 42;
	// ft_printf("%x\n", lhexa);
	// printf("%x\n", lhexa);

	// int uhexa = 42;
	// ft_printf("%X\n", uhexa);
	// printf("%X\n", uhexa);

	// ft_printf("%%\n");
	// printf("%%\n");
// }