/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 17:05:47 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell_lib.h"

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
		init_prompt(data);
		build_user_prompt(data);
		data->tokenizer = init_tokenizer();
		input = readline(data->prompt->usr_prompt);	
		if(skip_ws_prompt(data, input))
			continue;
		int_nbr = ft_exit(data, input);
		if(int_nbr >= 0 && int_nbr <= 255)
			return(int_nbr);
		input_cpy = parser(input, data);
		// print_exec_utils(data);
		init_exec(data);
		if (data->tokenizer->final_cmd != NULL)
			free_exec(data);
		ft_clear_tokenizer(data);
		add_history(input);
		free_tmp_struct(data);
		free_prompt(data);
		free(input);
	}
	return (0);
}
