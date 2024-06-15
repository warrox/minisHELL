/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/15 18:38:00 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	reset_in_out(t_data *data)
{
	data->exec->infile = 0;
	data->exec->outfile = 1;
}

void	children_process(t_data *data)
{
	int i;
	t_list_arg *tmp = data->tokenizer;
	
	
	i = ZERO_INIT;
	data->exec->pid = fork();
	if (data->exec->pid == -1)
	{
		close_tubes(data);
		free(data->exec->multi_tube);
		free_exec(data);
		exit(1);
	}
	while(i != data->exec->index && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	// if (is_redir(tmp))
	// {
	// 	while(tmp->array_sign[i] != 0)
	// 		init_files(data, tmp, i++);
	// }
	if (!data->exec->pid)
	{
		if (data->exec->index == 0)
		{
			//printf("1\n");
			first_pipe(data, tmp);
		}
		else if (data->exec->index == data->exec->nb_node)
		{
			//printf("3\n");
			last_pipe(data, tmp);
		}
		else
		{
			//printf("2\n");
			intermediate_pipe(data, tmp);
		}
		close_tubes(data);
		data->exec->cmd = build_cmd(data, tmp);
		if (!data->exec->cmd)
			//free function
			return;
		execve(data->exec->cmd, tmp->cmd_array, NULL);
		//error function
	}
}

void	exec_multi_pipe(t_data *data)
{
	int	i;
	//int status = 0;

	i = ZERO_INIT;
	data->exec->nb_node = nb_node(data);
	data->exec->nb_tube = (data->exec->nb_node - 1) * 2;
	data->exec->multi_tube = (int *)malloc(sizeof(int) * (data->exec->nb_tube));
	if (!data->exec->multi_tube)
		exit_error("Failed to allocate memory for pipes!\n");
	// printf("ICI -> %d\n", data->exec->nb_node);
	// printf("La -> %d\n", data->exec->nb_tube);
	init_tubes(data);
	//dprintf(2, "idx_init %d\n", data->exec->index);
	while(++(data->exec->index) < data->exec->nb_node)
	{
		if(!data->exec->multi_tube)
			init_tubes(data);
		children_process(data);
	}
	close_tubes(data);
	while (wait(NULL) != -1)
		;
	//free function
	free(data->exec->multi_tube);
}