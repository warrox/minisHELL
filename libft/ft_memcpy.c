/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:32:28 by whamdi            #+#    #+#             */
/*   Updated: 2023/11/22 11:17:22 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t	i;
	char	*p_source;
	char	*p_destination;

	if (!destination && !(char *)source)
		return (NULL);
	i = 0;
	p_source = (char *)source;
	p_destination = (char *)destination;
	while (i < size)
	{
		p_destination[i] = p_source[i];
		i++;
	}
	destination = p_destination;
	return (destination);
}
