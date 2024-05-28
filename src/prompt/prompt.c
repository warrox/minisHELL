/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/28 15:36:04 by whamdi           ###   ########.fr       */
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
		// ft_printf("input : %s\n",input);
		// exit(1);
			if (ft_strncmp(input, "exit", 4) == 0)
			{
				free_prompt(data);
				ft_clear_tokenizer(data->tokenizer);
				if(data->signal)
					free(data->signal);
				if(input)
					free(input);
				break ;
			}
		input_cpy = parser(input, data);
		add_history(input);
		free_prompt(data);
		free(input);
		// if(*input != '\0')
		// {
		// 	ft_clear_tokenizer(data->tokenizer);
		// 	if(data->signal)
		// 		free(data->signal);
		// }
	}
	return (0);
}
