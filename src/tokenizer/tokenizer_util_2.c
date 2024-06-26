#include "../../includes/minishell_lib.h"
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

