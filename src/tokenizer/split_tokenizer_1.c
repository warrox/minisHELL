#include "../../includes/minishell_lib.h"

int	to_next_q(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i + 1);
}

void	write_part(const char *str, char *result, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
}
