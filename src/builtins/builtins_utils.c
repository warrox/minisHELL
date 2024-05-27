/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:28:47 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/27 17:03:03 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	is_a_builtin(t_data *data)
{
	ft_printf("CMD ARG 0 : %s\n",data->tokenizer->cmd_and_arg[0]);
	ft_printf("CMD ARG 1 : %s\n",data->tokenizer->cmd_and_arg[1]);
	cmd_env(data);
	pwd_cmd(data);
	cmd_export(data);
	cmd_unset(data);
	cmd_echo(data);
}
