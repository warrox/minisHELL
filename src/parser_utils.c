
#include "../includes/minishell_lib.h"

t_data	*init_signal(t_data *data)
{
	data->signal = (t_signal *)malloc(sizeof(t_signal));
	if (!data->signal)
		return (NULL);
	data->signal->signal = ZERO_INIT;
	return (data);
}

void	msg_error_handler(int *signal, t_data *data)
{
	(void)data;
	if (*signal == COMMAND_NOT_FOUND)
		printf("command not found\n"); // ecrire dans le stderror.
	if (*signal == SYNTAX_ERROR)
	{
		printf("syntax error\n");
		// display_prompt(data);//DINGUERIE HERE IS WHY ADD HISTORY DOESTN WORK CORRECTLY
	}
	// add other signals in the future
}
int	check_if_quote_at_end(char c, char *input, int i)
{
	while (input[i])
	{
		if (input[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int	check_quote(char *input, int i, t_data *data)
{
	int	flag;
	int	flag_s;

	data->signal->signal = NULL_INIT;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (flag == 2)
				return (1);
			flag += 1;
		}
		//["]["]["]
		if (input[i] == '\"')
		{
			if (flag_s == 2)
			{
				if (check_if_quote_at_end('\"', input, i))
				{
					flag_s -= 1;
				}
				return (1);
			}
			flag_s += 1;
		}
		i++;
	}
	if (flag % 2 != 0 || flag_s == 1)
		data->signal->signal = SYNTAX_ERROR;
	return (0);
}
