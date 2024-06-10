/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 16:49:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_files(t_data *data)
{
	if (data->tokenizer->array_sign[0] == STDOUTS)
	{
		data->exec->outfile = open(data->tokenizer->file_array[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data);
	}
	else if (data->tokenizer->array_sign[0] == STDINS)
	{
		data->exec->infile = open(data->tokenizer->file_array[0], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found(data);
	}
}

void	exec_sub_proc(t_data *data)
{
	data->exec->cmd = build_cmd(data);
	if (!data->exec->cmd)
		cmd_not_found(data);
	if(is_redir(data))
	{
		init_files(data);
		if (data->exec->infile && data->exec->infile != 1)
		{
			dup2(data->exec->infile, STDIN_FILENO);
			close(data->exec->infile);
		}
		if (data->exec->outfile && data->exec->outfile != -1)
		{
			dup2(data->exec->outfile, STDOUT_FILENO);
			close(data->exec->outfile);
		}
	}
	//printf("FINAL_CMD --> %s\n", data->exec->cmd);
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	error_excve(data);
}