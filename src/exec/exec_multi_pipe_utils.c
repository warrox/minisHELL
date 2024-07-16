/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:22:59 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 13:34:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	setup_and_check(t_data *data, t_list_arg *tmp)
{
	setup_pipes(data, tmp);
	check_dir_and_perm(data, tmp);
	close_tubes(data);
	check_open_files(data);
	execve(data->exec->cmd, tmp->cmd_array, data->exec->my_envp);
	error_execve_multi(data, tmp);
}

void	check_open_files(t_data *data)
{
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
}

void	intermediate_pipe(t_data *data, t_list_arg *tok)
{
	int	i;

	i = 0;
	if (is_redir(tok))
	{
		while (tok->file_array[i])
			init_files_multi(data, tok, i++);
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
		hd_or_rdr_no_cmd_multi(data, tok);
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(data->exec->multi_tube[2 * data->exec->index - 2], STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(data->exec->multi_tube[2 * data->exec->index + 1], STDOUT_FILENO);
}

void	last_pipe(t_data *data, t_list_arg *tok)
{
	int	i;
	int index;
	
	i = 0;
	if (is_redir(tok))
	{
		while (tok->file_array[i])
			init_files_multi(data, tok, i++);
	}
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
	{
		index = data->exec->index * 2 - 2;
        if (index >= 0 && index < data->exec->nb_tube)
            dup2(data->exec->multi_tube[index], STDIN_FILENO);
	}
	if (data->exec->outfile != 1)
	{
		dprintf(2, "DUPIIINN\n");
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(1, STDOUT_FILENO);
}

void	first_pipe(t_data *data, t_list_arg *tok)
{
	int	i;

	i = ZERO_INIT;
	if (is_redir(tok))
	{
		while (tok->file_array[i])
			init_files_multi(data, tok, i++);
	}
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(0, STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(data->exec->multi_tube[1], STDOUT_FILENO);
}
