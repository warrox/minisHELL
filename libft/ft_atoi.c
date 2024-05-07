/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:06:01 by whamdi            #+#    #+#             */
/*   Updated: 2024/05/03 15:11:39 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nbr)
{
	long	result;
	long	sign;

	sign = 1;
	result = 0;
	while (*nbr && (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13)))
		++nbr;
	if (*nbr && (*nbr == '-' || *nbr == '+'))
	{
		if (*nbr++ == '-')
			sign *= -1;
	}
	while (*nbr && (*nbr >= '0' && *nbr <= '9'))
		result = (*nbr++ - '0') + result * 10;
	return (result * sign);
}

/*int	main(void)
{
	char *s = "-1234";
	int test = ft_atoi(s);
	__builtin_printf("%d", test);
}*/
