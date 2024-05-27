/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:13:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/27 10:13:32 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell_lib.h"

static char	*word_dup(char const *str, int start, int finish)
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
		if (str[start] != '<' && str[start] != '>')
			word[j++] = str[start];
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

char	**split_fill_c(char const *s, char c, char **split)
{
	int	index;
	int	i;
	int	j;

	index = -1;
	i = -1;
	j = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && index < 0)
			index = i;
		else if (s[i] == c && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			if (!split[j - 1])
				return (free_tab(split));
			index = -1;
			break ;
		}
	}
	if (s[i] == c)
		i++;
	if (s[i] != '\0')
		split[j++] = word_dup(s, i, strlen(s));
	split[j] = NULL;
	return (split);
}

char	**split_tokenizer(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	split = split_fill_c(s, c, split);
	return (split);
}
