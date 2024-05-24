/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:54:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 16:16:57 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	pwd_cmd(t_data *data)
{
	char	*value;

	value = NULL_INIT;
	if (ft_strncmp(data->tokenizer->cmd_and_arg[0], "pwd", 3) == 0)
	{
		value = getcwd(NULL, 0);
		ft_printf("%s\n", value);
		free(value);
	}
}
