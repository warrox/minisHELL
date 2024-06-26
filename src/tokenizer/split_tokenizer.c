/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:13:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 14:44:28 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell_lib.h"

static char	*word_dup(char const *str, int start, int finish, t_data *data)
{
	char	*word;
	int		i;
	int		j;

	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (start < finish)
	{
		if ((str[start] == '<' || str[start] == '>') && data->pansement == 1)
			word[j] = str[start];
		else if((str[start] == '<' || str[start] == '>') && data->pansement == 0)
			start++;
		word[j] = str[start];
		j++;
		start++;
	}
	word[j] = '\0';
	return (word);
}

static void	*free_tab(char **split)
{
	size_t	j;

	j = 0;
	while (split[j] != NULL)
	{
		free(split[j]);
		j++;
	}
	free(split);
	return (NULL);
}

char	**split_fill_c(char const *s, char c, char **split, t_data *data)
{
	int	index;
	int	j;

	index = -1;
	data->i = -1;
	j = 0;
	while (s[++data->i] != '\0')
	{
		if (s[data->i] != c && index < 0)
			index = data->i;
		else if (s[data->i] == c && index >= 0)
		{
			split[j++] = word_dup(s, index, data->i, data);
			if (!split[j - 1])
				return (free_tab(split));
			index = -1;
			break ;
		}
	}
	if (s[data->i] == c)
		data->i++;
	if (s[data->i] != '\0')
		split[j++] = word_dup(s, data->i, strlen(s), data);
	split[j] = NULL;
	return (split);
}

char	**split_tokenizer(char const *s, char c, t_data *data)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	split = split_fill_c(s, c, split, data);
	return (split);
}
