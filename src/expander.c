#include "../includes/minishell_lib.h"
#include "stdbool.h"
#include <stdio.h>


bool isExitCode(char *input, int *i)
{
	return(!ft_strncmp(&input[*i],"$?", 2));
}
bool isSingleQuote(char c)
{
	return (c == '\'');
}

char *passTilNextQuote(char *input, int *i, char *buffer) 
{
	int j;
	j = 0;
	(*i)++;
	while (input[*i] && !isSingleQuote(input[*i]))
	{
		buffer[j] = input[(*i)];
		(*i)++;
		j++;
	}
	if(input[(*i)] != '\0')
	{
		(*i)++;
	}
	return(buffer);
}
bool isHereDoc(char *input, int*i)
{
	return(!ft_strncmp(&input[*i],"<<",2));
}

void passVarDoc(char *input, int *i, char *buffer)
{
	int j;
	
	j = 0;
	while(j != 2)
		buffer[j++] = input[(*i)++];
	// (*i)  += 2;
	while(input[*i] && ft_isws(input[*i]))
		(*i)++;
	while(input[*i] && !ft_isws(input[*i]))
	{
		buffer[j] = input[(*i)++];
		(*i)++;
		j++;
	}
}

bool isVariable(char *input,int *i)
{
	return(!ft_strncmp(&input[*i], "$", 1));
}

void expandVariable(t_data *data, char *input, int *i, char *buffer)
{
	(*i)++;
	t_list_arg *current;
	int j;
	int buffer_len;
	size_t key_len;

	key_len = 0;
	j = 0;

	current = data->lst;
	buffer_len = ft_strlen(buffer);
	printf("COMBIEN : %d\n",buffer_len);
	while (current)
    {
        key_len = ft_strlen(current->key_and_val[0]);
        if (!ft_strncmp(&input[*i], current->key_and_val[0], key_len))
        {
            while(j++ < buffer_len)
			{
				printf("GOIN\n");
				(*i)++;
			}
			ft_strlcat(buffer, current->key_and_val[1], buffer_len + strlen(current->key_and_val[1]) + 1);
            buffer_len += strlen(current->key_and_val[1]);
        }
        current = current->next;
    }
}



void expander(t_data *data, char *input) 
{
	(void) data;
	int i;
	int j;
	char strExpanded[4096];
	ft_bzero(strExpanded, 4096);
	i = 0;
	j = 0;
	data->tokenizer->final_cmd = NULL;
	while(input[i]) 
	{
		if (isSingleQuote(input[i]))
		{
			// ft_strjoin(strExpanded,passTilNextQuote(input, &i));
			passTilNextQuote(input, &i, strExpanded);
		}
		if (isHereDoc(input, &i)) 
		{
			passVarDoc(input, &i, strExpanded);
		} 
		if (isExitCode(input,&i)) 
		{
			printf("ENTER EXIT CODE DO THE FUNC\n");
			// expandExitCode();
		} 
		if (isVariable(input,&i)) 
		{
			expandVariable(data,input,&i, strExpanded);
			printf("BOLOSEE3 : %s\n", strExpanded);
		}
		else
		{
			while(strExpanded[j] != 0)
				j++;
			strExpanded[j] = input[i];
			i++;
		}
	}
	data->tokenizer->final_cmd = ft_strdup(strExpanded);
	printf("what : %s\n", data->tokenizer->final_cmd);
	printf("FINAL : %s\n", strExpanded);

}

