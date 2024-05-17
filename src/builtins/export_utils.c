/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:50:22 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 20:08:36 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	check_export_cmd(char *input, t_data *data)
{
	if (ft_strcmp(input, "") == 0)
		return ;
	else if (ft_strcmp(input, "export") == 0 && data->lst != NULL)
		print_lst_export(data->lst);
}

void	concat_env_var(t_data *data, char *value, char *new)
{
	t_list_arg	*tmp;
	char		*new_val;
	char		*build_new_var;
	int			i;

	i = ZERO_INIT;
	tmp = data->lst;
	while (tmp && ft_strcmp(tmp->key_and_val[0], value) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		build_new_var = ft_strjoin(value, new);
		ft_lstadd_arg_back(&data->lst, ft_lst_arg_new(data->lst,
				&build_new_var[i]));
		free(build_new_var);
		return ;
	}
	new_val = ft_strjoin(tmp->key_and_val[1], new);
	free(tmp->key_and_val[1]);
	tmp->key_and_val[1] = new_val;
}

int	check_plus_egal(char *input)
{
	int	i;

	i = ZERO_INIT;
	while (input[i])
	{
		if (input[i] == '+' && input[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	case_plus_egal(t_data *data, t_list_arg *tmp, char **arg,
		char *tmp_built)
{
	free(tmp->key_and_val[0]);
	tmp->key_and_val[0] = ft_strjoin(arg[0], "=");
	parse_key_and_val(tmp);
	concat_env_var(data, tmp->key_and_val[0], arg[1]);
	free(tmp_built);
}

void	export_case(t_data *data, t_list_arg *tmp, char **arg, char **split)
{
	exec_export_case(data, tmp, split, arg);
	check_if_null(data, tmp, split);
}
