/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:02:48 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:28 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	nb_pipe(t_data *data)
{
	int	i;
	t_list_arg *tmp = NULL_INIT;
	
	tmp = data->tokenizer;
	i = ZERO_INIT;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_struct_exec(t_data *data)
{
	data->exec = (t_exec *)malloc(sizeof(t_exec));
	if (!data->exec)
		return ;
	data->exec->cmd = NULL_INIT;
	data->exec->infile = NULL_INIT;
	data->exec->here_doc = ZERO_INIT;
	data->exec->nb_cmd = ZERO_INIT;
	data->exec->outfile = ZERO_INIT;
	data->exec->nb_pipe = ZERO_INIT;
	data->exec->pid = NULL_INIT;
	data->exec->tube = NULL_INIT;
	data->exec->path = NULL_INIT;
	data->exec->path_cmd = NULL_INIT;
	data->exec->final_cmd = NULL_INIT;
}

void	exec_single_cmd(t_data *data)
{
	data->exec->pid = fork();
	if (data->exec->pid == -1)
		return;
	if (data->exec->pid == 0)
		exec_sub_proc(data);
	else
		waitpid(data->exec->pid, NULL, 0);
	
}

void	init_exec(t_data *data)
{
	int	i;
	i = ZERO_INIT;
	if(data->tokenizer->final_cmd == NULL)
		return;
	//print_exec_utils(data);
	init_struct_exec(data);
	data->exec->path = get_path(data);
	data->exec->path_cmd = ft_split(data->exec->path, ':');
	if (nb_pipe(data) == 1)
		exec_single_cmd(data);
}
