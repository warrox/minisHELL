/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 15:23:01 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void init_files_builtin(t_data *data, t_list_arg *tok, int i)
{
    if (tok->array_sign[i] == STDOUTS)
    {
        data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
        if (data->exec->outfile < 0)
            file_not_found(data, tok);
		printf("Opened outfile for builtin: %s\n", tok->file_array[i]);
    }
    else if (tok->array_sign[i] == STDINS)
    {
        data->exec->infile = open(tok->file_array[i], O_RDONLY);
        if (data->exec->infile < 0)
            file_not_found(data, tok);
		printf("Opened infile for builtin: %s\n", tok->file_array[i]);
    }
	else if (tok->array_sign[i] == APPEND)
	{
		data->exec->outfile = open(tok->file_array[i], O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data, tok);
		printf("Opened outfile for builtin: %s\n", tok->file_array[i]);
	}
}

void init_files(t_data *data, t_list_arg *tok, int i)
{
    if (tok->array_sign[i] == STDOUTS)
    {
        data->exec->outfile = open(tok->file_array[i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
        if (data->exec->outfile < 0)
            file_not_found(data, tok);
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
    }
    else if (tok->array_sign[i] == STDINS)
    {
        data->exec->infile = open(tok->file_array[i], O_RDONLY);
        if (data->exec->infile < 0)
            file_not_found(data, tok);
		dup2(data->exec->infile, STDIN_FILENO);
		close(data->exec->infile);
    }
	else if (tok->array_sign[i] == APPEND)
	{
		data->exec->outfile = open(tok->file_array[i], O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data, tok);
		dup2(data->exec->outfile, STDOUT_FILENO);
		close(data->exec->outfile);
	}
}

void	second_child_process(t_data *data)
{
	int i = ZERO_INIT;
	t_list_arg *tmp = data->tokenizer;
	
	printf("Redirected second\n");
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (is_a_builtin(tmp) != -1 && is_a_builtin(tmp) != -2)
	{
		init_files_builtin(data, tmp, i);
		// dprintf(2, "%d\n", data->exec->infile);
		if (data->exec->infile != 0)
		{
			dup2(data->exec->infile, STDIN_FILENO);
			close (data->exec->infile);
		}
		else
			dup2(data->exec->tube[0], STDIN_FILENO);
		if (data->exec->outfile != 1)
		{
			dup2(data->exec->outfile, STDOUT_FILENO);
			close (data->exec->outfile);
		}
		exec_builtin(data, is_a_builtin(tmp));
		if (data->exec->outfile != 1)
			close(data->exec->outfile);
		if (data->exec->infile != 0)
			close (data->exec->infile);
		close(data->exec->tube[0]);
		close(data->exec->tube[1]);
		free_resources_single(data);
		exit(1) ;
	}
	data->exec->cmd = build_cmd(data, tmp);
	if (data->exec->cmd == NULL)
		error_cmd_op(data, tmp);
	if (is_redir(tmp))
	{
		while(tmp->file_array[i] != 0)
			init_files(data, tmp, i++);
	}
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close (data->exec->infile);
		printf("Redirected stdin for builtin\n");
	}
	else
	{
		printf("Redirected stdin for builtin\n");
		dup2(data->exec->tube[0], STDIN_FILENO);
	}
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close (data->exec->outfile);
		printf("Redirected stdout for builtin\n");
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tmp) != 0)))
	{
		hd_or_rdr_no_cmd(data);
	}
	if (access(data->exec->cmd, F_OK) != 0)
		error_dir_file_not_found(data, tmp);
	if (access(data->exec->cmd, X_OK) != 0)
		error_permission_denied_op(data, tmp);
	if (check_dir(data->exec->cmd) == -1)
		error_is_a_dir_op(data, tmp);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	execve(data->exec->cmd, tmp->cmd_array, data->exec->my_envp);
	error_excve(data);
}

void	first_child_process(t_data *data)
{
	int i;
	i = 0;
	
	//printf("Redirected fisrt\n");
	if (is_a_builtin(data->tokenizer) >= 10 && is_a_builtin(data->tokenizer) <= 16)
	{
		init_files_builtin(data, data->tokenizer, i);
		if (data->exec->infile != 0)
		{
			dup2(data->exec->infile, STDIN_FILENO);
			close (data->exec->infile);
			//printf("Redirected stdin for builtin\n");
		}
		if (data->exec->outfile != 1)
		{
			dup2(data->exec->outfile, STDOUT_FILENO);
			close (data->exec->outfile);
			//printf("Redirected stdout for builtin\n");
		}
		else
		{
			dup2(data->exec->tube[1], STDOUT_FILENO);
			//printf("Redirected stdout for builtin\n");
		}
		exec_builtin(data, is_a_builtin(data->tokenizer));
		if (data->exec->outfile != 1)
			close(data->exec->outfile);
		if (data->exec->infile != 0)
			close (data->exec->infile);
		close(data->exec->tube[0]);
		close(data->exec->tube[1]);
		free_resources_single(data);
		exit(1) ;
	}
	data->exec->cmd = build_cmd(data, data->tokenizer);
	if (data->exec->cmd == NULL)
		error_cmd_op(data, data->tokenizer);
	if (is_redir(data->tokenizer))
	{
		while(data->tokenizer->file_array[i])
			init_files(data, data->tokenizer, i++);
	}
	if (data->exec->infile != 0)
	{
		dup2(data->exec->infile, STDIN_FILENO);
		close (data->exec->infile);
	}
	if (data->exec->outfile != 1)
	{
		dup2(data->exec->outfile, STDOUT_FILENO);
		close (data->exec->outfile);
	}
	else
		dup2(data->exec->tube[1], STDOUT_FILENO);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(data->tokenizer) != 0)))
	{
		hd_or_rdr_no_cmd(data);
	}
	if (access(data->exec->cmd, F_OK) != 0)
			error_dir_file_not_found(data, data->tokenizer);
	if (access(data->exec->cmd, X_OK) != 0)
			error_permission_denied_op(data, data->tokenizer);
	if (check_dir(data->exec->cmd) == -1)
			error_is_a_dir_op(data, data->tokenizer);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	execve(data->exec->cmd, data->tokenizer->cmd_array, data->exec->my_envp);
	error_excve(data);
}

void	exec_one_pipe(t_data *data)
{
	int status = 0;
	
	if (pipe(data->exec->tube) < 0)
		exit_error("pipe failed!\n");
	init_tmp_struct(data);
	check_here_doc(data);
	data->exec->pid_1 = fork();
	if (data->exec->pid_1 == -1)
		free_exec(data);
	if (data->exec->pid_1 == 0)
		first_child_process(data);
	data->exec->pid_2 = fork();
	if (data->exec->pid_2 == -1)
		free_exec(data);
	if (data->exec->pid_2 == 0)
		second_child_process(data);
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	waitpid(data->exec->pid_1, &status, 0);
	waitpid(data->exec->pid_2, &status, 0);
}

void	 exec_sub_proc(t_data *data)
{
	int	i;
	
	i = ZERO_INIT;
	if (is_a_builtin(data->tokenizer) != -1 && is_a_builtin(data->tokenizer) != -2) 
	{
		init_files_builtin(data, data->tokenizer, i);
		exec_builtin(data, is_a_builtin(data->tokenizer));
		if (data->exec->outfile != 1)
			close(data->exec->outfile);
		if (data->exec->infile != 0)
			close (data->exec->infile);
		return ;
	}
	data->exec->cmd = build_cmd(data, data->tokenizer);
	if (data->exec->cmd == NULL)
		error_cmd_single(data, data->tokenizer);
	if(is_redir(data->tokenizer))
	{
		while(data->tokenizer->file_array[i] != 0)
			init_files(data, data->tokenizer, i++);
	}
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(data->tokenizer) != 0)))
	{
		hd_or_rdr_no_cmd(data);
	}
	if (data->exec->here_doc && data->exec->cmd)
	{
		execve(data->exec->cmd, data->tokenizer->cmd_array, data->exec->my_envp);
		error_excve(data);
		exit(1);
	}
	if (access(data->exec->cmd, F_OK) != 0)
			error_dir_file_not_found(data, data->tokenizer);
	if (access(data->exec->cmd, X_OK) != 0)
			error_permission_denied_sgl(data, data->tokenizer);
	if (check_dir(data->exec->cmd) == -1)
			error_is_a_dir_sgl(data, data->tokenizer);
	if (data->exec->here_doc)
	{
		ft_clear_tokenizer(data);
		free_prompt(data);
		free_exec(data);
		free(data->signal);
		ft_lst_arg_clear(&data->lst);
		exit(1);
	}
	execve(data->exec->cmd, data->tokenizer->cmd_array, data->exec->my_envp);	
	error_excve(data);
}
