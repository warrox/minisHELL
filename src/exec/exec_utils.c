/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:56:28 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/20 17:28:30 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	is_redir(t_list_arg *tok)
{
	t_list_arg *tmp;

	tmp = tok;
	if (!tmp)
		return (0);
	if (tmp->array_sign[0])
		return (1);
	return (0);
}

char	*build_cmd(t_data *data, t_list_arg *tok)
{
	int	i;
	char *tmp_c;
	t_list_arg	*tmp;
	
	tmp = tok;
	i = 0;
	// dprintf(2, "LA %s\n", tmp->cmd_array[0]);
	if (!data->exec->path || data->exec->path == NULL)
		return (data->tokenizer->cmd_array[0]);
	if(!tmp->cmd_array)
		return (NULL); 
	if(tmp->cmd_array[0] == NULL)
		return (NULL);
	if (access(data->tokenizer->cmd_array[0], F_OK | X_OK) == 0)
		return (data->tokenizer->cmd_array[0]);
	while(data->exec->path_cmd[i])
	{
		tmp_c = ft_strjoin(data->exec->path_cmd[i], "/");
		data->exec->final_cmd = ft_strjoin(tmp_c, tmp->cmd_array[0]);
		free(tmp_c);
		if (access(data->exec->final_cmd, F_OK | X_OK) == 0)
			return (data->exec->final_cmd);
		free(data->exec->final_cmd);
		i++;
	}
	return(NULL);
}

void	free_exec(t_data *data)
{
	if (data->exec->path_cmd)
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