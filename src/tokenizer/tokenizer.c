/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/19 18:40:39 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <readline/history.h>
#include <stdio.h>
int triple_sign_checker(char *str)
{
	int i;
	i = 0;
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
	data->j = 0;
	data->i = 0;
	int flag;
	flag = 0;
	if(triple_sign_checker(tmp->input_splited) == -1)
		return(-1);
	tmp->count_size = count_sign(tmp->input_splited);
	printf("count size : %d\n", tmp->count_size);
	tmp->array_sign = ft_calloc(tmp->count_size + 1, sizeof(int));
	dprintf(2, "input : %s\n", tmp->input_splited);
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

int	parse_cmd_arg(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->tokenizer;
	while (tmp)
	{
		if(sort_sign(tmp,data) == -1)
			return(-1);
		create_signed(tmp);
		tmp->final_cmd = flush_redir(tmp->input_splited, data);
		tmp = tmp->next;
	}
	return(0);
}
