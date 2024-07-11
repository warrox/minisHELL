/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 12:41:15 by cyferrei         ###   ########.fr       */
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
		write(data->exec->outfile, data->tokenizer->cmd_array[i],
			ft_strlen(data->tokenizer->cmd_array[i]));
		if (i < last)
		{
			write(data->exec->outfile, " ", 1);
		}
		i++;
	}
}

void	print_echo(t_data *data, t_list_arg *tok)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (tok->cmd_array[flag + 1])
		flag++;
	while (tok->cmd_array[i])
	{
		flag--;
		write(data->exec->outfile, tok->cmd_array[i],
			ft_strlen(tok->cmd_array[i]));
		if (flag > 0)
			write(data->exec->outfile, " ", 1);
		i++;
	}
	write(data->exec->outfile, "\n", 1);
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
		ft_putstr_fd("\n", data->exec->outfile);
		return (1);
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
