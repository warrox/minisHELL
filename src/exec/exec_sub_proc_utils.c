/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:20 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 15:18:00 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exit_cmd_here_doc(t_data *data, t_list_arg *rpl)
{
	execve(data->exec->cmd, rpl->cmd_array, data->exec->my_envp);
	error_excve(data);
	exit(1);
}

void	exit_only_here_doc(t_data *data)
{
	close(data->spe_fd);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(1);
}

void	execute_builtin_sub_proc(t_data *data, t_list_arg *rpl, int i)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	init_files_builtin(data, rpl, i);
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	if (data->exec->infile != 0)
		(dup2(data->exec->infile, STDIN_FILENO), close(data->exec->infile));
	if (is_a_builtin(rpl) == EXIT)
		(close(save_stdin), close(save_stdout));
	exec_builtin(data, rpl, is_a_builtin(rpl));
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	execute_builtin_multi(t_data *data, t_list_arg *rpl, int i)
{
	i = 0;
	setup_pipes(data, rpl);
	exec_builtin(data, rpl, is_a_builtin(rpl));
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
}

void	check_dir_and_perm_sgl(t_data *data, t_list_arg *rpl)
{
	if (access(data->exec->cmd, F_OK) != 0)
		error_dir_file_not_found(data, rpl);
	if (access(data->exec->cmd, X_OK) != 0)
		error_permission_denied_sgl(data, rpl);
	if (check_dir(data->exec->cmd) == -1)
		error_is_a_dir_sgl(data, rpl);
}
