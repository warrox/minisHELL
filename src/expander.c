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


char *buff_copy(char *input)
{
	char *buffer;
	int len;
	int flag;
	len = 0;
	flag = 0;
	// printf("PD : %s\n", input);
	while(input[len] && input[len] != ' ')
	{
		// printf("Letter : %c\n",input[len]);
		if(input[len] == '$' || input[len] == '\'')
		{
			// len -= 1;
			break;
		}
		if(input[len] == '\"' || input[len] == '\'')
		{
			printf("GO\n");
			flag = 1;
		}
		len++;
	}
	if(flag == 1)
		len --;
	buffer = ft_substr(input, 0, len);
	// len = (*i);
	// while(input[len] && (!ft_isws(input[len]) || input[(len)] != '$'))
	// 	buffer[j++] = input[len++];
	return(buffer);
}
void expandVariable(t_data *data, char *input, int *i, char *buffer, int *j, int *dq)
{
	size_t key_len;
	int flag;
	(*i)++;
    t_list_arg *current = data->lst;
	key_len = 0;
	flag = 0;
	char *b_copy = buff_copy(&input[*i]);
	while (current)
    {
        key_len = ft_strlen(current->key_and_val[0]);
		// printf("B_COPY : %s\n", b_copy);
		// printf("B_LENGHT : %zu\n",ft_strlen(b_copy));
		// printf("XXX : %s\n", current->key_and_val[0]);
		// printf("R_LENGHT : %zu\n", ft_strlen(current->key_and_val[0]));
		// if(!ft_strncmp(&input[(*i)], current->key_and_val[0],key_len))
		// 	printf("TRUEEEE FDP\n");
		// if(!dq && ft_strlen(current->key_and_val[0]) == ft_strlen(b_copy))
		// {
		// 	printf("TRYEEEE AGAIN \n");
		// }
		if (!ft_strncmp(&input[(*i)], current->key_and_val[0], key_len) && (dq && (ft_strlen(current->key_and_val[0]) == ft_strlen(b_copy))))
		{
			// printf("GOIN\n");
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
		// echo "salut '$PWD'" 
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
