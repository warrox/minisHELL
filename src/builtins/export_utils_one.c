/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:52:40 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/08 15:45:11 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	is_valid_name(t_data *data)
{
	char	*join_1;
	char	*final_join;
	char	**split_cmd;
	int	i;

	// print_exec_utils(data);
	i = ZERO_INIT;
	split_cmd = NULL;
	split_cmd = ft_split(data->tokenizer->cmd_array[1], '=');
	if (!split_cmd)
		return (-1);
	if (split_cmd[0] == NULL)
	{
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (0);
	} 
	if (split_cmd[0] && (split_cmd[0][i] == '_' || ft_isalpha(split_cmd[0][i])))
	{
		i++;
		while (ft_isalpha(split_cmd[0][i]) || ft_isalnum(split_cmd[0][i]) || split_cmd[0][i] == '_')
			i++;
		if (split_cmd[0][i] != '\0')
		{
			join_1 = ft_strjoin("bash: export: ", split_cmd[0]);
			final_join = ft_strjoin(join_1, ": not a valid identifier\n");
			ft_putstr_fd(final_join, STDERR_FILENO);
			free(join_1);
			free(final_join);
			free_split(split_cmd);
			return(0);
		}
		else
		{
			free_split(split_cmd);
			return (1);
		}
	}
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	free_split(split_cmd);
	return (0);
}

int	check_export_nothing(t_data *data)
{
	t_list_arg *tmp;
	char **split = NULL_INIT;

	tmp = data->lst;
	split = ft_split(data->tokenizer->final_cmd, ' ');
	if (!split)
		return (0);
	while (tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], split[1]))
		{
			free_split(split);
			return (1);
		}
		tmp = tmp->next;
	}
	free_split(split);
	return (0);
}

void case_egal(t_data *data)
{
    t_list_arg *tmp;
    char **split_arg;
    int i = 1;

    // print_exec_utils(data);
    while (data->tokenizer->cmd_array[i])
    {
        // dprintf(2, "HELLO\n");
        split_arg = NULL;
        split_arg = ft_split(data->tokenizer->cmd_array[i], '=');
        if (!split_arg)
            return;

        tmp = data->lst;
        int found = 0;
        while (tmp)
        {
            if (ft_strcmp(tmp->key_and_val[0], split_arg[0]) == 0)
            {
                set_value(data, split_arg);
                found = 1;
                break;
            }
            tmp = tmp->next;
        }
        if (!found)
        {
            create_new_var(data, split_arg[0], split_arg[1]);
        }
        
        //free_split(split_arg);
        i++;
    }
}


int	check_plus_egal(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while (data->tokenizer->final_cmd[i])
	{
		if (data->tokenizer->final_cmd[i] == '+')
		{
			if (data->tokenizer->final_cmd[i + 1] != '=')
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}
