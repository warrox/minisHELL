/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:52 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/09 16:12:02 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
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


