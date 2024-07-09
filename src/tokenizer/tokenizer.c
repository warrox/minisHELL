/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/09 16:11:58 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

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
		tmp->tmp_cmd_array = split_tokenizer(tmp, data);
		tmp->cmd_array = clean_cmd_array(tmp);
		free_tab_clean(tmp->tmp_cmd_array);
		tmp = tmp->next;
	}
	return(0);
}
