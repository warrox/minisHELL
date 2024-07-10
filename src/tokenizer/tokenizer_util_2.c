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

void init_quote(t_quote *tool_box, char *str)
{
    tool_box->len = strlen(str);
    tool_box->start = 0;
    tool_box->end = tool_box->len - 1;
    tool_box->sf = 0;
    tool_box->df = 0;
}

void free_cleaned_array(char **array)
{
    if (array == NULL) return;
    for (int i = 0; array[i] != NULL; i++) 
    {
        free(array[i]);
    }
    free(array);
}

void free_cleaned_str(char *str)
{
    if (str) 
    {
        free(str);
    }
}



