/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/04 15:44:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	pwd_cmd(t_data *data)
{
	char	*value;

	value = NULL_INIT;
	if (ft_strncmp(data->tokenizer->cmd_array[0], "pwd", 4) == 0)
	{
		value = getcwd(NULL, 0);
		ft_printf("%s\n", value);
		free(value);
	}
}
