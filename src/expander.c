#include "../includes/minishell_lib.h"
#include "stdbool.h"
#include <stdio.h>

bool isSingleQuote(char c)
{
	return (c == '\'');
}

void passTilNextQuote(char *input, int *i) 
{
	(*i)++;
	while (input[*i] && !isSingleQuote(input[*i]))
		(*i)++;
	if(input[(*i)] != '\0')
	{
		(*i)++;
	}
}
bool isHereDoc(char *input, int*i)
{
	return(!ft_strncmp(&input[*i],"<<",2));
}

void passVarDoc(char *input, int *i)
{
	(*i) ++;
	while(input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		i++;
	// while(input[*i] &&)
}
void expander(t_data *data, char *input) 
{
	(void) data;
	int i;

	i = 0;
	while(input[i]) 
	{
		if (isSingleQuote(input[i]))
			passTilNextQuote(input, &i);
		if (isHereDoc(input, &i)) 
		{
			passVarDoc(input, &i);
		} 
		else 
			i++;
		// else if (isExitCode()) 
		// {
		// 	expandExitCode();
		// } 
		// else if (isVariable()) 
		// {
		// 	expandVariable();
		// }
	}
}

