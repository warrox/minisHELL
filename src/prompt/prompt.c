/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/28 15:04:34 by cyferrei         ###   ########.fr       */
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
		//	dprintf(2, "CTRL_D DETECTED\n");
			free_prompt(data);
			free(data->signal);
			ft_lst_arg_clear(&data->tokenizer);
			ft_clear_tokenizer(data);
			exit(0);
		}
		if(skip_ws_prompt(data, input))
			continue;
		int_nbr = ft_exit(data, input);
		if(int_nbr >= 0 && int_nbr <= 255)
			return(int_nbr);
		input_cpy = parser(input, data);
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
