/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:50:22 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/25 16:43:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	create_new_var(t_data *data, char *key, char *value)
{
	char	*build_var;
	char	*final_var;
	int		i;

	i = ZERO_INIT;
	build_var = NULL_INIT;
	final_var = NULL_INIT;
	build_var = ft_strjoin(key, "=");
	final_var = ft_strjoin(build_var, value);
	ft_lstadd_arg_back(&data->lst, ft_lst_arg_new(data->lst, &final_var[i]));
	free(build_var);
	free(final_var);
}

int	is_env_var(t_data *data, char **split_key)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], split_key[0]) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_export_cmd(t_data *data)
{
	if (ft_strcmp(data->tokenizer->input_splited, "export") == 0
		&& data->lst != NULL)
	{
		print_lst_export(data->lst);
		return(1);	
	}
	return (0);
}

void	concat_env_var(t_data *data, char *key, char *new)
{
	t_list_arg	*tmp;
	char		*new_value;

	new_value = NULL_INIT;
	tmp = data->lst;
	while (tmp && ft_strcmp(tmp->key_and_val[0], key) != 0)
		tmp = tmp->next;
	new_value = ft_strjoin(tmp->key_and_val[1], new);
	free(tmp->key_and_val[1]);
	tmp->key_and_val[1] = new_value;
}

void	case_plus_egal(t_data *data)
{
	char	**split_key;
	char	**split_value;

	split_key = NULL_INIT;
	split_value = NULL_INIT;
	split_key = ft_split(data->tokenizer->cmd_and_arg[1], '+');
	if (!split_key)
		return ;
	split_value = ft_split(data->tokenizer->cmd_and_arg[1], '=');
	if (!split_value)
		return ;
	dprintf(2, "%s\n", data->tokenizer->cmd_and_arg[1]);
	dprintf(2, "%s\n", split_key[0]);
	dprintf(2, "%s\n", split_value[1]);
	if (is_env_var(data, split_key))
		concat_env_var(data, split_key[0], split_value[1]);
	else
		create_new_var(data, split_key[0], split_value[1]);
	free_split(split_key);
	free_split(split_value);
}
