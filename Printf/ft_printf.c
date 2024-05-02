/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:48:49 by whamdi            #+#    #+#             */
/*   Updated: 2023/12/13 18:10:45 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_detector(const char *format, va_list params)
{
	int	i;

	i = 0;
	if (format[0] == 'c')
		i = ft_putchar_custom((char)va_arg(params, int), 1);
	if (format[0] == 's')
		i = ft_putstr_fd((char *)va_arg(params, char *), 1);
	if (format[0] == 'x')
		i = hex_convert((int)va_arg(params, int));
	if (format[0] == 'X')
		i = hex_convert_u((int)va_arg(params, int));
	if (format[0] == 'i' || format[0] == 'd')
		i = ft_putnbr_fd((int)va_arg(params, int), 1);
	if (format[0] == '%')
	{
		write(1, "%", 1);
		i = 1;
	}
	if (format[0] == 'u')
		i = put_nbr_u_dec((unsigned int)va_arg(params, unsigned int), 1);
	if (format[0] == 'p')
	{
		i = ft_print_pointer_address(va_arg(params, uintptr_t));
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		counter;
	va_list	params;

	va_start(params, format);
	i = 0;
	counter = 0;
	if (!format)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			i++;
			counter++;
		}
		if (format[i] == '%')
		{
			counter += ft_format_detector(&format[i + 1], params);
			i = i + 2;
		}
	}
	va_end(params);
	return (counter);
}

// #include <limits.h>

// int	main(void)
// {
// 	ft_printf(" %p %p \n", INT_MIN, INT_MAX);
// 	printf(" %p %p ", (void *)INT_MIN, (void *)INT_MAX);
//   return(0);
// }
