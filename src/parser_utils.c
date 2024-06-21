
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

void	msg_error_handler(int *signal)
{
	if (*signal == COMMAND_NOT_FOUND)
		ft_printf("command not found\n");
	if (*signal == SYNTAX_ERROR)
	{
		ft_printf("syntax error\n");
	}
	// add other signals in the future
}
