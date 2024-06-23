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

void expandVariable(t_data *data, char *input, int *i, char *buffer, int *j)
{
    (*i)++;
    t_list_arg *current = data->lst;
    while (current)
    {
        size_t key_len = ft_strlen(current->key_and_val[0]);
        if (!ft_strncmp(&input[*i], current->key_and_val[0], key_len))
        {
            ft_strlcat(buffer, current->key_and_val[1], 4096);
            *j += ft_strlen(current->key_and_val[1]);
            *i += key_len;
            break;
        }
        current = current->next;
    }
    buffer[*j] = ' ';
    (*j)++;
    buffer[*j] = '\0';
}

void expander(t_data *data, char *input)
{
    int i = 0;
    int j = 0;
    char strExpanded[4096];
    ft_bzero(strExpanded, 4096);

    while (input[i])
    {
        if (isSingleQuote(input[i]))
            passTilNextQuote(input, &i, strExpanded, &j);
        else if (isHereDoc(input, &i))
            passVarDoc(input, &i, strExpanded, &j);
        else if (isExitCode(input, &i))
        {
            printf("ENTER EXIT CODE DO THE FUNC\n");
            // expandExitCode();
        }
        else if (isVariable(input, &i))
            expandVariable(data, input, &i, strExpanded, &j);
        else
        {
    //         if(input[i] == '\"')
				// i++;
			strExpanded[j++] = input[i++];
        }
    }
    strExpanded[j] = '\0';
    data->tokenizer->final_cmd = ft_strdup(strExpanded);
}
