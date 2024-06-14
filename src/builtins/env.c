/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/11 17:45:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	cmd_env(t_data *data)
{	
	if (data->tokenizer->cmd_array[0] == NULL)
		return (1);
	if (ft_strncmp(data->tokenizer->cmd_array[0], "env", 4) == 0 && data->lst != NULL)
	{
		print_lst(data->lst);
		return (1);
	}
	else
		return (0);
}
