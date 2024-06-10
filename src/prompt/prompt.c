/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 11:23:02 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	free_prompt(t_data *data)
{
	if(data->prompt)
	{
		free(data->prompt->usr_name);
		free(data->prompt->usr_pwd);
		free(data->prompt->usr_prompt);
		free(data->prompt->usr_build_one);
		free(data->prompt->usr_build_two);
		free(data->prompt);
	}
}

int	display_prompt(t_data *data)
{
	char	*input;
	char	*input_cpy;

	input = NULL_INIT;
	input_cpy = NULL_INIT;
	data->tokenizer = NULL;
	init_signal(data);
	while (1)
	{
		init_prompt(data);
		build_user_prompt(data);
		data->tokenizer = init_tokenizer();
		input = readline(data->prompt->usr_prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free_prompt(data);
			ft_clear_tokenizer(data);
			free(data->signal);
			if (input)
				free(input);
			break ;
		}
		input_cpy = parser(input, data);
		// print_lst_cmdarg(data->tokenizer);
		if(data->tokenizer->final_cmd)
			print_exec_utils(data);
		ft_clear_tokenizer(data);
		add_history(input);
		free_prompt(data);
		free(input);
	}
	return (0);
}
