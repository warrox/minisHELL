#include "../../includes/libft.h"
#include "../../includes/minishell_lib.h"

static int	count_words(char const *str, char c)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (*str == c)
		{
			trigger = 0;
			if (count == 1)
				break;
		}
		str++;
	}
	if (count == 1)
		count = 2;
	return (count);
}

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
			break;
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

/*int	main(void)
{
	char	**res;
	int	i = 0;

	res = ft_split_tokenizer_space("cd <yo>", ' ');
	while (res[i])
	{
		printf("string[%d] = %s\n", i, res[i]);
		i++;
	}
	free_tab(res);
	return (0);
}*/

