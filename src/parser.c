/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 14:49:05 by whamdi           ###   ########.fr       */
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

t_list_arg	*init_tokenizer(void)
{
	t_list_arg	*tokenizer;

	tokenizer = ft_calloc(1, sizeof(t_list_arg));
	tokenizer->final_cmd = ZERO_INIT;
	tokenizer->cmd_array = NULL_INIT;
	tokenizer->tmp_cmd_array = NULL_INIT;
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
	if(syntax_checker(input, data) == -1)
		return(NULL);
	expander(data, input);
	if(cutting_input(data, data->tokenizer->final_cmd) == -1)
		return (NULL);
	if(parse_cmd_arg(data) == -1)
		return (NULL);
	return (input);
}
