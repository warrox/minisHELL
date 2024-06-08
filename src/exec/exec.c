/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:02:48 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/08 12:51:48 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_struct_pipe(t_data *data)
{
	data->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!data->pipe)
		return ;
	data->pipe->cmd = NULL_INIT;
	data->pipe->infile = NULL_INIT;
	data->pipe->here_doc = ZERO_INIT;
	data->pipe->nb_cmd = ZERO_INIT;
	data->pipe->oufile = ZERO_INIT;
	data->pipe->nb_pipe = ZERO_INIT;
	data->pipe->pid = NULL_INIT;
	data->pipe->tube = NULL_INIT;
}

void	exec_single_cmd(t_data *data)
{
	(void)data;
	printf("OK\n");
}

void	init_exec(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	print_exec_utils(data);
	init_struct_pipe(data);
	while (data->tokenizer->cmd_array[i])
		i++;
	if (i == 1)
		exec_single_cmd(data);
}

