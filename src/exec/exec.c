/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:02:48 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/28 17:28:03 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	reset_in_out(t_data *data)
{
	data->exec->infile = 0;
	data->exec->outfile = 1;
}

int	nb_node(t_data *data)
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
	data->exec->infile = 0;
	data->exec->here_doc = ZERO_INIT;
	data->exec->nb_cmd = ZERO_INIT;
	data->exec->outfile = 1;
	data->exec->nb_node = ZERO_INIT;
	data->exec->pid_1 = NULL_INIT;
	data->exec->pid_2 = NULL_INIT;
	data->exec->pid = NULL_INIT;
	data->exec->tube[0] = ZERO_INIT;
	data->exec->tube[1] = ZERO_INIT;
	data->exec->path = NULL_INIT;
	data->exec->path_cmd = NULL_INIT;
	data->exec->final_cmd = NULL_INIT;
	data->exec->nb_tube = ZERO_INIT;
	data->exec->index = -1;
}

void exec_single_cmd(t_data *data)
{
    handle_signal_children();
    init_tmp_struct(data);
    check_here_doc(data);
    if (is_a_builtin(data->tokenizer) == -1 || is_a_builtin(data->tokenizer) == -2)
    {
        data->exec->pid_1 = fork();
        if (data->exec->pid_1 == -1)
            return;
        if (data->exec->pid_1 == 0)
            exec_sub_proc(data);
        else
        {
            int status;
            waitpid(data->exec->pid_1, &status, 0);
            data->exit_status = WEXITSTATUS(status);
        }
    }
    else
    {
        exec_sub_proc(data);
        free_tmp_struct(data);
    }
}

int	init_exec(t_data *data)
{
	int	i;
	i = ZERO_INIT;
	init_struct_exec(data);
	build_tab_env(data);
	data->exec->path = get_path(data);
	data->exec->path_cmd = ft_split(data->exec->path, ':');
	if (nb_node(data) == 1)
		exec_single_cmd(data);
	else if (nb_node(data) == 2)
		exec_one_pipe(data);
	else
		exec_multi_pipe(data);
	return (WEXITSTATUS(data->exit_status));
}	
