#include "../../includes/libft.h"
#include "../../includes/minishell_lib.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
	{
		if((str[i] == '<' && str[i+ 1] == '>') || ((str[i] == '>' && str[i+ 1] == '>')))
			i++;
		word[i++] = str[start++];
	}
	word[i] = '\0';
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

char	**split_fill_tokenizer(char const *s, char c, char **split)
{
	size_t	j;
	int		index;
	int		i;

	index = -1;
	i = -1;
	j = 0;
	while (++i <= (int)ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			if (!split[j - 1])
				return (free_tab(split));
			index = -1;
		}
	}
	split[j] = NULL;
	return (split);
}

char	**split_tokenizer(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = split_fill_tokenizer(s, c, split);
	return (split);
}

