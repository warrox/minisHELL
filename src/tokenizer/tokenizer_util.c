#include "../../includes/minishell_lib.h"
#include <stdio.h>
bool ifPipe(char c)
{
	return(c == '|');
} 
int pipeAlone(char *input, int i)
{
	i++;
	while(ft_isws(input[i]))
		i++;
	if(input[i] && ft_isascii(input[i]))
		return(0);
	return(-1);
}
bool redirsign(char c)
{
	return(c == '<' || c == '>');	
}

int fileAfterRedirSign(char *input, int i)
{
	i++;
	while(ft_isws(input[i]))
		i++;
	if(input[i] && ft_isascii(input[i]))
		return(0);
	return(-1);

}
int	unexpectedToken(char *input)
{
	int i;
	int signal;

	signal = 0;
	i = 0;
	while(input[i])
	{
		if(ifPipe(input[i]) || redirsign(input[i]))
		{
			if(pipeAlone(input, i) == -1 || fileAfterRedirSign(input, i) == -1)
			{
				signal = SYNTAX_ERROR;
				msg_error_handler(&signal);
				return(-1);
			}
		}
		// if(redirsign(input[i]))
		// {
		// 	if(fileAfterRedirSign(input,i)== -1)
		// 	{
		// 		signal = SYNTAX_ERROR;
		// 		msg_error_handler(&signal);
		// 		return(-1);
		// 	}
		// }
		i++;
	}
	return(0);
}

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

