/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:53:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 13:58:06 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

long	ft_atoi_long(const char *str)
{
	int		i;
	int		sign;
	long	count;

	i = 0;
	count = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 34
		|| str[i] == 39 || str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = (count * 10) + (str[i] - 48);
		i++;
	}
	count = count * sign;
	return (count);
}

void	exit_helper(t_data *data)
{
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	exit(0);
}

void	exit_args(t_data *data)
{
	ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	data->exit_status = 1;
	exit(data->exit_status);
}
