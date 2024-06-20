
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
	(void)data;
	if (*signal == COMMAND_NOT_FOUND)
		ft_printf("command not found\n");
	if (*signal == SYNTAX_ERROR)
	{
		ft_printf("syntax error\n");
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
int check_quote_2(int flag_s,int flag,t_data *data)
{
	if(flag_s == 1)
	{
		data->signal->signal = SYNTAX_ERROR;
		msg_error_handler(&data->signal->signal, data);
		return(0);
	}
	if(flag == 0)
		return(1);
		
	if(flag == 1)
	{
		data->signal->signal = SYNTAX_ERROR;
		msg_error_handler(&data->signal->signal, data);
	}
	return(3);
}

int check_single_q(char c,int *flag, int *i)
{
	if (c == '\'')
	{
		*flag += 1;
		while(c == '\"')
			i++;
		if (*flag == 2)
		return (2);
	}
	return(0);
} 

int	check_quote(char *input, int i, t_data *data)
{
	int	flag;
	int	flag_s;

	data->signal->signal = NULL_INIT;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	i = 0;
	while (input[i])
	{
		if(check_single_q(input[i],&flag,&i) == 2)
			return(1);
		if (input[i] == '\"')
		{	
			flag_s += 1;
			while(input[i] == '\'')
				i++;
			if(flag_s == 2)
				return(1);
		}
		i++;
	}
	i = check_quote_2(flag_s, flag, data);
	if(i == 1 || i == 2)
		return(1);
	return (0);
}
