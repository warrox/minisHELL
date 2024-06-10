/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:56:28 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/10 16:58:56 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

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
	
	tmp = NULL_INIT;
	i = 0;
	if(!data->tokenizer->cmd_array)
		return (NULL);
	if(data->tokenizer->cmd_array[0] == NULL)
		return (NULL);
	if (access(data->tokenizer->cmd_array[0], F_OK | X_OK) == 0)
		return (data->tokenizer->cmd_array[0]);
	while(data->exec->path_cmd[i])
	{
		tmp = ft_strjoin(data->exec->path_cmd[i], "/");
		data->exec->final_cmd = ft_strjoin(tmp, data->tokenizer->cmd_array[0]);
		free(tmp);
		if (access(data->exec->final_cmd, F_OK | X_OK) == 0)
			return (data->exec->final_cmd);
		free(data->exec->final_cmd);
		i++;
	}
	return(NULL);
}

void	free_exec(t_data *data)
{
	free_split(data->exec->path_cmd);
	free(data->exec);
}

char	*get_path(t_data *data)
{
	t_list_arg *tmp;
	
	tmp = data->lst;
	while(tmp && ft_strncmp("PATH", tmp->key_and_val[0], 5))
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (NULL);
	}
	return (tmp->key_and_val[1]);
}