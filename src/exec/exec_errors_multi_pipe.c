/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors_multi_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:03:32 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 07:29:22 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	file_not_found_multi(t_data *data, t_list_arg *tok)
{
	if (tok->file_array[0] != NULL)
		write(STDERR_FILENO, tok->file_array[0], ft_strlen(tok->file_array[0]));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
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
	return ;
}

void	error_execve_multi(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array != NULL)
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": command not found\n", 21);
	free_prompt(data);
	free(data->signal);
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	free_exec(data);
	exit(127);
}

void	error_cmd(t_data *data, t_list_arg *tok)
{
	if (data->tokenizer->cmd_array != NULL)
	{
		if (tok->cmd_array[0] != NULL)
			write(STDERR_FILENO, tok->cmd_array[0],
				ft_strlen(tok->cmd_array[0]));
		write(STDERR_FILENO, ": command not found\n", 21);
		close_tubes(data);
		free(data->signal);
		free_tmp_struct(data);
		free(data->exec->multi_tube);
		free(data->exec->pid);
		free_exec(data);
		ft_lst_arg_clear(&data->lst);
		ft_clear_tokenizer(data);
		free_prompt(data);
		exit(127);
	}
	if (tok->cmd_array[0][0] == '\0')
		free(data->exec->final_cmd);
	if (tok->cmd_array && tok->cmd_array[0])
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	cleanup_and_exit(data, 127);
}

void	error_init(t_data *data, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (data->exec->multi_tube)
		free(data->exec->multi_tube);
	if (data->exec->pid)
		free(data->exec->pid);
	free_exec(data);
	exit(1);
}

void	hd_or_rdr_no_cmd_multi(t_data *data, t_list_arg *tok)
{
	if (data->tokenizer->cmd_array != NULL)
	{
		if (tok->cmd_array[0] != NULL)
			write(STDERR_FILENO, tok->cmd_array[0],
				ft_strlen(tok->cmd_array[0]));
		write(STDERR_FILENO, ": command not found\n", 21);
		close_tubes(data);
		free(data->signal);
		free(data->exec->multi_tube);
		free(data->exec->pid);
		rm_tmp_file_hd(data);
		free_exec(data);
		ft_lst_arg_clear(&data->lst);
		ft_clear_tokenizer(data);
		free_prompt(data);
		exit(127);
	}
	if (tok->cmd_array[0][0] == '\0')
		free(data->exec->final_cmd);
	if (tok->cmd_array && tok->cmd_array[0])
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	cleanup_and_exit(data, 127);
}
