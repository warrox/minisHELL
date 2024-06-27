/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:56:28 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 14:32:19 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	hd_or_rdr_no_cmd_multi(t_data *data)
{
	ft_clear_tokenizer(data);
	free_prompt(data);
	free(data->signal);
	close_tubes(data);
	free(data->exec->multi_tube);
	free(data->exec->pid);
	if (data->exec->outfile != 1)
		close(data->exec->outfile);
	if (data->exec->infile != 0)
		close(data->exec->infile);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	exit(126);
}

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

char *build_cmd(t_data *data, t_list_arg *tok)
{
	int i;
	char *tmp_c;
	t_list_arg *tmp = tok;
	
	// dprintf(2, "ICI%s\n", tmp->cmd_array[0]);
	if (!data->exec->path || !tmp->cmd_array || !tmp->cmd_array[0])
		return (NULL);
	if (access(tmp->cmd_array[0], F_OK | X_OK) == 0)
		return (tmp->cmd_array[0]);
	for (i = 0; data->exec->path_cmd[i]; i++)
	{
		tmp_c = ft_strjoin(data->exec->path_cmd[i], "/");
		data->exec->final_cmd = ft_strjoin(tmp_c, tmp->cmd_array[0]);
		free(tmp_c);
		if (access(data->exec->final_cmd, F_OK | X_OK) == 0)
			return (data->exec->final_cmd);
		free(data->exec->final_cmd);
	}
	dprintf(2, "AHBON?\n");
	return (NULL);
}

void free_exec(t_data *data)
{
    if (data->exec->path_cmd)
        free_split(data->exec->path_cmd);
    if (data->exec->my_envp) {
        // Free each string in the array
        int i = 0;
        while (data->exec->my_envp[i] != NULL) 
		{
            free(data->exec->my_envp[i]);
            i++;
        }
        // Free the array itself
        free(data->exec->my_envp);
    }
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