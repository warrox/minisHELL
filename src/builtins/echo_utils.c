/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:02:53 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 12:44:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	is_valid_flag_n(char *cmd)
{
	int	j;

	j = ZERO_INIT;
	if (cmd[j] == '-')
	{
		j++;
		while (cmd[j] == 'n' && cmd[j] != '\0')
			j++;
		if (cmd[j] == ' ' || cmd[j] == '\0')
			return (1);
	}
	return (0);
}
