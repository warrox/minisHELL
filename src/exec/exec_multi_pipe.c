/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:27:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/10 16:11:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	intermediate_pipe(t_data *data, t_list_arg *tok)
{
	int	i;

	i = 0;
	if (is_redir(tok))
	{
		while(tok->file_array[i])
			init_files_multi(data, tok, i++);
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
		hd_or_rdr_no_cmd_multi(data);
	if (data->exec->infile != 0)
	{
		// dprintf(2, "tok -> %s\n", tok->cmd_array[0]);
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
	i = 0;
	if (is_redir(tok))
	{
		while(tok->file_array[i])
			init_files_multi(data, tok, i++);
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
	{
		// dprintf(2, "TAMERE %d\n", data->exec->infile);
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
			init_files_multi(data, tok, i++);
	}
	// dprintf(2, "IN : %d || OUT : %d\n", data->exec->infile, data->exec->outfile);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tok) != 0)))
	{
		hd_or_rdr_no_cmd_multi(data);
	}
	if (data->exec->infile != 0)
	{
		// dprintf(2, "INFILE!\n");
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
	}
	else
		dup2(0, STDIN_FILENO);
	if (data->exec->outfile != 1)
	{
		// dprintf(2, "%s\n", tok->file_array[1]);
		// dprintf(2, "OUTFILE!\n");
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
	else
		dup2(data->exec->multi_tube[1], STDOUT_FILENO);
}
void	children_process(t_data *data)
{
	int i;
	t_list_arg *tmp = data->tokenizer;
	t_tmp_files *tempo = data->tmp_files;
	
	i = 0;
	//handle_signal_children();
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
		if (is_a_builtin(tmp) != -1 && is_a_builtin(tmp) != -2)
		{
			init_files_builtin(data, tmp, i);
			setup_pipes(data, tmp);
			exec_builtin(data, tmp, is_a_builtin(tmp));
			if (data->exec->outfile != 1)
				close(data->exec->outfile);
			if (data->exec->infile != 0)
				close (data->exec->infile);
			// close(data->exec->tube[0]);
			// close(data->exec->tube[1]);
			close_tubes(data);
			free_resources(data);
			exit(1);
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
		//dprintf(2, "IN %d| OUT %d | cmd %s\n", data->exec->infile, data->exec->outfile, data->exec->cmd);
		close_tubes(data);
		if (data->exec->outfile != 1)
			close(data->exec->outfile);
		if (data->exec->infile != 0)
			close (data->exec->infile);
		tempo = data->tmp_files;
		while(tempo)
		{
			if (tempo->fd && tempo->fd > 0)
				close(tempo->fd);
			tempo = tempo->next;
		}
		execve(data->exec->cmd, tmp->cmd_array, data->exec->my_envp);
		error_execve_multi(data, tmp);
	}
}

void	exec_multi_pipe(t_data *data)
{
	int	i;
	// int status = 0;
	int status;
	
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
	while(++(data->exec->index) < data->exec->nb_node)
	{
		if(!data->exec->multi_tube)
			init_tubes(data);
		children_process(data);
	}
	close_tubes(data);
	//dprintf(2, "IN %d| OUT %d\n", data->exec->infile, data->exec->outfile);
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
	{
		//dprintf(2, "PARENTS\n");
		close (data->exec->infile);
	}
	int j = 0;
	while (j < data->exec->nb_node)
		waitpid(data->exec->pid[j++], &status, 0);
	data->exit_status = WEXITSTATUS(status);
	free(data->exec->multi_tube);
	free(data->exec->pid);
}
