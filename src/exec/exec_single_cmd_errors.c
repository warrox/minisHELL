/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:21:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 14:33:31 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void error_permission_denied_sgl(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": Permission denied\n", 20);
	cleanup_and_exit_single(data, 1);
}

void error_is_a_dir_sgl(t_data *data, t_list_arg *tok)
{
	if (data->exec->final_cmd)
		free(data->exec->final_cmd);
	if (tok->file_array && tok->file_array[0])
		write(2, tok->file_array[0], ft_strlen(tok->file_array[0]));
	write(2, ": Is a directory\n", 17);
	cleanup_and_exit_single(data, 1);
}

void free_resources_single(t_data *data)
{
	// free(data->exec->final_cmd);
	// free(data->exec->multi_tube);
	free(data->exec->pid);
	free_tmp_struct(data);
	free_exec(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
}

void cleanup_and_exit_single(t_data *data, int exit_code)
{
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	// close_tubes(data);
	free_resources_single(data);
	exit(exit_code);
}
void error_cmd_single(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": command not found\n", 20);
	cleanup_and_exit_single(data, 127);
}
