/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 12:54:08 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	check_dir_and_perm(t_data *data, t_list_arg *tmp)
{
	if (access(data->exec->cmd, F_OK) != 0)
		error_dir_file_not_found(data, tmp);
	if (access(data->exec->cmd, X_OK) != 0)
		error_permission_denied(data, tmp);
	if (check_dir(data->exec->cmd) == -1)
		error_is_a_dir_mup(data, tmp);
}

void	execute_builtin(t_data *data, t_list_arg *tmp, int i)
{
	if (is_redir(tmp))
	{
		while (tmp->file_array[i] != 0)
			init_files_builtin(data, tmp, i++);
	}
	setup_pipes(data, tmp);
	exec_builtin(data, tmp, is_a_builtin(tmp));
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	close_tubes(data);
	free_resources(data);
	exit(1);
}

void	print_tmp_files(t_data *data)
{
	t_tmp_files	*current;

	current = data->tmp_files;
	printf("Liste des fichiers temporaires :\n");
	while (current != NULL)
	{
		printf("Nom du fichier : %s, Descripteur de fichier : %d\n",
			current->file_name, current->fd);
		current = current->next;
	}
}

void	children_process(t_data *data)
{
	int			i;
	t_list_arg	*tmp;

	tmp = data->tokenizer;
	i = 0;
	check_here_doc(data);
	if (g_sig == 2 || data->exec->ctrl_heredoc == 2)
		return ;
	data->exec->pid[data->exec->index] = fork();
	if (data->exec->pid[data->exec->index] == -1)
		error_pid(data);
	if (data->exec->pid[data->exec->index] == 0)
	{
		while (i++ != data->exec->index && tmp)
			tmp = tmp->next;
		if (is_a_builtin(tmp) != -1 && is_a_builtin(tmp) != -2)
		{
			execute_builtin_multi(data, tmp, i);
			close_tubes(data);
			free(data->signal);
			free_prompt(data);
			ft_clear_tokenizer(data);
			free(data->exec->multi_tube);
			free(data->exec->pid);
			free_tmp_struct(data);
			ft_lst_arg_clear(&data->lst);
			free_exec(data);
			exit(1);
		}
		dprintf(2, "TEST\n");
		data->exec->cmd = build_cmd(data, tmp);
		if (data->exec->cmd == NULL && (data->exec->here_doc
				|| (is_redir(tmp) != 0)))
			hd_or_rdr_no_cmd_multi(data, tmp);
		if (data->exec->cmd == NULL || tmp->cmd_array[0][0] == '\0')
			error_cmd(data, tmp);
		setup_and_check(data, tmp);
	}
}

void	exec_multi_pipe(t_data *data)
{
	int	i;
	int	status;
	int	j;

	i = ZERO_INIT;
	init_multi_pipe(data);
	if (!data->exec->multi_tube)
		error_init(data, "Failed to allocate memory for pipes!\n");
	data->exec->pid = ft_calloc(data->exec->nb_node + 1, sizeof(pid_t));
	if (!data->exec->pid)
		error_init(data, "Failed to int pid!\n");
	(init_tmp_struct(data), init_tubes(data));
	while (++(data->exec->index) < data->exec->nb_node)
	{
		if (!data->exec->multi_tube)
			init_tubes(data);
		children_process(data);
	}
	close_tubes(data);
	check_open_files(data);
	j = 0;
	while (j < data->exec->nb_node)
		waitpid(data->exec->pid[j++], &status, 0);
	data->exit_status = WEXITSTATUS(status);
	(free(data->exec->pid), free(data->exec->multi_tube));
}
