/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:36:05 by whamdi            #+#    #+#             */
/*   Updated: 2023/12/13 18:09:51 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>

int	ft_putchar_custom(int c, int fd);

int	ft_putnbr_fd(int n, int fd);
int	put_nbr_u_dec(unsigned int n, int fd);
int	ft_putstr_fd(char *s, int fd);
int	hex_convert(unsigned int int_to_convert);
int	hex_convert_u(unsigned int int_to_convert);
int	ft_print_pointer_address(uintptr_t ptr);
int	ft_printf(const char *format, ...);
int	convert_ptr_to_hex(uintptr_t int_to_convert);
#endif