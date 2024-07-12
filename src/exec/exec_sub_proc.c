/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 14:49:31 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	second_child_process(t_data *data)
{
	int			i;
	t_list_arg	*tmp;

	i = ZERO_INIT;
	tmp = data->tokenizer;
	reset_in_out(data);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (is_a_builtin(tmp) != -1 && is_a_builtin(tmp) != -2)
		execute_builtin_second_pipe(data, tmp, i);
	data->exec->cmd = build_cmd(data, tmp);
	if (data->exec->cmd == NULL)
		error_cmd_op(data, tmp);
	if (is_redir(tmp))
	{
		while (tmp->file_array[i] != 0)
			init_files(data, tmp, i++);
	}
	check_and_dup_second(data);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tmp) != 0)))
		hd_or_rdr_no_cmd(data);
	check_dir_and_perm_op(data, tmp);
	(close(data->exec->tube[0]), close(data->exec->tube[1]));
	execve(data->exec->cmd, tmp->cmd_array, data->exec->my_envp);
	error_excve(data);
}

void	first_child_process(t_data *data)
{
	int			i;
	t_list_arg	*rpl;

	rpl = data->tokenizer;
	i = 0;
	reset_in_out(data);
	if (is_a_builtin(rpl) != -1 && is_a_builtin(rpl) != -2)
		execute_builtin_first_pipe(data, rpl, i);
	data->exec->cmd = build_cmd(data, rpl);
	if (data->exec->cmd == NULL)
		error_cmd_op(data, rpl);
	if (is_redir(rpl))
	{
		while (rpl->file_array[i])
			init_files(data, rpl, i++);
	}
	check_and_dup_fisrt(data);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(rpl) != 0)))
		hd_or_rdr_no_cmd(data);
	check_dir_and_perm_op(data, rpl);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	execve(data->exec->cmd, rpl->cmd_array, data->exec->my_envp);
	error_excve(data);
}

void	exec_one_pipe(t_data *data)
{
	int	status;

	status = 0;
	if (pipe(data->exec->tube) < 0)
		exit_error("pipe failed!\n");
	init_tmp_struct(data);
	check_here_doc(data);
	data->exec->pid_1 = fork();
	if (data->exec->pid_1 == -1)
		free_exec(data);
	if (data->exec->pid_1 == 0)
		first_child_process(data);
	data->exec->pid_2 = fork();
	if (data->exec->pid_2 == -1)
		free_exec(data);
	if (data->exec->pid_2 == 0)
		second_child_process(data);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	data->exit_status = WEXITSTATUS(status);
	waitpid(data->exec->pid_1, &status, 0);
	waitpid(data->exec->pid_2, &status, 0);
}

void	exec_sub_proc(t_data *data)
{
	int			i;
	t_list_arg	*rpl;

	rpl = data->tokenizer;
	i = ZERO_INIT;
	if (is_a_builtin(rpl) != -1 && is_a_builtin(rpl) != -2)
		return (execute_builtin_sub_proc(data, rpl, i));
	data->exec->cmd = build_cmd(data, rpl);
	if (is_redir(rpl))
	{
		while (rpl->file_array[i] != 0)
			init_files(data, rpl, i++);
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(rpl) != 0)))
		hd_or_rdr_no_cmd(data);
	if (data->exec->cmd == NULL)
		error_cmd_single(data, rpl);
	if (data->exec->here_doc && data->exec->cmd)
		exit_cmd_here_doc(data, rpl);
	check_dir_and_perm_sgl(data, rpl);
	if (data->exec->here_doc)
		exit_only_here_doc(data);
	execve(data->exec->cmd, rpl->cmd_array, data->exec->my_envp);
	error_excve(data);
}
