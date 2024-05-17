/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 17:29:45 by cyferrei         ###   ########.fr       */
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
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_prompt(data);
			break ;
		}
		input_cpy = parser(input, data);
		add_history(input);
		free_prompt(data);
		free(input);
	}
	return (0);
}
