/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/11 12:54:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_files(t_data *data, int i)
{
	if (data->tokenizer->array_sign[i] == STDOUTS)
	{
		data->exec->outfile = open(data->tokenizer->file_array[i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data);
		dup2(data->exec->outfile, STDOUT_FILENO);	
		close(data->exec->outfile);

	}
	else if (data->tokenizer->array_sign[i] == STDINS)
	{
		data->exec->infile = open(data->tokenizer->file_array[i], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found(data);
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);

	}
}

void	exec_sub_proc(t_data *data)
{
	int	i;
	
	i = ZERO_INIT; 
	data->exec->cmd = build_cmd(data);
	if (!data->exec->cmd)
		cmd_not_found(data);
	if(is_redir(data))
	{
		while(data->tokenizer->array_sign[i] != 0)
			init_files(data, i++);
	}
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	error_excve(data);
}