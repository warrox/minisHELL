/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:49:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/08 18:49:20 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	free_prompt(t_data *data)
{
	if(data->prompt)
	{
		free(data->prompt->usr_name);
		free(data->prompt->usr_pwd);
		free(data->prompt->usr_prompt);
		free(data->prompt->usr_build_one);
		free(data->prompt->usr_build_two);
		free(data->prompt);
	}
}

