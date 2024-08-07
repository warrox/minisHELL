/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:47:07 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 15:27:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	check_dir(char *file)
{
	int	res;

	res = open(file, O_DIRECTORY);
	if (access(file, X_OK) == 0 && res != -1)
	{
		close(res);
		return (-1);
	}
	if (access(file, X_OK) == 0 && access(file, F_OK) == 0)
	{
		return (0);
	}
	return (0);
}

void	cleanup_and_exit(t_data *data, int exit_code)
{
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	close_tubes(data);
	free_resources(data);
	exit(exit_code);
}

void	free_resources(t_data *data)
{
	rm_tmp_file(data);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	free_tmp_struct(data);
	free_exec(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
}

void	close_tubes(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	if (data->exec->multi_tube)
	{
		while (i < data->exec->nb_tube)
		{
			close(data->exec->multi_tube[i]);
			i++;
		}
	}
}
