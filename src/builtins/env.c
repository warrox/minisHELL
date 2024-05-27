/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/27 15:32:19 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_env(t_data *data)
{
	//printf("%s\n", data->tokenizer->cmd_and_arg[0]);
	if (ft_strncmp(data->tokenizer->cmd_and_arg[0], "env", 3) == 0
		&& data->lst != NULL)
		print_lst(data->lst);
	else
		return ;
}
