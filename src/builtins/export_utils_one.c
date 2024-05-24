/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:52:40 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 18:56:48 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	case_egal(t_data *data)
{
	t_list_arg *tmp;
	char	**split_arg;
	
	split_arg = NULL_INIT;
	split_arg = ft_split(data->tokenizer->cmd_and_arg[1], '=');
	if (!split_arg)
		return;
	tmp = data->lst;
	while(tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], split_arg[0]) == 0)
			return(set_value(data, split_arg));
		tmp = tmp->next;
	}
	if (tmp == NULL)
		create_new_var(data, split_arg[0], split_arg[1]);
	free_split(split_arg);
}

int	check_plus_egal(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while (data->tokenizer->input_splited[i])
	{
		if (data->tokenizer->input_splited[i] == '+' && data->tokenizer->input_splited[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}