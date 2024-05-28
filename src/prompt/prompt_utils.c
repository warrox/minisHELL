/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:35:25 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/28 15:31:06 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

t_data	*init_prompt(t_data *data)
{
	data->prompt = (t_prompt *)malloc(sizeof(t_prompt));
	if (!data->prompt)
		return (NULL);
	data->prompt->usr_build_one = NULL_INIT;
	data->prompt->usr_build_two = NULL_INIT;
	data->prompt->usr_name = NULL_INIT;
	data->prompt->usr_prompt = NULL_INIT;
	data->prompt->usr_pwd = NULL_INIT;
	data->tokenizer = NULL;
	data->signal = NULL;
	return (data);
}

static char	*get_pwd(t_data *data)
{
	t_list_arg	*current;

	current = data->lst;
	while (current && ft_strncmp("PWD", current->key_and_val[0], 3))
		current = current->next;
	if (!current)
		return (NULL);
	if (ft_strncmp("PWD", current->key_and_val[0], 3) == 0)
		return (ft_strdup(current->key_and_val[1]));
	else
		return (NULL);
}

static char	*get_usr(t_data *data)
{
	t_list_arg	*current;

	current = data->lst;
	while (current && ft_strncmp("USER", current->key_and_val[0], 4))
		current = current->next;
	if (!current)
		return (NULL);
	if (ft_strncmp("USER", current->key_and_val[0], 4) == 0)
		return (ft_strdup(current->key_and_val[1]));
	else
		return (NULL);
}

t_data	*build_user_prompt(t_data *data)
{
	data->prompt->usr_name = get_usr(data);
	data->prompt->usr_pwd = get_pwd(data);
	data->prompt->usr_build_one = ft_strjoin(data->prompt->usr_name, ":~");
	data->prompt->usr_build_two = ft_strjoin(data->prompt->usr_build_one,
			data->prompt->usr_pwd);
	data->prompt->usr_prompt = ft_strjoin(data->prompt->usr_build_two, "$ ");
	return (data);
}
