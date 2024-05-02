/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:44:32 by whamdi            #+#    #+#             */
/*   Updated: 2023/12/13 10:23:46 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_custom(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	count_digits(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 10)
		return (1);
	while (nbr >= 10 || nbr >= 1)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	int		digit_count;
	int		j;

	nbr = n;
	j = 0;
	if (nbr < 0)
	{
		ft_putchar_custom('-', fd);
		nbr = -nbr;
		j = 1;
	}
	digit_count = count_digits(nbr);
	if (nbr < 10)
		ft_putchar_custom(nbr + '0', fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_custom(nbr % 10 + '0', fd);
	}
	return (digit_count + j);
}

int	put_nbr_u_dec(unsigned int n, int fd)
{
	unsigned long	nbr;
	int				digit_count;

	nbr = n;
	digit_count = count_digits(nbr);
	if (nbr >= 10)
	{
		put_nbr_u_dec(nbr / 10, fd);
	}
	ft_putchar_custom(nbr % 10 + '0', fd);
	return (digit_count);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
