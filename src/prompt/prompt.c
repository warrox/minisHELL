/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 17:10:17 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int g_sig;

int	display_prompt(t_data *data)
{
	char	*input;
	char	*input_cpy;
	int		int_nbr;
	input = NULL_INIT;
	int_nbr = ZERO_INIT;
	input_cpy = NULL_INIT;
	data->tokenizer = NULL;
	init_signal(data);
	while (1)
	{
		handle_signal_prompt();
		init_prompt(data);
		build_user_prompt(data);
		data->tokenizer = init_tokenizer();
		input = readline(data->prompt->usr_prompt);	
		if(input == NULL)
		{
			dprintf(2, "exit\n");
			free_prompt(data);
			free(data->signal);
			ft_lst_arg_clear(&data->tokenizer);
			ft_clear_tokenizer(data);
			exit(0);
		}
		if(skip_ws_prompt(data, input))
			continue;
		input_cpy = parser(input, data);	
		if(input_cpy != NULL)
		{
			init_exec(data);
			free_exec(data);
			add_history(input);
			ft_clear_tokenizer(data);
			free(input);
			free_tmp_struct(data);
		}
		free_prompt(data);
	}
	return (0);
}
