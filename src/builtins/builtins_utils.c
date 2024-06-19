/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:28:47 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/19 19:02:08 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

int	is_a_builtin(t_data *data)
{
	if(data->tokenizer->cmd_array[0] == NULL)
		return(0);
	if(cmd_env(data))
		return (1);
	else if (pwd_cmd(data))
		return (1);
	else if (cmd_export(data))
		return (1);
	else if (cmd_unset(data))
		return (1);
	else if (cmd_echo(data))
		return (1);
	else if (ft_current_directory(data->tokenizer->cmd_array[1], data))
		return (1);
	else
		return (0);
}
