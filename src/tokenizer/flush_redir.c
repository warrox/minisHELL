#include "../../includes/minishell_lib.h"
#include <stdio.h>

void handle_double_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy) 
{
	data->pansement = 0;
	(*i)++;
	while (str[*i] && str[*i] != '\"') 
	{
		if(flag_for_copy == 1) 
			buffer[(*j)++] = str[*i];
        (*i)++;
    }
	if (str[*i] == '\"') 
	{
        (*i)++;
		data->pansement = 1;
    }
}

void handle_single_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data, int flag_for_copy) 
{
	data->pansement = 0;
	(*i)++;
	while (str[*i] && str[*i] != '\'') 
	{
		if(flag_for_copy == 1)
			buffer[(*j)++] = str[*i];
        (*i)++;
    }
	if (str[*i] == '\'') 
	{
        data->pansement = 1;
        (*i)++;
    }
}

int handle_signs(char *str, int *i) 
{
    int tmp;
    tmp = sign_cmp(&str[*i]);
    if (tmp) {
        *i += tmp;
        *i += get_word_size(&str[*i]);
    }
    return tmp;
}

char *flush_redir(char *str, t_data *data) 
{
    char buffer[2048];
    int tmp;
	int len;

    data->i = 0;
    data->j = 0;
    data->pansement = 0;
	len = ft_strlen(str);
	while (data->i < len) 
	{
		if (str[data->i] == '\"')
			handle_double_quotes_flush(str, buffer, &data->i, &data->j,data,1);
		else if (str[data->i] == '\'') 
			handle_single_quotes_flush(str, buffer, &data->i, &data->j, data,1);
		else 
			tmp = handle_signs(str, &data->i);
		if (!tmp) 
		{
			buffer[data->j++] = str[data->i];
			data->i++;
		}
    }
    buffer[data->j] = 0;
    return ft_strdup(buffer);
}
