#include "../../includes/minishell_lib.h"

int check_pipe(char *input, int i,t_data *data)
{
	data->signal->signal = NULL_INIT;
	int flag;
	int flag_s;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '|')
		{
			if(input[i + 1] == '|')
				break; // to check
			flag += 1;
		}
		i++;
	}
	if(input[i] == '\0' && flag >= 1)
		return(0);
	data->signal->signal = SYNTAX_ERROR; 
	return(1);

}

int checker_err_pipe(char *input,t_data *data)
{
	int i;
	int is_valid;
	int not_valid;
	
	not_valid = 0;
	is_valid = 1;
	i = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '|')
			break;
		i++;
	}
	if(input[i] == '\0')
		return(is_valid);
	if(check_pipe(input,i,data) == 0) // bloc inverse cense renvoye not valid
		return(is_valid);

	if(data->signal->signal != NULL_INIT)	
		msg_error_handler(&data->signal->signal,data);
	return(not_valid);
}


