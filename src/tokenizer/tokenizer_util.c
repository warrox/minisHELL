#include "../../includes/minishell_lib.h"
#include <string.h>
int ft_is_oth_pipe(char *input, int i)
{
	i += 1;
	while(input[i] && input[i] != '|')
	{
		while(input[i] == ' ' || input[i] == '\t')
		{
			i++;
		}
		if(input[i] == '|')
		{
			return(1);
		}
		else
		{
			return(0);
		}
	}
	return(1);
} 
int	check_pipe(char *input, int i, t_data *data)
{
	int	flag;
	int	flag_s;

	data->signal->signal = NULL_INIT;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|' || ft_is_oth_pipe(input,i) == 1)
			{
				data->signal->signal = SYNTAX_ERROR;
				return(1); // to check
			}
			flag += 1;
		}
		i++;
	}
	if (input[i] == '\0' && flag >= 1)
	{
		return (0);
	}
	return (1);
}

int	checker_err_pipe(char *input, t_data *data)
{
	int	i;
	int	is_valid;
	int	not_valid;

	not_valid = 0;
	is_valid = 1;
	i = ZERO_INIT;
	while (input[i])
	{
		if (input[i] == '|')
			break ;
		i++;
	}
	if (input[i] == '\0')
		return (is_valid);
	if (check_pipe(input, i, data) == 0) // bloc inverse cense renvoye not valid
		return (is_valid);
	if (data->signal->signal != NULL_INIT)
		msg_error_handler(&data->signal->signal, data);
	return (not_valid);
}

char	*ft_strdup_cust(const char *source)
{
	int		i;
	char	*copied_s;

	i = 0;
	copied_s = malloc(ft_strlen(source) + 1);
	if (!copied_s)
		return (NULL);
	while (source[i])
	{
		while (source[i] == ' ' || source[i] == '\t')
			i++;
		copied_s[i] = source[i];
		i++;
	}
	copied_s[i] = '\0';
	return (copied_s);
}
// ------------------------------------

int	sign_cmp(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
}

