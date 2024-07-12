/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:34:32 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 11:40:52 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

t_list_arg	*find_key_user(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], "USER") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		ft_printf("USER is unset\n");
	return (tmp);
}

t_list_arg	*find_key_old_pwd(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int	cd_check_opt(char *path, t_data *data)
{
	t_list_arg	*tmp;
	t_list_arg	*save_current;

	data->i = 0;
	save_current = data->lst;
	tmp = NULL;
	if (path == NULL)
		return (-1);
	while (path[data->i] == ' ' || path[data->i] == '\t')
		data->i++;
	if (path[data->i] == '-')
	{
		while (path[data->i] == ' ' || path[data->i] == '\t')
			data->i++;
		if (path[data->i + 1] == '\0')
		{
			exec_cd_with_opt(data, tmp, save_current, data->tool_box.buffer);
			return (1);
		}
		else
			return (ft_printf("cd: string not in pwd: -\n", 1));
	}
	return (0);
}

int	check_cd(t_data *data, t_list_arg *tmp, char *path)
{
	if (ft_strstr(data->tokenizer->cmd_array[0], "cd")
		|| (ft_strstr(data->tokenizer->cmd_array[0], "cd")
			&& (data->tokenizer->cmd_array[0][2] == ' '
			&& data->tokenizer->cmd_array[0][3] == '\0')))
	{
		data->tool_box.j = iterate_in_str(data->tokenizer->final_cmd);
		if (data->tokenizer->final_cmd[data->tool_box.i + 2] == '\0'
			|| data->tokenizer->final_cmd[data->tool_box.j] == '\0')
			return (no_arg(data, tmp, data->tool_box.path_hu));
		if (cd_check_opt(path, data))
			return (1);
		if (chdir(path) == -1)
		{
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
			data->exit_status = 1;
			return (1);
		}
		getcwd(data->tool_box.buffer_old, 4096);
		if (chdir(path) == 0)
			return (exec_cd(data, tmp, data->tool_box.buffer,
					data->tool_box.buffer_old, 4096), 1);
	}
	return (0);
}

int	ft_current_directory(char *path, t_data *data)
{
	t_list_arg	*tmp;
	int			i;
	int			count;

	tmp = data->lst;
	i = 0;
	count = 0;
	init_tool_box(data);
	while (data->tokenizer->cmd_array[i])
		count += count_word(data->tokenizer->cmd_array[i++], ' ');
	if (count > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		data->exit_status = 1;
		return (1);
	}
	check_cd(data, tmp, path);
	return (0);
}
