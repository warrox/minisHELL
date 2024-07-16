/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:02:48 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 09:54:18 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	nb_node(t_data *data)
{
	int			i;
	t_list_arg	*tmp;

	tmp = NULL_INIT;
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
	data->exit_status = 0;
	data->exec->ctrl_heredoc = 0;
}

void	helper_single_cmd(t_data *data, t_list_arg *rpl, int status)
{
	if (is_a_builtin(rpl) == -1 || is_a_builtin(rpl) == -2)
	{
		data->exec->pid_1 = fork();
		if (data->exec->pid_1 == -1)
			return ;
		if (data->exec->pid_1 == 0)
			exec_sub_proc(data);
		else
		{
			waitpid(data->exec->pid_1, &status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				data->exit_status = (WTERMSIG(status));
				data->exit_status += 128;
			}
		}
	}
	else
	{
		exec_sub_proc(data);
		free_tmp_struct(data);
	}
}

void	exec_single_cmd(t_data *data)
{
	int			status;
	t_list_arg	*rpl;

	status = 0;
	rpl = data->tokenizer;
	init_tmp_struct(data);
	check_here_doc(data);
	handle_signal_children();
	helper_single_cmd(data, rpl, status);
}

int	init_exec(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	init_struct_exec(data);
	build_tab_env(data);
	g_sig = 0;
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
