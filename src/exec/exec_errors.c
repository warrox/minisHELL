/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:36:46 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:10 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exit_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(127); // voir exit code plus tard
}

void	error_excve(t_data *data)
{
	if (data->tokenizer->cmd_array != NULL)
		write(2, data->tokenizer->cmd_array[0], ft_strlen(data->tokenizer->cmd_array[0]));
	write(2, ": command not found\n", 21);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(126);
}

void	cmd_not_found(t_data *data)
{
	if (data->tokenizer->cmd_array != NULL)
		write(2, data->tokenizer->cmd_array[0], ft_strlen(data->tokenizer->cmd_array[0]));
	write(2, ": command not found\n", 21);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free_exec(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(127);
}

void	file_not_found(t_data *data)
{
	if (data->tokenizer->file_array[0] != NULL)
		write(2, data->tokenizer->file_array[0], ft_strlen(data->tokenizer->file_array[0]));
	write(2, ": No such file or directory\n", 29);
	// if (data->exec->outfile != -1)
	// 	close(data->exec->outfile);
	free(data->exec->cmd);
	free_exec(data);
	ft_clear_tokenizer(data);
	free_prompt(data);
	free(data->signal);
	ft_lst_arg_clear(&data->lst);
	exit(1);
}

