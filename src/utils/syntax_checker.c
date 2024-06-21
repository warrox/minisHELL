#include "../../includes/minishell_lib.h"
void init_check_quote(int *i,int *first_enter, int *flag_s, int *flag_d, int *signal)
{
	(*i) = 0;
	(*flag_s) = 0;
	(*flag_d) = 0;
	(*first_enter) = 0;
	(*signal) = 0;
}

int single_quote(char c)
{
	if(c == '\'')
		return(1);
	return(0);
}

int double_quote(char c)
{
	if(c == '\"')
		return(1);
	return(0);
}

int find_first_double(char *input)
{
	int i;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\"')
			break;
		i++;
	}
	return(i);
}


int find_first_single(char *input)
{
	int i;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\'')
			break;
		i++;
	}
	return(i);
}
void check_single(char *input)
{
	int i;
	int flag;
	int signal;
	signal = 0;
	flag = 0;
	i = 0;
	
	while(input[i])
	{			
		flag += single_quote(input[i++]);
	}
	if(flag % 2 != 0)
	{
		signal = SYNTAX_ERROR;
		msg_error_handler(&signal);
	}
}

void check_double(char *input)
{
	int i;
	int flag;
	int signal;
	signal = 0;
	flag = 0;
	i = 0;
	
	while(input[i])
	{			
		flag += double_quote(input[i++]);
	}
	if(flag % 2 != 0)
	{
		signal = SYNTAX_ERROR;
		msg_error_handler(&signal);
	}

}

int check_quote(char *input)
{
	int i;
	int first_enter;
	int flag_s;
	int flag_d;
	int signal;
	init_check_quote(&i, &first_enter, &flag_s, &flag_d, &signal);
	flag_d = find_first_double(input);
	flag_s = find_first_single(input);
	if(flag_s < flag_d)
		check_single(input);
	if(flag_d < flag_s)
		check_double(input);
	return(0);
}

int syntax_checker(char *input)
{
	if(unexpectedToken(input) != 0  || check_quote(input) != 0) // ajouter check pipe 
		return(-1);
	return(0);
}

