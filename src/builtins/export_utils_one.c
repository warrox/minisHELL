/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:52:40 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/04 23:42:38 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

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
