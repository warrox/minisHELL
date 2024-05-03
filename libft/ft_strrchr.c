/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:39:06 by whamdi            #+#    #+#             */
/*   Updated: 2024/05/03 15:14:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	len;

	len = ft_strlen(string);
	while (string[len] != ((unsigned char)searchedChar))
	{
		if (len == 0 && string[len] != searchedChar)
		{
			return ((char *)0);
		}
		len--;
	}
	return ((char *)&string[len]);
}
