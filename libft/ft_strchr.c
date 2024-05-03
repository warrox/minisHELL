/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:05 by whamdi            #+#    #+#             */
/*   Updated: 2024/05/03 15:13:43 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
