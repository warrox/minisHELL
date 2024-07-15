/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:31:38 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 10:40:03 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

void	case_not_equal_pos(char **result, const char *s)
{
	result = malloc(2 * sizeof(char *));
	result[0] = ft_strdup(s);
	result[1] = NULL;
}

static char	*strdup_until(const char *str, char delimiter)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	while (str[len] && str[len] != delimiter)
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	**split_first_equal(const char *s)
{
	char	**result;
	char	*first_part;
	char	*second_part;
	char	*equal_pos;

	result = NULL;
	if (!s)
		return (NULL);
	equal_pos = ft_strchr(s, '=');
	if (!equal_pos)
	{
		case_not_equal_pos(result, s);
		return (result);
	}
	first_part = strdup_until(s, '=');
	second_part = ft_strdup(equal_pos + 1);
	result = malloc(3 * sizeof(char *));
	if (!result || !first_part || !second_part)
		return (free(first_part), free(second_part), free(result), NULL);
	result[0] = first_part;
	result[1] = second_part;
	result[2] = NULL;
	return (result);
}
