/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:06:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/09 14:13:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_env(t_data *data, char *input)
{
	if(ft_strncmp(input, "env", 3) == 0)
		print_lst(data->lst);
}