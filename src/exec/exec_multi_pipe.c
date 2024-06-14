/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/14 16:17:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	first_pipe(t_list_arg *tok)
{
	if(is_redir(tok))
	{
		
	}
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
	if (!data->exec->pid)
	{
		if (data->exec->index == 0)
			first_pipe(data->tokenizer);
	}
}

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
	while(++(data->exec->index) < data->exec->nb_node)
	{
		if(!data->exec->multi_tube)
			init_tubes(data);
		children_process(data);
	}
	close_tubes(data);
	while (wait(NULL) > 0)
		;
	free(data->exec->multi_tube);
}