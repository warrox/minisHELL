/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:36:46 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/10 12:15:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	hd_or_rdr_no_cmd(t_data *data)
{
	ft_clear_tokenizer(data);
	free_prompt(data);
	free(data->signal);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	if (data->exec->infile)
		close(data->exec->infile);
	if (data->exec->outfile)
		close(data->exec->outfile);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	exit(126);
}

void	exit_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(127); // voir exit code plus tard
}

void	error_excve(t_data *data)
{
	if (data->tokenizer->cmd_array != NULL)
		write(2, data->tokenizer->cmd_array[0], ft_strlen(data->tokenizer->cmd_array[0]));
	data->exit_status = 126;
	write(2, ": command not found\n", 21);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	exit(126);
}

void	cmd_not_found(t_data *data)
{
	if (data->tokenizer->cmd_array != NULL && data->tokenizer->cmd_array[0] != NULL)
		write(2, data->tokenizer->cmd_array[0], ft_strlen(data->tokenizer->cmd_array[0]));
	data->exit_status = 127;
	write(2, ": command not found\n", 21);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	rm_tmp_file(data);
	ft_lst_arg_clear(&data->lst);
	exit(127);
}

void	file_not_found(t_data *data, t_list_arg *tok)
{
	char *join = NULL;
	
	if (tok->file_array[0] != NULL)
		join = ft_strjoin(tok->file_array[0], ": No such file or directory\n");
	if (!join)
		return;
	ft_putstr_fd(join, STDERR_FILENO);
	free(data->exec->cmd);
	ft_clear_tokenizer(data);
	close(data->exec->tube[1]);
	close(data->exec->tube[0]);
	free(data->tmp_files);
	free_exec(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(1);
}

