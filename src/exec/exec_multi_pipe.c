/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/24 17:24:06 by cyferrei         ###   ########.fr       */
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

void	children_process(t_data *data)
{
	int i;
	t_list_arg *tmp = data->tokenizer;

	i = 0;
	check_here_doc(data);
	data->exec->pid[data->exec->index] = fork();
	if (data->exec->pid[data->exec->index] == -1)
	{
		close_tubes(data);
		free_resources(data);
		exit(1);
	}
	if (data->exec->pid[data->exec->index] == 0)
	{
		while(i != data->exec->index && tmp)
		{
			tmp = tmp->next;
			i++;
		}
		data->exec->cmd = build_cmd(data, tmp);
		if (data->exec->cmd == NULL)
			error_cmd(data, tmp);
		setup_pipes(data, tmp);
		if (access(data->exec->cmd, F_OK) != 0)
			error_dir_file_not_found(data, tmp);
		if (access(data->exec->cmd, X_OK) != 0)
			error_permission_denied(data, tmp);
		if (check_dir(data->exec->cmd) == -1)
			error_is_a_dir_mup(data, tmp);
		close_tubes(data);
		execve(data->exec->cmd, tmp->cmd_array, NULL);
		error_execve_multi(data, tmp);
	}
}

void	exec_multi_pipe(t_data *data)
{
	int	i;
	int status = 0;

	i = ZERO_INIT;
	data->exec->nb_node = nb_node(data);
	data->exec->nb_tube = (data->exec->nb_node - 1) * 2;
	data->exec->multi_tube = (int *)malloc(sizeof(int) * (data->exec->nb_tube));
	if (!data->exec->multi_tube)
		error_init(data, "Failed to allocate memory for pipes!\n");
	data->exec->pid = ft_calloc(data->exec->nb_node + 1, sizeof(pid_t));
	if (!data->exec->pid)
		error_init(data, "Failed to int pid!\n");
	init_tubes(data);
	init_tmp_struct(data);
	// print_exec_utils(data);
	while(++(data->exec->index) < data->exec->nb_node)
	{
		if(!data->exec->multi_tube)
			init_tubes(data);
		children_process(data);
	}
	// free_tmp_struct(data);
	close_tubes(data);
	int j = 0;
	while (j < data->exec->nb_node)
		waitpid(data->exec->pid[j++], &status, 0);
	free(data->exec->multi_tube);
	free(data->exec->pid);
}
void error_dir_file_not_found(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(2, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(2, ": No such file or directory\n", 28);
	cleanup_and_exit(data, 1);
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