/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:28:58 by whamdi            #+#    #+#             */
/*   Updated: 2023/11/22 11:17:12 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (s[i] == (unsigned char)searchedChar)
		{
			return ((void *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	*str;
	str = memchr("bonjourno", 'o', 1);
				if (!str)
						printf("NULL");
				else
						printf("%s",str);
}*/
