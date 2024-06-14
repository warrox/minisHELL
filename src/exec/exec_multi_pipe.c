/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/14 15:35:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exec_multi_pipe(t_data *data)
{
	data->exec->nb_node = nb_node(data);
	data->exec->nb_tube = (data->exec->nb_node - 1) * 2;
	data->exec->multi_tube = (int *)malloc(sizeof(int) * (data->exec->nb_tube));
	if (!data->exec->multi_tube)
		exit_error("Failed to allocate memory for pipes!\n");
	// printf("ICI -> %d\n", data->exec->nb_node);
	// printf("La -> %d\n", data->exec->nb_tube);
	init_tubes(data);
	// big while loop
	close_tubes(data);
	free(data->exec->multi_tube);
}