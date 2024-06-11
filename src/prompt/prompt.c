/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/11 17:24:06 by cyferrei         ###   ########.fr       */
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
		int j = 0;
		while(ft_isws(input[j]))			
			j++;
		if(input[j] == '\0')
		{
			add_history(input);
			free_prompt(data);
			ft_clear_tokenizer(data);
			continue;
		}
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
		if(input[0] == '\0' || is_a_builtin(data))
		{
			add_history(input);
			free_prompt(data);
			ft_clear_tokenizer(data);
			continue;
		}
		init_exec(data);
		// printf("%s\n", data->tokenizer->final_cmd);
		if (data->tokenizer->final_cmd != NULL)
			free_exec(data);
		ft_clear_tokenizer(data);
		add_history(input);
		free_prompt(data);
		free(input);
	}
	return (0);
}
