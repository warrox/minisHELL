/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:39:58 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 18:06:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	ft_strstr(char *str, char *occ)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	if (!str || !occ)
		return (0);
	while (str[k])
	{
		i = k;
		j = 0;
		while (str[i] && str[i] == occ[j])
		{
			i++;
			j++;
		}
		if (!occ[j])
			return (1);
		k++;
	}
	return (0);
}
