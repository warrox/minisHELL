/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 11:32:49 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	set_value(t_data *data, char **split_arg)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp && ft_strcmp(tmp->key_and_val[0], split_arg[0]) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	else
	{
		free(tmp->key_and_val[1]);
		tmp->key_and_val[1] = ft_strdup(split_arg[1]);
		free_split(split_arg);
	}
}

int	check_egals(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while (data->tokenizer->final_cmd[i])
	{
		if (data->tokenizer->final_cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = ZERO_INIT;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_lst_export(t_list_arg *lst)
{
	while (lst)
	{
		ft_printf("declare -x ");
		ft_printf("%s=", lst->key_and_val[0]);
		ft_printf("%s\n", lst->key_and_val[1]);
		lst = lst->next;
	}
}

int	cmd_export(t_data *data)
{
	if (is_valid_name(data) != 1)
	{
		return (data->exit_status = 1);
	}
	if (check_export_cmd(data))
	{
		return (1);
	}
	if (check_plus_egal(data))
	{
		case_plus_egal(data);
		return (1);
	}
	if (check_egals(data))
	{
		case_egal(data);
		return (1);
	}
	if (check_export_nothing(data))
		return (1);
	return (0);
}
