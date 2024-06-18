/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/18 18:05:33 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	cmd_env(t_data *data)
{	
	if (data->tokenizer->cmd_array[0] == NULL)
		return (0);
	if (ft_strncmp(data->tokenizer->cmd_array[0], "env", 4) == 0 && data->lst != NULL)
	{
		print_lst(data->lst);
		return (1);
	}
	else
		return (0);
}
