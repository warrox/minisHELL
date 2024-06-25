
#include "../includes/minishell_lib.h"
#include <stdio.h>

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
	if (*signal == COMMAND_NOT_FOUND)
	{
		data->exit_status = 127;	
		ft_printf("command not found\n");
	}
	if (*signal == SYNTAX_ERROR)
	{
		data->exit_status = 2;
		ft_printf("syntax error\n");
	}
	if(*signal == UNEXPECTEDTOKEN)
	{
		data->exit_status = 2;
		printf("minishell: syntax error near unexpected token\n");
	}
	// add other signals in the future
}
