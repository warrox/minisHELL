/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors_multi_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:03:32 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/25 13:50:01 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	file_not_found_multi(t_data *data, t_list_arg *tok)
{
	if (tok->file_array[0] != NULL)
		write(2, tok->file_array[0], ft_strlen(tok->file_array[0]));
	write(2, ": No such file or directory\n", 29);
	free(data->exec->cmd);
	ft_clear_tokenizer(data);
	close_tubes(data);
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	free_exec(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(1);
}

void	error_execve_multi(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array != NULL)
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": command not found\n", 21);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	free_exec(data);
	exit(127);
}

void error_cmd(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": command not found\n", 20);
	cleanup_and_exit(data, 127);
}

void	error_init(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	if (data->exec->multi_tube)
		free(data->exec->multi_tube);
	if (data->exec->pid)
		free(data->exec->pid);
	free_exec(data);
	exit(1); // need to be checked !
}

void error_permission_denied(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": Permission denied\n", 20);
	cleanup_and_exit(data, 1);
}

void error_dir_file_not_found(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": No such file or directory\n", 28);
	cleanup_and_exit(data, 1);
}

void error_is_a_dir_mup(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": Is a directory\n", 17);
	cleanup_and_exit(data, 1);
}

