/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/30 14:28:22 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_env(t_data *data)
{
	//printf("%s\n", data->tokenizer->cmd_and_arg[0]);
	if (ft_strncmp(data->tokenizer->final_cmd, "env", 3) == 0
		&& data->lst != NULL)
		print_lst(data->lst);
	else
		return ;
}
