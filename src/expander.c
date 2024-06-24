#include "../includes/minishell_lib.h"
#include "stdbool.h"
#include <stdio.h>

bool isExitCode(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "$?", 2));
}

bool isSingleQuote(char c)
{
    return (c == '\'');
}

char *passTilNextQuote(char *input, int *i, char *buffer, int *j)
{
    (*i)++;  // Pass the opening quote
    while (input[*i] && !isSingleQuote(input[*i]))
    {
        buffer[(*j)++] = input[*i];
        (*i)++;
    }
    if (input[*i] == '\'')
    {
        (*i)++;
    }
    buffer[*j] = ' ';
    (*j)++;
    buffer[*j] = '\0'; 
    return buffer;
}

bool isHereDoc(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "<<", 2));
}

void passVarDoc(char *input, int *i, char *buffer, int *j)
{
    (*i) += 2;
    while (input[*i] && ft_isws(input[*i]))
    {
        (*i)++;
    }
    while (input[*i] && !ft_isws(input[*i]))
    {
        buffer[(*j)++] = input[(*i)++];
    }
    buffer[*j] = ' ';
    (*j)++;
    buffer[*j] = '\0';
}

bool isVariable(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "$", 1));
}

void expandVariable(t_data *data, char *input, int *i, char *buffer, int *j, int *dq)
{
	size_t key_len;
	int flag;
	(*i)++;
    t_list_arg *current = data->lst;
	key_len = 0;
	flag = 0;
	while (current)
    {
        key_len = ft_strlen(current->key_and_val[0]);
		if (!ft_strncmp(&input[*i], current->key_and_val[0], key_len) || (!dq && (ft_strlen(current->key_and_val[0]) == ft_strlen(&input[*i]))))
		{
			flag = 1;
			ft_strlcat(buffer, current->key_and_val[1], 4096);
			*j += ft_strlen(current->key_and_val[1]);
			*i += key_len;
			break;
		}
        current = current->next;
    }
	if(flag == 0)
	{
		while(input[*i] && !ft_isws(input[*i])) // ou comp 
			(*i)++;
	}
}

void expander(t_data *data, char *input)
{
    int i = 0;
    int j = 0;
    char strExpanded[4096];
    ft_bzero(strExpanded, 4096);
	int sq = 0;
	int dq = 0;
    while (input[i])
    {
		if (isDoubleQuote(input[i]) && !sq)
			dq = !dq;
		else if (isSingleQuote(input[i]) && !dq)
			sq = !sq;
		else if (isHereDoc(input, &i))
			passVarDoc(input, &i, strExpanded, &j);
		else if (isExitCode(input, &i))
		{
			// expandExitCode();
		} 
		if (isVariable(input, &i) && !sq)
		{
			expandVariable(data, input, &i, strExpanded, &j, &dq);
		}
		else
			strExpanded[j++] = input[i++];
    }
    strExpanded[j] = '\0';
    data->tokenizer->final_cmd = ft_strdup(strExpanded);
}
