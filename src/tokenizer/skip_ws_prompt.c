/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_ws_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:45:22 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 13:45:38 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	skip_ws_prompt(t_data *data, char *input)
{
	data->j = 0;
	while (ft_isws(input[data->j]))
		data->j++;
	if (input[data->j] == '\0' || input[0] == '\0')
	{
		add_history(input);
		free_prompt(data);
		ft_clear_tokenizer(data);
		return (1);
	}
	return (0);
}
