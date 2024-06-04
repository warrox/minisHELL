/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/04 15:47:19 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_env(t_data *data)
{
	if (ft_strncmp(data->tokenizer->cmd_array[0], "env", 4) == 0
		&& data->lst != NULL)
		print_lst(data->lst);
	else
		return ;
}
