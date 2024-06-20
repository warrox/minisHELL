/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/20 19:39:09 by cyferrei         ###   ########.fr       */
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
		int j = 0;
		while(ft_isws(input[j]))			
			j++;
		if(input[j] == '\0' || input[0] == '\0')
		{
			add_history(input);
			free_prompt(data);
			ft_clear_tokenizer(data);
			continue;
		}
		int_nbr = ft_exit(data, input);
		if(int_nbr >= 0 && int_nbr <= 255)
			return(int_nbr);
		input_cpy = parser(input, data);
		// print_exec_utils(data);
		if(is_a_builtin(data))
		{
			add_history(input);
			free_prompt(data);
			ft_clear_tokenizer(data);
			continue;
		}
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
