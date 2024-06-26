/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 11:43:24 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	pwd_cmd(t_data *data)
{
	char	*value;

	value = NULL_INIT;
	if (data->tokenizer->cmd_array[0] == NULL)
		return (0);
	if (ft_strncmp(data->tokenizer->cmd_array[0], "pwd", 4) == 0)
	{
		value = getcwd(NULL, 0);
		write(data->exec->outfile, value, ft_strlen(value));
		write(data->exec->outfile, "\n", 1);
		free(value);
		return (1);
	}
	return (0);
}
