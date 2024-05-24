/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 14:36:46 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	free_prompt(t_data *data)
{
	free(data->prompt->usr_name);
	free(data->prompt->usr_pwd);
	free(data->prompt->usr_prompt);
	free(data->prompt->usr_build_one);
	free(data->prompt->usr_build_two);
	free(data->prompt);
}

void	ft_clear_tokenizer(t_list_arg **tokenizer);

int	display_prompt(t_data *data)
{
	char	*input;
	char	*input_cpy;

	input = NULL_INIT;
	input_cpy = NULL_INIT;
	while (1)
	{
		init_prompt(data);
		build_user_prompt(data);
		input = readline(data->prompt->usr_prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_prompt(data);
			ft_clear_tokenizer(&data->tokenizer);
			break ;
		}
		input_cpy = parser(input, data);
		//ft_printf("tokenizer in prompt : %s\n",data->tokenizer->input_splited);	
		//ft_printf("Input after : %s\n", input);
		add_history(input);
		free_prompt(data);
		free(input);
		ft_clear_tokenizer(&data->tokenizer);
	}
	return (0);
}
