/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 18:04:50 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	print_echo_flag(t_data *data, int start)
{
	int i = 1;
	int flag = 0;
	while(data->tokenizer->cmd_array[flag + 1])
		flag++;	
	while(data->tokenizer->cmd_array[start + 1])
	{
		flag--;
		write(data->exec->outfile, data->tokenizer->cmd_array[start + 1], ft_strlen(data->tokenizer->cmd_array[start + 1]));
		if (flag > 0)
		{
			write(data->exec->outfile, " ", 1);		
		}
		i++;
	}
	write(data->exec->outfile, "\n", 1);
}

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
	int j;
	int	flag;
	int start;
	
	start = 0;
	flag = 0;
	i = 0;
	j = 0;
	while (data->tokenizer->cmd_array[i])
	{
		j = 0;
		while(data->tokenizer->cmd_array[i][j])
		{
			if (data->tokenizer->cmd_array[i][j] == '-')
			{
				j++;
				while (data->tokenizer->cmd_array[i][j] == 'n')
					j++;
				if ((data->tokenizer->cmd_array[i][j] == ' ' || data->tokenizer->cmd_array[i][j] == '\0'))
				{
					start++;
				}
				else
					break;
			}
			j++;
		}
		i++;
	}
	// dprintf(2, "ICI START %d\n", start);
	return (start);
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
			// dprintf(2, "TEST %s\n", data->tokenizer->cmd_array[]);
			// dprintf(2, "%d\n", check_flag(data));
			print_echo_flag(data, check_flag(data));
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
