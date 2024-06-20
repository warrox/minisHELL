/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/20 17:23:05 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

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
	
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (is_redir(tmp))
	{
		while(tmp->file_array[i] != 0)
		{
			if (data->exec->infile != 0 && data->exec->infile > 0)
				close(data->exec->infile);
			if (data->exec->outfile != 1 && data->exec->outfile > 0)
				close(data->exec->outfile);
			init_files(data, tmp, i++);
		}
	}
	data->exec->cmd = build_cmd(data, tmp);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(tmp) != 0)))
	{
		hd_or_rdr_no_cmd(data);
	}
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
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	execve(data->exec->cmd, tmp->cmd_array, NULL);
	error_excve(data);
}

void	first_child_process(t_data *data)
{
	int i;
	i = 0;

	if (is_redir(data->tokenizer))
	{
		while(data->tokenizer->file_array[i])
		{
			if (data->exec->infile != 0 && data->exec->infile > 0)
				close(data->exec->infile);
			if (data->exec->outfile != 1 && data->exec->outfile > 0)
				close(data->exec->outfile);
			init_files(data, data->tokenizer, i++);
		}
	}
	data->exec->cmd = build_cmd(data, data->tokenizer);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(data->tokenizer) != 0)))
	{
		hd_or_rdr_no_cmd(data);
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
	close(data->exec->tube[0]);
	close(data->exec->tube[1]);
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	error_excve(data);
}

void	exec_one_pipe(t_data *data)
{
	int status = 0;
	
	if (pipe(data->exec->tube) < 0)
		exit_error("pipe failed!\n");
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
	if(is_redir(data->tokenizer))
	{
		while(data->tokenizer->file_array[i] != 0)
			init_files(data, data->tokenizer, i++);
	}
	data->exec->cmd = build_cmd(data, data->tokenizer);
	if (!data->exec->cmd && (data->exec->here_doc || (is_redir(data->tokenizer) != 0)))
	{
		hd_or_rdr_no_cmd(data);
	}
	if (data->exec->here_doc && data->exec->cmd)
	{
		execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
		error_excve(data);
		exit(1);
	}
	if (!data->exec->cmd)
		cmd_not_found(data);
	else if (data->exec->here_doc)
	{
		ft_clear_tokenizer(data);
		free_prompt(data);
		free_exec(data);
		free(data->signal);
		ft_lst_arg_clear(&data->lst);
		exit(1);
	}
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	error_excve(data);
}
