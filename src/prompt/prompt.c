/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 18:48:15 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

extern int		g_sig;

void	not_input_cpy(t_data *data)
{
	init_exec(data);
	free_exec(data);
	add_history(data->input);
	ft_clear_tokenizer(data);
	free(data->input);
	free_tmp_struct(data);
}

void	init_display(char *input, int *int_nbr, char *input_cpy, t_data *data)
{
	input = NULL_INIT;
	int_nbr = ZERO_INIT;
	input_cpy = NULL_INIT;
	data->tokenizer = NULL;
}

void	display_prompt2(t_data *data)
{
	if (data->input == NULL)
	{
		dprintf(2, "exit\n");
		free_prompt(data);
		free(data->signal);
		ft_lst_arg_clear(&data->tokenizer);
		ft_clear_tokenizer(data);
		exit(0);
	}
}

int	display_prompt(t_data *data)
{
	init_display(data->input, &data->int_nbr, data->input_cpy, data);
	init_signal(data);
	while (1)
	{
		handle_signal_prompt();
		init_prompt(data);
		build_user_prompt(data);
		data->tokenizer = init_tokenizer();
		data->input = readline(data->prompt->usr_prompt);
		if (data->input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			free_prompt(data);
			free(data->signal);
			ft_clear_tokenizer(data);
            break;
		}
		if (skip_ws_prompt(data, data->input))
			continue ;
		data->input_cpy = parser(data->input, data);
		if (data->input_cpy != NULL)
			not_input_cpy(data);
		ft_clear_tokenizer(data);
		free_prompt(data);
	}
	return (0);
}
