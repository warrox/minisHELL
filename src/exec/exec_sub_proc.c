/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:49:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 12:26:47 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

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
	printf("FINAL_CMD --> %s\n", data->exec->cmd);
	if (!data->exec->cmd)
	{
		free_exec(data);
		exit(1);
	}
	execve(data->exec->cmd, data->tokenizer->cmd_array, NULL);
	exit(1);
}