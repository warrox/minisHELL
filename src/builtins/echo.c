/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/19 17:29:47 by whamdi           ###   ########.fr       */
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
		printf("%s",data->tokenizer->cmd_array[i]);
		if (flag > 0)
		{
			printf(" ");
		}
		i++;
	}
	printf("\n");
}

int	check_flag(t_data *data)
{
	int	i;
	int flag;

	flag = ZERO_INIT;
	i = ZERO_INIT;
	while (data->tokenizer->final_cmd[i])
	{
		if (data->tokenizer->final_cmd[i] && data->tokenizer->final_cmd[i] == '-')
		{
			i++;
			while (data->tokenizer->final_cmd[i] == 'n')
				i++;
			if (data->tokenizer->final_cmd[i] == ' ' || data->tokenizer->final_cmd[i] == '\0')
			{
				int j = i;
				while(data->tokenizer->final_cmd[j] == ' ' || data->tokenizer->final_cmd[j] == '\t')
					j++;
				if(data->tokenizer->final_cmd[j] != '-')
					break;
				flag++;
				continue;
			}
		}
		i++;
	}
	return (0);
}

int	check_echo_cmd(t_data *data)
{
	if (ft_strncmp(data->tokenizer->final_cmd, "echo", 5) == 0
		&& data->lst != NULL)
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}

int	cmd_echo(t_data *data)
{
	// for(int i = 0; data->tokenizer->cmd_array[i]; i++)
	// 	dprintf(2, "%s\n", data->tokenizer->cmd_array[i]);
	if (data->tokenizer->cmd_array[0] == NULL)
		return (0);
	if (ft_strstr(data->tokenizer->final_cmd, "echo"))
	{
		if (check_echo_cmd(data))
			return (1);
		if (check_flag(data))
			return (1);
		if (!check_flag(data))
		{
			print_echo(data);
			return (1);
		}
	}
	return (0);
}
