#include "../includes/minishell_lib.h"
#include "stdbool.h"

bool isSingleQuote(char c)
{
	return (c == '\'');
}

void passTilNextQuote(char *input, int *i) 
{
	if(!input[(*i)])
		return;
	(*i)++;
	while (!isSingleQuote(input[*i]))
		(*i)++;
	(*i)++;
}

void expander(t_data *data, char *input) 
{
	(void) data;
	int i;

	i = 0;
	while(input[i]) 
	{
		if (isSingleQuote(input[i]))
			passTilNextQuote(&input[i], &i);
		printf("%s\n", &input[i]);
		i++;
		// if (isHereDoc()) 
		// {
		// 	passVar();
		// } 
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

