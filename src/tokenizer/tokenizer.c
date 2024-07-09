/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/09 07:13:13 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>
int triple_sign_checker(char *str, t_data *data)
{
	int i;
	int j;
	i = 0;
	j = 0;
	handle_double_quotes_flush(str, NULL, &j, 0,data,0);
	j = 0;
	if(data->pansement == 0)
		handle_single_quotes_flush(str, NULL, &j, 0, data,0); 
	if(data->pansement == 1)
		return(-2);

	while(str[i])
	{
		if(ft_strncmp(&str[i], "<<<", 3)== 0 || ft_strncmp(&str[i], "<<>", 3) == 0 
			|| ft_strncmp(&str[i], ">>>", 3) == 0 ||ft_strncmp(&str[i], ">><", 3) == 0)
		{
			ft_printf("minishell: syntax error near unexpected token\n");
			return(-1);
		}
		i++;
	}
	return(0);
}

void fill_array_sign(t_data *data, char *str, t_list_arg *tmp)
{
	(void) str;
	if (ft_strncmp(&tmp->input_splited[data->i], "<<", 2) == 0)
	{
		data->i++;
		tmp->array_sign[data->j++] = HEREDOCS;
	}
	else if (ft_strncmp(&tmp->input_splited[data->i], ">>", 2) == 0)
	{
		data->i++;	
		tmp->array_sign[data->j++] = APPEND;
	}
	else if (ft_strncmp(&tmp->input_splited[data->i], "<", 1) == 0)
	{
		tmp->array_sign[data->j++] = STDINS;
	}
	else if (ft_strncmp(&tmp->input_splited[data->i], ">", 1) == 0)
	{
		tmp->array_sign[data->j++] = STDOUTS;
	}
}


int	sort_sign(t_list_arg *tmp, t_data *data)
{
	int flag;
	flag = 0;
	data->j = 0;
	data->i = 0;

	tmp->count_size = count_sign(tmp->input_splited);
	tmp->array_sign = ft_calloc(tmp->count_size + 1, sizeof(int));
	if(!tmp->array_sign)
		return(-1);
	while (tmp->count_size && tmp->input_splited[data->i])
	{
		fill_array_sign(data,&tmp->input_splited[data->i], tmp);
		data->i++;
	}
	return(0);
}

int	get_word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isws(str[i]))
		i++;
	while (str[i] && !ft_isws(str[i]))
		i++;
	return (i);
}


char *clean_quotes(char *str) 
{
    int len = strlen(str);
    int start = 0;
    int end = len - 1;
    char *cleaned_str;
	int sf = 0;
	int df = 0;
    if (len > 1) 
	{
        if (str[start] == '\"' && str[end] == '\"' && !sf) 
		{
            df = 1;
			start++;
            end--;
        } else if (str[start] == '\'' && str[end] == '\'' && !df) 
		{
            sf = 1;
			start++;
            end--;
        }
    }

    cleaned_str = (char *)malloc(end - start + 2);
    if (!cleaned_str) return NULL;

    int i = start; 
	int j = 0;
    // printf("SF : %d\n", sf);
	// printf("DF : %d\n", df);
	while (i <= end) 
	{
		while(str[i] && str[i] == '\"' && !sf)
			i++;
		while(str[i] && str[i] == '\'' && !df)
			i++;
		cleaned_str[j++] = str[i++];
    }
    cleaned_str[j] = '\0';
    return (cleaned_str);
}

char **clean_cmd_array(t_list_arg *tmp) 
{
    int count = 0;
    char **cleaned_array;

    while (tmp->tmp_cmd_array && tmp->tmp_cmd_array[count] != NULL) 
	{
        count++;
    }

    cleaned_array = (char **)malloc((count + 1) * sizeof(char *));
    if (!cleaned_array) 
		return (NULL);

    int i = 0;
    while (i < count) 
	{
        cleaned_array[i] = clean_quotes(tmp->tmp_cmd_array[i]);
        i++;
    }
    cleaned_array[count] = NULL;

    return cleaned_array;
}

int	parse_cmd_arg(t_data *data)
{
	t_list_arg	*tmp;
	int sort_sign_result;

	tmp = data->tokenizer;
	while (tmp)
	{
		sort_sign_result = sort_sign(tmp, data);
		if(sort_sign_result == -1)
			return(-1);
		else if(sort_sign_result == 0) 
			create_signed(tmp);
		tmp->final_cmd = flush_redir(tmp->input_splited, data);
		// printf("FLUSH : %s\n", tmp->final_cmd);
		tmp->tmp_cmd_array = split_tokenizer(tmp, data);
		tmp->cmd_array = clean_cmd_array(tmp);
		// if(tmp->tmp_cmd_array[0] == NULL)
		// {
		// 	tmp->tmp_cmd_array[0] = ft_strdup(tmp->final_cmd);
		// 	tmp->tmp_cmd_array[1] = NULL;
		// }
		free_tab_clean(tmp->tmp_cmd_array);
		tmp = tmp->next;
	}
	return(0);
}
