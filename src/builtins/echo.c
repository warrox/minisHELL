/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 14:16:55 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	print_echo_flag(t_data *data, int start)
{
	int	i;
	int	last;

	i = start + 1;
	last = 0;
	while (data->tokenizer->cmd_array[last + 1])
		last++;
	while (data->tokenizer->cmd_array[i])
	{
		printf("%s", data->tokenizer->cmd_array[i]);
		if (i < last)
		{
			printf(" ");
		}
		i++;
	}
}

void	print_echo(t_data *data, t_list_arg *tok)
{
	int	i;
	int	flag;

	(void)data;
	i = 1;
	flag = 0;
	while (tok->cmd_array[flag + 1])
		flag++;
	while (tok->cmd_array[i])
	{
		flag--;
		printf("%s", tok->cmd_array[i]);
		if (flag > 0)
			printf(" ");
		i++;
	}
	printf("\n");
}

int	check_flag(t_data *data)
{
	int		i;
	int		start;
	char	**rpl;

	i = 0;
	start = 0;
	rpl = data->tokenizer->cmd_array;
	while (rpl[i])
	{
		if (is_valid_flag_n(rpl[i]))
		{
			if (start + 1 == i)
				start = i;
		}
		i++;
	}
	return (start);
}

int	check_echo_cmd(t_data *data)
{
	if (ft_strncmp(data->tokenizer->final_cmd, "echo", 5) == 0
		&& data->lst != NULL)
	{
		if (data->exec->nb_node != 1)
		{
			printf("\n");
			return (1);
		}
	}
	return (0);
}

int	cmd_echo(t_data *data, t_list_arg *tok)
{
	if (check_echo_cmd(data))
		return (1);
	if (check_flag(data))
	{
		print_echo_flag(data, check_flag(data));
		return (1);
	}
	if (!check_flag(data))
	{
		print_echo(data, tok);
		return (1);
	}
	return (0);
}
