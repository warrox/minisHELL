/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_multi_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:41:44 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 13:34:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_outfile(t_data *data, t_list_arg *tok, int i)
{
	dprintf(2, "file_aray = %s\n", tok->file_array[i]);
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY,
			0644);
	dprintf(2, "fd = %d\n", data->exec->outfile);
	if (data->exec->outfile < 0)
		file_not_found_multi(data, tok);
}

void	init_files_multi(t_data *data, t_list_arg *tok, int i)
{
 	if (tok->array_sign[i] == STDOUTS)
		init_outfile(data, tok, i);
	if (tok->array_sign[i] == STDINS)
	{
		if (data->exec->infile != 0)
			close(data->exec->infile);
		data->exec->infile = open(tok->file_array[i], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found_multi(data, tok);
	}
	else if (tok->array_sign[i] == APPEND)
	{
		if (data->exec->outfile != 1)
			close(data->exec->outfile);
		data->exec->outfile = open(tok->file_array[i],
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found_multi(data, tok);
		close(data->exec->outfile);
	}
	dprintf(2, "fd = %d\n", data->exec->outfile);
}

void	setup_pipes(t_data *data, t_list_arg *tmp)
{
	if (data->exec->index == 0)
		first_pipe(data, tmp);
	else if (data->exec->index == data->exec->nb_node - 1)
		last_pipe(data, tmp);
	else
		intermediate_pipe(data, tmp);
}

void	init_tubes(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	// dprintf(2, "ICI %d", data->exec->nb_node);
	while (i < data->exec->nb_node - 1)
	{
		if (pipe(data->exec->multi_tube + 2 * i) < 0)
			error_init(data, "Fail to init tubes\n");
		i++;
	}
}
