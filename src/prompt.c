/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/08 10:37:52 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
#include <stdio.h>

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
	input = NULL_INIT;
	while (1)
	{
		init_prompt(data);
		build_user_prompt(data);
		input = readline(data->prompt->usr_prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_prompt(data);
			break ;
		}
		ft_printf("Vous avez entré: %s\n", input);
		input = parser(input, data);	
		if(input == NULL)
			msg_error_handler(data->signal->signal);	
		ft_printf("Input after : %s\n", input);
		add_history(input);
		free_prompt(data);
		free(input);
	}
	return (0);
}
