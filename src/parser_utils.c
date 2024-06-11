
#include "../includes/minishell_lib.h"
#include <readline/history.h>

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
int	check_quote(char *input, int i, t_data *data) // revoir la logique do not work when echo '"'
{
	int	flag;
	int	flag_s;

	data->signal->signal = NULL_INIT;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			flag += 1;
			while(input[i] == '\"')
				i++;
			if (flag == 2)
				return (1);
		}
		//["]["]["]
		if (input[i] == '\"')
		{
			if(input[i] == '\'')
				flag = 0;
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
	// if (flag % 2 != 0 || flag_s == 1)
	// {
	// 	data->signal->signal = SYNTAX_ERROR;
	// 	return(1);
	// }
	if(flag_s == 1)
	{
		data->signal->signal = SYNTAX_ERROR;
		msg_error_handler(&data->signal->signal, data);
		return(0);
	}
	if(flag == 0)
		return(1);

	data->signal->signal = SYNTAX_ERROR;
	msg_error_handler(&data->signal->signal, data);
	return (0);
}
