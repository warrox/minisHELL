/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:01:39 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/21 14:38:29 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	intermediate_pipe(t_data *data, t_list_arg *tok)
{
	int	i;

	i = 0; 
	if (is_redir(tok))
	{
		while(tok->array_sign[i] != 0)
		{
			// if (data->exec->infile != 0 && data->exec->infile > 0)
			// 	close(data->exec->infile);
			// if (data->exec->outfile != 1 && data->exec->outfile > 0)
			// 	close(data->exec->outfile);
			init_files_multi(data, tok, i++);
		}
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
	{
		hd_or_rdr_no_cmd_multi(data);
	}
	if (data->exec->infile != 0)
	{
		dprintf(2, "NB %d\n", data->exec->infile);
		dprintf(2, "TEST\n");
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
	{
		dup2(data->exec->multi_tube[2 * data->exec->index + 1], STDOUT_FILENO);
	}
}

void	last_pipe(t_data *data, t_list_arg *tok)
{
	int	i;
	i = 0;
	if (is_redir(tok))
	{
		while(tok->file_array[i])
		{
			// if (data->exec->infile != 0 && data->exec->infile > 0)
			// 	close(data->exec->infile);
			// if (data->exec->outfile != 1 && data->exec->outfile > 0)
			// 	close(data->exec->outfile);
			init_files_multi(data, tok, i++);
		}
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
	{
		dprintf(2, "TAMERE %d\n", data->exec->infile);
		hd_or_rdr_no_cmd_multi(data);
	}
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(data->exec->multi_tube[data->exec->index * 2 - 2], STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close (data->exec->outfile);
	}
	else
		dup2 (1, STDOUT_FILENO);
}

void	first_pipe(t_data *data, t_list_arg *tok)
{
	int	i;
	
	i = ZERO_INIT;
	if (is_redir(tok))
	{
		while(tok->file_array[i])
		{
			// if (data->exec->infile != 0 && data->exec->infile > 0)
			// 	close(data->exec->infile);
			// if (data->exec->outfile != 1 && data->exec->outfile > 0)
			// 	close(data->exec->outfile);
			init_files_multi(data, tok, i++);
		}
	}
	dprintf(2, "IN : %d || OUT : %d\n", data->exec->infile, data->exec->outfile);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
	{
		hd_or_rdr_no_cmd_multi(data);
	}
	if (data->exec->infile != 0)
	{
		dprintf(2, "INFILE!\n");
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(0, STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		dprintf(2, "%s\n", tok->file_array[1]);
		dprintf(2, "OUTFILE!\n");
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(data->exec->multi_tube[1], STDOUT_FILENO);
}

void	close_tubes(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	if (data->exec->multi_tube)
	{
		while(i < data->exec->nb_tube)
		{
			close(data->exec->multi_tube[i]);
			i++;
		}
	}
}

void	init_tubes(t_data *data)
{
	int i;
	
	i = ZERO_INIT;
	while(i < data->exec->nb_node - 1)
	{
		// printf("ICI -> %d\n", data->exec->nb_tube);
		if (pipe(data->exec->multi_tube + 2 * i) < 0)
			error_init(data, "Fail to init tubes\n");
		i++;
	}
}