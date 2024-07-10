/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:05:58 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 18:37:49 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	is_singlequote(char c)
{
	return (c == '\'');
}

int	is_doublequote(char c)
{
	return (c == '\"');
}

void	check_quotes(char *input, int *flag_s, int *flag_d, int *signal)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_doublequote(input[i]) && (*flag_s == 0))
			*flag_d = !(*flag_d);
		else if (is_singlequote(input[i]) && (*flag_d == 0))
			*flag_s = !(*flag_s);
		i++;
	}
	if (*flag_s || *flag_d)
		*signal = SYNTAX_ERROR;
}

int	check_quote(char *input, t_data *data)
{
	int	signal;
	int	first_enter;

	first_enter = 0;
	init_check_quote(&first_enter, &signal, data);
	check_quotes(input, &data->flag_s, &data->flag_d, &signal);
	if (signal == SYNTAX_ERROR)
	{
		msg_error_handler(&signal, data);
		return (-1);
	}
	return (0);
}

int	syntax_checker(char *input, t_data *data)
{
	if (unexpectedtoken(input, data) != 0 || check_quote(input, data) != 0)
	{
		data->exit_status = 2;
		return (-1);
	}
	return (0);
}
