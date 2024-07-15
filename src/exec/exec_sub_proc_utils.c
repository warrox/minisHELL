/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:20 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 16:16:03 by cyferrei         ###   ########.fr       */
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
	if (is_redir(rpl))
	{
		while (rpl->file_array[i] != 0)
			init_files_builtin(data, rpl, i++);
	}
	init_files_builtin(data, rpl, i);
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
