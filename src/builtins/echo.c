/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/25 18:07:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	print_echo(t_data *data)
{
	ft_putstr_fd(data->tokenizer->cmd_and_arg[1], 1);
	ft_putstr_fd("\n", 1);
}

int	check_flag(t_data *data)
{
	int i;

	i = ZERO_INIT;
	while(data->tokenizer->input_splited[i])
	{
		if(data->tokenizer->input_splited[i] == '-')
		{
			i++;
			while(data->tokenizer->input_splited[i] == 'n')
				i++;
			if(data->tokenizer->input_splited[i] == ' ')
				return(1);
			if(data->tokenizer->input_splited[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_echo_cmd(t_data *data)
{
	if(ft_strncmp(data->tokenizer->input_splited, "echo", 5) == 0 && data->lst != NULL)
	{
		ft_putstr_fd("\n", 1);
		return(1);
	}
	return (0);
}

void	cmd_echo(t_data *data)
{
	dprintf(2, "%s\n", data->tokenizer->input_splited);
	dprintf(2, "%s\n", data->tokenizer->cmd_and_arg[0]);
	dprintf(2, "%s\n", data->tokenizer->cmd_and_arg[1]);
	if(check_echo_cmd(data))
		return;
	if(check_flag(data))
	{
		dprintf(2, "OK\n");
		return;
	}
	if(!check_flag(data))
	{
		print_echo(data);
		return;
	}
}