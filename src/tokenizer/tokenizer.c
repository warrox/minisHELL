/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/23 15:59:41 by whamdi           ###   ########.fr       */
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
int quoted(char *ex_input, char *og_input)
{
	char copy[4096];
	ft_bzero(copy, 4096);
	int i;
	int j; 
	i = 0;
	j = 0;
	printf("ex : %s\n",ex_input);
	printf("OG : %s\n", og_input);
	exit(1);
	while(og_input[i] && ft_isws(og_input[i]))
		i++;
	while(og_input[i] && (og_input[i] != '\'' || og_input[i] != '\"'))
	{
		if(og_input[i] == '\"' || og_input[i] == '\'')
			i++;
		copy[j++] = og_input[i++];
	}
	copy[j++] = 0;
	printf("COPY : %s\n", copy);
	if(ft_strcmp(ex_input, copy) == 0)
	{
		printf("GOINM\n");
		return(-1);
	}
	if(&og_input[i])
		quoted(ex_input,&og_input[i]);
	return(0);
}

int	sort_sign(t_list_arg *tmp, t_data *data, char *og_input)
{
	data->j = 0;
	data->i = 0;
	int flag;
	flag = 0;
	
	if(quoted(tmp->input_splited, og_input) == -2)
		return(-2);
	if(triple_sign_checker(tmp->input_splited, data) == -1)
		return(-1);
	else if(triple_sign_checker(tmp->input_splited, data) == -2)
		return(-2);
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

int	parse_cmd_arg(t_data *data, char *og_input)
{
	t_list_arg	*tmp;
	int sort_sign_result;

	tmp = data->tokenizer;
	while (tmp)
	{
		sort_sign_result = sort_sign(tmp, data, og_input);
		if(sort_sign_result == -1)
			return(-1);
		// else if(sort_sign_result == 0) 
		// 	create_signed(tmp);
		// tmp->final_cmd = flush_redir(tmp->input_splited, data);
		tmp = tmp->next;
	}
	exit(1);
	return(0);
}
