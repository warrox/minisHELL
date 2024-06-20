#include "../includes/minishell_lib.h"
#include <stdio.h>

void handle_single_quote_ex(char *final_cmd, char *result, int *i, int *j, int *flag, int *sq_flag) 
{
    while (final_cmd[*i] != '\'' && final_cmd[*i + 1] != '\0') 
	{
        (*i)++;
        (*sq_flag)++;
        if (*flag % 2 != 0 && final_cmd[*i + 1] == '\0')
            return;
        (*flag)++;
        result[(*j)++] = final_cmd[*i];
    }
    *flag = 1;
}

void handle_double_quote_ex(char *final_cmd, char *result, int *i, int *j, int *flag) 
{
    while (final_cmd[*i] != '\"' && final_cmd[*i + 1] != '\0') {
        (*i)++;
        if (*flag % 2 != 0 && final_cmd[*i + 1] == '\0')
            return;
        (*flag)++;
        result[(*j)++] = final_cmd[*i];
    }
    *flag = 1;
}

void handle_expansion(char *final_cmd, char *result, t_data *data) 
{
    char *expanded = expansion(&final_cmd[++data->i], data);
    data->j += ft_strlen(expanded);
    ft_strlcat(result, expanded, ft_strlen(expanded) + ft_strlen(result) + 1);
    free(expanded);
    while (final_cmd[data->i] && final_cmd[data->i] != ' ')
        (data->i)++;
}

void init_expander(t_data *data) 
{
    data->i = 0;
    data->j = 0;
    data->flag = 0;
    data->sq_flag = 0;
}

void expander(t_data *data) 
{
    t_list_arg *tmp = data->tokenizer;
    init_expander(data);
    while (tmp) {
        data->i = 0;
        ft_bzero(tmp->result, 4096);
        while (tmp->final_cmd[data->i]) 
		{
			if (tmp->final_cmd[data->i] == '\'' && data->pansement == 0)
				handle_single_quote_ex(tmp->final_cmd, tmp->result, &data->i, &data->j, &data->flag, &data->sq_flag);
			else if (tmp->final_cmd[data->i] == '\"' && data->pansement == 0)
				handle_double_quote_ex(tmp->final_cmd, tmp->result, &data->i, &data->j, &data->flag);
			else if (tmp->final_cmd[data->i] == '$' && data->pansement == 0)
				handle_expansion(tmp->final_cmd, tmp->result, data);
			else
				tmp->result[data->j++] = tmp->final_cmd[data->i++];
        }

        if (data->flag)
            data->j -= 1;
        tmp->result[data->j] = '\0';
        tmp->cmd_array = ft_split(tmp->result, ' ');
        data->j = 0;
        data->i = 0;
        tmp = tmp->next;
    }
}

