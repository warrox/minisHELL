/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:01:39 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/14 15:10:45 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	close_tubes(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	if (data->exec->multi_tube)
	{
		while(i < data->exec->nb_tube)
		{
			close(data->exec->multi_tube[i]);
			i++;
		}
	}
}

void	init_tubes(t_data *data)
{
	int i;
	
	i = ZERO_INIT;
	while(i < data->exec->nb_node - 1)
	{
		// printf("ICI -> %d\n", data->exec->nb_tube);
		if (pipe(data->exec->multi_tube + 2 * i) < 0)
			free(data->exec->multi_tube);
		i++;
	}
}