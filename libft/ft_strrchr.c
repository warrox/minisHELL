/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:39:06 by whamdi            #+#    #+#             */
/*   Updated: 2023/11/21 11:53:52 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
