/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:01:39 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:23 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	intermediate_pipe(t_data *data, t_list_arg *tok)
{
	int	i;

	i = 0;
	(void)tok;
	reset_in_out(data);
	if (is_redir(tok))
	{
		while(tok->array_sign[i] != 0)
			init_files(data, tok, i++);
	}
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
	{
		dprintf(2, "LA -> %d\n", data->exec->index);
		// dprintf(2, " ICI %d\n", data->exec->multi_tube[2 * data->exec->index + 1]);
		dup2(data->exec->multi_tube[2 * data->exec->index + 1], STDOUT_FILENO);
	}
	// dprintf(2, "out %d\n", data->exec->outfile);
}

// void	last_pipe(t_data *data, t_list_arg *tok){
// 	int i;
	
// 	i = 0;
// 	reset_in_out(data);
// 	if (is_redir(tok))
// 	{
// 		while(tok->array_sign[i] != 0)
// 			init_files(data, tok, i++);
// 	}
// 	dprintf(2, "Redi pipe %d: infile: %d outfile: %d\n", data->exec->nb_node , data->exec->infile, data->exec->outfile);
// 	dup2(0, STDIN_FILENO);
// 	dup2(1, STDOUT_FILENO);
// 	if (data->exec->infile != 0){
// 		dup2(data->exec->infile, STDIN_FILENO);
// 		close(data->exec->infile);
// 	}
// 	if (data->exec->outfile != 1)
// 	{
// 		dprintf(2, "TCHOIN\n");
// 		dup2(data->exec->outfile, STDOUT_FILENO);
// 		close (data->exec->outfile);
// 	}
// }

void	last_pipe(t_data *data, t_list_arg *tok)
{
	int	i;
	(void)tok;
	i = 0;
	dprintf(2, "idx_bf %d\n", data->exec->index);
	reset_in_out(data);
	if (is_redir(tok))
	{
		while(tok->array_sign[i] != 0)
			init_files(data, tok, i++);
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
		dprintf(2, "TCHOIN\n");
		dup2(data->exec->outfile, STDOUT_FILENO);
		close (data->exec->outfile);
	}
	else
		dup2 (1, STDOUT_FILENO);
}

void	first_pipe(t_data *data, t_list_arg *tok)
{
	int	i;
	(void)tok;
	i = ZERO_INIT;
	reset_in_out(data);
	if (is_redir(tok))
	{
		while(tok->array_sign[i] != 0)
			init_files(data, tok, i++);
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
			free(data->exec->multi_tube);
		i++;
	}
}