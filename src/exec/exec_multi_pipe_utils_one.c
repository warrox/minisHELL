/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:12:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 10:34:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_multi_pipe(t_data *data)
{
	data->exec->nb_node = nb_node(data);
	data->exec->nb_tube = (data->exec->nb_node - 1) * 2;
	data->exec->multi_tube = (int *)malloc(sizeof(int) * (data->exec->nb_tube));
	if (!data->exec->multi_tube)
		return;
}

void	error_pid(t_data *data)
{
	close_tubes(data);
	free_resources(data);
	exit(1);
}
