#include "../../includes/minishell_lib.h"

void init_check_quote(int *i, int *first_enter, int *flag_s, int *flag_d, int *signal)
{
    (*i) = 0;
    (*flag_s) = 0;
    (*flag_d) = 0;
    (*first_enter) = 0;
    (*signal) = 0;
}

int is_single_quote(char c)
{
    return (c == '\'');
}

int is_double_quote(char c)
{
    return (c == '\"');
}

void check_quotes(char *input, int *flag_s, int *flag_d, int *signal)
{
    int i = 0;
    while (input[i])
    {
        if (is_double_quote(input[i]) && (*flag_s == 0))
            *flag_d = !(*flag_d);
        else if (is_single_quote(input[i]) && (*flag_d == 0))
            *flag_s = !(*flag_s);
        i++;
    }
    if (*flag_s || *flag_d)
        *signal = SYNTAX_ERROR;
}

int check_quote(char *input)
{
    int flag_s; 
	int flag_d; 
	int signal;
    int i;
	int first_enter;
	
	first_enter = 0;
	i = 0;
	init_check_quote(&i, &first_enter, &flag_s, &flag_d, &signal);
    check_quotes(input, &flag_s, &flag_d, &signal);
    if (signal == SYNTAX_ERROR)
    {
        msg_error_handler(&signal);
        return (-1);
    }
    return (0);
}

int syntax_checker(char *input, t_data *data)
{
    if (unexpectedToken(input) != 0 || check_quote(input) != 0)
	{
		data->exit_status = 2;	
		return (-1);
	} 
    return (0);
}
