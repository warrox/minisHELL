/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/09 15:13:30 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	pwd_cmd(t_data *data, char *input)
{
	int i;
	t_list_arg *tmp;

	tmp = data->lst;
	i= ZERO_INIT;
	if(ft_strncmp(input, "pwd", 3) == 0)
	{
		while(tmp->key_and_val && ft_strncmp(tmp->key_and_val[0], "PWD", 3) != 0)
			tmp = tmp->next;
		ft_printf("%s\n", tmp->key_and_val[1]);
	}
}