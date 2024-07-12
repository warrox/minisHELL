/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc_utils_one.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:19:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 17:05:24 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	check_and_dup_second(t_data *data)
{
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(data->exec->tube[0], STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
}

void	execute_builtin_second_pipe(t_data *data, t_list_arg *tmp, int i)
{
	init_files_builtin(data, tmp, i);
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(data->exec->tube[0], STDIN_FILENO);
	if (data->exec->outfile != 1)
		dup2(data->exec->outfile, STDOUT_FILENO);
	exec_builtin(data, tmp, is_a_builtin(tmp));
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	free_resources_single(data);
	exit(1);
}

void	execute_builtin_first_pipe(t_data *data, t_list_arg *rpl, int i)
{
	init_files_builtin(data, rpl, i);
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	if (data->exec->outfile != 1)
		dup2(data->exec->outfile, STDOUT_FILENO);
	else
		dup2(data->exec->tube[1], STDOUT_FILENO);
	exec_builtin(data, rpl, is_a_builtin(rpl));
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	free_resources_single(data);
	exit(1);
}

void	check_and_dup_fisrt(t_data *data)
{
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(data->exec->tube[1], STDOUT_FILENO);
}

void	check_dir_and_perm_op(t_data *data, t_list_arg *rpl)
{
	if (access(data->exec->cmd, F_OK) != 0)
		error_dir_file_not_found(data, rpl);
	if (access(data->exec->cmd, X_OK) != 0)
		error_permission_denied_op(data, rpl);
	if (check_dir(data->exec->cmd) == -1)
		error_is_a_dir_op(data, rpl);
}
