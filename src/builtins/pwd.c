/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	pwd_cmd(t_data *data, char *input)
{
	int i;
	t_list_arg *tmp;
	char *value;

	tmp = data->lst;
	i= ZERO_INIT;
	if(ft_strncmp(input, "pwd", 3) == 0)
	{
		value = getcwd(NULL, 0);
		// while(tmp && tmp->key_and_val && ft_strncmp(tmp->key_and_val[0], "PWD", 3) != 0)
		// 	tmp = tmp->next;	
		// if (!tmp)
		// 	return;
		// ft_printf("%s\n", tmp->key_and_val[1]);
		ft_printf("%s\n", value);
		free(value);
	}
}