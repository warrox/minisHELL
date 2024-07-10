/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_multi_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:41:44 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/10 19:23:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_files_multi(t_data *data, t_list_arg *tok, int i)
{
    if (tok->array_sign[i] == STDOUTS)
    {
        data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
        if (data->exec->outfile < 0)
            file_not_found_multi(data, tok);
    }
    else if (tok->array_sign[i] == STDINS)
    {
        data->exec->infile = open(tok->file_array[i], O_RDONLY);
        if (data->exec->infile < 0)
            file_not_found_multi(data, tok);
    }
	else if (tok->array_sign[i] == APPEND)
	{
		data->exec->outfile = open(tok->file_array[i], O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found_multi(data, tok);
	}
}

void setup_pipes(t_data *data, t_list_arg *tmp)
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