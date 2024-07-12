/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:58:53 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/12 11:32:47 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

t_list_arg	*find_key_pwd(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key_and_val[0], "PWD") == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int	count_word(char const *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}
