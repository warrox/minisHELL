/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:28:47 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 16:29:08 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

void	exec_builtin(t_data *data, t_list_arg *tok, int builtin)
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
	{
		dprintf(2, "ON EST ICI\n");
		cmd_echo(data, tok);
	}
	else if (builtin == CD)
		ft_current_directory(data->tokenizer->cmd_array[1], data);
	else if (builtin == EXIT)
		ft_exit(data, data->tokenizer->final_cmd);
}

int	is_a_builtin(t_list_arg *tok)
{
	if (tok->cmd_array[0] == NULL)
		return (-2);
	if (ft_strncmp(tok->cmd_array[0], "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(tok->cmd_array[0], "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(tok->cmd_array[0], "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(tok->cmd_array[0], "unset", 5) == 0)
		return (UNSET);
	else if (ft_strncmp(tok->cmd_array[0], "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(tok->cmd_array[0], "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(tok->cmd_array[0], "exit", 5) == 0)
		return (EXIT);
	else
		return (-1);
}
