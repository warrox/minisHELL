/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/23 11:47:55 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell_lib.h"
#include <stdio.h>

int	expand_stopper(char c)
{
	if (c == '{' || (c == '}' || c == '.' || c == ' ' || c == '\t'))
	{
		return (1);
	}
	return (0);
}
char	*expansion(char *input, t_data *data)
{
	int		i;
	int		end;
	char	*result;
	int		flag;
	char	*key;

	i = 0;
	end = 0;
	flag = 0;
	while (input[i])
	{
		if (expand_stopper(input[i]))
		{
			flag = 1;
			break ;
		}
		end++;
		i++;
	}
	key = ft_substr(input, 0, end);
	result = ft_strdup(search_occurence(key, data));
	i = 0;
	while (result[i] != 0)
		i++;
	if (flag == 1)
		result[i++] = input[end++];
	result[i++] = '\0';
	free(key);
	return (result);
}
t_list_arg	*init_tokenizer(void)
{
	t_list_arg	*tokenizer;

	tokenizer = ft_calloc(1, sizeof(t_list_arg));
	tokenizer->final_cmd = ZERO_INIT;

	tokenizer->array_sign = ZERO_INIT;
	tokenizer->file_array = NULL_INIT;
	tokenizer->count_size = ZERO_INIT;
	tokenizer->key_and_val = NULL_INIT;
	tokenizer->input_splited = NULL_INIT;
	return (tokenizer);
}
char	*parser(char *input, t_data *data)
{
	char	*result;
	if (*input == '\0')
		return (input);
	result = NULL;
	if(syntax_checker(input) == -1)
		return(NULL);
	expander(data, input);
	printf("IS PASSING PARSE : %s\n", data->tokenizer->final_cmd);
	if(cutting_input(data, data->tokenizer->final_cmd) == -1)
		return (NULL);
	// if(parse_cmd_arg(data) == -1)
	// 	return (NULL);
	return (input);
}
