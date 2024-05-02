/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:32:36 by whamdi            #+#    #+#             */
/*   Updated: 2023/11/22 11:17:27 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = (const char *)src;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	if (s < d && d < s + n)
	{
		s += n;
		d += n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	else
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	data[] = "Hello, World!";
	char	destination[20];

	ft_memmove(destination, data + 6, 6);
	printf("Source: %s\n", data + 6);
	printf("Destination: %s\n", destination);
	return (0);
}*/
