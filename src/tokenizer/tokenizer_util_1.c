#include "../../includes/minishell_lib.h"
#include <stdio.h>

int	ft_isws(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*get_filename(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*new;

	i = 0;
	while (str[i] && ft_isws(str[i]) == 1)
		i++;
	start = i;
	end = i;
	while (str[end] && !ft_isws(str[end]))
		end++;
	if (end == start)
		NULL; // CHECK
	new = ft_substr(str, start, end - start);
	return (new);
}

void	create_signed(t_list_arg *lst)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	lst->file_array = NULL;
	lst->file_array = ft_calloc(lst->count_size + 1, sizeof(char *));
	while (lst->input_splited[i])
	{
		tmp = sign_cmp(&lst->input_splited[i]);
		if(i > 1)
		{
			if(lst->input_splited[i - 1] == '\'')
			tmp = 0;
		}
		if (tmp != 0)
		{
			i += tmp;
			lst->file_array[j++] = get_filename(&lst->input_splited[i]);
		}
		else
			i++;
	}
}
