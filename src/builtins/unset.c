/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:46:41 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 16:04:24 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_unset(t_data *data, char *input)
{
	char **split = NULL_INIT;
	int i = 0;
	t_list_arg *tmp = data->lst;
	
	if(ft_strncmp(input, "unset", 5) == 0 && data->lst != NULL)
	{
		split = ft_split(input, ' ');
		if (!split)
			return;
		if (split[i + 1] == NULL)
			return(free_split(split));
		while(tmp)
		{
			printf("%s\n", split[i + 1]);
			printf("%s\n", tmp->key_and_val[0]);
			if(!ft_strcmp(split[i + 1], tmp->key_and_val[0]))
			{ 
				printf("OK\n");
				free_split(split);
				return;
			}
			tmp = tmp->next;
		}
		free_split(split);
	}
}
