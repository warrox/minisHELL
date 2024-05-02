/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:05 by whamdi            #+#    #+#             */
/*   Updated: 2023/11/22 11:18:16 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((unsigned char)searchedChar == string[i])
		{
			return ((char *)&string[i]);
		}
		if (string[i] == '\0')
		{
			break ;
		}
		i++;
	}
	return (NULL);
}
