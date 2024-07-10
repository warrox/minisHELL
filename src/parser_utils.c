/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:43:26 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 18:43:38 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

t_data	*init_signal(t_data *data)
{
	data->signal = (t_signal *)malloc(sizeof(t_signal));
	if (!data->signal)
		return (NULL);
	data->signal->signal = ZERO_INIT;
	return (data);
}

void	msg_error_handler(int *signal, t_data *data)
{
	if (*signal == COMMAND_NOT_FOUND)
	{
		data->exit_status = 126;
		ft_printf("EXIT : %d\n", data->exit_status);
		ft_printf("command not found\n");
	}
	if (*signal == SYNTAX_ERROR)
	{
		data->exit_status = 2;
		ft_printf("syntax error\n");
	}
	if (*signal == UNEXPECTEDTOKEN)
	{
		data->exit_status = 2;
		printf("minishell: syntax error near unexpected token\n");
	}
}
