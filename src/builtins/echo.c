/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 17:01:32 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	print_echo(t_data *data)
{
	int i = 1;
	int flag = 0;
	while(data->tokenizer->cmd_array[flag + 1]){
		// printf("%s",data->tokenizer->cmd_array[i]);
		flag++;	
	}
	while(data->tokenizer->cmd_array[i])
	{
		flag--;
		write(data->exec->outfile, data->tokenizer->cmd_array[i], ft_strlen(data->tokenizer->cmd_array[i]));
		if (flag > 0)
		{
			write(data->exec->outfile, " ", 1);		
		}
		i++;
	}
	write(data->exec->outfile, "\n", 1);
}

int	check_flag(t_data *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (data->tokenizer->final_cmd[i])
	{
		if (data->tokenizer->final_cmd[i] == '-')
		{
			int j = i + 1;
			while (data->tokenizer->final_cmd[j] == 'n')
				j++;
			if ((data->tokenizer->final_cmd[j] == ' ' || data->tokenizer->final_cmd[j] == '\0') && j > i + 1)
			{
				flag++;
				i = j - 1; // Avancer i au dernier 'n' pour continuer à chercher d'autres flags après l'espace
			}
		}
		i++;
	}
	return (flag);
}



int	check_echo_cmd(t_data *data)
{
	if (ft_strncmp(data->tokenizer->final_cmd, "echo", 5) == 0
		&& data->lst != NULL)
	{
		ft_putstr_fd("\n", data->exec->outfile);
		return (1);
	}
	return (0);
}

int	cmd_echo(t_data *data)
{
	if (data->tokenizer->cmd_array[0] == NULL)
		return (0);
	if (ft_strstr(data->tokenizer->final_cmd, "echo"))
	{
		if (check_echo_cmd(data))
			return (1);
		if (check_flag(data))
		{
			return (1);
		}
		if (!check_flag(data))
		{
			print_echo(data);
			return (1);
		}
	}
	return (0);
}
