/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:08:52 by whamdi            #+#    #+#             */
/*   Updated: 2023/12/13 18:16:58 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_convert_u(unsigned int int_to_convert)
{
	char			*hex;
	int				i;
	unsigned long	rest;
	int				counter;
	char			result[9];

	counter = 0;
	hex = "0123456789ABCDEF";
	rest = 0;
	i = 8;
	result[i--] = '\0';
	if (int_to_convert == 0)
	{
		result[i] = '0';
		counter += ft_putchar_custom(result[i], 1);
	}
	while (int_to_convert != 0)
	{
		rest = int_to_convert % 16;
		result[i--] = hex[rest];
		int_to_convert /= 16;
	}
	while (result[++i] != '\0')
		counter += ft_putchar_custom(result[i], 1);
	return (counter);
}

int	hex_convert(unsigned int int_to_convert)

{
	unsigned long	rest;
	char			result[9];
	char			*hex;
	int				i;
	int				counter;

	counter = 0;
	hex = "0123456789abcdef";
	rest = 0;
	i = 8;
	result[i--] = '\0';
	if (int_to_convert == 0)
	{
		result[i] = '0';
		counter += ft_putchar_custom(result[i], 1);
	}
	while (int_to_convert != 0)
	{
		rest = int_to_convert % 16;
		result[i--] = hex[rest];
		int_to_convert /= 16;
	}
	while (result[++i] != '\0')
		counter += ft_putchar_custom(result[i], 1);
	return (counter);
}

int	convert_ptr_to_hex(uintptr_t int_to_convert)
{
	char				*hex;
	int					i;
	unsigned long long	rest;
	int					counter;
	char				result[17];

	counter = 0;
	hex = "0123456789abcdef";
	rest = 0;
	i = 16;
	result[i--] = '\0';
	if (int_to_convert == 0)
		result[i] = '0';
	while (int_to_convert != 0)
	{
		rest = int_to_convert % 16;
		result[i--] = hex[rest];
		int_to_convert /= 16;
	}
	while (result[++i] != '\0')
	{
		ft_putchar_custom(result[i], 1);
		++counter;
	}
	return (counter + 2);
}

int	ft_print_pointer_address(uintptr_t ptr)
{
	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	ft_putstr_fd("0x", 1);
	return (convert_ptr_to_hex(ptr));
}
