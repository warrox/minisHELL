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
	buffer[(*j)] = input[(*i)];
	(*i) += 1;
	(*j)++;
	buffer[(*j)] = input[(*i)];
	(*i) += 1;
	(*j)++;

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


char *buff_copy(char *input)
{
	char *buffer;
	int len;
	int flag;
	len = 0;
	flag = 0;
	while(input[len] && input[len] != ' ')
	{
		if(input[len] == '$' || input[len] == '\'')
		{
			break;
		}
		if(input[len] == '\"' || input[len] == '\'')
		{
			flag = 1;
		}
		len++;
	}
	if(flag == 1)
		len --;
	buffer = ft_substr(input, 0, len);
	return(buffer);
}
void expandVariable(t_data *data, char *input, int *i, char *buffer, int *j, int *dq)
{
    t_list_arg *current; 
	char *b_copy;
	current = data->lst;
	data->key_len = 0;
	data->flag = 0;
	(*i)++;
	b_copy = buff_copy(&input[*i]);
	while (current)
    {
        data->key_len = ft_strlen(current->key_and_val[0]);
		if (!ft_strncmp(&input[(*i)], current->key_and_val[0], data->key_len) && (dq && (ft_strlen(current->key_and_val[0]) == ft_strlen(b_copy))))
		{
			data->flag = 1;
			ft_strlcat(buffer, current->key_and_val[1], 4096);
			*j += ft_strlen(current->key_and_val[1]);
			*i += data->key_len;
			break;
		}
        current = current->next;
    }
	if(data->flag == 0)
	{
		while(input[*i] && !ft_isws(input[*i])) 
			(*i)++;
	}
}
void expandExitCode(int *i, t_data *data, char *strExpanded, int *j)
{
	char *itoa_exitCode;
	int k;
	k = 0;
	(*i)+= 2;
	itoa_exitCode = ft_itoa(data->exit_status);
	while(itoa_exitCode[k])
	{
		strExpanded[(*j)++] = itoa_exitCode[k++];
	}
}

void expander(t_data *data, char *input)
{
    char strExpanded[4096];
    ft_bzero(strExpanded, 4096);
	data->i = 0;
	data->j = 0;
	data->sq = 0;
	data->dq = 0;
	while (input[data->i])
    {
		if (isDoubleQuote(input[data->i]) && !data->sq)
			data->dq = !data->dq;
		else if (isSingleQuote(input[data->i]) && !data->dq)
			data->sq = !data->sq;
		else if (isHereDoc(input, &data->i))
			passVarDoc(input, &data->i, strExpanded, &data->j);
		else if (isExitCode(input, &data->i) && !data->sq)
			expandExitCode(&data->i,data,strExpanded, &data->j);
		if (isVariable(input, &data->i) && !data->sq && (input[data->i + 1] && ft_isalnum(input[data->i+1])))
			expandVariable(data, input, &data->i, strExpanded, &data->j, &data->dq);
		else
			strExpanded[data->j++] = input[data->i++];
    }
    strExpanded[data->j] = '\0';
    data->tokenizer->final_cmd = ft_strdup(strExpanded);
}
