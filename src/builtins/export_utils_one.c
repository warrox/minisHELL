/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:52:40 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 19:24:45 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exec_export_case(t_data *data, t_list_arg *tmp, char **split,
		char **arg)
{
	char	*tmp_built;

	tmp_built = NULL_INIT;
	while (tmp)
	{
		tmp_built = ft_strjoin(tmp->key_and_val[0], "+");
		if (ft_strcmp(arg[0], tmp->key_and_val[0]) == 0
			&& !check_egals(split[data->i]))
			return (free(tmp_built));
		if (ft_strcmp(arg[0], tmp_built) == 0
			&& check_plus_egal(split[data->i]))
		{
			case_plus_egal(data, tmp, &arg[0], tmp_built);
			return ;
		}
		if (ft_strcmp(arg[0], tmp->key_and_val[0]) == 0
			&& check_egals(split[data->i]))
		{
			(set_value(data, tmp->key_and_val[0], arg[1]), free(tmp_built));
			return ;
		}
		tmp = tmp->next;
		free(tmp_built);
	}
}

t_list_arg	*parse_key_and_val(t_list_arg *tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(strlen(tmp->key_and_val[0]) + 1);
	if (new == NULL)
		return (NULL);
	while (tmp->key_and_val[0][i] != '+' && tmp->key_and_val[0][i] != '\0')
	{
		new[j] = tmp->key_and_val[0][i];
		i++;
		j++;
	}
	new[j] = '\0';
	strcpy(tmp->key_and_val[0], new);
	free(new);
	return (tmp);
}

void	check_if_null(t_data *data, t_list_arg *tmp, char **split)
{
	if (tmp == NULL)
		ft_lstadd_arg_back(&data->lst, ft_lst_arg_new(data->lst,
				split[data->i]));
}
