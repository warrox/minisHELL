/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:12:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 14:19:24 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exit_builtin_multi(t_data *data, t_list_arg *tmp, int i)
{
	execute_builtin_multi(data, tmp, i);
	close_tubes(data);
	free(data->signal);
	free_prompt(data);
	ft_clear_tokenizer(data);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	free_exec(data);
	exit(1);
}

void	init_multi_pipe(t_data *data)
{
	data->exec->nb_node = nb_node(data);
	data->exec->nb_tube = (data->exec->nb_node - 1) * 2;
	data->exec->multi_tube = (int *)malloc(sizeof(int) * (data->exec->nb_tube));
	if (!data->exec->multi_tube)
		return ;
}

void	error_pid(t_data *data)
{
	close_tubes(data);
	free_resources(data);
	exit(1);
}
