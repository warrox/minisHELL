#include "../../includes/minishell_lib.h"
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
int tripleSignDetector(char *input,int i)
{
	if(ft_strncmp(&input[i], "<<<", 3)== 0 || ft_strncmp(&input[i], "<<>", 3) == 0 
		|| ft_strncmp(&input[i], ">>>", 3) == 0 ||ft_strncmp(&input[i], ">><", 3) == 0)
	{
		return(-1);
	}
	return(0);	
} 
int	unexpectedToken(char *input, t_data *data)
{
	int i;
	int signal;
	int flag;

	flag = 0;
	signal = 0;
	i = 0;
	while(input[i])
	{
		if(input[i] == '\"')
			flag += 1;
		if(if_pipe(input[i]) || redirsign(input[i]))
		{
			if(pipe_alone(input, i) == -1 || fileAfterRedirSign(input, i) == -1)
			{
				signal = SYNTAX_ERROR;
				msg_error_handler(&signal, data);
				return(-1);
			}
			if(tripleSignDetector(input, i) == -1 && flag == 0)
			{
				signal = UNEXPECTEDTOKEN;
				msg_error_handler(&signal, data);
				return(-1);

			}
		}	
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

