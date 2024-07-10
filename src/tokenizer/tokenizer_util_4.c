/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:27:48 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 13:27:57 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	handle_single_quotes_t(char *str, t_data *data)
{
	data->pansement = 0;
	data->i++;
	while (str[data->i] && str[data->i] != '\'')
	{
		data->i++;
	}
	if (str[data->i] == '\'')
	{
		data->pansement = 1;
		data->i++;
	}
}
