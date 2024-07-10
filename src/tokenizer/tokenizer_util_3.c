/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:52 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 13:28:05 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	handle_double_quotes_t(char *str, t_data *data)
{
	data->pansement = 0;
	data->pansement_2 = 0;
	data->i++;
	while (str[data->i] && str[data->i] != '\"')
	{
		data->i++;
	}
	if (str[data->i] == '\"')
	{
		data->pansement = 1;
		data->pansement_2 = 1;
		data->i++;
	}
}

int	triple_sign_checker(char *str, t_data *data)
{
	int	j;

	data->i = 0;
	j = 0;
	handle_double_quotes_t(str, data);
	j = 0;
	if (data->pansement == 0)
		handle_single_quotes_t(str, data);
	if (data->pansement == 1)
		return (-2);
	while (str[data->i])
	{
		if (ft_strncmp(&str[data->i], "<<<", 3) == 0
			|| ft_strncmp(&str[data->i], "<<>", 3) == 0
			|| ft_strncmp(&str[data->i], ">>>", 3) == 0
			|| ft_strncmp(&str[data->i], ">><", 3) == 0)
		{
			ft_printf("minishell: syntax error near unexpected token\n");
			return (-1);
		}
		data->i++;
	}
	return (0);
}

void	fill_array_sign(t_data *data, char *str, t_list_arg *tmp)
{
	(void)str;
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
	int	flag;

	flag = 0;
	data->j = 0;
	data->i = 0;
	tmp->count_size = count_sign(tmp->input_splited);
	tmp->array_sign = ft_calloc(tmp->count_size + 1, sizeof(int));
	if (!tmp->array_sign)
		return (-1);
	while (tmp->count_size && tmp->input_splited[data->i])
	{
		fill_array_sign(data, &tmp->input_splited[data->i], tmp);
		data->i++;
	}
	return (0);
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
