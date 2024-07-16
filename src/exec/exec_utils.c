/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:56:28 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 17:13:01 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

// void	hd_or_rdr_no_cmd_multi(t_data *data)
// {
// 	ft_clear_tokenizer(data);
// 	free_prompt(data);
// 	free(data->signal);
// 	close_tubes(data);
// 	free(data->exec->multi_tube);
// 	free(data->exec->pid);
// 	if (data->exec->outfile != 1)
// 		close(data->exec->outfile);
// 	if (data->exec->infile != 0)
// 		close(data->exec->infile);
// 	free_exec(data);
// 	free_tmp_struct(data);
// 	ft_lst_arg_clear(&data->lst);
// 	exit(126);
// }

int	is_redir(t_list_arg *tok)
{
	t_list_arg	*tmp;

	tmp = tok;
	if (!tmp)
		return (0);
	if (tmp->file_array[0])
		return (1);
	return (0);
}

char	*build_cmd(t_data *data, t_list_arg *tok)
{
	int			i;
	char		*tmp_c;
	t_list_arg	*tmp;

	tmp = tok;
	if (!tmp->cmd_array)
		return (NULL);
	if (tmp->cmd_array[0] == NULL)
		return (NULL);
	if (!data->exec->path || !tmp->cmd_array || !tmp->cmd_array[0])
		return (NULL);
	if (access(tmp->cmd_array[0], F_OK | X_OK) == 0)
		return (tmp->cmd_array[0]);
	i = 0;
	while (data->exec->path_cmd[i])
	{
		tmp_c = ft_strjoin(data->exec->path_cmd[i], "/");
		data->exec->final_cmd = ft_strjoin(tmp_c, tmp->cmd_array[0]);
		free(tmp_c);
		if (access(data->exec->final_cmd, F_OK | X_OK) == 0)
			return (data->exec->final_cmd);
		free(data->exec->final_cmd);
		i++;
	}
	return (NULL);
}

void	free_exec(t_data *data)
{
	int	i;

	if (data->exec->path_cmd)
		free_split(data->exec->path_cmd);
	if (data->exec->my_envp)
	{
		i = 0;
		while (data->exec->my_envp[i] != NULL)
		{
			free(data->exec->my_envp[i]);
			i++;
		}
		free(data->exec->my_envp);
	}
	free(data->exec);
}

char	*get_path(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp && ft_strncmp("PATH", tmp->key_and_val[0], 5))
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (NULL);
	}
	return (tmp->key_and_val[1]);
}
