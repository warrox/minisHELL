/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:39:34 by whamdi            #+#    #+#             */
/*   Updated: 2024/05/03 15:14:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*news;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	news = (char *)malloc(sizeof(*s) * (len + 1));
	if (!news)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (i >= start && j < len)
		{
			news[j] = s[i];
			j++;
		}
	}
	news[j] = 0;
	return (news);
}

/*int	main(void)
{
	char	*copy;
	char	*s;

	copy = "Hello worldefekfjefjekfjekfeekljeklfjejkefjk";
	s = ft_substr(copy, 7, 10);
	printf("%s", s);
}*/
