/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:30:24 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 12:39:17 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	fileafterredirsign(char *input, int i)
{
	i++;
	while (ft_isws(input[i]))
		i++;
	if (input[i] && ft_isascii(input[i]))
		return (0);
	return (-1);
}

int	triplesigndetector(char *input, int i)
{
	if (ft_strncmp(&input[i], "<<<", 3) == 0 || ft_strncmp(&input[i], "<<>",
			3) == 0 || ft_strncmp(&input[i], ">>>", 3) == 0
		|| ft_strncmp(&input[i], ">><", 3) == 0)
	{
		return (-1);
	}
	return (0);
}

void	init_unexpectedtoken(t_data *data)
{
	data->flag = 0;
	data->signal_int = 0;
	data->i = 0;
}

int	unexpectedtoken(char *input, t_data *data)
{
	init_unexpectedtoken(data);
	while (input[data->i])
	{
		if (input[data->i] == '\"')
			data->flag += 1;
		if (if_pipe(input[data->i]) || redirsign(input[data->i]))
		{
			if (pipe_alone(input, data->i) == -1 || fileafterredirsign(input,
					data->i) == -1)
			{
				data->signal_int = SYNTAX_ERROR;
				msg_error_handler(&data->signal_int, data);
				return (-1);
			}
			if (triplesigndetector(input, data->i) == -1 && data->flag == 0)
			{
				data->signal_int = UNEXPECTEDTOKEN;
				msg_error_handler(&data->signal_int, data);
				return (-1);
			}
		}
		data->i++;
	}
	return (0);
}

int	sign_cmp(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
}
