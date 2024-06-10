/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 16:23:52 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	file_not_found(t_data *data)
{
	if (data->tokenizer->file_array[0] != NULL)
		write(2, data->tokenizer->file_array[0], ft_strlen(data->tokenizer->file_array[0]));
	write(2, ": No such file or directory\n", 29);
	// if (data->exec->outfile != -1)
	// 	close(data->exec->outfile);
	free_exec(data);
	exit(1);
}

void	init_files(t_data *data)
{
	if (data->tokenizer->array_sign[0] == STDOUTS)
	{
		data->exec->outfile = open(data->tokenizer->file_array[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (data->exec->outfile < 0)
			file_not_found(data);
	}
	else if (data->tokenizer->array_sign[0] == STDINS)
	{
		data->exec->infile = open(data->tokenizer->file_array[0], O_RDONLY);
		if (data->exec->infile < 0)
			file_not_found(data);
	}
}

int	is_redir(t_data *data)
{
	t_list_arg *tmp;

	tmp = data->tokenizer;
	if (tmp->array_sign[0])
		return (1);
	return (0);
}

char	*build_cmd(t_data *data)
{
	int	i;
	char	*tmp;
	char	*final_cmd;
	
	tmp = NULL_INIT;
	final_cmd = NULL_INIT;
	i = 0;
	if(data->tokenizer->cmd_array[0] == NULL)
		return (NULL);
	if (access(data->tokenizer->cmd_array[0], F_OK | X_OK) == 0)
		return (data->tokenizer->cmd_array[0]);
	while(data->exec->path_cmd[i])
	{
		tmp = ft_strjoin(data->exec->path_cmd[i], "/");
		final_cmd = ft_strjoin(tmp, data->tokenizer->cmd_array[0]);
		free(tmp);
		if (access(final_cmd, F_OK | X_OK) == 0)
			return (final_cmd);
		free(final_cmd);
		i++;
	}
	return(NULL);
}

void	exec_sub_proc(t_data *data)
{
	data->exec->cmd = build_cmd(data);
	if (!data->exec->cmd)
	{
		ft_clear_tokenizer(data);
		free_prompt(data);
		free_exec(data);
		free(data->signal);
		ft_lst_arg_clear(&data->lst);
		exit(1);
	}
	if(is_redir(data))
	{
		init_files(data);
		if (data->exec->infile && data->exec->infile != 1)
		{
			dup2(data->exec->infile, STDIN_FILENO);
			close(data->exec->infile);
		}
		if (data->exec->outfile && data->exec->outfile != -1)
		{
			dup2(data->exec->outfile, STDOUT_FILENO);
			close(data->exec->outfile);
		}
	}
	//printf("FINAL_CMD --> %s\n", data->exec->cmd);
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(1);
}