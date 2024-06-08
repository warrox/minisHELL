/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:56:28 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/08 16:14:33 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

char	*get_path(t_data *data)
{
	t_list_arg *tmp;
	
	tmp = data->lst;
	while(tmp && ft_strncmp("PATH", tmp->key_and_val[0], 5))
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (NULL);
	}
	// printf("ICI : %s", tmp->key_and_val[0]);
	return (tmp->key_and_val[1]);
}