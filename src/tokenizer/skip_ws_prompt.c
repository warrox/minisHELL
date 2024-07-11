/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_ws_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:45:22 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/11 15:30:19 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	skip_ws_prompt(t_data *data, char *input)
{
	int	flag;
	int	flag_2;

	flag = 0;
	flag_2 = 0;
	data->j = 0;
	while (ft_isws(input[data->j]))
	{
		if (input[data->j] && ft_isalnum(input[data->j])
			&& (input[data->j] != ' ' || input[data->j] != '\t'))
			flag_2 = 1;
		data->j++;
	}
	if (input[0] == '\0')
		flag = 1;
	if (input[data->j] == '\0' || input[0] == '\0')
	{
		if (flag == 0 && flag_2 == 1)
			add_history(input);
		free_prompt(data);
		ft_clear_tokenizer(data);
		return (1);
	}
	return (0);
}
