/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:28:47 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:26 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

void	exec_builtin(t_data *data, int builtin)
{	
	if (builtin == ENV)
		cmd_env(data);
	else if (builtin == PWD)
		pwd_cmd(data);
	else if (builtin == EXPORT)
		cmd_export(data);
	else if (builtin == UNSET)
		cmd_unset(data);
	else if (builtin == ECHO)
		cmd_echo(data);
	else if (builtin == CD)
		ft_current_directory(data->tokenizer->cmd_array[1], data);
}

int	is_a_builtin(t_data *data)
{
	//dprintf(2, "ICI %s\n", data->tokenizer->cmd_array[0]);
	if(data->tokenizer->cmd_array[0] == NULL)
		return(0);
	if (ft_strncmp(data->tokenizer->cmd_array[0], "env", 4) == 0)
	{
		//dprintf(2, "EVLIBE\n");
		return (ENV);
	}
	else if (ft_strncmp(data->tokenizer->cmd_array[0], "pwd", 4) == 0)
		return (PWD);
	else if (ft_strstr(data->tokenizer->final_cmd, "export"))
		return (EXPORT);
	else if (ft_strncmp(data->tokenizer->final_cmd, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strstr(data->tokenizer->final_cmd, "echo"))
		return (ECHO);
	else if (ft_current_directory(data->tokenizer->cmd_array[1], data))
		return (CD);
	else
		return (-1);
}
