/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 16:01:00 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	set_value(t_data *data, char *value, char *new)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp && ft_strcmp(tmp->key_and_val[0], value) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	else
	{
		free(tmp->key_and_val[1]);
		tmp->key_and_val[1] = ft_strdup(new);
	}
}

int	check_egals(char *input)
{
	int	i;

	i = ZERO_INIT;
	while (input[i])
	{
		if (input[i] == '=')
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

void	cmd_export(t_data *data, char *input)
{
	char		**split;
	char		**arg;
	t_list_arg	*tmp;

	split = NULL_INIT;
	arg = NULL_INIT;
	tmp = data->lst;
	data->i = 0;
	check_export_cmd(input, data);
	if (ft_strstr(input, "export") == 1)
	{
		split = ft_split(input, ' ');
		if (!split)
			return ;
		while (split[data->i++])
		{
			arg = ft_split(split[data->i], '=');
			if (!arg)
				return (free_split(split));
			tmp = data->lst;
			(export_case(data, tmp, arg, split), free_split(arg));
		}
		free_split(split);
	}
}
