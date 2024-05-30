/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:28:47 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/30 14:26:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	is_a_builtin(t_data *data)
{
	ft_printf("CMD ARG 0 : %s\n",data->tokenizer->final_cmd);
	cmd_env(data);
	pwd_cmd(data);
	cmd_export(data);
	cmd_unset(data);
	cmd_echo(data);
}
