/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:45:51 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/11 10:06:45 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

bool	isexitcode(char *input, int *i)
{
	return (!ft_strncmp(&input[*i], "$?", 2));
}

void	initexpandvariable(t_data *data)
{
	data->key_len = 0;
	data->flag = 0;
	data->i++;
}

void	passpartstring(int *flag, int *i, char *input)
{
	if (flag == 0)
	{
		while (input[*i] && !ft_isws(input[*i]))
			i++;
	}
}
