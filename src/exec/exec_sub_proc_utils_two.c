/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc_utils_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:08:53 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 16:17:54 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_outfile_cmd(t_data *data, t_list_arg *tok, int i)
{
	data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY,
			0644);
	if (data->exec->outfile < 0)
		file_not_found(data, tok);
	dup2(data->exec->outfile, STDOUT_FILENO);
	close(data->exec->outfile);
}

void	init_outfile_builtin(t_data *data, t_list_arg *tok, int i)
{
	data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY,
			0644);
	if (data->exec->outfile < 0)
		file_not_found(data, tok);
}

void	init_files_builtin(t_data *data, t_list_arg *tok, int i)
{
	if (tok->file_array[0] == NULL)
		return ;
	if (tok->array_sign[i] == STDOUTS)
		init_outfile(data, tok, i);
	else if (tok->array_sign[i] == STDINS)
	{
		data->exec->infile = open(tok->file_array[i], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found(data, tok);
	}
	else if (tok->array_sign[i] == APPEND)
	{
		if (data->exec->outfile != 1)
			close (data->exec->outfile);
		data->exec->outfile = open(tok->file_array[i],
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data, tok);
	}
}

void	init_files(t_data *data, t_list_arg *tok, int i)
{
	if (tok->file_array[0] == NULL)
		return ;
	if (tok->array_sign[i] == STDOUTS)
		init_outfile_cmd(data, tok, i);
	else if (tok->array_sign[i] == STDINS)
	{
		data->exec->infile = open(tok->file_array[i], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found(data, tok);
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else if (tok->array_sign[i] == APPEND)
	{
		data->exec->outfile = open(tok->file_array[i],
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data, tok);
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
}
