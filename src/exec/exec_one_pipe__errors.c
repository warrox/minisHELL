/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_pipe__errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:21:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 08:33:08 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	error_permission_denied_op(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": Permission denied\n", 20);
	data->exit_status = 1;
	cleanup_and_exit_op(data, 1);
}

void	error_is_a_dir_op(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": Is a directory\n", 17);
	cleanup_and_exit_op(data, 1);
}

void	free_resources_op(t_data *data)
{
	free(data->exec->pid);
	free_tmp_struct(data);
	free_exec(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
}

void	cleanup_and_exit_op(t_data *data, int exit_code)
{
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	free_resources_op(data);
	exit(exit_code);
}

void	error_cmd_op(t_data *data, t_list_arg *tok)
{
	if (!tok->cmd_array[0])
	{
		write(2, ": command not found\n", 20);
		free(data->exec->final_cmd);
		free(data->signal);
		free_prompt(data);
		free_tmp_struct(data);
		close(data->exec->tube[0]);
		close(data->exec->tube[1]);
		free_exec(data);
		ft_lst_arg_clear(&data->lst);
		ft_clear_tokenizer(data);
		exit(127);
	}
	if (tok->cmd_array[0][0] == '\0')
		free(data->exec->final_cmd);
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": command not found\n", 20);
	cleanup_and_exit_op(data, 127);
}
