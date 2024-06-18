/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/18 18:08:37 by cyferrei         ###   ########.fr       */
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
		ft_printf("%s\n", value);
		free(value);
		return (1);
	}
	return (0);
}
